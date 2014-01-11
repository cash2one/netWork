/* 
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�task.cpp
		�ļ����ã�����ʵ����task�������Լ������Ķ���
		���ʱ�䣺2012.5.10
		  ����ˣ�Evan
*/
#include"task.h"
#include"command_other_function_all_over.h"

extern map<string,Task_Configuration*> id_to_task;

Task::Task(int _taskType, int freq, char* _taskId, char* _taskName, char* _recNpcId, char* _finNpcId,
		int _chapt, unsigned _inFors, unsigned _prestige, unsigned _gold, unsigned _exp, int _giveType, list<taskStatus_T*> _taskStatus,
		set<give_t*> _taskReward, set<recv_t*> _taskRecv, int _subType, bool _isLastOfThisChapt)
{
	taskType = _taskType;
	frequency = freq;
	strncpy(taskId, _taskId, sizeof(taskId));
	strncpy(taskName, _taskName, sizeof(taskName));
	strncpy(recNpcId, _recNpcId, sizeof(recNpcId));
	strncpy(finNpcId, _finNpcId, sizeof(finNpcId));
	inFors = _inFors;
	prestige = _prestige;
	taskGold = _gold;
	taskExp = _exp;
	giveType = _giveType;
	taskStatus = _taskStatus;
	taskReward = _taskReward;
	taskRecv = _taskRecv;
	chapt = _chapt;
	subType = _subType;
	isLastOfThisChapt = _isLastOfThisChapt;
}

//����task�������ʼtaskʵ��
Task::Task(Task_Configuration *task_configuration)
{
	/* �����������ж�ȡ�����������ʼ������ʵ�� */
	int	_taskType = task_configuration->getTask_type();				//��������
	int _freq = task_configuration->getFrequency();					//����һ��ɽӴ���
	char* _taskId = task_configuration->getTaskId();		      //����id; �����ʡ�ˣ��Ѿ���startTaskId��
	char* _taskName = task_configuration->getTaskName();        //������
	char* _recNpcId = task_configuration->getRecNpcId();      //������NPC��id
	char* _finNpcId = task_configuration->getFinNpcId();      //������NPC��id
	unsigned _inFors = task_configuration->getInFors();
	unsigned _prestige = task_configuration->getPrestige();
	unsigned _gold = task_configuration->getTask_gold();           //�������Ľ�Ǯ����
	unsigned _exp = task_configuration->getTask_exp();			  //�������ľ��齱��
	int _giveType = task_configuration->getTask_giveType();		  //��������Ʒ�ķ�ʽ
	int _chapt = task_configuration->getTask_chapt();				  //���������½�
	int _subType = task_configuration->getSubType();				//����������
	bool _isLastOfThisChapt = task_configuration->getIsLastOfThisChapt();
	/* task_configuration��need����ת����task��status���� */
	list<need_t*> need = task_configuration->getTask_need();
	list<taskStatus_T*> _taskStatus;                               //��¼����״̬�ĳ�Ա����
	list<need_t*>::iterator iter_need;
	iter_need = need.begin();
	if (iter_need != need.end())
		cout<<"BisonShow "<<(*iter_need)->type<<" "<<(*iter_need)->id<<"  "<<(*iter_need)->num<<endl;
	for (iter_need; iter_need != need.end(); iter_need++)
	{
		//ʹ��need����status,��ʼ״̬������Ϊ0
		taskStatus_T *status = new taskStatus_T((*iter_need), 0);
		_taskStatus.push_back(status);
	}
	
	set<give_t*> give = task_configuration->getTask_give();		  //���give����
	set<recv_t*> recv = task_configuration->getTask_recv();		  //���recv����
	
	//������һ�����캯��
	//this(_taskId, _taskName, _recNpcId, finNpcId, _gold, _exp, _giveType, _taskStatus, give, recv);
	taskType = _taskType;
	frequency = _freq;
	strncpy(taskId, _taskId, sizeof(taskId));
	strncpy(taskName, _taskName, sizeof(taskName));
	strncpy(recNpcId, _recNpcId, sizeof(recNpcId));
	strncpy(finNpcId, _finNpcId, sizeof(finNpcId));
	inFors = _inFors;
	prestige = _prestige;
	taskGold = _gold;
	taskExp = _exp;
	giveType = _giveType;
	taskStatus = _taskStatus;
	taskReward = give;
	taskRecv = recv;
	chapt = _chapt;
	subType = _subType;
	isLastOfThisChapt = _isLastOfThisChapt;
}

