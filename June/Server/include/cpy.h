/************************************************************
	�ļ�����cpy.h
	�ļ����ã�����Cpy�����Ժͺ���
	���ߣ�chenzhen
	�������ڣ�2012.06.11
************************************************************/

#ifndef COPY_H
#define COPY_H
#include"ectype_reward_set.h"
#include<iostream>
#include<string>
#include<set>
#include<list>
#include<vector>
#include<time.h>
#include"map_cpy.h"
using namespace std;
class CpyLimit;
class Cpy
{
	list<string> cpyMap;    //������ͼid	
	char cpyId[SHOR_MID_VALUE_LENGTH + 1];
	map<string,Map_Cpy*> instMapSet;   //������ͼʵ��ָ��
	list<string>::iterator src_it;        //������ͼ������
	Map_Cpy *mapNow;    //��ǰ��ͼʵ��ָ��	
	set<string> canEntMapId;  //��ͨ������mapId
	bool flgBusy;             //�����Ƿ����
	CpyLimit *cpyLimit;       //�˸���������ʵ��ָ��

	string olderMapId;        //˳������ͼ
	
	EctypeRewardSet *rewardSet;		//������������
	
	/*��������ʱ��*/
	struct timeval begin;	
	
	/*����������ʱ��*/
	int seconds;
	
	/*ͨ�ظ������ķ�ʱ��*/
	int costTme;
	
	/*��������*/
	map<string,int>heroDieCtn;
	
	/*�÷�*/
	map<string,int>heroGold;
	
	/*�Ƿ��ǽ�ģ���Ϊ���*/
	bool isBorrowFlg;
	
	/*������ʱ���Ƿ�Ϊ���״̬����Ϊ��*/
	bool isTeam;
	
public:
	Cpy(char *_cpyId,list<string>& _cpyMap,CpyLimit *_cpyLimit,int _seconds = 2400);
	
	Cpy(void);
	
	/*�����������ڹ��캯�������*/
	void initMapSet(void);		
	
	/*��������*/
	bool entCpy(vector<string> &heroId);
	
	/*���õ�ǰ������ͼʵ��ָ��*/
	bool instMapNow(char *_mapId);
	
	/*���Դ�ӡ������ͼ��Ϣ����*/
	void printCpyMap(void);
	
	/*��������*/
	~Cpy(void);	
	
	/*����������*/
	bool entCpyMap(vector<string> &heroId,char *_mapId,Point* pTargetPt=NULL);
	
	/*���ø���״̬�Ƿ�Ϊ����*/
	void setFlgBusy(bool _flgBusy);
	
	/*��ø���״̬*/
	bool getFlgBusy(void);
	
	/*����һ������mapId���뵱ǰ��ҿɽ���mapId��������*/
	void inPutCanEntset(void);
	
	/*������ԭ*/
	void recover(void);	
	
	/*��������������*/
	bool entCpyAssist(vector<string> &heroId,int times,char *_mapId,Point* pTargetPt=NULL); 
	
	/*���������²��ϵ*/
	int getEntMapOlder(char *oldMapId,char *newMapId);
	
	/*�˳�����*/
	void exitCpy(vector<string> &heroId);
	
	/*���������Զ�����*/
	void recoverCpy(void);
	
	/*����ͨ��*/
	bool PassCpyJudge(char *_mapId);
	
	/* ��ø��������� */
	EctypeRewardSet *getRewardSet(void);
	
	/*��ʼ����������*/
	void initRewardSet(void);
	
	/*�ж�ʱ���Ƿ�ʱ*/
	bool timeOut(void);
	
	/*���ø���������Ϣ*/	
	void initCpy(void);
	
	/*�������պ������ж�*/
	bool judgeRecover(void);
	
	/*ͨ�غ����ݼ�¼*/
	void passRecord(void);
	
	/*�����˳���������*/
	void exitHero(vector<string> &heroId);
	
	/*������������������*/
	bool entMapAssist(vector<string> &heroId,char *_mapId,Point* pTargetPt);
	
	/*��������������*/
	bool entAssist(vector<string> &heroId,int olderNext);  
	
	/*��������ǰ��"Ԥ����������"����*/
	void goAheadCpy(vector<string> &heroId);
	
	char* getCpyId(void);
	
	/*���͸�������ʵʱ����*/
	void sentLveMonMsg(void);
	
	/*�������˳���������*/
	void exitHero(void);
	
	/*��ø����Ѷ�*/
	int getDiffcult(string _cpyIds);
	
	/*ȫ���˳�����*/
	void exitCpy(void);
	
	/*����ʱ��Ϊ�������÷���*/
	int judgeTmeGole(void);
	
	/*������������Ϊ�������÷���*/
	void judgeDieGole(void);
	
	/*������������Ϊ�������÷���*/
	void judgeAllGole(void);
	
	/*���ɵ÷���Ϣ*/
	void formGoleMsg(char *goleMsg,int length);
	
	/*���͵÷���Ϣ*/
	void sentGoleMsg(char *goleMsg);
	
	/*�÷ִ���*/
	void goleDeal(char *goleMsg,int length);
	
	/*�洢����*/
	void storeGole(void);
	
	/*��vecװ��ҵ�id*/
	void mapToVec(vector<string> &herId);
	
	/*����ʱ��Ϊ�������÷���*/
	int getTmeSecond(void);
	
	/*���ʹ˵�ͼ�Ϲ������Ŀ��Ϣ*/
	void sentMonSumMsg(vector<string> &heroId);
	
	/*������ͨ���������*/
	void testCanPas(void);
	
	/*������������*/
	void ctnDieTme(void);
	
	/*ͨ��mapId�ҵ�mapʵ��*/
	Map_Cpy* getCpyMap(char *mapId);
	
	/*��õ�ͼid����*/
	list<string>& getCpyMapSet(void);
	
	/*��ʼ����չ����*/
	void initBorrowCpy(char *_cpyId,list<string>& _cpyMap,CpyLimit *_cpyLimit,int _seconds  = 30);
	
	/*������չ����*/
	void recoverBorrowCpy(void);
	
	/*��һ����ˢ��ǰ����ʾ*/
	void formNextMonMsg(int groups,int timeSecods);
	
	/*ɾ����ͼ*/
	void deleteMap(void);
	
	/*����Ƿ�Ϊ��ı��ֵ*/
	bool getIsBorrowFlg(void);
	
	/*���ý��븱����״̬*/
	void setIsTeam(bool _isTeam);
	
	/*ͨ�غ��ȥ����ֵ*/
	void minusStrlength(void);
	
	//ˢ��¼
	void recordLessTme();
	
	private:
	
	/*��ľ�¸���ͨ�����ݴ���*/
	bool passTowerLayer(void);
	
};
#endif
	
		

	
