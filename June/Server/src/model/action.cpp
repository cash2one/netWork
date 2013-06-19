/************************************************************
	�ļ�����action.cpp
	�ļ����ã�ʵ����Action��ķ���
	���ߣ�chenzhen
	�������ڣ�2012.08.04
************************************************************/
#include"action.h"

Action::Action(void)
{
	mapNow = NULL;
	astar = NULL;
}

/*��ʼ����ͼ��astar*/
void Action::init(Map_Inform *_map)
{
	setMap(_map);
	initAstar(_map);
}

/*��ʼ��astar*/
void Action::initAstar(Map_Inform *map)
{
	if(astar == NULL)
	{
        astar = new Astar(map);
    }	
}

/*��ʼ����ͼ*/
void Action::setMap(Map_Inform *_map)
{
	if(_map != NULL)
	{
		mapNow = _map;	
	}
}

/*����ͼʱ,��Ҫ�ǳ�����*/
void Action::chgMapAstar(Map_Inform *map)
{
	if(astar != NULL)
	{
		delete astar;
		astar = NULL;        
    }	
	astar = new Astar(map);
}

/*Ѱ·*/
list<Point> Action::findWay(Point &logic,Point &logicWantGo)
{
	list<Point> resultRod;
	if(!judgeFindCondition(logic,logicWantGo))
	{
		return resultRod;
	}
	astar->findWay(logic,logicWantGo);
	return astar->getWayArr();
}

/*Ѱ·ǰ���������*/
bool Action::judgeFindCondition(Point &logic,Point &logicWantGo)
{
	/*�ж�a���Ƿ�Ϊ��*/
	if(astar == NULL)
	{
		return false;
	}
	
	/*�жϵ��Ƿ����*/
	if(logic._x == logicWantGo._x && logic._x == logicWantGo._x)
	{
		return false;
	}
	
	/*�жϵ�ĺϷ���*/
	if(judgeFindPt(logic) && judgeFindPt(logicWantGo))
	{			
		return true;
	}
	return false;
}

/*����ĺϷ���*/
bool Action::judgeFindPt(Point &logic)
{
	/*x�����Ƿ�Խ��*/
	if(logic._x < 0 && logic._x > mapNow->getRow())
	{
		return false;
	}
	
	/*y�����Ƿ�Խ��*/
	if(logic._y < 0 && logic._y > mapNow->getCol())
	{
		return false;
	}
	
	/*�Ƿ�Ϊ�ϰ���*/
	if(mapNow->getMapHinder()[logic._x][logic._y] == 1)
	{
		return false;
	}
	return true;	
}

/*��������*/
Action::~Action(void)
{
	if(astar != NULL)
	{
		delete astar;
		astar = NULL;
	}
	
	if(mapNow != NULL)
	{
		mapNow = NULL;
	}
}

Astar* Action::getAstar(void)
{
	return astar;
}


		