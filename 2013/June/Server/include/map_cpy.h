/************************************************************
	�ļ�����map_cpy.h
	�ļ����ã���Map_Cpy������Ժͷ���
	���ߣ�chenzhen
	�������ڣ�2012.03.11
************************************************************/
#ifndef MAP_CPY_H
#define MAP_CPY_H
#include<iostream>	
#include"map_inform.h"
#include"map_inform_asist.h"
using namespace std;

class Map_Cpy : public Map_Inform
{
private:	 
	
	/*�˵�ͼ��������ʵ��ָ��*/
	Cpy *cpy;
	
	/*���ƹ��︴����*/
	int ctnReBruDieMon;
	
	/*ˢ�������±�*/
	int index;
	
	/*ˢ������*/	
	vector<BruGro>bruGropVec;
	
	/*ÿ����ˢ����ʱ��,����ɵ�ͼ˼��ʱ��*/
	vector<int>bruEachTme;
	
	/*��ʱ��������ɹ���˼��ʱ�䣩*/
	int ctnBru;
	
	/*�Դ�����id*/
	// list<string> lveMonCtnId;	
	
	bool pasFlg,goNext;
	
	int sumMon;
	
	int lveSumMon;
	
	char sumMonMsg[SHOR_MID_VALUE_LENGTH + 1];
	
	
	set<string>::iterator bruMonId_it;
	
	/*���븱����һ���Լ����ո���*/
	void getNextStage(void);
	
	/*��������ˢ������*/
	bool initGroBru(void);
	
	/*��һ����ˢ�������ж�*/
	bool judgeGroDieOut(void);
	
	/*����ʱ���Ƿ�*/
	bool judgeBruGroTmeOut(void);
	
	/*������ģʽˢ�ֽӿ�*/
	void bruMonByGroMod(void);	
	
	
	/*��������ˢ�ֺ���*/
	void bruMonByGroFun(int _index);
	
	/*����ˢ������*/
	void copyBruGropVec(vector<BruGro> &_bruGropVec,char *newMap);
	
	/*��������*/
	void GromonDead(char *monId);
	
	/*���ð���ˢ��ģʽ*/
	void initGroMon(void);
	
	/*���������ˢ�ֺ���*/
	void bruMonByCtnFun();
	
	/*ˢ�µ�ͼ��Ϣ����*/
	void bruMapFun(void);

	/*���������Ƿ�ˢ��*/
	bool judgeBruGroIndex(void);	
	
	/*�ѹ���ӵ�ͼ��ɾ��*/
	void  monLveOutView(void);
	
public:
	/*���캯��*/
	Map_Cpy(char *_mapId,char *_mapFilePath,char *_mapName,int _mapWidth,\
	int _mapHeight,int _row,int _col,int _baseDigst,Point _entPt,\
	Point _outPt,Point _tribesPt,Point _religionPt,Point _rangerPt,\
	map<string,MonsterBase *>& _monId_connect_monster,\
	vector<BruGro> _bruGropVec,	vector<int>_bruEachTme,\
	map<string,const jumpId_infor*>& _jumpId_connect_jumpInfo,\
	map<string,TakeGoods*> &_takeGoodsMap,map<string,Bottle*> &_botInMap,\
	map<string,Trap*> &_trapInstMap,set<Point> _dishPtSet,Point _centerPt,size_t _radius,bool _flgCpy,\
	int _sumMon,int warType,int _changePkType,int _mapType=0,\
	int _campEntFlag=0,int _levelLowerLimit=0,int _levelUpperLimit=100);
	
	
	/*��һ�ν��븱��*/
	void fristEntMap(void);
	
	/*���ø���ֵ*/
	void SetCpy(Cpy *_cpy);
	
	/*���Ƶ�ͼ��Ϣ����������Ϊ�����ָ����еĹֵ�id*/
	Map_Cpy* copyMap(int roomNum,char *cpyId = NULL);
	
	/*��ͼ˼���ص�����*/
	void mapThkCalBak(void);
	
	/*��������*/
	~Map_Cpy(void);
	
	/*��ͣ�˵�ͼ����ˢ���ֵ�˼��*/
	void stopAllLveMonThk(void);
	
	/*�����˵�ͼ��������ˢ���ֵ�˼��*/	
	void reSetAllLveMonThk(void);
	
	/*�������ŵ�ͼ��Ϣ*/
	void initMap(void);
	
	
	/*���Ը�ˢ�����ι���id*/	
	void testGroMonId(void);
	
	/*���Ը�ˢ������ʱ��*/	
	void testGroCtn(void);
	
	/*���Դ�ӡˢ��ʱ������*/
	void testBruEachTme(void);
	
	/*�������ձ�־*/
	bool recoverCpy(void);
	
	/*���Դ�ӡ�����д���б���Ϣ*/
	void testLveCtn(void);
	
	/*���Դ�ӡ����������Ϣ*/
	void testMapInfor(void);
	
	/*���ɹ�����Ŀ��Ϣ*/
	void formSumMonMsg(void);
	
	/*���ɹ�����Ŀ��Ϣ*/
	char* getSumMonMsg(void);	
	
	/*���¸���������Ŀ*/
	void sentSumMonMsg(void);
	
	/*ɱ��һ����*/
	void killOneMon(void);
	
	/*���Թ��������*/
	void testLveMager(set<string> &monId);
	
	/*��ͼ��ͣ˼������*/
	void stopThk(void);
	
	void getMonObj(vector< vector<string> > &mon_vec);	//tory add
	
	/*��һ����ˢ��ǰ����ʾ*/
	void formNextMonMsg(void);
	
	/*���ظ�������ָ��*/
	Cpy* getCpy(void);
};
#endif 
