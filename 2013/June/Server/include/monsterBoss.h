#ifndef MONSTERBOSS_H
#define MONSTERBOSS_H
//#include"monsterBase.h"
#include"monsterBase.h"
#include"map_inform.h"
class Map_Inform;
class MonsterBoss : public MonsterBase
{
private:
	char *mapId;        //��Ӧ��ͼ��id   Evan add
	char *nickName;     //��Ӧ������ǳƣ�һ�����͵Ĺ�ֻ��һ���ǳƣ�
	char *typeId;        //��������
	char *identity;     //id
	int  lifeUpperVal;  //��������ֵ
	int  lifeVal;        //��ǰ����ֵ
	int  magicUpperVal;  //ħ������ֵ   Evan add
	int  magicVal;       //��ǰħ��ֵ   Evan add
	Point pt;           //��ǰ����㣨��ͼ�����ص㣩
	int attack;         //������
	int eat;            //���
	int life_station;   //����״̬,�����жϺ�ʱ�����ٶ���	
	Point born_pt;         //������
	ev_timer *think_timer;
	int walk_ranage;      //��·��Χ
	int attack_range;
	Map_Inform *map_now;      //���ڵ�ͼָ��
	Astar *astar;

	char *photoId;	         //ͼƬid
	Point logic_pt;          //��ǰ�߼���	
	vector<string> skill_list;   //�����б�
	list<HatVal> enmityValues;    //����б�
	
	char* perHerId;           // ����׷����Ŀ��id
	Point perLstPt;           //��һ�ε�Ѱ·�յ�(�߼����������ظ�Ѱ·   
	list<Point>selfWay;         //�Լ�Ѳ��·��
	Point goWaPt;              //��һ��ȥ׷Ŀ���뿪�Լ���Ѳ�ߵ�	
	list<Point>::iterator pt_it ;    //�Լ�ÿ��Ѳ���յ㴦
	
	int hatRge;               //��޷�Χ
	
	string selfMsg;          //ˢ��ʱ����Ϣ
	
	Point endFinPt;         //Ѳ���յ�
	
	
	list<Point>runWay;     //����·��
	Point mapOutPt;        //��ͼ�ĳ��㣬boss����������
	list<Point>::iterator runPt_it ;    //�Լ������յ㴦
	int flgRun;            //���ܱ�־
private:
	void getSlfRd(Point endpt);
	void sentMsg(set<string> &id_box,string &msg_perHero,string &msg_others);
	void schRge(void);
	Hero* getHero(char *heroId);
	void monfdWay(Point end);
	void getRdPt(string &msg_others);
	void attPerHero(string &msg_perHero,string &msg_others,Hero *perHero);
	
	void die(void);
	
	
	
public :
	MonsterBoss(char *_mapId,char *_typeId,char *_nickName,char *_identity, int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal, Point _pt, int _attack, int _eat,int _walk_ranage,int _attack_range,char *_photoId,Point logicPt,Map_Inform *_map);
	void initTimer(void);
	void attackHero(void);	
	~MonsterBoss(void);
	
	MonsterBase* copyMon(MonsterBase* newMon,Map_Inform *_mapNow);
	void setMap(Map_Inform* _map);
	
	virtual void response(void);  
	void thinkCallBack(struct ev_loop *loop,ev_timer *time,int revents);
	
	virtual char* getPhotoId(void);
	virtual void setPhotoId(char *_photoId);
	
	virtual int getAttackRange(void);
	virtual int getWalkRange(void);
	
	virtual Map_Inform* getMap(void);
	virtual char *getNickName(void);
	virtual char *getMapId(void);
//	virtual char *getTypeId(void);
	virtual char *getIdentity(void);	
	virtual void setLifeUpperVal(int _lifeUpperVal);
	virtual int getLifeUpperVal(void); //�����������ֵ 
	virtual void setMagicUpperVal(int _magicUpperVal); 
	virtual int getMagicUpperVal(void);   //���ħ������ֵ	
	virtual void setLifeVal(int _lifeVal);   //�޸ĵ�ǰ����ֵ	
	virtual int getLifeVal(void);
	virtual void setMagicVal(int _magicVal); //�޸ĵ�ǰħ��ֵ 
	virtual int getMagicVal(void);
   	virtual Point getLocation(void);      //��õ�ǰλ��
   	virtual void setLocation(Point _pt);  //�޸ĵ�ǰλ��
	virtual void setAttack(int _attack);   //�޸Ĺ�����
	virtual int getAttack(void);           //��ù�����	
	virtual int getEaten(void);            //��õ�ǰ���ֵ
	virtual void setEaten(int _eat);       //�޸����ֵ	
	virtual int getLifeStation(void);    //�������״̬
	virtual void setLifeStation(int _life);  //�޸�����״̬
	virtual Point getBornPoint(void);
	
	virtual void setLogicPt(Point _logice_pt);
	virtual Point getLogicPt(void);
	virtual void pushSkillId(char *skillId);
	virtual vector<string>& getSkillList(void);
	virtual void chageEny(char *_perHerId);
	virtual list<HatVal>& getEnmityValues(void) ;
	virtual void InpushEnmityValues(HatVal &hatva);
	virtual HatVal* getOneEnmityValues(void);
	virtual void dropOneEnmityValues(HatVal &hatva);
	
	virtual void brushMon(void);

	virtual void formBshMsg(void);
	virtual string& getBshMsg(void);
	
	
	
private:	
	void escape(void);
	void getRunWayPt(string &msg_others);
	
	
};
#endif


