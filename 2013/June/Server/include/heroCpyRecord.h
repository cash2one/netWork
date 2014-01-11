/************************************************************
	�ļ�����heroCpyRecord.h
	�ļ����ã�HeroCpyRecord��ķ��������Ե�����
	���ߣ�chenzhen
	�������ڣ�2012.09.11
************************************************************/
#ifndef HERO_CPY_RECORD_H
#define HERO_CPY_RECORD_H
#include"other_define_data.h"
#include"wholeDefine.h"
#include<iostream>
#include<string.h>
#include<vector>
#include<string>
#include<list>
#include<map>

using namespace std;
const int GLOAD = 1;
const int BLACK = 0;
const int FIRES = 2;
class Hero;


typedef struct CpyStateFlg
{
	char cpyTpeId[LITTLE_MID_VALUE_LENGTH + 1];
	int flg;
	CpyStateFlg(char *_cpyTpeId,int _flg = 0)
	{
		memset(cpyTpeId,'\0',sizeof(cpyTpeId));
		strncpy(cpyTpeId,_cpyTpeId,strlen(_cpyTpeId));
		flg = _flg;
	}
	
	CpyStateFlg(const CpyStateFlg &cpyState)
	{
		memset(cpyTpeId,'\0',sizeof(cpyTpeId));
		strncpy(cpyTpeId,cpyState.cpyTpeId,strlen(cpyState.cpyTpeId));
		flg = cpyState.flg;
	}
	
	CpyStateFlg& operator= (const CpyStateFlg &cpyState)
	{
		memset(cpyTpeId,'\0',sizeof(cpyTpeId));
		strncpy(cpyTpeId,cpyState.cpyTpeId,strlen(cpyState.cpyTpeId));
		flg = cpyState.flg;
		return *this;
	}
		
}CpyStateFlg;

