/****************************************************************
 * Filename: read_ectype_reward_goods.cpp
 * 
 * Description: ����������������Ʒ�����ö�ȡ����
 *
 * Original Author : bison, 2012-6-13
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

//����������Ʒ��ȫ����
extern map<string, vector<string> > type_2_goodsList;

int read_ectype_reward_goods(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ

	char typeId[51];						//��Ʒ����id

	strcpy(szDocName, fileName);
	doc = xmlReadFile(szDocName, "UTF-8", XML_PARSE_RECOVER); //�����ļ�
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Goods"))
		{
			xmlChar *_typeId = xmlGetProp(secondNode, (const xmlChar *)"typeId");
			strncpy(typeId, const_cast<char *>(reinterpret_cast<const char *>(_typeId)), 51);
			xmlFree(_typeId);
			
			//װ������
			cTem = xmlNodeGetContent(secondNode);
			//��Ʒid��
			string GoodsList = const_cast<char *>(reinterpret_cast<const char *>(cTem));
			xmlFree(cTem);
			string oneGoods;					//������Ʒid
			int pos = 0;						//�ָ���λ��
			vector<string> temp;				//��Ʒid�б�
			//�����ļ������ԷֺŸ�������Ʒid����
			while (!GoodsList.empty())
			{
				pos = GoodsList.find(';');
				if (pos == -1)
				{
					//��ֹ���һ��û�ӷֺ�
					oneGoods = GoodsList;
					temp.push_back(oneGoods);
					break;
				}
				oneGoods = GoodsList.substr(0, pos);
				temp.push_back(oneGoods);
				GoodsList = GoodsList.substr(pos + 1);
			}
			type_2_goodsList.insert(pair<string,vector<string> >(typeId, temp));
		}
	}
	xmlFreeDoc(doc);
	/* 
	//���Ը�����Ʒ�������ö�ȡ���
	map<string,vector<string> >::iterator iter;
	//iter = type_2_goodsList.find("white020");
	for (iter = type_2_goodsList.begin(); iter != type_2_goodsList.end(); iter++)
	{
		cout<<iter->first<<endl;
		vector<string> goodsIdSet = iter->second;
		for (int i = 0; i < goodsIdSet.size(); i++)
			cout<<goodsIdSet[i]<<endl;
		cout<<endl;
	}
	*/
	
	return 0;
}