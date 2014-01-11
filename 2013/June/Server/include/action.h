/************************************************************
	�ļ�����action.h
	�ļ����ã���Action������Ժͷ���������
	���ߣ�chenzhen
	�������ڣ�2012.08.04
************************************************************/
#ifndef ACTION_H
#define ACTION_H
#include"astar.h"
#include"map_inform.h"
class Action
{
	Astar *astar;             //a��
	
	Map_Inform *mapNow;
	/*Ѱ·ǰ���������*/
	bool judgeFindCondition(Point &logic,Point &logicWantGo);
	
	/*����ĺϷ���*/
	bool judgeFindPt(Point &logic);
	
	/*��ʼ��astar*/
	void initAstar(Map_Inform *map);
	
	/*����ͼʱ,��Ҫ�ǳ�����*/
	void chgMapAstar(Map_Inform *map);
	
	/*��ʼ����ͼ*/
	void setMap(Map_Inform *_map);
	
public:
	
	Action(void);
	
	/*��ʼ����ͼ��astar*/
	void init(Map_Inform *_map);	
	
	/*Ѱ·*/
	list<Point> findWay(Point &logic,Point &logicWantGo);	
	
	Astar* getAstar(void);
	
	/*��������*/
	~Action(void);	
};
#endif
	