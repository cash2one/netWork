#ifndef MONSTERBASE_H
#define MONSTERBASE_H
#include"game_fight_assist.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"astar.h"
#include <list>
#include<stdlib.h>
#include<map>
#include"data_structure_struct.h"
#include"library_head.h"
#include"libev.h"
#include"map_inform.h"
#include"hero.h"
#include"monster_other_action_function.h"
#include"hatValRue.h"

#include"bruMonInfor.h"
#include<time.h>
#include<unistd.h>
#include"other_define_data.h"
#include<math.h>
#include"skillBase.h"
#include"monster_base_asist.h"
#include"five_elements.h"
#include"boxAsist.h"
#include"wholeDefine.h"
#include"move_asist.h"
class SkillBase;
class Map_Inform;
extern const string DROP_BLOOD_ID; // move to cpp for safety = "X010";                  //������Ѫ
	
class MonsterBase
{
protected:

	char mapId[SHOR_MID_VALUE_LENGTH + 1];        //��Ӧ��ͼ��id   Evan add
	
	char nickName[LONG_MID_VALUE_LENGTH + 1];     //��Ӧ������ǳƣ�һ�����͵Ĺ�ֻ��һ���ǳƣ�
	
	char appendNickName[LONG_MID_VALUE_LENGTH + 1];   //����ָ�����
	
	char typeId[SHOR_MID_VALUE_LENGTH + 1];        //������ֵ���Ա�ʶID
	
	char identity[SHOR_MID_VALUE_LENGTH + 1];     //����ʵ��id
	
	char stage[SHOR_MID_VALUE_LENGTH + 1];  
	
	int  lifeUpperVal;  //��������ֵ
	
	int  lifeVal;        //��ǰ����ֵ
	
	int  magicUpperVal;  //ħ������ֵ   Evan add
	
	int  magicVal;       //��ǰħ��ֵ   Evan add
		
	Point pt;           //��ǰ����㣨��ͼ�����ص㣩	
	
	bool isAlive;        //����״̬,trueΪ���ţ�falseΪ��	
	
	Point born_pt;         //������
	
	ev_timer think_timer;    //��ʱ��
	
	int walk_ranage;      //��·��Χ
	
	int attack_range;     //������Χ
		
	Map_Inform *map_now;      //���ڵ�ͼָ��
	
	Astar *astar;             //a��
	
	char photoId[SHOR_MID_VALUE_LENGTH + 1];	         //ͼƬid
	
	Point logic_pt;          //��ǰ�߼���	
	
	
	vector<string> skill_list;   //�����б�
	
	list<HatVal>enmityValues ;   //����б�
	
	char perHerId[SHOR_MID_VALUE_LENGTH + 1];           // ����׷����Ŀ��id
	
	int hatRge;               //��޷�Χ	
	
	char selfMsg[IN_VIEW_LENGTH + 1];          //ˢ��ʱ����Ϣ	
	char outMsg[OUT_VIEW_LENGTH + 1];           //����֪ͨ	
	char otherMsg[MONSTER_MSG_LENGTH + 1];       //Ѱ·��ս����Ϣ
	
	int hrtSud;      //����
	
	int outHrt;     //����
	
	int inHrt;      //����
	
	/*�ı�ǰ*/
	int out_AttVal;    //�⹦����ֵ
	
	int in_AttVal;    //�ڹ�����ֵ
	
	int out_DefVal;    //�⹦����ֵ
	
	int in_DefVal;    //�ڹ�����ֵ
	
	
	int outAttVal;    //�⹦����ֵ
	
	int inAttVal;    //�ڹ�����ֵ
	
	int outDefVal;    //�⹦����ֵ
	
	int inDefVal;    //�ڹ�����ֵ
	
	int defSumVal;   //����ֵ�ܺ�
	
	/*ԭ����*/
	int hitCopy;
	
	int hit;        //����
	
	int crit;       //����
	
	int voids;      //����
	
	int tenacity;       //����	
	
	/*��ԭǰ*/
	int tena_city;       //����	
	
	int failGoodsLess;   //����������ֵ
	
	int failGoodsMost;   //����������ֵ
	
	int hatVal;      //���ֵ
	
	int gold;       //���
	
	set<string> failList;  //�����б�
	
