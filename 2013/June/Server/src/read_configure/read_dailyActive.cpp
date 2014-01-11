
/********************************************************************

    created:	2012/9/05  15:24
	
	�ļ�����	read_dailyActive.cpp

    author:     ChenZhen 

    purpose:  	������ȡ�ճ������ļ�����ʽΪxml)
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
#include"dailyActive.h"
using namespace std;

extern map<string,DailyActive*> dailyActiveConfMap;
int read_dailyActive(char *fileName)
{
	
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	int flgItem = 0;
	string activeId;
	string mapId;
	string beginTime;
	string endTime;
	string peaceTme;
	Point piexPt;
	int level,day;
	set<int>whichDay;
	set<string> beginTmeSet,endTmeSet;
	set<string>peaceTmeSet;
	DailyActive *newDailyActive;
	
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
	flgItem = 0;
	newDailyActive = NULL;
	
	//ѭ����ȡxml���ӽڵ㣬��ȡ�����Ӧ������	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"active"))
		{
			set<OffTmeStr>offTmeSet;
			string offBeginTime;    //��ʾ��ʼʱ��
			int offTimes;       //��ʾ����
			int durTimes;       //ÿ����ʾ���ʱ��
	
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*ȡ���ճ��������id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"activeId"))
				{
					xmlChar *_activeId=xmlGetProp(propNodePtr_item,(const xmlChar*)"activeId");
					activeId = const_cast<char *>(reinterpret_cast<const char *>(_activeId));					
					xmlFree(_activeId);
				}
				/*ȡ���ճ�������ڼ���ʼ*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"day1"))
				{
					xmlChar *_day1=xmlGetProp(propNodePtr_item,(const xmlChar*)"day1");
					day = atoi(reinterpret_cast<const char *>(_day1));
					xmlFree(_day1);
					if(day > 0)
					{
						whichDay.insert(day);
					}
				}
				/*ȡ���ճ�������ڼ���ʼ*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"day2"))
				{
					xmlChar *_day2=xmlGetProp(propNodePtr_item,(const xmlChar*)"day2");
					day = atoi(reinterpret_cast<const char *>(_day2));		
					xmlFree(_day2);
					if(day > 0)
					{
						whichDay.insert(day);
					}
				}
				/*ȡ���ճ�������ڼ���ʼ*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"day3"))
				{
					xmlChar *_day3=xmlGetProp(propNodePtr_item,(const xmlChar*)"day3");
					day = atoi(reinterpret_cast<const char *>(_day3));			
					xmlFree(_day3);
					if(day > 0)
					{
						whichDay.insert(day);
					}
				}
				
				/*ȡ���ճ������ʾ��ʼʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"offBeginTime1"))
				{
					xmlChar *_offBeginTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"offBeginTime1");
					offBeginTime = const_cast<char *>(reinterpret_cast<const char *>(_offBeginTime));		
					xmlFree(_offBeginTime);
				}
				
				/*ȡ���ճ������ʾ����*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"offTimes1"))
				{
					xmlChar *_offTimes=xmlGetProp(propNodePtr_item,(const xmlChar*)"offTimes1");					
					offTimes = atoi(reinterpret_cast<const char *>(_offTimes));		
					xmlFree(_offTimes);
				}
				
				/*ȡ���ճ��ÿ����ʾ�ļ��ʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"durTimes1"))
				{
					xmlChar *_durTimes=xmlGetProp(propNodePtr_item,(const xmlChar*)"durTimes1");					
					durTimes = atoi(reinterpret_cast<const char *>(_durTimes));		
					xmlFree(_durTimes);
					
					if(offBeginTime.size() > 1 && offTimes > 0 && durTimes > 0)
					{
						OffTmeStr offTmeStr(const_cast<char *>(offBeginTime.c_str()),\
						offTimes,durTimes);
						offTmeSet.insert(offTmeStr);
					}
				}
				
				
				/*ȡ���ճ������ʾ��ʼʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"offBeginTime2"))
				{
					xmlChar *_offBeginTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"offBeginTime2");
					offBeginTime = const_cast<char *>(reinterpret_cast<const char *>(_offBeginTime));		
					xmlFree(_offBeginTime);
				}
				
				/*ȡ���ճ������ʾ����*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"offTimes2"))
				{
					xmlChar *_offTimes=xmlGetProp(propNodePtr_item,(const xmlChar*)"offTimes2");					
					offTimes = atoi(reinterpret_cast<const char *>(_offTimes));		
					xmlFree(_offTimes);
				}
				
				/*ȡ���ճ��ÿ����ʾ�ļ��ʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"durTimes2"))
				{
					xmlChar *_durTimes=xmlGetProp(propNodePtr_item,(const xmlChar*)"durTimes2");					
					durTimes = atoi(reinterpret_cast<const char *>(_durTimes));		
					xmlFree(_durTimes);
					
					if(offBeginTime.size() > 1 && offTimes > 0 && durTimes > 0)
					{
						OffTmeStr offTmeStr(const_cast<char *>(offBeginTime.c_str()),\
						offTimes,durTimes);
						offTmeSet.insert(offTmeStr);
					}
				}
				
				
				/*ȡ���ճ������ʾ��ʼʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"offBeginTime3"))
				{
					xmlChar *_offBeginTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"offBeginTime3");
					offBeginTime = const_cast<char *>(reinterpret_cast<const char *>(_offBeginTime));		
					xmlFree(_offBeginTime);
				}
				
				/*ȡ���ճ������ʾ����*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"offTimes3"))
				{
					xmlChar *_offTimes=xmlGetProp(propNodePtr_item,(const xmlChar*)"offTimes3");					
					offTimes = atoi(reinterpret_cast<const char *>(_offTimes));		
					xmlFree(_offTimes);
				}				
				
				/*ȡ���ճ��ÿ����ʾ�ļ��ʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"durTimes3"))
				{
					xmlChar *_durTimes=xmlGetProp(propNodePtr_item,(const xmlChar*)"durTimes3");					
					durTimes = atoi(reinterpret_cast<const char *>(_durTimes));		
					xmlFree(_durTimes);
					
					if(offBeginTime.size() > 1 && offTimes > 0 && durTimes > 0)
					{
						OffTmeStr offTmeStr(const_cast<char *>(offBeginTime.c_str()),\
						offTimes,durTimes);
						offTmeSet.insert(offTmeStr);
					}
				}
				
				
				/*ȡ���ճ���ĺ�ƽʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"peaceTme1"))
				{
					xmlChar *_peaceTme=xmlGetProp(propNodePtr_item,(const xmlChar*)"peaceTme1");
					peaceTme = const_cast<char *>(reinterpret_cast<const char *>(_peaceTme));		
					xmlFree(_peaceTme);
					
					if(peaceTme.size() > 1)
					{
						peaceTmeSet.insert(peaceTme);
					}
				}
				
				/*ȡ���ճ���ĺ�ƽʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"peaceTme2"))
				{
					xmlChar *_peaceTme=xmlGetProp(propNodePtr_item,(const xmlChar*)"peaceTme2");
					peaceTme = const_cast<char *>(reinterpret_cast<const char *>(_peaceTme));		
					xmlFree(_peaceTme);
					
					if(peaceTme.size() > 1)
					{
						peaceTmeSet.insert(peaceTme);
					}
				}
				

				/*ȡ���ճ���Ŀ�ʼʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"beginTime1"))
				{
					xmlChar *_beginTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"beginTime1");
					beginTime = const_cast<char *>(reinterpret_cast<const char *>(_beginTime));		
					xmlFree(_beginTime);
					if(beginTime.size() > 1)
					{
						beginTmeSet.insert(beginTime);	
					}
				}
				
				/*ȡ���ճ���Ŀ�ʼʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"beginTime2"))
				{
					xmlChar *_beginTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"beginTime2");
					beginTime = const_cast<char *>(reinterpret_cast<const char *>(_beginTime));		
					xmlFree(_beginTime);
					if(beginTime.size() > 1)
					{
						beginTmeSet.insert(beginTime);		
					}
				}
				
				/*ȡ���ճ���Ŀ�ʼʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"beginTime3"))
				{
					xmlChar *_beginTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"beginTime3");
					beginTime = const_cast<char *>(reinterpret_cast<const char *>(_beginTime));		
					xmlFree(_beginTime);
					if(beginTime.size() > 1)
					{
						beginTmeSet.insert(beginTime);	
					}
				}
				/*ȡ���ճ���Ŀ�ʼʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"beginTime4"))
				{
					xmlChar *_beginTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"beginTime4");
					beginTime = const_cast<char *>(reinterpret_cast<const char *>(_beginTime));		
					xmlFree(_beginTime);
					if(beginTime.size() > 1)
					{
						beginTmeSet.insert(beginTime);		
					}
				}
				/*ȡ���ճ���Ŀ�ʼʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"beginTime5"))
				{
					xmlChar *_beginTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"beginTime5");
					beginTime = const_cast<char *>(reinterpret_cast<const char *>(_beginTime));		
					xmlFree(_beginTime);
					if(beginTime.size() > 1)
					{
						beginTmeSet.insert(beginTime);	
					}
				}
				
				/*ȡ���ճ���Ľ���ʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endTime1"))
				{
					xmlChar *_endTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"endTime1");
					endTime = const_cast<char *>(reinterpret_cast<const char *>(_endTime));		
					xmlFree(_endTime);
					if(endTime.size() > 1)
					{
						endTmeSet.insert(endTime);		
					}					
				}
				/*ȡ���ճ���Ľ���ʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endTime2"))
				{
					xmlChar *_endTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"endTime2");
					endTime = const_cast<char *>(reinterpret_cast<const char *>(_endTime));		
					xmlFree(_endTime);
					if(endTime.size() > 1)
					{
						endTmeSet.insert(endTime);			
					}					
				}
				/*ȡ���ճ���Ľ���ʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endTime3"))
				{
					xmlChar *_endTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"endTime3");
					endTime = const_cast<char *>(reinterpret_cast<const char *>(_endTime));		
					xmlFree(_endTime);
					if(endTime.size() > 1)
					{
						endTmeSet.insert(endTime);			
					}					
				}
				/*ȡ���ճ���Ľ���ʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endTime4"))
				{
					xmlChar *_endTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"endTime4");
					endTime = const_cast<char *>(reinterpret_cast<const char *>(_endTime));		
					xmlFree(_endTime);
					if(endTime.size() > 1)
					{
						endTmeSet.insert(endTime);			
					}					
				}
				/*ȡ���ճ���Ľ���ʱ��*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endTime5"))
				{
					xmlChar *_endTime=xmlGetProp(propNodePtr_item,(const xmlChar*)"endTime5");
					endTime = const_cast<char *>(reinterpret_cast<const char *>(_endTime));		
					xmlFree(_endTime);
					if(endTime.size() > 1)
					{
						endTmeSet.insert(endTime);			
					}					
				}
				
				/*ȡ���ճ���ĵ�ͼid*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId"))
				{
					xmlChar *_mapId=xmlGetProp(propNodePtr_item,(const xmlChar*)"mapId");
					mapId = const_cast<char *>(reinterpret_cast<const char *>(_mapId));		
					xmlFree(_mapId);
				}
				
				/*ȡ���ճ�������غ�����*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x"))
				{
					xmlChar *_x=xmlGetProp(propNodePtr_item,(const xmlChar*)"x");
					piexPt._x = atoi(reinterpret_cast<const char *>(_x));					
					xmlFree(_x);
				}
				
				/*��ȡ�ճ��������������*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y"))
				{
					xmlChar *_y=xmlGetProp(propNodePtr_item,(const xmlChar*)"y");
					
					piexPt._y = atoi(reinterpret_cast<const char *>(_y));
					
					xmlFree(_y);
				}
				
				/*��ȡ�ճ�������Ƶȼ�*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"level"))
				{
					xmlChar *_level=xmlGetProp(propNodePtr_item,(const xmlChar*)"level");
					
					level = atoi(reinterpret_cast<const char *>(_level));
					
					xmlFree(_level);
					flgItem = 1;
				}
				
				/*ʵ�����ճ����ͼƬid*/	
				if(flgItem == 1)
				{
					newDailyActive = new DailyActive(const_cast<char*>\
					(activeId.c_str()),const_cast<char *>(mapId.c_str()),\
					whichDay,offTmeSet,beginTmeSet,endTmeSet,peaceTmeSet,\
					piexPt,level);

					dailyActiveConfMap[activeId] = newDailyActive;
						
					flgItem = 0;
					
					whichDay.clear();
					beginTmeSet.clear();
					endTmeSet.clear();
				}		
					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}

