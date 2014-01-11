#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"skill_configuration.h"
#include<string>
//add to test.
#include <iostream>
using namespace std;
extern map<string,Skill_Configuration*>id_to_skill;

int read_files_zhudong(char * fileName) //�����������͵ļ��ܻ������ݵĶ�ȡ  evan add 2012.5.25
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);	
	string id;           		//����Id
	string name;         		//��������
	int   type;				//��������  ��1��������2��������3��debuff��4��buff��5��ҽ�ƣ���
	int   effect;              //���ܸ���Ч��
	int   con_time;            //Ч������ʱ��
	int   cd_time;             //����cd����ȴʱ�䣩
	int	  factor;              //����ϵ������ֵ
	int   genuine;             //��������
	int	  time_sec;            //���ܶ�������ʱ�䣨�룩
	int   time_usec;           //���ܶ�������ʱ�䣨΢�룩 
	int  nggjjdz_debuff;	    //debuff�����ڹ�����
	int  wggjjdz_debuff;		//debuff�����⹦����		
	int  ngfyjdz_debuff;		//debuff�����ڹ�����		
	int  wgfyjdz_debuff;		//debuff�����⹦����
	int  mzjd_debuff;			//debuff��������
	int  jdrx_debuff;			//debuff��������
	int	 jdsb_debuff;			//debuff��������
	int  jdbj_debuff;			//debuff���ͱ���
	int  cxdx_debuff;			//������Ѫֵ
	int  attack_type;			//������ʽ
	int  attack_range;			//��������
	int  genuine_growup;		//�������ĳɳ�����
	int	 effect_growup;			//����Ч���ɳ�����
	int	 factor_growup;		//����ϵ���ɳ�����
	int    control_grade;		//�ȼ�����
	int    value1;
	int    value2;
	int    value3;
	
	//��ȡskill_zhudong�����ļ�
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
				return -3;
			}
			while(curNode != NULL)
			{
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{
					cTem= xmlNodeGetContent(curNode);
					id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					name=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect"))
				{
					cTem= xmlNodeGetContent(curNode);
					effect=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"con_time"))
				{
					cTem= xmlNodeGetContent(curNode);
					con_time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cd_time"))
				{
					cTem= xmlNodeGetContent(curNode);
					cd_time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"factor"))
				{
					cTem= xmlNodeGetContent(curNode);
					factor=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"genuine"))
				{
					cTem= xmlNodeGetContent(curNode);
					genuine=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"nggjjdz_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					nggjjdz_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wggjjdz_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					wggjjdz_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ngfyjdz_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					ngfyjdz_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wgfyjdz_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					wgfyjdz_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"mzjd_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					mzjd_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"jdrx_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					jdrx_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"jdsb_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					jdsb_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"jdbj_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					jdbj_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cxdx_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					cxdx_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time_sec"))
				{
					cTem= xmlNodeGetContent(curNode);
					time_sec=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time_usec"))
				{
					cTem= xmlNodeGetContent(curNode);
					time_usec=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"attack_type"))
				{
					cTem= xmlNodeGetContent(curNode);
					attack_type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"attack_range"))
				{
					cTem= xmlNodeGetContent(curNode);
					attack_range=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"genuine_growup"))
				{
					cTem= xmlNodeGetContent(curNode);
					genuine_growup=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"factor_growup"))
				{
					cTem= xmlNodeGetContent(curNode);
					factor_growup=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect_growup"))
				{
					cTem= xmlNodeGetContent(curNode);
					effect_growup=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"control_grade"))
				{
					cTem= xmlNodeGetContent(curNode);
					control_grade=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value1"))
				{
					cTem= xmlNodeGetContent(curNode);
					value1=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value2"))
				{
					cTem= xmlNodeGetContent(curNode);
					value2=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value3"))
				{
					cTem= xmlNodeGetContent(curNode);
					value3=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Skill_Configuration *skill;
					skill = new Skill_Configuration(id,name,type,effect,con_time,cd_time,factor,
													genuine,time_sec,time_usec,nggjjdz_debuff,wggjjdz_debuff,
													ngfyjdz_debuff,wgfyjdz_debuff,mzjd_debuff,jdrx_debuff,jdsb_debuff,
													jdbj_debuff,cxdx_debuff,attack_type,attack_range,effect_growup,
													genuine_growup,factor_growup,control_grade,value1,value2,value3);
					id_to_skill[id] = skill;
				}
				curNode=curNode->next;	
			}
			
				
		curnow=curnow->next;
	}
	////cout<<"####################################################################"<<endl;
	////cout<<"the size of lists is :"<<id_to_skill.size()<<endl;
	////cout<<"####################################################################"<<endl;
	xmlFreeDoc(doc);
	return 0;	
}

