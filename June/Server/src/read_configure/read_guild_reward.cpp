/****************************************************************
 * Filename: read_guild_reward.cpp
 * 
 * Description: ��ȡ����������ɳ�����
 *
 * Original Author : bison, 2012-11-20
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "guild.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

map<string, GuildReward_T> id_2_guildReward;		//���ɽ���

int read_guild_reward(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ
	GuildReward_T tempGuildReward;		//���ɽ���
	int guildLevel = 0;
	
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
	
	id_2_guildReward.clear();
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Item"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					//������ID
					xmlChar *_id = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(tempGuildReward.id, (char*)_id, sizeof (tempGuildReward.id));
					xmlFree(_id);
				}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"brandType")) {
					//д��������ʷ�ķ�������
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"brandType");
					tempGuildReward.brandType = atoi((char*)_item);
					xmlFree(_item);		
				}
			}
			
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//��������ȼ��仯
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Level"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"guildLevel")) {
							//���ɵȼ�
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"guildLevel");
							guildLevel = atoi((char*)_item);
							xmlFree(_item);
							if (guildLevel < 1 || guildLevel > 5)
							{
								cout<<"Fuck wellion, you give an error guild reward config!!!"<<endl;
							}
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardGuildGlory")) {
							//�����İ��ɰﹱ
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardGuildGlory");
							tempGuildReward.rewardGuildGlory[guildLevel - 1] = atoi((char*)_item);
							xmlFree(_item);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardGuildExp")) {
							//�������ɾ���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardGuildExp");
							tempGuildReward.rewardGuildExp[guildLevel - 1] = atoi((char*)_item);
							// printf("\taddLife[%d]: %d", level - 1, tempGuildReward.addLife[level - 1]);
							xmlFree(_item);
						}
#if 0						
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardGuildMoney")) {
							//���������ʽ�
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardGuildMoney");
							tempGuildReward.rewardGuildMoney[guildLevel - 1] = atoi((char*)_item);
							// printf("\taddMagic[%d]: %d", level - 1, tempGuildReward.addMagic[level - 1]);
							xmlFree(_item);
						}
#endif						
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardSelfGlory")) {
							//�������˰ﹱ
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardSelfGlory");
							tempGuildReward.rewardSelfGlory[guildLevel - 1] = atoi((char*)_item);
							// printf("\taddOutDef[%d]: %d", level - 1, tempGuildReward.addOutDef[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardSelfExp")) {
							//�����ĸ��˾���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardSelfExp");
							tempGuildReward.rewardSelfExp[guildLevel - 1] = atoi((char*)_item);
							// printf("\taddInDef[%d]: %d", level - 1, tempGuildReward.addInDef[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardSelfMoney")) {
							//�����ĸ��˽�Ǯ
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardSelfMoney");
							tempGuildReward.rewardSelfMoney[guildLevel - 1] = atoi((char*)_item);
							// printf("\taddOutAttack[%d]: %d", level - 1, tempGuildReward.addOutAttack[level - 1]);
							xmlFree(_item);
						}
					}
					// cout<<endl;
				}
			}
			
			id_2_guildReward.insert(pair<string, GuildReward_T>(tempGuildReward.id, tempGuildReward));
			
		}
	}
	
	// cout<<"have read conf by pary size is "<<id_2_guildReward.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}
