/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�hero_grow_up.cpp
		�ļ����ã���ɫ������Ҫ�ľ���ֵ
		  ʵ���ߣ�cookie
		���ʱ�䣺2012.6.14
*/
#include"user_role_manage_growup.h"
#include<iostream>
#include<vector>
#include<set>
#include<map>
using namespace std;
int ratio(int mon)
{
	int r;
	if(0<mon&&mon<11)
	{
		r=100;
		return r;
	}
	if(10<mon&&mon<21)
	{
		r=25;
		return r;
	}
	if(20<mon&&mon<31)
	{
		r=50;
		return r;
	}
	if(30<mon&&mon<41)
	{
		r=40;
		return r;
	}
	if(40<mon&&mon<51)
	{
		r=25;
		return r;
	}
	if(50<mon&&mon<61)
	{
		r=20;
		return r;
	}
	else
	{
		r=15;
		return r;
	}
}
int exp(int mon)
{
	int arg=mon/10;
	int result;
	if(mon%10)
	{
		arg+=1;
	}
	result=arg*arg*mon*100;
	return result;
}

//��־�����㺯��������r:���������mon:���ﵱǰ�ȼ���role:����ȼ�
int gExp(int r,int mon,int role)
{
	int result=(ratio(mon)*exp(mon)*mon)/(role*10);
	// result=result/10;
	switch (r)
	{
		case 1:
			return result/1000;
		case 2:
			return result*11/10000;
		case 3:
			return result*13/10000;
		case 4:
			return result*15/10000;
		default:
			return 0;
	}
}