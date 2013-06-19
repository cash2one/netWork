
/********************************************************************

    created:	2012/9/05  15:24
	
	�ļ�����	read_inner_active_code.cpp

    author:     ChenZhen 

    purpose:  	������ȡ�ڲ��������ļ�����ʽΪxml)
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
using namespace std;

extern set<AvtiveCode> innerActiveCodeMap;

int read_inner_active_code(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	string codeId;	
	string goodsId;
	set<AvtiveCode>::iterator code_it;
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
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"order"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*��Ʒ����id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goodsId"))
				{
					xmlChar *_goodsId=xmlGetProp(propNodePtr_item,(const xmlChar*)"goodsId");
					goodsId = const_cast<char *>(reinterpret_cast<const char *>(_goodsId));					
					xmlFree(_goodsId);
				}					
				attrPtr = attrPtr->next;	
			}
		}
		else if(!xmlStrcmp(curNode->name,(const xmlChar *)"item"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*������id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"code"))
				{
					xmlChar *_code=xmlGetProp(propNodePtr_item,(const xmlChar*)"code");
					codeId = const_cast<char *>(reinterpret_cast<const char *>(_code));					
					xmlFree(_code);
					
					if(goodsId.size() > 1 && codeId.size() > 1)
					{
						AvtiveCode newActiveCode(const_cast<char*>\
						(codeId.c_str()),const_cast<char*>\
						(goodsId.c_str()));
						
						code_it = innerActiveCodeMap.find(newActiveCode);
						
						if(code_it == innerActiveCodeMap.end())
						{
							innerActiveCodeMap.insert(newActiveCode);
						}
					}
				}					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
}

