/****************************************************************
 * Filename: guild_war_room.h
 * 
 * Description: ��ս������
 *
 * Original Author : bison, 2012-7-23
 *
 ****************************************************************/
#ifndef _GUILD_WAR_ROOM_H_
#define _GUILD_WAR_ROOM_H_
#include"guild.h"
#include"guild_asist.h"
#include "hero.h"
#include "libev.h"
#include"map_src.h"
#include "command_other_function_all_over.h"

#define GWR_IDLE			0			//�������
#define	GWR_ONE				1			//��һ�����ɽ��뷿��
#define GWR_LOCK			2			//���÷�������
#define GWR_TWO				4			//�������ɽ��뷿��
#define GWR_PREPARE			8			//һ��������ͷ����׼����ʼ
#define GWR_READY			16			//����������ͷ������׼����ʼ
#define GWR_START			32			//ս����ʼ
#define GWR_OVER			64			//ս������

#define GWR_KILL_2_SCORE	10			//ɱ����ת��������	

//ͳ����Ϣ

//��ս��ÿ����Ա��ͳ����Ϣ
typedef struct GuildWarCount_S
{
	int index;			//�������ж�Ӧ���±�
	int score;			//����ս����
	int killNum;
	int ranking;
	char heroId[51];
	int nextFreeIndex;	
}GuildWarCount_T;

//����ս��
typedef struct GuildWarFlag_S
{
	int state;					//0:�ɼ�ǰ 1:�ɼ��� 2:�ɼ��� 3:�����ɹ�
	int group;
	char ownerHeroId[51];
	char ownerGuildName[51];
	GuildWarFlag_S()
	{
		state = 0;
		group = -1;
		memset(ownerHeroId, 0, sizeof ownerHeroId);
		memset(ownerGuildName, 0, sizeof ownerGuildName);
	}
	
	void init()
	{
		state = 0;
		group = -1;
		memset(ownerHeroId, 0, sizeof ownerHeroId);
		memset(ownerGuildName, 0, sizeof ownerGuildName);
	}
	
	GuildWarFlag_S(int state, int _group, char* id1, char *id2, char *guildName)
	{
		state = 0;
		group = _group;
		memset(ownerHeroId, 0, sizeof ownerHeroId);
		memset(ownerGuildName, 0, sizeof ownerGuildName);
	}
	
}GuildWarFlag_T;

typedef struct GuildWarReward_S
{
	int money;
	int glory;
	int reserved;
}GuildWarReward_T;

typedef struct GuildWarControl_S
{
	int quickStartNeedHeroNum;
	int lockTime;
	int perpareTime;
	int readyTime;
	int pkTime;
	int rewardTime;
	int protectTime;
	int killScoreOfHero;
	int killScoreOfGuild;
	int flagScoreOfHero[3];
	int flagScoreOfGuild[3];
	GuildWarReward_T joinReward;
	GuildWarReward_T scoreRewardBase;
	GuildWarReward_T winRankReward[4];
	GuildWarReward_T loseRankReward[4];
	
} GuildWarControl_T;

extern GuildWarControl_T guildWarCtl;

