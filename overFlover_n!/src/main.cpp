/************************************************************
	�ļ�����main.cpp
	�ļ����ã���NumStr������Ժͷ���������
	���ߣ�chenzhen
	�������ڣ�2013.04.01
************************************************************/
#include"numStr.h"
using namespace std;
	
int main(void)
{
	string data1("1000"),data2("1000");
	NumStr numStr1(data1),numStr2(data1);
	--numStr1;
	numStr1.printData();
	
	NumStr result (numStr1 + numStr2);
	result.printData();
	return 1;
}
	
	
	
