
/********************************************************************

    created:	2012/2/22  15:24
	
	�ļ�����	read_take_goods.cpp

    author:     ChenZhen 

    purpose:  	������ȡ���Բ�ժ��������ߵ������ļ�����ʽΪxml)
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
#include"takeGoods.h"
using namespace std;

extern map<string,TakeGoods*> takeGoodsConfMap;

int read_take_goods(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	int flgItem;
	
	strncpy(szDocName,fileName,strlen(fileName));
	
	//cout<<"in the configuration_files_map.cpp file:"<<fileName<<endl;
	//��ȡ��ͼ�����ļ�
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		return -1;
	}
	
	//�õ�xml�ļ���root
	curNode=xmlDocGetRootElement(doc);
	if(NULL==curNode)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	
	//xml����ر���
	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_item;
	flgItem = 0;
	
	//ѭ����ȡxml���ӽڵ㣬��ȡ�����Ӧ������	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"item"))
		{
			string typeId;
			string name;
			string photoId;
			string goodsId;
			string offerWords;
			TakeGoods *takeGoods = NULL;
			bool isDis,trigByMsg = false;
			int takeModle;           //�ɲɼ���Ʒͬʱ�ɲɼ�������
			int taskStyle;           //�ɲɼ���Ʒ������
			int brandType;
			double takeTme;         //�ɼ�����ʱ��
			bool isMove = false;            //�Ƿ�ᶯ
			int durTme;             //��ϯ�ĳ���ʱ��
			bool isInterrupt = false;       //�Ƿ���Դ��
	
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*ȡ����ժȡ��Ʒ������id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
					xmlChar *_typeId=xmlGetProp(propNodePtr_item,(const xmlChar*)"typeId");
					typeId = const_cast<char *>(reinterpret_cast<const char *>(_typeId));					
					xmlFree(_typeId);
				}
				/*ȡ����ժȡ��Ʒ����Ʒid*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goodsId"))
				{
					xmlChar *_goodsId=xmlGetProp(propNodePtr_item,(const xmlChar*)"goodsId");
					goodsId = const_cast<char *>(reinterpret_cast<const char *>(_goodsId));					
					xmlFree(_goodsId);
				}
				
				/*��ȡ��ժȡ��Ʒ������*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{
					xmlChar *_name=xmlGetProp(propNodePtr_item,(const xmlChar*)"name");
					
					name = const_cast<char *>(reinterpret_cast<const char *>(_name));
					
					xmlFree(_name);
				}
				
				/*��ȡ��ժȡ��Ʒ������ʽ*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"trigByMsg"))
				{
					int trigFlg;
					xmlChar *_trigByMsg=xmlGetProp(propNodePtr_item,(const xmlChar*)"trigByMsg");			
					trigFlg=atoi(reinterpret_cast<const char *>(_trigByMsg));					
					xmlFree(_trigByMsg);
					if(trigFlg == 0)
					{
						trigByMsg = false;
					}
					else
					{
						trigByMsg = true;
					}
				}
				
				/*��ȡ��ժȡ��Ʒ��Ӧ��ʾ��Ϣ������*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"offerWords"))
				{
					xmlChar *_offerWords=xmlGetProp(propNodePtr_item,(const xmlChar*)"offerWords");
					
					offerWords = const_cast<char *>(reinterpret_cast<const char *>\
					(_offerWords));
					
					xmlFree(_offerWords);
				}
				
				/*��ȡ��ժȡ���Ƿ�ɶ�*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"durTme"))
				{
					xmlChar *_durTme=xmlGetProp(propNodePtr_item,(const xmlChar*)"durTme");			
					durTme=atoi(reinterpret_cast<const char *>(_durTme));			
					xmlFree(_durTme);
				}
				
				/*��ȡ��ժȡ���Ƿ�ɶ�*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isMove"))
				{
					int moveFlg;
					xmlChar *_isMove=xmlGetProp(propNodePtr_item,(const xmlChar*)"isMove");			
					moveFlg=atoi(reinterpret_cast<const char *>(_isMove));					
					xmlFree(_isMove);
					if(moveFlg == 0)
					{
						isMove = false;
					}
					else
					{
						isMove = true;
					}
				}
				
				/*��ȡ��ժȡ��Ʒժȡ���Ƿ���ʧ*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isDis"))
				{
					int flgDis;
					xmlChar *_isDis=xmlGetProp(propNodePtr_item,(const xmlChar*)"isDis");			
					flgDis=atoi(reinterpret_cast<const char *>(_isDis));					
					xmlFree(_isDis);
					if(flgDis == 0)
					{
						isDis = false;
					}
					else
					{						
						isDis = true;
					}
				}
				
				/*��ȡ�ɲɼ���Ʒͬʱ�ɲɼ�������*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"takeModle"))
				{
					xmlChar *_takeModle=xmlGetProp(propNodePtr_item,(const xmlChar*)"takeModle");			
					takeModle=atoi(reinterpret_cast<const char *>(_takeModle));					
					xmlFree(_takeModle);
				}
				
				/*��ȡ�ɲɼ���Ʒ������*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"taskStyle"))
				{
					xmlChar *_taskStyle=xmlGetProp(propNodePtr_item,(const xmlChar*)"taskStyle");			
					taskStyle=atoi(reinterpret_cast<const char *>(_taskStyle));					
					xmlFree(_taskStyle);
				}
				
				/*��ȡ�ɼ�����ʱ��*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"takeTme"))
				{
					xmlChar *_takeTme=xmlGetProp(propNodePtr_item,(const xmlChar*)"takeTme");			
					takeTme=atof(reinterpret_cast<const char *>(_takeTme));					
					xmlFree(_takeTme);
				}
				
				
				/*��ȡ�ɼ�������*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"brandType"))
				{
					xmlChar *_brandType=xmlGetProp(propNodePtr_item,(const xmlChar*)"brandType");			
					brandType=atoi(reinterpret_cast<const char *>(_brandType));					
					xmlFree(_brandType);
				}
				
				/*��ȡ�ɼ�������*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isInterrupt"))
				{
					xmlChar *_isInterrupt=xmlGetProp(propNodePtr_item,(const xmlChar*)"isInterrupt");			
					int interFlg=atoi(reinterpret_cast<const char *>(_isInterrupt));					
					xmlFree(_isInterrupt);
					if(interFlg == 1)
					{
						isInterrupt = true;
					}
				}
				
				
				/*��ȡ��ժȡ��Ʒ��ͼƬid*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"photoId"))
				{
					xmlChar *_photoId=xmlGetProp(propNodePtr_item,(const xmlChar*)"photoId");
					
					photoId = const_cast<char *>(reinterpret_cast<const char *>(_photoId));
					
					xmlFree(_photoId);
					flgItem = 1;
				}
				
				/*ʵ������ժȡ��Ʒ��ͼƬid*/	
				if(flgItem == 1)
				{
					takeGoods = new TakeGoods(const_cast<char*>(typeId.c_str()),\
					const_cast<char*>(goodsId.c_str()),const_cast<char*>\
					(name.c_str()),const_cast<char*>(photoId.c_str()),\
					isDis,trigByMsg,takeModle,taskStyle,brandType,takeTme,\
					const_cast<char*>(offerWords.c_str()),durTme,isMove,isInterrupt);
					takeGoodsConfMap[typeId] = takeGoods;
					flgItem = 0;
				}		
					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}

