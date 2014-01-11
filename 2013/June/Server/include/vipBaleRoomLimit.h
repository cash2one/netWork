/************************************************************
	�ļ�����vipBaleRoomLimit.h
	�ļ����ã�����VipBaleRoomLimit�����Ժͺ���
	���ߣ�chenzhen
	�������ڣ�2012.12.14
************************************************************/

#ifndef VIP_BALE_ROOM_LIMIT_H
#define VIP_BALE_ROOM_LIMIT_H
#include "instancing_manage.h"
#include"wholeDefine.h"
#include<vector>
#include<string>
#include<list>

/*vip�ȼ�����*/
const int ERROR_VIP_LEVEL = 0;

/*�������ֵ�ͼ����*/
const int ERROR_IN_HAPPY_CITY = 1;

/*��̯״̬*/
const int ERROR_IN_SELL_STATION = 2;

/*����״̬*/
const int ERROR_IN_YA_BIAO_STATION = 3;

/*����ͬһ�ŵ�ͼ����*/
const int ERROR_IN_ERROR_ERROR_YA_BIAO_STATION = 4;

class Map_Src;

using namespace std;
class VipBaleRoomLimit
{	
	int num;         //��������Ҫ������
	int vipRank;        //��������Ҫ��vip�ȼ�
	int room;         //����������
	char vipMapId[SHOR_MID_VALUE_LENGTH + 1];     //vip��������
	char vipLimitId[SHOR_MID_VALUE_LENGTH +1];  //��������id
	vector<Map_Src*> initVipRom; //��������
	list<int> asistList;     //�����������Թ���������	
	
public:
	/*vip���ṹ�캯��*/
	VipBaleRoomLimit(char *_vipLimitId,char *_vipMapId,int _num,int _vipRank,int _room);
	
	/*��ʼ��vip����*/
	void initVipMap(void);
	
	/*����vip����*/
	~VipBaleRoomLimit(void);
	
	/*����vip����*/
	void recoverVipRom(int _room);
	
	/*���˽�vip������*/
	bool qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason);
	
	/*����vip���᷿��*/
	void assignRom(vector<string> &heroId);
	
	/*��vip���ắ��*/
	bool  entVipRoom(vector<string> &heroId,int _roomNum);  
	
	/*�˳�vip����*/
	void exitVipRoomAsist(vector<string> &heroId);
	
	/*���ð���ÿ������İ���ʵ��ָ��*/
	void setMapVipRoom(void);
	
};
#endif
