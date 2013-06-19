/****************************************************************
 * Filename: read_five_elem_conf.cpp
 * 
 * Description: ��ȡ��������
 *
 * Original Author : bison, 2012-1-18
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "five_elements.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

FiveElemConf_T heroFiveElemConf;				//������������

int read_five_elem_conf(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ
	int elem;							//������
	int level = 0;
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"FiveElem"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"startLevel")) {
					//���п�ʼ������Ҫ����ҵȼ�
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"startLevel");
					heroFiveElemConf.startLevel = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"changeNeedGold")) {
					//����������Ҫ��Ԫ��
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"changeNeedGold");
					heroFiveElemConf.changeNeedGold = atoi((char*)_item);
					xmlFree(_item);
				}
			}
			
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//��ȡ���п���ϵ��
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"Elem")) {
							//���ܵȼ�
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"Elem");
							elem = atoi((char*)_item);
							xmlFree(_item);
							if (elem < 1 || elem > 6)
							{
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								cout<<"the config of fiveElem conf is error"<<endl;
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								return -1;
							}
							elem -= 1;
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defGoldFactor")) {
							//���������ԶԽ�Ŀ���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defGoldFactor");
							heroFiveElemConf.defFactor[elem][0] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defWoodFactor")) {
							//���������Զ�ľ�Ŀ���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defWoodFactor");
							heroFiveElemConf.defFactor[elem][1] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defEarthFactor")) {
							//���������Զ����Ŀ���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defEarthFactor");
							heroFiveElemConf.defFactor[elem][2] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defWaterFactor")) {
							//���������Զ�ˮ�Ŀ���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defWaterFactor");
							heroFiveElemConf.defFactor[elem][3] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defFireFactor")) {
							//���������ԶԻ�Ŀ���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defFireFactor");
							heroFiveElemConf.defFactor[elem][4] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defNoElemFactor")) {
							//���������Զ��޵Ŀ���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defNoElemFactor");
							heroFiveElemConf.defFactor[elem][5] = atof((char*)_item);
							xmlFree(_item);
						}
					}
					// cout<<endl;
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"level"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lvl")) {
							//���еȼ�
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"lvl");
							level = atoi((char*)_item);
							xmlFree(_item);
							if (level < 0 || level > 100)
							{
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								cout<<"the config of fiveElem conf is error"<<endl;
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								return -1;
							}
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needHeroLevel")) {
							//���еȼ���Ҫ����ҵȼ�
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"needHeroLevel");
							heroFiveElemConf.needHeroLevel[level] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"upgradeNeedExp")) {
							//������һ����Ҫ�ľ���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"upgradeNeedExp");
							heroFiveElemConf.upgradeNeedExp[level] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"fiveValue")) {
							//�õȼ�����������
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"fiveValue");
							heroFiveElemConf.fiveValue[level] = atoi((char*)_item);
							xmlFree(_item);
						}
					}
					// cout<<endl;
				}
			}
			
		}
	}
	
	cout<<"[BisonShow]@read_five_elem_conf.cpp"<<endl;
	xmlFreeDoc(doc);
	return 0;
}
