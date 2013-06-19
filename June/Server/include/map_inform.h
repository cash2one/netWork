/************************************************************
	�ļ�����map_inform.h
	�ļ����ã���Map_Inform������Ժͷ���
	���ߣ�chenzhen
	�������ڣ�2012.03.11
************************************************************/
#ifndef MAP_INFORM_H
#define MAP_INFORM_H
#include"data_structure_struct.h"
#include<vector>
#include<iostream>
#include<map>
#include<set>
#include"nbox.h"
#include"libev.h"
#include"mapAction.h"
#include"command_other_function_all_over.h"	
#include"map_inform_asist.h"
#include"takeGoods.h"
#include"boxAsist.h"
using namespace std;
class MonsterBase;
class MonsterActive;
class MonsterPassivity;
class MonsterPatrol;
class MonsterBoss;
class MonsterActiveBoss;
class Nbox;
class Cpy;
class TakeGoods;
class Bottle;
class Trap;
class Pick;
class Map_Inform
{
protected:	
	char mapId[SHOR_MID_VALUE_LENGTH + 1];          	//��ͼid
	char mapFilePath[SHOR_MID_VALUE_LENGTH + 1];		//·��
	char mapName[SHOR_MID_VALUE_LENGTH + 1];			//����
	int mapWidth;			//��ȣ����أ�
	int mapHeight;			//�߶ȣ����أ�
	
	int row;				//����������
	int col;				//����������
	int baseDigst;			//��ͼƫ����
	
	string td_room;	
	
	map<string,MonsterBase *>monId_connect_monster;  //��ͼ������Ϣ
	
	map<string,const jumpId_infor*>jumpId_connect_jumpInfo; //��ת����Ϣ��
	
	vector< vector<int> >map_hinder;    			//��ͼÿ������ϰ����
	
	Nbox *box;                                     //�Ź���
	
	ev_timer timer;                            //��ͼ��ʱ��
	
	Point entPt;               //��ͼ�����
	Point outPt;               //��ͼ�ĳ���
	
	/****************** xhm added start***************************/
    Point tribesPt;			//��Ӫ���ɵ����أ�
	Point rangerPt;			//��Ӫ���������أ�
	Point religionPt;		//��Ӫа�ɵ����أ�

	int mapType;			//��ͼ���ͣ�
	int warType;			//��ս���ͣ���1,��ƽģʽ��2,ȫ��ģʽ��3,��Ӫģʽ��4,����ģʽ��
	int changePkType;		//pkģʽ�������ͣ���0,�����Ըı�PKģʽ 1,���Ըı�PKģʽ��

	int	levelLowerLimit;	//��ת��ȼ������ƣ�
	int levelUpperLimit;	//��ͼ��ת��ȼ�����ֵ��
	/******************* xhm added end****************************/
	int flgThk;
	
	/* ��ͼ˼����־���жϵ�ͼ�Ƿ�����*/
	bool flgCpy;					
	
	/*��ͼ��������ҵ�fd*/
	set<int> heroFd;  	
	
	/*�ɲ�ժ����Ʒ*/	
	map<string,TakeGoods*> takeGoodsMap;
	
	map<string,Bottle*> botInMap;	
	
	map<string,Trap*> trapInstMap;
	
	map<string,MonsterActiveBoss*> monActBoss;
	
	list<string> monAttRedList;
	
	list<string>::iterator redMon_it;
	
	int bruRedMonCtn;
	
	/*�Ա��Ӧid����*/
	map<string, set<string> > lPos_to_heroId;		//��ÿ�ŵ�ͼ�н������߼�����Ϊ��������ӦHero����ָ���б��map��������
	
	/*���е�����Ʒid*/
	map<string,Pick*> dropGoodsMap;
	
	map<string,MonsterBase *>::iterator escapePt_it;
	
	set<Point> dishPtSet;
	
	bool isActiveDishBru;                           //ϵͳ�Ƿ��ѵ���ˣ��Ǳ�ʾ�����
	
	/*��������*������һ���ĵ㣬�����������㣩*/
	Point centerPt;   
	
	/*�뾶*/
	size_t radius;
	
	/*������ɵ��ۼ�*/
	size_t randPtCtn;
	
public:	
	
	/*��̬���������Ƶ�ͼ�Ϲ���˼��ʱ��Ĵ�*/
	int	campEntFlag;		//������Ӫ�Ƿ�ɽ�ͼ�õ�ͼ���ֵ��0���ɽ��� 1�����ɽ��룩��
	static int count;                           //add chenzhen 6.1 ����˼��˼��ʱ���
public:
	
