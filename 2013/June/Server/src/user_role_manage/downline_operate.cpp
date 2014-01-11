//������������Ϣ�ĺ궨��
#include"command_return_define_data.h"
//���й��ߺ�����ͷ�ļ�
#include"command_other_function_all_over.h"
//��ɫ����ͷ�ļ�
#include"command_user_role_manage.h"
//ά����ǰʱ���ͷ�ļ�
#include "my_time.h"
#include "team_operation.h"
#include"role.h"

#include"pet_box.h"

#include"pet.h"

#include"map_inform.h"

#include "team.h"

#include "guild_war_asist.h"

#include "wagon.h"
#include "revival_config.h"

#include "analyzeCampWar.h"

#include"meridian_asist.h"

#include "campWarManagement.h"

#include "rankInfoAsist.h"

#include"boxAsist.h"

#include"commodity.h"

#include "hero_drugs_manage.h"

#include "towerDefTeamAsist.h"

#include "rob_flag_war_logic.h"

#include"cpyAsist.h"
#include "mailSysterm.h"
extern GuildWarAsist *guildWarManage;			//����ս����

extern map<string,Wagon*> wagonInstMap;			//������ʵ��

//�����û��б�
extern list<Role*> idle_role_list;
//���н�ɫ�б�
extern list<Hero*> idle_hero_list;

extern map<int, Role*> fd_to_pRole;

extern map<string,Map_Src*>mapId_connect_map;

//extern map<string, Role*> userName_to_pRole;

extern map<string, Hero*> heroId_to_pHero;

extern map<string,Revival_Config*> mapId_to_revival;		//�����������Ϣ
	

extern map<string,set<string > > tid; //���Ŀ�Ķ�Ӧ����id

extern map<string,set<string > > pid;	//���Ŀ�Ķ�Ӧhero
	
extern map<string,Pet*> id_to_activePet;	

extern campWarManagement campWarController;

extern char server_name[10];

extern Role *pg_role;

extern map<string ,PrivateStall* > onLineStall; //����̯λ

extern map<string, MailSysterm*> mail_map;

extern int sock_fd;
extern Hero* pg_hero;
extern int g_msg_len;
char doneline_info[512];

