/************************************************************
	�ļ�����main.cpp
	�ļ����ã������ļ�
	���ߣ�chenzhen
	�������ڣ�2013.04.01
************************************************************/

#include<iostream>
#include"allocate.h"
#include"iterator.h"
using namespace std;

int main(void)
{
	Allocate<int> allocate;
	int *p = allocate.allocate();
	
	*p = 4;
	
	cout<<"p:"<<*p<<endl;
	
	return 1;
}

