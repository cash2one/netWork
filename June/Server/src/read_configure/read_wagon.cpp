
/********************************************************************

    created:	2012/9/05  15:24
	
	�ļ�����	read_wagon.cpp

    author:     ChenZhen 

    purpose:  	������ȡ�������ļ�����ʽΪxml)
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
#include"wagon.h"
using namespace std;

extern map<string,Wagon*> wagonConfMap;
extern map<string, wagonColorRank_T*> wagonId_2_rankRate;	//ÿ������ɫˢ����

int read_wagon(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	int flgItem;
	string typeId;
	string name;
	string photoId;
	string goodsId;
	string color;
	int lifeVal;
	int hurt;
	float rewardTimes = 1.0f;					//��Ʒ������ϵ��
	bool haveSpeedGame;
	int blackSpeed;
	int yellowSpeed;
	int redSpeed;
	double gameLastTime;
	double gameCdTime;
	double incSpeedTime;
	
	//����ɫˢ�¸���
	int upRate;							//��Ʒ����������
	int downRate;						//��Ʒ�ʽ�������
	int stillRate;						//��Ʒ�ʲ���ĸ���
	char prevId[51] = {0};				//��һƷ����Id
	char nextId[51] = {0};				//��һƷ����Id
	Wagon *newWagon;
	
	strncpy(szDocName,fileName,strlen(fileName));
	
	
	//��ȡ��ͼ�����ļ�
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL == doc)
	{
		return -1;
	}
	
	//�õ�xml�ļ���root
	curNode=xmlDocGetRootElement(doc);
	if(NULL==curNode)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	
	//xml����ر���
	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_item;
	flgItem = 0;
	newWagon = NULL;
	
	//ѭ����ȡxml���ӽڵ㣬��ȡ�����Ӧ������	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"item"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*ȡ����ժȡ��Ʒ������id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
					xmlChar *_typeId=xmlGetProp(propNodePtr_item,(const xmlChar*)"typeId");
					typeId = const_cast<char *>(reinterpret_cast<const char *>(_typeId));					
					xmlFree(_typeId);
				}
				/*ȡ����������ֵ*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lifeVal"))
				{
					xmlChar *_lifeVal=xmlGetProp(propNodePtr_item,(const xmlChar*)"lifeVal");
					lifeVal = atoi(reinterpret_cast<const char *>(_lifeVal));					
					xmlFree(_lifeVal);
				}
				/*ȡ�������˺�ֵ*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hurt"))
				{
					xmlChar *_hurt=xmlGetProp(propNodePtr_item,(const xmlChar*)"hurt");
					hurt = atoi(reinterpret_cast<const char *>(_hurt));					
					xmlFree(_hurt);
				}
				
				//��ȡ����������
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardTimes"))
				{
					xmlChar *_rewardTimes=xmlGetProp(propNodePtr_item, (const xmlChar*)"rewardTimes");
					
					rewardTimes = atof(reinterpret_cast<const char *>(_rewardTimes));
					
					xmlFree(_rewardTimes);
				}
				
				//��ȡ����ɫˢ�½�����
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"upRate"))
				{
					xmlChar *_upRate=xmlGetProp(propNodePtr_item, (const xmlChar*)"upRate");
					
					upRate = atoi(reinterpret_cast<const char *>(_upRate));
					
					xmlFree(_upRate);
				}
				//��ȡ����ɫˢ�º�����
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"downRate"))
				{
					xmlChar *_downRate=xmlGetProp(propNodePtr_item, (const xmlChar*)"downRate");
					
					downRate = atoi(reinterpret_cast<const char *>(_downRate));
					
					xmlFree(_downRate);
				}
				//��ȡ����ɫˢ�²�����
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"stillRate"))
				{
					xmlChar *_stillRate=xmlGetProp(propNodePtr_item, (const xmlChar*)"stillRate");
					
					stillRate = atoi(reinterpret_cast<const char *>(_stillRate));
					
					xmlFree(_stillRate);
				}
				
				//��һƷ����ID		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prevId"))
				{
					xmlChar *_prevId=xmlGetProp(propNodePtr_item, (const xmlChar*)"prevId");
					
					strncpy(prevId, (char*)_prevId, sizeof (prevId));
					
					xmlFree(_prevId);
				}
				
				//��һƷ����ID		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"nextId"))
				{
					xmlChar *_nextId = xmlGetProp(propNodePtr_item, (const xmlChar*)"nextId");
					
					strncpy(nextId, (char*)_nextId, sizeof (nextId));
					
					xmlFree(_nextId);
				}
				
				/*ȡ��������ɫ*/		
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"color"))
				{
					xmlChar *_color=xmlGetProp(propNodePtr_item,(const xmlChar*)"color");
					
					color = const_cast<char *>(reinterpret_cast<const char *>(_color));
					
					xmlFree(_color);
				}
				
				/*��ȡ��ժȡ��Ʒ������*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{
					xmlChar *_name=xmlGetProp(propNodePtr_item,(const xmlChar*)"name");
					
					name = const_cast<char *>(reinterpret_cast<const char *>(_name));
					
					xmlFree(_name);
				}
				
				/*��ȡ��ժȡ��Ʒ��ͼƬid*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"photoId"))
				{
					xmlChar *_photoId=xmlGetProp(propNodePtr_item,(const xmlChar*)"photoId");
					
					photoId = const_cast<char *>(reinterpret_cast<const char *>(_photoId));
					
					xmlFree(_photoId);
				}
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"haveSpeedGame"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"haveSpeedGame");
					
					haveSpeedGame = atoi((char*)_item);
					
					xmlFree(_item);
				}
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"blackSpeed"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"blackSpeed");
					
					blackSpeed = atoi((char*)_item);
					
					xmlFree(_item);
				}
				
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"yellowSpeed"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"yellowSpeed");
					
					yellowSpeed = atoi((char*)_item);
					
					xmlFree(_item);
				}
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"redSpeed"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"redSpeed");
					
					redSpeed = atoi((char*)_item);
					
					xmlFree(_item);
				}
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"gameLastTime"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"gameLastTime");
					
					gameLastTime = atof((char*)_item);
					
					xmlFree(_item);
				}
				
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"gameCdTime"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"gameCdTime");
					
					gameCdTime = atof((char*)_item);
					
					xmlFree(_item);
				}
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"incSpeedTime"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"incSpeedTime");
					
					incSpeedTime = atof((char*)_item);
					
					xmlFree(_item);
					
					flgItem = 1;
				}
				
				/*ʵ������ժȡ��Ʒ��ͼƬid*/	
				if(flgItem == 1)
				{
					newWagon = new Wagon(const_cast<char*>(typeId.c_str()),\
										lifeVal,hurt,const_cast<char*>(color.c_str()),\
										 const_cast<char*>(name.c_str()),\
										 const_cast<char*>(photoId.c_str()), rewardTimes,
										 haveSpeedGame, blackSpeed, yellowSpeed, redSpeed,
										 gameLastTime, gameCdTime, incSpeedTime);
					wagonConfMap[typeId] = newWagon;
					wagonColorRank_T *oneItem = new wagonColorRank_T(upRate, downRate, stillRate, prevId, nextId);
					wagonId_2_rankRate[typeId] = oneItem;
					flgItem = 0;
				}		
					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	
	xmlFreeDoc(doc);
	return 0;
}

