/********************************************************************

    created:   2012/2/24  
	
	�ļ�����	nbox.h

    author:     cookie 

    purpose:  �Ź���ͷ�ļ���
			  ����Nbox�࣬˫��vector�����������꣬ͨ������Ϊ��ֵ��������ID�б�set��������
	
	�޸ģ�	2012.2.27��Tory��
	��д��  2012.08.23��chenzhen�������ĵ�
*********************************************************************/
#ifndef _NBOX_H__
#define _NBOX_H__
#include <set>
#include <vector>
#include <string>
#include <stdlib.h>
#include "data_structure_struct.h"
#include <iostream>


#include"map_inform.h"
#include"monsterBase.h"
#include"boxAsist.h"
class MonsterBase;
class Wagon;
class Pet;
class TakeGoods;
using namespace std;


typedef struct PointCmp
{
  bool operator() (const Point& pt1, const Point& pt2) const
  {
	return pt1._x != pt2._x || pt1._y != pt2._y ;
  }
}PointCmp;

class Map_Inform;
class Nbox
{		
private:
	/*��ǰ��ͼʵ��ָ��*/
	Map_Inform *map_now;
	
	/*�˾Ź�����ߣ��Լ���С(��������Ϊ��λ��*/
	Point scrSizePiexPt;
	
	/*��Ļ���鳤��*/
	Point MapScrPtSize;
	
	/*�Ź������ݣ��������������id*/
	vector <vector <OneScreen> > herOrMonIdVec;	
	
	set<Point> oldSrcPtSet;
	
	set<Point> newSrcPtSet;
	
	set<Point> sameSrcPtSet;
	
	set<Point> diffOldSrcPtSet;
	
	set<Point> diffNewSrcPtSet;
	 
	
	/*�ж���Ļ�����Ƿ�Ϸ�*/
	bool judgeSCrIndex(Point &srcPt);
	
	
	
	
	
	/*�����¾ɾŹ���Ľ����Ľ��������ƶ���Ϣ*/
	void ctnSmeValSet(void);
	
	/*�������¾Ź������¾ɾŹ���Ľ����Ĳ���ȷ���½��Ϣ���ٷ��ƶ���Ϣ*/
	void ctnDiffNewValSet(void);
	
	/*�����þɾŹ������¾ɾŹ���Ľ����Ĳ����������Ϣ*/
	void ctnDiffOldValSet(void);
	
	
	/*�жϴ˽�ɫ���Ƴ���ǰ��Ļ,�Ƴ�������false��ľ����true*/
	bool judgeOutSrc(Point &oldSrcPt,Point &newSrcPt);

	/*�������ľŹ���srcPtΪ��Ļ���꣩*/
	void getStaInSrcVec(Point &srcPt,set<Point> &SrcPtSet);
	
	/*�������*/
	void clearSet(void);
	
	/*�ռ�һ���������id*/
	void mapSrcPtToHerIdSet(Point &SrcPt,set<string> &heroIdSet);
	
	/*ͨ�����������þ�����heroid����*/
	void mapSrcPtToHerIdSet(set<Point> &SrcPtSet,set<string> &heroIdSet);
	
	/*��Ļ����ת����string��*/
	void ptToStr(const Point &srcPt, string& str);
	
	/*��ʼ����Ļ����*/
	void initScrVec(void);
	
public:

	Nbox(Map_Inform *_map_now,Point _scrSizePiexPtPiexPt);
	
	~Nbox(void);
	//��ȡָ���ص��Ѷ����뷶Χ�ڵĽ�ɫ�����͹�������
	void getObjInRange(Point &srcPt, int distSqr, set<string> &heroIdSet, set<string> &monsterSet);
	/*�ӾɾŹ�������ɾ��,���أ����ڲ�����*/
	bool deleteInOldSrc(Point &srcPt,StyObj &obj);
	
	/*����Ź�������,���أ����ڲ�����*/
	bool inputInOldSrc(Point &srcPt,StyObj &obj);
	
	
	/*��þŹ�����ʵ������������*/
	bool getObjpT(StyObj &obj,Point &piexPt);

	
	/*�ӾɾŹ�������ɾ��,���ߺ��е�ͼʱ���Ż��ⲿ����*/
	bool deleteInOldSrc(StyObj &obj);
	