//��memcache������task���ݻָ�taskʵ��
Task::Task(TaskData_T taskData)
{
	char* taskIdSrc = taskData.taskId;
	Task_Configuration *task_configuration;
	
	map<string,Task_Configuration*>::iterator iter_conf;
	iter_conf = id_to_task.find(taskIdSrc);
	if(iter_conf == id_to_task.end())
	{
		cout<<"Bison Warning @task.cpp:82."<<endl;
		cout<<"very Bad, there is no the specified task with the id of "<<taskIdSrc<<endl;
		return ;
	}
	
	task_configuration = iter_conf->second;
	
	/* �����������ж�ȡ�����������ʼ������ʵ�� */
	int _taskType = task_configuration->getTask_type();				//��������
	int _freq = task_configuration->getFrequency();					//����һ��ɽӴ���
	char* _taskId = task_configuration->getTaskId();				//����id; �����ʡ�ˣ��Ѿ���startTaskId��
	char* _taskName = task_configuration->getTaskName();			//������
	char* _recNpcId = task_configuration->getRecNpcId();		//������NPC��id
	char* _finNpcId = task_configuration->getFinNpcId();		//������NPC��id
	unsigned _inFors = task_configuration->getInFors();
	unsigned _prestige = task_configuration->getPrestige();
	unsigned _gold = task_configuration->getTask_gold();			//�������Ľ�Ǯ����
	unsigned _exp = task_configuration->getTask_exp();				//�������ľ��齱��
	int _giveType = task_configuration->getTask_giveType();			//��������Ʒ�ķ�ʽ
	int _chapt = task_configuration->getTask_chapt();				//���������½�
	int _subType = task_configuration->getSubType();				//����������
	bool _isLastOfThisChapt = task_configuration->getIsLastOfThisChapt();
	
	/* task_configuration��need����ת����task��status���� */
	list<need_t*> need = task_configuration->getTask_need();
	list<taskStatus_T*> _taskStatus;                               //��¼����״̬�ĳ�Ա����
	list<need_t*>::iterator iter_need;
	iter_need = need.begin();
	if (iter_need != need.end())
		cout<<(*iter_need)->type<<" "<<(*iter_need)->id<<"  "<<(*iter_need)->num<<endl;
	for (iter_need; iter_need != need.end(); iter_need++)
	{
		//ʹ��need����status,��ʼ״̬������Ϊ0
		taskStatus_T *status = new taskStatus_T((*iter_need), 0);
		_taskStatus.push_back(status);
	}
	
	set<give_t*> give = task_configuration->getTask_give();		  //��Ϊgive�ǹ̶��Ĳ���giveʵ����������������giveʹ����ͬ�ڴ�
	set<recv_t*> recv = task_configuration->getTask_recv();		  //recvҲ�̶���������task�б仯
	
	//������һ�����캯��
	//this(_taskId, _taskName, _recNpcId, finNpcId, _gold, _exp, _giveType, _taskStatus, give, recv);
	frequency = _freq;
	taskType = _taskType;
	strncpy(taskId, _taskId, sizeof(taskId));
	strncpy(taskName, _taskName, sizeof(taskName));
	strncpy(recNpcId, _recNpcId, sizeof(recNpcId));
	strncpy(finNpcId, _finNpcId, sizeof(finNpcId));
	inFors = _inFors;
	prestige = _prestige;
	taskGold = _gold;
	taskExp = _exp;
	giveType = _giveType;
	taskStatus = _taskStatus;
	taskReward = give;
	taskRecv = recv;
	chapt = _chapt;
	subType = _subType;
	isLastOfThisChapt = _isLastOfThisChapt;
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	int i = 0;
	for (iter; iter != taskStatus.end(); iter++)
	{	
		(*iter)->value = taskData.status[i];
		i++;
	}
	
}