int read_files_yiliao(char * fileName) //ҽ�����͵ļ��ܻ������ݵĶ�ȡ  evan add 2012.5.25
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);	
	string id;           		//����Id
	string name;         		//��������
	int    type;				//��������  ��1��������2��������3��debuff��4��buff��5��ҽ�ƣ���
	int    effect;              //���ܸ���Ч��
	int    con_time;            //Ч������ʱ��
	int    cd_time;             //����cd����ȴʱ�䣩
	int	   factor;              //����ϵ������ֵ
	int    genuine;             //��������
	int	   time_sec;            //���ܶ�������ʱ�䣨�룩
	int    time_usec;           //���ܶ�������ʱ�䣨΢�룩
	int    cure_type;           //ҽ����ʽ��1������ҽ�ƣ�2��Ⱥ��ҽ��	
	int	   factor_growup;		//����ϵ���ɳ����� 
	int    control_grade;		//�ȼ�����
	int    value1;
	int    value2;
	int    value3;
	//��ȡskill_yiliao�����ļ�
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
				return -3;
			}
			while(curNode != NULL)
			{
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{
					cTem= xmlNodeGetContent(curNode);
					id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					name=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect"))
				{
					cTem= xmlNodeGetContent(curNode);
					effect=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"con_time"))
				{
					cTem= xmlNodeGetContent(curNode);
					con_time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time_cd"))
				{
					cTem= xmlNodeGetContent(curNode);
					cd_time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"factor"))
				{
					cTem= xmlNodeGetContent(curNode);
					factor=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"genuine"))
				{
					cTem= xmlNodeGetContent(curNode);
					genuine=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cure_type"))
				{
					cTem= xmlNodeGetContent(curNode);
					cure_type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time_sec"))
				{
					cTem= xmlNodeGetContent(curNode);
					time_sec=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time_usec"))
				{
					cTem= xmlNodeGetContent(curNode);
					time_usec=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"factor_growup"))
				{
					cTem= xmlNodeGetContent(curNode);
					factor_growup=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"control_grade"))
				{
					cTem= xmlNodeGetContent(curNode);
					control_grade=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value1"))
				{
					cTem= xmlNodeGetContent(curNode);
					value1=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value2"))
				{
					cTem= xmlNodeGetContent(curNode);
					value2=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value3"))
				{
					cTem= xmlNodeGetContent(curNode);
					value3=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Skill_Configuration *skill;
					skill = new Skill_Configuration(id,name,type,effect,con_time,cd_time,factor,genuine,
							time_sec,time_usec,cure_type,factor_growup,control_grade,value1);
					id_to_skill[id] = skill;
				}
				curNode=curNode->next;	
			}		
		curnow=curnow->next;
	}
	////cout<<"####################################################################"<<endl;
	////cout<<"the size of lists is :"<<id_to_skill.size()<<endl;
	////cout<<"####################################################################"<<endl;
	xmlFreeDoc(doc);
	return 0;	
}

int read_files_buff(char * fileName) //buff���͵ļ��ܻ������ݵĶ�ȡ  evan add 2012.5.25
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);	
	string id;           		//����Id
	string name;         		//��������
	int    type;				//��������  ��1��������2��������3��debuff��4��buff��5��ҽ�ƣ���
	int    effect;              //���ܸ���Ч��
	int    cd_time;             //����cd����ȴʱ�䣩
	int    genuine;             //��������
	int   zjngshbfb_buff;        //buff�����ڹ��˺�
	int   zjwgshbfb_buff;        //buff�����⹦�˺�
	int   zjsmsx_buff;        	 //buff������������
	int   ftsh_buff;             //�����˺�
	int   smxh_buff;       		 //��������
	int   xxl_buff;              //��Ѫ��
	int   cxsjcz_buff;           //����ʱ���ֵ
	int	  consumer_growth;		 //�������ĳɳ�����
	int   cxsjcz_growup_buff;	 //���ܳ���ʱ��ɳ�����
	int   cd_growup_buff;		 //����CD�ɳ�����      
	int   xg_growup_buff;		 //����Ч���ɳ�
	int    control_grade;		//�ȼ�����
	int    value1;
	int    value2;
	int    value3;
	//��ȡskill_yiliao�����ļ�
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
				return -3;
			}
			while(curNode != NULL)
			{
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{
					cTem= xmlNodeGetContent(curNode);
					id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					name=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect"))
				{
					cTem= xmlNodeGetContent(curNode);
					effect=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"genuine"))
				{
					cTem= xmlNodeGetContent(curNode);
					genuine=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cd_time"))
				{
					cTem= xmlNodeGetContent(curNode);
					cd_time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"zjngshbfb_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					zjngshbfb_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"zjwgshbfb_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					zjwgshbfb_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"zjsmsx_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					zjsmsx_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ftsh_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					ftsh_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"smxh_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					smxh_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"xxl_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					xxl_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cxsjcz_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					cxsjcz_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"consumer_growth"))
				{
					cTem= xmlNodeGetContent(curNode);
					consumer_growth=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cxsjcz_growup_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					cxsjcz_growup_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cd_growup_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					cd_growup_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"xg_growup_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					xg_growup_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"control_grade"))
				{
					cTem= xmlNodeGetContent(curNode);
					control_grade=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value1"))
				{
					cTem= xmlNodeGetContent(curNode);
					value1=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value2"))
				{
					cTem= xmlNodeGetContent(curNode);
					value2=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value3"))
				{
					cTem= xmlNodeGetContent(curNode);
					value3=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Skill_Configuration *skill;
					skill = new Skill_Configuration(id,name,type,effect,cd_time,genuine,zjngshbfb_buff,
							zjwgshbfb_buff,zjsmsx_buff,ftsh_buff,smxh_buff,xxl_buff,cxsjcz_buff,
							consumer_growth,cxsjcz_growup_buff,cd_growup_buff,xg_growup_buff,control_grade);
					id_to_skill[id] = skill;
				}
				curNode=curNode->next;	
			}		
		curnow=curnow->next;
	}
	//cout<<"####################################################################"<<endl;
	//cout<<"the size of lists is :"<<id_to_skill.size()<<endl;
	//cout<<"####################################################################"<<endl;
	xmlFreeDoc(doc);
	return 0;
}

int read_files_beidong(char * fileName) //�������͵ļ��ܻ������ݵĶ�ȡ  evan add 2012.5.25
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);	
	string id;           		//����Id
	string name;         		//��������
	int    type;				//��������  ��1��������2��������3��debuff��4��buff��5��ҽ�ƣ���
	int    effect;              //���ܸ���Ч��
	int    smsxjdz_bd;          //������������
	int    wgshbfb_bd;          //�����⹦�˺�
	int    wggjbfb_bd;          //�����⹦����
	int    nggjbfb_bd;          //�����ڹ�����
	int    wgfybfb_bd;          //�����⹦����
	int    ngfybfb_bd;          //�����ڹ�����
	int    mzjdz_bd;            //��������
	int    bjjdz_bd;            //���ӱ���
	int    sbjdz_bd;            //��������
	int    rxjdz_bd;            //��������
	int    fjxgcs_growup_bd;	//����Ч������ֵ�ɳ�����
	int    control_grade;		//�ȼ�����
	int    value1;
	int    value2;
	int    value3;
	//��ȡskill_yiliao�����ļ�
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
				return -3;
			}
			while(curNode != NULL)
			{
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{
					cTem= xmlNodeGetContent(curNode);
					id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					name=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect"))
				{
					cTem= xmlNodeGetContent(curNode);
					effect=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"smsxjdz_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					smsxjdz_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wgshbfb_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					wgshbfb_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wggjbfb_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					wggjbfb_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"nggjbfb_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					nggjbfb_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wgfybfb_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					wgfybfb_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ngfybfb_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					ngfybfb_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"mzjdz_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					mzjdz_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"bjjdz_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					bjjdz_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"sbjdz_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					sbjdz_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"rxjdz_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					rxjdz_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"fjxgcs_growup_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					fjxgcs_growup_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"control_grade"))
				{
					cTem= xmlNodeGetContent(curNode);
					control_grade=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value1"))
				{
					cTem= xmlNodeGetContent(curNode);
					value1=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value2"))
				{
					cTem= xmlNodeGetContent(curNode);
					value2=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value3"))
				{
					cTem= xmlNodeGetContent(curNode);
					value3=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Skill_Configuration *skill;
					skill = new Skill_Configuration(id,name,type,effect,smsxjdz_bd,wgshbfb_bd,wggjbfb_bd,
							nggjbfb_bd,wgfybfb_bd,ngfybfb_bd,mzjdz_bd,bjjdz_bd,sbjdz_bd,
							rxjdz_bd,fjxgcs_growup_bd,control_grade);
					id_to_skill[id] = skill;
				}
				curNode=curNode->next;	
			}		
		curnow=curnow->next;
	}
	//cout<<"####################################################################"<<endl;
	//cout<<"the size of lists is :"<<id_to_skill.size()<<endl;
	//cout<<"####################################################################"<<endl;
	xmlFreeDoc(doc);
	return 0;	
}