	/*����Ź�������,���ߺ��е�ͼʱ���Ż��ⲿ����*/
	bool inputInOldSrc(StyObj &obj);
	
	
	/*��ͼ���ص�ת������Ļ����*/
	Point mapLogToSrcPtv(Point &piexPt,int flg = 0);
	
	
	/*���ػ�þŹ������ݺ�����ͨ��id*/
	void getStaInSrcVec(StyObj &obj);
	
	
	/*�ж�һ�����Ƿ�Ϸ�������������Ļ����*/
	void testInSrc(Point &piexPt);
	
	/*����ͨ���±�����*/
	void testIndex(Point &srcPt);
	
	/*��վŹ����е�����*/
	void clearBox(void);
	
	/*ͨ��piexPtΪ���������þŹ���*/
	void getNineSrcByLogPt(Point &piexPt);		
	
	/*��ɫ��������*/
	void heroPollTme(Hero *hero,char *moveMsg,bool isNewRod);
	
	/*�ƶ�������Ҳ���ԣ����ľŹ�������*/
	bool MovePt(StyObj &obj,Point &newPt);
	
	/*��װ����Ϣ���ͺ������ԾŹ�����*/
	void sentBoxMsg(set<Point> &SrcPtSet,char *msg,char *heroId = NULL);
	
	/*��װ����Ϣ���ͺ������ԾŹ�����,Ϊ�໥������,��Ҫ������ҵ���Ϣ����*/
	void sentBoxViewMsg(set<Point> &SrcPtSet,char *msg,Hero *myHero,int style);
	
	/*���Ը����Ÿ��������*/
	void testMapSet(OneScreen &idSet);
	
	/*���Ը����Ÿ��������*/
	void testKindSet(set<Point> &SrcPtSet);
	
	/*���Ը����Ÿ��������*/
	void testAllkindScr(void);
	
	/*��װ����Ϣ���ͺ������ԾŹ�����*/
	void sentBoxMsg(char *msg,char *heroId = NULL);
	
	
	/*�����ƶ�����*/
	void petMove(Pet *pet,char *moveMsg,bool isNewRoad, char *wonerId = NULL);
	
	/*���ƶ�����*/
	void wagonMove(Wagon *wagon,char *moveMsg, bool isNewRoad, char *wonerId = NULL);
	
	/*���ƶ��ƶ�����*/
	void takeGoodsMove(TakeGoods *takeGoods,char *moveMsg, bool isNewRod = false);
	
	/*��ɫ������˳���Ұ*/
	void heroEnter(Hero *hero,int style);
	
	/*��þŹ��������*/
	set<Point>& getNewSrcPtSet(void);
	
	
	/*ͨ������������һ�����ļ���*/
	OneScreen& getOneSrcMap(Point &piexPt);
	
	/*�����ƶ�����*/
	void monsterMove(MonsterBase *monster,char *moveMsg, bool isNewRod = false);	
	
	
	/*ͨ�����������þ�����heroid����*/
	void getNineSrcHerIdSet(Point &piexPt,set<string> &heroIdSet);
	
	/*ͨ���������귢�;Ź�������*/
	void sendMsgPiexPt(Point &piexPt,char *msg);
	
	/*��ȫͼɾ��һ��obj*/
	bool deleteObj(StyObj &obj);
	
	/*��һ��������ɾ��һ��obj*/
	bool deletObjHerVec(OneScreen& idSet,StyObj &obj);
	
	//������������Ļ
	void getNeighbour(Point pixPt, set<Point> &nbSet);
	
	//ͨ����Ļ��������Ļ
	void getOneScreen(OneScreen * &screen, Point scrPt);
	
	//��ȡ��Ļ��������Ļ	
	void getNeighbour(Point pixPt, OneScreen **screens);
	
	/*ͨ�������������������긽������heroid����*/
	void getCentPtSrcHerIdSet(Point &piexPt,set<string> &heroIdSet);
};

#endif
