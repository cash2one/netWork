#ifndef _MY_TIME_H_
#define _MY_TIME_H_

#include<sys/time.h>
#include"libev.h"
#include"time.h"

extern ev_timer *myTimer;
extern struct timeval myTime;
extern struct ev_loop *loops;
extern int mySecond;				//��
extern int myMin;					//��
extern int myHour;					//ʱ			
extern int myWeekDay;				//�ܼ�

#define MY_WEEK_DAY	myWeekDay
#define MY_HOUR		myHour
#define MY_MIN		myMin
#define MY_TIME		myTime
#define MY_TV_SEC	myTime.tv_sec
#define MY_TV_USEC	myTime.tv_usec

void initMyTimer(void);
void initMyTime(void);
timeval getMyTime(void);
int getMySecond(void);
bool isSameDayWithNow(int second);
bool isNextDayWithNow(int second);

//��ȡ����ʣ��ʱ��
unsigned getHappyRemain();
extern bool isInHappyTime;							//�Ƿ�������ʱ��
extern bool isInFirstRoomHappyTime;					//�Ƿ������µ�һ¥������ʱ��
extern bool isInSecondRoomHappyTime;				//�Ƿ��������˼������ʱ��
#endif
