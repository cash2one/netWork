/************************************************************
	�ļ�����map_inform_asist.h
	�ļ����ã���Map_Inform��ĸ����������ݽṹ
	���ߣ�chenzhen
	�������ڣ�2012.08.29
************************************************************/
#ifndef MAP_INFORM_ASIST_H
#define MAP_INFORM_ASIST_H
#include<string>
#include<set>
using namespace std;
/*ˢ�����νṹ��*/
typedef struct BruGro
{
	/*ÿ���Ĺ���id*/
	set<string>monId;
	
	/*���������жϴ������Ƿ�����*/
	int ctn;
	
	BruGro(set<string> _monId)
	{
		monId = _monId;
		ctn = 0;
	}
	
	BruGro(const BruGro &bruGro)
	{
		monId = bruGro.monId;
		ctn = bruGro.ctn;
	}
	
	BruGro& operator= (const BruGro &bruGro)
	{
		monId = bruGro.monId;
		ctn = bruGro.ctn;
		
		return *this;
	}
	
	
	BruGro(void)
	{
		ctn = 0;
	}
	/*�жϴ������Ƿ����꣬��Ϊ����*/
	bool judDieCtn(void)
	{
		return ctn >= monId.size();
	}
	/*����*/
	void monDie(char *_monId)
	{
		set<string>::iterator set_it;
		if(_monId == NULL || strlen(_monId) == 0)
		{
			return;
		}
		set_it = monId.find(_monId);
		if(set_it == monId.end())
		{		
			return;
		}
		ctn++;
			
	}
	/*����*/
	void init(void)
	{
		ctn = 0;
	}
	/*����һ������id*/
	void inPut(string _monId)
	{
		monId.insert(_monId);	
	}
	
	/*����ˢ������*/
	void testPrint(void)
	{
		cout<<"test oneObject groupGruMonId begin:"<<endl;
		set<string>::iterator monId_it;
		cout<<"the num of the monsterId:"<<monId.size()<<endl;
		for(monId_it = monId.begin();monId_it != monId.end();monId_it++)
		{
			cout<<"monsterId:"<<*monId_it<<endl;
		}
		cout<<"test oneObject groupGruMonId end:"<<endl;
	}
}BruGro;


#endif