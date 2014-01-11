/****************************************************************
 * Filename: hero_attack_wagon.cpp
 * 
 * Description: ������
 *
 * Original Author : bison, 2012-9-10
 *
 ****************************************************************/
#include"attack_wagon.h"
#include"hero.h"
// #include"command_game_fight_manage.h"
#include"task_failed_comm.h"
#include"wholeDefine.h"

extern map<string,Wagon*> wagonInstMap;						//��ʵ��
extern map<string, Hero*> heroId_to_pHero;					//���ʵ��
extern map<string,Pet*>	id_to_activePet;					//����ʵ��

extern int sock_fd; 
extern int g_msg_len;
extern Hero* pg_hero;

void attactWagonComm(char *buff)
{
#if 0
	char *wagonId;							//��Id
	char *skillId;							//ʹ�ü��ܵ�Id
	int index = 0;							//����������
	
	MSG_BEGIN(buff, g_msg_len);
	MSG_INT(index);
	MSG_CHAR(wagonId);
	MSG_CHAR_END(skillId);
	
	//��fd��heroʵ��
	Hero *hero = pg_hero;
	
	map<string,Wagon*>::iterator it_wagon;
	//cout<<"BisonTest��wagonInstMap size is "<<wagonInstMap.size()<<endl;
	it_wagon = wagonInstMap.find(wagonId);
	if (it_wagon == wagonInstMap.end())
	{
		//û�������
		cout<<"BisonTest: Attack failed because of no the wagon of this id "<<wagonId<<endl;
		return;
	}
	
	Wagon *wagon = it_wagon->second;
	
	Map_Inform *wagonMap = hero->getMap();
	if (wagonMap == NULL)
	{
		cout<<"This Map no Id ????????????????????"<<endl;
		return;
	}
	char *wagonMapId = wagonMap->getIdentity();
	if (strcmp(wagonMapId, "map_001") == 0)
	{
		cout<<"You can't attack wagon In This Map"<<endl;
		return;
	}
	char* owerId;
	Hero *owner = wagon->getOwner();
	if (owner == NULL)
	{
		cout<<"This wagon has no owner, but you can attack it"<<endl;
		goto LG;	//û�����˵���Ҳ�ܱ���
		// return;
	}
	//�����˲��ܴ��Լ�����
	owerId = owner->getIdentity();
	if (!strcmp(owerId, hero->getIdentity()))
	{
		return;
	}
LG: ;	
	//ȫ�����ص�
	Point wagonLocation = wagon->getPt();
	int range;			//�����ߵĹ�����Χ
	//bool isLive;		//���Ƿ񻹻���
	int distance = 0;	//��������������
	
	Skill *skill; 
	//int skillNeedMagic = 0;						//���ܵ�ħ������
	int attackLife = 100;						//�����ߵ�ǰѪ��������Ϊ���������ֵ
	int attackMagic = 100;						//������ħ��������Ϊ���������ֵ
	//int attackHurt = wagon->getHurt();			//��ÿ�α�������Ѫ�̶�
	//index = 0 Ϊ�˹�����
	if (index == 0)
	{
		map<string,Skill*> attack_skill_list;				//��ҽ�ɫ�ļ����б�	
		map<string,Skill*>::iterator skill_iter;
		attack_skill_list = hero->getSkill_list();	
		skill_iter = attack_skill_list.find(skillId);
		if(skill_iter == attack_skill_list.end())
		{
			cout<<"BisonTest: hero does not has this skill to use when attack wagon"<<endl;
			return;
		}                   
		skill = skill_iter->second;							//�����ʹ�õļ���
		
		if (skill->gettype() != 1 || skill->geteffect() != 1)
		{
			//������Ⱥ������ҽ�ƣ�ֻҪ�����������ܶ�����������
			cout<<"skill type can't attack wagon"<<endl;
			return;
		}
		
		if(!isFightStatusOfHero(hero, skill))					//�ж���ҵ��������ͼ��ܵ�ʱ���Ƿ��������
		{
			cout<<"BisonTest: magical or time is not ok to use this skill"<<endl;
			return;
		}
		
		cout<<"BisonTest: Hero attacks the wagon "<<wagonId<<endl;
		//�жϾ����Ƿ�
		Point heroLocation = hero->getLocation();
		int deltaX = wagonLocation._x - heroLocation._x;
		int deltaY = wagonLocation._y - heroLocation._y;
		int distance = sqrt(deltaX * deltaX + deltaY * deltaY);
		range = hero->getAtk_range();
		cout<<"BisonTest: distance is "<<distance<<" hero attack range is "<<range<<endl; 
		if (distance > range)
		{
			cout<<"BisonTest: The wagon is out attack range"<<endl;
			return;
			
		} else {
			//�������߿���
			//hero->setMagicVal(hero->getMagicVal() - skillNeedMagic);
			PropertyOfAttackerChange(hero, skill);
			//��ҵĵ�ǰѪ��
			attackLife = hero->getLifeVal();		//�ѵ����й�����������Ѫ�����������������������
			attackMagic = hero->getMagicVal();
		}
	} else if (index == 1) {
		//index = 1��Ϊ�������
		Pet *pet = hero->getPetBox()->getActivePet();
		if (pet == NULL)
		{
			cout<<"BisonTest: hero have no active Pet "<<endl;
			return;
		} else {
			//����λ��
			Point petLocation = pet->getLogicNow();
			petLocation = LogicalExchangeMap(petLocation);
			int deltaX = wagonLocation._x - petLocation._x;
			int deltaY = wagonLocation._y - petLocation._y;
			int distance = sqrt(deltaX * deltaX + deltaY * deltaY);
			range = pet->getAttackRange();
			cout<<"BisonTest: distance is "<<distance<<" pet attack range is "<<range<<endl; 
			if (distance > range)
			{
				cout<<"BisonTest: The wagon is out attack range"<<endl;
				return;
				
			} 
		}
	} else {
		return;
	}
	
	attackWagon(hero->getIdentity(), attackLife, attackMagic, skillId, wagonId);
#endif
}

