/****************************************************************
 * Filename: read_internal_forces.cpp
 * 
 * Description: ��������ϵͳ��ֵ�Ķ�ȡ
 *
 * Original Author : bison, 2012-6-13
 *
 ****************************************************************/
 
#include"internal_forces.h"
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<sstream>
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

map<string, InForsDat_T> party_2_inForsDat;

int read_internal_forces(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ

	int valueIndex;
	int totalIndex;
	int levelIndex;
	char party[10] = {0};

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
		//�����ȡ�ȼ��ڵ�
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"InternalForce"))
		{
			InForsDat_T tempIFD;
			int vipIndex = 0;
			int needGoldIndex = 0;
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"party"))
				{	
					//��ȡ����
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"party");
					strncpy(tempIFD.party, (char*)_item, sizeof tempIFD.party);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"perTimeNeedInner"))
				{
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					tempIFD.perTimeNeedInner = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"useInnerTimeLmt"))
				{
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					tempIFD.useInnerTimeLmt = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"useInnerGetExp"))
				{
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					tempIFD.useInnerGetExp = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"useGlodGetExp"))
				{
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					tempIFD.useGlodGetExp = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"luckRate"))
				{
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					tempIFD.luckRate = atof((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"luckTimes"))
				{
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					tempIFD.luckTimes = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"useGlodGetExp"))
				{
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					tempIFD.useGlodGetExp = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrncmp(attrPtr->name, (const xmlChar*)"vip", 3))
				{
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					tempIFD.vipUseGoldTimeLmt[vipIndex++] = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrncmp(attrPtr->name, (const xmlChar*)"needGoldTimes", 13))
				{
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					tempIFD.thisTimeNeedGold[needGoldIndex++] = atoi((char*)_item);
					xmlFree(_item);
				}  
			}
			
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Item"))
				{
					levelIndex = 0;
					valueIndex = 0;
					totalIndex = 0;
					InForsLvlAdd_T lvlAdd;
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"level"))
						{
							//���ȼ�
							xmlChar *_item = xmlGetProp(thirdNode, attrPtr->name);
							levelIndex = atoi((char*)_item);
							xmlFree(_item);
							if (levelIndex > MAX_INTERNAL_FORCES_LEVEL || levelIndex < 0)
							{
								cout<<"The internal_forces config's lesson is error"<<endl;
								return -1;
							}
							lvlAdd.level = levelIndex;
							
						} else if (!xmlStrncmp(attrPtr->name, (const xmlChar*)"add", 3))
						{
							//������
							xmlChar *_item = xmlGetProp(thirdNode, attrPtr->name);
							lvlAdd.value[valueIndex++] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrncmp(attrPtr->name, (const xmlChar*)"total", 5))
						{
							//��������
							xmlChar *_item = xmlGetProp(thirdNode, attrPtr->name);
							lvlAdd.total[totalIndex++] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needInner"))
						{
							xmlChar *_item = xmlGetProp(thirdNode, attrPtr->name);
							lvlAdd.needIF = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"upgradeNeedExp"))
						{
							xmlChar *_item = xmlGetProp(thirdNode, attrPtr->name);
							lvlAdd.upgradeNeedExp = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"canUseGold"))
						{
							xmlChar *_item = xmlGetProp(thirdNode, attrPtr->name);
							lvlAdd.canUseGold = atoi((char*)_item);
							xmlFree(_item);
						}
					}
					tempIFD.level_2_nomalAdd.insert(pair<int, InForsLvlAdd_T>(levelIndex, lvlAdd));
				}
			}
			
			party_2_inForsDat.insert(pair<string, InForsDat_T>(tempIFD.party, tempIFD));
		}
	}
	xmlFreeDoc(doc);
	
	
	//����
	if (party_2_inForsDat.find("M") == party_2_inForsDat.end())
	{
		cout<<"Init Party-M's internalForces error!!!"<<endl;
	}
	if (party_2_inForsDat.find("H") == party_2_inForsDat.end())
	{
		cout<<"Init Party-H's internalForces error!!!"<<endl;
	}
	if (party_2_inForsDat.find("X") == party_2_inForsDat.end())
	{
		cout<<"Init Party-X's internalForces error!!!"<<endl;
	}
	if (party_2_inForsDat.find("G") == party_2_inForsDat.end())
	{
		cout<<"Init Party-G's internalForces error!!!"<<endl;
	}
	return 0;
}