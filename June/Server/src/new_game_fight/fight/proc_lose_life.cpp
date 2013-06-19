#include"hero_fight.h"

#include"dropgoods.h"

// #include "TD_Instancing.h"	//����������ͷ�ļ�

#include "instancing_manage.h"		//����������ͷ�ļ�

#include "campWarManagement.h"		//��Ӫս������ͷ�ļ�

#include "guild_war_asist.h"		//����ս������ͷ�ļ�

#include"task_failed_comm.h"

#include"hatValRue.h"
#include "sitControl.h"
#include"monsterActiveBoss.h"
#include"monsterStatuary.h"
extern HatValRue *hatValRue; 
 
extern map<string,Map_Src*>mapId_connect_map;

extern campWarManagement campWarController;

extern Instancing_manage *Inst_MNG;

extern GuildWarAsist *guildWarManage;			//����ս����

extern map<string,Wagon*> wagonInstMap;						//��ʵ��

void proc_hero_lose_life(Hero* atker, Hero* atked, unsigned lifeHurt)
{
	atked->stopCollectTimer(3);			//��ұ�������ϲɼ�
	if (lifeHurt == 0)
	{
		return;
	}
	
	cout<<"***********************"<<endl;
	cout<<"atked state:"<<atked->getHeroState()<<endl;
	cout<<"atker state:"<<atker->getHeroState()<<endl;
	cout<<"***********************"<<endl;
	cancelSit(atker);
	cancelSit(atked);
	
	int lifeVal = atked->getLifeVal();
	if (lifeVal <= lifeHurt)
	{
		atked->setLifeVal(0);
		atked->setLifeStation(DEAD);
		
		if (atker == NULL)
		{
			return;
		}
		
		//ս����Ҷ��ڰ���ս������
		if (atker->isInGuildWarRoom() && atked->isInGuildWarRoom())
		{
			//���ӹ����ߵ��˺�ͳ��
			guildWarManage->hurtCount(atker, lifeHurt);
			if (atked->getLifeStation() == DEAD)
			{
				//���ӹ����ߵ�ɱ����
				guildWarManage->killCount(atker);
			}
		}
		
		//������Ӫս���ݣ���������RTX xhm;
		if(atked->getLifeStation()==DEAD)
		{
			// if (atker->getTaskState() & TASK_NEED_PK_HERO)
			{
				string heroMapId = atker->getMapId();
				if (heroMapId == "map_021")
				{
					atker->updateHeroTaskStatus(PK_OTHER_HERO_TASK_NEED_TYPE, (char*)"pk", 1);
					atker->clrTskStSomeBit(TASK_NEED_PK_HERO);
				}
			}
			
			if(atked->getisRedName())//�������ɱ���Ǻ��������ӽ�ɫ��ɱ����ֵ��С��
			{
				if(atker->addReadNameKillsValue(1))
					cout<<"[XHM WARNING] AddReadNameKillsValue ERROR(game_fight_help_property_attackerAndhiter.cpp)."<<endl;
			}
			
			if(atked->isInCampWar()&&atker->isInCampWar())//�����ɱ�ߺͱ���ɱ�߶�������Ӫս�У�ִ�����²�����
			{
				int campWarType = atked->getCampWarType();//�������ɱ���������ϣ����ӱ���ɱ�ߵ�����������
				if (campWarType == 4)
				{
					campWarController.campResWarKill(atker, atked);
				}
				else 
				{
					if(campWarType >= 2&& campWarController.addDeathInCampWar(atked) < 0)
					{
						cout<<"[XHM WARNING] Added deaths in the CampWar ERROR(game_fight_help_property_attackerAndhiter.cpp)."<<endl;
					}
					
					campWarType = atker->getCampWarType();//�����ɱ���������ϣ����ӻ�ɱ�ߵ�ɱ�д�����
					if(campWarType >= 1 && campWarController.addKillsInCampWar(atker) < 0)
					{
						cout<<"[XHM WARNING] Added kills in the CampWar ERROR(game_fight_help_property_attackerAndhiter.cpp)."<<endl;
					}
				}
				
			}
		}
		/*�����ж�*/
		atker->term(atked);
		
	} else {
		atked->setLifeVal(lifeVal - lifeHurt);
	}
}

