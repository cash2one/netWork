#ifndef REWARD_RECHARGE_CONFIG
#define REWARD_RECHARGE_CONFIG

#include<iostream>
#include<string>

using namespace std;
class Reward_recharge_config
{
private:
	int type;							//�ۼƳ�ֵ����
	int flag;							//�������
	int money;							//������Ǯ����
	int repeat;							//�����͵���Ʒռ�õĸ�������
	int num;							//goodsid����Ŀ
	char goodsid[1024];					//����goodsid�����͵�����

public:
	Reward_recharge_config(int _type,int _flag,int _money,int _repeat,int _num,char* _goodsid);
	int getType(void);
	int getFlag(void);
	int getMoney(void);
	int getRepeat(void);
	int getNum(void);
	char* getGoodsid(void);
};

#endif