char* Task::getTaskId(void)
{
	return taskId;
}
char* Task::getTaskName(void)
{
	return taskName;
}
/*string Task::getTask_Type(void)
{
	return task_type;
}
*/
char* Task::getRecNpcId(void)
{
	return recNpcId;
}
char* Task::getFinNpcId(void)
{
	return finNpcId;
}

unsigned Task::getInFors(void)
{
	return inFors;
}

unsigned Task::getPrestige(void)
{
	return prestige;
}

unsigned Task::getTaskGold(void)
{
	return taskGold;
}

unsigned Task::getTaskExp(void)
{
	return taskExp;
}

//����һ������ɽӵĴ���
int Task::getFreq(void)
{
	return frequency;
}

int Task::getGiveType(void)
{
	return giveType;
}

/* ��ȡ�����״̬���� */
list<taskStatus_T*> Task::getTaskStatus(void)
{
	return taskStatus;
}
/* ��ȡ����Ľ������� */
set<give_t*> Task::getTaskReward(void)
{
	return taskReward;
}

/* ��ȡ�������ʱ�������� */
set<recv_t*> Task::getTaskRecv(void)
{
	return taskRecv;
}
/* �ж������Ƿ���ɣ������ɷ���true,���򷵻�false */
bool Task::isTaskFinish(void)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	bool finishFlag = true;
	for (iter; iter != taskStatus.end(); iter++)
	{
		/* typeΪ0���Ի����񣬲���������ص���֤*/
		
		//��Ҫ��֤λ�õ�����֤λ���Ѿ���֤��
		if ((*iter)->type == 6)
		{
			if ((*iter)->value != 1)
			{
				cout<<"BisonWarn @task.cpp: the targer location is out finishing task range"<<endl;
				finishFlag = false;
			}
		}
		//0�ǶԻ���4����������Ҫ���
		else if ((*iter)->type != 0 && (*iter)->type != 4)
		{
			if ((*iter)->num != (*iter)->value) 
			{
				finishFlag = false;
				break;
			}
		}
	}
	return finishFlag;
}

/* getBeginTaskGive -- �õ���ʼ����ʱ��Ҫ����ҵĵ�����Ϣ */
int Task::getBeginTaskGive(char *beginGive)
{
	set<recv_t*>::iterator iter_recv;
	iter_recv = taskRecv.begin();
	// string giveMsg;
	for (iter_recv; iter_recv != taskRecv.end(); iter_recv++)
	{
		//�������������Ʒ
		if ((*iter_recv)->type == 0)
		{
			// giveMsg = giveMsg + (*iter_recv)->id + intTostring((*iter_recv)->num);
			sprintf(beginGive, "%s,%d", (*iter_recv)->id, (*iter_recv)->num);
			//��������������ֻ�ܸ�һ�֣��õ���Ϳ���ֹͣ������жϷ�����
			return 0;
			//add to bag
		}
		if ((*iter_recv)->type != 0)
		{ 
			//�������񣬰ѻ���ID����
			// giveMsg = (*iter_recv)->id;
			strncpy(beginGive, (*iter_recv)->id, sizeof((*iter_recv)->id));
			return 0;
		}
	}
	//give�б���û�н�����ʱ����Ҫ���ĵ���
	return -1;
}

//����������Ҫ����Ʒ
int Task::recycleTaskNeedGoods(map<string, int> &needRecycle)
{
	//Bag *bag = hero->bag;
	// string msg;
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	for (iter; iter != taskStatus.end(); iter++)
	{
		if ((*iter)->type == 2 || (*iter)->type == 18)
		{
			//��������ʱ����Ҫ���ٸ��ͻ��ն��ϸ�
			//bag->remove((*iter)->id, (*iter)->num, hero->getFd());
			// msg = (*iter)->id + intTostring((*iter)->num);
			// sprintf(needRecycle, "%s,%d", (*iter)->id, (*iter)->num);
			needRecycle.insert(pair<string, int>((*iter)->id, (*iter)->num));
			//��������û��һ�����������������͵��ߵ����
			// return 0;
		}
		else if ((*iter)->type == 3)
		{
			//������ߣ�ȫ������
			//bag->removeAll((*iter)->id, hero->getFd()); 
			//��ȫ�������ˣ�ֻ������Ҫ�ĸ������������������Լ�����
			// msg = (*iter)->id + intTostring((*iter)->num);
			// sprintf(needRecycle, "%s,%d", (*iter)->id, (*iter)->num);
			needRecycle.insert(pair<string, int>((*iter)->id, (*iter)->num));
			// return 0;
		}
	}
	if (needRecycle.size() == 0)
	{
		return -1;
	} else {
		return 0;
	}
}

