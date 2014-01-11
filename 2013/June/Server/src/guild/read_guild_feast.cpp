#include"guild_club.h"
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<sstream>
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

extern map<string, GuildFeastConf_T> feastId_2_feastConf;

int read_guild_feast_info(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;		//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;			//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;				//���ֵ

	char id[51];					//��ϯ����ID
	int cost;					//��ϯ����Ԫ����
	int lastTime;				//��ϯ����ʱ��
	int contb;					//�����߶԰��ɹ��׶�
	int hostMoney;				//�����߻�ý�Ǯֵ
	int hostGlory;				//�����߻�ðﹱֵ
	int hostReputation;			//�����߻������ֵ
	int joinMoney;				//�����߻�ý�Ǯֵ
	int joinGlory;				//�����߻�ðﹱֵ
	int joinReputation;			//�����߻������ֵ

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

	cout<<"jolly: begin read_guild_feast"<<endl;
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		//�����ȡ���ɻ�ڵ�
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Feast"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					//��ϯ����Id
					xmlChar *_id = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);
					xmlFree(_id);
					
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"cost")) {
					//��ϯ����
					xmlChar *_cost = xmlGetProp(secondNode, (const xmlChar*)"cost");
					cost = atoi(reinterpret_cast<const char*>(_cost));
					xmlFree(_cost);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lastTime")) {
					//��ϯ����ʱ��
					xmlChar *_lastTime = xmlGetProp(secondNode, (const xmlChar*)"lastTime");
					lastTime = atoi(reinterpret_cast<const char*>(_lastTime));
					xmlFree(_lastTime);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"contb")) {
					//�����߶԰��ɹ��׶�
					xmlChar *_contb = xmlGetProp(secondNode, (const xmlChar*)"contb");
					contb = atoi(reinterpret_cast<const char*>(_contb));
					xmlFree(_contb);
				}
			}
			
			//��ȡ��ϯ����
			
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"HostReward"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hostMoney"))
						{	
							//�����߻�ý�Ǯֵ
							xmlChar *_hostMoney = xmlGetProp(thirdNode, (const xmlChar*)"hostMoney");
							hostMoney = atoi(reinterpret_cast<const char*>(_hostMoney));
							xmlFree(_hostMoney);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hostGlory")) {
							//�����߻�ðﹱֵ
							xmlChar *_hostGlory = xmlGetProp(thirdNode, (const xmlChar*)"hostGlory");
							hostGlory = atoi(reinterpret_cast<const char*>(_hostGlory));
							xmlFree(_hostGlory);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hostReputation")) {
							//�����߻������ֵ
							xmlChar *_hostReputation = xmlGetProp(thirdNode, (const xmlChar*)"hostReputation");
							hostReputation = atoi(reinterpret_cast<const char*>(_hostReputation));
							xmlFree(_hostReputation);
						}
					}
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"JoinReward"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"joinMoney"))
						{	
							//�����߻�ý�Ǯֵ
							xmlChar *_joinMoney = xmlGetProp(thirdNode, (const xmlChar*)"joinMoney");
							joinMoney = atoi(reinterpret_cast<const char*>(_joinMoney));
							xmlFree(_joinMoney);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"joinGlory")) {
							//�����߻�ðﹱֵ
							xmlChar *_joinGlory = xmlGetProp(thirdNode, (const xmlChar*)"joinGlory");
							joinGlory = atoi(reinterpret_cast<const char*>(_joinGlory));
							xmlFree(_joinGlory);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"joinReputation")) {
							//�����߻������ֵ
							xmlChar *_joinReputation = xmlGetProp(thirdNode, (const xmlChar*)"joinReputation");
							joinReputation = atoi(reinterpret_cast<const char*>(_joinReputation));
							xmlFree(_joinReputation);
						}
					}
				}
			}
			GuildFeastConf_T feastConf(id, cost, lastTime, contb, hostMoney, hostGlory,
				hostReputation, joinMoney, joinGlory, joinReputation);
				
			feastId_2_feastConf.insert(pair<string, GuildFeastConf_T>(id, feastConf));
		}
	}
	cout<<"BisonTest: @read_guild_feast.cpp: "<<feastId_2_feastConf.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}