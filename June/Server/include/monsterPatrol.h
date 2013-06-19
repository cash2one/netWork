/********************************************************************

    filename: monsterPatrol.h 

    author:       ChenZhen

    amend:   2012/5/09       by Tory

*********************************************************************/
#ifndef MONSTERPATROL_H
#define MONSTERPATROL_H
#include"monsterBase.h"
#include"map_inform.h"
/**
**��������
**/
#include "TD_Instancing.h"


class MonsterPatrol : public MonsterBase
{
private:	

	Point endFinPt; 				//Ѳ���յ㣨�����߼��㣬ͨ�����ص�ת�����õ���	       				
	
	int radius;              		//�Լ�Ѱ·�뾶
	
	bool flgEnd;        //Ѱ·�յ�ת�����ֵ
	
	
public :
	MonsterPatrol(char *_mapId,char *_typeId,char *_nickName,char *_identity, char *_type,char *_kind,\
	int _experience,double _cdTime,int _lifeUpperVal,int _lifeVal,\
	int _magicUpperVal,int _magicVal,int _getHrtSud,int _outHrt,int _inHrt, int _outAttVal, int _inAttVal,\
	int _outDefVal, int _inDefVal,int _defSumVal,double _hit,double _crit,int _voids,int _tenacity,\
	int _moveRange, int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,\
	int _hatVal,int _gold,set<string>& _failId, Point _pt,int _rank,int _speed,int _fiveEleInt,int _fiveHurt,\
	int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,\
	vector<string> &skiIdSet,char *_genAttId,double _angVal,int _ownerAttriType,char* _ownerAttri,\
	double _attackRatio,bool isInnerAttack,LveCtnManger _lveCtnMager,Point logicPt,int _radius);
		
	/*��������*/
	~MonsterPatrol(void);
	
	/*����˼������*/
	virtual void response(void);
	
	void getEnd(Point _logicPt);
		
	/*�������*/
	virtual MonsterBase* copyMon(char *_mapId);

	/*������������*/
	virtual void die(bool flgInit = false);
	
	/*����������������*/
	void initMonsterALL(void);
	
};
#endif