static Point str2point(char* str)
{
	int pos = findChar(str, ',', strlen(str));
	if (pos == -1)
	{
		pos = findChar(str, ':', strlen(str));
		if (pos == -1)
		{
			cout<<"BisonWarning if you failed task ,please check this @task.cpp!"<<endl;
			cout<<"BisonWarning @task.cpp: You have given a str that can't exchange to Point"<<endl;
			pos = strlen(str);
		}
	}
	char xstr[16];
	sub_str(xstr, str, 0, pos);
	int PointX = atoi(xstr);
	sub_str(xstr, str, pos + 1, 0);
	int PointY = atoi(xstr);
	Point pt(PointX, PointY);
	return pt;
}

/**
 * taskUpdate -- ��������״̬
 * @_needId: �����������id
 * @_value:  ��Ҫ���õ�״̬����
 * @return: ���³ɹ�����need����ţ�����ʧ�ܷ���-1,����valueֵ���������Ч���£�����_needId���ڸ������need�����У�
 */
int Task::taskUpdate(char* _needId, int _value)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	int ret = 0;
	for (iter; iter != taskStatus.end(); iter++)
	{
		char* temp = (*iter)->id;
		int pos = 0;
		char oneNeedId[51];
		
		//��Ҫ��֤λ�õ���������, ��֤����ĸ���ʱ_value����-1��������һ��need��Id�����
		if ((*iter)->type == 6 && _value == -1)
		{
			//���͵���������
			if (findChar(temp, ':', strlen(temp)) == -1 || findChar(_needId, ',', strlen(_needId)) == -1)
			{
				return -1;
			}
			
			Point ptNeed = str2point(temp);
			Point ptGiven = str2point(_needId);
			cout<<"@@@@@@@@@@@@@@@@@@@@@BisonTest distance check@@@@@@@@@@@@@@@@@@@@@"<<endl; 
			cout<<"@@@@@@@@@@@@@@@@@@@@@BisonTest distance check@@@@@@@@@@@@@@@@@@@@@"<<endl; 
			cout<<"ptNeed._x "<<ptNeed._x<<endl;
			cout<<"ptNeed._y "<<ptNeed._y<<endl;
			cout<<"ptGiven._x "<<ptGiven._x<<endl;
			cout<<"ptGiven._y "<<ptGiven._y<<endl;
			cout<<"@@@@@@@@@@@@@@@@@@@@@BisonTest distance check@@@@@@@@@@@@@@@@@@@@@"<<endl; 
			cout<<"@@@@@@@@@@@@@@@@@@@@@BisonTest distance check@@@@@@@@@@@@@@@@@@@@@"<<endl; 
			int deltaX = ptNeed._x - ptGiven._x;
			int deltaY = ptNeed._y - ptGiven._y;
			int distance = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (distance > 400)
			{
				return -1;
			} else {
				//taskStatus_T *statusTemp = (*iter); //������ǰ��taskStatus�ṹ�ڴ�
				//statusTemp->value = _value;
				//taskStatus.erase(iter);
				//taskStatus.insert(statusTemp);
				//���������֤�ɹ���value�����³�1
				(*iter)->value = 1;
				return ret;
			}
		}
		if ((*iter)->type == 11)
		{
			if (_value < 0 || _value > (*iter)->num || _value <= (*iter)->value)
			{
				return -1;
			}
			(*iter)->value = _value;
			return ret;
		}
		
		int len = strlen(temp);
		while (len > 0)
		{
			pos = findChar(temp, ':', len);
			if (pos == -1)
			{
				strncpy(oneNeedId, temp, len + 1);
				temp = temp + len;
			}
			else 
			{
				sub_str(oneNeedId, temp, 0, pos);
				//strncpy(oneGuildId, temp, pos);
				temp = temp + pos + 1;
			}
			len = strlen(temp);
			if (!strcmp(oneNeedId, _needId))
			{
				if (_value < 0 || _value > (*iter)->num)
				{
					//invalid value
					cout<<"taskUpdate Invalid value"<<endl;
					return -1; 
					
				} else if (_value <= (*iter)->value) {
					//error update or no need to update;
					cout<<"taskUpdate little value now value is "<<(*iter)->value<<endl;
					return -1;
					
				} else {
					//valid update
					//������ǰ��taskStatus�ṹ�ڴ�
					(*iter)->value = _value;
					return ret;
				}
			}
		}
		//need��ż�1
		ret++;
	}
	
	cout<<"taskUpdate No Need"<<endl;
	return -1;
}

