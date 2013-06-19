
/********************************************************************

    created:	2012/9/05  15:24
	
	�ļ�����	read_bottle.cpp

    author:     ChenZhen 

    purpose:  	������ȡƿ�������ļ�����ʽΪxml)
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
using namespace std;

extern map<int,RewardFactor> factor_reward;

int read_factor_reward(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	int level;
	RewardFactor rewardFactor;
	
	strncpy(szDocName,fileName,strlen(fileName));
	
	
	//��ȡ��ͼ�����ļ�
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL == doc)
	{
		return -1;
	}
	
	//�õ�xml�ļ���root
	curNode=xmlDocGetRootElement(doc);
	if(NULL == curNode)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	
	//xml����ر���
	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_item;
	
	//ѭ����ȡxml���ӽڵ㣬��ȡ�����Ӧ������	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"reward"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{						
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"grade"))
				{
					xmlChar *_level=xmlGetProp(propNodePtr_item,(const xmlChar*)"grade");
					level =atoi(reinterpret_cast<const char *>(_level));					
					xmlFree(_level);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lixianFactor"))
				{
					xmlChar *_lixianFactor=xmlGetProp(propNodePtr_item,(const xmlChar*)"lixianFactor");
					rewardFactor.lixianFactor = atoi(reinterpret_cast<const char *>(_lixianFactor));					
					xmlFree(_lixianFactor);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lianxuFactor"))
				{
					xmlChar *_lianxuFactor=xmlGetProp(propNodePtr_item,(const xmlChar*)"lianxuFactor");
					rewardFactor.lianxuFactor = atoi(reinterpret_cast<const char *>(_lianxuFactor));					
					xmlFree(_lianxuFactor);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dazuoFactor"))
				{
					xmlChar *_dazuoFactor=xmlGetProp(propNodePtr_item,(const xmlChar*)"dazuoFactor");
					rewardFactor.dazuoFactor = atoi(reinterpret_cast<const char *>(_dazuoFactor));					
					xmlFree(_dazuoFactor);
					
					factor_reward.insert(map<int,RewardFactor>::value_type(level,rewardFactor));
				}					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}

