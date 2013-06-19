/****************************************************************
 * Filename: task_goods.cpp
 * 
 * Description: ���������Ϣ
 *
 * Original Author : bison, 2012-7-6
 *
 ****************************************************************/

#ifndef _TASK_GOODS_H_
#define _TASK_GOODS_H_

#include"command_other_function_all_over.h"
#include<time.h>

//���������Ϣ
class TaskGoodsInfo
{
	private:
		char taskGoodsId[51];
		char monsterId[1024];
		double rate;
		
	public:
		TaskGoodsInfo(char* _taskGoodsId, char* _monsterId, double _rate);
		//�ô��Ƿ����
		bool dropTaskGoodsOk(void);
		//��ȡ�������ID
		char* getTaskGoodsId(void);
		//��ȡ��Ӧ����ID
		char* getMonsterId(void);
		//��������Ĺ����Ƿ����õ���
		bool isMonsterDrop(char* deadMonsterId);
};
#endif