/**
 * getNeedType -- ���������needType
 * @needId: �����������id
 * @return: ���ҵ����������needId��Ӧ�����ͣ�����ʧ�ܷ���-2
 */
int Task::getNeedType(char* needId)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	int ret = 0;
	for (iter; iter != taskStatus.end(); iter++)
	{
		char* temp = (*iter)->id;
		int pos = 0;
		char oneNeedId[51];
		int len = strlen(temp);
		while (len > 0)
		{
			pos = findChar(temp, ':', len);
			if (pos == -1)
			{
				strncpy(oneNeedId, temp, len + 1);
				temp = temp + len;
			}
			else 
			{
				sub_str(oneNeedId, temp, 0, pos);
				//strncpy(oneGuildId, temp, pos);
				temp = temp + pos + 1;
			}
			len = strlen(temp);
			if (!strcmp(oneNeedId, needId))
			{
				return (*iter)->type;
			}
		}
	}
	
	return -2;
}

/* XXX:todo: */
int Task::taskCheckReward(char* _giveId, int _num)
{
	
}
/**
 * taskReward -- �����������
 * @_giveId�����ѡ�����Ʒid, �ò�����giveTypeΪ0����ϵͳĬ�Ϸ���ʱ����Ϊ��
 * @return: ���ء�,��Ʒid,������������string��ʽ�����giveTypeΪ0��ϵͳĬ�Ϸ��䡣
 * 	���������ȫ��Reward��Ʒ���У����giveType��Ϊ0ʱ��
 * 	����1:�ͻ��˷�����giveId�ڽ�����Ʒ�����У������ַ�����,giveId,num"
 * 	����2��giveId��ð��ģ������ַ�����,_giveId,0"
 */
int Task::taskGetReward(char* _giveId, map<string, int> &rewardList)
{
	
	set<give_t*>::iterator iter_give;
	iter_give = taskReward.begin();
	cout<<"giveType:"<<giveType<<endl;
	if (giveType == 0)
	{
		for (iter_give; iter_give != taskReward.end(); iter_give++)
		{
			//���ǿ�ʼ����ʱ��Ҫ����ҵĵ���
			if ((*iter_give)->type != 3)
			{
				rewardList.insert(pair<string, int>((*iter_give)->id, (*iter_give)->num));
				// msg = msg + "," + (*iter_give)->id + intTostring((*iter_give)->num);
			}
		}
		return 0;
	} else {
		for (iter_give; iter_give != taskReward.end(); iter_give++)
		{
			if (!strcmp((*iter_give)->id, _giveId))
			{
				rewardList.insert(pair<string, int>((*iter_give)->id, (*iter_give)->num));
				// msg = msg + "," + (*iter_give)->id + intTostring((*iter_give)->num);
				return 0;
			}
		}
		return -1;
	}
	
	// return msg;
}

/************************************************************
 * getTaskGoods -- �õ��������id
 * Return: ������Ѽ�������ߵ����񣬷���Ҫ�Ѽ����������ID
 *		   ���򣬷��ؿ�string
 ************************************************************/
char* Task::getTaskGoods(void)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	for (iter; iter != taskStatus.end(); iter++)
	{
		//�������
		if ((*iter)->type == 3 || (*iter)->type == 2)
		{
			if ((*iter)->value < (*iter)->num)
			{
				// taskGoodsId = (*iter)->id;
				return (*iter)->id;
			}
		}
	}
	
	return NULL;
}