	/*��ʼ���Ź���*/
	void InitBox(void);
	
	/*��þŹ���*/
	Nbox* getBox(void);
	
	/*��õ�ͼid*/
	char* getMapId(void);
	
	/*��õ�ͼid*/
	char* getIdentity(void);
	
	/*��õ�ͼ��ȣ����أ�*/
	int getHeight(void);
	
	/*��õ�ͼ�߶ȣ����أ�*/
	int getWidth(void);
	
	/*��õ�ͼƫ����*/
	int getBaseDigst(void);
	
	/*��õ�ͼ��ȣ�����*/
	int getRow(void);
	
	/*��õ�ͼ��ߣ�����*/
	int getCol(void);

	/*���캯��*/
	Map_Inform(char *_mapId,char *_mapFilePath,char *_mapName,int _mapWidth,\
	int _mapHeight,int _row,int _col,int _baseDigst,Point _entPt,\
	Point _outPt,Point _tribesPt,Point _religionPt,Point _rangerPt,\
	map<string,MonsterBase *>& _monId_connect_monster,\
	map<string,const jumpId_infor*>& _jumpId_connect_jumpInfo,\
	map<string,TakeGoods*> &_takeGoodsMap,map<string,Bottle*> &_botInMap,\
	map<string,Trap*> &_trapInstMap,set<Point> _dishPtSet,Point _centerPt,size_t _radius,bool _flgCpy,\
	int warType=1,int _changePkType=0,int _mapType=0,int _campEntFlag=0,\
	int _levelLowerLimit=0,int _levelUpperLimit=100);
	
	/*���õ�ͼ�ϰ���*/
	void setMapHinder(vector< vector<int> > &_map_hinder);
	
	/*��õ�ͼ�ϰ�����Ϣ*/
	vector< vector<int> >& getMapHinder(void);     	//����map_hinder���ã��ر�С��
	
	/*��õ�ͼ������Ϣ*/
	map<string,MonsterBase *>& getMonId_connect_monster(void);
	
	map<string,const jumpId_infor*>& getJumpId_connect_jumpInfo(void);//�������ã�	
	
	/*��������*/
	~Map_Inform(void);       						
	
	
	/*��ʼ����ʱ��*/
	void initTimer(void);	
	
	/*��ͼ˼���ص�����*/
	virtual void mapThkCalBak(void) = 0;	
	
	/*��õ�ͼ���*/
	Point getEntPt(void);
	
	/*��õ�ͼ����*/
	Point getOutPt(void);
	
	/*��ø�����־*/
	bool getFlgCpy(void);	
	
	/*����Ź���id*/
	bool insertID(StyObj &obj);						
	
	/*�޸�heroId��Map_Inform�оŹ����ڵ�λ�ã���command_time_poll.cpp�ڵ���*/
	bool updateID(StyObj &obj,Point &newPt);			
	
	/*ɾ��һ��id*/
	bool deleteID(StyObj &obj);						//ɾ��hero id
	
	/*��ȡ��ҵĵ�ǰ���������*/
	bool getPtNow(StyObj &obj,Point &piexPt);
	
	/*�ж��߼����Ƿ���ȷ*/
	bool judgeLogPt(Point &logPt);

	/*��һ���߼���ת�����ַ���*/
	void logPtToStr(string &logPtStr,Point &logPt);
	
	/*���ػ�þŹ������ݺ�����ͨ��id*/
	void getStaInSrcVec(StyObj &obj,map<string,StyObj> &reselt);

	/*��lPos_to_heroId��ɾ��һ�������id*/
	bool eraseObjId(string &logPtStr,string &objId);

	/*��lPos_to_heroId�в���һ�������id*/
	bool insertObjId(string &logPtStr,string &objId);

	/*��ȡ����ĵ�ǰ���������*/
	bool getPtMonNow(string monId,Point &piexPt);
	
	/*��ȡƿ�޵ĵ�ǰ���������*/
	bool getPtBotNow(string botId,Point &piexPt);
	
	/*��ȡ����ĵ�ǰ���������*/
	bool getPtPetNow(string petId,Point &piexPt);
	
