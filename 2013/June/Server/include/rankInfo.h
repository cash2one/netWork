/*************************************************

Copyright: xhm

Author:xhm

Date:2012-12-7 

Description:GM server���������߼�ʵ��Դ�ļ���

**************************************************/
#ifndef _RANK_INFO_H
#define _RANK_INFO_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "hero.h"
#include "my_memcached.h"

#define MAX_INFO_TYPE	8						//������Ϣ���ʹ�С

#define MAX_WEALTH_RANK_VALUE 40				//�Ƹ�����λ��
#define MAX_ACTIVITY_RANK_VALUE 40				//�����λ��
#define MAX_POWER_RANK_VALUE 40					//ս������λ��
#define MAX_SHAMBLES_RANK_VALUE 40				//��������λ��
#define MAX_READNAME_RANK_VALUE 40				//��ɱ��������λ��
#define MAX_PRESTIGE_RANK_VALUE 40				//��������λ��
#define MAX_LEVEL_RANK_VALUE 40					//�ȼ�����

#define MAX_RANK_VALUE 40

#define COUNT_FACTIONWAR_MODULUS 2				//�����ս����ϵ��
#define COUNT_ORDCAMPWAR_MODULUS 2				//������Ӫս1����ϵ��
#define COUNT_LEADERCAMPWAR_MODULUS 2			//������Ӫս2����ϵ��
#define COUNT_CHIEFCAMPWAR_MODULUS 2			//������Ӫս3����ϵ��
#define COUNT_ENTER_DUPLICATION_MODULUS 1		//�¸�������ϵ��
#define COUNT_ATTRACK_BOSS_MODULUS 1			//��ɱ�boss����ϵ��

#define LIFE_VALUE_MODULUS  0.01				//���������ֵϵ��
#define MAGIC_VALUE_MODULUS 0.01				//�����ħ��ֵϵ��
#define OUTER_ATTACK_MODULUS  0.5				//�⹦����ϵ��	
#define INTER_ATTACK_MODULUS 0.5				//�ڹ�����ϵ��	
#define OUTER_DEF_MODULUS 0.2					//�⹦����ϵ��	
#define INTER_DEF_MODULUS 0.2					//�ڹ�����ϵ��	
#define HIT_MODULUS 4							//����ϵ��	
#define CRIT_MODULUS 4							//����ϵ��	
#define DUCK_MODULUS 3							//����ϵ��	
#define TOUGH_MODULUS 3						//����ϵ��	

#define COUNT_BE_READNAME_MODULUS 1				//��Ϊ��������ϵ��
#define VALUE_SIN_MODULUS 1						//���ֵϵ��

#define COUNT_READKILLS_MODULUS 1				//ɱ������ϵ��

#define PRESTIGE_MODULUS 1						//����ϵ��

using namespace std;


/**
	������Ϣ�ṹ��
*/
typedef struct RankInfo_S{											
	int grade;														//��ǰ�ȼ�				��������:�ȼ�
	int camp;														//��Ӫ��				��������:����
	char party[2];													//���ɣ�				��������:����
	char HeroName[HERO_MAME_LEN];									//Ӣ������				��������:��������
	char HeroId[HERO_ID_LEN+1];										//Ӣ��ID				��������:����id
	char petId[50];													//����id û����Ϊ0		��������:����ʵ��id
	unsigned long 	value;											//����ֵ��С			��������:ս��
	char petName[50];
	int power;														//����ս��
	
	/*�βι��캯��*/
	RankInfo_S(int _grade,unsigned long _value,char* _HeroName,int _camp,char* _party,char* _heroId,int _power)		
	{
		camp=_camp;
		grade=_grade;
		value=_value;
		memcpy(party,_party,strlen(_party));
		party[strlen(_party)]='\0';
		
		memcpy(HeroId,_heroId,strlen(_heroId));
		HeroId[strlen(_heroId)]='\0';	
		
		memcpy(HeroName,_HeroName,strlen(_HeroName));
		HeroName[strlen(_HeroName)]='\0';
		
		strncpy(petId,"0",sizeof(petId));
		
		strncpy(petName,"0",sizeof(petName));
		
		power=_power;
	}
	
	/*�βι��캯��*/
	RankInfo_S(int _grade,unsigned long _value,char* _HeroName,char* _heroId,char *_petId,char *_petName)		
	{
		grade=_grade;
		value=_value;
		
		memcpy(HeroId,_heroId,strlen(_heroId));
		HeroId[strlen(_heroId)]='\0';	
		
		memcpy(HeroName,_HeroName,strlen(_HeroName));
		HeroName[strlen(_HeroName)]='\0';
		
		strncpy(petId,_petId,sizeof(petId));
		
		strncpy(petName,_petName,sizeof(petName));
		
		camp=-1;
		strncpy(party,"0",sizeof(party));
		power=-1;
	}
	
	/*Ĭ�Ϲ��캯��*/
	RankInfo_S()												
	{
		grade=0;
		value=0;
		camp=-1;
		memset(party,'\0',strlen(party));
		memset(HeroId,'\0',strlen(HeroId));
		memset(HeroName,'\0',strlen(HeroName));
		memset(petId,'\0',strlen(petId));
	}
	
}RankInfo_T;