//�������needType�������needId, ֻ���ͬһ��������ͬһ��needType������ֶ�ε����
int Task::getSpecialNeedId(int needType, char* needId)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	for (iter; iter != taskStatus.end(); iter++)
	{
		//�������
		if ((*iter)->type == needType)
		{
			strncpy(needId, (*iter)->id, sizeof((*iter)->id));
			return 0;
		}
	}
	
	return -1;
}

Task::~Task(void)
{
	list<taskStatus_T*>::iterator iter_status;
	iter_status = taskStatus.begin();
	for (iter_status; iter_status != taskStatus.end(); )
	{
		taskStatus_T *status = (*iter_status);
		//��ʱ��¼��ǰ���Ա㰲ȫɾ��
		iter_status++;
		//taskStatus.erase(iter_temp);
		delete status;
	}
	taskStatus.clear();
}

/**
 * getTaskStatusValue -- �õ������ĳ�������״̬����
 * @_needId: �����������id
 * @return: value��_needId�ĵ�ǰ״ֵ̬��-1��needId�������������б���
 */
int Task::getTaskStatusValue(char* _needId)
{
	int ret = -1;
	char oneNeedId[51];
	int pos;
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	for (iter; iter != taskStatus.end(); iter++)
	{
		char *temp = (*iter)->id;
		int len = strlen(temp);
		while (len > 0)
		{
			pos = findChar(temp, ',', len);
			if (pos == -1)
			{
				strncpy(oneNeedId, temp, len + 1);
				temp = temp + len;
			}
			else 
			{
				sub_str(oneNeedId, temp, 0, pos);
				//strncpy(oneGuildId, temp, pos);
				temp = temp + pos + 1;
			}
			len = strlen(temp);
			if (!strcmp(oneNeedId, _needId))
			{
				ret = (*iter)->value;
				goto LE;
			}
		}
	}
LE: ;	
	return ret;
}

int Task::getTaskChapt(void)
{
	return chapt;
}

//��ʼ��������
TaskData_T Task::initTaskData(void)
{
	TaskData_T taskData; 
	taskData.taskFlag = 0;					//��־Ϊ��Ч����
	strncpy(taskData.taskId, taskId, sizeof(taskData.taskId));
	
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	int i = 0;
	for (iter; iter != taskStatus.end(); iter++)
	{	
		taskData.status[i] = (*iter)->value;
		i++;
	}
	return taskData;
}

//��ȡ��������
int Task::getTaskType(void)
{
	return taskType;
}

//��ȡ����������
int Task::getSubType(void)
{
	return subType;
}

//�Ƿ���Ҫ�����ռ�ĳ�ֵ���
bool Task::needMoreCollection(char* collectionId)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	for (iter; iter != taskStatus.end(); iter++)
	{
		if ((*iter)->type == 2 || (*iter)->type == 14 || (*iter)->type == 15)
		{
			if (!strcmp((*iter)->id, collectionId) && (*iter)->value < (*iter)->num)
			{
				return true;
			}
		}
	}
	
	return false;
}

bool Task::getIsLastOfThisChapt()
{
	return isLastOfThisChapt;
}
/*
void Task::setTask_Monster_Accout(int _task_monster_accout)
{
	task_monster_accout = _task_monster_accout;
}
int Task::getTask_Monster_Accout()
{
	return task_monster_accout;
}

string Task::getTaskId(void)
{
	return taskId;
}
string Task::getTaskName(void)
{
	return taskName;
}
string Task::getTask_Type(void)
{
	return task_type;
}
string Task::getRecNpcId(void)
{
	return recNpcId;
}
string Task::getFinNpcId(void)
{
	return finNpcId;
}
string Task::getTask_Monster_Id(void)
{
	return task_monster_id;
}
int    Task::getTask_Monster_Num(void)
{
	return task_monster_num;
}
set<string> Task::getTask_Goods_Id(void)
{
	return task_goods_id;
}
int    Task::getTask_Gold_Num(void)
{
	return task_gold_num;
}
int    Task::getTask_Exp(void)
{
	return task_exp;
}
*/