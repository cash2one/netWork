/***********************************************
*	��Ǯ��ʹ�÷���:Money_operator
*	����:jolly
*	����:2012.12.17
*	����:�ṩ���ӽ�Ǯ��ʹ�ý�Ǯ�ķ���
***********************************************/
#ifndef MONEY_OPERATOR_H
#define MONEY_OPERATOR_H
#include <iostream>
#include <string>
#include "data_structure_struct.h"
#include "hero.h"
#include "money.h"
#include "command_return_define_data.h"
using namespace std;

bool increaseBoundGold(Hero *hero,long _boundGold);	//���Ӱ�Ԫ��	
bool useBoundGold(Hero *hero,long _boundGold);	//ʹ�ð�Ԫ������
bool campareBoundGold(Hero *hero,long _boundGold);		//�жϰ�Ԫ���Ƿ���

bool increaseGold(Hero *hero,long _gold);	//����Ԫ��	
bool useGold(Hero *hero,long _gold);	//ʹ��Ԫ������
bool campareGold(Hero *hero,long _gold);		//�ж�Ԫ���Ƿ���

bool increaseBoundGameMoney(Hero *hero,long _boundGameMoney);	//���Ӱ���Ϸ��	
bool useBoundGameMoney(Hero *hero,long _boundGameMoney);	//ʹ�ð���Ϸ������
bool campareBoundGameMoney(Hero *hero,long _boundGameMoney);		//�жϰ���Ϸ���Ƿ���

bool increaseGameMoney(Hero *hero,long _gameMoney);	//������Ϸ��
bool useGameMoney(Hero *hero,long _gameMoney);	//ʹ����Ϸ������
bool campareGameMoney(Hero *hero,long _gameMoney);		//�ж���Ϸ���Ƿ���

bool increaseAccMoney(Hero *hero,long accMoney);		//��ֵ
#endif