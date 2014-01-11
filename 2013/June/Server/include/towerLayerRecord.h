/************************************************************
	�ļ�����towerLayerRecord.h
	�ļ����ã�TowerLayerRecord��ķ��������Ե�����
	���ߣ�chenzhen
	�������ڣ�2012.09.11
************************************************************/
#ifndef TOWER_LAYER_RECORD_H
#define TOWER_LAYER_RECORD_H
#include"other_define_data.h"
#include"wholeDefine.h"
#include<iostream>
#include<string.h>
#include<vector>
#include<string>
#include<list>
#include<map>
#include<set>

class Hero;
using namespace std;

/*��������ݳ�ʼ��ͷ����*/
#define TOWER_F 33
#define TOWER_S 1

/*��������ݳ�ʼ��ͷ����*/
#define LAYER_F 33
#define LAYER_S 2

typedef struct TowerRecordAsist
{
	char Id[LITTLE_MID_VALUE_LENGTH + 1];
	int flg;
	
	TowerRecordAsist(char *_Id = NULL,int _flg = 0)
	{
		memset(Id,'\0',sizeof(Id));
		if(_Id)
		{
			strncpy(Id,_Id,strlen(_Id));
		}
		flg = _flg;
	}
	
	TowerRecordAsist(const TowerRecordAsist &towerAsist)
	{
		memset(Id,'\0',sizeof(Id));
		strncpy(Id,towerAsist.Id,strlen(towerAsist.Id));
		flg = towerAsist.flg;
	}
	
	TowerRecordAsist& operator= (const TowerRecordAsist &towerAsist)
	{
		memset(Id,'\0',sizeof(Id));
		strncpy(Id,towerAsist.Id,strlen(towerAsist.Id));
		flg = towerAsist.flg;
		return *this;
	}
		
}TowerRecordAsist;


class TowerLayerRecord
{
	map<string,TowerRecordAsist> towerMap;             //��״̬����
	
	map<string,TowerRecordAsist> layerMap;         //ÿһ���������ι���
	
	char towerMsg[LONG_MID_VALUE_LENGTH + 1];          //��������Ϣ
	
	char layerMsg[LONG_MID_VALUE_LENGTH + 1];          //�㿪����Ϣ
	
	char nowTowerId[LITTLE_MID_VALUE_LENGTH + 1];      //��ǰ������id
	
	char nowLayerId[LITTLE_MID_VALUE_LENGTH + 1];      //��ǰ������id
	
	Hero* owner;                                       //����
	
	set<string> swapLayerId;                           //ɨ���㼯��
	
	bool isSwap;                                       //û��ɨ������Ϊ�٣�����Ϊ��
	
	public:
	
	/*Ĭ�ϵ�һ�����ĵ�һ�㿪��*/
	TowerLayerRecord(Hero* _owner);
	
	/*�����֮��ͨ��һ�㺯��*/
	void changeLayerId(void);
	
	/*�ж��Ƿ�Ϊ��ǰ��*/
	bool isRightTower(char *towerId);
	
	/*�жϲ��Ƿ���*/
	bool isRightLayer(char *layerId);
	
	/*��������*/
	~TowerLayerRecord(void);
	
	/*������Ŀ�����Ϣ*/
	char* getTowerMsg(void);
	
	/*��ò�Ŀ�����Ϣ*/
	char* getLayerMsg(void);
	
	/*����ɨ���������*/
	void beginSwapOutReward(void);
	
	/*��ȡɨ������*/
	void endSwapOutReward(void);
	
	/*ˢ�²��־������*/
	void brushLayerFlg(void);
	
	/*�ж��Ƿ��б�Ҫˢ�����Ϊ�棬��ʾ����ˢ�£����򣬱�ʾû��Ҫˢ��*/
	bool isShouldBrushLayer(void);

	private:
	
	/*�����������Ϣ*/
	void initTwoerMsg(void);
	
	/*���ɲ������Ϣ*/
	void initLayerMsg(bool _isCanBuy = false);
	
	/*���ĵ�ǰ����id*/
	bool changeTowerId(void);
	
	/*����ʱ��ʼ���������*/
	void initLayerFlg(void);
	
	/*���������Ϣ*/
	void initMsg(void);		
	
	/*��ʼ����ľ����������*/
	void initTwoerMap(void);
	
	/*��ʼ����ľ�²������*/
	void initLayerMap(void);	
	
	/*��memcached�涫��*/
	void storeData(void);
	
	/*���õ�ɨ������*/
	void bornSwapOutRewardSet(void);
	
	/*��ʼ�����Ƿ���Խ���*/
	void initLayerCanFlg(void);
	
	/*����ÿ���־��������*/
	void chgLayerFlg(char *layerId,int flag);
	
	/*����ʱ���Ĳ��־������*/
	void coverChgeLayerFlg(void);
	
	/*�������һ�㣬���һ�����󣬿����Ǹ�ˢ�°�ť*/
	void lastLayer(void);
};

/*���Ժ�ľ�¶�ȡ�����Ƿ���ȷ*/
void testTowerLayerConf(void);

void testTowerLayerConfAsist(map<string,string> &conf);

#endif
	
	