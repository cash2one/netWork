/****************************************************************
 * Filename: read_dirty_words.cpp
 * 
 * Description: ��ȡ�Ƿ��ʻ�
 *
 * Original Author : bison, 2012-10-11
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

extern set<string> dirtyWordsPack;					//��ʿ�
extern set<string> illegalCharPack;					//�����Ƿ�����

int read_dirty_words(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//���ڵ�
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//�ڵ�����ֵ
	char szDocName[50]={0};
	xmlChar *cTem;						//���ֵ

	string dirty;						//���
	string illegal;						//�Ƿ��ַ�

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
	
	illegalCharPack.clear();
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"illegality"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//��ȡ���
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"illegalityChat"))
				{
					cTem = xmlNodeGetContent(thirdNode);
					dirty = const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				
				}
				//��ȡ�����Ƿ��ַ�
				else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"illegalityName"))
				{
					cTem = xmlNodeGetContent(thirdNode);
					illegal = const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
					illegalCharPack.insert(illegal);
				}
			}
			
		}
	}
	
	dirtyWordsPack.clear();
	int pos = 0;
	string oneDirtyWords;
	while (!dirty.empty())
	{
		pos = dirty.find(',');
		if (pos == -1)
		{
			//��ֹ���һ��û�Ӷ���
			oneDirtyWords = dirty;
			dirty = "";
		} else {
			oneDirtyWords = dirty.substr(0, pos);
			dirty = dirty.substr(pos + 1);
		}
		dirtyWordsPack.insert(oneDirtyWords);
	}
	
	// cout<<"BisonTest: the dirty dictionary has "<<dirtyWordsPack.size()<<" dirty words"<<endl;
	// cout<<"BisonTest: @read_dirty_words.cpp: "<<"illegalChars size is "<<illegalCharPack.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}