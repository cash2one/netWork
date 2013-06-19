#ifndef TAKE_GOODS_H
#define TAKE_GOODS_H
#include<string>
#include<set>
#include<map>
#include<time.h>
#include"data_structure_struct.h"
#include"command_return_define_data.h"
#include"other_define_data.h"
#include"boxAsist.h"
#include"libev.h"
#include"astar.h"
const int TYPETAKEGOODS = 0;

using namespace std;
class Map_Inform;
class Hero;
class TakeGoods
{
	Point pt;                 //��������
	char id[SHOR_MID_VALUE_LENGTH + 1];	              //ʵ��id
	char typeId[SHOR_MID_VALUE_LENGTH + 1];            //����id
	char photoId[SHOR_MID_VALUE_LENGTH + 1];           //ͼƬid
	char name[SHOR_MID_VALUE_LENGTH + 1];              //����
	char bornMsg[IN_VIEW_LENGTH + 1];           //������Ϣ
	char outMsg[OUT_VIEW_LENGTH + 1];		      //������Ϣ
	char dishOwner[SHOR_MID_VALUE_LENGTH + 1];    //��ϯ��������
	char dishNewNme[SHOR_MID_VALUE_LENGTH + 1];   //��ϯ�����׷�ӵ�������
	char offerWords[SHOR_MID_VALUE_LENGTH + 1];   //��ʾ��Ϣ
	Point logicPt;            //�߼�����
	Map_Inform *map_now;          //��ͼʵ��ָ��
	char goodsId[SHOR_MID_VALUE_LENGTH + 1];               //��ƷId
	static int count;
	bool bruOut;
	bool isDispear;                //�ɼ����Ƿ����ʧ
	bool trigByMsg;                //�Ƿ�Ϊ��Ϣ����
	ev_timer think_timer;    //��ʱ��
	
	int takeModle;           //�ɲɼ���Ʒͬʱ�ɲɼ�������
	int taskStyle;           //�ɲɼ���Ʒ������
	int brandType;			//������
	double takeTme;         //�ɼ�����ʱ��
	set<string> onwerSet;   //�ɼ���id�ļ���
	bool isMove;            //����ᶯ
	
	Astar *astar;             //a��
	ev_timer moveTimer;		 //�ƶ���ʱ��
	Point bornPiexPt;        //�������ص�
	Point bornLogPt;         //�����߼���
	int speed,lastSpeed;               //�ƶ��ٶ�
	
	bool flgEndPt;           //Ѱ·�յ��Ƿ���Ѱ��
	Point endFinPt;
	
	
	int durTme;              //��ϯ����ʱ��
	struct timeval beginTme;	//��ϯ��ʼʱ��
	
	int moveCtn;               //�˶�ʱ���ۻ�
	int moveRate;               //�˶���Ƶ��
	
	int dishState;              //��ϯ״̬��0��ʾ��ɫ��Ĳˣ�1��ʾϵͳ��Ĳˣ���������ʱ�仹û�е������ܳԣ�2��ʾϵͳ��Ĳˣ���ʱ�䵽�ˣ����Գԣ�
	
	bool isDished;              //�Ƿ�һ��ˣ��Ǳ�ʾˢ���������в˵����ӣ������ǿ����ӣ�
	char emptyPhotoId[SHOR_MID_VALUE_LENGTH + 1];           //�����ӵ�ͼƬid
	bool chgState;              //��ֹ��ε�bursh���������ʾ����ˢ������ˢ��
	
	bool isCampSource;          //�Ƿ�����Ӫ��Դս�������Դ,��Ϊ��
	bool isUsed;                //�Ƿ��Ѿ�ˢ���ˣ���Ϊ��
	
	
	char ownerNickName[SHOR_MID_VALUE_LENGTH + 1];  //�����ĵ��ǳƣ����ڰ���ս���棩
	int ownerType;             //�������Լ������ڰ���ս���棩
	char ownerValue[SHOR_MID_VALUE_LENGTH + 1];  //��������ֵ�����ڰ���ս���棩
	bool isInterrupt;         //�Ƿ��ϣ���Ϊ���Ա����
public:
	Point currPt,endPt;
	list<Point>keyPath;
	
	
public:
	TakeGoods(char *_typeId,char *_goodsId,char *name,char *_photoId,\
	bool _isDis,bool _trigByMsg,int _takeModle,int _taskStyle,\
	int _brandType,double _takeTme,char *_offerWords,int _durTme,\
	bool _isMove,bool _isInterrupt);
	
	/*��������*/
	~TakeGoods(void);
	
	/*����ˢ����Ϣ*/
	void formBornMsg(void);
	
	/*����������Ϣ*/
	void formOutMsg(void);	
	
	/*���id*/
	char* getId(void);
	
	/*��ñ��������ʵ��ָ��*/
	Hero* getHero(char *heroId);
	
	/*���õ�ͼ�Լ��߼�����*/
	void setLogicMap(Map_Inform *_map_now);
	
	/*���õ�ͼ�Լ��߼�����*/
	TakeGoods* copyTakeGoods(Point _pt,bool _isResource = false,bool isUid = false);
	
