/************************************************************
	�ļ�����main.cpp
	�ļ����ã���NumStr������Ժͷ���������
	���ߣ�flyer
	�������ڣ�2013.04.01
************************************************************/
#include"numStr.h"
#include"asistFun.h"
using namespace std;

FUN NumStr::dealErrorFun = &errorDealFun;

int main(void)
{	
	string data1("5");
	NumStr numStr1(data1);
	if(numStr1.strDataIsRight() && numStr1.scaleIsRight())
	{		
		loopFor(numStr1);
	}
	
	return 1;
}
	
	
	
