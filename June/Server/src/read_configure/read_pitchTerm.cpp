#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>

extern PitchTerm pitchTerm;
using namespace std;
extern map<string,PitchTerm *> mapIdToPitchTerm;
int read_pitchTerm(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	xmlChar *carrier;
	char szDocName[50]={0};
	
	string mapId;
	
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
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"pitch"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*ȡ��ƿ�޵�����id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"mapId");
					mapId = const_cast<char *>(reinterpret_cast<const char *>(carrier));						
					xmlFree(carrier);
				}
				/*ȡ��ƿ�޵�����ֵ*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x1"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"x1");
					pitchTerm.pt1._x =  atoi(reinterpret_cast<const char *>(carrier));		
					xmlFree(carrier);
				}
				
				/*ȡ��ƿ�޵��˺�ֵ*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y1"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"y1");
					pitchTerm.pt1._y = atoi(reinterpret_cast<const char *>(carrier));					
					xmlFree(carrier);
				}
				
				/*��ȡƿ�޵�����*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x2"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"x2");
					
					pitchTerm.pt2._x = atoi(reinterpret_cast<const char *>(carrier));	
	
					xmlFree(carrier);
				}
				
				/*��ȡƿ�޵�ͼƬid*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y2"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"y2");
					
					pitchTerm.pt2._y  = atoi(reinterpret_cast<const char *>(carrier));	
					
					xmlFree(carrier);
				}
				
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
/* 
	for(map<string,string>::iterator i=mapIdToGoodsId.begin();i!=mapIdToGoodsId.end();++i)
	{
		cout<<i->first<<endl;
		cout<<i->second<<endl;
	} */
	xmlFreeDoc(doc);
	return 0;
}