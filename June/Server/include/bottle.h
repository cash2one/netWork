#ifndef BOTTLE_H
#define BOTTLE_H
#include"libev.h"
#include<set>
#include<string>
#include"data_structure_struct.h"
#include"command_return_define_data.h"
#include"other_define_data.h"
#include"boxAsist.h"
const int TYPEBOTTLE = 2;

using namespace std;
class Hero;
class Map_Inform;
class Bottle
{
	char id[SHOR_MID_VALUE_LENGTH + 1];	              //ʵ��id
	char typeId[SHOR_MID_VALUE_LENGTH + 1];            //����id
	char photoId[SHOR_MID_VALUE_LENGTH + 1];           //ͼƬid
	char name[SHOR_MID_VALUE_LENGTH + 1];              //����
	int lifeVal;              //����ֵ
	int lifeValUpper;         //��������ֵ
	int hurt;                  //ÿ���˺�
	char bornMsg[IN_VIEW_LENGTH + 1];           //������Ϣ
	char outMsg[OUT_VIEW_LENGTH + 1];		      //������Ϣ
	Point logicPt;            //�߼�����
	Point pt;                 //��������
	Map_Inform *map_now;         
	static int count;
	bool bruOut;
	ev_timer think_timer;    //��ʱ��
	
	int brushStyle;          //ˢ��ģʽ  
	double bloodPre;     //�����߻�Ѫ
	double magicPre;    //�����߻���
	
	char dropStage[SHOR_MID_VALUE_LENGTH + 1];       //����׶�
	size_t dropNum;           //�����ټ�
public:
	Bottle(char *_typeId,int _lifeVal,int _hurt,int _brushStyle,double bloodPre,double magicPre,char *_name,size_t dropNum,char* _dropStage,char *_photoId);
	
	/*����ˢ����Ϣ*/
	void formBornMsg(void);
	
	/*���id*/
	char* getId(void);
	
	/*����������Ϣ*/
	void formOutMsg(void);
	
	/*������ʵ��ָ��*/
	Hero* getHero(char *heroId);
	
	/*���õ�ͼʵ��ָ��*/
	void setMap(Map_Inform *_map_now);
	
	/*����߼������*/
	Point getLogicPt(void);

	/*����ƿ��*/
	Bottle* copyBottle(char *_mapId);
	
	/*���ƿ��id*/
	char* getBottleId(void);
	
	/*����ʵ��id*/
	void setInstId(char *_id);
	
	/*ˢ��ƿ��*/
	void brushMsg(void);
	
	/*ƿ�޴ӵ�ͼ����*/
	void disperMsg(void);
	
	/*������������*/
	void setPiexPt(Point _pt);

	/*��������*/
	~Bottle(void);
	
	/*����ƿ��<���غ������ڶ�ȡ��ͼ�����ļ�������>*/
	Bottle* copyBottle(Point _pt);
	
	/*���ƿ�޵�����ֵ*/
	int getLifeVal(void);
	
	/*����ƿ�޵�����ֵ*/
	void setLifeVal(int _lifeVal);
	
	/*���������Ϣ*/
	char* getBronMsg(void);
	
	/*���������Ϣ*/
	char* getOutMsg(void);
	
	/*�����������*/
	Point getPiexPt(void);
	
	/*����ƿ�޵�����ֵ*/
	void beAttack(const char* attackId);
	
	/*���ƿ���˺�ֵ*/
	int getHurt(void);
	
	/*������ٴ�ˢ���ж�*/
	bool isAlive(void);
	
	/*�������Ϣ����*/
	bool sendDieMsg(void);	
	
	/*�Ѵ�������־*/
	bool dieOutFlg(void);
	
	/*�Ѵ�������־*/
	bool aliveFlg(void);
	
	/*ȡ��ͼʵ��ָ��*/
	Map_Inform* getMap(void);
	
	/*ȡ����id*/
	char* getTypeId(void);
	
	/*���ˢ��ģʽֵ*/
	int getBrushStyle(void);
	
	/*����ƿ������*/
	void initBot(void);
	
	//��ȡѪ����
	int getLifeUpperVal();
	
	/*�����߻�Ѫ�İٷֱ�*/
	double getBloodPre(void);
	
	/*�����߻����İٷֱ�*/
	double getMagicPre(void);
	
	const char* getDropStage(void) const;
	
};
#endif
