/************************************************************
	�ļ�����boxAsist.h
	�ļ����ã�����Ź��������ܺ���
	���ߣ�chenzhen
	�������ڣ�2012.11.15
************************************************************/
#ifndef BOX_ASIST_H
#define BOX_ASIST_H
#include"wholeDefine.h"
#include<string.h>
#include<string>
#include<map>
#include<set>
#include<iostream>
using namespace std;

/*�Ź����ȡ����*/
#define HERO_STYLE_TYPE			0
#define MONSTER_STYLE_TYPE		1
#define PET_STYLE_TYPE			2
#define WAGON_STYLE_TYPE		3
#define BOTTLE_STYLE_TYPE		4
#define TAKEGOODS_STYLE_TYPE	5
#define PICK_STYLE_TYPE			6
#define DROP_EQUIP_STYLE_TYPE	7
#define TRAP_STYLE_TYPE			8
#define STATUARY_STYLE_TYPE		9

class Map_Inform;
class Hero;

typedef struct StyObj
{
	char objId[SHOR_MID_VALUE_LENGTH + 1];
	int type;
	StyObj(char *_objId,int _type)
	{
		memset(objId,'\0',SHOR_MID_VALUE_LENGTH + 1);
		strncpy(objId,_objId,strlen(_objId));
		type = _type;
	}
}StyObj;


typedef struct OneScreen_S {
	set<string> heroSet;			//heroId����
	set<string> monsterSet;			//����Id����
	set<string> petSet;				//����ID����
	set<string> wagonSet;			//��Id����
	set<string> bottleSet;			//ƿ�ӹ���
	set<string> takeSet;			//�ɼ���
	set<string> pickSet;			//������
	set<string> dropEqpSet;			//dropEqp
	set<string> trapSet;			//trap
	set<string> statuarySet;		//statuary

}OneScreen;

inline bool isValidType(int _type)
{
	if(_type < HERO_STYLE_TYPE || _type > STATUARY_STYLE_TYPE)
	{
		return false;
	}
	return true;
	
}

inline bool ScreenDel(OneScreen & screen, StyObj &obj)
{
	set<string> *p = (set<string>*) &screen;
	if (!isValidType(obj.type))
	{
		return false;
	}
	set<string> *temp = p + obj.type;
	if (temp->find(obj.objId) == temp->end())
	{
		return false;
	}
	temp->erase(obj.objId);
	return true;
}

inline bool ScreenInsert(OneScreen & screen, StyObj &obj)
{
//	cout<<"ScreenInsert begin obj.objId:"<<obj.objId<<endl;
	set<string> *p = (set<string>*) &screen;
	if (!isValidType(obj.type))
	{
		return false;
	}
//	cout<<"ScreenInsert front obj.type:"<<obj.type<<endl;
	set<string> *temp = p + obj.type;
	if (temp->find(obj.objId) != temp->end())
	{
		return false;
	}
//	cout<<"ScreenInsert back obj.type:"<<obj.type<<endl;
	
	temp->insert(obj.objId);
//	cout<<"ScreenInsert end obj.objId:"<<obj.objId<<endl;
	return true;
}

inline void ScreenPrint(OneScreen & screen)
{
	set<string> *p = (set<string>*) &screen;
	set<string> *temp;
	set<string>::iterator it;
	for (int i = 0; i < 10; i++)
	{
		temp = p + i;
		cout<<"type is "<<i<<endl;
		for (it = temp->begin(); it != temp->end(); it++)
		{
			cout<<"id is "<<*it<<endl;
		}
	}
}

inline void ScreenClear(OneScreen & screen)
{
	set<string> *p = (set<string>*) &screen;
	set<string> *temp;
	set<string>::iterator it;
	for (int i = 0; i < 10; i++)
	{
		temp = p + i;
		temp->clear();
	}
}

/*�жϷ���Ź���������Ƿ���ȷ*/
bool isStyObjTpe(int _type);

/*��Ϣ������*/
class SendMsgClass
{
	public:
		/*��װ����Ϣ���ͺ������ԾŹ�����*/
		static void sentBoxMsg(set<string> &nbox_id_set,char *msg,char *heroId = NULL);	
		
		/*ȫ��ͼ������Ϣ*/
		static void sendMapMsg(Map_Inform *map_now,char *msg,int fd = -1);		
		//�����ŵ�ͼ�Ľ�ɫ��Ϣ���͸�ָ����fd
		static void sendMapMsg(Map_Inform *map_now, int fd);
		
		/*��װ����Ϣ���ͺ������ԾŹ�����,Ϊ�໥������,��Ҫ������ҵ���Ϣ����*/
		static void sentBoxViewMsg(OneScreen &nbox_id_set,\
					char *msg,Map_Inform *map_now,Hero *myHero,int style);
};
#endif