void proc_mon_lose_life(Hero *atker, MonsterBase* mon, unsigned lifeHurt)
{
	if (lifeHurt == 0)
	{
		/*add chenzhen 201301311556 ����Ҳ��������*/
		HatVal hatval(atker->getIdentity(), hatValRue->getGenHitPer() * 10);  
		
		mon->InpushEnmityValues(hatval);
		
		/*������Ӧ����*/
		mon->setRepFlg(true);
			/*���ֵ end*/
		mon->response();
		
		return;
	}
	
	int lifeVal = mon->getLifeVal();
	mon->setGoodsOwner(atker->getIdentity());
	// cout<<"lifeVal is "<<lifeVal<<" and lifeHurt is "<<lifeHurt<<endl;
	if (lifeVal <= lifeHurt)
	{
		mon->setLifeVal(0);
	//	mon->setLifeStation(DEAD);        //chenzhen add 20130109
		mon->setLifeStation(false);
		/*������������*/	
		char* heroId=atker->getIdentity();
		char* ownerId=mon->getGoodsOwner();	
		
		/*�bossû��������*/
		if(strcmp(mon->getType(),"ActiveBossMon") == 0)
		{			
		
	//		strncpy(ownerId,"0",2);
			
			/*׷��ͷ�Σ�boss�ս���*/
			atker->addTitle("T050");
			
		}
		monsterDropGoods(ownerId,mon);
		// dropTaskGoods(atker, mon);
		
		/*add chenzhen by 201301291511 �boss����ֳ�*/
		if(strcmp(mon->getType(),"ActiveBossMon") == 0)
		{
			/*��¼���һ��*/
			((MonsterActiveBoss*)mon)->inputLastHero(atker->getIdentity());			
			
			cout<<"give the last hero begin:"<<atker->getIdentity()<<endl;
			/*�����һ�����˾���*/
			getexperience(atker, mon);
			cout<<"give the last hero end:"<<atker->getIdentity()<<endl;
			string firstHeroId = ((MonsterActiveBoss*)mon)->getFirstHero();
			Hero *firstHurt = heroid_to_hero(firstHeroId);
			if(firstHurt)
			{
				cout<<"give the first hero begin:"<<firstHurt->getIdentity()<<endl;
				/*����һ�����˾���*/
				getexperience(firstHurt,mon);
				cout<<"give the first hero end:"<<firstHurt->getIdentity()<<endl;
			}
			
		}		
		else
		{
			// cout<<"ownerId is:"<<ownerId<<endl;
		
			// cout<<"ownerId:"<<ownerId<<"         heroId:"<<heroId<<endl;
			if (strcmp(ownerId,heroId)==0)
			{			
				dropTaskGoods(atker, mon);
				getexperience(atker, mon);
			}
			else
			{
				Hero *monsterOwner = heroid_to_hero(ownerId);
				if (monsterOwner != NULL)
				{
					dropTaskGoods(monsterOwner, mon);
					// cout<<"test begin():"<<endl;
					getexperience(monsterOwner, mon);
					// cout<<"test end():"<<endl;
				}
			}
		}
		//cout<<"property_attackerAndhiter:jolly add dropgoods end"<<endl;
		
		//Tory add 2012.7.20 starting �����������������ֵ����
		//����������,����������Ӧ����������ID�ӽ�ɫ���������Id�б���ɾ��
		string behavior_type = mon->getType();
		if(behavior_type.find("Tower") != string::npos)   	
		{
			HatVal* hatva = mon->getOneEnmityValues();
			if(hatva != NULL)
			{
				string des_heroId = hatva->id;
				map<string, Hero*>::iterator hero_it;
				hero_it = heroId_to_pHero.find(des_heroId);
				if(hero_it == heroId_to_pHero.end())
				{
					cout<<"return from attack_monster_success,cause can't find the enermy hero: "<<des_heroId<<endl;
				}
				Hero *in_hero = hero_it->second;            //in_hero--->�����ж���Χ֮�ڰ����Ľ�ɫ	
				//cout<<"before in_hero->getAttracMonNum()"<<in_hero->getAttracMonNum()<<endl;
				in_hero->delAttracMonId(mon->getIdentity());		//����������ID����ɾ���������˵Ĺ���ID
				//cout<<"after in_hero->getAttracMonNum()"<<in_hero->getAttracMonNum()<<endl;        
			}
				
			Map_Inform *map_now = mon->getMap();
			string td_room = map_now->getTd_roomid();
			TD_Instancing *this_inst = Inst_MNG->id2tdRoom(td_room);
			this_inst->AddSelfInstancingStatus(INST_STATUS_HELP_VAL);			//ͳ�ƻ�ɱ������Ŀ�����Ӷ���ֵ
			this_inst->AddSelfInstancingStatus(INST_STATUS_MONSTER_DISAPPEAR);	//MONSTER_DISAPPEAR��1
			
		}
		// cout<<"die monsterId:"<<mon->getIdentity()<<endl;
		/*add chenzhen by 201303221511 �����*/
		if(strcmp(mon->getType(),"MonStatuary") == 0)
		{
			/*��¼���һ��*/
			((MonsterStatuary*)mon)->setHeroId(atker->getIdentity());			
		}
		mon->die();
		//tory add 2012.7.20 ending
    } else {
	
		mon->setLifeVal(lifeVal - lifeHurt);
		
		/*add by chenzhen 201301291514 �boss����¼��һ������*/
		if(strcmp(mon->getType(),"ActiveBossMon") == 0)
		{
			((MonsterActiveBoss*)mon)->inputFirstHero(atker->getIdentity());
		}
		
		/*add chenzhen by 201303221511 �������ʱû�з�Ӧ*/
		if(strcmp(mon->getType(),"MonStatuary") == 0)
		{
			return;		
		}
		
		//���ֵ start
		//cout<<"property_attackerAndhiter:chenzhen monster chouhen start"<<endl;
		HatVal hatval(atker->getIdentity(), hatValRue->getGenHitPer() * lifeHurt);   	
		mon->InpushEnmityValues(hatval);
		
		/*������Ӧ����*/
		mon->setRepFlg(true);
			/*���ֵ end*/
		mon->response();
			//cout<<"property_attackerAndhiter:chenzhen monster chouhen end"<<endl;
		
	}
}

