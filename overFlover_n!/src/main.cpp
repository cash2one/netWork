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
	string data1("5"),data2("12");
	NumStr numStr1(data1),numStr2(data2);
//	--numStr1;
//	numStr1.printData();
	
//	numStr1 += numStr2;
//	numStr1.printData();
	
//	NumStr result = numStr1 * numStr2;
//	result.printData();

	NumStr result = loop(numStr1);
	result.printData();
	
	
	return 1;
}
	
	
	