	char kind[SHOR_MID_VALUE_LENGTH + 1];          	//�������֣�����ͨ����Ӣ��Boss��
	
	char type[SHOR_MID_VALUE_LENGTH + 1];           	//������Ϊ����
	
	
	int experience;        //����
	
	double angVal;         //bossŭ��ֵ
	
	bool flgRun;          //Boss�����ܱ�־
	
	char goodsOwner[IDL + 1]; // ��Ʒ��˭
	  
	
	double cdTime;         //��ͨ����cdʱ��
	
	ev_timer cdTimer;    //cd��ʱ��
	
	bool isCdCool;          //cd��ȴ�����ʾ����ȴ�����Թ����ˣ����ʾ�ɲ�������
	
	
	bool Rec;        	  //����ԭλ��־
	
	list<Point>selfWay ;        	//�Լ�Ѳ��·��
	
	list<Point>::iterator pt_it;    //�Լ�ÿ��Ѳ���յ㴦
	
	Point perLstPt;                 //�ع�ԭ�㣨����������߼��㣩
	
	vector<SkillBase*> skiInstSet;   //�����б�
	
	vector<SkillTime> moreAtt;       //��������ʱ�Լ���
	vector<SkillTime> moreAttDef;       //��������ʱ�Լ���
	vector<SkillTime> oneAtt;        //������ʱ�Լ���
	vector<SkillTime> oneAttPt;        //��Ѩ��ʱ�Լ���
	vector<SkillTime> oneAttDizz;        //��Ѩ��ʱ�Լ���
	vector<SkillTime> moreAttTen;       //��������ʱ�Լ���,����
	vector<SkillTime> moreAttHit;       //��������ʱ�Լ���,����
	
	bool skiBody;                    //����״̬,�����ƶ������ɹ���
	bool attackPoint;                //��Ѩ״̬,���ƶ��������ܹ���
	bool dizz;                       //ѣ��״̬�������ƶ���Ҳ���ܹ���	

	bool unEnemySta;                //�޵�״̬��trueΪ�޵�
	int rank;                       //�ȼ�
	int speed;                      //�ƶ��ٶ�
	LveCtnManger lveCtnMager;       //��������� 
	
	
	int fiveEleInt;      //�������Դ���ֵ
	int fiveEleRank;     //���еȼ�ֵ
	int fiveHurt;        //�����˺�ֵ
	
	FiveElem *fiveElement;	//����ʵ��

	int forGo;             //Ѱ·���������
	int goForCtn;         //����Ѱ·������
	int expTme;            //���鱶��
	int monyTme;           //��ұ���	
	int kindInt;           //��������<ת����int��>		
	
	bool repFlg;          //������Ӧ��־,true Ϊ������Ӧ	
	
	Point presuitPt;      //��׷�����ʱ���ж�����Ƿ��ƶ�
	
	
	char genAttId[SHOR_MID_VALUE_LENGTH + 1];       //��ͨ����id	
	
	
	int playCd;                     //��������ʱ��<����ɹ���˼��ʱ��>
	int plyCdCtn;
	bool isHurt;                    //�Ƿ񹥻�
	bool isInPatrol;                //�Ƿ���Ѳ����
	bool isBloodTmeOpenFlg;                //��Ѫ��ʱ���Ƿ��ѿ������ѿ���Ϊ��
	
	ev_timer bloodTimer;    //��ʱ��
	
	bool isPersuitHero;            //�Ƿ���׷�ˣ���Ϊ��
	
	int ownerAttriType;            //���ͣ�����Ϊ1����ӪΪ2��3Ϊ�����,4Ϊ�ɲɼ�����֣��������Ϊ0
	char ownerAttri[SHOR_MID_VALUE_LENGTH + 1];     //���ɣ���Ӫ����
	
	double attackRatio;          //��ɱ�����ְ���������
	
	bool isInnerAttack;          //ƫ�ڹ�Ϊ�棬ƫ�⹦Ϊ��
	
	bool isUsed;                 //����֣�Ϊ�ٱ�ʾ�˹ֻ�û�б�ˢ����������Ϊ��
	char taskOwnerId[SHOR_MID_VALUE_LENGTH + 1];  //�˹���˭�������
	
	ev_timer taskTime;        //����ִ��ʱ���ʱ��
	
