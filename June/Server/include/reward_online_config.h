#ifndef REWARD_ONLINE_CONFIG
#define REWARD_ONLINE_CONFIG

#include<iostream>
#include<string>
#include<vector>

using namespace std;
class Reward_online_config
{
private:
	char stage[20];							//�׶�
	int time;							//ʱ��
	vector<int> moneyPercent;			//�漴��Ϸ�Ҹ���
	vector<int> moneyNum;				//�漴��Ϸ������

	vector<int> goldPercent;			//�漴Ԫ������
	vector<int> goldNum;				//�漴Ԫ������
	
	vector<int> goodsPercent;			//�漴��Ʒ����
	vector<string> goodsid;				//�漴��Ʒid

public:
	Reward_online_config(char *_stage,int _time,vector<int> _moneyPercent,vector<int> _moneyNum,vector<int> _goldPercent,\
	vector<int> _goldNum,vector<int> _goodsPercent,vector<string> _goodsid);
	
	char* getStage(void);

	int getTime(void);

	vector<int> getMoneyPercent(void);

	vector<int> getMoneyNum(void);

	vector<int> getGoldPercent(void);

	vector<int> getGoldNum(void);

	vector<int> getGoodsPercent(void);
	
	vector<string> getGoodsid(void);
};

#endif