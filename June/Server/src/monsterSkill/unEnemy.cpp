#include"unEnemy.h"
#include"bossSkiThk.h"
#include"user_role_manage_assist.h"
#include"monsterBase.h"
#include"cpyAsist.h"
UnEnemy::UnEnemy(char *_name,char *_id,int _rank,double _relPer,\
double _angVal,double _cdTime,double _playCd,double _hrtRatio,\
bool _lastSki,double _lastTime):SkillBase(_name,_id,_rank,_relPer,\
_angVal,_cdTime,_playCd,_hrtRatio,_lastSki)
{
	lastTime = _lastTime;
}

/*���ɼ���ʹ�ú�������Ϣ,��Ҫ���޵м�����*/
void UnEnemy::formMsg(char *msg_others,int lengStr,char *_heroId)
{
	if(msg_others == NULL || lengStr <= 0)
	{
		cout<<"the skill msg is error:"<<id<<endl;
	}
	snprintf(msg_others,lengStr,"%d,%d,%d,%s,%s,%d,%d,%f",\
			FIGHT_FRIST_HEAD,FIGHT_SECOND_BUFF,OPEN_BUFF,\
			typeId,_heroId,12,0,lastTime);
}
/*ʹ�ü���*/
bool UnEnemy::useSkill(vector<string> &herId,bool _station)
{
	char msg_others[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	/*Ϊ�˶���ʱ���ã����ü������*/
	if(!isOverTme || herId.empty())
	{
		cout<<"the cd or the herId is empty:"<<id<<endl;
		return false;
	}
	
	/*�жϷ���Ƶ��,cdʱ���ж�*/
	if(!judgeRelPer())
	{
		cout<<"the  relPercent is not meet:"<<id<<endl;
		return false;
	}
		
	/*�޵м�����Ϣ����*/
	formMsg(msg_others,sizeof(msg_others));
		
	/*��ϢȺ��*/
	sendMsgNineBox(msg_others);

	/*�����޵�״ֵ̬*/
	owner->setUnEnemySta(true);
	
	/*����������ȴ�Ͳ���ʱ�䶨ʱ��*/
	initCdAndPlayTmer();
	
	/*����ͣ��������������*/
	stopThk();
	
	initTimer();
	
	return true;	
}

/*��ʱ����ʼ������*/
void UnEnemy::initTimer(void)
{	
	ext_ev_timer_init(&think_timer,monSkiUnEnemyCalBack,lastTime,0,this);
	ev_timer_start(loops,&think_timer);		
}

/*��ʱ����ͣ����*/
void UnEnemy::stopThk(void)
{
	ev_timer_stop(loops,&think_timer);
}

/*�޵г���ʱ�䴦��*/
void UnEnemy::recoverUnEnemySki(void)
{
	if(owner == NULL || !owner->getUnEnemySta())
	{
		return;
	}	
	
	owner->setUnEnemySta(false);		
}

/*��������ʵ��*/
SkillBase* UnEnemy::copySkillInst(MonsterBase *_owner)
{
	char *monId,instId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	SkillBase *newSkillInst;
	if(_owner == NULL)
	{
		return NULL;
	}
	monId = _owner->getIdentity();
	snprintf(instId,sizeof(instId),"%s%s%s",monId,"_",id);	
	
	newSkillInst = new UnEnemy(name,instId,rank,relPer,angVal,cdTime,\
	playCd,hrtRatio,lastSki,lastTime);
	
	newSkillInst->initOwner(_owner);
	newSkillInst->initTypeId();
	return newSkillInst;
}

/*��������ʱ����*/
void UnEnemy::ownerDie(void)
{
	stopThk();
	
	if(owner != NULL)
	{
		owner->setUnEnemySta(false);
	}
	SkillBase::ownerDie();
}

UnEnemy::~UnEnemy(void)
{
	stopThk();
}
