/*
        �ļ����ͣ�ʵ���ļ�
        �ļ����ƣ�command_other_function_game_flight_other.cpp
        �ļ����ã�����Ҵ򶷲����������õĺ�����ʵ��
*/


#include"game_fight_assist.h"

#include<math.h>        
#include<sys/time.h>
#include<unistd.h>  
#include<map>       
#include"command_fight_function_other.h"

#include"command_return_define_data.h"

#include"command_other_function_all_over.h"
#include"map_inform.h"

#include"skill.h"
#include"dropgoods.h"  //add by jolly
#include"monsterBase.h"
#include"hero_help.h"
#include"pet_box.h"
#include"user_role_hero_attack_manage.h"
#include"boxAsist.h"
extern map<string,Map_Inform*>mapId_connect_map;
extern map<string,Hero*>heroId_to_pHero;


/*������Χ���ж�*/
int attackRangePoint(Point pt_attack,Point pt_hited,int attack_range)
{
    int flag_attackRange=1;
    double distance=0.0;
    distance=pow(fabs(pt_attack._x-pt_hited._x),2)+pow(fabs(pt_attack._y-pt_hited._y),2);     
    distance=sqrt(distance);
//	cout<<"jude distance:"<<(int)distance<<endl;
//	cout<<"attack_range+32:"<<attack_range + 32<<endl;
//	cout<<"pt_attack._x:"<<pt_attack._x<<" pt_attack._y:"<<pt_attack._y<<endl;
//	cout<<"pt_hited._x:"<<pt_hited._x<<" pt_hited._y:"<<pt_hited._y<<endl;
    if(int(distance) < attack_range + 32)
    {
        return flag_attackRange;        
    } else
    {
        //	//cout<<"can attackattack_range"<<attack_range<<endl;
        flag_attackRange=0;
        return flag_attackRange;
    }
}
/*
    �޸����ݣ���ҹ�����ҳɹ�������Ϣ
    �޸��ˣ�Evan
    �޸�ʱ�䣺2012.4.10
*/
#if 0
void send_success(Hero *attack,Hero *hited,Skill *skill,int redlose)
{
    string msg_attack = "2";       //�����ɹ���Ϣ	
    msg_attack = msg_attack + intTostring(ATTACK_RETURN_SELF);
    msg_attack = msg_attack + intTostring(SUCCESS);
    string skillid = skill->getid();//������ʹ�õļ���Id
    char *attackid = attack->getIdentity();//������Id
    int lifeval = attack->getLifeVal();    //������Ѫֵ
    int magicval = attack->getMagicVal();  //��������ʣ��ֵ
    
    /*�������ߵ�Ѫֵ�ı� evan add 2012.7.61*/
    HeroHelp *herohelp;
    herohelp = attack->getherohelp();   
	int lifeval_add = herohelp->getlife_change();                   //�����ߵ�ǰѪֵ�仯
	herohelp->setlife_change(0);
	attack->setherohelp(herohelp);
    /*�������ߵ�Ѫֵ�ı� evan add 2012.7.31*/
    char *hitid = hited->getIdentity();    //��������Id	
    int lifeval_hited = hited->getLifeVal();//����������ʣѪֵ
    msg_attack = msg_attack + "," + skillid + charTostring(attackid) + intTostring(lifeval) + intTostring(magicval) + intTostring(lifeval_add) +
                 charTostring(hitid) + intTostring(lifeval_hited)+intTostring(redlose);
    //cout<<"attack hero msg_attack:"<<msg_attack<<endl;	
    Map_Inform *map_now;
    map_now = attack->getMap(); 
	
	if(map_now == NULL)
	{
		return;
	}
    Nbox *box=map_now->getBox();    
	if(box == NULL)
	{
		return;
	}
	StyObj obj(attack->getIdentity(),HERO_STYLE_TYPE);
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(const_cast<char *>(msg_attack.c_str()));
	
    /*����Ҳ���ս������ʱ����Ҳ����ƶ� evan add 2012.7.19 starting*/
    struct timeval tv;
    struct timezone tz;
    gettimeofday (&tv , &tz);
    int sec_now = tv.tv_sec;                             //��ȡϵͳ��ǰʱ�䣺��
    HeroHelp *attackhelp;
    attackhelp = attack->getherohelp();
    attackhelp->setisyd(true);                      //��������������ʱ����Ҳ����ƶ�
    int time_sec = skill->gettime_sec();                //��������ʱ��
    attackhelp->setisyd_contime(time_sec);              
    attackhelp->setisyd_now_time(sec_now);              //�������ſ�ʼʱ��
    attack->setherohelp(attackhelp);
    /*����Ҳ���ս������ʱ����Ҳ����ƶ� ending*/
}
#endif
/*
    �޸����ݣ���ҹ�������ɹ�������Ϣ
    �޸��ˣ�Evan
    �޸�ʱ�䣺2012.4.17*/

