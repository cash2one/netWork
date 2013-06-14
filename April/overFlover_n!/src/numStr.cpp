/************************************************************
	�ļ�����numStr.cpp
	�ļ����ã���NumStr������Ժͷ���������
	���ߣ�chenzhen
	�������ڣ�2013.04.01
************************************************************/
#include"numStr.h"
#include"asistFun.h"

/*--��������*/
void NumStr::reduceOne(void)
{
	if(strData.empty())
	{
		cout<<"NumStr::reduceOne error the strData is empty"<<endl;
		dealErrorFun(ERROR_EMPTY);
	}
		
	if(strData[0] == '0')
	{
		cout<<"NumStr::reduceOne error the strData is zero"<<endl;
		dealErrorFun(ERROR_OTHRE);
	}
	
	int len = strData.size() - 1;
	
	while(len >= 0)
	{
		if(strData[len] > '0')
		{
			strData[len] -= 1;
			break;
		}		
		strData[len] += scale - 1;
		--len;
	}
	
	if(strData[0] == '0')
	{
		strData.erase(strData.begin());
	}
}

/*--���غ���*/
NumStr& NumStr::operator--(void)
{
	reduceOne();
	return *this;
}

/*���Դ�ӡ����*/			
void NumStr::printData(void)
{
	cout<<"the strData:"<<strData<<endl;
}

/*���� += ����*/
NumStr& NumStr::operator+= (const NumStr &numStrF)
{
	string result;
	if(numStrF.empty() || strData.empty())
	{
		cout<<"NumStr::operator+= the argument is error empty:"<<endl;
		dealErrorFun(ERROR_EMPTY);
	}
	
	int lenF,lenS;
	size_t lastNumSum;
	bool isEnterHead = false;
	
	lenF = numStrF.size() - 1;
	lenS = strData.size() - 1;	

	
	for(;lenF >= 0 && lenS >= 0; --lenF,--lenS)
	{
		lastNumSum = numStrF.strData[lenF] - '0' + strData[lenS] - '0';
		
		if(isEnterHead)
		{
			lastNumSum += 1;
			isEnterHead = false;
		}
		
		if(lastNumSum < 10)
		{
			result.insert(result.begin(),'0' + lastNumSum);
		}
		else
		{
			result.insert(result.begin(),'0' + lastNumSum - 10);
			
			isEnterHead = true;
		}
	}
	
	for(;lenF >= 0; --lenF)
	{
		lastNumSum = numStrF.strData[lenF] - '0';
		
		if(isEnterHead)
		{
			lastNumSum += 1;
			isEnterHead = false;
		}
		
		if(lastNumSum < 10)
		{
			result.insert(result.begin(),'0' + lastNumSum);
		}
		else
		{
			result.insert(result.begin(),'0' + lastNumSum - 10);
			
			isEnterHead = true;
		}
	}
	
	for(;lenS >= 0; --lenS)
	{
	
		lastNumSum = strData[lenS] - '0';
		
		if(isEnterHead)
		{
			lastNumSum += 1;
			isEnterHead = false;
		}
		
		if(lastNumSum < 10)
		{
			result.insert(result.begin(),'0' + lastNumSum);
		}
		else
		{
			result.insert(result.begin(),'0' + lastNumSum - 10);
			
			isEnterHead = true;
		}
	}
	
	if(isEnterHead)
	{
		result.insert(result.begin(),'0' + 1);
	}
	
	fillNewData(result);
	
	return *this;
}






	
		
	


