#ifndef REWARD_LEVEL_CONFIG
#define REWARD_LEVEL_CONFIG

#include<iostream>
#include<string>

using namespace std;
class Reward_level_config
{
private:
	int type;							//�ȼ�Ҫ��
	int flag;							//��ұ�־
	int money;							//�������
	int repeat;							//�����͵���Ʒ��ռ�õĸ�����
	int num;							//goodsid����Ŀ
	char goodsid[1024];						//����goodsid�����͵�����
public:
	Reward_level_config(int _type,int _flag,int _money,int _repeat,int _num,char* _goodsid);
	int getType(void);
	int getFlag(void);
	int getMoney(void);
	int getRepeat(void);
	int getNum(void);
	char* getGoodsid(void);
};

#endif