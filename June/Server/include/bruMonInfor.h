/************************************************************
	�ļ�����bruMonInfor.h
	�ļ����ã���BruMonInfor������Ժͷ���
	���ߣ�chenzhen
	�������ڣ�2012.03.11
************************************************************/
#ifndef BRUSHMONSTERINFORM_H
#define BRUSHMONSTERINFORM_H
#include<iostream>
#include<vector>
#include<string>
#include<set>
using namespace std;
class BruMonInfor
{
private:
	string typeId;                 //��������id
	int brushed_count;             //���̳���������
	int sum;                       //����
	int alive_count;               //�ִ���������
	set<string>liveMonId;         //�������Ѿ�ˢ���Ҵ��ĵĹֵ�id
	set<string>bushMonId;         //�����ͻ�û��ˢ���Ĺֵ�id
	set<string>dieMonId;          //�����͵��Ѿ�����id
public:
	BruMonInfor(char *_typeId,int _brushed_count,int _sum,int _alive_count);
	
	/*��ô������ִ��Ĺֵ�id����*/
	set<string>& getLivMonId(void);
	
	/*��ô����ͼ����̳��ֵ�id����*/
	set<string>& getBushMonId(void);
	
	
	set<string>& getDieMonId(void);
	
	/*��ô����͹���id*/
	char* getTyId(void);
	
	/*��ô����͹�����̳���Ŀ*/
	int getBrshCnt(void);
	
	/*��ô����͹�������Ŀ*/
	int getSumCnt(void);
	
	/*�õ����ŵĹֵ���Ŀ*/
	int getLivCnt(void);
	
	/*���ý�Ҫˢ�ֵ���Ŀ*/
	void setBrshCnt(int _num);
	
	/*�����ֵܹ���Ŀ*/	
	void setSumCnt(int _num);
	
	/*���û��ŵĹֵ���Ŀ*/
	void setLivCnt(int _num);
	
	/*�������Ĺֵ�id��������������(�ڹ�����������������ã�*/
	void InputDieId(char *monId);
	
	/*�ѻ��ŵĹֵ�id������������*/
	void InputLiveId(char *monLivId);
	
	/*��Ҫ����������id����ˢ��������*/
	void exchage(void);
	
	/*��Ҫ����Ҫˢ�Ĺֵ�id�������vector��*/
	void outBruMonId(vector<string> &bruId,int _num = 0);
	
	/*�Ѹ�ˢ�õĵĹֵ�id��������vector�������������У�//����InputLiveId����*/
	void InputLiveId(vector<string> &bruId);   
	
	~BruMonInfor(void);
	
	/*��Ҫˢ�ֵ�id����ˢ��������*/
	void InputBruId(char *monId);
	
	/*��Ҫˢ�ֵ�id����ˢ��������(��Ҫ�ڵ�ͼ�����ļ�������ã�*/
	void inputBruId(char* monBruId);  
	
	/*ȡ�����м����̳��Ĺ���id*/
	void outBruMonIdAll(vector<string>& bruId);          //һ���԰�һ�����͵Ĺ�ȫˢ������
	
	/*���Դ�ӡ������������*/
	void testPrintDie(void);
	
	/*���Դ�ӡ�����������*/
	void testPrintLive(void);
	
	/*���Դ�ӡ��Ҫ�̳���������*/
	void testPrintBush(void);
	
	/*���Դ�����Ž���ˢ������*/
	void exchageLve(void);
	
	/*��ԭbrush*/
	void initBrush(void);
	
	
	/*���ô������*/
	void setLiveMonId(set<string> &_liveMonId);
	
	/*������������*/
	void setDieMonId(set<string> &_dieMonId);
	
	/*����ˢ������*/
	void setBushMonId(set<string> &_bushMonId);
	
	/*����ˢ������*/
	BruMonInfor* copyMonBru(void);
	
	/*��������������*/
	void inputOneLve(char* monLivId);
	
	
};
#endif
	
	

	
