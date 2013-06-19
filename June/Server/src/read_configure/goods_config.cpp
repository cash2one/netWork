#include"goods_config.h"
#include<string.h>
#include<string>
#include<iostream>
using namespace::std;
Goods_Config::Goods_Config(char* _id,char* _name,char* _effect,int _order,int _repeat,int _type,int _levelLimit,int _gold,int _goldBound,int _money,int _moneyBound,int _price)
{
	int len;
	len = strlen(_id);
	id = new char[len+1];
	strncpy(id,_id,len);
	id[len]='\0';		//��Ʒid

	len = strlen(_name);
	name = new char[len+1];
	strncpy(name,_name,len);
	name[len]='\0';				//��Ʒ����
	
	len = strlen(_effect);
	effect = new char[len+1];
	strncpy(effect,_effect,len);
	effect[len]='\0';			//��ƷЧ��
	
	order=_order;			//�������
	repeat=_repeat;				//�ѵ�����
	type=_type;				//����
	levelLimit=_levelLimit;			//�ȼ�����
	gold=_gold;				//����Ԫ���۸�
	goldBound=_goldBound;
	moneyBound=_moneyBound;//������Ϸ�Ҽ۸�
	money=_money;	
	price=_price;
}

char* Goods_Config::getId(void)           //��Ʒid
{
	return id;
}

char* Goods_Config::getName(void)		 //��Ʒ����
{
	return name;
}

char* Goods_Config::getEffect(void)        //��ƷЧ��
{
	return effect;
}

int Goods_Config::getOrder(void)			//�������
{
	return order;
}

int Goods_Config::getRepeat(void)         //�ѵ�����
{
	return repeat;
}

int	Goods_Config::getType(void)         //����
{
	return type;
}

int Goods_Config::getLevelLimit(void)        //�ȼ�����
{
	return levelLimit;
}

int Goods_Config::getGold(void)    //����Ԫ���۸�
{
	return gold;
}

int Goods_Config::getGoldBound(void)
{
	return goldBound;
}

int Goods_Config::getMoneyBound(void)
{
	return moneyBound;
}

int Goods_Config::getMoney(void)      //������Ϸ�Ҽ۸�
{
	return money;
}

int Goods_Config::getPrice(void)      //������Ϸ�Ҽ۸�
{
	return price;
}