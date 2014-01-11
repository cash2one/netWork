/************************************************************
	�ļ�����recoverBlood.h
	�ļ����ã�����recoverBlood��Boss��Ѫ���ܣ�������Ժͳ�Ա
	���ߣ�chenzhen
	�������ڣ�2012.07.13
************************************************************/
#include"recoverBlood.h"
#include"cpyAsist.h"
RecoverBlood::RecoverBlood(char *_name,char *_id,int _rank,\
double _relPer,double _angVal,double _cdTime,double _playCd,\
double _hrtRatio,bool _lastSki,double _trigPer,double _recoverPer)\
:SkillBase(_name,_id,_rank,_relPer,_angVal,_cdTime,_playCd,_hrtRatio,\
_lastSki)
{
	recoverPer = _recoverPer;
	trigPer = _trigPer;
	useSkillFlg = false;
}

/*�ж�����ֵ�Ƿ��Ѿ��ﵽ���ⴥ������*/
bool RecoverBlood::judgeLifePer()
{
	int lifeUpperVal;
	int lifeVal;
	lifeUpperVal = owner->getLifeUpperVal();
	lifeVal = owner->getLifeVal();
	
	/*�ж�Ѫ���Ƿ����㴥������*/
	if(1.0 * lifeVal/lifeUpperVal <= trigPer)
	{
		return true;
	}
	return false;
}

/*��Ѫ����*/
bool RecoverBlood::gainBlood(int &bloodChg)
{	
	int lifeUpperVal;
	int lifeVal;	
	bloodChg = -1;
	/*Ϊ�˶���ʱ���ã����ü������*/
	if(!isOverTme || useSkillFlg)
	{
		return false;
	}
	
	/*Ѫֵ�������жϷ���Ƶ��,cdʱ���ж�*/
	if(!judgeLifePer() && !judgeRelPer() )
	{
		cout<<"the relPercent is not meet:"<<id<<endl;
		return false;
	}
	
	lifeUpperVal = owner->getLifeUpperVal();
	lifeVal = owner->getLifeVal();
	bloodChg = lifeUpperVal * recoverPer;
	lifeVal += bloodChg;
		
	/*���Ѫ����������*/
	if(lifeVal >= owner->getLifeUpperVal())
	{
		lifeVal = owner->getLifeUpperVal();
	}	
	
	/*��Ѫ*/
	owner->setLifeVal(lifeVal);
	
	
	/*����������ȴ�Ͳ���ʱ�䶨ʱ��*/
	initCdAndPlayTmer();
	
	useSkillFlg = true;
	return true;
	
}

/*��������ʵ��*/
SkillBase* RecoverBlood::copySkillInst(MonsterBase *_owner)
{
	char *monId,instId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	if(_owner == NULL)
	{
		return NULL;
	}
	monId = _owner->getIdentity();	
	snprintf(instId + strlen(instId),sizeof(instId),"%s%s%s",monId,"_",id);	
	SkillBase *newSkillInst;
	newSkillInst = new RecoverBlood(name,instId,rank,relPer,angVal,cdTime,\
	playCd,hrtRatio,lastSki,trigPer,recoverPer);
	newSkillInst->initOwner(_owner);
	newSkillInst->initTypeId();
	return newSkillInst;
}

/*���ɼ���ʹ�ú�������Ϣ*/
void RecoverBlood::formMsg(char *msg_others,int lengStr,int bloodChg,char *_heroId)
{
	if(msg_others == NULL || lengStr <= 0 || bloodChg <= 0)
	{
		cout<<"the skill msg is error:"<<id<<endl;
		return;
	}
	
#if	0
	cout<<"msg_others begin:"<<msg_others<<endl;
	cout<<"msg_others typeId:"<<typeId<<endl;
	cout<<"msg_others strlen(msg_others):"<<strlen(msg_others)<<endl;
	cout<<"msg_others lengStr:"<<lengStr<<endl;
	cout<<"msg_others owner->getIdentity():"<<owner->getIdentity()<<endl;
	cout<<"msg_others owner->getLifeUpperVal():"<<owner->getLifeUpperVal()<<endl;
	cout<<"msg_others owner->getLifeVal():"<<owner->getLifeVal()<<endl;
	cout<<"msg_others owner->getMagicVal():"<<owner->getMagicVal()<<endl;
	cout<<"msg_others owner->getMagicUpperVal():"<<owner->getMagicUpperVal()<<endl;
	cout<<"msg_others bloodChg:"<<bloodChg<<endl;
	cout<<"msg_others playCd:"<<playCd<<endl;
	
#endif	

	cout<<"recover blood begin:"<<typeId<<endl;
	
	snprintf(msg_others,lengStr,"%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d",\
	26,2,1,typeId,(int)playCd,owner->getIdentity(),owner->getLifeVal(),\
	owner->getLifeUpperVal(),owner->getMagicVal(),owner->getMagicUpperVal(),bloodChg);
	
	cout<<"recover sendMsg:"<<msg_others<<endl;
	
	cout<<"recover blood end:"<<typeId<<endl;
	
#if 0	
	snprintf(msg_others + strlen(msg_others),lengStr - strlen(msg_others),"%d%s%d%s%s%s%s%s%d",\
			MONSTER_SKILL_HEAD,",",MONSTER_SKILL_CHANGE_PRO,",",\
			owner->getIdentity(),",",typeId,",",owner->getLifeVal());	
#endif
}
	
/*ʹ�û�Ѫ���ܼ���*/
bool RecoverBlood::useSkill(vector<string> &herId,bool _station)
{
	char msg_recoverBlood[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	int bloodChg;
	/*�жϻ�Ѫ�����Ƿ񴥷�*/
	if(gainBlood(bloodChg) && bloodChg > 0)
	{
		/*��Ѫ����ʹ�ú��γ���Ϣ*/
		formMsg(msg_recoverBlood,sizeof(msg_recoverBlood),bloodChg);
		
		/*��Ѫ����ʹ�ú󣬷�����Ϣ*/
		sendMsgNineBox(msg_recoverBlood);
		return true;
	}
	return false;
}

/*��������*/
RecoverBlood::~RecoverBlood(void)
{
}

/*��������ʱ����*/
void RecoverBlood::ownerDie(void)
{
	SkillBase::ownerDie();
	useSkillFlg = false;
}

	
