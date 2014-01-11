#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<map>
#include<iostream>

using namespace::std;
int read_files_illegality_word(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	//��ȡequip�����ļ�
	xmlKeepBlanksDefault(0);
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		return -1;
	}
	//�õ�xml�ļ���root
	curnow=xmlDocGetRootElement(doc);
	if(NULL==curnow)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	//xml����ر���
	char  chatStr[7925];
	char  nameStr[581];
	while(curnow!=NULL)
	{	
		
		curNode = curnow->xmlChildrenNode;
			if(NULL==curNode)
			{
				xmlFreeDoc(doc);
				return -3;
			}	 
			  
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"chat"))
			{
					cTem= xmlNodeGetContent(curNode);
					strcpy(chatStr,(char *)cTem);
					//chatStr=(char *)cTem;
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					strcpy(nameStr,(char *)cTem);
					//nameStr=(char *)cTem;
					xmlFree(cTem);
				}
				
				curNode=curNode->next;
			
	}
	cout<<strlen(chatStr)<<endl;
	cout<<strlen(nameStr)<<endl;
	xmlFreeDoc(doc);
	return 0;
}
