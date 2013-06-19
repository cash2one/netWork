/************************************************************
	�ļ�����cpyLimit.h
	�ļ����ã�����CpyLimit�����Ժͺ���
	���ߣ�chenzhen
	�������ڣ�2012.06.11
************************************************************/

#ifndef CPY_LIMIT_H
#define CPY_LIMIT_H
#include<vector>
#include<string>
#include"cpy.h"
#include "instancing_manage.h"

/*��45����֮��ĸ�����������������ڿ����*/
const int CPYRANK = 45;

/*���븱��������ʾ��Ϣ*/

/*�˸���û�п���*/
const int ERROR_NO_OPEN = 0; 

/*����Ѻ��״̬*/
const int ERROR_YA_BIAO = 1;

/*����pk����*/
const int ERROR_PK = 2;

/*����ǰ����ڣ����ʾ���ɵȼ�����*/
const int IS_PARTY_LEVE_LOW = 3;

/*�ڸ�����*/
const int ERROR_IN_COPY = 4;

/*û�м����κΰ���*/
const int ERROR_NOT_JOIN_PARTY = 5;

/*���˽�����ʱ������ӣ��Ҳ��Ƕӳ�*/
const int ERROR_IN_TEAM = 6;

/*���˽�����ʱ���������ǻ��߸���npc����*/
const int ERROR_IN_MAIN_CITY = 7;

/*���˽�����ʱ�����ڶ�Ӧ�����ǻ���npc����*/
const int ERROR_IN_JL_NPC = 8;

/*���˽�����ʱ�����ڶ�Ӧ�����ǻ���npc����*/
const int ERROR_IN_KF_NPC = 9;

/*���˽�����ʱ�����ڰ�̯״̬*/
const int ERROR_IN_SELL = 10;

/*���˽�����ʱ�����ڰ�̯״̬*/
const int ERROR_OTHER = 11;

/*�����񸱱�ʱ�����ǵ���*/
const int ERROR_NOT_ONE_PERSON = 12;

/*��������ɫ�ȼ�����*/
const int ERROR_LOWER_RANK = 14;

/*��������ɫ����ֵ����*/
const int ERROR_LOWER_LAST_POWER = 13;


/*�����ľ�¸�����û�п���*/
const int TOWER_LAYER_COPY_TOWER_CLOSED = 15;

/*�����ľ�¸�����û�п���*/
const int TOWER_LAYER_COPY_LAYER_CLOSED = 16;

/*�����ľ�¸���������*/
const int TOWER_LAYER_COPY_TOWER_ERROR = 17;

/*�����ľ�¸��������*/
const int TOWER_LAYER_COPY_LAYER_ERROR = 18;

/*�����ľ�¸���ID����*/
const int TOWER_LAYER_COPY_COPY_ERROR = 19;

/*���ֵ�ͼ*/
const int ERROR_IN_HAPPY = 20;

using namespace std;

typedef struct CpyMemRecord
{
	char nickName[HERO_MAME_LEN + 1];	//���֣�
	char party[PARTY_LEN];				//���ɣ�
	char heroId[HEROID_LENGTH + 1];  	//id
	char guildName[101];                //��������
	int grad;							//�ȼ�	
	int campFlg;                       //��Ӫ��־
	size_t vipLevel;                   //vip�ȼ�
	size_t recordTme;               	//ͨ�ؼ�¼
	
private:

	int values1;
	int values2;
	int values3;	
	char otherVal[200];               //Ԥ������ֵ

public:

	CpyMemRecord(const CpyMemRecord& memRecord)
	{
		init();		
		strncpy(nickName,memRecord.nickName,strlen(memRecord.nickName));
		strncpy(party,memRecord.party,strlen(memRecord.party));
		strncpy(heroId,memRecord.heroId,strlen(memRecord.heroId));
		grad = memRecord.grad;
		campFlg = memRecord.campFlg;
		vipLevel = memRecord.vipLevel;
		recordTme = memRecord.recordTme;
	}
	
	CpyMemRecord()
	{
		init();		
	}
	
	explicit CpyMemRecord(Hero *recordHero,size_t _recordTmes)
	{
		init();
		
		if(!recordHero)
		{
			cout<<"CpyMemRecord CpyMemRecord(const Hero *recordHero,size_t _recordTmes) the  recordHero is NULL:"<<endl;
		}
		
		strncpy(nickName,recordHero->getNickName(),strlen(recordHero->getNickName()));
		strncpy(party,recordHero->getParty(),strlen(recordHero->getParty()));
		strncpy(heroId,recordHero->getIdentity(),strlen(recordHero->getIdentity()));
		grad = recordHero->getGradeNow();
		campFlg = recordHero->getCamp();
		vipLevel = recordHero->getVipStage();
		recordTme = _recordTmes;
	}
	
	bool changeRecord(Hero *recordHero,size_t _recordTmes)
	{
		if(!recordHero)
		{
			cout<<"changeRecord the  recordHero is NULL:"<<endl;
			return false;
		}
		if(strlen(heroId) != 0)
		{			
			if(recordTme <= _recordTmes)
			{
				cout<<"changeRecord the  _recordTmes is not the lower record:"<<endl;
				return false;
			}
		}
		
		init();
		strncpy(nickName,recordHero->getNickName(),strlen(recordHero->getNickName()));
		strncpy(party,recordHero->getParty(),strlen(recordHero->getParty()));
		strncpy(heroId,recordHero->getIdentity(),strlen(recordHero->getIdentity()));
		grad = recordHero->getGradeNow();
		campFlg = recordHero->getCamp();
		vipLevel = recordHero->getVipStage();
		recordTme = _recordTmes;
		return true;
	}
		
		
	CpyMemRecord& operator=(const CpyMemRecord& memRecord)
	{
		init();		
		strncpy(nickName,memRecord.nickName,strlen(memRecord.nickName));
		strncpy(party,memRecord.party,strlen(memRecord.party));
		strncpy(heroId,memRecord.heroId,strlen(memRecord.heroId));
		grad = memRecord.grad;
		campFlg = memRecord.campFlg;
		vipLevel = memRecord.vipLevel;
		recordTme = memRecord.recordTme;
	}

private:	
	void init()
	{
		memset(nickName,'\0',sizeof(nickName));
		
		memset(party,'\0',sizeof(party));
		
		memset(heroId,'\0',sizeof(heroId));
		
		memset(guildName,'\0',sizeof(guildName));
		
		grad = 0;
		campFlg = -1;
		vipLevel = 0;
		recordTme = 0;
	}
	
}CpyMemRecord;


