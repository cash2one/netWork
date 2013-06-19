/************************************************************
	�ļ�����dailyActive.cpp
	�ļ����ã��ճ�����ʵ��
	���ߣ�chenzhen
	�������ڣ�2012.10.25
************************************************************/
#include"command_other_function_all_over.h"
#include "systemMessage.h"
#include"dailyActive.h"
#include"map_src.h"
#include"my_time.h"

extern map<string,Map_Src*>mapId_connect_map;
static struct tm* timeNow;

DailyActive::DailyActive(char *_activeId,char *_mapId,set<int> _whichDay,\
set<OffTmeStr> _offTme,set<string> _beginTme,set<string> _endTme,\
set<string>_peaceTme,Point _peixPt,int _level)
{
	memset(activeId,'\0',sizeof(activeId));
	memset(mapId,'\0',sizeof(mapId));
	memset(openMsg,'\0',sizeof(openMsg));
	memset(offMsg,'\0',sizeof(offMsg));
	strncpy(activeId,_activeId,strlen(_activeId));	
	strncpy(mapId,_mapId,strlen(_mapId));
	
	peixPt = _peixPt;
	level = _level;
	isOpen = false;
	whichDay = _whichDay;
	beginTme = _beginTme;
	endTme = _endTme;
	offType = true;     //���Ϊ�����ǰ��ʾ����Ϊtrue;
	
	offTme = _offTme;
	peaceTme = _peaceTme;
	
	duringTmeSeconds = 0;
	lastTmeSeconds = 0;
	goToTmeSeconds = 0;
	int durTme = getdurTme();
	if(durTme < 0)
	{
		cout<<"DailyActive::DailyActive the during time is error:"<<activeId<<endl;
	}
	else
	{
		duringTmeSeconds = getdurTme();
	}
	
}

/*��ǰ����*/
void DailyActive::formOpenMsg(void)
{
	int flg;
	
	memset(openMsg,'\0',SHOR_MID_VALUE_LENGTH + 1);
	
	if(isOpen)
	{
		flg = 1;		
	}
	else
	{
		flg = 0;		
	}
	sprintf(openMsg + strlen(openMsg),"%d,%d,%s,%d",\
			2,16,activeId,flg);
}

/*����ǰ��ʾ��Ϣ*/
void DailyActive::formOffMsg(void)
{	
	int flag;
	
	/*����ǰ��ʾ*/
	if(offType)
	{
		/*�����ѿ���*/
		if(isOpen)
		{
			return;
		}
		flag = 1;
		offType = false;
	}
	
	/*�ر�ǰ��ʾ*/
	else
	{
		/*�����ѹر�*/
		if(!isOpen)
		{
			return;
		}
		flag = 0;
		offType = true;
	}

	memset(offMsg,'\0',sizeof(offMsg));
	sprintf(offMsg,"%d,%d,%s,%d",2,17,activeId,flag);
}

/*���ÿ������ֵ*/
void DailyActive::setisOpen(bool _isOpen)
{
	isOpen = _isOpen;
}

/*��ÿ������ֵ*/
bool DailyActive::getisOpen(void)
{
	return isOpen;
}

/*��ÿ�����Ϣ*/
char* DailyActive::getOpenMsg(void)
{
	return openMsg;
}

/*��ÿ�����ʾ��Ϣ*/
char* DailyActive::getOffMsg(void)
{
	return offMsg;
}

/*�鿴�ȼ��Ƿ�����*/
bool DailyActive::examLevel(int _level)
{
	return level <= _level;
}

/*�ѽ�ɫ���͵����ʼ�ĵ�*/
bool DailyActive::takePart(Hero *myHero)
{
	if(myHero == NULL)
	{
		cout<<"the hero of takePart is NULL:"<<endl;
		return false;
	}
	
	Map_Src *myMap;
	map<string,Map_Src*>::iterator src_it;
	src_it = mapId_connect_map.find(mapId);
	if(src_it == mapId_connect_map.end())
	{
		cout<<"the map is error:"<<mapId<<endl;
		return false;
	}
	
	myMap = src_it->second;	
	return sendInMapPoint(myMap,peixPt,myHero);
}

/*����ճ��id*/
char* DailyActive::getActiveId(void)
{
	return activeId;
}
	