	/*������������*/
	void setPt(Point _pt);
	
	/*�����������*/
	Point getPt(void);
	
	/*���ժȡ��Ʒid*/
	char* getTakeId(void);
	
	/*����߼�����*/
	Point getLogicPt(void);
	
	void brushMsg(void);
	
	bool getBruOut(void);
	
	/*����ʵ��id*/
	void setInstId(char *_id);
	
	char* getBronMsg(void);
	
	/*ժȡ��Ʒ����*/
	void disperMsg(void);
	
	char* getGoodsId(void);
	
	char* getOutMsg(void);	
	
	/*��ô�����ʽ*/
	bool getTrigFlg(void);
	
	/*��òɼ�����ʱ��*/
	double getTakeTme(void);
	
	/*��ղɼ��˼���*/
	void clearOwner(char *ownerId = NULL);
	
	/*��ղɼ��˼���*/
	void inPutOwner(char *ownerId);
	
	/*��������������߼�����*/
	void setLocation(Point _pt,int flag = 1);
	
	/*�жϴ˲�ժ���Ƿ��λ*/
	bool isRec(void);
	
	/*����Ƿ�ᶯ�ı�־*/
	bool getIsMove(void);
	
	/*Ѱ·׷������*/
	void findAttWay(Point &end);
	
	/*��ͣ�����ʱ��*/
	void stopMoveTimer();
	
	/*��ͣ�ƶ�*/
	void stopMove(void);
	
	/*·��ƽ������*/
	void smoothRoadPt(void);
	
	/*���������ʱ��*/
	void startMoveTimer();
	
	/*��Ѱ·Ѱ�����߼���ת�������ص�*/
	void exchgeWayRod(void);
	
	/*��õ�ͼʵ��ָ��*/
	Map_Inform* getMap(void);
	
	/*����ٶ�*/
	int getSpeed(void);
	
	/*��������ٶ�*/
	int getLastSpeed(void);
	
	/*����ƶ��յ�*/
	void getEndPt(void);
	
	/*��ÿ�ժȡ��Ʒ����*/
	int getTaskStyle(void);
	
	/*��ȡ�ɼ���Ʒ������*/
	int getBrandType(void);
	
	/*����ƿ��*/
	TakeGoods* copyTakeGoods(char *_mapId);
	
	/*�ᶯ�Ŀ�ժȡ��Ļص�����*/
	void calBack(void);
	
	/*������������*/
	void setDIshOwner(char *_ownerId);
	
	/*�����ϯ������ʱ��*/
	int getTolDurTme(void);
	
	/*�����ϯ������ʣ�೤ʱ��*/
	int getLastTme(void);
	
	/*�����ϯ��������*/
	void setDishNewNme(char *nickNme);
	
	/*��ÿ�ժȡ��Ʒ��Ӧ����ʾ��Ϣ*/
	char* getOfferWords(void);
	
	/*�������˶�Ƶ��*/
	void  ctnMoveRate(void);
	
	/*�Ƿ���Զ�*/
	bool isMoveTme(void);
	
	/*�������id*/
	char* getTypeId(void);
	
	/*�����ϯ�Ƿ�ɳ�״ֵ̬*/
	int getDishState(void);
	
	/*������ϯ�Ƿ�ɳ�״ֵ̬*/
	void setDishState(int _newState);
	
	/*���ÿ���ϯ��ͼƬid*/
	void setEmptyPhotoId(char *_emptyPhotoId);
	
	/*������ϯ�Ƿ��ѵ��*/
	void setIsDished(bool _isDished);
	
	/*�����ϯ�Ƿ��ѵ��*/
	bool getIsDished(void);
	
	/*������ϯͼƬid*/
	void setPhotoId(char *_photoId);
	
	/*������ϯ����*/
	void setName(char *_name);
	
	/*�����ϯͼƬid*/
	char* getPhotoId(void);
	
	/*�����ϯ����*/
	char* getName(void);
	
	/*������ϯ������*/
	void initDishNewNme(void);
	
	/*������ϯ����������*/
	void initDishOwner(void);
	
	/*����Ƿ�����Ӫ��Դս�������Դ,��Ϊ��*/
	bool getIsCampSource(void);
	
	/*����Ƿ�����Ӫ��Դս�������Դ,��Ϊ��*/
	void setIsCampSource(bool _isCampSource);
	
	/*������Դ�Ƿ��Ѿ�ˢ���ˣ���Ϊ��*/
	bool getIsUsed(void);
	
	/*������Դ�Ƿ��Ѿ�ˢ���ˣ���Ϊ��*/
	void setIsUsed(bool _isUsed);
	
	/*���ÿ�ժȡ��Ʒ������*/
	void initTakeGoods(void);
	
	/*���ð���ս���������*/
	void initFlagByHero(char *heroId);
	
	/*��ù���ֵ*/
	char* getOwnerValue(void);
	
	/*��ù�������*/
	int getOwnerType(void);	
	
	bool isPicking();
	
	//�Ƿ��ϣ���Ϊ���Դ��
	bool IsInterrupt();
};
#endif
