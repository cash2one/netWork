#ifndef VIP_DATA
#define VIP_DATA
#include<iostream>
#include<string.h>
using namespace std;

struct VipDataInitial
{
	char id[13];	//vip id
	int lastTime;	//����ʱ��
	char title[13];	//ͷ��
	int invalid1;	//��������1,
	int invalid2;	//��������2
	int invalid3;	//��������3
	int invalid4;	//��������4
	char giftBagId[13];	//�������id
};

#endif