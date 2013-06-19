/******************************
* created:   2012/2/06  9:24
* �ļ�����	astar.h
* author:       Tory 
* purpose:  
* �޸ģ�	2012.2.16
******************************/
#ifndef __ASTAR__
#define __ASTAR__
using namespace std;
#include <list>
#include<vector>
#include <stdio.h>
#include <algorithm>
#include"data_structure_struct.h"
#define SLANT 14		//б������ֵ
#define STRAIGHT 10		//ֱ������ֵ

class Astar;
class Map_Inform;

class Mark
{
	friend class Astar;
	public:
		Mark(){};
		Mark(int posX, int posY, Mark* pareMark, int currentG, int currentH);
		Mark(const Mark& mark);				//�������캯��
		Mark& operator=(const Mark &m);		//=������
		~Mark();

		Mark*	get_pareMark();				//��ø��ڵ�
		int		get_f();
		Point 	point();
	private:
		Mark* 	_pareMark;					//���ڵ�
		int		_g;
		int 	_h;
		int 	_f;
		int 	_posX;
		int		_posY;
};


class Astar
{
	public:
		Astar(Map_Inform *newMap);
		~Astar();

	public:
		list<Point> 	findWay(Point start, Point end);
		list<Point>& getWayArr(void);
	private:
		int 	_startX;		//��ʼ�������
		int		_startY;		//��ʼ��������
		int 	_endX;			//Ŀ��������
		int		_endY;			//Ŀ���������
		int		_w_map;			//��ͼ���
		int		_h_map;			//��ͼ�߶�
		vector< vector<int> > _mapArr;		//��ͼ������Ϣ���ɹ����벻�ɹ��㣩
		list<Mark *>	_openList;			//	mark�㿪���б��������ֺ�ѡȡ��С_fֵ��
		list<Point> 	_wayArr;
		vector< vector <bool> >		_markFlagArr;	//���ڱ��ĳ�����Ƿ��Ѽ��뿪���б��ر��б����ͼ�����Ӧ��ʹ��
		list<Mark *>	_closeList;					//mark��ر��б����Ѱ·ʱ�õ���һϵ����С_fֵ�㣬����·������������ͷ��ڴ�
	private:
		void	addOpenList(Mark *pmark);
		Mark* 	new_Mark(int posX, int posY, bool isSlant, Mark* pareMark);		
		
};

bool compare(Mark* first, Mark* second);			//�Զ���list�ȽϺ���������list����Ƚ�

#endif