void proc_wagon_lose_life(Hero* atker, Wagon* wagon, int lifeHurt)
{
	bool isLive = wagon->beAttacked();
	if (!isLive)
	{
		cout<<"[BisonSHow] the wagon has been distroyed!"<<endl;
		//��Ź�����������Ϣ
		wagon->disperMsg();
			
		wagonInstMap.erase(wagon->getIdentity());
		
		Hero *owner = wagon->getOwner();
		if(owner != NULL)
		{
			
			//hero����û����
			memset(owner->memHero->wagonId, 0, sizeof(owner->memHero->wagonId));
			//��ҵ�������ʧ��
			char taskId[10] = "task00295"; 
			taskFailedDeal(owner, taskId, 1);
			strncpy(taskId, "task00419", 10);
			taskFailedDeal(owner, taskId, 0);
		}
		delete wagon;
	}
}


void proc_bottle_lose_life(Hero* atker, Bottle* bottInst, int lifeHurt)
{
	bool isCHg = false;
	bottInst->beAttack(atker->getIdentity());
	
	cout<<"go proc_bottle_lose_life begin:"<<bottInst->getLifeVal()<<endl;

	if(bottInst->getLifeVal() == 0)
	{
		//����ƿ�޵���
		dropTaskGoods(atker,bottInst);

		useMoneyBox(atker,bottInst->getTypeId(),bottInst->getPiexPt());
		
		/*add chenzhen 20130128 ����ƿ�޻�������߻�һ��������Ѫ����*/
		int reBlod = bottInst->getBloodPre() * atker->getLifeUpperVal();
		int reMagic = bottInst->getMagicPre() * atker->getMagicUpperVal();
		
		cout<<"go proc_bottle_lose_life second:"<<endl;
		
		if(atker->getLifeVal() < atker->getLifeUpperVal())
		{
			reBlod += atker->getLifeVal();
			if(reBlod >= atker->getLifeUpperVal())
			{
				reBlod = atker->getLifeUpperVal();
			}
			atker->setLifeVal(reBlod);
			isCHg = true;
			cout<<"the now blood :"<<atker->getLifeVal()<<endl;
		}
	
		if(atker->getMagicVal() < atker->getMagicUpperVal())
		{
			reMagic += atker->getMagicVal();
			if(reMagic >= atker->getMagicUpperVal())
			{
				reMagic = atker->getMagicUpperVal();
			}
			atker->setMagicVal(reMagic);
			isCHg = true;
			cout<<"the now magic :"<<atker->getMagicVal()<<endl;
		}
		
		cout<<"go proc_bottle_lose_life thrid:"<<endl;
		
		cout<<"the blood :"<<atker->getLifeVal()<<endl;
#if 0		
		/*���ͻ��˸�������*/
		if(isCHg)
		{		
			atker->send_msg_att();
		}
#endif	
	}
	
	
	
	
}