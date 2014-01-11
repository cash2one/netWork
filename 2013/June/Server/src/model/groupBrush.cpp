/************************************************************
	�ļ�����groupBrush.cpp
	�ļ����ã�ʵ��GroupBrush�����Ժͺ���
	���ߣ�chenzhen
	�������ڣ�2012.07.06
************************************************************/

#include"groupBrush.h"
#include<math.h>
GroupBrush::GroupBrush(char *_groupId,double _generRatio,\
					  double _eliteRatio,bool _randFlg,int _bossNum,\
					  double _activeRatio,double _passRatio,double _patRatio)
{
	groupId = _groupId;
	generRatio = _generRatio;
	eliteRatio = _eliteRatio;
	randFlg = _randFlg;
	bossNum = _bossNum;
	activeRatio = _activeRatio;
	passRatio = _passRatio;
	patRatio = _patRatio;
}

/*�������id*/
char* GroupBrush::getGroupId(void)
{
	return const_cast<char *>(groupId.c_str());
}

/*�����ͨ�ֱ���*/
double GroupBrush::getGenerRatio(void)
{
	return generRatio;
}

/*��þ�Ӣ�ֱ���*/
double GroupBrush::getEliteRatio(void)
{
	return eliteRatio;
}

/*��������ֱ���*/
double GroupBrush::getActiveRatio(void)
{
	return activeRatio;
}

/*��ñ����ֱ���*/
double GroupBrush::getPassRatio(void)
{
	return passRatio;
}

/*���Ѳ�߹ֱ���*/
double GroupBrush::getPatRatio(void)
{
	return patRatio;
}

/*���boss�Ƿ�����̳�*/
bool GroupBrush::getRandFlg(void)
{
	return randFlg;
}

/*���boss�������*/
int GroupBrush::getBossNum(void)
{
	return bossNum;
}

/*�����ͨ������*/
int GroupBrush::getGenerNum(int _sum)
{
	return ceil(_sum * generRatio);
}
	
/*��þ�Ӣ������*/
int GroupBrush::getEliteNum(int _sum)
{
	return ceil(_sum * eliteRatio);
}
	
/*�������������*/
int GroupBrush::getActiveNum(int _sum)
{
	return ceil(_sum * activeRatio);
}
	
/*��ñ���������*/
int GroupBrush::getPassNum(int _sum)
{
	return ceil(_sum * passRatio);
}
	
/*���Ѳ�߹�����*/
int GroupBrush::getPatNum(int _sum)
{
	return ceil(_sum * patRatio);
}
/*������ι����������*/
MonGroNum GroupBrush::getMonGroNum(int _sum)
{
	int sum;              //��������
	int generNum;        //��ͨ������
	int eliteNum;        //��Ӣ������
	int activeNum;       //����������
	int passNum;         //����������
	int patNum;          //Ѳ�߹�����
	int bossNum;         //BOSS����
	sum = _sum;
	generNum = getGenerNum(_sum);
	eliteNum = getEliteNum(_sum);
	activeNum = getActiveNum(_sum);
	passNum = getPassNum(_sum);
	patNum = getPatNum(_sum);
	bossNum = getBossNum();
	MonGroNum result(sum,generNum,eliteNum,bossNum,activeNum,passNum,patNum);
	return result;
}

/*���ƺ���*/
GroupBrush* GroupBrush::CopyGroBru(void)
{
	GroupBrush* newGroBru;
	newGroBru = NULL;
	
	newGroBru = new GroupBrush(const_cast<char *>(groupId.c_str()),generRatio,\
							   eliteRatio,randFlg,bossNum,activeRatio,passRatio,patRatio);		
	return newGroBru;	
}

/*��������*/
GroupBrush::~GroupBrush(void)
{
	
}


	