#if 0
void attack_monster_success(Hero *attack,MonsterBase *hited,Skill *skill,int redlose)
{
    string msg_attack = "2";                //��������ɹ����ص���Ϣ
    msg_attack = msg_attack + intTostring(ATTACK_RETURN_SELF);
	msg_attack = msg_attack + intTostring(SUCCESS);
    
	#if 0
	//tory add 2012.7.20 starting
	if(attack == NULL || hited == NULL skill == NULL )
	{
		cout<<"return from game_fight_assist::attack_monster_success,cause NULL"<<endl;
		return ;
	}
    string mapsId = hited->getMapId();
    if(mapsId.find("ectype_map_046") != string::npos)   //����������(��ʱͨ����ǰ�������ڵĵ�ͼ�����)
    {
        HatVal* hatva = hited->getOneEnmityValues();
        if(hatva != NULL)
        {
            string des_heroId = hatva->id;
            map<string, Hero*>::iterator hero_it;
            hero_it = heroId_to_pHero.find(des_heroId);
            if(hero_it == heroId_to_pHero.end())
            {
               cout<<"return from game_fight_assist::attack_monster_success,cause can't find the enermy hero: "<<des_heroId<<endl;
			   return ;
            }
            Hero *in_hero = hero_it->second;            //in_hero--->�����ж���Χ֮�ڰ����Ľ�ɫ	
            //cout<<"before in_hero->getAttracMonNum()"<<in_hero->getAttracMonNum()<<endl;
            in_hero->delAttracMonId(hited->getIdentity());
			//cout<<"after in_hero->getAttracMonNum()"<<in_hero->getAttracMonNum()<<endl;          
        }
    } 
    //tory add 2012.7.20 ending
	#endif
	
	string skillid = skill->getid();//������ʹ�õļ���Id
    char *attackid = attack->getIdentity();//������Id
    int lifeval = attack->getLifeVal();    //������Ѫֵ
    int magicval = attack->getMagicVal();  //��������ʣ��ֵ
	char *hitid = hited->getIdentity();    //��������Id	
	int lifeval_hited = hited->getLifeVal();//����������ʣѪֵ	
    /*�������ߵ�Ѫֵ�ı� evan add 2012.7.61*/
    HeroHelp *herohelp;
    herohelp = attack->getherohelp();   
	int lifeval_add = herohelp->getlife_change();                   //�����ߵ�ǰѪֵ�仯
	herohelp->setlife_change(0);
	attack->setherohelp(herohelp);
    /*�������ߵ�Ѫֵ�ı� evan add 2012.7.31*/
    
    msg_attack = msg_attack + "," + skillid + charTostring(attackid) + intTostring(lifeval) + intTostring(magicval) + intTostring(lifeval_add) +
                 charTostring(hitid) + intTostring(lifeval_hited)+intTostring(redlose);
    Map_Inform *map_now;
    map_now = attack->getMap();
	if(map_now == NULL)
	{
		return;
	}
	     
    Nbox *box=map_now->getBox(); 
	if(box == NULL)
	{
		return;
	}
	
	StyObj obj(attack->getIdentity(),HERO_STYLE_TYPE);
	
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(const_cast<char *>(msg_attack.c_str()));
	
    
    //	//cout<<"attack monster msg_attack:"<<msg_attack<<endl;
    /*����Ҳ���ս������ʱ����Ҳ����ƶ� evan add 2012.7.19 starting*/
    struct timeval tv;
    struct timezone tz;
    gettimeofday (&tv , &tz);
    int sec_now = tv.tv_sec;                             //��ȡϵͳ��ǰʱ�䣺��
    HeroHelp *attackhelp;
    attackhelp = attack->getherohelp();
    attackhelp->setisyd(true);                      //��������������ʱ����Ҳ����ƶ�
    int time_sec = skill->gettime_sec();                //��������ʱ��
    attackhelp->setisyd_contime(time_sec);              
    attackhelp->setisyd_now_time(sec_now);              //�������ſ�ʼʱ��
    attack->setherohelp(attackhelp);
    /*����Ҳ���ս������ʱ����Ҳ����ƶ� ending*/
	if(lifeval_hited <= 0)
	{
		// if(map_now->getFlgCpy())
		// {
			// hited->die(true);
		// }
		// else
		// {
			// hited->die();
		// }
		
	}

}
#endif



