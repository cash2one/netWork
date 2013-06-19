/****************************************************************
 * Filename: read_happy_map.cpp
 * 
 * Description: ��ȡ���ֵ�ͼ��������
 *
 * Original Author : bison, 2012-10-11
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

HappyMapReward_T HappyMapRewardConf;			//����ͼ��������

int read_happy_map(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ
	int grade = 0;
	int expIndex = 0;
	int monIndex = 0;
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"reward"))
		{
					
			expIndex = 0;
			monIndex = 0;
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"grade")) {
					//��ҵȼ�
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"grade");
					grade = atoi((char*)_item);
					xmlFree(_item);
					if (grade < 0 || grade > 80)
					{
						cout<<"hero level in happy map conf is error!"<<endl;
						return -1;
					}
				} else if (!xmlStrncmp(attrPtr->name, (const xmlChar*)"vipExp", 6)) {
					//��ͨ��ҵ�ǰ�ȼ����齱��ϵ��
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					HappyMapRewardConf.rewardLevel[grade].ExpFactor[expIndex++] = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrncmp(attrPtr->name, (const xmlChar*)"vipMon", 6)) {
					//��ͨ��ҵ�ǰ�ȼ���Ǯ����ϵ��
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					HappyMapRewardConf.rewardLevel[grade].MonFactor[monIndex++] = atoi((char*)_item);
					xmlFree(_item);
				}
			}
		}
	}

	// cout<<"BisonTest: @read_happy_map.cpp: "<<endl;
	// cout<<"incHappyExpBase and incHappyMoneyBase are "<<endl;
	// cout<<incHappyExpBase[0]<<"\t"<<incHappyExpBase[1]<<"\t"<<incHappyExpBase[2]<<"\t"<<incHappyExpBase[3]<<endl;
	// cout<<incHappyMoneyBase[0]<<"\t"<<incHappyMoneyBase[1]<<"\t"<<incHappyMoneyBase[2]<<"\t"<<incHappyMoneyBase[3]<<endl;
	xmlFreeDoc(doc);
	return 0;
}