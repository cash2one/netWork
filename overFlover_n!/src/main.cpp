/************************************************************
	�ļ�����main.cpp
	�ļ����ã���NumStr������Ժͷ���������
	���ߣ�chenzhen
	�������ڣ�2013.04.01
************************************************************/
#include"numStr.h"
#include"asistFun.h"
using namespace std;

FUN NumStr::dealErrorFun = &errorDealFun;

int main(void)
{	
	string data1("5"),data2("1");
	NumStr numStr1(data1),numStr2(data2),result;
	loopFor(numStr1);
	
	return 1;
}
	
	
	
