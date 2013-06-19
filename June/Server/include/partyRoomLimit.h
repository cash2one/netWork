/************************************************************
	�ļ�����partyRoomLimit.h
	�ļ����ã�����PartyRoomLimit�����Ժͺ���
	���ߣ�chenzhen
	�������ڣ�2012.12.14
************************************************************/

#ifndef PARTY_ROOM_LIMIT_H
#define PARTY_ROOM_LIMIT_H
#include "instancing_manage.h"
#include"wholeDefine.h"
#include<vector>
#include<string>
#include<list>

/*û�м����κΰ���*/
const int PARMAP_ERROR_NOT_PARTY = 0;

/*���ɵȼ�����*/
const int PARMAP_ERROR_RANK_LEVEL = 1;

/*��̯״̬*/
const int PARMAP_ERROR_IN_SELL_STATION = 2;

/*Ѻ��״̬*/
const int PARMAP_ERROR_IN_YA_BIAO_STATION = 3;

class Map_Src;

using namespace std;
class PartyRoomLimit
{	
	int num;         //��Ҫ������
	int partyRank;   //��������Ҫ����ɵȼ�
	int room;        //����������
	char partyMapId[SHOR_MID_VALUE_LENGTH + 1];     //vip��������
	char partyLimitId[SHOR_MID_VALUE_LENGTH +1];  //��������id
	vector<Map_Src*> initPartyRom; //��������
	list<int> asistList;     //�����������Թ���������
	map<int,string>roomNumToPartyId;    
	map<string,int>partyIdToRoomNum;
	bool activeFlg;   //�Ƿ�Ϊ�ϵͳ��ˣ�����ǣ���Ϊ��
	bool todayActiveFlg;   //�����Ƿ���ϵͳ��˻����Ϊ��
	
public:
	/*���ɷ��乹�캯��*/
	PartyRoomLimit(char *_partyLimitId,char *_partyMapId,int _num,int _partyRank,int _room);
	
	/*�������ɷ���*/
	~PartyRoomLimit(void);
	
	/*��ʼ�����ɷ���*/
	void initPartyMap(void);
	
	/*���ð���ÿ������İ���ʵ��ָ��*/
	void setMapPartyRoom(void);
	
	/*���˽����ɰ�����*/
	bool qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason);
	
	/*�����ɰ��ắ��*/
	bool entPartyRoom(vector<string> &heroId,int _roomNum);
	
	/*�˳����ɰ���*/
	void exitPartyRoomAsist(vector<string> &heroId);
	
	/*������ɰ��᷿��*/
	void assignRom(vector<string> &heroId,char *partyId);
	
	/*���հ��ɰ���*/
	void recoverPartyRom(int _room);
	
	/*����Ƿ�Ϊϵͳ��˱��ֵ*/
	bool getActiveFlg(void);
	
	/*�����Ƿ�Ϊϵͳ��˱��ֵ*/
	void setActiveFlg(bool _isActiveFlg);
	
	/*ϵͳ���*/
	void systemDish(Map_Src *treatMap,char *myGuildId);
	
	/*����Ƿ����Ϊϵͳ��˱��ֵ*/
	bool getTodayActiveFlg(void);
	
	/*�����Ƿ����Ϊϵͳ��˱��ֵ*/
	void setTodayActiveFlg(bool _todayActiveFlg);
	
	/*����ϵͳ��ϯΪ�ɳ�״̬*/
	void setSystemDishState(int _dishState);
	
	/*����ϵͳ��ϯΪû��ˢ��״̬*/
	void setIsActiveDishBru(void);
	
	/*����ϵͳ��ϯΪ��ˢ��״̬*/
	void setIsActiveDishBruTrue(void);
	
	/*ϵͳ��ϯ,��Щ�Ѿ�*/
	void isTmeToDinner(void);
	
	/*�ر�ϵͳ����*/
	void closeSystemDish(void);
};
#endif
