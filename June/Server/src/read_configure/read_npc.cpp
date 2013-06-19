
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>

#include"data_structure_struct.h"

using namespace std;

extern map<string , map <string ,Point > > npc; //npc����

int read_npc(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	xmlNodePtr curNext;
	char szDocName[50]={0};
	xmlChar *szKey;          //��ʱ�ַ�������
	
	Point point;
	string mapId;
	string typeId;
	map <string ,Point > idToNPC;   //��ͼ��NPC����
	strncpy(szDocName,fileName,strlen(fileName));
	
	
	//��ȡ��ͼ�����ļ�
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL == doc)
	{
		cout<<"failed in  32"<<endl;
		return -1;
	}
	
	//�õ�xml�ļ���root
	curNode=xmlDocGetRootElement(doc);
	if(NULL == curNode)
	{	cout<<"failed in  39"<<endl;
		xmlFreeDoc(doc);
		return -3;
	}
	
	//xml����ر���
	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_item;
	
	int flag=0;
	//ѭ����ȡxml���ӽڵ㣬��ȡ�����Ӧ������	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"map"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attr=propNodePtr_item->properties;
			if(!xmlStrcmp(attr->name,(const xmlChar*)"mapId"))
			{
				szKey=xmlGetProp(propNodePtr_item,(const xmlChar*)"mapId");
				mapId = const_cast<char *>(reinterpret_cast<const char *>(szKey));					
				xmlFree(szKey);
				//cout<<"typeId  is  :   "<<mapId<<endl;
			}
			curNext = curNode->xmlChildrenNode;
		
			while(curNext!=NULL)
			{
				propNodePtr_item = curNext;
				xmlAttrPtr attrPtr=propNodePtr_item->properties;
				while(attrPtr!=NULL)
				{			
					
					if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
					{
						
						szKey=xmlGetProp(propNodePtr_item,(const xmlChar*)"typeId");
						typeId = const_cast<char *>(reinterpret_cast<const char *>(szKey));					
						xmlFree(szKey);
							//cout<<"typeId  is  :   "<<typeId<<endl;
					}
					
					if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x"))
					{
						szKey=xmlGetProp(propNodePtr_item,(const xmlChar*)"x");
						point._x = atoi(reinterpret_cast<const char *>(szKey));					
						xmlFree(szKey);
						//cout<<"point._x  is  :   "<<point._x<<endl;
					}
								
					if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y"))
					{
						szKey=xmlGetProp(propNodePtr_item,(const xmlChar*)"y");
						point._y = atoi(reinterpret_cast<const char *>(szKey));					
						xmlFree(szKey);
						//cout<<"point._y  is  :   "<<point._y<<endl;
						idToNPC.insert(pair<string ,Point >(typeId,point) );
					}	
					attrPtr = attrPtr->next;					
				}
				
				curNext = curNext->next;
			}
		}
		npc.insert(pair<string , map <string ,Point > >(mapId,idToNPC) );
		idToNPC.clear();
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}