/****************************************************************
 * Filename: task_failed_comm.cpp
 * 
 * Description: ����ʧ��
 *
 * Original Author : bison, 2012-9-12
 *
 ****************************************************************/

#include"task_failed_comm.h"
#include"command_return_define_data.h"

//����ʧ�ܴ���
void taskFailedDeal(Hero *hero, char* taskId, int flag)
{
	Task *task = hero->delAcceptedTaskList(taskId);
	if (task != NULL)
	{
		char msg[64];
		// msg = "5";
		// msg += intTostring(TASK_FAILED_RETURN);
		// msg += "," + taskId;
		sprintf(msg, "5,%d,%s", TASK_FAILED_RETURN, taskId);
		send_msg(hero->getFd(), msg);
		cout<<"BisonShow the task is failed! and msg is "<<msg<<endl;
		
		if (flag == 0)
		{
			//�����ؽӵ�����
			hero->setFinishTaskMap(taskId);
		}
		delete task;
	}
}