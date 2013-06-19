
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
#include"bottle.h"
using namespace std;

extern map<string,Bottle*> bottleConfMap;

int read_bottle(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
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
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"item"))
		{
			int flgItem = 0;
			string typeId;
			string name;
			string photoId;
			string goodsId;
			string dropStage;
			int lifeVal;
			int hurt;
			int brushStyle = 0;
			double bloodPre = 0.2;
			double magicPre = 0.2;
			Bottle *newBottle = NULL;
			int dropNum = 0;
			
	
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*ȡ��ƿ�޵�����id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
					xmlChar *_typeId=xmlGetProp(propNodePtr_item,(const xmlChar*)"typeId");
					typeId = const_cast<char *>(reinterpret_cast<const char *>(_typeId));					
					xmlFree(_typeId);
				}
				/*ȡ��ƿ�޵�����ֵ*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lifeVal"))
				{
					xmlChar *_lifeVal=xmlGetProp(propNodePtr_item,(const xmlChar*)"lifeVal");
					lifeVal = atoi(reinterpret_cast<const char *>(_lifeVal));					
					xmlFree(_lifeVal);
				}
				
				/*ȡ��ƿ�޵��˺�ֵ*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hurt"))
				{
					xmlChar *_hurt=xmlGetProp(propNodePtr_item,(const xmlChar*)"hurt");
					hurt = atoi(reinterpret_cast<const char *>(_hurt));					
					xmlFree(_hurt);
				}
				/*ȡ��ƿ�޵�ˢ��ģʽ*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"brushStyle"))
				{
					xmlChar *_brushStyle=xmlGetProp(propNodePtr_item,(const xmlChar*)"brushStyle");
					brushStyle = atoi(reinterpret_cast<const char *>(_brushStyle));					
					xmlFree(_brushStyle);
				}
				/*ȡ��ƿ�޵Ļ�Ѫ�ٷֱ�*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"bloodPre"))
				{
					xmlChar *_bloodPre=xmlGetProp(propNodePtr_item,(const xmlChar*)"bloodPre");
					bloodPre = atof(reinterpret_cast<const char *>(_bloodPre));					
					xmlFree(_bloodPre);
				}
				/*ȡ��ƿ�޵Ļ����ٷֱ�*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"magicPre"))
				{
					xmlChar *_magicPre=xmlGetProp(propNodePtr_item,(const xmlChar*)"magicPre");
					magicPre = atof(reinterpret_cast<const char *>(_magicPre));					
					xmlFree(_magicPre);
				}
				/*��ȡƿ�޵�����*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{
					xmlChar *_name=xmlGetProp(propNodePtr_item,(const xmlChar*)"name");
					
					name = const_cast<char *>(reinterpret_cast<const char *>(_name));
					
					xmlFree(_name);
				}
				
				/*��ȡƿ�޵�������*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dropNum"))
				{
					xmlChar *_dropNum=xmlGetProp(propNodePtr_item,(const xmlChar*)"dropNum");
					
					dropNum = atof(reinterpret_cast<const char *>(_dropNum));		
					
					xmlFree(_dropNum);
				}
				
				/*��ȡƿ�޵���׶�*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dropStage"))
				{
					xmlChar *_dropStage=xmlGetProp(propNodePtr_item,(const xmlChar*)"dropStage");
					
					dropStage = const_cast<char *>(reinterpret_cast<const char *>(_dropStage));
					
					xmlFree(_dropStage);
				}
				
				/*��ȡƿ�޵�ͼƬid*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"photoId"))
				{
					xmlChar *_photoId=xmlGetProp(propNodePtr_item,(const xmlChar*)"photoId");
					
					photoId = const_cast<char *>(reinterpret_cast<const char *>(_photoId));
					
					xmlFree(_photoId);
					flgItem = 1;
				}
				
				/*ʵ����ƿ�޵�ͼƬid*/	
				if(flgItem == 1)
				{
					newBottle = new Bottle(const_cast<char*>(typeId.c_str()),\
					lifeVal,hurt,brushStyle,bloodPre,magicPre,const_cast<char*>(name.c_str()),\
					dropNum,const_cast<char*>(dropStage.c_str()),const_cast<char*>(photoId.c_str()));
					
					bottleConfMap[typeId] = newBottle;
					flgItem = 0;
				}		
					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}

