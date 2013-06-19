/****************************************************************
 * Filename: read_cycle_task_reward.cpp
 * 
 * Description: ��ȡÿ��ѭ������Ŀ
 *
 * Original Author : bison, 2012-9-24
 *
 ****************************************************************/
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<sstream>
#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<string>
#include "task.h"
using namespace std;

map<int, vector<double> > cycleTaskRewardFactor;

int read_cycle_task_reward_info(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ

	int cycleTaskLevel = 0;
	int cycleTaskLoop = 0;
	double rewardFactor = 0.;

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

	cout<<"BisonTest:begin @read_cycle_task_reward.cpp"<<endl;

	vector<string> tempCycleLevelSet;
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		//�����ȡÿ��������Ŀ
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"cycleTaskReward"))
		{	
			attrPtr = secondNode->properties;
			xmlChar *_itemLevel = xmlGetProp(secondNode, (const xmlChar *)"level");
			int cycleLevel = atoi((char*)_itemLevel);
			xmlFree(_itemLevel);
			vector<double> factor;
			factor.clear();
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardFactor")) {
							//ÿ���������
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardFactor");
							rewardFactor = atof((char*)_item);
							xmlFree(_item);
							factor.push_back(rewardFactor);
						}
					}
				}
			}
			
			cycleTaskRewardFactor.insert(pair<int, vector<double> >(cycleLevel, factor));
		}
	}
	cout<<"BisonTest: @read_cycle_task_reward.cpp end: "<<endl;
	xmlFreeDoc(doc);
	return 0;
}