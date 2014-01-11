#include"function_read_configuration_files.h"
#include"task_configuration.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string.h>
using namespace std;
extern map<string,Task_Configuration*> id_to_task;
map<int, TaskChaptReward_T> chapt_2_taskReward;
int read_files_task(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;
	xmlNodePtr typeNode;
	xmlNodePtr chaptNode;
	xmlNodePtr curNode;
	xmlNodePtr childNode;
	xmlAttrPtr attrPtr;    //�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	char taskId[51];		//����ID
	char taskName[51];   	//��������
	char recNpcId[51];      //������NPC id
	char finNpcId[51];      //������NPC id
	int taskType;      	//�������ͣ����ߡ�֧�ߵ�
	int taskChapt;     	//�����½ڣ����ݵȼ�����
	unsigned taskLevel;	//����ȼ�
	unsigned inFors;
	unsigned prestige;
	unsigned taskGold;  //��������Ǯ
	unsigned taskExp;	//����������
	int subType = 0;	//����������
	int giveType;		//��������������Ʒ�ķ�ʽ��0��ϵͳĬ�ϣ�1�����ѡ��
	int freq;			//����һ��ɽӴ���
	bool isLastOfThisChapt;
	char chaptReward[51] = {0};
	char chaptRewardNum = 0;
	
	/* �������Ҫ������ */
	list<need_t*> taskNeed;
	/* ���������� */
	set<give_t*> taskGive;
	/* ���񴥷��������� */
	set<touch_t*> taskTouch;
	/* �������ʱ������������ */
	set<recv_t*> taskRecv;
	
//	xmlKeepBlanksDefault(0);
//	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	doc = xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER); //�����ļ�
	if (doc == NULL)
	{
		return -1;
	}
	
	//�õ�xml�ļ���root
	rootNode = xmlDocGetRootElement(doc);
	if (rootNode == NULL)
	{
		xmlFreeDoc(doc);
		return -1;
	}
	
	for (typeNode = rootNode->xmlChildrenNode; typeNode != NULL; typeNode = typeNode->next)
	{
		//��ȡ��������
		taskType = 0;	//�ȳ�ʼΪ0���Ժ��ٶ���ȱʡֵ
		if (!xmlStrcmp (typeNode->name, (const xmlChar*)"taskType"))
		{
			attrPtr = typeNode->properties;
			xmlChar *_taskType = xmlGetProp(typeNode, (const xmlChar *)"type");
			taskType = atoi(reinterpret_cast<const char *>(_taskType));
			xmlFree(_taskType);
			
			
		}
		
		//����ÿ�½�
		for (chaptNode = typeNode->xmlChildrenNode; chaptNode != NULL; chaptNode = chaptNode->next)
		{
			//��ȡ�����½�
			taskChapt = 0;			//�ȳ�ʼΪ0���Ժ��ٶ���ȱʡֵ
			if (!xmlStrcmp (chaptNode->name, (const xmlChar*)"Chapters"))
			{
				TaskChaptReward_T tempChaptReward;
				int cnt = 0;
				for (attrPtr = chaptNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
				{
					if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
					{
						xmlChar *_taskChapt = xmlGetProp(chaptNode, (const xmlChar *)"id");
						taskChapt = atoi((char*)_taskChapt);
						xmlFree(_taskChapt);
					} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardId"))
					{
						xmlChar *_item = xmlGetProp(chaptNode, (const xmlChar*)"rewardId");
						strncpy(tempChaptReward.rewardId, (char*)_item, sizeof tempChaptReward.rewardId);
						xmlFree(_item);
						cnt++;
					} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"num"))
					{
						xmlChar *_item = xmlGetProp(chaptNode, (const xmlChar*) "num");
						tempChaptReward.rewardNum = atoi((char*)_item);
						xmlFree(_item);
						cnt++;
					}
				}
				
				if (cnt > 0)
				{			
					chapt_2_taskReward.insert(pair<int, TaskChaptReward_T>(taskChapt, tempChaptReward));
				}
		
			}
			
			//�������ڵ�
			for (curNode = chaptNode->xmlChildrenNode; curNode != NULL; curNode = curNode->next)
			{
				if (!xmlStrcmp(curNode->name, (const xmlChar*)"task"))
				{	//��task�ڵ������
					taskLevel = 0;         //�����ļ����ڲ���ÿ��������level���ԣ�����Ĭ��ֵ0
					for (attrPtr = curNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"subType")) {	
							/* ������������� */
							xmlChar *_subType = xmlGetProp(curNode, (const xmlChar*)"subType");
							subType = atoi((char*)_subType);				
							//cout<<"in read_task_config::taskId: "<<taskId<<endl;
							xmlFree(_subType);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"isLastOfThisChapt"))
						{
							xmlChar *_item = xmlGetProp(curNode, (const xmlChar*)"isLastOfThisChapt");
							isLastOfThisChapt = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id")) {	
							/* ������id���� */
							xmlChar *_taskId = xmlGetProp(curNode, (const xmlChar*)"id");
							strncpy(taskId, const_cast<char *>(reinterpret_cast<const char *>(_taskId)), 51);				
							//cout<<"in read_task_config::taskId: "<<taskId<<endl;
							xmlFree(_taskId);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"name")) {	
							/* ������name���� */
							xmlChar *_name = xmlGetProp(curNode, (const xmlChar*)"name");
							strncpy(taskName, const_cast<char *>(reinterpret_cast<const char *>(_name)), 51);			
							xmlFree(_name);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"receiveNPC")) {
							/* ��������ܵ�NPC id���� */
							xmlChar *_recNpcId = xmlGetProp(curNode, (const xmlChar*)"receiveNPC");
							strncpy(recNpcId, const_cast<char *>(reinterpret_cast<const char *>(_recNpcId)), 51);			
							xmlFree(_recNpcId);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardNPC")) {
							/* ���������NPC id���� */
							xmlChar *_finNpcId = xmlGetProp(curNode, (const xmlChar*)"rewardNPC");
							strncpy(finNpcId, const_cast<char *>(reinterpret_cast<const char *>(_finNpcId)), 51);			
							xmlFree(_finNpcId);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"level")) {
							/* ��ȡ����ȼ����� */
							xmlChar *_taskLevel = xmlGetProp(curNode, (const xmlChar*)"level");
							taskLevel = atoi(reinterpret_cast<const char*>(_taskLevel));
							xmlFree(_taskLevel);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"infors"))
						{
							xmlChar* _item = xmlGetProp(curNode, (const xmlChar*)"infors");
							inFors = atoi((char*)_item);
							xmlFree(_item);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestige"))
						{
							xmlChar* _item = xmlGetProp(curNode, (const xmlChar*)"prestige");
							prestige = atoi((char*)_item);
							xmlFree(_item);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money")) {
							/* ��ȡ�����Ǯ�������� */
							xmlChar *_taskGold = xmlGetProp(curNode, (const xmlChar*)"money");
							taskGold = atoi(reinterpret_cast<const char*>(_taskGold));
							xmlFree(_taskGold);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"experience")) {
							/* ��ȡ�����齱������ */
							xmlChar *_taskExp= xmlGetProp(curNode, (const xmlChar*)"experience");
							taskExp = atoi(reinterpret_cast<const char*>(_taskExp));
							xmlFree(_taskExp);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"giveType")) {
							/* ��ȡ��������Ʒ��ʽ���� */
							xmlChar *_giveType= xmlGetProp(curNode, (const xmlChar*)"giveType");
							giveType = atoi(reinterpret_cast<const char*>(_giveType));
							xmlFree(_giveType);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"frequency")) {
							if (taskType == 2) {
								/* ��ȡ����һ��ɽӴ������� */
								xmlChar *_freq= xmlGetProp(curNode, (const xmlChar*)"frequency");
								freq = atoi(reinterpret_cast<const char*>(_freq));
								xmlFree(_freq);
							}
						}
					}
					
					//��task���ӽڵ�need �� give
					for (childNode = curNode->xmlChildrenNode; childNode != NULL; childNode = childNode->next)
					{
						if (!xmlStrcmp(childNode->name, (const xmlChar*)"need"))
						{	//��task��need�ӽڵ������
							int need_type;
							char need_id[51];
							int need_num;	
							for (attrPtr = childNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"type"))
								{	
									/* ���������� */
									xmlChar *_type = xmlGetProp(childNode, (const xmlChar*)"type");
									need_type = atoi(reinterpret_cast<const char *>(_type));
									xmlFree(_type);
							
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id")) {	
									/* �����������Ҫ�������Ʒid */
									xmlChar *_id = xmlGetProp(childNode, (const xmlChar*)"id");
									strncpy(need_id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);	
									xmlFree(_id);
									
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"num")) {
									/* ���������Ҫ���� */
									xmlChar *_num = xmlGetProp(childNode, (const xmlChar *)"num");
									need_num = atoi(reinterpret_cast<const char *>(_num));
									xmlFree(_num);
								
								}
							}
							
							need_t *need = new need_t(need_type, need_id, need_num); //ʵ��need �ṹ
							taskNeed.push_back(need);
							
						}  else if (!xmlStrcmp(childNode->name, (const xmlChar*)"give")) {	
							//��task��give�ӽڵ������
							int give_type;
							char give_id[51];
							int give_num;
							for (attrPtr = childNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"type"))
								{	
									/* ������������ */
									xmlChar *_type = xmlGetProp(childNode, (const xmlChar*)"type");
									give_type = atoi(reinterpret_cast<const char *>(_type));
									xmlFree(_type);
							
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id")) {	
									/* ����������Ʒid */
									xmlChar *_id = xmlGetProp(childNode, (const xmlChar*)"id");
									strncpy(give_id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);	
									xmlFree(_id);
									
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"num")) {
									/* �������� */
									xmlChar *_num = xmlGetProp(childNode, (const xmlChar *)"num");
									give_num = atoi(reinterpret_cast<const char *>(_num));
									xmlFree(_num);
								
								}
							}
							
							give_t *give = new give_t(give_type, give_id, give_num); //ʵ��give �ṹ
							taskGive.insert(give);
							
						} else if (!xmlStrcmp(childNode->name, (const xmlChar*)"touch")) {	
							//��task��touch�ӽڵ������
							int touch_type;
							char touch_id[51];
							int touch_num;
							for (attrPtr = childNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"type"))
								{	
									/* �����񴥷����� */
									xmlChar *_type = xmlGetProp(childNode, (const xmlChar*)"type");
									touch_type = atoi(reinterpret_cast<const char *>(_type));
									xmlFree(_type);
							
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id")) {	
									/* �����񴥷���Ʒid */
									xmlChar *_id = xmlGetProp(childNode, (const xmlChar*)"id");
									strncpy(touch_id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);	
									
									xmlFree(_id);
									
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"num")) {
									/* ������ʱδȷ���书�� */
									xmlChar *_num = xmlGetProp(childNode, (const xmlChar *)"num");
									touch_num = atoi(reinterpret_cast<const char *>(_num));
									xmlFree(_num);
								
								}
							}
							
							touch_t *touch = new touch_t(touch_type, touch_id, touch_num); //ʵ��touch �ṹ
						
							taskTouch.insert(touch);
						}  else if (!xmlStrcmp(childNode->name, (const xmlChar*)"recv")) {	
							//��task��touch�ӽڵ������
							int recv_type;
							char recv_id[51];
							int recv_num;
							for (attrPtr = childNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"type"))
								{	
									/* �����񴥷����� */
									xmlChar *_type = xmlGetProp(childNode, (const xmlChar*)"type");
									recv_type = atoi(reinterpret_cast<const char *>(_type));
									xmlFree(_type);
							
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id")) {	
									/* �����񴥷���Ʒid */
									xmlChar *_id = xmlGetProp(childNode, (const xmlChar*)"id");
									strncpy(recv_id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);	
									xmlFree(_id);
									
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"num")) {
									/* ������ʱδȷ���书�� */
									xmlChar *_num = xmlGetProp(childNode, (const xmlChar *)"num");
									recv_num = atoi(reinterpret_cast<const char *>(_num));
									xmlFree(_num);
								
								}
							}
							
							recv_t *recv = new recv_t(recv_type, recv_id, recv_num); //ʵ��give �ṹ
							taskRecv.insert(recv);
						}
					} /* end of for ����task�ӽڵ� */
					
					/* ʵ��һ��task_conf */
					Task_Configuration *task_conf = new Task_Configuration(taskId, taskName,
					recNpcId, finNpcId, freq, taskType, inFors, prestige, taskGold, taskExp, giveType, taskChapt, taskLevel,
					taskNeed, taskGive, taskTouch, taskRecv, subType, isLastOfThisChapt);
						
					id_to_task[taskId] = task_conf;
					taskNeed.clear();
					taskGive.clear();
					taskTouch.clear();
					taskRecv.clear();
					//cout<<"read taskId of "<<taskId<<endl;
					
				} /* end of if �ڵ�Ϊtask */
				
			} /* end of for �ڵ���� */
		} /* end of for chapt */
	}	/*end of for type */
	//cout<<"&&&&&&&&&&&&&&&&&&&&&&::::"<<id_to_task.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}