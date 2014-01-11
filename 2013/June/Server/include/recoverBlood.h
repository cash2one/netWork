/************************************************************
	�ļ�����recoverBlood.h
	�ļ����ã�����recoverBlood��Boss��Ѫ���ܣ�������Ժͳ�Ա
	���ߣ�chenzhen
	�������ڣ�2012.07.13
************************************************************/
#ifndef RECOVER_SBLOOD_H
#define RECOVER_SBLOOD_H
#include"skillBase.h"
#include"monsterBase.h"
class RecoverBlood : public SkillBase
{
	double recoverPer;        //��Ѫ�ٷֱ�
	double trigPer;          //���ⴥ��������Ѫ������ĳһ�ٷֱȣ�
	bool useSkillFlg;           //�Ƿ�����������ܣ����ʾ�ǣ��˼���ֻ����һ�Σ�
public:
	RecoverBlood(char *_name,char *_id,int _rank,double _relPer,\
	double _angVal,double _cdTime,double _playCd,double _hrtRatio,\
	bool _lastSki,double _trigPer,double _recoverPer);
				
	/*�ж�����ֵ�Ƿ��Ѿ��ﵽ���ⴥ������*/
	bool judgeLifePer(void);
	
	/*��Ѫ����*/
	bool gainBlood(int &bloodChg);
	
	/*��������ʵ��*/
	SkillBase* copySkillInst(MonsterBase *_owner);
	
	/*ʹ�ü���*/
	bool useSkill(vector<string> &herId,bool _station = false);
	
	/*������Ϣ*/
	void formMsg(char *msg_others,int lengStr,int bloodChg,char *_heroId = NULL);
	
	/*��������*/
	~RecoverBlood(void);
	
	/*��������ʱ����*/
	void ownerDie(void);
};
#endif

		