/**
  * Filename: task_touch_configuration.h
  * Description: ��ȡ���񴥷����������ļ�
  * Author: bison @2012.5.25
  */

//#ifndef TASK_CONFIGURATION_H
//#define TASK_CONFIGURATION_H
#include<iostream>
#include<string>
#include<set>

using namespace std;
class Task_Touch_Configuration
{
	private:
		string touch_id;			// ��������id
		string taskId;				// ����id
		string touch_type;           // ��������
		unsigned int hero_level;     // ��ɫ�ȼ�
	public:
		Task_Touch_Configuration(string _touch_id, string _taskId, string _touch_type,unsigned int hero_level);
		string getTouch_Id(void);
		string getTaskId(void);
		string getTouch_Type(void);
		unsigned int getHero_Level(void);
};

//#endif