	/*��ȡ��ҵĵ�ǰ���������*/
	bool getPtHeroNow(string heroId,Point &piexPt);

	
	/*���ù�����Ϣ*/
	void setMonId_connect_monster(map<string,MonsterBase *>& _monId_connect_monster); 
	
	/*��ͼֹͣ˼��*/
	void stopThk(void);
	
	/*�������fd*/
	void inPutFd(int fd);
	
	/*ɾ�����fd*/
	void delFd(int fd);
	
	/*����ڴ˵�ͼ����*/
	int getFdSze(void);
	
	/*���õ�ͼ�������ڵ�ͼʵ��ָ��*/
	
	void setMonMap(void); 
	
	/*��ô˵�ͼ���������fd*/
	set<int> getHeroFd(void);
	
	/*���Ƶ�ͼ����ʵ���Լ���ˢ�ּ�¼��*/	
	void copyMapMon(map<string,MonsterBase*> &newMonIn,\
					char *newMapId,map<string,const jumpId_infor*>&\
					newjumpId_connect_jumpInfo);
							
	/*��ӡ���Ե�ͼ��Ϣ*/
	void printMonsterInform(void);
	
	/*��ô˵�ͼ��ڵ���߼�����*/
	Point getLogicEntPt(void);
	
	/*_index Ϊ��Ӫ���±꣬��ȡ��Ӧ��Ӫ����Ӫս�µ����ص����꣬0֧�ɣ�1�ڽ̣�2���� ����Ĭ��Ϊ֧��*/
	Point getCampWarPt(int _index);
	
	/*�������ŵ�ͼ��Ϣ*/
	virtual void initMap(void);
	
	/*���õ�ͼ˼�����ֵ*/
	void setThkFlg(int _thkFlg);
	
	/*ͨ������id��ù���ʵ��ָ��*/
	MonsterBase* getMonsterObj(string monId);
	
	/*ͨ������id��ù���ʵ��ָ��*/
	TakeGoods* getTakeObj(string takeGoodsId);
	
	/*�������������Ϣ*/
	void getAllMonObj(vector<MonsterBase*> &monObj);
	void getAllMonObj(vector< vector<MonsterBase *> > &);
	/*��ͣ�˵�ͼ����ˢ���ֵ�˼��*/
	virtual void stopAllLveMonThk(void) = 0;
	
	/*�����˵�ͼ��������ˢ���ֵ�˼��*/	
	virtual void reSetAllLveMonThk(void) = 0;
	
	/*���ƿ�ժȡ��Ʒ*/
	void copyTakeGoods(map<string,TakeGoods*> &_takeGoodsMap,char *_mapId);
	
	/*���ÿ�ժȡ��Ʒ��ͼʵ��ָ��*/
	void setTakeGoodsMap(void);
	
	/*��ȡժȡ��Ʒ�ĵ�ǰ���������*/
	bool getPtTakeGoodsNow(string takeGoodId,Point &piexPt);
	
	/*���ÿ�ժȡ��Ʒ��ͼʵ��ָ��*/
	void bruTakeMsg(void);
	
	/*ժȡ��Ʒ����*/
	void disperTakeGood(string _takeGoodId);
	
	/*��ȡ���ĵ�ǰ���������*/
	bool getPtWagonNow(string heroId,Point &piexPt);
	
	/*���ƿ�ժȡ��Ʒ*/
	void copyBotInMap(map<string,Bottle*>& _botInMap,char *_mapId);
	
	/*����ƿ����Ʒ��ͼ��Ϣ*/
	void setBotMap(void);
	
	/*ͨ��ƿ��ʵ��id���ƿ��ʵ��*/
	Bottle* getBotInst(char *_botId);
	
	/*ˢ����ͼƿ����Ϣ*/
	void brushBotMsg(void);
	
	/*��������*/
	void copyTrapVec(map<string,Trap*> &_trapInstMap,char *_mapId);
	
	/*���������ͼ��Ϣ*/
	void setTrapMap(void);
	
	/*ˢ����ͼ������Ϣ*/
	void brushTrapMsg(void);
	
	/*ͨ������ʵ��id�������ʵ��*/
	Trap* getTrapInst(char *_trapId);
	
	/*��ȡ����ĵ�ǰ���������*/
	bool getPtTrapNow(string trapId,Point &piexPt);
	
	/*��ȡ������Ʒ�ĵ�ǰ���������*/
	bool getPtPickNow(string pickid,Point &piexPt);
	
	/*��ȡ���ʵ��ָ��*/
	Hero* getHero(char *heroId);
	