/*������¼���mem*/
typedef struct HeroCpyRecMem
{	
	/*�ѽ������<������>*/
	int entCtn[COPY_SUM_LEVEL];
	
	/*��ͨ����������<�ۼ���>*/
	int passCtn[COPY_SUM_LEVEL];
	
	/*�ɽ��븱��������ÿ��ˢ��*/
	int canEntCtn[COPY_SUM_LEVEL];
	
	/*��ͨ�����������ķ���<�ۼ���>*/
	int passGoldCtn[COPY_SUM_LEVEL]; 
	
	/*����״ֵ̬*/
	int cpyFlg[COPY_SUM_FLG];
	
	int sumPas;                 //���и���ͨ���ܴ���
	int sumEnt;                 //���и��������ܴ���
	int goldSum;                //�ܷ���
	HeroCpyRecMem(void)
	{
		sumPas = 0;
		sumEnt = 0;
	}	
	
	/*�ѽ��븱��map��ʼ��*/
	bool initEntData(map<string,int> &cpyEnterCtn)
	{
		int length,i;	
		map<string,int>::iterator ent_it;
		
		/*�������ȡ������Ϊ��*/		
		length = COPY_SUM_LEVEL;
		for(i = 0,ent_it = cpyEnterCtn.begin();ent_it != cpyEnterCtn.end() &&\
			i < length;++ent_it,++i)
		{
			ent_it->second = entCtn[i];
		}
		return true;
	}
	
	/*�ɽ��븱��map��ʼ��*/
	bool initCanEntData(map<string,int> &cpyCanEntCtn)
	{	
		int length,i;	
		map<string,int>::iterator canEnt_it;
		
		/*�������ȡ������Ϊ��*/		
		length = COPY_SUM_LEVEL;
		for(i = 0,canEnt_it = cpyCanEntCtn.begin();canEnt_it != cpyCanEntCtn.end() &&\
			i < length;++canEnt_it,++i)
		{
			canEnt_it->second = canEntCtn[i];
		}
		return true;
	}
			
	/*��ͨ�ظ���map��ʼ��*/
	bool initPassEntData(map<string,int> &cpyPassCtn)
	{
		int length,i;	
		map<string,int>::iterator passEnt_it;
		
		/*�������ȡ������Ϊ��*/		
		length = COPY_SUM_LEVEL;
		for(i = 0,passEnt_it = cpyPassCtn.begin();passEnt_it != cpyPassCtn.end() &&\
			i < length;++passEnt_it,++i)
		{
			passEnt_it->second = passCtn[i];
		}
		return true;
	}
	
	/*��ͨ�ظ����ķ���map��ʼ��*/
	bool initPassGoldData(map<string,int> &cpyPassGold)
	{
		int length,i;	
		map<string,int>::iterator passGold_it;
		
		/*�������ȡ������Ϊ��*/		
		length = COPY_SUM_LEVEL;
		for(i = 0,passGold_it = cpyPassGold.begin();passGold_it !=\
			cpyPassGold.end() && i < length;++passGold_it,++i)
		{
			passGold_it->second = passGoldCtn[i];
		}
		return true;
	}
	
	/*������״̬��ʼ��*/
	bool initCpyStateFlg(list<CpyStateFlg> &cpyStateFlg)
	{		
		list<CpyStateFlg>::iterator state_it;
		int i,length;
		
		length = COPY_SUM_FLG;
		for(i = 0,state_it = cpyStateFlg.begin();state_it != cpyStateFlg.end() &&\
			i < length;++state_it,++i)
		{
			state_it->flg = cpyFlg[i];
		}
		
		return true;
	}
	/*��ʼ��ͨ������*/
	bool initSumPas(int &sumCpyPas)
	{
		sumCpyPas = sumPas;
		return true;
	}
	/*��ʼ�����и������������*/
	bool initSumEnt(int &sumCpyEnt)
	{
		sumCpyEnt = sumEnt;
		return true;
	}
	
	/*��ʼ�����и����ܷ���*/
	bool initSumGold(int &sumCpyGold)
	{
		sumCpyGold = goldSum;
		return true;
	}
	
	/*����ͨ������*/
	bool updateSumPas(int sumCpyPas)
	{
		sumPas = sumCpyPas;
		return true;
	}
	
	/*����ͨ���ܷ���*/
	bool updateSumGold(int sumCpyGold)
	{
		goldSum = sumCpyGold;
		return true;
	}
	
	/*�������и������������*/
	bool updateSumEnt(int sumCpyEnt)
	{
		sumEnt = sumCpyEnt;
		return true;
	}
	
	/*����canEntCtn������*/
	bool updateCanEntCtnVec(map<string,int> &cpyCanEntCtn)
	{
		map<string,int>::iterator canEnt_it;
		int i,length;	
		if(cpyCanEntCtn.empty())
		{
			return false;
		}		
		length = COPY_SUM_LEVEL;
		for(i = 0,canEnt_it = cpyCanEntCtn.begin();canEnt_it != cpyCanEntCtn.end() &&\
			i < length;++canEnt_it,++i)
		{
			canEntCtn[i] = canEnt_it->second;
		}
		
		return true;
	}
	
	/*����entCtn������*/
	bool updateEntCtnVec(map<string,int> &cpyEnterCtn)
	{
		map<string,int>::iterator ent_it;
		int i,length;
		
		if(cpyEnterCtn.empty())
		{
			return false;
		}
		
		length = COPY_SUM_LEVEL;
		for(i = 0,ent_it = cpyEnterCtn.begin();ent_it != cpyEnterCtn.end() &&\
			i < length;++ent_it,++i)
		{
			entCtn[i] = ent_it->second;
		}
		
		return true;
	}
	
	/*������ͨ�ظ�������*/
	bool upDatePassEntData(map<string,int> &cpyPassCtn)
	{	
		map<string,int>::iterator pass_it;
		int i,length;
		
		if(cpyPassCtn.empty())
		{
			return false;
		}
		
		length = COPY_SUM_LEVEL;
		for(i = 0,pass_it = cpyPassCtn.begin();pass_it != cpyPassCtn.end() &&\
			i < length;++pass_it,++i)
		{
			passCtn[i] = pass_it->second;
		}
		
		return true;
	}
	
	/*������ͨ�ظ�����������*/
	bool upDateCpyStateFlg(list<CpyStateFlg> &cpyStateFlg)
	{	
		
		list<CpyStateFlg>::iterator state_it;
		int i,length;
		
		if(cpyStateFlg.empty())
		{
			return false;
		}
		
		length = COPY_SUM_FLG;
		for(i = 0,state_it = cpyStateFlg.begin();state_it != cpyStateFlg.end() &&\
			i < length;++state_it,++i)
		{
			cpyFlg[i] = state_it->flg;
		}
		
		return true;
	}
	
	/*���¸���״̬*/
	bool upDatePassGoldData(map<string,int> &cpyPassGold)
	{	
		map<string,int>::iterator gold_it;
		int i,length;
		
		if(cpyPassGold.empty())
		{
			return false;
		}
		
		length = COPY_SUM_LEVEL;
		for(i = 0,gold_it = cpyPassGold.begin();gold_it != cpyPassGold.end() &&\
			i < length;++gold_it,++i)
		{
			passGoldCtn[i] = gold_it->second;
		}
		
		return true;
	}
	
	/*�����Ѿ�������*/
	void testEntCtn(void)
	{
		int length,i;
		cout<<"test the entCtn container begin:"<<endl;
		length = COPY_SUM_LEVEL;
		for(i = 0; i < length;i++)
		{
			cout<<"the index:"<<i<<" the values:"<<entCtn[i]<<endl;
		}
		cout<<"test the entCtn container end:"<<endl;
	}
	/*������ͨ������*/
	void testPasCtn(void)
	{
		int length,i;
		cout<<"test the passCtn container begin:"<<endl;
		length = COPY_SUM_LEVEL;
		for(i = 0; i < length;i++)
		{
			cout<<"the index:"<<i<<" the values:"<<passCtn[i]<<endl;
		}
		cout<<"test the passCtn container end:"<<endl;
	}
	/*���Կɽ�������*/
	void testCanEntCtn(void)
	{
		int length,i;
		cout<<"test the canEntCtn container begin:"<<endl;
		length = COPY_SUM_LEVEL;
		for(i = 0; i < length;++i)
		{
			cout<<"the index:"<<i<<" the values:"<<canEntCtn[i]<<endl;
		}
		cout<<"test the canEntCtn container end:"<<endl;
	}
	
	void initRecordMem(void)
	{
		// entCtn.empty();
		
		// passCtn.empty();
		
		// canEntCtn.empty();
		
		sumPas = 0;   
		
		sumEnt = 0;  
	}
		
}HeroCpyRecMem;	

