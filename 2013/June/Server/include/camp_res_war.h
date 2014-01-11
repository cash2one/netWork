#ifndef _CAMP_RES_WAR_H_
#define _CAMP_RES_WAR_H_

#include"hero.h"
#include"map_src.h"

#define	CAMP_RES_ROOM_MAX_HERO_NUM			3
#define CAMP_RES_ROOM_MAX_CAMP_NUM			1


#define CAMP_RES_WAR_IDLE_STATE				0
#define CAMP_RES_WAR_PREPARE_STATE			1
#define CAMP_RES_WAR_START_STATE			2
#define CAMP_RES_WAR_OVER_STATE				3


typedef struct INT
{
	int a;
	INT (int x)
	{
		a = x;
	}

	bool operator < (const INT &val) const
	{
		return (a >= val.a);
	}
	operator int() const
	{
		return a;
	}

}INT;

typedef struct CampResWarReward_S
{
	char heroId[51];
	int money;
	int prestige;
	char goodsId[51];
	CampResWarReward_S(char *hid, int mny, int ptg, char *gid)
	{
		strncpy(heroId, hid, sizeof heroId);
		money = mny; 
		prestige = ptg;
		if (gid != NULL)
		{
			strncpy(goodsId, gid, sizeof goodsId);
		} else {	
			memset(goodsId, 0, sizeof goodsId);
		}
	}
}CampResWarReward_T;

typedef struct RankReward_S
{
	int minScore;
	int money;
	int prestige;
	char goodsId[51];
} RankReward_T;

//��Ӫ��Դս����
typedef struct CRW_Control_S
{
	int brushNumPerTimes;
	int pickScore;
	int perCampLimitHeros;
	int roomLimitHeros;
	int prepareTime;
	int pkTime;
	int brushTime;
	int rewardTime;
	Location_T from;
	int winCampRewardMinScore;
	int winCampRewardMoney;
	int winCampRewardPtg;
	int joinRewardMoney;
	int joinRewardPtg;
	int resNumRewardMoneyBase;
	int resNumRewardPtgBases;
	RankReward_T rankReward[3];
}CRW_Control_T;

extern CRW_Control_T campResWarCtl;

class CampResWar
{
private:
	map<string, int> heroId_2_resNum[3];
	map<INT, string> rankAll;
	int totalJoinNum;
	int remainResCnt;
	int perCampJoinNum[3];
	int perCampResCnt[3];
	int isWinnerCamp[3];
	
	ev_timer roomCtlTimer;
	ev_timer brushResTimer;
	int index;
	int times;							//��Դˢ�´���
	int roomState;
	int timeState;
	char mapId[51];
	Map_Src* scene;
public:
	CampResWar();
	~CampResWar();
	
	void create(int index, Map_Src* mapPtr);
	void reset();
	//���俪��
	void open();
	//�жϷ����Ƿ���
	bool isOpen();
	//��ȡ�����
	int getRoomIndex();
	//��ȡ����״̬
	int getRoomState();
	//��ȡ����ʱ��״̬
	int getTimeState();
	//��ȡ��������(0 ~ 2:��ȡÿ����Ӫ����������3:��ȡ������)
	int getJoinNum(int index);
	bool canHeroJoin();
	int join(Hero *hero, int &openNext);
	int exit(Hero* hero);
	//���·�����Ϣ
	void update_room_infor();
	//�����ڷ�����Ϣ
	void send_room_msg(char *msg, int flag = 3, int tag = 0);
	//��ʱ��ʣ��ʱ��
	int getCtlTimerRemain();
	//ˢ��ʱ��ʣ��
	int getBrushTimerRemain();
	//����׼����ʱ
	void startPrepareTimer();
	//����ս����ʱ
	void startPkTimer();
	//����ˢ��Դ��ʱ
	void startBrushTimer();
	//�����������ü�ʱ
	void startResetTimer();
	//ֹͣˢ��Դ��ʱ��
	void stopBrushTimer();

	
	//��Դս��ʼ
	void start();
	//ˢ����Դ
	int brush();
	//��Դս����
	void over();
	//����
	void award();
	//�����峡
	void clear();
	//��Դ�ɼ�
	int collect(Hero* hero);
	//ɱ������
	int kill(Hero* atker, Hero* atked);
	//����
	int revival(Hero* hero);
	
	int viewResNum(Hero* hero, char* heroId);
	
};

#endif