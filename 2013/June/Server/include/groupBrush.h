/************************************************************
	�ļ�����groupBrush.h
	�ļ����ã�����GroupBrush�����Ժͺ���
	���ߣ�chenzhen
	�������ڣ�2012.07.06
************************************************************/

#ifndef GROUP_BRUSH_H
#define GROUP_BRUSH_H
#include<string>
#include"data_structure_struct.h"
using namespace std;
class GroupBrush
{
	string groupId;           //����id
	double generRatio;        //��ͨ����ռ����
	double eliteRatio;        //��Ӣ����ռ����
	double activeRatio;       //��������ռ����	
	double passRatio;         //��������ռ����
	double patRatio;          //Ѳ�߹���ռ����
	bool randFlg;             //boss���Ƿ�����̳�
	int bossNum;              //BOSS�������̳���������
	public:
	GroupBrush(char *_groupId,double _generRatio,\
			  double _eliteRatio,bool _randFlg,\
			  int _bossNum,double _activeRatio,\
			  double _passRatio,double _patRatio);			 
	
	/*�������id*/
	char* getGroupId(void);
	
	/*�����ͨ�ֱ���*/
	double getGenerRatio(void);
	
	/*��þ�Ӣ�ֱ���*/
	double getEliteRatio(void);
	
	/*��������ֱ���*/
	double getActiveRatio(void);
	
	/*��ñ����ֱ���*/
	double getPassRatio(void);
	
	/*���Ѳ�߹ֱ���*/
	double getPatRatio(void);
	
	/*���boss�Ƿ�����̳�*/
	bool getRandFlg(void);
	
	/*���boss�������*/
	int getBossNum(void);
	
	/*�����ͨ������*/
	int getGenerNum(int _sum);
	
	/*��þ�Ӣ������*/
	int getEliteNum(int _sum);
	
	/*�������������*/
	int getActiveNum(int _sum);
	
	/*��ñ���������*/
	int getPassNum(int _sum);
	
	/*���Ѳ�߹�����*/
	int getPatNum(int _sum);
	
	/*������ι����������*/
	MonGroNum getMonGroNum(int _sum);
	
	/*���ƺ���*/
	GroupBrush* CopyGroBru(void);
	
	/*��������*/
	~GroupBrush(void);
};
#endif
	
	