void doneline_operate(char *buffers)                  
{
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR_END(char* my_hero_id);
	
    map<int,Role*>::iterator role_it; 
    role_it = fd_to_pRole.find(sock_fd);
    if(role_it == fd_to_pRole.end())
    {
        cout<<"[XHM MSG] exit_accident.cpp,find Role error"<<endl;
		sprintf(doneline_info,"1,6,1");
		send_msg(sock_fd,doneline_info);
		//send msg;
        return;
    }
    Role *player;//�������roleʵ��ָ��
    player = role_it->second;
	
    Hero *myHero = player->getActive_hero();//�����������Ϸ����������Ҫ�Իheroʵ�������ߴ���   
	Map_Inform *map_now;
	Nbox *box;	
	char* heroId;
	
    if(myHero != NULL)
    {	
		if(strlen(myHero->getFbRom()) > 0)/*���������˳�����*/
		{
			outCpy(myHero);
		}   
		
        map_now = myHero->getMap();
		
        if(map_now == NULL)
        {
            cout<<"in exit_accident::map_now is NULL"<<endl;
			//send msg;
			sprintf(doneline_info,"1,6,2");
			send_msg(sock_fd,doneline_info);
            return ;
        }
		
        box=map_now->getBox();  	

		if(box == NULL)
		{

			cout<<"it is error:"<<endl;
			sprintf(doneline_info,"1,6,3");
			send_msg(sock_fd,doneline_info);				
			//send msg;
			return;
		}		
		
		myHero->abandTaskBySubType(1, true);
		
		heroId = myHero->getIdentity();
		
		StyObj obj(heroId,HERO_STYLE_TYPE);
		
		box->getStaInSrcVec(obj);
		
		map_now->deleteID(obj);
		
		map_now->delFd(myHero->getFd());
	
		box->heroEnter(myHero,2);   
	
		/*������������״̬����,���Զ�����سǸ���,���������� jolly 10,12 start*/
		if (myHero->getLifeVal()<=0)
		{			
			Map_Src *scene_map=NULL;
			Point revival_pt;
			cout<<"jolly:hero is dead ,so before offline,we should move hero to city at first exit_exception 69"<<endl;
			map<string,Revival_Config*>::iterator it;
			it=mapId_to_revival.find(map_now->getIdentity());
			if (it==mapId_to_revival.end())
			{				
				cout<<"jolly:revival error hero_revival.cpp 154"<<endl;	
				map<string,Map_Src*>::iterator map_it;				
				map_it = mapId_connect_map.find("map_001");
				if (map_it==mapId_connect_map.end())
				{
					cout<<"jolly:map_001 error exit_exception 173"<<endl;
				}					
				else
				{
					scene_map = map_it->second;
					revival_pt=	scene_map->getEntPt();	
					myHero->setMapId("map_001");	
					myHero->setMap(scene_map);
					myHero->setLocation(revival_pt);  						
				}
			}
			else
			{						
				Revival_Config *revival=it->second;
				string revival_map=revival->getRevivalMap();				
				map<string,Map_Src*>::iterator map_it;
				map_it = mapId_connect_map.find(revival_map);
				if(map_it == mapId_connect_map.end())
				{					
					cout<<"Acording to mapid can't find the Mapinform (in hero_revival)"<<endl;
				}
				else
				{	
					scene_map = map_it->second;
					revival_pt._x=revival->getPtx();
					revival_pt._y=revival->getPty();
					myHero->setMapId(revival_map.c_str());
					myHero->setMap(scene_map);
					myHero->setLocation(revival_pt);
				}  
			}
			myHero->setLifeStation(1);
			int revival_life=myHero->getLifeUpperVal();
			int revival_magic=myHero->getMagicUpperVal();
			myHero->setLifeVal(revival_life);
			myHero->setMagicVal(revival_magic);
		}
		cout<<"-------------------------164-------------------------"<<endl;
						
		
		stopMeridianTimer(heroId);//ֹͣ������ʱ
		if (myHero->isInCollecting())
		{
			myHero->stopCollectTimer(6);
		}
		
		if (myHero->getRewardOnline())//��������,��¼���߽��������
		{
			myHero->getRewardOnline()->judgeTotalTime();
		}
		
		// myHero->memHero->offlineTime = MY_TV_SEC;
		cout<<"-------------------------169-------------------------"<<endl;//����ʱ��		
		myHero->memHero->rewarddata.offline_time=MY_TV_SEC;
		Guild* my_guild = myHero->getGuild();
		if(my_guild != NULL)
		{
			//unfinished
			//���������
			my_guild->setHeroOnline(myHero->getIdentity(), false);
			cout<<"-------------------------175-------------------------"<<endl;
			//����ڰ���ս�����У������߳�
			if (myHero->isInGuildWarRoom())
			{
				//�˳�����ս����
				// guildWarManage->exitGuildWar(myHero, true);	
				cout<<"-------------------------180-------------------------"<<endl;
				robFlagWarManage->exitRoom(myHero, true);
			}
		}
#if 1		

		//��������������Ȳ������ֻ������ָ������,
		//�߻�������ҵ���һ��ʱ��֮ǰ��������Լ�����
		char* wagonId = myHero->memHero->wagonId;
		map<string,Wagon*>::iterator wagon_it;
		if (strlen(wagonId) != 0)
		{
			wagon_it = wagonInstMap.find(wagonId);
			if(wagon_it != wagonInstMap.end())
			{	
				Wagon *myWagon = wagon_it->second;
				//�����������
				myWagon->divorceWithOwner(); 
			}
			
		}
#endif	

		/* �����߽�ɫ�����ʼ�����д���ⲿ�ļ� tory */
   		map<string, MailSysterm*>::iterator iter = mail_map.find(myHero->getIdentity());
		if(iter != mail_map.end())	
		{
			MailSysterm* m_s = iter->second;
			if(m_s != NULL)
			{
				m_s->save_mail_data(myHero->getIdentity());
				delete m_s;
			}	
		}  
		mail_map.erase(myHero->getIdentity());
		
		//�����Ƿ��̯��� ��������ֹͣ��̯
		if(myHero->getHeroState()==5)
		{
			//�ҵ������̯λ
			myHero->stall.initPrivateStall();
		}	
		
		//�������ǰ���������ȭ��Ϸ,������˳� jolly add 2013.1.9
		myHero->exitFingerGuessingGame();		//��û�вμ� ���б���
		
		//���½�ɫ����
		updateRankTempData(myHero);
		cout<<"-------------------------229-------------------------"<<endl;
		//���������Ӫս���˳�
		CampData_T campWardata= myHero->getCampWarData();
		cout<<"-------------------------231-------------------------"<<endl;
		/*������Ӫս���ͣ�ѡ����벻ͬ����Ӫս.*/
		int campWarType=campWardata.campWarType;
		cout<<"-------------------------233-------------------------"<<endl;
		switch(campWarType)
		{
		case 1:																//��ӵ���ͨ��Ӫս�У�
			campWarController.exitFromOrdinayCampWar(heroId,campWardata.campWarRoomNum,1);
			break;
		case 2:																//��ӵ�ͳ��������Ӫս�У�
			campWarController.exitFromLeaderCampWar(heroId);
			break;
		case 3:																//��ӵ�����������Ӫս�У�
			campWarController.exitFromChiefCampWar(heroId);	
			break;
		case 4:
			campWarController.exitCampResWar(myHero);
			break;	
		default:
			break;
		}
		


		cout<<"second offLine mapId:"<<map_now->getMapId()<<endl;
		//�����ڵ�ͼ�е�����
        map_now->deleteID(obj); 
		cout<<"-------------------------249-------------------------"<<endl;

		myHero->memHero->rewarddata.offline_time = MY_TV_SEC;		//��¼����ʱ�䣨�룩
		//��������Է�������֮ǰû�浽memcached�е����� by bison
		myHero->memSet();
		
		char account_msg[1024]={'\0'};/*��¼��ɫ���ߵ���ˮ�� jolly 11.15 start*/
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d,%ld,%ld,%ld,%ld",1,3,server_name,(int)myTime.tv_sec,player->getUserName(),myHero->getIdentity(),myHero->getNickName(),\
		myHero->getLevel(),myHero->getMoney()->money_getBoundGold(),myHero->getMoney()->money_getGold(),myHero->getMoney()->money_getBoundGameMoney(),myHero->getMoney()->money_getGameMoney());	
		write_log(account_msg);
		
		myHero->stopTongBuTimer();/*��¼��ɫ���ߵ���ˮ�� jolly 11.15 end*/	
		
        Pet_Box *pet_box=myHero->getPetBox();/*jolly�޸�,��������ȫ�������,�ó�������*/
        Pet *pet=pet_box->getActivePet();

        if(pet!=NULL)
        {					
			cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
            map<string,Pet*>::iterator it;
			string pet_identity=pet->getIdentity();
			it=id_to_activePet.find(pet_identity);
			if (it==id_to_activePet.end())
			{
				cout<<"error-------------------------------------exit_exception.cpp 259"<<endl;
			}
			else
			{	
				pet->send_msg_downLine(myHero);
			}
        }  		
		myHero->endHappyTimer(1);			//ֹͣ����ͼʱ���ʱ
		delete myHero;
	}
	
	sprintf(doneline_info,"1,6,0");
	send_msg(sock_fd,doneline_info);	
	//send_msg;
}