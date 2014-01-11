/************************************************************
	�ļ�����read_cpyLimit.cpp
	�ļ����ã���ȡ�����������Ƶ������ļ�
	���ߣ�chenzhen
	�������ڣ�2012.06.11
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"cpyLimit.h"
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
int read_files_cpyLimit(char *fileName)  //��ȡ����������     
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;     //xml�м�ڵ���ʱ����
	
	char szDocName[50]={0};
	strcpy(szDocName,fileName);
	doc = xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	
	if(NULL == doc)
	{
		return -1;
	}
	//�õ�xml�ļ���root
	curNode = xmlDocGetRootElement(doc);		
	if(NULL == curNode)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	curNode=curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_Limit;
	string cpyLimitId;        //��������id
	string cpyId;             //����id
	int num;                  //��������Ҫ������
	int rank;                 //��������Ҫ��ȼ�
	int room;                 //����������
	int flgLimit;             //��־����
	double jdgGolRat;         //�������ϵ��
	int jugTme;               //��������ʱ��
	int baseGole = 20;             //ͨ�ػ�����
	string name;              //����
	size_t costFatigue = 5;       //����ֵ
	flgLimit = -1;
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"cpyLimit"))
		{
			propNodePtr_Limit = curNode;
			xmlAttrPtr attrPtr = propNodePtr_Limit->properties;
			
			while(attrPtr!=NULL)
			{	
				/*��ȡcpyLimitId����*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyLimitId"))
				{					
					xmlChar *_cpyLimitId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"cpyLimitId");
					cpyLimitId = reinterpret_cast<const char *>(_cpyLimitId);
					xmlFree(_cpyLimitId);
				}
				
				/*��ȡcpyId����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyId"))
				{					
					xmlChar *_cpyId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"cpyId");
					cpyId = reinterpret_cast<const char *>(_cpyId);
					xmlFree(_cpyId);
				}
				/*��ȡjugTme����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"jugTme"))
				{					
					xmlChar *_jugTme = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"jugTme");
					jugTme = atoi(reinterpret_cast<const char *>(_jugTme));
					xmlFree(_jugTme);
				}
				/*��ȡbaseGole����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"baseGole"))
				{					
					xmlChar *_baseGole = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"baseGole");
					baseGole = atoi(reinterpret_cast<const char *>(_baseGole));
					xmlFree(_baseGole);
				}
				/*��ȡjdgGolRat����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"jdgGolRat"))
				{					
					xmlChar *_jdgGolRat = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"jdgGolRat");
					jdgGolRat = atof(reinterpret_cast<const char *>(_jdgGolRat));
					xmlFree(_jdgGolRat);
				}
				/*��ȡnum����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"num"))
				{					
					xmlChar *_num = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"num");
					num = atoi(reinterpret_cast<const char *>(_num));
					xmlFree(_num);
				}
				
				/*��ȡrank����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"rank"))
				{					
					xmlChar *_rank = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"rank");
					rank = atoi(reinterpret_cast<const char *>(_rank));
					xmlFree(_rank);
				}
				
				/*��ȡname����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{					
					xmlChar *_name = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"name");
					name = reinterpret_cast<const char *>(_name);
					xmlFree(_name);
				}
				/*��ȡcostFatigue����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"costFatigue"))
				{					
					xmlChar *_costFatigue = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"costFatigue");
					costFatigue = atoi(reinterpret_cast<const char *>(_costFatigue));
					xmlFree(_costFatigue);
				}
				
				/*��ȡroom����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"room"))
				{					
					xmlChar *_room = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"room");
					room = atoi(reinterpret_cast<const char *>(_room));
					xmlFree(_room);
					flgLimit = 1;
				}
				
				/*ʵ����CpyLimit��*/
				if(flgLimit == 1)
				{
					room = 20;
					CpyLimit *newCpyLimit = new CpyLimit(const_cast<char *>(cpyLimitId.c_str()),\
					const_cast<char *>(cpyId.c_str()),const_cast<char*>(name.c_str()),\
					baseGole,jugTme,jdgGolRat,num,rank,costFatigue,room);
					
					cpyId_to_cpyLimit[cpyId] = newCpyLimit;
					flgLimit = 0;
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
	
	
