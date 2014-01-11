#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"data_structure_struct.h"
#include"hero_configuration.h"
#include"hatValRue.h"
extern HatValRue *hatValRue;  

int read_files_hatValRue(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	strcpy(szDocName,fileName);
	//��ȡHatValRue�����ļ�
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
	
	curNode=curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_hero;
	double hatInRag;       //�����޷�Χʱ��ֵ
	double genHitPer;      //��ͨ�������ֵ��������
	double sklHitPer;		//�˺����ܳ��ֵ��������
	double proLosPer;		//���漼�ܳ��ֵ��������
	double friHitGan;       //��һ�ι������ֵ
	double chageAir;        //ת��Ŀ���ޱ���
	double hatUpVal;         //��ֵ����ֵ
	double redueValPer;      //�ﵽ�������ʱ�������������
	int hatRage;              //��޷�Χ
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"hatValRul"))
		{
			propNodePtr_hero=curNode;
			xmlAttrPtr attrPtr=propNodePtr_hero->properties;
			while(attrPtr!=NULL)
			{	
				//ȡ�������޷�Χʱ��ֵ������
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hatInRag"))
				{					
					xmlChar *_hatInRag=xmlGetProp(propNodePtr_hero,(const xmlChar*)"hatInRag");
					hatInRag=atof(reinterpret_cast<const char *>(_hatInRag));
					xmlFree(_hatInRag);
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"genHitPer"))
				{					
					xmlChar *_genHitPer=xmlGetProp(propNodePtr_hero,(const xmlChar*)"genHitPer");
					genHitPer=atof(reinterpret_cast<const char *>(_genHitPer));
					xmlFree(_genHitPer);
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"sklHitPer"))
				{
					xmlChar *_sklHitPer=xmlGetProp(propNodePtr_hero,(const xmlChar*)"sklHitPer");
					sklHitPer=atof(reinterpret_cast<const char *>(_sklHitPer));
					xmlFree(_sklHitPer);
				}
			
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"proLosPer"))
				{
					xmlChar *_proLosPer=xmlGetProp(propNodePtr_hero,(const xmlChar*)"proLosPer");
					proLosPer=atof(reinterpret_cast<const char *>(_proLosPer));
					xmlFree(_proLosPer);
					
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"friHitGan"))
				{
					xmlChar *_friHitGan=xmlGetProp(propNodePtr_hero,(const xmlChar*)"friHitGan");
					friHitGan=atof(reinterpret_cast<const char *>(_friHitGan));
					xmlFree(_friHitGan);
				}
			
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"chageAir"))
				{
					xmlChar *_chageAir=xmlGetProp(propNodePtr_hero,(const xmlChar*)"chageAir");
					chageAir=atof(reinterpret_cast<const char *>(_chageAir));
					xmlFree(_chageAir);
				}
			
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hatUpVal"))
				{
					xmlChar *_hatUpVal=xmlGetProp(propNodePtr_hero,(const xmlChar*)"hatUpVal");
					hatUpVal=atof(reinterpret_cast<const char *>(_hatUpVal));
					xmlFree(_hatUpVal);
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"redueValPer"))
				{
					xmlChar *_redueValPer=xmlGetProp(propNodePtr_hero,(const xmlChar*)"redueValPer");
					redueValPer=atof(reinterpret_cast<const char *>(_redueValPer));
					xmlFree(_redueValPer);
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hatRage"))
				{
					xmlChar *_hatRage=xmlGetProp(propNodePtr_hero,(const xmlChar*)"hatRage");
					hatRage=atoi(reinterpret_cast<const char *>(_hatRage));
					xmlFree(_hatRage);		
					hatValRue=new HatValRue(hatInRag,genHitPer,sklHitPer,proLosPer,friHitGan,chageAir,hatUpVal,redueValPer,hatRage);
					break;
				}
				attrPtr=attrPtr->next;				
			}
			break;
		}
		curNode=curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
