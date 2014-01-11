/****************************************************************
 * Filename: read_task_goods.cpp
 * 
 * Description: �����������Ϣ
 *
 * Original Author : bison, 2012-6-13
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include"task_goods_info.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

//������ߵ�ȫ�ֱ���
extern map<string, TaskGoodsInfo*> id2taskGoodsInfo;

int read_task_goods_info(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ

	char taskGoodsId[51] = {0};						//�������ID
	char monsterId[1024] = {0};						//����ID
	double rate;							//��������������ߵĸ���

	strcpy(szDocName, fileName);
	doc = xmlReadFile(szDocName, "UTF-8", XML_PARSE_RECOVER); //�����ļ�
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Item"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"taskGoodsId"))
				{
					//��ȡ�������id
					xmlChar *_taskGoodsId = xmlGetProp(secondNode, (const xmlChar*)"taskGoodsId");
					strncpy(taskGoodsId, const_cast<char *>(reinterpret_cast<const char *>(_taskGoodsId)), sizeof taskGoodsId);
					xmlFree(_taskGoodsId);
					
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"monsterId")) {
					//��ȡ����id
					xmlChar *_monsterId = xmlGetProp(secondNode, (const xmlChar*)"monsterId");
					strncpy(monsterId, const_cast<char *>(reinterpret_cast<const char *>(_monsterId)), sizeof monsterId);
					xmlFree(_monsterId);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rate")) {
					//��ȡ����������Ʒ�ĸ���
					xmlChar *_rate = xmlGetProp(secondNode, (const xmlChar*)"rate");
					rate = atof(reinterpret_cast<const char*>(_rate));
					xmlFree(_rate);
				} 
			}
			TaskGoodsInfo* tskGoodsInfo = new TaskGoodsInfo(taskGoodsId, monsterId, rate);
			id2taskGoodsInfo.insert(pair<string, TaskGoodsInfo*>(taskGoodsId, tskGoodsInfo));
		}
	}
	xmlFreeDoc(doc);
	
	map<string, TaskGoodsInfo*>::iterator iter;
	iter = id2taskGoodsInfo.begin();
	TaskGoodsInfo *tinf = iter->second;
	
	return 0;
}