/**
	��ɫ�μ�����������Ϣ�滺��ṹ��
*/
typedef struct MemRankInfo_S{	
	char powerRankKey[MAX_POWER_RANK_VALUE][HERO_ID_LEN+1];						//����ս��
	RankInfo_T powerRankInfo[MAX_POWER_RANK_VALUE];		
	
	char levelRankKey[40][50];													//�ȼ�����
	RankInfo_T levelRankInfo[40];	

	char wealthRankKey[MAX_WEALTH_RANK_VALUE][HERO_ID_LEN+1];					//�Ƹ�
	RankInfo_T wealthRankInfo[MAX_WEALTH_RANK_VALUE];
	
	char activityRankKey[MAX_ACTIVITY_RANK_VALUE][HERO_ID_LEN+1];				//��Ծ��
	RankInfo_T activityRankInfo[MAX_ACTIVITY_RANK_VALUE];
	
	char shamblesRankKey[MAX_SHAMBLES_RANK_VALUE][HERO_ID_LEN+1];				//ɱ¾
	RankInfo_T shamblesRankInfo[MAX_SHAMBLES_RANK_VALUE];
	
	char prestigeRankKey[MAX_PRESTIGE_RANK_VALUE][HERO_ID_LEN+1];				//����
	RankInfo_T prestigeRankInfo[MAX_PRESTIGE_RANK_VALUE];
	
	char petRankKey[40][50];													//����
	RankInfo_T petRankInfo[40];
	
	char rideRankKey[40][50];													//����
	RankInfo_T rideRankInfo[40];
	
}MemRankInfo_T;

typedef pair<string,RankInfo_T> RANK_PAIR; 								//�Զ���pair����

#define AddRankInfo(a,b) (map<string,RankInfo_T>::value_type(a,b)) 	
#define AddBasicRankInfo(a,b) (map<string,RankBasicInfo_T>::value_type(a,b))	//����map���ݵĲ��룻

using namespace std;

class RankInfo{

public:

RankInfo();
~RankInfo();

/**************************
��������  ��ʼ�����ݣ�
***************************/
void initBasicData();



/**************************
�������� �������ͣ�����ɫ��Ϣ���뵽���������б��У�
�������� _type  ����������Ϣ���ͣ�
		 _value ���ڵ�ǰ��ɫ��������ֵ�Ĵ�С��
  ����ֵ bool 	����ɹ�ture ����false; 
    ���� ��ɫ��ȡ������Ϣʱ��
***************************/
bool updateRankInfo(int _type,unsigned long _value);



/**************************
�������� ��ȡ������Ϣ����Ϣ��string���ͱ�ʾ��
�������� _index ��Ҫ��ȡ����Ϣ�����±ꣻ
  ����ֵ string ��ȡ��Ϣ�ľ���ֵ; 
***************************/
char*  gainRankInfo(int _index);

/**************************
�������� ��ʼ��ȡ������Ϣ�б���memcached�����ȡ���ܲμ������Ľ�ɫ��Ϣ���ұ��棻
  ����ֵ bool ��ȡ��Ϣ�ɹ�; 
    ���� ����ʱ����ã�
***************************/
void setInfoToLocal(void);


/**************************
�������� ������ʱ���ݱ���map��
  ����ֵ bool ��ȡ��Ϣ�ɹ�; 
	���� ��ɫ����ʱ���ã�
***************************/
bool updateTempData(Hero* hero);

void saveRankLog(void);



public:
	vector<map<string,RankInfo_T>*>myRankVector;	//�μ�������ɫ��Ϣ���͹���

	map<string,RankInfo_T>powerRank;				//ս���ʸ�������Ϣ����
	map<string,RankInfo_T>levelRank;				//�ȼ��ʸ���Ϣ����
	map<string,RankInfo_T>wealthRank;				//�Ƹ��ʸ�������Ϣ����
	map<string,RankInfo_T>shamblesRank;				//ɱ¾�ʸ�������Ϣ����
	map<string,RankInfo_T>prestigeRank;				//�����ʸ���Ϣ����
	map<string,RankInfo_T>activityRankInfo;			//������ʸ�������Ϣ����
	map<string,RankInfo_T>petRank;					//�����ʸ���Ϣ����
	map<string,RankInfo_T>rideRank;					//�����ʸ���Ϣ����

	MemRankInfo_T myMemRankInfo;					//�洢memcache�����ݻ�������
	
	char rewardHero[9][50];				//0-2���� 3-5���� 6-8����
	
	void analysis(void);
	
	char rankInfoMsg[50][4096];			// ˳��:ս��,�ȼ�,�Ƹ�,ɱ¾,����,�,����,����

public:
	int power;
	int grade;										//��ǰ�ȼ���
	int camp;										//��Ӫ
	char party[2];									//���ɣ�
	char heroId[HERO_ID_LEN+1];						//��ǰӢ��id;
	char heroName[HERO_MAME_LEN];					//��ǰӢ���ǳƣ�
	char petId[50];									//����ʵ��id
	char petName[50];

	int	RankInfoLastSize[8];			//��һ���������ݵĴ�С��
	unsigned long lowLimit[8];			//��ǰ���Ƽ���������������ƣ�
	int RankCountLimit[8];				//���������������ƣ�
};

#endif
