/************************************************************
	�ļ�����statuaryHero.h
	�ļ����ã�����StatuaryHero��
	���ߣ�chenzhen
	�������ڣ�2013.03.01
************************************************************/

#ifndef STATUARY_HERO_H
#define STATUARY_HERO_H
#include"libev.h"
#include"wholeDefine.h"
#include"data_structure_struct.h"
#include<string>
#include<map>
using namespace std;
class Map_Src;

struct MemStatuaryHero
{
	char vocation[SHOR_MID_VALUE_LENGTH + 1];       //ְҵid
	char photoId[SHOR_MID_VALUE_LENGTH + 1];        //������ɫid
	char heroId[SHOR_MID_VALUE_LENGTH + 1];        //������ɫid
	char mapId[SHOR_MID_VALUE_LENGTH + 1];         //���ڵ�ͼid
	char titleId[SHOR_MID_VALUE_LENGTH + 1];       //�ƺţ���Ϊ����ļ���
	char requre[SHOR_MID_VALUE_LENGTH + 1];        //������ɫrequre,��ӦͼƬid��һ������������Щͷ��
	char heroName[SHOR_MID_VALUE_LENGTH + 1];      //������ɫ�ǳ�
	int lastSeconds;                               //��ʣ������
	int piex_x;                                    //������
	int piex_y;                                    //������
	int level;                                     //��ɫ�ȼ�
	int lifeVal;                                   //����ֵ
	int lifeUpperVal;                              //��������ֵ
	int magicUpperVal;                             //ħ������ֵ
	int magicVal;                                  //ħ��ֵ
	
	
	MemStatuaryHero(char *_heroId,char* _heroName,char *_vocation,int _level,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,\
	int _magicVal,char *_mapId,char *_photoId,char* _titleId,char* _requre,int _lastSeconds,Point _piexPt)
	{
		initMemStatuaryHero();
		strncpy(vocation,_vocation,strlen(_vocation));
		strncpy(photoId,_photoId,strlen(_photoId));
		strncpy(heroId,_heroId,strlen(_heroId));
		strncpy(mapId,_mapId,strlen(_mapId));
		strncpy(titleId,_titleId,strlen(_titleId));
		strncpy(requre,_requre,strlen(_requre));
		strncpy(heroName,_heroName,strlen(_heroName));
		lastSeconds = _lastSeconds;
		piex_x = _piexPt._x;
		piex_y = _piexPt._y;
		level = _level;
		lifeUpperVal = _lifeUpperVal;
		lifeVal = _lifeVal;
		magicUpperVal = _magicUpperVal;
		magicVal = _magicVal;		
	}
		
	void initMemStatuaryHero(void)
	{
		memset(vocation,'\0',sizeof(vocation));
		memset(photoId,'\0',sizeof(photoId));
		memset(heroId,'\0',sizeof(heroId));
		memset(mapId,'\0',sizeof(mapId));
		memset(titleId,'\0',sizeof(titleId));
		memset(requre,'\0',sizeof(requre));
		memset(heroName,'\0',sizeof(heroName));
		lastSeconds = 0;
		piex_x = 0;
		piex_y = 0;
		level = 0;
		lifeUpperVal = 0;
		lifeVal = 0;
		magicUpperVal = 0;
		magicVal = 0;		
	}
};	
	

class StatuaryHero
{
	MemStatuaryHero* memStatuaryHero;               //�ṹ�壬�Ż���	
	Map_Src *map_now;                           //��ͼʵ��ָ��
	ev_timer last_timer;                           //����ʱ���ʱ��
	Point piexPt;								   //��������
	char inSeeMsg[LONG_MID_VALUE_LENGTH + 1];      //������Ϣ
	char outSeeMsg[LONG_MID_VALUE_LENGTH + 1];      //������Ϣ
	
	
	public:
	
	StatuaryHero(MemStatuaryHero* _memStatuaryHero);
	
	/*��ù�����ɫid*/
	char* getHeroId(void);
	
	/*���memStatuaryHero*/
	MemStatuaryHero* getMemStatuaryHero(void);
	
	/*��������*/
	~StatuaryHero(void);
	
	/*����������Ϣ*/
	void formInSeeMsg(void);
	
	/*����������Ϣ*/
	void formOutSeeMsg(void);
	
	/*���������Ϣ*/
	char* getInSeeMsg(void);
	
	/*���������Ϣ*/
	char* getOutSeeMsg(void);
	
	/*��ʼ����ͼʵ��ָ��*/
	bool initMapInform(void);
	
	/*�����������*/
	Point getPiexPt(void);
	
	/*ˢ������*/
	void brushMsg(void);
	
	/*�޸�����*/
	void setPiex(Point _piexPt);
	
	/*�ݻٵ���*/
	void destoryMsg(void);
};
#endif