	//�ٻ���
	bool isCallType;             //�Ƿ�Ϊ�ٻ��֣���Ϊ�ٻ���
	bool isCalled;               //�Ƿ��ѱ��ٻ�
	
	MonsterBase *callBoss;         //�ٻ��ֵ�boss
	
public:	
	MonsterBase(char *_mapId,char *_typeId,char *_nickName,char *_identity,char *_type,\
	char *_kind,int _experience,double _cdTime,int _lifeUpperVal,int _lifeVal,\
	int _magicUpperVal,int _magicVal,int _getHrtSud,int _outHrt,int _inHrt,\
	int _outAttVal, int _inAttVal,int _outDefVal, int _inDefVal,int _defSumVal,\
	double _hit,double _crit,int _voids,int _tenacity,int _moveRange,int _hatRange,\
	int _attRange,int _failGoodsless,int _failGoodsmost,int _hatVal,int _gold,\
	set<string>& _failId,Point _pt,int _rank,int _speed,int _fiveEleInt,int _fiveHurt,\
	int _fiveEleRank,int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,\
	vector<string> &_skiIdSet,char *_genAttId,double _angVal,int _ownerAttriType,\
	char* _ownerAttri,double _attackRatio,bool isInnerAttack,LveCtnManger _lveCtnMager);
	
	ev_timer moveTimer;				//�ƶ���ʱ��
	list<Point> keyPath;
	Point currPt, endPt;
	int lastSpeed;
	void startMoveTimer();
	void stopMoveTimer();
	int getSpeed();
	int getLastSpeed();
	void stopMove(bool _isChgePerPt = true);
	
	
	/*ɾ��һ�����ֵ*/
	void dropOneEnmityValues(HatVal &hatva);
	
	/*��ù��ﵱǰ����б�*/
	list<HatVal>& getEnmityValues(void);
	
	/*���һ�����ֵ*/
	HatVal* getOneEnmityValues(void);
	
	/*��ù��﹥������*/
	int getAttackRange(void);
	
	/*��ù������ڵ�ͼʵ��ָ��*/
	Map_Inform* getMap(void);
	
	/*��ù���ͼƬid*/
	char* getPhotoId(void);	
	
	/*���ù���ͼƬid*/
	void setPhotoId(char *_photoId);
	
	/*��ù����ǳ�*/
	char *getNickName(void);
	
	/*���ù�����������ֵ*/
	void setLifeUpperVal(int _lifeUpperVal);
	
	/*���ù��ﵱǰ����ֵ*/
	virtual void setLifeVal(int _lifeVal);   
	
	/*���ù���ħ������ֵ*/
	void setMagicUpperVal(int _magicUpperVal); 
	
	/*���ù��ﵱǰħ��ֵ*/
	void setMagicVal(int _magicVal);
	
	/*��ù�����������ֵ*/
	int getLifeUpperVal(void);
	
	/*��ù��ﵱǰ����ֵ*/
	int getLifeVal(void);
	
	/*��ù���ħ������ֵ*/
	int getMagicUpperVal(void);   
	
	/*��ù��ﵱǰħ��ֵ*/
	int getMagicVal(void);
	
	/*��ù���id*/
	char *getIdentity(void);
	
	/*��ù��ﵱǰ���������*/
   	Point getLocation(void);      //��õ�ǰλ��
	
	/*���ù��ﵱǰ���������*/
   	void setLocation(Point _pt, int flag = 0);  //�޸ĵ�ǰλ��
	
	/*��ù��ﵱǰ����״ֵ̬*/
	bool getLifeStation(void);    //�������״̬
	
	/*���ù��ﵱǰ����״ֵ̬*/
	void setLifeStation(bool _life);  //�޸�����״̬
	
	/*��ù������ڵ�ͼid*/
	char *getMapId(void);
	
	/*��ù���������������*/
	Point getBornPoint(void);
	
	/*��ù��ﵱǰ�߼������*/
	Point getLogicPt(void);
	
	/*���ù��ﵱǰ�߼������*/
	void setLogicPt(Point _logice_pt);
	
	/*������＼��id*/
	void pushSkillId(char *skillId);
	
	/*��ù��ﵱǰ����id�б�*/
	vector<string>& getSkillList(void);
	