/*�ж������Ƿ���*/
bool DailyActive::isRightDay(int dayInt)
{
	set<int>::iterator day_it;
	if(whichDay.empty())
	{
		return true;
	}
	day_it = whichDay.find(dayInt);
	if(day_it == whichDay.end())
	{
		return false;
	}
	return true;
}

/*�Ƿ񵽴￪��ʱ��*/
bool DailyActive::isBegin(char *timeNow)
{
	set<string>::iterator begin_it;
	if(timeNow == NULL || strlen(timeNow) ==0)
	{
		cout<<"the argument is empty:"<<endl;
		return false;
	}
	begin_it = beginTme.find(timeNow);
	if(begin_it == beginTme.end())
	{
		return false;
	}
	
	someActiveBeginTme = timeNow;
	
	return true;
}

/*�Ƿ񵽴�ر�ʱ��*/
bool DailyActive::isEnd(char *timeNow)
{
	set<string>::iterator end_it;
	set<string>::iterator peace_it;
	
	if(timeNow == NULL || strlen(timeNow) ==0)
	{
		cout<<"the argument is empty:"<<endl;
		return false;
	}
	
	/*��ƽʱ��*/
	if(!peaceTme.empty())
	{
		peace_it = peaceTme.find(timeNow);	
		if(peace_it != peaceTme.end())
		{
			cout<<"the peace time is now:"<<activeId<<endl;
			return true;
		}
	}
	
	end_it = endTme.find(timeNow);
	if(end_it == endTme.end())
	{
		return false;
	}
	
	lastTmeSeconds = 0;
	goToTmeSeconds = 0;
	someActiveBeginTme.clear();
	
	return true;
}

/*�ж���ĳ��ʱ��δ˻�Ƿ���*/
bool DailyActive::isMidTme(char *timeNow)
{	
	set<string>::iterator end_it;
	set<string>::iterator begin_it;
	
	if(timeNow == NULL || strlen(timeNow) ==0)
	{
		cout<<"the argument is empty:"<<endl;
		return false;
	}
	for(begin_it = beginTme.begin(),end_it = endTme.begin();\
		begin_it != beginTme.end() && end_it != endTme.end();\
		++begin_it,++end_it)
	{
		if((*begin_it).compare(timeNow) <= 0 && (*end_it).compare(timeNow) == 1)
		{
			someActiveBeginTme = *begin_it;
			return true;
		}
	}
}

/*���ĳ����ĳ���ʱ��*/
int DailyActive::getdurTme(void)
{
	int hour1,min1,hour2,min2;
	int result;
	set<string>::iterator begin_it,end_it;
	if(beginTme.empty() || endTme.empty())
	{
		cout<<"the beginTme and the endTme is empty:"<<activeId<<endl;
		return -1;
	}
	
	begin_it = beginTme.begin();
	end_it = endTme.begin();
	
	if(!tmeStrChgInt(hour1,min1,const_cast<char *>((*begin_it).c_str())))
	{
		cout<<"the begin_it is error:"<<*begin_it<<endl;
		return -1;
	}
	if(!tmeStrChgInt(hour2,min2,const_cast<char *>((*end_it).c_str())))
	{
		cout<<"the end_it is error:"<<*end_it<<endl;
		return -1;
	}
	// cout<<"test begin:"<<activeId<<endl;
	// cout<<"begin_it:"<<*begin_it<<endl;
	// cout<<"hour1:"<<hour1<<"  min1:"<<min1<<endl;
	// cout<<"end_it:"<<*end_it<<endl;
	// cout<<"hour2:"<<hour2<<"  min2:"<<min2<<endl;
	// cout<<"test end:"<<activeId<<endl;
	return (hour2 - hour1) * 3600 + (min2 - min1) * 60;
}

/*��ʾʱ���Ƿ��ѵ�������ˣ�������Ϣ*/
bool DailyActive::isOffTme(char *timeNow)
{
	set<OffTmeStr>::iterator off_it;
	
	if(timeNow == NULL || strlen(timeNow) == 0 || offTme.empty())
	{
		return false;
	}
	OffTmeStr tmeNow(timeNow);
	
	off_it = offTme.find(tmeNow);
	if(off_it == offTme.end())
	{
		return false;
	}
	
	/*������ʾ��Ϣ*/
	formOffMsg();
	
	/*����ȫ������*/
	SYSTEM_MESSAGE::systemActivityMsg(offMsg,(*off_it).offTimes,(*off_it).durTimes,level);
	
	return true;
}

