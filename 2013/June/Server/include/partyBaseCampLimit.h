/************************************************************
	�ļ�����partyBaseCampLimit.h
	�ļ����ã�����PartyBaseCampLimit�����Ժͺ���
	���ߣ�chenzhen
	�������ڣ�2012.12.14
************************************************************/

#ifndef PARTY_BASE_CAMP_LIMIT_H
#define PARTY_BASE_CAMP_LIMIT_H
#include "instancing_manage.h"
#include"wholeDefine.h"
#include<vector>
#include<string>
#include<list>



/*û�м����κΰ���*/
const int CAMP_ERROR_NOT_PARTY = 0;

/*���ɵȼ�����*/
const int CAMP_ERROR_RANK_LEVEL = 1;

/*���ڰ�̯*/
const int CAMP_ERROR_IN_SELL_STATION = 2;

/*Ѻ��*/
const int CAMP_ERROR_IN_YA_BIAO_STATION = 3;


/*̽Ӫʱ�仹û�е�*/
const int CAMP_ERROR_TIME_NOT_OPEN = 4;

class Map_Src;

using namespace std;
class PartyBaseCampLimit
{
	bool isOpen;     //ͨ��ʱ����ƿ���
	int num;         //��Ҫ������
	int partyRank;   //��Ҫ����ɵȼ�
	int room;        //������
	char campMapId[SHOR_MID_VALUE_LENGTH + 1];     //��������
	char campLimitId[SHOR_MID_VALUE_LENGTH +1];  //����id
	vector<Map_Src*> initCampRom; //��������
	list<int> asistList;     //�����������Թ���������
	map<int,string>roomNumToPartyId;    
	map<string,int>partyIdToRoomNum;
	
public:
	/*���ɷ��乹�캯��*/
	PartyBaseCampLimit(char *_campLimitId,char *_campMapId,int _num,int _partyRank,int _room);
	
	/*�������ɷ���*/
	~PartyBaseCampLimit(void);
	
	/*��ʼ�����ɷ���*/
	void initCampMap(void);
	
	/*���ð���ÿ������İ���ʵ��ָ��*/
	void setMapCampRoom(void);
	
	/*���˽����ɰ�����*/
	bool qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason,\
	bool _enterFlg = false);
	
	/*�����ɰ��ắ��*/
	bool entCampRoom(vector<string> &heroId,int _roomNum);
	
	/*�˳����ɰ���*/
	void exitCampRoomAsist(vector<string> &heroId);
	
	/*������ɰ��᷿��*/
	void assignRom(vector<string> &heroId,char *partyId);
	
	/*���հ��ɰ���*/
	void recoverCampRom(int _room);
	
	/*���ÿ������ֵ*/
	void setOpenFlg(bool _openFlg);
	
	/*��ÿ������ֵ*/
	bool getOpenFlg(void);
	
};
#endif
