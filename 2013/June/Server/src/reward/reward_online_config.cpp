#include "reward_online_config.h"
#include <string.h>

Reward_online_config::Reward_online_config(char *_stage,int _time,vector<int> _moneyPercent,vector<int> _moneyNum,\
										vector<int> _goldPercent,vector<int> _goldNum,vector<int> _goodsPercent,vector<string> _goodsid)
{	
	memset(stage,0,sizeof(stage));
	strncpy(stage,_stage,sizeof(stage));
	
	time=_time;							//ʱ��
	
	moneyPercent=_moneyPercent;			//�漴��Ϸ�Ҹ���
	moneyNum=_moneyNum;				//�漴��Ϸ������

	goldPercent=_goldPercent;			//�漴Ԫ������
	goldNum=_goldNum;				//�漴Ԫ������
	
	goodsPercent=_goodsPercent;			//�漴��Ʒ����
	goodsid=_goodsid;				//�漴��Ʒid
	
}

char* Reward_online_config::getStage(void)
{
	return stage;
}

int Reward_online_config::getTime(void)
{
	return time;
}

vector<int> Reward_online_config::getMoneyPercent(void)
{
	return moneyPercent;
}

vector<int> Reward_online_config::getMoneyNum(void)
{
	return moneyNum;
}

vector<int> Reward_online_config::getGoldPercent(void)
{
	return goldPercent;
}

vector<int> Reward_online_config::getGoldNum(void)
{
	return goldNum;
}

vector<int> Reward_online_config::getGoodsPercent(void)
{
	return goodsPercent;
}
vector<string> Reward_online_config::getGoodsid(void)
{
	return goodsid;
}