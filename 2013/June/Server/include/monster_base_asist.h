#ifndef MONSTER_BASE_ASIST_H
#define MONSTER_BASE_ASIST_H
#include<time.h>
#include<string>
#include<math.h>
using namespace std;
/************************************************************
	�ļ�����monster_base_asist.h
	�ļ����ã���MonsterBase��ĸ����������ݽṹ
	���ߣ�chenzhen
	�������ڣ�2012.08.29
************************************************************/

#define MON_DEBUF_DIZZ_STATE			0x1				//ѣ��
#define MON_DEBUF_FORB_MOVE_STATE		0x2				//�����ɲ��������ƶ�
#define MON_DEBUF_FORB_ATTK_STATE		0x4				//��Ѩ�����ƶ�
#define MON_DEBUF_IN_POISON_STATE		0x8				//�ж���������Ѫ
#define	MON_DEBUF_LOSE_HIT_STATE 		0x10			//��ʧ����������
#define MON_DEBUF_LOSE_DF_AT_STATE		0x20			//���𣺼�������
#define MON_DEBUF_LOSE_TENC_STATE		0x40			//��������������
#define MON_DEBUF_LOSE_SPEED_STATE		0x2000			//�����ƶ��ٶ�






/*��ʱ�Լ���*/
typedef struct SkillTime
{
	double cdTimes;                 //����ʱ��
	int alCtn;                      //�Ѿ��ܹ���ʱ�䣨�����˼��������
	int thkCnt;                     //�����˼������
	int effectType;                 //����Ч������,Ϊ�˽����չ
	int values;                  //ÿ�ε�Ѫ����
	char attheroId[SHOR_MID_VALUE_LENGTH + 1];               //������id
	
	
	SkillTime(char *_heroId,double _cdTimes,int _effectType,int _values)
	{
		memset(attheroId,'\0',SHOR_MID_VALUE_LENGTH + 1);
		alCtn = 0;
		cdTimes = _cdTimes;
		thkCnt = ceil(cdTimes/MONSTER_THINK_TIME);
		effectType = _effectType;
		values = _values;
		if(_heroId != NULL)
		{
			strncpy(attheroId,_heroId,strlen(_heroId));
		}
	}
	
	SkillTime(const SkillTime &skillTme)
	{
		memset(attheroId,'\0',sizeof(attheroId));
		alCtn = skillTme.alCtn;
		cdTimes = skillTme.cdTimes;
		thkCnt = ceil(cdTimes/MONSTER_THINK_TIME);
		effectType = skillTme.effectType;
		values = skillTme.values;		
		strncpy(attheroId,skillTme.attheroId,strlen(skillTme.attheroId));
		
	}
	
	SkillTime& operator= (const SkillTime &skillTme)
	{
		memset(attheroId,'\0',sizeof(attheroId));
		alCtn = skillTme.alCtn;
		cdTimes = skillTme.cdTimes;
		thkCnt = ceil(cdTimes/MONSTER_THINK_TIME);
		effectType = skillTme.effectType;
		values = skillTme.values;		
		strncpy(attheroId,skillTme.attheroId,strlen(skillTme.attheroId));
		return *this;		
	}
	
	
	
	/*cdʱ���ж�*/
	bool timeOut(void)
	{
		return alCtn >= thkCnt;
	}
	
	/*"ʱ��"����*/
	void gain(void)
	{
		alCtn++;
	}
	
	/*ʱ���Ƿ�Ϊ������*/
	bool sentPos(void)
	{
		return alCtn %2 == 0;
	}
		
}SkillTime;	

/*���������������*/	
typedef struct LveCtnManger
{
	int sumLveCtn;                     //������
	int durTme;                     //ˢ��������ۺϳɵ�ͼ˼��������
	int lvedCtn;                    //��ˢ��������
	int waitTme;                    //ʱ��ȴ�����
	LveCtnManger(int _sumLveCtn = 1,int _durTme = 0)
	{
		sumLveCtn = _sumLveCtn;
		durTme = _durTme;
		
		lvedCtn = 1;
		waitTme = 0;
	}
	
	LveCtnManger(const LveCtnManger &lveCtn)
	{
		sumLveCtn = lveCtn.sumLveCtn;
		durTme = lveCtn.durTme;
		
		lvedCtn = lveCtn.lvedCtn;
		waitTme = lveCtn.waitTme;
	}
	
	LveCtnManger& operator= (const LveCtnManger &lveCtn)
	{
		sumLveCtn = lveCtn.sumLveCtn;
		durTme = lveCtn.durTme;
		
		lvedCtn = lveCtn.lvedCtn;
		waitTme = lveCtn.waitTme;
		
		return *this;
	}
	
	
	/*�������Ƿ�ˢ��*/
	bool isLveCtn(void)
	{
		lvedCtn++;
		if(lvedCtn <= sumLveCtn)
		{	
			waitTme = 0;
			return true;
		}
		return false;			
	}
	
	/*�ж�ˢ��ʱ���Ƿ�*/
	bool isWaitTme(void)
	{
		if(waitTme >= durTme)
		{
			return true;
		}
		waitTme++;
		return false;		
	}
	
	/*����*/
	void initCover(void)
	{
		lvedCtn = 1;
		waitTme = 0;
	}
	/*��������*/
	int testPro(void)
	{
		cout<<"sumLveCtn:"<<sumLveCtn<<endl;
		cout<<"lvedCtn:"<<lvedCtn<<endl;
		cout<<"durTme:"<<durTme<<endl;	
		return sumLveCtn;		
	}
	
	bool isAliveAgin(void)
	{
		return lvedCtn <= sumLveCtn;		
	}
		
		
}LveCtnManger;

#endif