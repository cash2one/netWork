/************************************************************
	�ļ�����read_groupBrush.cpp
	�ļ����ã���ȡˢ��ģʽ�������ļ�
	���ߣ�chenzhen
	�������ڣ�2012.07.06
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"groupBrush.h"
#include<map>
extern map<string,GroupBrush*> groupBrush;
int read_files_groupBrush(char *fileName)
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
	xmlNodePtr propNodePtr_group;
	
	string groupId;           //����id
	double generRatio;        //��ͨ����ռ����
	double eliteRatio;        //��Ӣ����ռ����
	double activeRatio;       //��������ռ����	
	double passRatio;         //��������ռ����
	double patRatio;          //Ѳ�߹���ռ����
	bool randFlg;             //boss���Ƿ�����̳�
	int bossNum;              //BOSS�������̳���������
	
	int flgLimit;             //��־����
	
	flgLimit = -1;
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"groupType"))
		{
			propNodePtr_group = curNode;
			xmlAttrPtr attrPtr = propNodePtr_group->properties;
			
			while(attrPtr!=NULL)
			{	
				/*��ȡgroupId����*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"groupId"))
				{					
					xmlChar *_groupId = xmlGetProp(propNodePtr_group,(const xmlChar*)"groupId");
					groupId = reinterpret_cast<const char *>(_groupId);
					xmlFree(_groupId);
				}
				
				/*��ȡ��ͨ����ռ����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"generRatio"))
				{					
					xmlChar *_generRatio = xmlGetProp(propNodePtr_group,(const xmlChar*)"generRatio");
					generRatio = atof(reinterpret_cast<const char *>(_generRatio));
					xmlFree(_generRatio);
				}
				
				/*��ȡ��Ӣ����ռ����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"eliteRatio"))
				{					
					xmlChar *_eliteRatio = xmlGetProp(propNodePtr_group,(const xmlChar*)"eliteRatio");
					eliteRatio = atof(reinterpret_cast<const char *>(_eliteRatio));
					xmlFree(_eliteRatio);
				}
				
				/*��ȡboss���Ƿ����ˢ��*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"randFlg"))
				{
					int flg;
					xmlChar *_randFlg = xmlGetProp(propNodePtr_group,(const xmlChar*)"randFlg");
					flg = atoi(reinterpret_cast<const char *>(_randFlg));
					xmlFree(_randFlg);
					if(flg == 1)
					{
						randFlg = true;
					}
					else
					{
						false;
					}
					
				}
				
				/*��ȡboss������*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"bossNum"))
				{
					int flg;
					xmlChar *_bossNum = xmlGetProp(propNodePtr_group,(const xmlChar*)"bossNum");
					bossNum = atoi(reinterpret_cast<const char *>(_bossNum));
					xmlFree(_bossNum);
				}
				
				/*��ȡ��������ռ����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"passRatio"))
				{					
					xmlChar *_passRatio = xmlGetProp(propNodePtr_group,(const xmlChar*)"passRatio");
					passRatio = atof(reinterpret_cast<const char *>(_passRatio));
					xmlFree(_passRatio);
					
				}
								
				/*��ȡ��������ռ����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"activeRatio"))
				{					
					xmlChar *_activeRatio = xmlGetProp(propNodePtr_group,(const xmlChar*)"activeRatio");
					activeRatio = atof(reinterpret_cast<const char *>(_activeRatio));
					xmlFree(_activeRatio);
				}
				
				/*��ȡѲ�߹���ռ����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"patRatio"))
				{					
					xmlChar *_patRatio = xmlGetProp(propNodePtr_group,(const xmlChar*)"patRatio");
					patRatio = atof(reinterpret_cast<const char *>(_patRatio));
					xmlFree(_patRatio);
					flgLimit = 1;
				}
				
				/*ʵ����GroupBrush��*/
				if(flgLimit == 1)
				{
					GroupBrush *group_Brush = new GroupBrush(const_cast<char *>(groupId.c_str()),generRatio,\
															randFlg,bossNum,eliteRatio,passRatio,activeRatio,\
															patRatio);
								
					groupBrush[groupId] = group_Brush;
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