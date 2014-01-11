/************************************************************
	�ļ�����rigidity.h
	�ļ����ã�����Rigidity��Boss�����ܣ�������Ժͳ�Ա
	���ߣ�chenzhen
	�������ڣ�2012.07.13
************************************************************/
#ifndef RIGIDITY_H
#define RIGIDITY_H
#include<set>
#include"data_structure_struct.h"
#include"skillBase.h"
#include"libev.h"
class Rigidity : public SkillBase
{
	ev_timer think_timer;    //��ʱ��
	ManMonSkiTme skiTme;
	double lastTime;        //����ʱ��
	double trigPer;          //���ⴥ��������Ѫ������ĳһ�ٷֱȣ�
	bool flgThk;            //��ʱ���Ƿ���ͣ
public:
	Rigidity(char *_name,char *_id,int _rank,double _relPer,\
	double _angVal,double _cdTime,double _playCd,\
	double _hrtRatio,bool _lastSki,double _trigPer,\
	double _lastTime);
				
	/*�ж�����ֵ�Ƿ��Ѿ��ﵽ���ⴥ������*/
	bool judgeLifePer(void);
	
	/*������*/
	bool standStill(vector<string> &heroId);
	
	/*��������ʵ��*/
	SkillBase* copySkillInst(MonsterBase *_owner);
	
	/*��ʱ����ʼ������*/
	void initTimer(void); 
	
	/*��ͣ˼��*/
	void stopThk(void);	
	
	/*������Щ�м�������id*/
	void insertHerId(vector<string> &heroId);
	
	/*��˼�������������*/
	bool response(void);
	
	/*����˺�����ʱ��*/
	double getLastTme(void);
	
	/*ʹ�ü���*/
	bool useSkill(vector<string> &herId,bool _station = false);
	
	/*�γ���Ϣ*/
	void formMsg(char *msg_others,int lengthStr,char *_heroId = NULL);
	
	/*���ܳ���ʱ�䵽����������id*/
	bool delHerId(void);
	
	/*��������*/
	~Rigidity(void);
	
	/*���ñ�������Ҷ�ʱ���ֵ����*/
	bool setHerStiFlg(string &heroId,bool _flg);
	
	/*��ö�������*/
	int getStillType(char *_skillId);
	
	/*��������ʱ����*/
	void ownerDie(void);
};
#endif

		