	/*���ù��ﵱǰ���롱�������id*/
	void chageEny(char *_perHerId);
	
	/*��ù�������*/
	int getHrtSud(void) ;
	
	/*���ù�������*/
	void setHrtSud(int _hrtSud) ;
	
	/*��ù�������*/
	int getOutHrt(void);
	
	/*���ù�������*/
	void setOutHrt(int _outHrt) ;
	
	/*��ù�������*/
	int getInHrt(void);
	
	/*��ù�������*/
	int getWalkRange(void);
	
	/*���ù�������*/
	void setInHrt(int _inHrt) ;
	
	/*��ù����⹦*/
	int getOutAttVal(void) ;
	
	/*���ù����⹦*/
	void setOutAttVal(int _outAttVal) ;
	
	/*��ù����ڹ�*/
	int getInAttVal(void) ;
	
	/*���ù����ڹ�*/
	void setInAttVal(int _intAttVal) ;
	
	/*��ù������*/
	int getOutDefVal(void) ;
	
	/*���ù������*/
	void setOutDefVal(int _outDefVal) ;
	
	/*��ù����ڷ�*/
	int getInDefVal(void) ;
	
	/*���ù����ڷ�*/
	void setInDefVal(int _inDefVal) ;
	
	/*��ù����ܷ�*/
	int getDefSumVal(void) ;
	
	/*���ù����ܷ�*/
	void setDefSumVal(int _defSumVal) ;
	
	/*��ù�������*/
	int getHit(void) ;
	
	/*���ù�������*/
	void setHit(int _hit) ;
	
	/*��ù��ﱩ��*/
	int getCrit(void) ;
	
	/*���ù��ﱩ��*/
	void setCrit(int _crit) ;
	
	/*��ù�������*/
	int getVoids(void) ;
	
	/*���ù�������*/
	void setVoids(int _voids) ;
	
	/*��ù�������*/
	int getTenty(void) ;
	
	/*���ù�������*/
	void setTenty(int _tenacity) ;
	
	/*���ù����޷�Χ*/
	void setHatRge(int _hatRange) ;
	
	/*��ù�����С����ֵ*/
	int getFilGdsLess(void) ;
	
	/*���ù�����С����ֵ*/
	void setFilGdsLess(int _failGoodsLess) ;
	
	/*��ù���������ֵ*/
	int getFilGdsMore(void) ;
	
	/*���ù���������ֵ*/
	void setFilGdsMore(int _failGoodsMost) ;
	
	/*��ù�����ֵ*/
	int getHatVal(void) ;
	
	/*��ù�����*/
	int getGold(void) ;
	
	/*���ù�����*/
	void setGold(int _gold) ;
	
	/*�������ߺ���*/
	void out(void); 
	
	/*��ù�����Ϊ��������*/
	char* getType(void);             //add chenzhen 5.11
	
	/*���ù�����Ϊ��������*/
	void setType(char *_type);       //add chenzhen 5.11
	
	/*��ù�����������id*/
	char *getTypeId(void);
		
	/*��ù�������*/
	void setKind(char *_kind);      //add chenzhen 5.31
	
	/*��ù�����Ʒ������*/
	char* getGoodsOwner(void);//add chenzhen 6.8
		
	/* ���Boss�ֵ�ŭ��ֵ*/
	double getAngVal(void);	
	
	/* ����Boss�ֵ�ŭ��ֵ*/
	void setAngVal(double _angVal);	
	
	/*����ˢ������Ϣ����*/
	void formBshMsg(void);
	
	/*���ˢ������Ϣ����*/
	char* getBshMsg(void);
	
	/*��������˼������*/
	void initTimer(void);      //add chenzhen 6.5

	/*ˢ�ֺ������˴�Ϊ���麯��*/
	void brushMon(void);	
	
	/*Ѱ·׷������*/
	void findAttWay(Point &end,bool isPer = true);
	
	/*��װ����Ϣ���ͺ���,ȫ��ͼ����*/
	void sendMsg(string msg_perHero,string msg_others);
	
	/*��ñ��������ʵ��ָ��*/
	Hero* getHero(char *_perHerId);
	
	/*��ù��ﾭ��ֵ*/
	int getExperience(void);    //add chenzhen 6.25
	
	/*��ù����޷�Χ*/
	int getHatRge(void) ;
	 