	/*��ȡ���ʵ��ָ��*/
	void trapAttack(void);
	
/****************** xhm added start***************************/	
	/*
		@argument�� void
		  @return�� int 1 ��ƽģʽ 2 ȫ��ģʽ 3 ��Ӫģʽ 4 ����ģʽ
		@function�� ��ȡ��ǰ��ͼ��սģʽ
	*/
	int getWarType(void);
	
	/*
		@argument�� void
		  @return�� int 1 ��ƽģʽ 2 ȫ��ģʽ 3 ��Ӫģʽ 4 ����ģʽ
		@function�� ��ȡ��ǰ��ͼ��սģʽ
	*/
	void setWarType(int _index);	
	
	
	/*
		@argument�� void
		  @return�� int 0�������л���սģʽ 1�������л���սģʽ
		@function�� ��ȡ��ǰ��ͼ�л���սģʽ����
	*/
	int getChangePkType(void);
	
	/*
		@argument�� void
		  @return�� int 0���� 1���� 2���� 3����ս 4��Ӫս 5��������
		@function�� ��ȡ��ǰ��ͼ����
	*/	
	int getMapType(void);
	
	/*
		@argument�� void
		  @return�� int 0���� 1���� 2���� 3����ս 4��Ӫս 5��������
		@function�� ��ȡ��ǰ��ͼ����
	*/	
	void setMapType(int _index);	
	

	/*
		@argument�� void
		  @return�� int 0������Ӫ�ɽ��� 1������Ӫ���ɽ���
		@function�� ��ȡ��ǰ��ͼ������Ӫ�Ƿ���л�����
	*/	
	int getCampEntFlag(void);

	/*
		@argument�� void
		  @return�� int ��ǰ��ͼ��͵ȼ����ƣ�
		@function�� ��ȡ��ǰ��ͼ��͵ȼ����ƣ�
	*/	
	int getLevelLowerLimit(void);

	/*
		@argument�� void
		  @return�� int ��ǰ��ͼ��͵ȼ����ƣ�
		@function�� ��ȡ��ǰ��ͼ��ߵȼ����ƣ�
	*/	
	int getLevelUpperLimit(void);	
/****************** xhm added end***************************/
	
	/*��������*/
	virtual void GromonDead(char *monId);
	
	string getTd_roomid(void);
	
	void setTd_roomid(string td_inst_room);

	
	/*�������ձ�־*/
	virtual bool recoverCpy(void);
	
	/*��վŹ����е�����*/
	void clearBox(void);
	
	/*���Դ�ӡ�����д���б���Ϣ*/
	void testMonsterWait(void);
	
	/*���ù���Ĵ��������*/
	void initMonLvMager(void);
	
	/*�ж��߼����Ƿ�Ϊ�ϰ���<�����Ϊ�߼���>*/
	bool judgeLogPtHind(Point &logPt);
	
	/*���¸���������Ŀ*/
	virtual void sentSumMonMsg(void);
	
	/*ɱ��һ����*/
	virtual void killOneMon(void);	
	
	/*����Ұ��boss*/
	void insertBoss(MonsterActiveBoss* newBoss);
	
	/*���������ڴ˵�ͼ�ϵ�Ұ��BOSS�ĵ�ͼָ��*/
	void setMonBossMap(void) ;
	
	/*ˢ�������ڴ˵�ͼ�ϵ�Ұ��BOSS*/
	void brushMonBoss(void);
	
	/*���������ڴ˵�ͼ�ϵ�Ұ��BOSS*/
	void initMonBoss(void);
	
	/*�ж����������Ƿ�Ϸ�*/
	bool judgePiex(Point &piexPt);
	
	/*���ɹ�����Ŀ��Ϣ<���麯��>*/
	virtual char* getSumMonMsg(void) = 0;
	
	/*��ȡ����װ���ĵ�ǰ���������*/
	bool getPtEquipNow(string equipId,Point &piexPt);
	
	/*����������Ϣ*/
	void initTrap(void);
	
	/*���������ʱ��*/
	void reSetTrapThk(void);
	
	/*��ͣ�����ʱ��*/
	void stopTrapThk(void);
	
	/*���õ�ͼ��ʱ��,��ոõ�ͼ�е����е�����Ʒ*/
	void clearDropMap(void);
	
	/*������ÿ��ˢ��һ����ɱ�����Ĺ�*/
	void brushRedMon(void);
	
