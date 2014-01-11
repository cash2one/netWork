/************************************************************
	�ļ�����read_party_base_camp.cpp
	�ļ����ã���ȡ�������������ļ�
	���ߣ�chenzhen
	�������ڣ�2012.12.14
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"partyBaseCampLimit.h"
#include"cpyAsist.h"
extern map<string,PartyBaseCampLimit*> mapIdToCampRomLimit;
extern map<int,string> levelToMapId;
int read_party_base_camp(char *fileName)     
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
	string campLimitId;        //����id
	string campMapId;          //����mapid
	int num;               //������Ҫ������
	int partyLevel;              //������Ҫ����ɵȼ�
	int room;                 	//������
	int flgCampLimit;         //��־����
	
	flgCampLimit = -1;
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"partyBaseCamp"))
		{
			propNodePtr_Limit = curNode;
			xmlAttrPtr attrPtr = propNodePtr_Limit->properties;
			
			while(attrPtr!=NULL)
			{	
				/*��ȡcampLimitId����*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"campLimitId"))
				{					
					xmlChar *_campLimitId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"campLimitId");
					campLimitId = reinterpret_cast<const char *>(_campLimitId);
					xmlFree(_campLimitId);
				}
				
				/*��ȡcampMapId����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"campMapId"))
				{					
					xmlChar *_campMapId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"campMapId");
					campMapId = reinterpret_cast<const char *>(_campMapId);
					xmlFree(_campMapId);
				}
				/*��ȡnum����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"num"))
				{					
					xmlChar *_num = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"num");
					num = atoi(reinterpret_cast<const char *>(_num));
					xmlFree(_num);
				}
				
				/*��ȡpartyLevel����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"partyLevel"))
				{					
					xmlChar *_partyLevel = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"partyLevel");
					partyLevel = atoi(reinterpret_cast<const char *>(_partyLevel));
					xmlFree(_partyLevel);
	
				}
				
				/*��ȡroom����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"room"))
				{					
					xmlChar *_room = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"room");
					room = atoi(reinterpret_cast<const char *>(_room));
					xmlFree(_room);
					flgCampLimit = 1;
				}
				
				/*ʵ����PartyBaseCampLimit��*/
				if(flgCampLimit == 1)
				{
					room = 100;
					PartyBaseCampLimit *newPartyBaseCampLimit = new PartyBaseCampLimit(const_cast<char *>(campLimitId.c_str()),const_cast<char *>\
					(campMapId.c_str()),num,partyLevel,room);
					
					mapIdToCampRomLimit[campMapId] = newPartyBaseCampLimit;
					newPartyBaseCampLimit->setMapCampRoom();
					flgCampLimit = 0;
					insertLevelCampMap(partyLevel,campMapId);
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	insertHightestLevelCampMap();
	testPrintLevelCampMap();
	xmlFreeDoc(doc);
	return 0;
}
	
	
