#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"rideEquip_config.h"
#include<map>
#include<string>
#include<iostream>
using namespace std;
extern map<string,RideEquip_config*>id_to_rideEquip;
int read_files_equip(char *fileName)
{

	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	char id[20]={'\0'};           //װ��ID
	char  name[50]={'\0'};		 //װ������
	int    grade;        //װ���ȼ�
	int    order;        //װ������
	int	   rank;         //װ������
	int	   type;         //װ������
	char   party[10]={'\0'};        //װ������
	int	   suit_type;    //��װ���
	char  suit_id[20]={'\0'};       //��װID
	int    life;         //����ֵ
	int    inharm;       //�ڹ��˺�
	int    outharm;      //�⹦�˺�
	int    inattack;     //�ڹ�����
	int    outattack;    //�⹦����
	int    indefence;    //�ڹ�����
	int    outdefence;   //�⹦����
	int    genuine;      //����
	int    crit;         //����
	int    hit; 		 //����
	int    dodge;        //����
	int    tenacity; 	 //����
	int	   durability;   //�;ö�
	int    priceBound;
	int	   price;        //�۸�
	int	   goldBound;
	int	   gold;			//Ԫ������۸�
	int sellPrice; 			//�����۸�
	
	//����������,���ʱװ
	int time;
	char photoId[10]={'\0'};
		
	//��ȡequip�����ļ�
	xmlKeepBlanksDefault(0);
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		return -1;
	}
	//�õ�xml�ļ���root
	curnow=xmlDocGetRootElement(doc);
	if(NULL==curnow)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	//xml����ر���
	curnow=curnow->xmlChildrenNode;
	
	while(curnow!=NULL)
	{	
		
		curNode = curnow->xmlChildrenNode;
			if(NULL==curNode)
			{
				xmlFreeDoc(doc);
				continue;
			}	
			while(curNode != NULL)
			{
				int len;
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(id,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(id));
					xmlFree(cTem);					
				}
				
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(name,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(name));
					xmlFree(cTem);	
				}
				
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"grade"))
				{
					cTem= xmlNodeGetContent(curNode);
					grade=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"order"))
				{
					cTem= xmlNodeGetContent(curNode);
					order=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"rank"))
				{
					cTem= xmlNodeGetContent(curNode);
					rank=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					//cout<<"rank:"<<rank<<endl;
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"time"))
				{
					cTem= xmlNodeGetContent(curNode);
					time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					//cout<<"time:"<<time<<endl;
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"attribute"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					//cout<<"type:"<<type<<endl;
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"party"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(party,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(party));
					xmlFree(cTem);						
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"suit_type"))
				{
					cTem= xmlNodeGetContent(curNode);
					suit_type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					//cout<<"suit_type:"<<suit_type<<endl;
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"suit_id"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(suit_id,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(suit_id));
					xmlFree(cTem);						
					//cout<<"suit_id:"<<suit_id<<endl;
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"hp"))
				{
					cTem= xmlNodeGetContent(curNode);
					life=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"inHrt"))
				{
					cTem= xmlNodeGetContent(curNode);
					inharm=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"outHrt"))
				{
					cTem= xmlNodeGetContent(curNode);
					outharm=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}if(!xmlStrcmp(curNode->name,(const xmlChar *)"inAttVal"))
				{
					cTem= xmlNodeGetContent(curNode);
					inattack=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}if(!xmlStrcmp(curNode->name,(const xmlChar *)"outAttVal"))
				{
					cTem= xmlNodeGetContent(curNode);
					outattack=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"inDefVal"))
				{
					cTem= xmlNodeGetContent(curNode);
					indefence=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}if(!xmlStrcmp(curNode->name,(const xmlChar *)"outDefVal"))
				{
					cTem= xmlNodeGetContent(curNode);
					outdefence=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}if(!xmlStrcmp(curNode->name,(const xmlChar *)"mp"))
				{
					cTem= xmlNodeGetContent(curNode);
					genuine=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"crit"))
				{
					cTem= xmlNodeGetContent(curNode);
					crit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}if(!xmlStrcmp(curNode->name,(const xmlChar *)"hit"))
				{
					cTem= xmlNodeGetContent(curNode);
					hit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"dodge"))
				{
					cTem= xmlNodeGetContent(curNode);
					dodge=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"tenacity"))
				{
					cTem= xmlNodeGetContent(curNode);
					tenacity=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}if(!xmlStrcmp(curNode->name,(const xmlChar *)"durability"))
				{
					cTem= xmlNodeGetContent(curNode);
					durability=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"moneyBound"))
				{
					cTem= xmlNodeGetContent(curNode);
					priceBound=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"money"))
				{
					cTem= xmlNodeGetContent(curNode);
					price=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"price"))
				{
					cTem= xmlNodeGetContent(curNode);
					sellPrice=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"gold"))
				{
					cTem= xmlNodeGetContent(curNode);
					gold=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"goldBound"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldBound=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"photoId"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(photoId,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(photoId));
					xmlFree(cTem);
					Equip_config *equip;			
					equip=new Equip_config(id,name,grade,order,rank,type,party,suit_type,suit_id,life,
											inharm,outharm,inattack,outattack,indefence,outdefence,genuine,crit,hit,
											dodge,tenacity,durability,priceBound,price,goldBound,gold,sellPrice,time,photoId);
					id_to_equip[id]=equip;
				}		
				curNode=curNode->next;
			}
		curnow = curnow->next;
	}
	//cout<<"in read_equip_config::equip size is :"<<id_to_equip.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}