	/*���ù�����ֵ*/
	void setHatVal(int _hatVal) ;
		
	/*���ù�������б�*/
	void setFailList(set<string>&  _failList) ;	
	
	/*��ù�������б�*/
	set<string>& getFailList(void);
	
	/*��ù�������*/
	char* getKind(void);            //add chenzhen 5.31
	
	/*���ù�����Ʒ������*/
	void setGoodsOwner(char *_owner);//add chenzhen 6.8 
	
	/*���ù������ڵ�ͼʵ��ָ�룬�˴�Ϊ���麯��*/
	void setMap(Map_Inform* _map);
	
	/*����ֹͣ˼������*/
	void stopThk(void);         //add chenzhen 6.5
	
	/*�����ٴ�����˼������*/
	void resetTimer(void);        //add chenzhen 6.6	
	
	/*Ѱ·*/
	void findSlfWay(Point endPt);
	
	/*��޷�Χ����*/
	void schRge(void);
	
	/*Boss���ܺ���*/
	void escape(void);

	/*���������������˴�Ϊ���麯��*/
	virtual void die(bool flgInit = false);		
	
	/*��ʼ������ʵ��ָ���б�*/
	void initSkiInst(vector<string> &_skiIdSet);
	
	/*��ü���id�б�*/
	void getSkiIdSet(vector<string> &skiIdSet);
	
	/*���diedNoThink��ֵ*/
	virtual bool getDiedNoThink(void);			
	
	/*����һ�����ֵ*/
	virtual void InpushEnmityValues(HatVal &hatva);	
	
	/*������������*/
	virtual ~MonsterBase(void);	
	
	/*��ȡ��޷�Χ�ڵ����Ϊvector*/
	void exchageHat(vector<string> &_herIdSet);
	
	/*����˼���������˴�Ϊ���麯��*/
	virtual void response(void) = 0;		
	
	/*���ƹ�����Ϣ�������˴�Ϊ���麯��*/
	virtual MonsterBase* copyMon(char *_mapId) = 0;	
	
	/*ʹ�ü���*/
	bool useSkill(vector<string> &herId,bool _station = false);
	
	/*�����������ܴ�����*/
	void delSki(void);
	
	/*���Դ�ӡBoss����*/
	void testPrintSki(void);
	
	/*�������ɼ���id*/
	string asistSkiId(string &_skiId);
	
	/*������Ϣ���ɺ���*/
	void formAttMsg(char *msg_others,int legnth,Hero *hitHero,int attack,int attFlg,int voidFlg);
	
	/*���㱩����*/
	int coutFlgCrit(double &critTme);
	
	/*�����ͨ����ֵ*/
	int countAttPerGen(Hero *perHero);
	
	/*����������*/
	int coutFlgVoid(Hero *perHero,double &hitPer);
	
	/*�����˺�ֵ������Ҳ������*/
	int countAttVal(int genAtt,Hero *perHero,int &attTypFlg,int &voidFlg,double skiHrtRatio = 0.0,double _cdTime = 1.0);
	
	/*������Һ���*/
	void attPerHero(char *msg_others,int length,Hero *perHero,bool moveFlg = false,double skiHrtRatio = 0.0,double _cdTime = 1.0);
	
	/*��������Ƿ�ɹ����жϺ���*/
	bool judgeAtt(Hero *perHero);
	
	/*Ⱥ��������Ϣ���ɺ���*/
	void skiAttHero(char *msg_others,int length,vector<string> &heroIds,char *skiId,double skiHrtRatio,double _cdTime);
	
	/*�ж��Ƿ�ΪBoss�֣��Ƿ���1�����򷵻�0*/	
	bool judgeBoss(void);
	
	/*����ʱ�Լ��ܹ���*/
	void inputHitTime(double _cdTimes,int _flgType = 0,int _dropBlood = 0,\
	char *_heroId = NULL,int _outAttVals = 0,int _inAttVals = 0,\
	int _outDefVals = 0,int _inDefVals = 0);
	
	/*����ʱ�Լ��ܹ���*/
	void inputHitTime(char *attId,int typeEffect,double lastTme,int value);
	
	/*����ʱ�Լ��ܹ���*/
	void hitedEffectBySki(SkillTime &_skiTme);
	