void attackWagon(char* attackerId, int attackerCurLife, int attackerCurMagic, char* skillId, char* wagonId)
{
#if 0
	Hero *attHero;
	Map_Inform *map_now;
	Nbox* box;
	map<string,Wagon*>::iterator it_wagon;
	//cout<<"BisonTest��wagonInstMap size is "<<wagonInstMap.size()<<endl;
	it_wagon = wagonInstMap.find(wagonId);
	if (it_wagon == wagonInstMap.end())
	{
		//û�������
		return;
	}
	attHero = heroid_to_hero(attackerId);
	if(attHero == NULL)
	{
		return;
	}
	
	Wagon *wagon = it_wagon->second;
	
	// string msg;						//��Ϣ
	map<string,StyObj> nbox_id_set;		//���ľŹ����Ա
	Point wagonLocation = wagon->getLogicPt();
	Point piexPt;
	piexPt = attHero->getLocation();	
	StyObj obj(wagonId,WAGON_STYLE_TYPE);
	
	//��ȡ���ľŹ���,���ù����߾Ź���
	map_now = attHero->getMap();
	if(map_now == NULL)
	{
		return;
	}
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	box->getStaInSrcVec(obj);
	
	cout<<"BisonTest: nbox size is "<<nbox_id_set.size()<<endl;
	bool isLive = wagon->beAttacked();
	
	char msg[400];
	//����Χ�˷�����������Ϣ
	// msg = "2";
	// msg += intTostring(ATTACK_RETURN_SELF);
	// msg += intTostring(SUCCESS);
	// msg = msg + "," + skillId;
	// msg = msg + "," + attackerId;
	// msg += intTostring(attackerCurLife);
	// msg += intTostring(attackerCurMagic);
	// msg += intTostring(0);
	// msg += "," + wagonId;
	// msg += intTostring(wagon->getLifeVal());
	// msg += intTostring(wagon->getHurt());
	// msg += intTostring(0);			//�����ޱ���������
	// msg += intTostring(piexPt._x);	
	// msg += intTostring(piexPt._y);
	sprintf(msg, "2,%d,1,%s,%s,%d,%d,0,%s,%d,%d,0,%d,%d", ATTACK_RETURN_SELF, skillId, attackerId,
		attackerCurLife, attackerCurMagic, wagonId, wagon->getLifeVal(), wagon->getHurt(),
		piexPt._x, piexPt._y);
	box->sentBoxMsg(msg);
	
	cout<<"BisonTest isLive value is "<<isLive<<endl;
	//���Ѿ�����
	if (!isLive)
	{
		cout<<"[BisonSHow] the wagon has been distroyed!"<<endl;
		//��Ź�����������Ϣ
		wagon->disperMsg();
			
		wagonInstMap.erase(wagonInstMap.find(wagonId));
		
		Hero *owner = wagon->getOwner();
		if(owner != NULL)
		{
			
			//hero����û����
			strncpy(owner->memHero->wagonId, "\0", 2);	
			
			//��ҵ�������ʧ��
			char taskId[10] = "task00295"; 
			taskFailedDeal(owner, taskId, 1);
			strncpy(taskId, "task00419", 10);
			taskFailedDeal(owner, taskId, 0);
		}
		
		/* Task *task = owner->delAcceptedTaskList(taskId);
		string msg = "5";
		msg += intTostring(TASK_FAILED_RETURN);
		msg += "," + taskId;
		send_msg(owner->getFd(), msg);
		if (task != NULL)
		{
			delete task;
		} */
		delete wagon;
	}
#endif
}
 