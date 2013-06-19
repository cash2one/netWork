/************************************************************
	�ļ�����skillBase.h
	�ļ����ã�����SkillBase��Boss���ܻ��ࣩ������Ժͳ�Ա
	���ߣ�chenzhen
	�������ڣ�2012.07.13
************************************************************/
#ifndef SKILL_BASE_H
#define SKILL_BASE_H
#include<string>
#include<vector>
#include<time.h>
#include"wholeDefine.h"
#include"libev.h"
#include"bossSkiThk.h"
/*�ƻ�֮��������*/
#define DELUDE 1    
   
/*���޵���������*/
#define TIGHT_ENCIRCLE 2   
 
/*��ȭ���۵�����*/
#define FIST 3          


/*�˴��ǻط����ͻ��˵���Ϣ�꣬���澭���Ϻ󣬻�ɾ��*/
const int MONSTER_SKILL_HEAD  = 2;   //���＼��ͷ����
const int MONSTER_SKILL_TYPE = 14;  //Ⱥ������
const int MONSTER_SKILL_SINGLE = 13;  //�������ֻ�Ƕ���
const int MONSTER_SKILL_CHANGE_PRO = 15;  //����˲���ı�����
const int HIT_TYPE_HERO = 1;
const int HIT_TYPE_MONSTER = 0;
const int STAND_STILL_ID = 1;           //����id��Ϊ��������＼�ܣ�����
const int STAND_STILL_FUNCTION = 1;           //����id��Ϊ��������＼�ܣ�����

const int MONSTER_SKILL_RECOVER_BLOOD_ID  = 14; //��Ѫ����
const int RECOVER_BLOOD_FUNCTION = 2;                  //��Ѫ����

const int STAND_UNENEMY_FUNCTION = 13;          //�޵м���


class MonsterBase;
using namespace std;
class SkillBase
{
protected:	
	char name[SHOR_MID_VALUE_LENGTH + 1];              //��������
	char id[SHOR_MID_VALUE_LENGTH + 1];                //����ʵ��id 
	char typeId[SHOR_MID_VALUE_LENGTH + 1];            //��������id<�����ͻ��˵ļ���id>
	int rank;                 //���ܵȼ�
	double relPer;        	 //�ͷ�Ƶ��
	double angVal;			 //��������ŭ��ֵ
	double cdTime;           //cdʱ��
	MonsterBase *owner;      //�˼���ʹ���ߵĹ���
	double hrtRatio;         //�����˺�ϵ��
	bool lastSki;     //�����Ƿ�Ϊ�������ܣ�trueΪ����ʱ�似�ܣ�falseΪ˲�����ܣ�	
	

	double playCd;           //���ܲ���ʱ��

	ev_timer think_timer;    //��ʱ��,���Ʋ���ʱ�䣬�Լ���ȴʱ��
	
	bool isOverTme;          //���ţ��Լ���ȴʱ�䶼����,ture ��ʾ���˼�������ȴ�Ҳ�����
	
	
public:
	SkillBase(char *_name,char *_id,int _rank,double _relPer,double _angVal,\
	double _cdTime,double _playCd,double _hrtRatio,bool _lastSki);
	
	/*��ü�������*/
	char* getName(void);
	
	/*��ü���id*/
	char* getId(void);
	
	/*��ü���id������getId����*/
	char* getIdentity(void);
	
	/*��ü���ʹ�õȼ�*/
	int getRank(void);
	
	/*��ü��ܴ���Ƶ��*/
	double getRelPer(void);
	
	/*��ü��ܴ�������ŭ��ֵ*/
	double getAngVal(void);
	
	/*��ü���cdʱ��*/
	double getCdTme(void);
	
	/*�жϼ��ܴ���Ƶ���Ƿ�����*/
	bool judgeRelPer(void);
	
	/*�жϼ��ܴ���ŭ��ֵ�Ƿ�����*/
	bool judgeAngVal(void);
	
	/*��ʼ���˼�������*/
	void initOwner(MonsterBase *monster);
	
	/*��ô˼�������*/
	MonsterBase* getOwner(void);
	
	/*�жϴ˼����Ƿ�Ϊ�ɳ���*/
	bool getLastSki(void);
	
	/*��������ʱ����*/
	virtual void ownerDie(void);
	
	/*��������ʵ��*/
	virtual SkillBase* copySkillInst(MonsterBase *_owner);
	
	/*ʹ�ü���*/
	virtual bool useSkill(vector<string> &herId,bool _station = false);
	
	/*���ͼ���ʹ�ú���Ϣ��������*/
	void sendOneMsg(char *_heroId,char *msg_others);
	
	/*���ͼ���ʹ�ú���Ϣ��Ⱥ����*/
	void sendMsgNineBox(char *msg_others);
	
	/*��������������Ϊ�麯��*/
	virtual ~SkillBase(void);
	
	/*��ü����˺�ϵ��*/
	double getHrtRatio(void);
	
	/*��ʼ����������id*/
	void initTypeId(void);
	
	/*��ü�����ȴʱ���cdʱ���Ƿ��ѹ�*/
	bool getIsOverTme(void);
	
	/*���ü�����ȴʱ���cdʱ���Ƿ��ѹ�*/
	void setIsOverTme(bool _isOver);	
	
	/*��������cd�Ͳ���cd��ʱ��*/
	void initCdAndPlayTmer(void);
	
	/*��ͣ��ʱ��*/
	void stopTme(void);
};
#endif
	
	