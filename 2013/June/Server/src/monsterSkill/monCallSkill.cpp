/************************************************************
	�ļ�����monCallSkill.cpp
	�ļ����ã�����MonCallSkill���ٻ����ܣ�
	���ߣ�chenzhen
	�������ڣ�2013.05.13
************************************************************/
#include"monCallSkill.h"
MonCallSkill::MonCallSkill(char *_name,char *_id,int _rank,\
double _relPer,double _angVal,double _cdTime,double _playCd,\
double _hrtRatio,bool _lastSki,double _trigPer)\
:SkillBase(_name,_id,_rank,_relPer,_angVal,_cdTime,_playCd,_hrtRatio,\
_lastSki)
{
	trigPer = _trigPer;	
}

/*�ж�����ֵ�Ƿ��Ѿ��ﵽ���ⴥ������*/
bool MonCallSkill::judgeLifePer()
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

/*��������ʵ��*/
SkillBase* MonCallSkill::copySkillInst(MonsterBase *_owner)
{
	char *monId,instId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	if(_owner == NULL)
	{
		return NULL;
	}
	monId = _owner->getIdentity();	
	snprintf(instId + strlen(instId),sizeof(instId),"%s%s%s",monId,"_",id);	
	SkillBase *newSkillInst;
	newSkillInst = new MonCallSkill(name,instId,rank,relPer,angVal,cdTime,\
	playCd,hrtRatio,lastSki,trigPer);
	newSkillInst->initOwner(_owner);
	newSkillInst->initTypeId();
	((MonCallSkill *)newSkillInst)->getCallType();
	return newSkillInst;
}
	
/*ʹ�û�Ѫ���ܼ���*/
bool MonCallSkill::useSkill(vector<string> &herId,bool _station)
{
	/*Ϊ�˶���ʱ���ã����ü������*/
	if(_station || !isOverTme)
	{
		cout<<"the cd or the dingshen station:"<<id<<endl;
		return false;
	}
	
	/*Ѫֵ�������жϷ���Ƶ��,cdʱ���ж�*/
	if(!judgeLifePer() && !judgeRelPer())
	{
		cout<<"the relPercent is not meet:"<<id<<endl;
		return false;
	}
	
	UseSkillAsist(herId);
	
	initCdAndPlayTmer();
	
	return true;
}

/*��������*/
MonCallSkill::~MonCallSkill(void)
{
}

/*��������ʱ����*/
void MonCallSkill::ownerDie(void)
{
	SkillBase::ownerDie();
}

//�����ٻ�����
void MonCallSkill::getCallType(void)
{
	if(strncmp(typeId,"callTypeT",9) == 0)
	{
		typeFlg = 1;
	}
	else if(strncmp(typeId,"callTypeM",9) == 0)
	{
		typeFlg = 2;
	}
	else if(strncmp(typeId,"callTypeTAM",11) == 0)
	{
		typeFlg = 3;
	}
}

//�ٻ�
void MonCallSkill::UseSkillAsist(const vector<string> &herId)
{
	if(typeFlg == 1)
	{
		owner->callTrap(herId);
	}
	
	else if(typeFlg == 2)
	{
		owner->callMon();
	}
	
	else if(typeFlg == 3)
	{
		owner->callTrap(herId);
		owner->callMon();
	}
}
	
	
	

	
