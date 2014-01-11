/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�user_role_manage_task.h
		�ļ����ã������ͻ��˷��͸�����������Ƿ����������Ϣ
		  ʵ���ߣ�Evan 
		���ʱ�䣺2012.5.18
*/
#include"user_role_finish_task.h"
#include"command_return_define_data.h"
#include"hero.h"
#include"task.h"
#include"task_configuration.h"
#include<string.h>
#include<iostream>
#include <arpa/inet.h>
#include <cstdlib>
#include <stdlib.h>
#include <sstream>
#include"command_other_function_all_over.h"
#include<map>
#include"pet_config.h"
#include"pet.h"
#include"pet_box.h"
#include"wagon.h"
#include"guild_asist.h"
#include"systemMessage.h"
#include"money_operator.h"
using namespace std;
#include"wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;

extern map<string, Hero*> heroId_to_pHero;
extern map<string,Pet_Config*>id_to_pet;
extern map<string,Wagon*> wagonInstMap;						//��ʵ��
extern int yabiaoDouble;

#define TASK_VARY_REWARD

#if defined(TASK_VARY_REWARD)
//0-�ճ������ɣ�1 - ��Ӫ���;3-ѭ������
const int moneyFactor[3] = {10, 5, 5};
const int expFactor[3][8] =
{
							0, 150, 150, 300, 500, 800, 1200, 1500,
							0, 70, 70, 120, 200, 300, 650, 1000,
							0, 100, 150, 250, 400, 700, 1200, 2000
};

#endif