	/*���ñ��������༼��*/
	void callOneAtt(void);
	
	/*���ñ��ǻ������༼��*/
	void callMoreAtt(SkillTime &_skiTme);
	
	/*�������зǻ������༼��*/
	void dealMoreAtt(void);
	
	/*�������зǻ������༼��*/
	void hitedSkiFun(void);
	
	/*���ñ��������༼��,��Ѩ*/
	void callOneAttPt(void);
	
	/*���ñ��������༼��,ѣ��*/
	void callOneAttDizz(void);
	
	/*������Ѫ��Ϣ�γ�*/
	void formSelDropBldMsg(SkillTime &_skiTme,char *msg_other,int length);
	
	/*������Ѫ��Ϣ�γ�*/
	void sendDropBldMsg(SkillTime &_skiTme,char *msg_other);
	
	/*������Ѫ��Ϣ�γ�*/
	void formDropBldMsg(SkillTime &_skiTme,char *msg_other,int length);
	
	/*���湥����ֵ*/
	void storeAttDef(void);
	
	/*���ù��������༼��*/
	void dealMoreAttDef(void);
	
	/*�жϹ����Ƿ�ﵽ����,���߽�������*/
	bool judgeAttDef(void);
	
	/*�ı乥����ֵ*/
	void reduceAttDef(SkillTime &skiTme);
	
	/*��ԭ������ֵ*/
	void recoverAttDef(SkillTime &skiTme);
	
	/*�ж������Ƿ�ﵽ����,���߽�������*/
	bool judgeAttTen(void);
	
	/*������*/
	void reduceAttTen(SkillTime &newSkiTime);
	
	/*�ָ�����*/
	void recoverAttTen(SkillTime &newSkiTime);
	
	/*���û������༼��,��������*/
	void dealMoreAttTen(void);
	
	/*������*/
	void reduceAttHit(SkillTime &newSkiTime);
	
	/*�ָ�����*/
	void recoverAttHit(SkillTime &newSkiTime);
	
	/*�ж������Ƿ�ﵽ����,���߽�������*/
	bool judgeAttHit(void);
	
	/*���û������༼��,��������*/
	void dealMoreAttHit(void);
	
	/*�����޵�״̬*/
	void setUnEnemySta(bool _unEnemySta);
	
	/*�����޵�״̬*/
	bool getUnEnemySta(void);
	
	/*��õȼ�*/
	int getRank(void);
	
	/*���ù���ֵ*/
	void initRecAttDef(void);
	
	/*���ù���������ʱ�Լ���Ӱ��*/
	void initHitedSki(void);
	
	/*���ñ��ֵ*/
	void initFlgVal(void);
	
	/*�������ĳ���б����������Ϊ�棬����룬������ɾ��*/
	void dealPetLst(bool _flg);
	
	/*�������ĳ���б�������ȫɾ��*/
	void dealPerByEmy(void);
	
	/*�жϴ�������*/
	bool dealLveCtn(void);
	
	/*�ж�ʱ�乻��*/
	bool dealDurTme(void);
	
	/*�ж�׷��������Ƿ��ƶ�,�ƶ��򷵻���*/
	bool jdgSmePt(Point heroPt);
	
	/*������Ϣ*/
	void formOutMsg(void);
	
	/*���������Ϣ*/
	char* getOutMsg(void);
	
	/*��ù����������*/
	LveCtnManger getLveMag(void);
	
	/*��ù��ﾭ�鱶��*/
	int getExpTme(void);
	
	/*��ù����Ǯ����*/
	int getMonyTme(void);
	
	/*��ȡ��������*/
	FiveElem *getFiveElem();
	
	/*�����ƶ��̶�ͷ�ļ�*/
	void getMovHeadMsg(string &moveMsg);
	
	/*�������͵���int�ͱ�ʾ*/
	void kindIntInit(void);

	
	/*Ѳ�߹��߶�Ƶ�ʣ�����͸���ͬʱ�����жϣ�*/
	bool judgeGoFor(void);
	
	/*��forGoȫ�����ж�10ȡ��������*/
	void dealGoFor(void);
	
	/*���ù�������*/
	void initMonVal(void);
	
	/*���Թ���������*/
	int testLveManger(void);
	
	/*���������Ӧ���ֵ*/
	bool getRepFlg(void);
	
