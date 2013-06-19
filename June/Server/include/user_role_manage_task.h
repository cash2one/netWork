/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�user_role_manage_task.h
		�ļ����ã������ͻ��˷��͸���������ҿɽ������б���Ϣ����
		  ʵ���ߣ�Evan
		���ʱ�䣺2012.5.17
*/
#ifndef USER_ROLE_MANAGE_TASK
#define USER_ROLE_MANAGE_TASK

#include"command_return_define_data.h"
#include"hero.h"
#include"task.h"
#include<iostream>
#include <arpa/inet.h>
#include <stdlib.h>
using namespace std;

//�����Ƿ�ɽ��ж�
void taskAction(char *buffer);
//�������������Ϣ
void taskInfoComm(char *buffer);
//��������
void taskAband(char *buffer);
//����������
void dealAbandTask(Hero *hero, char *taskId, bool offlineFlag = false, int flag = 0);
//����ɽ���֤�ͷ��Ϳɽ���Ϣ
void checkAcceptAndSendMsg(Hero *hero, set<string> taskIdSet, char* canAcc, int flag = 0);
//�������������Ϣ
void sendHeroTaskInfo(Hero *myHero, int flag);
//�����ճ�����
void resetDailyTask(Hero *myHero);

void getTaskChaptRewardComm(char* buffer);

void freshHeroCycleTask(Hero* hero);

void viewHeroCycleTaskInfo(char* buffer);
#endif
