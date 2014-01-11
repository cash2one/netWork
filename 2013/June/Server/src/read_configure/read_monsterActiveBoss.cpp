
/********************************************************************

    created:	2012/2/22  15:24
	
	�ļ�����	function_read_configuration_files_map.cpp

    author:     ChenZhen 

    purpose:  	������ȡ���е�ͼ�������ļ�����ʽΪxml)
	
	��	�ģ�	Tory 	2012/2/28
	
	�޸����ݣ�	��data_structure_struct�е�Monster_Inform�ṹ���ΪMonster_Inform�࣬
				���κ��߼��Ķ�������Ϊ����hero_configuration�ౣ��ͳһ

*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"data_structure_struct.h"
#include"monster_configuration.h"
#include"map_inform.h"
#include<iostream>
#include<vector>
#include<string.h>

#include"monsterBase.h"
#include"monsterActiveBoss.h"
#include"map_src.h"
using namespace std;

#include "data_structure_struct.h"
#define Map_Val(a,b) ( map<string,const jumpId_infor*>::value_type( (a),(b)) )

extern map<string,Map_Src*>mapId_connect_map;
extern map<string,Monster_Inform*>monTypeId_connect_property;
int read_monsterActiveBoss(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};	
	int flgItem;
	string typeId;
	string mapId;
	Point piexPt;
	
	MonsterActiveBoss *newActiveBoss;
	
	strncpy(szDocName,fileName,strlen(fileName));
	
	
	string nickName;
	string uniqueId;
	string photoId;
			
	int lifeUpperVal;
	int lifeVal;
	int magicUpperVal;
	int magicVal;
		
	int sum;
	int walkRange;
	int attackRange;
			
	Point logicEndPt;
	int count;
			
			
	int hrtSud;      //����
	int outHrt;     //����
	int inHrt;      //����
	int outAttVal;    //�⹦����ֵ
	int inAttVal;    //�ڹ�����ֵ
	int outDefVal;    //�⹦����ֵ
	int inDefVal;    //�ڹ�����ֵ
	int defSumVal;   //����ֵ�ܺ�
	int hit;        //����
	int crit;       //����
	int voids;    	  //����
	int tenacity;       //����	
	int hatRge;               //��޷�Χ
	int hatVal;               //���ֵ
	
	int failGoodsLess;   //����������ֵ
	int failGoodsMost;   //����������ֵ
	int hatRange;      //��޷�Χ
	int gold;       //���
	set<string> failList;  //�����б�
	int radius;
	char *type;          //add chenzhen 5.30 ���б�����������Ѳ�����֣�
	char *kind;          //add chenzhen 5.30 ������ͨ����Ӣ��Boss���֣�
	double cdTime;       //cdʱ��
	int experience;      //����
	int angVal;          //ŭ��ֵ
	vector<string>skiIdSet;   //����id�б�
	int rank;            //�ȼ�
	int speed;           //�ƶ��ٶ�
	LveCtnManger lveCtnMager;      //���������������
			
	int fiveEleInt;      //�������Դ���ֵ
	int fiveEleRank;     //���еȼ�ֵ
	int fiveHurt;        //�����˺�ֵ
			
	int goFor;           //�߶�Ƶ��
	int expTme;           //���鱶��
	int monyTme;          //��Ǯ����
	char *genAttId; 
	char *stage;
	
	int _ownerAttriType;  //����������Ӫ����������
	char* _ownerAttri;    //���������󣬰���Ӫֵ
	double attackRatio;          //��ɱ�����ְ���������
	
	bool isInnerAttack;   //ƫ�ڹ�Ϊ�棬����Ϊ��
	
	Monster_Inform *mon_inform = NULL;
	
	
	map<string,Map_Src*>::iterator src_it;
	
	Map_Src* map_now;
	
	map<string,Monster_Inform*>::iterator it;
	
	MonsterActiveBoss *monActiveBoss;

	
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
	
	//ѭ����ȡxml���ӽڵ㣬��ȡ�����Ӧ������	
	while(curNode!=NULL)
	{	
		
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"activeBoss"))
		{
			propNodePtr_item = curNode;
			monActiveBoss = NULL;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*ȡ���boss������id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
					xmlChar *_typeId=xmlGetProp(propNodePtr_item,(const xmlChar*)"typeId");				
					
					typeId = "MP";				
					
					typeId += const_cast<char *>(reinterpret_cast<const char *>(_typeId));
	
					xmlFree(_typeId);
					
					
					it = monTypeId_connect_property.find(typeId);			
       				if(it == monTypeId_connect_property.end())
					{
						return -5;							
					}		
					it->second->sum+=1;				//������Ϸ�У����ֵֹ���Ŀ		
					
					int len_sum,Sum,sum;
					sum = it->second->sum;        //���ŵ�ͼ�У����ֵֹ���Ŀ
					Sum  = sum;
					for(sum += 1,len_sum =0;sum >= 1;sum /= 10)
					{
						len_sum++;
					}						
					char *sum_str=new char[len_sum+1];
					sprintf(sum_str,"%d",Sum+1);
					uniqueId = typeId;
					uniqueId += "_";
				//	uniqueId += mapId;
				//	uniqueId += "_";
					uniqueId += sum_str;		
					delete [] sum_str;
				}
				/*ȡ���boss��mapId*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId"))
				{
					xmlChar *_mapId=xmlGetProp(propNodePtr_item,(const xmlChar*)"mapId");
					mapId = const_cast<char *>(reinterpret_cast<const char *>(_mapId));				
					xmlFree(_mapId);
					
					src_it = mapId_connect_map.find(mapId);
					if(src_it == mapId_connect_map.end())
					{
						map_now = NULL;
						return -5;
						// continue;
					}
					else
					{
						map_now = src_it->second;
					}
				}
				
				/*ȡ���boss�����غ�����*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x"))
				{
					xmlChar *_x=xmlGetProp(propNodePtr_item,(const xmlChar*)"x");
					piexPt._x = atoi(reinterpret_cast<const char *>(_x));					
					xmlFree(_x);
				}
				
				/*ȡ���boss������������*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y"))
				{
					xmlChar *_y=xmlGetProp(propNodePtr_item,(const xmlChar*)"y");
					piexPt._y = atoi(reinterpret_cast<const char *>(_y));					
					xmlFree(_y);
					flgItem = 1;
					
					
					it=monTypeId_connect_property.find(typeId);
					if(it == monTypeId_connect_property.end())
					{
						return -5;
					}
					mon_inform=it->second;			//ȡmap��������Ӧ��ֵ
					
					lifeUpperVal = mon_inform->lifeUpperVal;
					lifeVal = mon_inform->lifeVal;
					magicUpperVal = mon_inform->magicUpperVal;
					magicVal = mon_inform->magicVal;
					hrtSud = mon_inform->hrtSud;
					outHrt = mon_inform->outHrt;
					inHrt = mon_inform->inHrt;
					outAttVal = mon_inform->outAttVal;
					inAttVal = mon_inform->inAttVal;
					outDefVal = mon_inform->outDefVal;
					defSumVal = mon_inform->defSumVal;
					inDefVal = mon_inform->inDefVal;
					defSumVal = mon_inform->defSumVal;
					
					
					hit = mon_inform->hit;
					crit = mon_inform->crit;
					voids = mon_inform->voids;
					
					tenacity = mon_inform->tenacity;
					hatRange = mon_inform->hatRange;
					failGoodsLess = mon_inform->failGoodsLess;
					failGoodsMost = mon_inform->failGoodsMost;
					hatVal = mon_inform->hatVal;
					gold = mon_inform->gold;
					failList = mon_inform->failList;
					
					nickName = mon_inform->nickName;
					walkRange = mon_inform->walk_range;
					attackRange = mon_inform->attack_range;
					photoId = mon_inform->photoId;
					type = mon_inform->type;        //add chenzhen 5.30
					kind = mon_inform->kind;          //add chenzhen 5.11
					radius = mon_inform->radius;      //add chenzhen 5.29
					cdTime = mon_inform->cdTime;
					experience = mon_inform->getExperience();
					angVal = mon_inform->getAngVal();
					skiIdSet = mon_inform->getSkiIdSet();
					rank = mon_inform->getRank();
					speed = mon_inform->getSpeed();
					
					fiveEleInt = mon_inform->fiveEleInt;
					fiveEleRank = mon_inform->fiveEleRank;
					fiveHurt =  mon_inform->fiveHurt;  
					goFor = mon_inform->goFor;
					expTme = mon_inform->expTme;
					monyTme = mon_inform->monyTme;
					genAttId = mon_inform->genAttId;
					stage = mon_inform->stage;
					
					_ownerAttriType = mon_inform->ownerAttriType;
					_ownerAttri = mon_inform->ownerAttri;
					attackRatio = mon_inform->attackRatio;
					isInnerAttack = mon_inform->isInnerAttack;
				}
							
				/*ʵ����Ұ��BOSS*/	
				if(flgItem == 1)
				{
				
					monActiveBoss = new MonsterActiveBoss(const_cast<char *>(mapId.c_str()),\
												const_cast<char *>(typeId.c_str()),\
												const_cast<char *>(nickName.c_str()),\
												const_cast<char *>(uniqueId.c_str()),type,\
												kind,experience,cdTime,lifeUpperVal,lifeVal,\
												magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
												outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,\
												hit,crit,voids,tenacity,walkRange, hatRange,\
												attackRange,failGoodsLess,failGoodsMost,\
												hatVal,gold,failList,piexPt,rank,speed,\
												fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,\
												monyTme,stage,const_cast<char *>(photoId.c_str()),\
												skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,\
												attackRatio,isInnerAttack,lveCtnMager);
					monActiveBoss->setMap(map_now);							
					map_now->insertBoss(monActiveBoss);	
					flgItem = 0;
				}		
					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	
	// if(map_now != NULL)
	// {
		// map_now->setMonBossMap();
	// }
	
	xmlFreeDoc(doc);
	return 0;
}