	/*������ÿֻ��ˢ�����ļ��ʱ��*/
	bool isNextRedMonOut(void);
	
	/*���һ���Ӵܵ�*/
	bool randEscapePt(Point &endFinPt);
	
	/*���*/
	TakeGoods * olderKandy(char *dishId,char *_onwerId,char *_nickName);

	/*����ĳ��������*/
	Pick* getDropPickInst(char *pickId);
	
	/*ɾ��ĳ��������*/
	void deleteDropInst(char *pickId);
	
	/*����ʱ�����������*/
	void insertDropInst(Pick *dropGoods);
	
	/*��̬������ϯ*/
	TakeGoods* newDishInst(char *dishId);
	
	/*�����ϯ*/
	void clearDish(void);
	
	/*ͨ���˵�idɾ��ĳ����ϯʵ��*/
	void delOneDish(char *takeGoodsId);
	
	/*�ж������߼���֮���Ƿ�����ϰ���*/		
	bool judgeLineCanPas(Point &logBeginPt,Point &logEndinPt);
	
	/*��ֱ��x���ֱ��֮���Ƿ����ϰ���*/
	bool verticlalLineX(Point &logBeginPt,Point &logEndinPt);
	
	/*��ֱ��y���ֱ��֮���Ƿ����ϰ��㣬���ϰ��㣬�򷵻ؼ٣�����Ϊ��*/
	bool verticlalLineY(Point &logBeginPt,Point &logEndinPt);
	
	/*�ж�һ��double�Ƿ�Ϊ����,������򷵻��棬��intValuesΪ������*/
	bool isIntDigst(double y,int &intValues);
	
	/*б��֮���Ƿ����ϰ��㣬���ϰ��㣬�򷵻ؼ٣�����Ϊ��*/
	bool slantLine(Point &logBeginPt,Point &logEndinPt);
	
	/*���õ�ͼƿ����Ϣ*/
	void initBot(void);
	
	/*���ݽ�ɫ���ɹ�������*/
	void initMonValues(Hero *enterHero);
	
	/*��̬������ϯ*/
	TakeGoods* newDishInst(TakeGoods *confDish);
	
	/*ϵͳ���*/
	void systemTreat(void);
	
	/*ϵͳ��͸�������*/
	TakeGoods* systemTreatAsist(void);
	
	/*ϵͳ��͸�������*/
	char* getSystemTreatId(void);
	
	/*���ϵͳ�Ƿ��ѵ���ˣ��Ǳ�ʾ���*/
	bool getIsActiveDishBru(void);
	
	/*����ϵͳ�Ƿ��ѵ���ˣ��Ǳ�ʾ���*/
	void setIsActiveDishBru(bool _isActiveDishBru);
	
	/*����ϵͳ��ϯΪ�ɳ�״̬*/
	void setSystemDishState(int _dishState);
	
	/*��ȡ����ĵ�ǰ���������*/
	bool getPtStatuaryNow(string statuaryId,Point &piexPt);
	
	/*��ʼ�������*/
	void initMonStatuary(void);
	
	/*ˢ����������*/
	void brushTable(void);
	
	/*��Դս��ˢ����Դ��*/
	void brushTakeSource(int _num,bool isPartyWar = false,int _flagA = -1);
	
	/*���ÿ�ժȡ��Ʒ������*/
	void initTakeGoods(void);
	
	/*���*/
	TakeGoods* olderKandy(char *dishId,char *deskInstId,char *_onwerId,char *_nickName);
	
	/*ϵͳ��������*/
	void activeCloseDish(void);
	
	/*������ɵ�*/
	bool randRescePt(Point &resultPt);
	
	/*��ʼ�������*/
	void initMonStatuaryByHero(Hero *hero);
	
	/*ˢ�������*/
	char* brushTaskMon(Hero *hero,char *npcId,int taskType = 3);
	
	/*�ٻ�n������*/
	void callTrap(size_t n);
	
	/*�ٻ���������*/
	void callTrap(const vector<string> &herIdSet);
	
	/*�ٻ����й�*/
	void callMon(MonsterBase *callBoss);
	
	/*�ٻ�n����*/
	void callMon(size_t n);
	
	private :
	
	void getHeroInstSet(const vector<string> &herIdSet,vector<const Hero*> &herInstVec);
	
	bool randCallMonPt(const Point &bossPt,Point &resultPt,const int &bossRadius);
};
#endif 
