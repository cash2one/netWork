/****************************************************************
 * Filename: read_hero_conf.cpp
 * 
 * Description: ��ȡ����������ɳ�����
 *
 * Original Author : bison, 2012-11-20
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "hero_conf.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

map<string, Hero_Conf_T> party_2_heroConf;		//�����ɵĽ�ɫ����

int read_hero_conf(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ
	Hero_Conf_T tempHeroConf;			//��ɫ����
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
	
	party_2_heroConf.clear();
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"hero"))
		{
			Point tempPt;
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"party"))
				{	
					//����ID
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"party");
					strncpy(tempHeroConf.party, (char*)_item, sizeof (tempHeroConf.party));
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"pt_x")) {
					//������x
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"pt_x");
					tempPt._x = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"pt_y")) {
					//������y
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"pt_y");
					tempPt._y = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"mapId"))
				{	
					//����ͼID
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"mapId");
					strncpy(tempHeroConf.mapId, (char*)_item, sizeof (tempHeroConf.mapId));
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"attkType")) {
					//��������
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"attkType");
					tempHeroConf.attkType = atoi((char*)_item);
					xmlFree(_item);
				}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lifeUpperVal")) {
					//��������
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"lifeUpperVal");
					tempHeroConf.lifeUpperVal = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"magicUpperVal")) {
					//����ħ��
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"magicUpperVal");
					tempHeroConf.magicUpperVal = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"outDef")) {
					//�����
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"outDef");
					tempHeroConf.outDef = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"inDef")) {
					//�ڷ���
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"inDef");
					tempHeroConf.inDef = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"outAttack")) {
					//�⹦����
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"outAttack");
					tempHeroConf.outAttack = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"inAttack")) {
					//�ڹ�����
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"inAttack");
					tempHeroConf.inAttack = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hited")) {
					//����
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"hited");
					tempHeroConf.hited = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"crit")) {
					//����
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"crit");
					tempHeroConf.crit = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"dodge")) {
					//����
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"dodge");
					tempHeroConf.dodge = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"tenacity")) {
					//����
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"tenacity");
					tempHeroConf.tenacity = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"outHurt")) {
					//���˺�
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"outHurt");
					tempHeroConf.outHurt = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"inHurt")) {
					//���˺�
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"inHurt");
					tempHeroConf.inHurt = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"yueliReward")) {
					//���˺�
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"yueliReward");
					tempHeroConf.bornHeroSkillExp = atoi((char*)_item);
					xmlFree(_item);
				}
			}
			//������
			tempHeroConf.bornPt = tempPt;
			// cout<<"************************party:"<<tempHeroConf.party<<"****************************"<<endl;
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//��ȡ�ȼ�Ӱ����
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"level"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lvl")) {
							//���ܵȼ�
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"lvl");
							level = atoi((char*)_item);
							if (level < 1 || level > 200)
							{
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								cout<<"the config of hero conf "<<tempHeroConf.party<<" is error"<<endl;
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								return -1;
							}
							// cout<<"level:"<<level<<endl;
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needExp")) {
							//����������Ҫ����
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"needExp");
							tempHeroConf.upgradeNeedExp[level - 1] = atoi((char*)_item);
							xmlFree(_item);
							// printf("nedExp[%d]: %d", level - 1, tempHeroConf.upgradeNeedExp[level - 1]);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addLife")) {
							//������������
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addLife");
							tempHeroConf.addLife[level - 1] = atoi((char*)_item);
							// printf("\taddLife[%d]: %d", level - 1, tempHeroConf.addLife[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addMagic")) {
							//��������ħ��
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addMagic");
							tempHeroConf.addMagic[level - 1] = atoi((char*)_item);
							// printf("\taddMagic[%d]: %d", level - 1, tempHeroConf.addMagic[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addOutDef")) {
							//���������⹦����
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addOutDef");
							tempHeroConf.addOutDef[level - 1] = atoi((char*)_item);
							// printf("\taddOutDef[%d]: %d", level - 1, tempHeroConf.addOutDef[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addInDef")) {
							//���������ڹ�����
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addInDef");
							tempHeroConf.addInDef[level - 1] = atoi((char*)_item);
							// printf("\taddInDef[%d]: %d", level - 1, tempHeroConf.addInDef[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addOutAttack")) {
							//���������⹦����
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addOutAttack");
							tempHeroConf.addOutAttack[level - 1] = atoi((char*)_item);
							// printf("\taddOutAttack[%d]: %d", level - 1, tempHeroConf.addOutAttack[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addInAttack")) {
							//���������ڹ�����
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addInAttack");
							tempHeroConf.addInAttack[level - 1] = atoi((char*)_item);
							// printf("\taddInAttack[%d]: %d", level - 1, tempHeroConf.addInAttack[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addHited")) {
							//������������
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addHited");
							tempHeroConf.addHited[level - 1] = atoi((char*)_item);
							// printf("\taddHited[%d]: %d", level - 1, tempHeroConf.addHited[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addCrit")) {
							//�������ӱ���
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addCrit");
							tempHeroConf.addCrit[level - 1] = atoi((char*)_item);
							// printf("\taddCrit[%d]: %d", level - 1, tempHeroConf.addCrit[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addDodge")) {
							//������������
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addDodge");
							tempHeroConf.addDodge[level - 1] = atoi((char*)_item);
							// printf("\taddDodge[%d]: %d", level - 1, tempHeroConf.addDodge[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addTenacity")) {
							//������������
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addTenacity");
							tempHeroConf.addTenacity[level - 1] = atoi((char*)_item);
							// printf("\taddTenacity[%d]: %d", level - 1, tempHeroConf.addTenacity[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addOutHurt")) {
							//���������⹦�˺�
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addOutHurt");
							tempHeroConf.addOutHurt[level - 1] = atoi((char*)_item);
							// printf("\taddOutHurt[%d]: %d", level - 1, tempHeroConf.addOutHurt[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addInHurt")) {
							//�������ӵ��ڹ��˺�
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addInHurt");
							tempHeroConf.addInHurt[level - 1] = atoi((char*)_item);
							// printf("\taddInHurt[%d]: %d", level - 1, tempHeroConf.addInHurt[level - 1]);
							xmlFree(_item);
						}
					}
					// cout<<endl;
				}
			}
			party_2_heroConf.insert(pair<string, Hero_Conf_T>(tempHeroConf.party, tempHeroConf));
			
		}
	}
	
	// cout<<"[BisonShow]@read_hero_conf.cpp all heroConf size is "<<sizeof(Hero_Conf_T) * 4<<endl;
	// cout<<"have read conf by pary size is "<<party_2_heroConf.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}
