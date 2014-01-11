/************************************************************
	�ļ�����map_src.h
	�ļ����ã���Map_Src������Ժͷ���
	���ߣ�chenzhen
	�������ڣ�2012.03.11
************************************************************/
#ifndef MAP_SRC_H
#define MAP_SRC_H
#include<iostream>
#include"map_inform.h"

class VipBaleRoomLimit;
class PartyRoomLimit;
class PartyBaseCampLimit;
class Map_Src : public Map_Inform
{
private:	             	
	
	/*����ʵ��ָ��*/
	VipBaleRoomLimit *vipRoom;	
	
	/*vip�����*/
	int vipRoomNum;
	
	/*�Ƿ���vip���ᣬtrueΪvip����*/
	bool isVipRom;
	
	/*vip�����Ƿ�ռ�ã�trueΪ��ռ��*/
	bool isVipRomBusy;
	
	
	
	/*����ʵ��ָ��*/
	PartyRoomLimit *partyRoom;	
	
	/*���ɷ����*/
	int partyRoomNum;
	
	/*�Ƿ��ǰ��ɰ��ᣬtrueΪ���ɰ���*/
	bool isPartyRom;
	
	/*���ɰ����Ƿ�ռ�ã�trueΪ��ռ��*/
	bool isPartyRomBusy;
	
	
	
	/*���ɴ�Ӫ*/
	PartyBaseCampLimit *campRoom;	
	
	/*���ɴ�Ӫ�����*/
	int campRoomNum;
	
	/*�Ƿ��Ǵ�Ӫ���ᣬtrueΪ���ɴ�Ӫ����*/
	bool isCampRom;
	
	/*���ɴ�Ӫ�����Ƿ�ռ�ã�trueΪ��ռ��*/
	bool isCampRomBusy;
	
	
	
	
	
	/*���ƹ��︴����*/
	int ctnReBruDieMon;	
	
	/*��������������ˢ����*/
	void exchageDie(void);
	
	/*ѭ��ˢ�ֺ���*/
	void loopBruMon(bool isFirst = false);
	
	/*����ˢ��Ƶ��*/
	bool ctlTme(int lveTme = 12);
	
	/*��һ�ν��볡��ˢ��*/
	void entMap(void);
	
	/*ˢ�ֽӿ�*/
	void bruMonFun(void);	
	
public:

	/*���캯��*/
	Map_Src(char *_mapId,char *_mapFilePath,char *_mapName,int _mapWidth,\
	int _mapHeight,int _row,int _col,int _baseDigst,Point _entPt,\
	Point _outPt,Point _tribesPt,Point _religionPt,Point _rangerPt,\
	map<string,MonsterBase *>& _monId_connect_monster,\
	map<string,const jumpId_infor*>& _jumpId_connect_jumpInfo,\
	map<string,TakeGoods*> &_takeGoodsMap,map<string,Bottle*> &_botInMap,\
	map<string,Trap*> &_trapInstMap,set<Point> _dishPtSet,Point _centerPt,size_t _radius,bool _flgCpy,\
	int warType,int changePkType,int mapType,int campEntFlag,\
	int levelLowerLimit,int levelUpperLimit);	
	
	/*��ͼ˼���ص�����*/
	void mapThkCalBak(void);

	
	
	/*��ô˵�ͼ���й�������id����*/
	set<string> getTypeMonOneMap(void);

	/*��������*/
	~Map_Src(void);   
	
	/*��ͣ�˵�ͼ����ˢ���ֵ�˼��*/
	void stopAllLveMonThk(void);
	
	/*�����˵�ͼ��������ˢ���ֵ�˼��*/	
	void reSetAllLveMonThk(void);
	
	
	/*���Ƶ�ͼ��Ϣ����������Ϊ�����ָ����еĹֵ�id*/
	Map_Src* copyMap(int roomNum);
	
	/*���ù�������*/
	void initMon(void);
	
	/*�������ŵ�ͼ��Ϣ*/
	void initMap(void);
	
	/*��ͼ��ͣ˼������*/
	void stopThk(void);
	
	/*���ɹ�����Ŀ��Ϣ*/
	char* getSumMonMsg(void);
	
	
	/*����Ƿ�Ϊvip�����־*/
	bool getIsVipRom(void);
	
	/*�����Ƿ�Ϊvip�����־*/
	void setIsVipRom(bool _busy);
	
	
	/*���vip�����Ƿ�ռ�ñ�־*/
	bool getIsVipRomBusy(void);
	
	/*���vip�����Ƿ�ռ�ñ�־*/
	void setIsVipRomBusy(bool _busy);
	
	/*����vip����������ʵ��ָ��*/
	void setVipRoom(VipBaleRoomLimit *_vipRoom);
	
	/*����vip����*/
	void enterVipRoomFirst(void);
	
	/*���᳡����ͼ˼������*/
	bool vipCallBack(void);
	
	/*����õ�vip�����*/
	void ctnTheVipRoomNum(void);
	
	/*�˳�vip����*/
	void exitVipRoom(vector<string> &heroVec);
	
	/*����õ����ɰ����*/
	void ctnThePartyRoomNum(void);
	
	/*���vip�����Ƿ�ռ�ñ�־*/
	void setIsPartyRomBusy(bool _busy);
	
	/*���vip�����Ƿ�ռ�ñ�־*/
	bool getIsPartyRomBusy(void);
	
	/*�����Ƿ�Ϊ���ɵ�ͼ*/
	void setIsPartyRom(bool _busy);
	
	/*����Ƿ�Ϊ���ɰ����־*/
	bool getIsPartyRom(void);
	
	/*���ð��ɰ���������ʵ��ָ��*/
	void setPartyRoom(PartyRoomLimit *_partyRoom);
	
	PartyRoomLimit* getPartyRoomLimit(void);
	
	/*������ɰ���*/
	void enterPartyRoomFirst(void);
	
	/*���᳡����ͼ˼������*/
	bool partyCallBack(void);
	
	
	/*���ð��ɴ�Ӫ����������ʵ��ָ��*/
	void setCampRoom(PartyBaseCampLimit *_campRoom);
	
	/*��ð��ɰ����Ƿ�ռ�ñ�־*/
	bool getIsCampRomBusy(void);
	
	/*��ð��ɰ����Ƿ�ռ�ñ�־*/
	void setIsCampRomBusy(bool _busy);
	
	/*����õ����ɴ�Ӫ�����*/
	void ctnTheCampRoomNum(void);
	
	/*�˳����ɴ�Ӫ����*/
	void exitCampRoom(vector<string> &heroVec);
	
	/*����Ƿ�Ϊ���ɴ�Ӫ�����־*/
	bool getIsCampRom(void);
	
	/*�����Ƿ�Ϊ���ɴ�Ӫ��ͼ*/
	void setIsCampRom(bool _busy);
	
	/*���ɴ�Ӫ���᳡����ͼ˼������*/
	bool campCallBack(void);
	
	/*������ɴ�Ӫ����*/
	void enterCampRoomFirst(void);
	
	/*ϵͳ��͸�������*/
	bool systemTreat(TakeGoods *newDish);
};
#endif 
