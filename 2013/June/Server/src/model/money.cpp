#include "money.h"
extern int sock_fd;
extern char g_out_buf[20480];
Money::Money(void)
{
	money_data.boundGold=0;
	
	money_data.gold=0;

	money_data.boundGameMoney=0;

	money_data.gameMoney=0;
	
	money_data.accGold=0;
	
	money_data.moneyFlag=true;
	
	money_data.goldFlag=true;
}

Money::Money(moneyData _moneydata)
{
	money_data=_moneydata;
}

void Money::load(moneyData _moneydata)
{
	money_data=_moneydata;
}

void Money::money_increaseBoundGold(long _boundGold)		//���Ӱ�Ԫ��
{
	money_data.boundGold+=_boundGold;		
}	
long Money::money_getBoundGold(void)		//���������ϰ�Ԫ������
{
	return money_data.boundGold;
}
void Money::money_setBoundGold(long _boundGold)			//����������ϰ�Ԫ������
{
	money_data.boundGold=_boundGold;
}
void Money::money_useBoundGold(long _boundGold)	//ʹ�ð�Ԫ������
{
	money_data.boundGold-=_boundGold;
}

void Money::money_increaseGold(long _gold)	//����Ԫ��
{
	money_data.gold+=_gold;
}
long Money::money_getGold(void)		//����������Ԫ������
{
	return money_data.gold;
}
void Money::money_setGold(long _gold)		//�����������Ԫ������
{
	money_data.gold=_gold;
}
void Money::money_useGold(long _gold)		//ʹ��Ԫ������
{
	money_data.gold-=_gold;
}

void Money::money_increaseBoundGameMoney(long _boundGameMoney)	//���Ӱ���Ϸ��
{
	money_data.boundGameMoney+=_boundGameMoney;
}

long Money::money_getBoundGameMoney(void)		//���������ϰ���Ϸ������
{	
	return money_data.boundGameMoney;
}
void Money::money_setBoundGameMoney(long _boundGameMoney)		//����������ϰ���Ϸ������
{
	money_data.boundGameMoney=_boundGameMoney;
}
void Money::money_useBoundGameMoney(long _boundGameMoney)		//ʹ�ð���Ϸ������
{
	money_data.boundGameMoney-=_boundGameMoney;
}

void Money::money_increaseGameMoney(long _gameMoney)		//������Ϸ��
{
	money_data.gameMoney+=_gameMoney;
}

long Money::money_getGameMoney(void)		//������������Ϸ������
{
	return money_data.gameMoney;
}
void Money::money_setGameMoney(long _gameMoney)	//�������������Ϸ������
{
	money_data.gameMoney=_gameMoney;
}
void Money::money_useGameMoney(long _gameMoney)	//ʹ����Ϸ������
{
	money_data.gameMoney-=_gameMoney;
}

bool Money::getMoneyFlag(void)		//ȡ��־
{
	return money_data.moneyFlag;
}
	
void Money::setMoneyFlag(char *msg,int _moneyFlag)			//���ñ�־
{
	if (msg==NULL)
	{
		return;
	}
	if (_moneyFlag==1)
	{
		money_data.moneyFlag=true;
	}
	else
	{
		money_data.moneyFlag=false;
	}
	sprintf(msg,"%d,%d,%d,%d",9,MONEY_FLAG,1,_moneyFlag);
}

bool Money::getGoldFlag(void)					//ȡ��־
{
	return money_data.goldFlag;
}

void Money::setGoldFlag(char *msg,int _goldFlag)			//���ñ�־
{
	if (msg==NULL)
	{
		return;
	}
	if (_goldFlag==1)
	{
		money_data.goldFlag=true;
	}
	else
	{
		money_data.goldFlag=false;
	}
	sprintf(msg,"%d,%d,%d,%d",9,MONEY_FLAG,0,_goldFlag);
}

void Money::send_msg_money(char *msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	if (money_data.boundGold<0)
	{
		money_data.boundGold=0;
	}
	if (money_data.gold<0)
	{
		money_data.gold=0;
	}
	if (money_data.boundGameMoney<0)
	{
		money_data.boundGameMoney=0;
	}
	if (money_data.gameMoney<0)
	{
		money_data.gameMoney=0;
	}
	snprintf(msg,len,"%d,%d,%ld,%ld,%ld,%ld,%d,%d",9,ONLINE_BAG_RETURN,money_data.boundGold,money_data.gold,money_data.boundGameMoney,\
	money_data.gameMoney,money_data.moneyFlag,money_data.goldFlag);
}

void Money::increase(int _flag,long _money)
{
	if (_flag==1)
	{
		money_increaseBoundGold(_money);
	}
	else if (_flag==2)
	{
		money_increaseGold(_money);
	}
	else if (_flag==3)
	{
		money_increaseBoundGameMoney(_money);
	}
	else if (_flag==4)
	{
		money_increaseGameMoney(_money);
	}
	else
	{
		cout<<"money flag is error in money.cpp 266"<<endl;
	}
}

bool Money::beforeUse(long _gameMoney)
{

	if(_gameMoney > money_data.gameMoney)
	{
		cout<<"money is not enough in money.cpp"<<endl;
		return false;
	}
	else
	{
		return true;
	}
}

int Money::showMoneyData(moneyData *obj, char *outfile)
{
	FILE *out;
	if((out = fopen(outfile, "w+")) == NULL){
		fprintf(stderr, "fopen file %s error!\n", outfile);
		return -1;
	//	exit(EXIT_FAILURE);
	}
 	fprintf(out, "test moneyData money_data.boundGold:%ld\n", obj->boundGold);
	fprintf(out, "test moneyData money_data.gold:%ld\n", obj->gold);
	fprintf(out, "test moneyData money_data.boundGameMoney:%ld\n", obj->boundGameMoney);
	fprintf(out, "test moneyData money_data.gameMoney:%ld\n", obj->gameMoney);
	fprintf(out, "test moneyData money_data.gameMoney:%ld\n", obj->accGold);
	fprintf(out, "test moneyData money_data.moneyFlag:%d\n", obj->moneyFlag);
	fprintf(out, "test moneyData money_data.goldFlag:%d\n", obj->goldFlag);

	if(fclose(out) != 0){
		fprintf(stderr, "fclose file error!\n");
		return -1;	
	//	exit(EXIT_FAILURE);
	} 	
	
	return 0;
}

moneyData Money::getMemStruct(void)
{
	return money_data;
}

void Money::setAccMoney(long _accMoney)
{
	money_data.accGold=_accMoney;
}
	 
void Money::increaseAccMoney(long _accMoney)
{
	if (_accMoney<0)
	{
		return;
	}
	money_data.accGold+=_accMoney;
}

long Money::getAccMoney(void)
{
	return money_data.accGold;
}

void Money::money_inform(char *msg,int len)
{
	snprintf(msg,len,"%d,%d,%ld,%ld,%ld,%ld",9,MONEY,money_data.boundGold,money_data.gold,money_data.boundGameMoney,money_data.gameMoney);
}