#ifndef TRAP_H
#define TRAP_H
#include"libev.h"
#include<set>
#include<string>
#include"data_structure_struct.h"
#include"command_return_define_data.h"
#include"other_define_data.h"
#include"boxAsist.h"
const int TYPETRAP = 3;

using namespace std;
class Hero;
class Map_Inform;
class Trap
{

	char id[SHOR_MID_VALUE_LENGTH + 1];	              //ʵ��id
	char typeId[SHOR_MID_VALUE_LENGTH + 1];            //����id
	char photoId[SHOR_MID_VALUE_LENGTH + 1];           //ͼƬid
	char name[SHOR_MID_VALUE_LENGTH + 1];              //����
	int attackRge;                  //��������
	double cdTme;              //cd ʱ��	
	char bornMsg[IN_VIEW_LENGTH + 1];           //������Ϣ
	char outMsg[OUT_VIEW_LENGTH + 1];		      //������Ϣ
	char attMsg[TRAP_ATT_LENGTH + 1];
	Point logicPt;            //�߼�����
	Point pt;                 //��������
	Map_Inform *map_now;         
	static int count;

	ev_timer think_timer;    //��ʱ��
	int cdPlay;              //��������ʱ��<�����˼��ʱ��>
	int playCtn;             //��������ʱ��
	bool isAtt;              //�Ƿ񹥻�
	int attStyle;            //����ģʽ
	double attPercent;       //�˺��ٷֱ�
	
	bool isDispear;          //�Ƿ����ʧ
	
	bool isWarning;          //�Ƿ��о�ʾ����Ϊ��
	char warningMsg[IN_VIEW_LENGTH + 1];           //��ʾ��Ϣ
	ev_timer warnTimer;    //��ʾ��ʱ��
	double warnTime;          //��ʾʱ��
	bool isWarned;           //ֻҪԤ�������ͱ�����
	bool isCalled;       //�Ƿ���boss�ٻ������ı��ֵ����Ϊ�ٻ�����
	bool isUsed;             //�Ƿ��ã���Ϊ�Ѿ�ˢ������
	bool isMove;         //�Ƿ�����ƶ�����Ϊ����
public:
	Trap(char *_typeId,double _attack,int _attackRge,int _attStyle,double _cdTme,bool _isWarning,double _waringTime,char *_name,char *_photoId);
	
	/*����ˢ����Ϣ*/
	void formBornMsg(void);
	
	/*���id*/
	char* getId(void);
	
	/*����������Ϣ*/
	void formOutMsg(void);	
	
	/*���õ�ͼʵ��ָ��*/
	void setMap(Map_Inform *_map_now);
	
	/*����߼������*/
	Point getLogicPt(void);

	/*��������*/
	Trap* copyTrap(char *_mapId);
	
	
	/*����ʵ��id*/
	void setInstId(char *_id);
	
	/*ˢ��ƿ��*/
	void brushMsg(void);
	
	/*ƿ�޴ӵ�ͼ����*/
	void disperMsg(void);
	
	/*������������*/
	void setPiexPt(Point _pt,bool flag = false);

	/*��������*/
	~Trap(void);
	
	/*��������ʵ��id*/
	char* getTrapId(void);
	
	/*��������<���غ������ڶ�ȡ��ͼ�����ļ�������>*/
	Trap* copyTrap(Point _pt,bool _isCalled);	
	
	/*�������Ĺ�������*/
	int getAttackRge(void);
	
	/*������������ɵ�ͼ˼������*/
	double getCdTme(void);
	
	/*���������Ϣ*/
	char* getBronMsg(void);	
	
	/*��������*/
	bool AttackPerson(void);
	
	/*���������Ϣ*/
	char* getOutMsg(void);
	
	/*�����������*/
	Point getPiexPt(void);
	
	/*������ʱ��*/
	void initTimer(void);
	
	/*����ص�����*/
	bool calBack(void);
	
	/*����������Ϣ*/
	void initTrap(void);
	
	/*��ͣ��ʱ��*/
	void stopTimer(void);		
	
	/*����Ƿ����ʧ�ı��ֵ*/
	bool getIsDispear(void);
	
	/*������ʧ��ʱ��*/
	void initTimerDispear(void);
	
	/*Ԥ������*/
	bool warning(void);
	
	/*�����ٻ����ֵ*/
	void setIsCalled(bool _isCalled);
	
	/*����ٻ����ֵ*/
	bool getIsCalled(void);
	
	/*����Ƿ�ˢ���ı��ֵ*/
	bool getIsUsed(void);
	
	/*�ж��Ƿ�����ƶ�*/
	bool getIsMove(void);	
	
	private:
	
	/*�������Ĺ�����*/
	double getAttack(void);
	
	/*���㹥����*/
	int getAttackPow(int heroLife);
	
	/*������ʵ��ָ��*/
	Hero* getHero(char *heroId);
	
	/*�����Ѫ����*/
	int judgeAttackPersonDie(Hero *hitedHero,int attPow);	
	
	/*�Ƿ���cd����������*/
	bool isPlayCd(void);
	
	/*�������徯ʾ��Ϣ*/
	void initWarnDispear(void);
	
	/*�жϹ�����Χ���Ƿ�����*/
	bool isAttackPerson(set<string> &HeroIdSet);
	
	/*���ɾ�ʾ��Ϣ*/
	void formWarnMsg(void);
	
	/*�ƶ���������*/
	void move(Point piexPt);
	
};
#endif
