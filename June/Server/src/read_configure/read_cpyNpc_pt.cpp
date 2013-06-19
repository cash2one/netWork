/************************************************************
	�ļ�����read_cpyNpc_pt.cpp
	�ļ����ã���ȡ����npc��������Ϣ
	���ߣ�chenzhen
	�������ڣ�2012.12.29
************************************************************/
#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<libxml/parser.h>

/*������ͨ����npc���͵�*/
extern Point JLGENPT;

/*������ͨ����npc���͵�*/
extern Point KFGENPT;

/*������ɸ���npc���͵�*/
extern Point KFPARPT;

/*������ɸ���npc���͵�*/
extern Point JLPARPT;

/*��ɫ����ɸ���npc���͵���پ�����ܴ���*/
extern int LIMPRTRAG;

/*��ɫ����ͨ����npc���͵���پ�����ܴ���*/
extern int LIMGENRAG;

int read_Npc_cpy_pt(char *fileName)
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
	xmlNodePtr propNodePtr_npc;		
	while(curNode!=NULL)
	{
		string mapId;         //��npc��ͼid
		Point piexPt;         //��npc�����ص�����
		int cpyType;             //��npc�ƹܵĸ�������
		int range;            //������ͼ��Ŀ
		
		int npcFlg = -1;
	
		
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"NpcPt"))
		{		
			propNodePtr_npc=curNode;
			xmlAttrPtr attrPtr=propNodePtr_npc->properties;
			
			while(attrPtr!=NULL)
			{	
				/*��ȡ��ͼid */
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId"))
				{
					xmlChar *_mapId=xmlGetProp(propNodePtr_npc,(const xmlChar*)"mapId");
					mapId = reinterpret_cast<const char *>(_mapId);					
					xmlFree(_mapId);						
				}
				
				/*�ƹܸ�������*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyType"))
				{
					xmlChar *_cpyType=xmlGetProp(propNodePtr_npc,(const xmlChar*)"cpyType");			
					cpyType = atoi(reinterpret_cast<const char *>(_cpyType));				
					xmlFree(_cpyType);						
				}				
				
				/*��ȡnpc�ĺ�����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x"))
				{
					xmlChar *x=xmlGetProp(propNodePtr_npc,(const xmlChar*)"x");
					piexPt._x = atoi(reinterpret_cast<const char *>(x));			
					xmlFree(x);					
				}	
				/*��ȡnpc��������*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y"))
				{
					xmlChar *y=xmlGetProp(propNodePtr_npc,(const xmlChar*)"y");
					piexPt._y = atoi(reinterpret_cast<const char *>(y));			
					xmlFree(y);					
				}	
				/*��ȡnpc���ƹܾ���*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"range"))
				{
					xmlChar *_range=xmlGetProp(propNodePtr_npc,(const xmlChar*)"range");
					range = atoi(reinterpret_cast<const char *>(_range));			
					xmlFree(_range);	
					npcFlg = 1;
				}
				
				attrPtr=attrPtr->next;
				
				if(npcFlg == 1)
				{
					if(mapId.compare("map_001") == 0)
					{
						if(cpyType == 1)
						{
							KFGENPT = piexPt;
							
							LIMGENRAG = range;
						}
						else
						{
							KFPARPT = piexPt;
							
							LIMPRTRAG = range;
						}						
					}
					
					else if(mapId.compare("map_010") == 0)
					{
						if(cpyType == 1)
						{
							JLGENPT = piexPt;
							
							LIMGENRAG = range;
						}
						else
						{
							JLPARPT = piexPt;
							
							LIMPRTRAG = range;
						}
							
					}
					npcFlg = 0;
				}					
			}	
		}
		curNode=curNode->next;
	}	
	xmlFreeDoc(doc);
	return 0;
}
