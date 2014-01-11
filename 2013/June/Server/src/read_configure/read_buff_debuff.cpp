/****************************************************************
 * Filename: read_buff_debuff.cpp
 * 
 * Description: ��ȡ����buff��debuff
 *
 * Original Author : bison, 2012-12-10
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "buff_debuff.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

map<string, Buff_debuff_conf_T*> buf_debuf_conf;	//buff��debuff������

int read_buff_debuff(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ

	char skillId[51] = {0};
	int effect = 0;
	int lastTimeBase = 0;
	int lastTimeFactor = 0;
	int effectBase = 0;
	int effectIncFactor = 0;
	
	//�����ļ�
	strcpy(szDocName, fileName);
	doc = xmlReadFile(szDocName, "UTF-8", XML_PARSE_RECOVER);
	if (doc == NULL)
	{
		return -1;
	}

	//�õ�xml�ļ���root
	rootNode = xmlDocGetRootElement(doc);
	if (rootNode == NULL)
	{
		xmlFreeDoc(doc);
		return -1;
	}
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"debuff"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//��ȡһ��debuff��
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"skillId"))
						{	
							//��Ӧ�ļ���ID
							xmlChar *_skillId = xmlGetProp(thirdNode, (const xmlChar*)"skillId");
							strncpy(skillId, const_cast<char *>(reinterpret_cast<const char *>(_skillId)), 51);
							xmlFree(_skillId);
						}else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effect")) {
							//debuffЧ�����
							xmlChar *_effect = xmlGetProp(thirdNode, (const xmlChar*)"effect");
							effect = atoi(reinterpret_cast<const char*>(_effect));
							xmlFree(_effect);
						}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lastTimeBase")) {
							//����ʱ�����
							xmlChar *_lastTimeBase = xmlGetProp(thirdNode, (const xmlChar*)"lastTimeBase");
							lastTimeBase = atoi(reinterpret_cast<const char*>(_lastTimeBase));
							xmlFree(_lastTimeBase);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lastTimeFactor")) {
							//����ʱ��ϵ��
							xmlChar *_lastTimeFactor = xmlGetProp(thirdNode, (const xmlChar*)"lastTimeFactor");
							lastTimeFactor = atoi(reinterpret_cast<const char*>(_lastTimeFactor));
							xmlFree(_lastTimeFactor);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effectBase")) {
							//debuff���û���
							xmlChar *_effectBase = xmlGetProp(thirdNode, (const xmlChar*)"effectBase");
							effectBase = atoi(reinterpret_cast<const char*>(_effectBase));
							xmlFree(_effectBase);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effectIncFactor")) {
							//debuff����ϵ��
							xmlChar *_effectIncFactor = xmlGetProp(thirdNode, (const xmlChar*)"effectIncFactor");
							effectIncFactor = atoi(reinterpret_cast<const char*>(_effectIncFactor));
							xmlFree(_effectIncFactor);
						}
					}
					Buff_debuff_conf_T *debuff = new Buff_debuff_conf_T(skillId, effect, lastTimeBase,
						lastTimeFactor, effectBase, effectIncFactor);
					buf_debuf_conf.insert(pair<string, Buff_debuff_conf_T*>(skillId, debuff));
				}		
			}	
		} else if (!xmlStrcmp(secondNode->name, (const xmlChar*)"buff"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//��ȡһ��debuff��
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"skillId"))
						{	
							//��Ӧ�ļ���ID
							xmlChar *_skillId = xmlGetProp(thirdNode, (const xmlChar*)"skillId");
							strncpy(skillId, const_cast<char *>(reinterpret_cast<const char *>(_skillId)), 51);
							xmlFree(_skillId);
						}else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effect")) {
							//buffЧ�����
							xmlChar *_effect = xmlGetProp(thirdNode, (const xmlChar*)"effect");
							effect = atoi(reinterpret_cast<const char*>(_effect));
							xmlFree(_effect);
						}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lastTimeBase")) {
							//����ʱ�����
							xmlChar *_lastTimeBase = xmlGetProp(thirdNode, (const xmlChar*)"lastTimeBase");
							lastTimeBase = atoi(reinterpret_cast<const char*>(_lastTimeBase));
							xmlFree(_lastTimeBase);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lastTimeFactor")) {
							//����ʱ��ϵ��
							xmlChar *_lastTimeFactor = xmlGetProp(thirdNode, (const xmlChar*)"lastTimeFactor");
							lastTimeFactor = atoi(reinterpret_cast<const char*>(_lastTimeFactor));
							xmlFree(_lastTimeFactor);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effectBase")) {
							//buff���û���
							xmlChar *_effectBase = xmlGetProp(thirdNode, (const xmlChar*)"effectBase");
							effectBase = atoi(reinterpret_cast<const char*>(_effectBase));
							xmlFree(_effectBase);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effectIncFactor")) {
							//buff����ϵ��
							xmlChar *_effectIncFactor = xmlGetProp(thirdNode, (const xmlChar*)"effectIncFactor");
							effectIncFactor = atoi(reinterpret_cast<const char*>(_effectIncFactor));
							xmlFree(_effectIncFactor);
						}
					}
					
					Buff_debuff_conf_T *debuff = new Buff_debuff_conf_T(skillId, effect, lastTimeBase,
						lastTimeFactor, effectBase, effectIncFactor);
					// cout<<"[BisonShow] skillId is "<<skillId<<endl;
					buf_debuf_conf.insert(pair<string, Buff_debuff_conf_T*>(skillId, debuff));
					
				}		
			}	
		}
	}
	// cout<<"[BisonShow] buf_debuf_conf size is "<<buf_debuf_conf.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}