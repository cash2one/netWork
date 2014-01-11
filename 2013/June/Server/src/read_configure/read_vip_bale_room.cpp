/************************************************************
	�ļ�����read_vip_bale_room.cpp
	�ļ����ã���ȡvip�������������ļ�
	���ߣ�chenzhen
	�������ڣ�2012.12.14
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"vipBaleRoomLimit.h"
extern map<string,VipBaleRoomLimit*> mapIdToVipBaleRomLimit;
int read_files_vipBaleRomLimit(char *fileName)  //��ȡVIP������     
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
	string vipLimitId;        //vip����id
	string vipMapId;          //vip����mapid
	int num;                  //��vip������Ҫ������
	int vipRank;              //��vip������Ҫ��vip�ȼ�
	int room;                 //����������
	int flgVipLimit;             //��־����
	
	flgVipLimit = -1;
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"vipBaleLimit"))
		{
			propNodePtr_Limit = curNode;
			xmlAttrPtr attrPtr = propNodePtr_Limit->properties;
			
			while(attrPtr!=NULL)
			{	
				/*��ȡvipLimitId����*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"vipLimitId"))
				{					
					xmlChar *_vipLimitId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"vipLimitId");
					vipLimitId = reinterpret_cast<const char *>(_vipLimitId);
					xmlFree(_vipLimitId);
				}
				
				/*��ȡvipMapId����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"vipMapId"))
				{					
					xmlChar *_vipMapId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"vipMapId");
					vipMapId = reinterpret_cast<const char *>(_vipMapId);
					xmlFree(_vipMapId);
				}
				/*��ȡnum����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"num"))
				{					
					xmlChar *_num = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"num");
					num = atoi(reinterpret_cast<const char *>(_num));
					xmlFree(_num);
				}
				
				/*��ȡvipRank����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"vipRank"))
				{					
					xmlChar *_vipRank = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"vipRank");
					vipRank = atoi(reinterpret_cast<const char *>(_vipRank));
					xmlFree(_vipRank);
				}
				
				/*��ȡroom����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"room"))
				{					
					xmlChar *_room = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"room");
					room = atoi(reinterpret_cast<const char *>(_room));
					xmlFree(_room);
					flgVipLimit = 1;
				}
				
				/*ʵ����CpyLimit��*/
				if(flgVipLimit == 1)
				{
					room = 500;
					VipBaleRoomLimit *newVipBaleRoomLimit = new VipBaleRoomLimit(\
					const_cast<char *>(vipLimitId.c_str()),const_cast<char *>\
					(vipMapId.c_str()),num,vipRank,room);
					mapIdToVipBaleRomLimit[vipMapId] = newVipBaleRoomLimit;
					newVipBaleRoomLimit->setMapVipRoom();
					flgVipLimit = 0;
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
	
	
