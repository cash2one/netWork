/****************************************************************
 * Filename: read_guild_activity.cpp
 * 
 * Description: ��ȡ���ɻ��Ϣ
 *
 * Original Author : bison, 2012-9-13
 *
 ****************************************************************/
 
#include"guild_activity.h"
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<sstream>
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

extern map<string, GuildActivity*> id_2_guildAct;		//���ɻʵ��

int read_guild_activity_info(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ

	int guildLevelLimit;				//���ɵȼ�����
	char id[51];							//�ID
	int weekDay;						//����
	int beginHour;						//��ʼʱ��
	int beginMin;						//��ʼ����
	int endHour;						//�����ʱ���
	int endMin;							//������ķ�����

	//�����ļ�
	strcpy(szDocName, fileName);
	doc = xmlReadFile(szDocName, "UTF-8", XML_PARSE_RECOVER);
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

	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		//�����ȡ���ɻ�ڵ�
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Activity"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					//���
					xmlChar *_id = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);
					xmlFree(_id);
					
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"guildLevelLimit")) {
					//��԰��ɵȼ�������
					xmlChar *_limit = xmlGetProp(secondNode, (const xmlChar*)"guildLevelLimit");
					guildLevelLimit = atoi(reinterpret_cast<const char*>(_limit));
					xmlFree(_limit);
				}
			}
			
			//��ȡ�ʱ��ڵ�
			
			set<ActivityTime_T*> timeSet;
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Time"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"weekDay"))
						{	
							//���
							xmlChar *_weekDay = xmlGetProp(thirdNode, (const xmlChar*)"weekDay");
							weekDay = atoi(reinterpret_cast<const char*>(_weekDay));
							xmlFree(_weekDay);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"beginHour")) {
							//���ʼʱ
							xmlChar *_beginHour = xmlGetProp(thirdNode, (const xmlChar*)"beginHour");
							beginHour = atoi(reinterpret_cast<const char*>(_beginHour));
							xmlFree(_beginHour);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"beginMin")) {
							//���ʼ��
							xmlChar *_beginMin = xmlGetProp(thirdNode, (const xmlChar*)"beginMin");
							beginMin = atoi(reinterpret_cast<const char*>(_beginMin));
							xmlFree(_beginMin);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"endHour")) {
							//�����ʱ
							xmlChar *_endHour = xmlGetProp(thirdNode, (const xmlChar*)"endHour");
							endHour = atoi(reinterpret_cast<const char*>(_endHour));
							xmlFree(_endHour);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"endMin")) {
							//�������
							xmlChar *_endMin = xmlGetProp(thirdNode, (const xmlChar*)"endMin");
							endMin = atoi(reinterpret_cast<const char*>(_endMin));
							xmlFree(_endMin);
						}
					}
				
					ActivityTime_T *actTime = new ActivityTime_T(weekDay, beginHour, 
						beginMin, endHour, endMin);
						//cout<<"BisonTest: id "<<id<<": "<<weekDay<<"-"<<beginHour<<"-"<<beginMin<<"-"<<endHour<<"-"<<endMin<<endl;
					timeSet.insert(actTime);
				}
			}
			GuildActivity *guildAct = new GuildActivity(id, guildLevelLimit, timeSet);
			id_2_guildAct.insert(pair<string, GuildActivity*>(id, guildAct));
		}
	}
	cout<<"BisonTest: @read_guild_activity.cpp: "<<id_2_guildAct.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}