/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�user_role_manage_growup.h
		�ļ����ã��ɳ�ϵͳ����
		  ʵ���ߣ�Evan
		���ʱ�䣺2012.6.13
*/
#ifndef USER_ROLE_MANAGE_GROWUP
#define USER_ROLE_MANAGE_GROWUP
#include"hero.h"
void herogrowup(Hero *hero);
int ratio(int mon);
int exp(int mon);
//��־�����㺯��������r:���������mon:���ﵱǰ�ȼ���role:����ȼ�
int gExp(int r,int mon,int role);
#endif