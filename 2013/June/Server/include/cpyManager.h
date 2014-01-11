/************************************************************
	�ļ�����cpyManage.h
	�ļ����ã���CpyManger<������̬������>�����Ժͷ�����ʵ��
	���ߣ�chenzhen
	�������ڣ�2012.11.29
************************************************************/
#ifndef CPY_MANAGER
#define CPY_MANAGER
#include"cpy.h"
#include<vector>
class CpyManger
{
	vector<Cpy*> cpyVec;
	
	set<int> ctnManager;
	
	/*�ж��Ƿ�Ϊ��*/
	bool judgeEmpty(void);
	
	/*�ж��ѻ���set�����Ƿ���index*/
	bool judRecovered(int index);
	
	public:
	
	/*���캯��*/
	CpyManger(int _num);
	
	/*����һ������ָ��*/
	int offerCpy(Cpy *offer);	
	
	/*���ո���ָ��*/
	bool recover(Cpy* _cpy,int index);
	
	/*����һ������ָ��*/
	Cpy* offerCpy(int &index);
	
	/*���Դ�ӡ*/
	void print(void);

};
#endif

	
	
	