class GuildWarRoom
{
private:
	char roomId[IDL + 1];				//�����
	Map_Inform *scene;					//��ս��ͼ
	char host[2][IDL + 1];				//host[0]:������host[1]:����
	// Guild* warGuild[2];				//��ս����
	char sideName[2][IDL + 1];			//sideName[0]:��������sideName[1]:�Ͱ���
	int joinNum[2];						//ÿ��Ĳ�������
	bool guildPrepare[2];				//���ɿ�ʼ׼��
	unsigned callFreqCtl[2];			//�ٻ�Ƶ�ʿ���
	int totalKills[2];					//�ܵ�ɱ����
	int totalScore[2];					//�����ܻ���
	int killLastTime[2];				//ɱ���һ���˵�ʱ��
	int winIndex;						//��ʤ���±�
	// int guildFlag[3];				//������״̬			 
	GuildWarFlag_T guildFlag[3];		//������ս��
	int groupFlagState[2];				//���ɲ�����Щ��
	GuildWarCount_T
		warCount[2][MAX_GUILD_MEMBS];	//��սͳ����Ϣ
	int firstFreeIndex[2];				//ͳ����Ϣ����ĵ�һ����ʹ���±�
	map<string, GuildWarCount_T*>
		heroId_2_countInfo[2];			//��ɫID��Ӧ��ͳ������
	GuildWarCount_T *p_rank[2][MAX_GUILD_MEMBS];		//��ս����		
	map<string, int> heroId_2_score[2];	//�������ɵĻ���ͳ��
	map<int, string> score_2_heroId[2];	//�������ɵİ���������
	int roomState;						//����״̬
	char password[18];					//��������
	ev_timer timer;						//�����ʱ��
	ev_timer flagTimer[3];				//���Ķ�ʱ��				
	void initRoomInfo();				//��ʼ��������
	int addOneGroupMem(int group, char* heroId);		//��սһ������һ����Ա
	int delOneGroupMem(int group, char* heroId);		//ɾ����սһ����һ����Ա
	void newCompMethod();

public:
	//�����ʼ��
	GuildWarRoom(int num, Map_Inform *mapRoom);
	//ռ�췿��
	int holdRoom(Hero *hero);
	//�ٻ�����
	void callJoin(Hero *hero);
	//��ʼս��
	int startWar();
	//������ɳ�Ա
	int remove(char* heroId);
	
	int startDefendFlagTimer(int index);
	
	int stopDefendFlagTimer(int index);
	
	//���ð������
	void lockRoom(char* password);
	//��ȡ����ID
	char* getId();
	//��ȡ��ͼ
	Map_Inform *getScene();
	//���÷���״̬
	void setRoomState(int state);
	//�鿴����״̬
	int getRoomState(void);
	//��������
	void unlockRoom();
	//��������Ƿ���ȷ
	bool isPassOK(char* pass);
	
	//�����������䶨ʱ��
	void startLockTimer();
	//ֹͣ�������䶨ʱ��
	void stopLockTimer();
	//��������׼����ʱ��
	void startPrepareTimer();
	//��ֹ�����׼��״̬
	void stopPrepareTimer();
	//����������ʱ��
	void startReadyTimer();
	//ֹͣ������ʱ��
	void stopReadyTimer();
	//��ս��ʼ��ʱ
	void startStartTimer();
	//��ʼ�������ö�ʱ����ʱ
	void startResetTimer();
	
	//���뷿���ͼ
	void enterMap(Hero *hero, int group);
	//�г������ͼ
	void exitMap(Hero *hero);
	//���뷿��
	int joinRoom(Hero *hero);
	//֪ͨ�������Կ�ʼ
	void informManagerCanStart(Hero* hero);
	
	//�ж��������
	int groupJudge(Hero *hero);
	//��ҵİ���Ѿ�ռ���˸÷���
	bool isInThisRoom(char* heroId, int index);
	
	//���������ʼ��ť
	int prepareGuildWar(Hero *hero);
	//����ս����
	void rankGuildWar();
	
	//����ս���ɱ����ͳ�ƣ�ɱ������ͳ�ƻ���ת��������1:5000
	void guildWarAddOneHeroKillNum(Hero *hero);
	//����ս����˺����ͳ�ƣ��˺�ֵ��ͳ�ƻ���ת���ı�����1:1
	void guildWarAddHurtCount(Hero *hero, int hurt);
	//�ַ���ս����
	void giveReward();
	//��ȡ������ͷ��
	Hero* getHost(int index);
	//��ȡ��ʱ��ʣ��ʱ��
	int getRemainTime();
	//�˳�����ս
	void exit(Hero *hero, bool offlineFlag);
	//��һ�ߵĲ�ս��Ա����Ϣ
	void sendMsgToOneGroup(int group, char* msg, int flag);
	//�鿴һ�����ɷ�����Ϣ
	int viewOneGuildMsg(int group, char* msg);
	//���÷���
	void resetRoom();
	//��ս�и���
	int revival(Hero* hero);
	//����Ƿ���Բɼ�ĳ������
	int isPickFlagOk(Hero* hero, int index);
	//�������
	int finishPickFlag(Hero* hero, int index);
	//ֹͣ����
	int stopPickFlag(int index);
	//ռ������
	void occupyFlag(int index);
};
#endif
