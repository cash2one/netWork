/****************************************************************
 * Filename: meridian.cpp
 * 
 * Description: ����ϵͳ
 *
 * Original Author : bison, 2012-7-13
 *
 ****************************************************************/

#include"meridian.h"
#include<map>
using namespace std;

//��������Ĭ�Ϲ���
Meridian::Meridian()
{
	level = 0;
	now = YANGQ;
	meridTimer = new ev_timer;
	timerBusy = false;
}

//������ָ������
Meridian::Meridian(MERID_TYPE_T _now, int _level)
{
	now = _now;
	level = _level;
	meridTimer = new ev_timer;
	timerBusy = false;
}

//ʹ�ô�memcache���������ݶԾ������лָ�
Meridian::Meridian(MeridData_T meridData)
{
	now = (MERID_TYPE_T)meridData.now;
	level = meridData.level;
	meridTimer = new ev_timer;
	timerBusy = meridData.timerBusy;
}

//����������
bool Meridian::upgrade()
{
	//�������������������60��
	if (level >= MAX_MERIDIAN_LEVEL && now == YANGQ)
	{
		return false;
	}
	
	//������һ������
	now = (MERID_TYPE_T)((now + 1) % 8);
	
	//���һ���ֻغ��µȼ���1
	if (now == RENM)
	{
		level++;
	}
	
	return true;
}

//����ǿ��
bool Meridian::strengthen()
{
	//����ǿ�����ǿ��30��
	if (level < MAX_MERIDIAN_LEVEL || level >= MAX_MERIDIAN_LEVEL + 30)
	{
		return false;
	}
	
	if (now == RENM)
	{
		level++;
	}
	
	now = (MERID_TYPE_T)((now + 1) % 8);
	return true;
}

MERID_TYPE_T Meridian::getNow()
{
	return now;
}

//���־����ܵȼ� (now + 1) * level + (7 - now) * (level - 1);
int Meridian::getLevel()
{
	return level;
}

ev_timer* Meridian::getTimer()
{
	return meridTimer;
}

Meridian::~Meridian()
{
	delete meridTimer;
}

bool Meridian::getTimerBusy()
{
	return timerBusy;
}

void Meridian::setTimerBusy(bool busy)
{
	timerBusy = busy;
}


//��ȡ��������������ֵ
int Meridian::getIncTotalVal(int &val1, int &val2, int node)
{
	if (node <= now)
	{
		val1 = heroMeridConf.item[node].incTotalVal1[level];
		val2 = heroMeridConf.item[node].incTotalVal2[level];
	} else {
		val1 = heroMeridConf.item[node].incTotalVal1[level - 1];
		val2 = heroMeridConf.item[node].incTotalVal2[level - 1];
	}
	return 0;
}