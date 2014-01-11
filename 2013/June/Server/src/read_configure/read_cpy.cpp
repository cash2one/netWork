/************************************************************
	�ļ�����read_cpyLimit.cpp
	�ļ����ã���ȡ�����������Ƶ������ļ�
	���ߣ�chenzhen
	�������ڣ�2012.03.11
************************************************************/
/************************************************************
		�޸ı�ע
	�޸��ߣ�chenzhen
	�޸����ڣ�2012.06.11
	�޸����ݣ����ݸ�����������������������,���ע��
************************************************************/

#include"function_read_configuration_files.h"
#include"cpy.h"
#include"cpyLimit.h"
#include"map_inform.h"
#include<libxml/parser.h>
#include"command_other_function_all_over.h"
#include"cpyManager.h"

/*������ӵ�ȫ�ֱ�������Ϊ����id��ֵΪ��������ʵ��ָ�룬add chenzhen 2012.06.11*/
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern CpyManger *cpyManger;
int read_files_cpy(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;    //xml�ڵ����͵���ʱ����
	
	char szDocName[50]={0};
	
	strcpy(szDocName,fileName);	
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
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
	curNode=curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_cpy;		
	while(curNode!=NULL)
	{
		string MapId;         //������ͼid����ʱ����
		string cpyId;        //����id
		string cpyLimitId;   //��������id
		int mapSum;          //������ͼ��Ŀ
		list<string> cpyMapSet;   //װ������ͼid
		int room;            //����������
		int flgCpy;          //��־��ʱ����
		flgCpy = -1;
		map<string,CpyLimit*>::iterator cpyLimit_it;  //������
		
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"cpy"))
		{
		
			propNodePtr_cpy=curNode;
			xmlAttrPtr attrPtr=propNodePtr_cpy->properties;
			
			while(attrPtr!=NULL)
			{	
				/*��ȡ����id */
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyId"))
				{
					xmlChar *_cpyId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"cpyId");
					cpyId = reinterpret_cast<const char *>(_cpyId);					
					xmlFree(_cpyId);						
				}
				
				/*��ȡ��������id*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyLimitId"))
				{
					xmlChar *_cpyLimitId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"cpyLimitId");
					cpyLimitId = reinterpret_cast<const char *>(_cpyLimitId);					
					xmlFree(_cpyLimitId);						
				}				
				
				/*��ȡ������ͼid*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"MapId1"))
				{
					xmlChar *_MapId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"MapId1");
					MapId = reinterpret_cast<const char *>(_MapId);					
					xmlFree(_MapId);
					cpyMapSet.push_back(MapId);
				}	
				
				/*��ȡ������ͼid*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"MapId2"))
				{
					xmlChar *_MapId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"MapId2");
					MapId = reinterpret_cast<const char *>(_MapId);					
					xmlFree(_MapId);
					cpyMapSet.push_back(MapId);
				}
				
				/*��ȡ������ͼid*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"MapId3"))
				{
					xmlChar *_MapId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"MapId3");
					MapId = reinterpret_cast<const char *>(_MapId);					
					xmlFree(_MapId);
					cpyMapSet.push_back(MapId);
				}	
				
				/*��ȡ������ͼid*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"MapId4"))
				{
					xmlChar *_MapId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"MapId4");
					MapId = reinterpret_cast<const char *>(_MapId);					
					xmlFree(_MapId);
					cpyMapSet.push_back(MapId);
				}
				
				/*��ȡ������ͼid*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"MapId5"))
				{
					xmlChar *_MapId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"MapId5");
					MapId = reinterpret_cast<const char *>(_MapId);					
					xmlFree(_MapId);
					cpyMapSet.push_back(MapId);
				}	
				
				/*��ȡmapSum����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapSum"))
				{					
					xmlChar *_mapSum = xmlGetProp(propNodePtr_cpy,(const xmlChar*)"mapSum");
					mapSum = atoi(reinterpret_cast<const char *>(_mapSum));
					xmlFree(_mapSum);
					flgCpy = 1;
				}
				attrPtr=attrPtr->next;	
				
				/*���ɸ�������*/			
				if(flgCpy == 1 && cpyMapSet.size() == mapSum)
				{
					cpyLimit_it = cpyId_to_cpyLimit.find(cpyId);
					if(cpyLimit_it == cpyId_to_cpyLimit.end())
					{
						cout<<"the config cpyId.xml is error :"<<cpyId<<endl;
						exit(1);
					}
					room = cpyLimit_it->second->getRoom();
					int i;					
					for(i = 0;i < room;i++)
					{							
						char initCpyId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};        //����ʵ��id��������id����׷����ˮ��
						strncpy(initCpyId,cpyId.c_str(),strlen(cpyId.c_str()));
						strncat(initCpyId,"_",strlen("_"));
						appendNum(initCpyId,i,4);	//�����ռ��λ					
						Cpy *newCpy = new Cpy(initCpyId,cpyMapSet,cpyLimit_it->second);
						cpyLimit_it->second->PushCpy(newCpy);
					}
					flgCpy = 0;
				}				
			}	
		}
		curNode=curNode->next;
	}
	
	xmlFreeDoc(doc);
	return 0;
}
