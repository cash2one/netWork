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
	string data1("2"),data2("1");
	NumStr numStr1(data1),numStr2(data2),result;
//	--numStr1;
//	numStr1.printData();
	
//	numStr1 += numStr2;
//	numStr1.printData();
	
//	result = numStr1 * numStr2;
//	result.printData();

	result = loop(numStr1);
	result.printData();
	
	return 1;
}
	
	
	
