/************************************************************
	�ļ�����dailyActive.h
	�ļ����ã��ճ���������
	���ߣ�chenzhen
	�������ڣ�2012.10.25
************************************************************/
#ifndef DALY_ACTIVE_H
#define DALY_ACTIVE_H
#include"data_structure_struct.h"
#include"activeAsist.h"
#include<string>
#include"hero.h"

using namespace std;

typedef struct OffTmeStr
{
	string beginTime;    //��ʾ��ʼʱ��
	int offTimes;       //��ʾ����
	int durTimes;       //ÿ����ʾ���ʱ��
	OffTmeStr(char *_beginTime,int _offTimes = 0,int _durTimes = 0)
	{
		beginTime = _beginTime;
		offTimes = _offTimes;
		durTimes = _durTimes;
	}
	bool operator < (const OffTmeStr &offTme) const
	{
		if(beginTime.compare(offTme.beginTime) == -1)
		{
			return true;
		}
		return false;
	}
	
	bool operator == (const OffTmeStr &offTme) const
	{
		if(beginTime.compare(offTme.beginTime) == 0)
		{
			return true;
		}
		return false;
	}
}OffTmeStr;

class DailyActive
{
	char activeId[SHOR_MID_VALUE_LENGTH + 1];	
	char openMsg[SHOR_MID_VALUE_LENGTH + 1];
	char offMsg[SHOR_MID_VALUE_LENGTH + 1];
	char mapId[SHOR_MID_VALUE_LENGTH + 1];
	Point peixPt;
	bool isOpen;	
	int level;
	set<int> whichDay;
	set<string>beginTme;
	set<string>endTme;
	set<string>peaceTme;
	set<OffTmeStr> offTme;
	
	bool offType;
	
	/*�����ʱ�䣬��*/
	size_t duringTmeSeconds;
	
	/*�һ��ʼʱ�䣬��*/
	size_t goToTmeSeconds;
	
	/*���ʣ��ʱ�䣬��*/
	size_t lastTmeSeconds;
	
	/*����ĳ�εĿ�ʼʱ��*/
	string someActiveBeginTme;
	
	public:
	
	DailyActive(char *_activeId,char *_mapId,set<int> _whichDay,\
	set<OffTmeStr> _offTme,set<string> _beginTme,set<string> _endTme,\
	set<string>_peaceTme,Point _peixPt,int _level);
	
	/*��ǰ����*/
	void formOpenMsg(void);
	
	/*���ÿ������ֵ*/
	void setisOpen(bool _isOpen);
	
	/*��ÿ������ֵ*/
	bool getisOpen(void);
	
	/*��ÿ�����Ϣ*/
	char* getOpenMsg(void);
	
	/*�鿴�ȼ��Ƿ�����*/
	bool examLevel(int _level);
	
	/*�ѽ�ɫ���͵����ʼ�ĵ�*/
	bool takePart(Hero *myHero);
	
	/*����ճ��id*/
	char* getActiveId(void);
	
	/*�ж������Ƿ���*/
	bool isRightDay(int dayInt);
	
	/*�Ƿ񵽴￪��ʱ��*/
	bool isBegin(char *timeNow);
	
	/*�Ƿ񵽴�ر�ʱ��*/
	bool isEnd(char *timeNow);
	
	/*�ж���ĳ��ʱ��δ˻�Ƿ���*/
	bool isMidTme(char *timeNow);
	
	/*���ĳ����ĳ���ʱ��*/
	int getdurTme(void);
	
	/*����ǰ��ʾ��Ϣ*/
	void formOffMsg(void);
	
	/*��ÿ�����ʾ��Ϣ*/
	char* getOffMsg(void);
	
	/*��ʾʱ���Ƿ��ѵ�������ˣ�������Ϣ*/
	bool isOffTme(char *timeNow);
	
	/*������ʾ���ͱ��ֵ*/
	void setOffType(bool _offType);
	
	/*��ú�ƽʱ��*/
	int getPeaceTme(void);
	
	/*��û�Ļ��ʼ�೤ʱ��*/
	size_t getGoToTmeSeconds(void);
	
	/*������ʼ�೤ʱ��*/
	void formGoToTmeSeconds(void);
	
	/*��û��ʣ��ʱ��*/
	size_t getLastTmeSeconds(void);
	
	/*��ӡ���Ի�е�ʱ��*/
	void printTme(void);
	
	int getLimitLevel();
};
#endif