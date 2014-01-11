/************************************************************
	�ļ�����numStr.h
	�ļ����ã���NumStr������Ժͷ���������
	���ߣ�chenzhen
	�������ڣ�2013.04.01
************************************************************/
#ifndef NUMSTR_H
#define NUMSTR_H
#include<iostream>
#include<stdlib.h>

typedef void (*FUN)(int errorType);

using namespace std;

class NumStr
{	
	string strData;
	
	size_t scale;
	
	static FUN dealErrorFun;
	
	/*--��������*/
	void reduceOne(void);
	
	public:
	NumStr(const string &_strData,int _scale = 10):strData(_strData),scale(_scale)
	{
		strData = _strData;
	}
	
	NumStr(const NumStr &_strData):strData(_strData.strData),scale(_strData.scale)
	{
		
	}

	NumStr(void):scale(10)
	{

	}
	
	/*�ж��Ƿ�Ϊ��*/
	inline bool empty(void)
	{
		return strData.empty();
	}
	
	inline bool empty(void) const
	{
		return strData.empty();
	}
	
	/*�󳤶�*/
	inline size_t size(void)
	{
		return strData.size();
	}
	
	inline size_t size(void) const
	{
		return strData.size();
	}
	
	inline void fillNewData(const string& newData)
	{
		strData.clear();
		strData = newData;
	}
	
	
	inline NumStr& operator =(const NumStr &_strData)
	{
		strData = _strData.strData;
		scale = _strData.scale;
	}	
	
	/*--���غ���*/
	NumStr& operator--(void);
	
	/*���� += ����*/
	NumStr& operator+= (const NumStr &numStrF);
	
	/*���Դ�ӡ����*/	
	void printData(void);	
	
	friend const NumStr operator* (const NumStr& numStrF,const NumStr& numStrS);
	
	friend bool operator < (const NumStr &numStrL,const NumStr &numStrR);
	
};

#endif
	
