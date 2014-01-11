/************************************************************
	�ļ�����read_monster_skill.cpp
	�ļ����ã���ȡ�����������Ƶ������ļ�
	���ߣ�chenzhen
	�������ڣ�2012.07.10
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"skillBase.h"
#include"recoverBlood.h"
#include"rigidity.h"
#include"unEnemy.h"
#include"monCallSkill.h"
extern map<string,SkillBase*> monster_skill_map;
int read_monster_skill(char *fileName)  
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
	xmlNodePtr propNodePtr_skill;
	string name;              //��������
	string id;                //����id 
	int rank;                 //���ܵȼ�
	double relPer;        	 //�ͷ�Ƶ��
	double angVal;			 //��������ŭ��ֵ
	double cdTime;           //cdʱ��	
	double trgPer;            //����ֵ��������
	int flgSkill;             //��־����
	
	SkillBase *skill;         //����ʵ��ָ��
	double recoverLife;      //����ֵ�ָ�����
	double lastTime;         //���ܳ���ʱ��
	bool durance;           //�Ƿ�Ϊ��ʱ�Լ���
	double hrtRatio;        //�����˺�
	int during;
	double playCd;          //���ܶ�������ʱ��
	
	flgSkill = -1;
	
	/*Ĭ��Ϊ2��*/
	playCd = 2;             
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"skill"))
		{
			propNodePtr_skill = curNode;
			xmlAttrPtr attrPtr = propNodePtr_skill->properties;
			
			while(attrPtr!=NULL)
			{	
				/*��ȡ����id����*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"id"))
				{					
					xmlChar *_id = xmlGetProp(propNodePtr_skill,(const xmlChar*)"id");
					id = reinterpret_cast<const char *>(_id);
					xmlFree(_id);
				}
				
				/*��ȡ������������*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{					
					xmlChar *_name = xmlGetProp(propNodePtr_skill,(const xmlChar*)"name");
					name = reinterpret_cast<const char *>(_name);
					xmlFree(_name);
				}
				
				/*��ȡ���ܵȼ���������*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"rank"))
				{					
					xmlChar *_rank = xmlGetProp(propNodePtr_skill,(const xmlChar*)"rank");
					rank = atoi(reinterpret_cast<const char *>(_rank));
					xmlFree(_rank);
				}
				
				/*��ȡ���ܴ���Ƶ������*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"relPer"))
				{					
					xmlChar *_relPer = xmlGetProp(propNodePtr_skill,(const xmlChar*)"relPer");
					relPer = atof(reinterpret_cast<const char *>(_relPer));
					xmlFree(_relPer);
				}
				
				/*��ȡ����ŭ��ֵ��������*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"angVal"))
				{					
					xmlChar *_angVal = xmlGetProp(propNodePtr_skill,(const xmlChar*)"angVal");
					angVal = atof(reinterpret_cast<const char *>(_angVal));
					xmlFree(_angVal);
				}
				/*��ȡ����cdʱ��*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cdTime"))
				{					
					xmlChar *_cdTime = xmlGetProp(propNodePtr_skill,(const xmlChar*)"cdTime");
					cdTime = atof(reinterpret_cast<const char *>(_cdTime));
					xmlFree(_cdTime);
				}
				/*��ȡ���ܲ���ʱ��*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"playCd"))
				{					
					xmlChar *_playCd = xmlGetProp(propNodePtr_skill,(const xmlChar*)"playCd");
					playCd = atof(reinterpret_cast<const char *>(_playCd));
					xmlFree(_playCd);
				}
				/*��ȡ�����˺�ϵ��*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hrtRatio"))
				{					
					xmlChar *_hrtRatio = xmlGetProp(propNodePtr_skill,(const xmlChar*)"hrtRatio");
					hrtRatio = atof(reinterpret_cast<const char *>(_hrtRatio));
					xmlFree(_hrtRatio);
				}
				/*��ȡ�����Ƿ�Ϊ��ʱ����*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"during"))
				{					
					xmlChar *_during = xmlGetProp(propNodePtr_skill,(const xmlChar*)"during");
					during = atoi(reinterpret_cast<const char *>(_during));
					xmlFree(_during);
					durance = during ? true:false;
						
				}
				/*��ȡ��������ֵ������������*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"trgPer"))
				{					
					xmlChar *_trgPer = xmlGetProp(propNodePtr_skill,(const xmlChar*)"trgPer");
					trgPer = atof(reinterpret_cast<const char *>(_trgPer));
					xmlFree(_trgPer);
				}
				/*��ȡ���ܻظ�����ֵ��������*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"recoverLife"))
				{					
					xmlChar *_recoverLife = xmlGetProp(propNodePtr_skill,(const xmlChar*)"recoverLife");
					recoverLife = atof(reinterpret_cast<const char *>(_recoverLife));
					xmlFree(_recoverLife);
				}
				
				/*��ȡ���ܻظ�����ֵ��������*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lastTime"))
				{					
					xmlChar *_lastTime = xmlGetProp(propNodePtr_skill,(const xmlChar*)"lastTime");
					lastTime = atof(reinterpret_cast<const char *>(_lastTime));
					xmlFree(_lastTime);
					flgSkill = 1;
				}
			
				/*ʵ����Skill��*/
				if(flgSkill == 1)
				{
					flgSkill = 0;
					if(id.find("darkSukBld") != string::npos)
					{
						/*Ĭ��*/
						recoverLife = 0.1;
						skill = new RecoverBlood(const_cast<char *>(name.c_str()),\
						const_cast<char *>(id.c_str()),rank,relPer,angVal,\
						cdTime,playCd,hrtRatio,durance,trgPer,recoverLife);	
					}
					else if(id.find("proArms") != string::npos ||\
							id.find("delMethod") != string::npos ||\
							id.find("tightEncir") != string::npos)
					{
						skill = new Rigidity(const_cast<char *>(name.c_str()),\
						const_cast<char *>(id.c_str()),rank,relPer,angVal,\
						cdTime,playCd,hrtRatio,durance,trgPer,lastTime);
					}
					else if(id.find("dieHard") != string::npos)
					{
						skill = new UnEnemy(const_cast<char *>(name.c_str()),\
						const_cast<char *>(id.c_str()),rank,relPer,angVal,\
						cdTime,playCd,hrtRatio,durance,lastTime);
					}
					
					else if(id.find("callType") != string::npos)
					{
						skill = new MonCallSkill(const_cast<char *>(name.c_str()),\
						const_cast<char *>(id.c_str()),rank,relPer,angVal,\
						cdTime,playCd,hrtRatio,durance,trgPer);
					}
					
					else
					{
						skill = new SkillBase(const_cast<char *>(name.c_str()),\
						const_cast<char *>(id.c_str()),rank,relPer,angVal,\
						cdTime,playCd,hrtRatio,durance);
						// cout<<"id:"<<id<<endl;
						// cout<<"relPer:"<<relPer<<endl;
					}
					
					monster_skill_map[id] = skill;
					
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
	
	