	/*�޸�������Ӧ���ֵ*/
	void setRepFlg(bool _repFlg);	
	
	/*��ʼ��׷�ٵ�����*/
	void initPersuitPt(void);
	
	/*ˢ�ֺ���*/
	void outScence(void);
	
	/*����������*/
	void reLife(void);
	
	/*���ù��ﲿ������*/
	void initMonsterBaseAsist(void);
	
	/*����������������*/
	virtual void initMonsterALL(void);
	
	/*��ʱ����������Ϣ*/
	void sendOutMsg(void);
	
	/*��Ѱ·Ѱ�����߼���ת�������ص�*/
	void exchgeWayRod(void);
	
	/* �麯���������ִӿͻ�����ʧ */
	virtual void disappear();
	
	/* �麯����ʹ�����־�ֹ���� */
	virtual void StandStill();
	
	
	/*���������ʼ����������*/
	virtual void initOnwer(Hero *owner);
	
	/*��������ʱ���ͷż���ʵ��*/
	void deleteSkillInst(void);
	
	/*�ж϶����Ƿ񲥷���*/
	bool isPlayOver();
	
	/*·��ƽ������*/
	void smoothRoadPt(void);
	
	/*��õ���׶�*/
	char *getStage(void);
	
	/*�����Ѫ����*/
	void recoverBloodSelf(void);
	
	/*·��ƽ������,���õ�ͼ�����һ������*/
	void smoothRoadPtSelf(void);
	
	/*���㱩����<������ĵĹ�ʽ20130110*/
	int coutFlgCrit(Hero *perHero,double &critTme);
	
	/*��Ѫ�����ж�*/
	bool isRecoverBlood(void);
	
	/*��û�Ѫ��ʱ�����ֵ*/
	bool getIsBloodTmeOpenFlg(void);
	
	/*���û�Ѫ��ʱ�����ֵ*/
	void setIsBloodTmeOpenFlg(bool _isBloodTmeOpenFlg);
	
	/*������������ʱ����˼��ʱ��*/
	void initResponseAgain(void);
	
	/*���︴ԭλ���ж�*/
	bool reBack(void);
	
	/*��ð��ɣ���Ӫ����*/
	char* getOwnerAttri(void);
	
	/*�޸İ��ɣ���Ӫ����*/
	void setOwnerAttri(char *_ownerAttri);
	
	/*��ù�����ɣ���Ӫ����*/
	int getOwnerAttriType(void);
	
	/*�޸Ĺ�����ɣ���Ӫ����*/
	void setOwnerAttriType(int _ownerType);
	
	/*��Ӫ�ֵı任*/
	void exchgeCampAttriType(int _ownerType);	
	
	/*�ж��Ƿ�����*/
	int ctnHitRatio(int hitVoid);
	
	/*�ж��Ƿ�����*/
	int ctnCritRatio(Hero *hitPerson);
	
	/*����֣�׷�Ӵ�����������Ϣ*/
	bool appendTaskInfo(Hero *hero);
	
	/*��������棨�жϴ˹��Ƿ�ˢ����*/
	bool getIsUsed(void);
	
	/*����ִ��ʱ�䵽*/
	void taskMonCalBack(void);
	
	/*�ж�����ֵ������Ƿ���*/
	bool judgeTask(void);
	
	/*�ٻ�����*/
	void callTrap(const vector<string> &herId);
	
	/*�����ٻ��ֱ�־ֵ*/
	void setIsCallType(bool _isCallType);
	
	/*����ٻ����ֵ*/
	bool getIsCallType(void);
	
	/*�����ٻ����ٻ������ı�־ֵ*/
	void setIsCalled(bool _isCalled);
	
	/*����ٻ����ٻ������ı�־ֵ*/
	bool getIsCalled(void);
	
	/*����cd��ȴ���ֵ*/
	void setIsCdCool(bool _isCdCool);
	
	/*�ٻ���*/
	void callMon(void);
	
	void setCallBoss(MonsterBase* _callBoss);
	
	private:
	
	double getLength(Point heroPt);
	
	void sortByPt(void);	
	
	//�ж��ٻ��ֵ�boss�Ƿ�����������Ϊ����
	bool isCallBossLife(void)  ;
};
#endif