class HeroCpyRecord
{
	Hero *owner;       //����
	map<string,int> cpyEnterCtn;   //ÿ�ָ����ѽ������
	map<string,int> cpyPassCtn;    //ÿ�ָ���ͨ�ش���
	map<string,int> cpyPassGold;    //ÿ�ָ���ͨ�ط���
	map<string,int> cpyCanEntCtn;  //ÿ�ָ����ɽ������
	list<CpyStateFlg> cpyEntState;  //ÿ�ָ���״̬
	int sumCpyPas;                 //���и���ͨ���ܴ���
	int sumCpyEnt;                 //���и��������ܴ���
	int sumGold;                   //���и���ͨ���ܷ���
	
	int canEntTmes;
	int VipEntTotal;          
	
	HeroCpyRecMem myHeroCpyRecMem;     //��������Ķ���
	
	public:
	
	HeroCpyRecord(void);
	
	HeroCpyRecord(HeroCpyRecMem _myHeroCpyRecMem);
	
	void setOwner(Hero *_owner);
	
	/*������ͨ�ظ�����������*/
	void inputPasCtn(char *cpyId);
	
	/*������ͨ�ظ�����������*/
	void inputPasGold(char *cpyId,int gold);
	
	/*�����ѽ��븱����������*/
	void inputEntCtn(char *cpyId);
	
	/*��������*/
	~HeroCpyRecord(void);

	
	/*������ͨ�ظ�������*/
	void initPasCtn(void);
	
	
	/*������еĽ��븱�����ܴ���<��ס��������ÿһ���>*/
	int getEntSum(void);
	
	/*������е�ͨ�ظ������ܴ���<��ס��������ÿһ���>*/
	int getPasSum(void);
	
	/*������е�ͨ�ظ������ܷ���<��ס��������ÿһ���>*/
	int getPasGoldSum(void);
	
	/*�ж��Ƿ���Խ����¸��ȼ��ĸ���*/
	bool judUperRank(char *cpyId);
	
	/*���ÿ�ָ�����״̬*/
	int judgeState(int ent,int can);
	
	/*��ü���*/
	Hero* getOwner(void);
	
	/*�ôӻ����м��ص���������ʼ�����Ա����*/
	bool initRecordDate(void);
	
	/*����ʱ���ðѳ�Ա���ݱ����ڴӻ�����*/
	bool storeRecordDate(void);
	
	/*���ػ�������*/
	HeroCpyRecMem getMyHeroRecMem(void);
	
	
	/*�ж��Ƿ���Խ����¸��ȼ��ĸ���*/
	bool judUperRankAsist(char *cpyId);
	
	/*��ʼ������״ֵ̬*/		
	void initOlder(void);
	
	/*���Ը���״ֵ̬*/
	void testOlder(void);	
	
	/*ͨ�غ����*/
	bool chgState(char *cpyId);
	
	/*�жϸ����Ƿ�ɽ�*/
	bool judgeCanEnt(char *cpyId);
	
	/*�������и���״ֵ̬*/
	void sendEntMsg(void);
	
	/*��ʼ���������������*/		
	void initAllKindMap(void);
	
	/*�ж�ĳ�����Ƿ���ͨ�أ���������id�������Ѷ�*/
	bool isPassCpy(char *cpyId);
	
	/*�������и���*/
	void GMPassAll(void);
};
#endif
	
	