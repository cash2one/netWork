/****************************************************************
 * Filename: read_global.cpp
 * 
 * Description: ȫ��
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

int normalHeroSpeed;
int normalPetSpeed;
int normalMonsterSpeed;
int normalWagonSpeed;

int read_global(char *fileName)
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

	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		//�����ȡ�ȼ��ڵ�
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"speed"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"normalHeroSpeed"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"normalHeroSpeed");
					normalHeroSpeed = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"normalPetSpeed"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"normalPetSpeed");
					normalPetSpeed = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"normalMonsterSpeed"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"normalMonsterSpeed");
					normalMonsterSpeed = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"normalWagonSpeed"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"normalWagonSpeed");
					normalWagonSpeed = atoi((char*)_item);
					xmlFree(_item);
				}
			}
			
		}
	}
	xmlFreeDoc(doc);
	
	
	//����
	cout<<"normal Hero speed is "<<normalHeroSpeed<<endl;
	cout<<"normal monster speed is "<<normalMonsterSpeed<<endl;
	cout<<"normal pet speed is "<<normalPetSpeed<<endl;
	cout<<"normal wagon speed is "<<normalWagonSpeed<<endl;
	return 0;
}