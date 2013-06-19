/* 
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�npc.h
		�ļ����ã�ʵ����npc�������Լ������Ķ���
		���ʱ�䣺2012.5.10
		  ����ˣ�Evan		
*/

#ifndef TASK_H
#define TASK_H
#include<string>
#include<set>
#include<map>
#include<vector>
#include"data_structure_struct.h"
#include"task_configuration.h"

#define DIALOG_TASK_NEED_TYPE			0			//�Ի�����
#define KILL_TASK_NEED_TYPE				1			//ɱ������
#define PICKUP_TASK_NEED_TYPE			2			//�ɼ�����
#define COLLECT_TASK_NEED_TYPE			3			//�ռ�����
#define	WAGON_TASK_NEED_TYPE			4			//��������
#define TOTEM_TASK_NEED_TYPE			5			//ͼ������
#define LOCATION_TASK_NEED_TYPE			6			//λ����֤����
#define USE_TASK_NEED_TYPE				7			//ʹ����Ʒ����
#define JOIN_CAMP_TASK_NEED_TYPE		10			//ѡ����Ӫ����
#define	KILL_LIMIT_TASK_NEED_TYPE		11			//ɱ���Ƶȼ�������
#define EQUIP_CUILI_TASK_NEED_TYPE		12			//װ����������
#define	EQUIP_JINGLIAN_TASK_NEED_TYPE	16			//װ����������		
#define	JOIN_GUILD_TASK_NEED_TYPE		13			//�����������
#define TREASURE_MAP_TASK_NEED_TYPE		14			//�Ҳر�ͼ����
#define CYCLE_TASK_NEED_TYPE			20			//ѭ������������
#define RESCUE_TASK_NEED_TYPE			15			//������Ա����
#define BUY_EQUIP_TASK_NEED_TYPE		17			//��װ��������
#define BUY_DAOJU_TASK_NEED_TYPE		18			//����ߵ�����
#define PK_OTHER_HERO_TASK_NEED_TYPE	19			//PK���������
#define PASS_ECTYPE_TASK_NEED_TYPE		21			//ͨ�ظ�������
#define KILL_NPC_BOSS_TASK_NEED_TYPE	22			//ɱ��NPC���boss����
#define PASS_TOWER_LAYER_TASK_NEED_TYPE	23			//��Ҫͨ������¥������

//task�浽���ݿ��״̬����
typedef struct TaskData_S
{ 
	//bool noTaskFlag;					//�����Ƿ�Ϊ��Ч
	long taskFlag;						//�����־��Ϊ-1����δʹ��
	char taskId[10];					//����ID
	int status[5];						//�����״̬����
	TaskData_S()
	{
		taskFlag = -1;				//Ĭ����Ϊ��Ч����ʾû�д�task����
		memset(taskId, 0, sizeof(taskId));
		status[0] = 0;status[1] = 0;status[2] = 0;status[3] = 0;status[4] = 0;
	}
	void operator =(const TaskData_S &data)
	{
		taskFlag = data.taskFlag;
		strncpy(taskId, data.taskId, sizeof(taskId));
		memcpy(status, data.status, sizeof(status));
	}
}TaskData_T;

typedef struct CyCleTaskSet_S
{
	
} CyCleTaskSet_T;

extern map<int, vector<string> > levelCycleTaskSet;

extern map<int, vector<double> > cycleTaskRewardFactor;

class Task
{
private:
	int	   taskType;			//��������
	char taskId[51];			//����ID
	char taskName[51];  	 	//��������
	char recNpcId[51];      	//������NPC id
	char finNpcId[51];      	//������NPC id
	//modified by bison
	list<taskStatus_T*> taskStatus;		//����״̬
	set<give_t*> taskReward;			//������,�������ۣ������Ժ�ֻ��������Ʒʱʹ�ã���Ǯ�;�����ó��������
	set<recv_t*> taskRecv;				//�������ʱ��������
	unsigned inFors;					//����
	unsigned prestige;					//����
	unsigned taskGold;					//��������Ǯ
	unsigned taskExp;					//����������
	int giveType;						//������ɺ���Ʒ������ʽ��0��ϵͳĬ�ϣ�1�����ѡ��
	int chapt;							//���������½�
	int subType;						//����������
	int frequency;						//����һ��֮�ڿɽӴ���
	bool isLastOfThisChapt;				//�Ƿ��Ǳ��½ڵ����һ������
public:
	Task(int _taskType, int freq, char* _taskId, char* _taskName, char* _RecNpcId, char* _FinNpcId,
		int _chapt, unsigned _inFors, unsigned _prestige, unsigned _gold,unsigned _exp, int _giveType, list<taskStatus_T*> _taskStatus,
		set<give_t*> _taskReward, set<recv_t*> _taskRecv, int subType, bool _isLastOfThisChapt);
	
	//���������ʼ��taskʵ��
	Task(Task_Configuration *task_configuration);
	//��memcache��������״̬���ݹ���taskʵ��
	Task(TaskData_T taskData);
	~Task(void);
	//ͨ��������״̬����ж������Ƿ����
	bool isTaskFinish(void);
	//��������״̬����
	int taskUpdate(char* _needId, int _value);
	//��齱��������Ӧ�õĽ����Ƿ�ƥ��
	int taskCheckReward(char* _giveId, int _num);
	
	//������ ���ؽ�����һ����Ϣ������������Ʒid������
	int taskGetReward(char* _giveId, map<string, int> &rewardList);
	
	//�ѿ�ʼ����ʱ��Ҫ����ҵĵ�����ӵ���ұ���
	int getBeginTaskGive(char* beginGive);
	//����������Ҫ����Ʒ
	int recycleTaskNeedGoods(map<string, int> &needRecycle);
	//�õ��������ID
	char* getTaskGoods(void);
	//�õ������ĳ�������״̬����ֵ
	int getTaskStatusValue(char* _needId);
	//void setTask_Monster_Accout(int _task_monster_accout);
	//int  getTask_Monster_Accout(void);
	
	//��ȡ����һ���ڿɽӵĴ���
	int getFreq(void);
	//��ȡ��������
	int getTaskType(void);
	int getNeedType(char* needId);
	int getTaskChapt(void);
	unsigned getInFors();
	unsigned getPrestige();
	unsigned getTaskGold(void);
	unsigned getTaskExp(void);
	int getGiveType(void);
	int getSubType(void);
	bool getIsLastOfThisChapt();
	list<taskStatus_T*> getTaskStatus(void);
	set<give_t*> getTaskReward(void);
	set<recv_t*> getTaskRecv(void);
	char* getTaskId(void);
	char* getTaskName(void);
	//string getTask_Type(void);
	char* getRecNpcId(void);
	char* getFinNpcId(void);
	//��ʼ��������
	TaskData_T initTaskData(void);
	
	//�Ƿ���Ҫ�����ռ�ĳ�ֵ���
	bool needMoreCollection(char* collectionId);
	//�������needType�������needId, ֻ���ͬһ��������ͬһ��needType������ֶ�ε����
	int getSpecialNeedId(int needType, char* needId);		//�ϣ�������ֺ��������༶����ķ���ʱ������Ҫ��
	//string getTask_Monster_Id(void);
	//int    getTask_Monster_Num(void);
	//set<string> getTask_Goods_Id(void);
	//int    getTask_Gold_Num(void);
	//int    getTask_Exp(void);
};
#endif