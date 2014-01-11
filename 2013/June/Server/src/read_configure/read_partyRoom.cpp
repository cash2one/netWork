/************************************************************
	�ļ�����read_partyRoom.cpp
	�ļ����ã���ȡ�������������ļ�
	���ߣ�chenzhen
	�������ڣ�2012.12.14
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"partyRoomLimit.h"
extern map<string,PartyRoomLimit*> mapIdToPartyRomLimit;
int read_files_partyRomLimit(char *fileName)     
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
	string partyLimitId;       
	string partyMapId;          
	int partyNum;                 
	int partyRank;              
	int room;                 
	int flgPartyLimit;           
	
	flgPartyLimit = -1;
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"partyLimit"))
		{
			propNodePtr_Limit = curNode;
			xmlAttrPtr attrPtr = propNodePtr_Limit->properties;
			
			while(attrPtr!=NULL)
			{	
				/*��ȡpartyLimitId����*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"partyLimitId"))
				{					
					xmlChar *_partyLimitId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"partyLimitId");
					partyLimitId = reinterpret_cast<const char *>(_partyLimitId);
					xmlFree(_partyLimitId);
				}
				
				/*��ȡpartyMapId����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"partyMapId"))
				{					
					xmlChar *_partyMapId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"partyMapId");
					partyMapId = reinterpret_cast<const char *>(_partyMapId);
					xmlFree(_partyMapId);
				}
				/*��ȡpartyNum����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"partyNum"))
				{					
					xmlChar *_partyNum = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"partyNum");
					partyNum = atoi(reinterpret_cast<const char *>(_partyNum));
					xmlFree(_partyNum);
				}
				
				/*��ȡpartyRank����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"partyRank"))
				{					
					xmlChar *_partyRank = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"partyRank");
					partyRank = atoi(reinterpret_cast<const char *>(_partyRank));
					xmlFree(_partyRank);
	
				}
				
				/*��ȡroom����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"room"))
				{					
					xmlChar *_room = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"room");
					room = atoi(reinterpret_cast<const char *>(_room));
					xmlFree(_room);
					flgPartyLimit = 1;
				}
				
				/*ʵ����partyRoomLimit��*/
				if(flgPartyLimit == 1)
				{
					room = 100;
					PartyRoomLimit *newPartyRoomLimit = new PartyRoomLimit(const_cast<char *>\
					(partyLimitId.c_str()),const_cast<char *>(partyMapId.c_str()),partyNum,\
					partyRank,room);
					
					mapIdToPartyRomLimit[partyMapId] = newPartyRoomLimit;
					newPartyRoomLimit->setMapPartyRoom();
					flgPartyLimit = 0;
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
	
	
