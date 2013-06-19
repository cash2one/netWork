/***********************************************
*	��Ǯ��:Money
*	����:jolly
*	����:2012.7.10
*	����:�ṩ���ӽ�Ǯ��ʹ�ý�Ǯ�ķ����Ľӿ�
***********************************************/
#ifndef MONEY_H
#define MONEY_H
#include <iostream>
#include <string>
#include "data_structure_struct.h"
#include "hero.h"
#include "command_return_define_data.h"
using namespace std;

class Hero;
class Money
{
private:	

	moneyData money_data;	
	
public:
	
	Money(void);
	Money(moneyData _moneydata);
	void load(moneyData _moneydata);
	void money_increaseBoundGold(long _boundGold);	//���Ӱ�Ԫ��	
	long money_getBoundGold(void);		//���������ϰ�Ԫ������	
	void money_setBoundGold(long _boundGold);	//����������ϰ�Ԫ������
	void money_useBoundGold(long _boundGold);	//ʹ�ð�Ԫ������
	
	void money_increaseGold(long _gold);	//����Ԫ��	
	long money_getGold(void);		//����������Ԫ������	
	void money_setGold(long _gold);	//�����������Ԫ������
	void money_useGold(long _gold);	//ʹ��Ԫ������
	
	void money_increaseBoundGameMoney(long _boundGameMoney);	//���Ӱ���Ϸ��	
	long money_getBoundGameMoney(void);		//���������ϰ���Ϸ������	
	void money_setBoundGameMoney(long _boundGameMoney);	//����������ϰ���Ϸ������
	void money_useBoundGameMoney(long _boundGameMoney);	//ʹ�ð���Ϸ������
	
	void money_increaseGameMoney(long _gameMoney);	//������Ϸ��
	long money_getGameMoney(void);		//������������Ϸ������	
	void money_setGameMoney(long _gameMoney);	//�������������Ϸ������
	void money_useGameMoney(long _gameMoney);	//ʹ����Ϸ������
	
	
	bool beforeUse(long _gameMoney); 
	
	bool getMoneyFlag(void);					//ȡ��־
	void setMoneyFlag(char *msg,int _flag);			//���ñ�־
	
	bool getGoldFlag(void);					//ȡ��־
	void setGoldFlag(char *msg,int _flag);			//���ñ�־
	
	void saveInStruct();					//����ṹ��
	
	void send_msg_money(char *msg,int len);
	
	void increase(int _flag,long _money);	
	
	int showMoneyData(moneyData *obj, char *outfile);
	
	moneyData getMemStruct(void);
	
	void setAccMoney(long _accMoney);
	void increaseAccMoney(long _accMoney);
	long getAccMoney(void);
	
	void money_inform(char *msg,int len);
};
#endif