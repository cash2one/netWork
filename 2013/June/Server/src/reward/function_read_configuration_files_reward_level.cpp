#include"function_read_configuration_files.h"
#include "data_structure_struct.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern LevelRewardData levelRewardData[10];
int read_files_reward_level(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ

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
	
	int i=0;
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"reward"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"level"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"level");
					levelRewardData[i].level=atoi((char*)cTem);
					xmlFree(cTem);
					// cout<<"level:"<<levelRewardData[i].level<<endl;
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"repeat"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"repeat");
					levelRewardData[i].repeat = atoi((char*)cTem);
					xmlFree(cTem);
					// cout<<"repeat:"<<levelRewardData[i].repeat<<endl;
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"number"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"number");
					levelRewardData[i].number = atoi((char*)cTem);
					xmlFree(cTem);
					// cout<<"number:"<<levelRewardData[i].number<<endl;
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"goodsid"))
				{	
					memset(levelRewardData[i].goodsid,0,sizeof(levelRewardData[i].goodsid));
					cTem = xmlGetProp(secondNode, (const xmlChar*)"goodsid");
					strncpy(levelRewardData[i].goodsid, (char*)cTem, sizeof (levelRewardData[i].goodsid));
					xmlFree(cTem);
					// cout<<"goodsid:"<<levelRewardData[i].goodsid<<endl;
				}	
			}
			i++;
		}
	}
		
	xmlFreeDoc(doc);
	return 0;
}
