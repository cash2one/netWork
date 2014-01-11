/****************************************************************
 * Filename: read_ectype_reward_info.cpp
 * 
 * Description: ��������������Ϣ�Ķ�ȡ
 *
 * Original Author : bison, 2012-6-13
 *
 ****************************************************************/
 
#include"ectype_reward_info.h"
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<sstream>
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

//����������Ʒ��ȫ����
extern map<string, vector<string> > type_2_goodsList;
//������Ϣ��ȫ�ֱ���
extern map<string, Ectype_Reward_Info*> idNum_2_rewardInfo;

int read_ectype_reward_info(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ

	char ectypeId[51];					//�������ID
	int heroSkillExp;					//���＼�ܵ�
	int petSkillExp;					//���＼�ܵ�
	int exp;							//������������
	int money;							//����������Ǯ
	int silver;							//������������
	int useGold;
	char typeId[51];					//��Ʒ����id
	double vipRate[50] = {0.0};			//vip����
	int rateIndex;

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
		//�����ȡ�ȼ��ڵ�
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"EctypeReward"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					//��ȡ�������ID
					xmlChar *_ectypeId = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(ectypeId, const_cast<char *>(reinterpret_cast<const char *>(_ectypeId)), 51);
					xmlFree(_ectypeId);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"goldRate")) {
					//Ԫ��ˢ�µȼ�
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"goldRate");
					useGold = atoi(reinterpret_cast<const char*>(_item));
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"pelSkill")) {
					//���＼�ܵ�
					xmlChar *_exp = xmlGetProp(secondNode, (const xmlChar*)"pelSkill");
					heroSkillExp = atoi(reinterpret_cast<const char*>(_exp));
					xmlFree(_exp);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"skill")) {
					//���ܵ�
					xmlChar *_exp = xmlGetProp(secondNode, (const xmlChar*)"skill");
					petSkillExp = atoi(reinterpret_cast<const char*>(_exp));
					xmlFree(_exp);
				}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"exp")) {
					//����ֵ
					xmlChar *_exp = xmlGetProp(secondNode, (const xmlChar*)"exp");
					exp = atoi(reinterpret_cast<const char*>(_exp));
					xmlFree(_exp);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money")) {
					//�����İ󶨽�Ǯֵ
					xmlChar *_money = xmlGetProp(secondNode, (const xmlChar*)"money");
					money = atoi(reinterpret_cast<const char*>(_money));
					xmlFree(_money);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"silver")) {
					//�ǰ󶨵Ľ�Ǯֵ
					xmlChar *_silver = xmlGetProp(secondNode, (const xmlChar*)"silver");
					silver = atoi(reinterpret_cast<const char*>(_silver));
					xmlFree(_silver);
				}
			}
			Ectype_Reward_Info *rewardInfo = new Ectype_Reward_Info(ectypeId, heroSkillExp, petSkillExp, exp, money, silver, useGold);
			
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//��ڵ��ȡ��Ʒ������
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"item"))
				{
					rateIndex = 0;
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrncmp(attrPtr->name, (const xmlChar*)"vip", 3))
						{
							//��ȡ��Ʒ����vip����
							xmlChar *_rate = xmlGetProp(thirdNode, attrPtr->name);
							vipRate[rateIndex++] = atof((char*)_rate);
							xmlFree(_rate);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"typeId")) {
							//��ȡ��Ʒ����
							xmlChar *_typeId = xmlGetProp(thirdNode, (const xmlChar*)"typeId");
							strncpy(typeId, (char*)_typeId, 51);
							xmlFree(_typeId);
						}
					}
					
					// cout<<"rateIndex is     "<<rateIndex<<endl;
					//��ͷ��������
					// rewardInfo->addOneRewardItem(typeId, rateIndex, vipRate[0], vipRate[1], vipRate[2], vipRate[3], vipRate[4], vipRate[5], vipRate[6], vipRate[7], vipRate[8], vipRate[9], vipRate[10], vipRate[11], vipRate[12], vipRate[13], vipRate[14], vipRate[15], vipRate[16], vipRate[17], vipRate[18], vipRate[19], vipRate[20], vipRate[21], vipRate[22], vipRate[23], vipRate[24], vipRate[25], vipRate[26], vipRate[27], vipRate[28], vipRate[29], vipRate[30], vipRate[31], vipRate[32], vipRate[33], vipRate[34], vipRate[35], vipRate[36], vipRate[37], vipRate[38], vipRate[39], vipRate[40], vipRate[41], vipRate[42], vipRate[43], vipRate[44], vipRate[45], vipRate[46], vipRate[47],vipRate[48], vipRate[49]);
					rewardInfo->addOneReward(typeId, rateIndex, vipRate);
				}
			}
			idNum_2_rewardInfo.insert(pair<string, Ectype_Reward_Info*>(ectypeId, rewardInfo));
		}	
	}
	xmlFreeDoc(doc);
	
	
	//���Ը�������
	// map<string, Ectype_Reward_Info*>::iterator it_test;
	// it_test = idNum_2_rewardInfo.find("001_0");
	// Ectype_Reward_Info* reward = it_test->second;
	// reward->testData();
	
	return 0;
}