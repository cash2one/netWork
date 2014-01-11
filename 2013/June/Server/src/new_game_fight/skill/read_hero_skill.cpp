/****************************************************************
 * Filename: read_hero_skill.cpp
 * 
 * Description: ��ȡ���＼������
 *
 * Original Author : bison, 2012-11-14
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "hero_skill.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;
extern map<string, HeroSkill*> skillId_2_heroSkill;		//��ɫ����
HeroMemSkill_T M_SkillBase[HERO_SKILL_MAX_NUM];
HeroMemSkill_T H_SkillBase[HERO_SKILL_MAX_NUM];
HeroMemSkill_T G_SkillBase[HERO_SKILL_MAX_NUM];
HeroMemSkill_T X_SkillBase[HERO_SKILL_MAX_NUM];

int read_hero_skill(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ
	HeroSkill_T tempSkill;				//��������
	unsigned level = 0;
	
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
	
	skillId_2_heroSkill.clear();
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"skill"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					//���＼��ID
					xmlChar *_skillId = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(tempSkill.skillId, (char*)_skillId, sizeof (tempSkill.skillId));
					xmlFree(_skillId);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"type")) {
					//���＼������
					xmlChar *_type = xmlGetProp(secondNode, (const xmlChar*)"type");
					tempSkill.type = atoi((char*)_type);
					xmlFree(_type);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"buffType")) {
					//���ܸ���buff����
					xmlChar *_buffType = xmlGetProp(secondNode, (const xmlChar*)"buffType");
					tempSkill.buffType = atoi((char*)_buffType);
					xmlFree(_buffType);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"attackDistance")) {
					//���ܹ�����Χ
					xmlChar *_attackRange = xmlGetProp(secondNode, (const xmlChar*)"attackDistance");
					tempSkill.attackRange = atoi((char*)_attackRange);
					xmlFree(_attackRange);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hurtRange")) {
					//�����˺���Χ
					xmlChar *_attackRange = xmlGetProp(secondNode, (const xmlChar*)"hurtRange");
					tempSkill.hurtRange = atoi((char*)_attackRange);
					xmlFree(_attackRange);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"animationTime")) {
					//���ܶ���ʱ��
					xmlChar *_animationTime = xmlGetProp(secondNode, (const xmlChar*)"animationTime");
					tempSkill.animationTime = atof((char*)_animationTime);
					xmlFree(_animationTime);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"partyFactor")) {
					//�����˺�ϵ�����չ�ϵ����
					xmlChar *_partyFactor = xmlGetProp(secondNode, (const xmlChar*)"partyFactor");
					tempSkill.partyFactor = atof((char*)_partyFactor);
					xmlFree(_partyFactor);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"attkType")) {
					//��������
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"attkType");
					tempSkill.attkType = atoi((char*)_item);
					xmlFree(_item);
				}
			}
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//��ȡ���ܵȼ�Ӱ����
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"upgrade"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"level")) {
							//���ܵȼ�
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"level");
							level = atoi((char*)_item);
							if (level > 20)
							{
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								cout<<"the config of hero skill"<<tempSkill.skillId<<" is error"<<endl;
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								return -1;
							}
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"heroLevel")) {
							//����������Ҫ������ȼ�
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"heroLevel");
							tempSkill.upgradeNeedHeroLevel[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needMoney")) {
							//����������Ҫ�Ľ�Ǯ
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"needMoney");
							tempSkill.upgradeNeedMoney[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needExp")) {
							//����������Ҫ�ľ���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"needExp");
							tempSkill.upgradeNeedExp[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"cdTime")) {
							//����CDʱ��
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"cdTime");
							tempSkill.cdTime[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"magic")) {
							//���ܺ�ħ
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"magic");
							tempSkill.needMagic[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"skillFactor")) {
							//�����˺�ϵ��
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"skillFactor");
							tempSkill.factor[level - 1] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"value")) {
							//������ֵ
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"value");
							tempSkill.value[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"value1")) {
							//���ܸ�������ֵ
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"value1");
							tempSkill.totalVal[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"value2")) {
							//���ܸ�������ֵ
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"value2");
							tempSkill.attkNum[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						}
					}
				}
			}
			HeroSkill *heroSkill = new HeroSkill(tempSkill);
			skillId_2_heroSkill.insert(pair<string, HeroSkill*>(tempSkill.skillId, heroSkill));
			
		}
	}
	
	// cout<<"[BisonShow]@read_hero_skill.cpp all heroSkill size is "<<skillId_2_heroSkill.size()<<endl;
	for (int i = 0; i < HERO_SKILL_MAX_NUM; i++)
	{
		memset(M_SkillBase, 0, sizeof(M_SkillBase));
		sprintf(M_SkillBase[i].skillId, "M%03d", i);
		M_SkillBase[i].level = 0;
		memset(H_SkillBase, 0, sizeof(H_SkillBase));
		sprintf(H_SkillBase[i].skillId, "H%03d", i);
		H_SkillBase[i].level = 0;
		memset(G_SkillBase, 0, sizeof(G_SkillBase));
		sprintf(G_SkillBase[i].skillId, "G%03d", i);
		G_SkillBase[i].level = 0;
		memset(X_SkillBase, 0, sizeof(X_SkillBase));
		sprintf(X_SkillBase[i].skillId, "X%03d", i);
		X_SkillBase[i].level = 0;
		// cout<<"init one skillId and skillId is "<<X_SkillBase[i].skillId<<endl;
		
	}
	xmlFreeDoc(doc);
	return 0;
}
