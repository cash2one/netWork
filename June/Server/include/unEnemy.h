#ifndef UNENMITY_H
#define UNENMITY_H
#include"skillBase.h"
#include"libev.h"
class UnEnemy : public SkillBase 
{
	double lastTime;          //����ʱ��
	
	ev_timer think_timer;    //��ʱ��
	
public:
	UnEnemy(char *_name,char *_id,int _rank,double _relPer,\
	double _angVal,double _cdTime,double _playCd,double _hrtRatio,\
	bool _lastSki,double _lastTime);
	
	
	/*���ɼ���ʹ�ú�������Ϣ*/
	void formMsg(char *msg_others,int lengStr,char *_heroId = NULL);
	
	/*ʹ�ü���*/
	bool useSkill(vector<string> &herId,bool _station = false);
	
	/*�޵г���ʱ�䴦��*/
	void recoverUnEnemySki(void);
	
	/*��������ʵ��*/
	SkillBase* copySkillInst(MonsterBase *_owner);
	
	/*��ʱ����ʼ������*/
	void initTimer(void);
	
	/*��ʱ����ͣ����*/
	void stopThk(void);
	
	/*��������ʱ����*/
	void ownerDie(void);

	/*��������*/
	~UnEnemy(void);
};
#endif