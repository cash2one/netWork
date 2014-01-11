#ifndef TASK_CONFIGURATION_H
#define TASK_CONFIGURATION_H
#include<iostream>
#include<string>
#include<list>
#include<set>
using namespace std;

#include"data_structure_struct.h"

typedef struct TaskChaptReward_S
{
	char rewardId[51];
	int rewardNum;
	TaskChaptReward_S()
	{
		memset(rewardId, 0, sizeof rewardId);
		rewardNum = 0;
	}
} TaskChaptReward_T;

extern map<int, TaskChaptReward_T> chapt_2_taskReward;

class Task_Configuration
{
private:  
	char taskId[51];			//npcid
	char taskName[51];   	//��������
	char recNpcId[51];      //������NPC id
	char finNpcId[51];      //������NPC id
	
	int frequency;			//������һ���ڿɽӴ���
	int taskType;			//�������ͣ�1�������������񣻡���
	int taskChapt;			//�����½ڣ�1��0-10�����񣻡���
	unsigned taskLevel;     //����ȼ�
	unsigned inFors;		//����
	unsigned prestige;		//����
	unsigned taskGold;		//��������Ǯ��
	unsigned taskExp;		//��������
	int giveType;			//��������Ʒ��ʽ��0��ϵͳĬ�Ͻ�����1�����ѡ����
	int subType;			//����������
	bool isLastOfThisChapt;	//�Ƿ��Ǳ������һ������
	
	
	/* ����������� --��������������� */
	list<need_t*> taskNeed;
	/* ����������Ǯ��װ��������� */
	set<give_t*> taskGive;
	/* ����Ĵ����������� */
	set<touch_t*> taskTouch;
	/* ������������������ */
	set<recv_t*> taskRecv;
	
public:
	Task_Configuration(char* _id, char* _name, char* _recNpcId, char* _finNpcId, int _frequecy, int _type, unsigned _inFors, unsigned _prestige, unsigned _gold, unsigned _exp, int _giveType, int _chapt, unsigned _level, list<need_t*> _need, set<give_t*> _give, set<touch_t*> _touch, set<recv_t*> _recv, int _subType, bool _isLastOfThisChapt);	
	char* getTaskId(void);
	char* getTaskName(void);
	char* getRecNpcId(void);
	char* getFinNpcId(void);
	
	int getFrequency(void);
	int getTask_type(void);
	int getTask_chapt(void);
	unsigned getTask_level(void);
	unsigned getPrestige();
	unsigned getInFors();
	unsigned getTask_gold();
	unsigned getTask_exp();
	int getTask_giveType();
	int getSubType();
	bool getIsLastOfThisChapt();
	/* get�������Ҫ���Ժ���ɽ��� */
	list<need_t*> getTask_need(void);
	set<give_t*> getTask_give(void);
	set<touch_t*> getTask_touch(void);
	set<recv_t*> getTask_recv(void);
/*	set<string> getTask_Goods_Id(void);
	int    getTask_Gold_Num(void);
	int    getTask_Exp(void);
*/	
};
#endif