/************************************************************
	�ļ�����monCallSkill.h
	�ļ����ã�����MonCallSkill���ٻ����ܣ�������Ժͳ�Ա
	���ߣ�chenzhen
	�������ڣ�2013.05.09
************************************************************/
#ifndef MON_CALL_SKILL_H
#define MON_CALL_SKILL_H
#include"skillBase.h"
#include"monsterBase.h"
class MonCallSkill : public SkillBase
{
	double trigPer;          //���ⴥ��������Ѫ������ĳһ�ٷֱȣ�
	int typeFlg;             //�ٻ����ͣ�1��ֻ�ٻ����� 2��ֻ�ٻ��� 3���ٻ�����͹�
public:
	MonCallSkill(char *_name,char *_id,int _rank,double _relPer,\
	double _angVal,double _cdTime,double _playCd,double _hrtRatio,\
	bool _lastSki,double _trigPer);
				
	/*�ж�����ֵ�Ƿ��Ѿ��ﵽ���ⴥ������*/
	bool judgeLifePer(void);
	
	/*��������ʵ��*/
	SkillBase* copySkillInst(MonsterBase *_owner);
	
	/*ʹ�ü���*/
	bool useSkill(vector<string> &herId,bool _station = false);
	
	/*��������*/
	~MonCallSkill(void);
	
	/*��������ʱ����*/
	void ownerDie(void);
	
	//�����ٻ�����
	void getCallType(void);
	
	private:
	
	//�ٻ�
	void UseSkillAsist(const vector<string> &herId);
	
	
};
#endif

		