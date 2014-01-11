/****************************************************************
 * Filename: read_merid_conf.cpp
 * 
 * Description: ��ȡ���ﾭ������
 *
 * Original Author : bison, 2012-1-18
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "meridian.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

MeridConf_T heroMeridConf;						//���ﾭ������

int read_merid_conf(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ
	int merid = 0;							//������
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Meridian"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"startLevel")) {
					//������ʼ�����ȼ�
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"startLevel");
					heroMeridConf.startLevel = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needBoundGoldPerFiveMin")) {
					//����5���Ӿ�������ʱ����Ҫ��Ԫ����
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"needBoundGoldPerFiveMin");
					heroMeridConf.needBoundGoldPerFiveMin = atoi((char*)_item);
					xmlFree(_item);
				}
			}
			
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//��ȡ������Ŀ
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"merid")) {
							//��������
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"merid");
							merid = atoi((char*)_item);
							xmlFree(_item);
							if (merid < 0 || merid > 7)
							{
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								cout<<"the config of meridian conf is error its range is(0~7)but it is"<<merid<<endl;
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								return -1;
							}
						}
					}
					
					for (forthNode = thirdNode->xmlChildrenNode; forthNode != NULL; forthNode = forthNode->next)
					{
						//��ȡ������Ŀ
						if (!xmlStrcmp(forthNode->name, (const xmlChar*)"level"))
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lvl")) 
								{
									//��������
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"lvl");
									level = atoi((char*)_item);
									xmlFree(_item);
									if (level < 0 || level > 90)
									{
										cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
										cout<<"the config of meridian config is error level(0~90)but it is"<<level<<endl;
										cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
										return -1;
									}
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needHeroLevel")) {
									//ѧϰ�õȼ�������Ҫ�Ľ�ɫ�ȼ�
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"needHeroLevel");
									heroMeridConf.item[merid].needHeroLevel[level] = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"time")) {
									//ѧϰ�õȼ�������Ҫ��ʱ��
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"time");
									heroMeridConf.item[merid].time[level] = atoi((char*)_item);
									// cout<<"merid is "<<merid<<"level is "<<level<<" and time is:"<<heroMeridConf.item[merid].time[level]<<endl;
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"incType1")) {
									//ѧϰ��������������������1
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"incType1");
									heroMeridConf.item[merid].incType1[level] = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"incVal1")) {
									//ѧϰ����������������ֵ1
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"incVal1");
									heroMeridConf.item[merid].incVal1[level] = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"incTotalVal1")) {
									//ѧϰ����������������ֵ1����ֵ
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"incTotalVal1");
									heroMeridConf.item[merid].incTotalVal1[level] = atoi((char*)_item);
									xmlFree(_item);
								}else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"incType2")) {
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"incType2");
									heroMeridConf.item[merid].incType2[level] = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"incVal2")) {
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"incVal2");
									heroMeridConf.item[merid].incVal2[level] = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"incTotalVal2")) {
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"incTotalVal2");
									heroMeridConf.item[merid].incTotalVal2[level] = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						}
					}
				}
			}
		}
	}
	
	cout<<"[BisonShow]@read_merid_conf.cpp"<<endl;
	xmlFreeDoc(doc);
	return 0;
}