class CpyLimit
{
	//������̬�ģ�����Ⱥ����,ͳ�����ã�����������
	size_t totalSize;

	int num;         //��������Ҫ������
	int rank;        //��������Ҫ��ȼ�
	int room;         //����������
	char cpyId[SHOR_MID_VALUE_LENGTH + 1];     //����id
	char cpyLimitId[SHOR_MID_VALUE_LENGTH +1];  //��������id
	char name[SHOR_MID_VALUE_LENGTH +1];  //��������
	vector<Cpy*> initCpyRom; //��������
	
	list<int> asistList;     //�����������Թ���������
	
	//��̬�������±�
	set<int> dynamicUsedIndex;
	
	//������ķ��ۺţ���Ӧ��manager�е��±��
	map<int,int> dyRomIndexToMagIndex;
	
	
	//�����еĿտײ���
	list<int> dynamicUseAbleIndex;
	
	int judgeTme;            //����ʱ��
	double jugGodRat;           //����ϵ��
	int baseGole;            //������
	map<string,EctypeRewardSet*> swapHeroRewardMap;   //ɨ������
	
	size_t costFatigue;           //��������ֵ
	 
	CpyMemRecord* memRecord;      //ͨ�ؼ�¼
	
public:
	/*���캯��*/
	CpyLimit(char *_cpyLimitId,char *_cpyId,char *_name,int _baseGole,int _judgeTme,double _jugGodRat,int _num,int _rank,size_t costFatigue,\
	int _room);
	
	/*��ø���������*/
	int getRoom(void);  
	
	/*���븱������*/
	void PushCpy(Cpy *newCpy);
	
	/*���븱���ʸ����*/
	bool qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason,\
					 bool isTol = false,bool isParty = false);
	
	/*��ӽ�����*/
	string enable_enter_cpy(vector<string> &heroId, Failure_Reason* reason,bool isParty = false);
	
	/*����շ���,��������*/
	void assignRom(vector<string> &heroId,int roomNum);
	
	/*���븱��*/
	void enterRom(int _roomNum,vector<string> &heroId,char *_mapId,Point *pTargetPoint=NULL);
	
	/*�������շ���*/
	void recoverRom(char *_cpyId);
	
	/*�˳�����*/
	void exitCpy(int _roomNum,vector<string> &heroId);
	
	/*�жϸ��������Ƿ񳬳��ܷ�����*/
	bool roomExist(int _roomNum);
	
	/*��ø���������*/
	Cpy* getRoomCpy(int roomNum);  
	
	/*���Ҫ��ȼ�*/
	int getRank(void);
	
	/*��ø����Ѷ�*/
	int getDiffcult(void);
	
	/*������֮ǰ�������뷿���ȷ��*/
	bool qualifyExamLast(vector<string> &heroId,int &_roomNum);
	
	/*���䷿�䣬�ҽ�����,���˽�*/
	void assignRom(vector<string> &heroId);
	
	/*�������ʱ��*/
	int getJdgTme(void);
	
	/*�������ϵ��*/
	double getJdgRat(void);
	
	/*��������*/
	~CpyLimit(void);
	
	/*ͨ��room,�Լ�mapId�ҵ�mapʵ��*/
	Map_Cpy* getMapCpy(int room,char *mapId);
	
	
	/*��չ����*/
	bool borrowCpyFun(void);
	
	/*��չ��������*/
	void recoverBorrowCpy(int indexList);
	
	char *getCpyId(void);
	
	/*��û�����*/
	int getBaseGole(void);
	
	/*��Ӻ��ж�Ա��ͬ��֮�󣬻����Ǹ�Ԥ���ķ����*/
	void recoverRom(int roomNum);
	
	/*ֻ�ܵ��˽����񸱱����*/
	bool taskCpyQualifyExam(vector<string> &heroId,Failure_Reason* failure_reason);
	
	/*���˽���ľ�¸������*/
	bool qualifyExamTowerLayerCopy(vector<string> &heroId,Failure_Reason* failure_reason);
	
	/*����ɨ����������*/
	void insertWipeOut(char *heroId);
	
	/*ɾ��ɨ����������*/
	void eraseWipeOut(char *heroId);
	
	const char* getName() const;
	
	size_t getCostFatigue() const;
	
	CpyMemRecord* getRecord();
	
	void recordLessTme(const char* recordHeroId,size_t secondstimes);
	
	//ȡ
	void initMemRecord();
	
	//��
	void storeMemRecord();
	
	private:
	
	/*���ɨ����������*/
	void clearWipeOut(void);
	
	
	
	
};
#endif
