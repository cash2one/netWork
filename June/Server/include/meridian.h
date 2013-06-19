/****************************************************************
 * Filename: meridian.h
 * 
 * Description: ����
 *
 * Original Author : bison, 2012-7-13
 *
 ****************************************************************/

#ifndef _MERIDIAN_H_
#define _MERIDIAN_H_

#include"libev.h"
#define MAX_MERIDIAN_LEVEL		90

typedef enum
{
	RENM,			//����
	DUM,			//����
	CHONGM,			//����
	DAIM,			//����
	YINW,			//��ά
	YANGW,			//��ά
	YINQ,			//����
	YANGQ			//����
}MERID_TYPE_T;

typedef struct MeridItem_S
{
	int needHeroLevel[100];
	int time[100];
	int incType1[100];
	int incVal1[100];
	int incTotalVal1[100];
	int incType2[100];
	int incVal2[100];
	int incTotalVal2[100];
} MeridItem_T;

typedef struct MeridConf_S
{
	int startLevel;					//��ʼ���������ȼ�
	int needBoundGoldPerFiveMin;	//ÿ����5���Ӿ�������ʱ����Ҫ��Ԫ����
	MeridItem_T item[8];
} MeridConf_T;

extern MeridConf_T heroMeridConf;			//���ﾭ������

typedef struct MeridData_S
{
	int now;
	int level;
	bool timerBusy;
	int remainTime;
	MeridData_S()
	{
		now = 7;
		level = 0;
		timerBusy = false;
		remainTime = 0;
	}
	void operator =(const MeridData_S &data)
	{
		//memcpy(acc, data.acc, sizeof(acc));
		//memcpy(fin, data.fin, sizeof(fin));
		now = data.now;
		level = data.level;
		timerBusy = data.timerBusy;
		remainTime = data.remainTime;
	}
}MeridData_T;

class Meridian
{
	private:
		MERID_TYPE_T now;			//��ǰ�Ѿ��ﵽ�ľ�����
		int level;					//�����ȼ����ݲ߻��ķ������԰���ͨ�ȼ���ǿ���ȼ���Ϊһ���������� 
		ev_timer *meridTimer;		//������ʱ��
		bool timerBusy;				//�Ƿ�������
	public:
		Meridian();
		Meridian(MERID_TYPE_T _now, int _level);
		//��memcache�������������ָ�
		Meridian(MeridData_T meridData);
		~Meridian();
		//��������
		bool upgrade();
		//����ǿ��
		bool strengthen();
		MERID_TYPE_T getNow();
		int getLevel();
		ev_timer* getTimer();
		//��ȡ��ʱ���Ƿ�ռ��
		bool getTimerBusy();
		//���ö�ʱ��ռ��
		void setTimerBusy(bool busy);
		//��ȡ��������������ֵ
		int getIncTotalVal(int &val1, int &val2, int now);
};

#endif
