/************************************************************
	�ļ�����attackBottle.h
	�ļ����ã�����Ź��������ܺ���
	���ߣ�chenzhen
	�������ڣ�2012.12.13
************************************************************/
#ifndef ATTACK_BOTTLE_H
#define ATTACK_BOTTLE_H
#include"bottle.h"
class Hero;

/*����ƿ�޵�ͨ�ź���*/
void attactBottleCom(char *buffer);

/*����ƿ�޺���*/
void attackBottle(Hero *attHero,char* skillId,Bottle *bottInst);

/*���﹥��ƿ�޺���*/
void petAttackBottle(char *ownerId,char *identity,Point piexPt,char *skillId,Bottle *bottInst);

#endif