void taskFinish(char *buff)
{
	cout<<"finish task check!"<<endl;
	char *heroId;	  //��ɫId
	char *taskId;     //����Id
	char *NPCId;      //��ҽ������NPCId 
	char *goodId;     //������ƷId
	
	
	MSG_BEGIN(buff, g_msg_len);
	MSG_CHAR(heroId);
	MSG_CHAR(taskId);
	MSG_CHAR(NPCId);
	MSG_CHAR_END(goodId);
	Hero *hero = pg_hero;
	
	char msg_task[64];
	
	sprintf(msg_task, "5,%d,%s,0", TASK_FINISH_RETURN, taskId);
	
	Task *task;
	map<string,Task*> task_list;
	
	task = hero->findAcceptedTaskList(taskId);
	if (task == NULL)
	{
		// msg_task = msg_task + intTostring(FAILED); 
		send_msg(hero->getFd(),msg_task);
		cout<<"[BisonWarn] Not find hero accepted this task taskid is "<<taskId<<endl;
		return ;
	}
	
	// string type = task->getTask_Type();
	// if(type == "1")  //״̬�ж�  �����ɲ߻��ṩ���ĵ����
	// {
		
	// }
	char* npcId_task = task->getFinNpcId();
	//cout<<"come here finid"<<endl;
	if(strcmp(NPCId, npcId_task))   //�ͻ���Ҫ�������NPC�Ƿ�����������������ļ��м�¼��Ҫ�������NPC�Ƿ�һ��
	{
		cout<<"[BisonWarn] the finishnpc is error when finish Task;"<<endl;
		// msg_task = msg_task + intTostring(FAILED); 
		send_msg(hero->getFd(),msg_task);
		return ;
	}
	
	//����������⴦��
	Wagon *wagon = NULL;
	if (!strcmp(taskId, "task00295") || !(strcmp(taskId, "task00419")))
	{
		char* wagonId = hero->memHero->wagonId;
		
		cout<<"BisonTest: You have come here with a wagon "<<wagonId<<endl;
		if (strlen(wagonId) == 0)
		{
			cout<<"Wagon is dead so can't finish wagon task!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		
		map<string,Wagon*>::iterator it_wagon;
		cout<<"BisonTest��wagonInstMap size is "<<wagonInstMap.size()<<endl;
		it_wagon = wagonInstMap.find(wagonId);
		if (it_wagon == wagonInstMap.end())
		{
			//û�������
			cout<<"Wagon is dead so can't finish wagon task!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		
		wagon = it_wagon->second;
		
		//�Ƚ����������ǲ���������
		Hero *owner = wagon->getOwner();
		if (owner == NULL)
		{
			cout<<"Wagon doesn't have owner when finish Task!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		char* ownerId = owner->getIdentity();
		if (strcmp(ownerId, hero->getIdentity()))
		{
			//�������˲���������
			cout<<"Wagon's owner is not this hero!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		
		//����������
		Point pt = wagon->getPt();
		// string pointStr = intTostring(pt._x).substr(1);
		// pointStr += intTostring(pt._y);
		char pointStr[32];
		sprintf(pointStr, "%d,%d", pt._x, pt._y);
		cout<<"BisonTest wagon Point is "<<pointStr<<endl;
		int ret = task->taskUpdate(pointStr, -1);
		if (ret == -1)
		{
			cout<<"The wagon is too far away from the finish NPC!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		
		//�����Ƿ���Ѫ
		if (wagon->getLifeVal() <= 0)
		{
			//���Ѿ�����
			cout<<"Wagon's is dead!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		cout<<"BisonTest: all Ok with wagon!"<<endl;
	}
	//��֤��������Ƿ�����
	if (!task->isTaskFinish())
	{
		// msg_task = msg_task + intTostring(FAILED); 
		send_msg(hero->getFd(),msg_task);
		cout<<" finish Fail"<<endl;
		return;
	} else {
		cout<<" finish Success"<<endl;
	}

	unsigned inFors = task->getInFors();
	unsigned prestige = task->getPrestige();
	unsigned gold = task->getTaskGold();						//��ȡ��������Ǯ
	unsigned exp = task->getTaskExp();							//��ȡ��ɵ��������ľ���
	int giveType = task->getGiveType();							//��ȡ��������Ʒ��ʽ
	
	int taskType = task->getTaskType();
	int heroLevel = hero->getLevel();
	if (taskType == 2 || taskType == 5)
	{
		gold = gold * heroLevel * heroLevel;
		exp = exp * heroLevel * heroLevel * heroLevel;
	} else if (taskType == 8 || taskType == 7)
	{
		gold = gold * heroLevel * heroLevel;
		exp = exp * heroLevel * heroLevel * heroLevel;
	} else if (taskType == 4)
	{
		gold = gold * heroLevel * heroLevel;
		exp = exp * heroLevel * heroLevel * heroLevel;
	} else if (taskType == 9)
	{
		double cycleFactor = hero->getCycleTaskRewardFactor();
		gold = gold * heroLevel * heroLevel * cycleFactor;
		exp = exp * heroLevel * heroLevel * heroLevel * cycleFactor;
	}
	
	if (taskType == 1)
	{
		pg_hero->updataSingleTarget(0,0);			//����Ŀ��
	}
	
	//jolly added ��ĳЩ���ʱ��,����������Ҫ�౶����,�ڴ˴����,����������ѯ start
	//�������� ˫������
	if (strcmp(taskId, "task00295")==0)		
	{
		exp=exp*yabiaoDouble;
	}
	//jolly added ��ĳЩ���ʱ��,����������Ҫ�౶����,�ڴ˴����,����������ѯ end
	
	map<string, int> rewardList;
	//�������ϵͳ������Ʒ����һ�û��ѡ����ȡ������Ʒ�����������ʧ�ܴ���
	if (giveType != -1)
	{
		if (giveType != 0 && goodId[0] == '\0')
		{
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			cout<<"BisonTest in user_role_finish_task.cpp:161!"<<endl;
			cout<<"If you see this , it shows that the giveType of task.xml in server not same with the client's!"<<endl;
			cout<<"The server's giveType is "<<giveType<<endl;
			return ;
		}
		rewardList.clear();
		task->taskGetReward(goodId, rewardList);
		Bag *bag=hero->getBag();
		if (bag->bagIsFull(rewardList.size()))
		{
			send_msg(hero->getFd(),msg_task);
			cout<<"Bison Test: user_role_finish_task.cpp:205. reward size is "<<rewardList.size()<<endl;
			cout<<"There is not enough idle spaces in bag to store the rewards!"<<endl;
			return ;
		}
		
		hero->addInternalForces(inFors);
		hero->addPrestigeValue(prestige);
		hero->setExpNow(exp);
		increaseBoundGameMoney(hero,gold);
		map<string, int>::iterator it_reward;
		it_reward = rewardList.begin();
		for (it_reward; it_reward != rewardList.end(); it_reward++)
		{
			saveGoodsInBag(hero, const_cast<char*>(it_reward->first.c_str()), it_reward->second);
		}
		
	} else {			
		hero->setExpNow(exp);
		increaseBoundGameMoney(hero,gold);
	}
	
	//����һ����Ͳ��ܷ���failed��
	int chapt = task->getTaskChapt();
	hero->delAcceptedTaskList(taskId);							//ɾ����Ӧ���ѽ�����

	//hero->memHero->taskSaveData.acced[chapt];
	//��������Ҫ����Ʒ���գ�
	rewardList.clear();
	int needRecycle = task->recycleTaskNeedGoods(rewardList);			//��ȡ��Ҫ���յ����������Ϣ added by bison 7.5
	Bag *bag = hero->getBag();
	if (needRecycle == 0)
	{
		map<string, int>::iterator it_rec = rewardList.begin();
		for (;it_rec != rewardList.end(); it_rec++)
		{
			if (it_rec->second == 0)
			{
				useAllGoods(hero, const_cast<char *>(it_rec->first.c_str()));
			}
			else {
				int _index=bag->searchIndex(const_cast<char *>(it_rec->first.c_str()));
				// if (bag->finishTask(it_rec->second, _index))
				if (useBagGoods(hero, const_cast<char *>(it_rec->first.c_str()),it_rec->second)==0)
				{
					send_msg_useSuccess(hero,_index);
				}
			}
		}
		
	}
	
	// msg_task = msg_task + intTostring(SUCCESS);
	
	//��������Ʒ�������þ����Ǯ�����Է�ֹ��������������������Ʒ������
	//hero_add_exp(hero,exp);             //����������þ���ӵ�������
	
	float rewardTimes = 1.0f;
	if (wagon != NULL)
	{
		rewardTimes = wagon->getRewardTimes();
	}
	//����ǰ�������Ļ����а��ɽ���
	if (task->getTaskType() == 2)
	{
		char guildTaskReward[200] = {0};
		// string guildTaskReward = getGuildTaskReward(hero, taskId);
		int ret = getGuildTaskReward(hero, taskId, guildTaskReward, rewardTimes);
		if (ret != 0 || strlen(guildTaskReward) != 0)
		{ 
			systemSendMssage(hero, guildTaskReward, 3);
		}
		//send_msg(hero->getFd(), guildRewardMsg);
	}
	//������
	if (wagon != NULL)
	{
		wagon->disperMsg();
		if (wagonInstMap.find(wagon->getId()) != wagonInstMap.end())
		{
			wagonInstMap.erase(wagonInstMap.find(wagon->getId()));
		}
		delete wagon;
		wagon = NULL;
		strncpy(hero->memHero->wagonId, "\0", 2);
	}   
	if (strcmp(taskId,"task00419")==0)//��Ӫ����
	{
		hero->updataSingleTarget(1,5);
	}   
	else if (strcmp(taskId,"task00005")==0)
	{
		hero->updataSingleTarget(0,2);
	}
	else if (strcmp(taskId,"task00381")==0||strcmp(taskId,"task00385")==0||strcmp(taskId,"task00389")==0||strcmp(taskId,"task00393")==0 \
	||strcmp(taskId,"task00397")==0||strcmp(taskId,"task00401")==0)//��Ӫ����
	{
		hero->updataSingleTarget(2,11);
	}
	else if (strcmp(taskId,"task00398")==0||strcmp(taskId,"task00394")==0||strcmp(taskId,"task00390")==0||strcmp(taskId,"task00386")==0 \
	||strcmp(taskId,"task00382")==0||strcmp(taskId,"task00378")==0)		//����
	{
		hero->updataSingleTarget(2,12);
	}
	else if (strcmp(taskId,"task00399")==0||strcmp(taskId,"task00395")==0||strcmp(taskId,"task00391")==0||strcmp(taskId,"task00387")==0 \
	||strcmp(taskId,"task00383")==0||strcmp(taskId,"task00379")==0)	//��ʹ
	{
		hero->updataSingleTarget(2,13);
	}
	
	//map<string,Task*> task_list_finish;
/*
	set<string> task_list_finish;
	task_list_finish = hero->getFinish_Task_List();         //��ȡ����ѽ������б�
	
	task_list_finish.insert(taskId);
//	task_list_finish[taskId] = task;  

	hero->setFinish_Task_List(task_list_finish);
*/
	
	// msg_task = msg_task + intTostring(gold) + intTostring(hero->getExpNow()); 
	sprintf(msg_task, "5,%d,%s,1,%d,%d", TASK_FINISH_RETURN, taskId, gold, hero->getExpNow());
	send_msg(hero->getFd(),msg_task);
	//��λͼ�����滻,���ں��棬�Է��л�����
	hero->setFinishTaskMap(taskId);
	
	if (task->getSubType() == 1)
	{
		hero->setTaskNeedKillNpcBossId(NULL);
	}
	
	if (task->getIsLastOfThisChapt())
	{
		hero->setTaskPassChapt(chapt);
	}
	
	if (task->getTaskType() == 9)
	{
		hero->setCycleTaskFinish(taskId);
	}
	
	//�༶����
	if (task->getTaskType() == 4)
	{
		//�ճ�����֮�༶����֮���������
		//�Ѹ����������������Ϊ�ɽ�
		//ֻ�ж༶����֮�������needType �Ż�Ϊ20
		char sonTaskIdSet[100];
		memset(sonTaskIdSet, 0, sizeof(sonTaskIdSet));
		task->getSpecialNeedId(20, sonTaskIdSet);
		cout<<"BisonTest: sonTaskIdSet is "<<sonTaskIdSet<<endl;
		if(strlen(sonTaskIdSet) == 0)
		{	
			//�༶�������������ɣ�Ҫ�����������״̬
			cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&taskId is "<<taskId<<endl;
			hero->updateHeroTaskStatus(CYCLE_TASK_NEED_TYPE, taskId); 
		}
	}
	
	delete task; 
}