/*������ʾ���ͱ��ֵ*/
void DailyActive::setOffType(bool _offType)
{
	offType = _offType;
}

/*��ú�ƽʱ��*/
int DailyActive::getPeaceTme(void)
{
	int hour1,min1,hour2,min2;
	int result;
	set<string>::iterator begin_it,end_it;
	if(beginTme.empty() || peaceTme.empty())
	{
		cout<<"the beginTme and the peaceTme is empty:"<<activeId<<endl;
		return -1;
	}
	
	begin_it = beginTme.begin();
	end_it = peaceTme.begin();
	
	if(!tmeStrChgInt(hour1,min1,const_cast<char *>((*begin_it).c_str())))
	{
		cout<<"the begin_it is error:"<<*begin_it<<endl;
		return -1;
	}
	if(!tmeStrChgInt(hour2,min2,const_cast<char *>((*end_it).c_str())))
	{
		cout<<"the end_it is error:"<<*end_it<<endl;
		return -1;
	}
	// cout<<"test begin:"<<activeId<<endl;
	// cout<<"begin_it:"<<*begin_it<<endl;
	// cout<<"hour1:"<<hour1<<"  min1:"<<min1<<endl;
	// cout<<"end_it:"<<*end_it<<endl;
	// cout<<"hour2:"<<hour2<<"  min2:"<<min2<<endl;
	// cout<<"test end:"<<activeId<<endl;
	return (hour2 - hour1) * 3600 + (min2 - min1) * 60;
}

/*������ʼ�೤ʱ��*/
void DailyActive::formGoToTmeSeconds(void)
{
	if(someActiveBeginTme.empty())
	{
		cout<<"DailyActive::formGoToTmeSeconds the someActiveBeginTme is empty:"<<activeId<<endl;
		return;
	}
	int beginhour = -1, beginmin = -1;
	/*���ַ���ʱ��ת����int��*/
	if(!tmeStrChgInt(beginhour,beginmin,const_cast<char *>(someActiveBeginTme.c_str())) || beginhour < 0 || beginmin < 0)
	{
		cout<<"DailyActive::formGoToTmeSeconds the someActiveBeginTme is error:"<<activeId<<endl;
		return;
	}
	
	gettimeofday(&myTime, NULL);	
	timeNow = localtime(&myTime.tv_sec);
	
	int totalSeconds = (timeNow->tm_hour - beginhour) * 3600 + (timeNow->tm_min - beginmin) * 60 + timeNow->tm_sec;
	
	if(totalSeconds > 0)
	{
		goToTmeSeconds = totalSeconds;
	}
}

/*��û�Ļ��ʼ�೤ʱ��*/
size_t DailyActive::getGoToTmeSeconds(void)
{
	formGoToTmeSeconds();
	return goToTmeSeconds;
}

/*��û��ʣ��ʱ��*/
size_t DailyActive::getLastTmeSeconds(void)
{
	int lastTme;
	formGoToTmeSeconds();
	lastTme = duringTmeSeconds - goToTmeSeconds;
	if(lastTme <=0 || goToTmeSeconds == 0)
	{
		lastTmeSeconds = 0;
	}
	else
	{
		lastTmeSeconds = lastTme;
	}
	return lastTmeSeconds;
}

/*��ӡ���Ի�е�ʱ��*/
void DailyActive::printTme(void)
{
	cout<<"the activeId begin:"<<activeId<<endl;
	cout<<"duringTmeSeconds:"<<duringTmeSeconds<<endl;
	cout<<"goToTmeSeconds:"<<getGoToTmeSeconds()<<endl;
	cout<<"lastTmeSeconds:"<<getLastTmeSeconds()<<endl;
	if(!someActiveBeginTme.empty())
	{
		cout<<"someActiveBeginTme:"<<someActiveBeginTme<<endl;
	}
	cout<<"the activeId end:"<<activeId<<endl;
}

int DailyActive::getLimitLevel()
{
	return level;
}
	
	