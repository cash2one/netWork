/****************************************************************
 * Filename: rob_flag_war.h
 * 
 * Description: ���ɶ���ս
 *
 * Original Author : bison, 2013-4-12
 *
 ****************************************************************/

#ifndef _ROB_FLAG_WAR_H_
#define _ROB_FLAG_WAR_H_

#include "libev.h"
#include "map_src.h"
#include "my_time.h"


#define ROB_FLAG_WAR_ROOM_IDLE_STATE 			0
#define ROB_FLAG_WAR_ROOM_OCCUPY_STATE			1
#define ROB_FLAG_WAR_ROOM_LOCK_STATE			2
#define ROB_FLAG_WAR_ROOM_PREPARE_STATE			3
#define ROB_FLAG_WAR_ROOM_READY_STATE			4
#define ROB_FLAG_WAR_ROOM_START_STATE			5
#define ROB_FLAG_WAR_ROOM_OVER_STATE			6

#define ROB_FLAG_WAR_FLAG_INVALID_STATE			0
#define ROB_FLAG_WAR_FLAG_IDLE_STATE			1
#define ROB_FLAG_WAR_FLAG_PICKING_STATE			2
#define ROB_FLAG_WAR_FLAG_BRING_STATE			3

// #define ROB_FLAG_WAR_HERO_NO_MOVE_STATE			0
#define ROB_FLAG_WAR_HERO_IDLE_STATE			0
#define ROB_FLAG_WAR_HERO_PICKING_STATE			1
#define ROB_FLAG_WAR_HERO_BRING_STATE			2


typedef struct RobFlagWarReward_S
{
	int money;
	int glory;
	int prestige;
	int reserved;
}RobFlagWarReward_T;

typedef struct RobFlagWarControl_S
{
	int quickStartNeedHeroNum;
	int scoreRadius;
	int lockTime;
	int prepareTime;
	int readyTime;
	int pkTime;
	int rewardTime;
	int flagScore;
	Location_T scorePlace[2];
	RobFlagWarReward_T winGuildReward;
	RobFlagWarReward_T loseGuildReward;
	RobFlagWarReward_T encourageReward;
	
} RobFlagWarControl_T;

extern RobFlagWarControl_T robFlagWarCtl;

//��ս��ÿ����Ա��ͳ����Ϣ  
typedef struct RobFlagWarHeroData_S
{
	int index;			//�������ж�Ӧ���±�
	char heroId[51];
	char nickName[51];
	char party[2];
	int level;
	int heroState;
	
	int nextFreeIndex;
	
	void init()
	{
		memset(heroId, 0, sizeof heroId);
		memset(nickName, 0, sizeof nickName);
		memset(party, 0, sizeof party);
		level = 0;
		heroState = ROB_FLAG_WAR_HERO_IDLE_STATE;
	}
}RobFlagWarHeroData_T;

typedef struct RobFlagWarData_S
{
	char guildName[51];
	int guildRank;					//��������
	char hostId[51];
	int joinNum;
	bool isPrepare;
	unsigned callFreqCtl;			//�ٻ�Ƶ�ʿ���(��¼�ϴ��ٻ�ʱ��)
	int robTimes;					//�������Ĵ���
	int robSuccessTimes;			//�ɹ��������Ĵ���
	int totalScore;					//�ܻ���
	int flagState;					//����״̬		0:��ʼ״̬��1:�ڴ�Ӫ��2:���ڱ����У�3:������
	char flagOwnerId[51];			//��������
	
	
	//��������������ô���ӣ�������Ϊ���Ժ����չ���ǣ�����Ŀǰ�����湷ƨ����û��
	RobFlagWarHeroData_T
		warCount[MAX_GUILD_MEMBS];	//��սͳ����Ϣ
	int firstFreeIndex;				//ͳ����Ϣ����ĵ�һ����ʹ���±�
	map<string, RobFlagWarHeroData_T*>
		heroId_2_countInfo;			//��ɫID��Ӧ��ͳ������
	
	void init()
	{
		memset(guildName, 0, sizeof guildName);
		memset(hostId, 0, sizeof hostId);
		memset(flagOwnerId, 0, sizeof flagOwnerId);
		joinNum = 0;
		guildRank = 0;
		isPrepare = false;
		callFreqCtl = MY_TV_SEC;
		robTimes = 0;
		robSuccessTimes = 0;
		flagState = ROB_FLAG_WAR_FLAG_INVALID_STATE;
		totalScore = 0;
		firstFreeIndex = 0;
		heroId_2_countInfo.clear();
		
		int i = 0;
		for (i; i < MAX_GUILD_MEMBS - 1; i++)
		{
			warCount[i].init();
			
			warCount[i].index = i;
			warCount[i].nextFreeIndex = i + 1;
		}
		warCount[i].nextFreeIndex = GUILD_END_FLAG;
	}
} RobFlagWarData_T;


class RobFlagWar
{
private:
	//data
	char roomId[51];
	Map_Inform *scene;
	int roomState;						//����״̬
	int winIndex;						//��ʤ���±�
	char password[18];					//Ҳ����չ�õ�
	ev_timer timer;						//������ƶ�ʱ��
	RobFlagWarData_T groupData[2];		//��ս˫������
	
	//func
	void initRoomData();
	
public:
	
	//�����ʼ��
	RobFlagWar(int num, Map_Inform *mapRoom);
	void reset();
	
	char* getRoomId();
	Map_Inform* getScene();
	int getRoomState();
	int getWinIndex();
	char *getPassword();
	ev_timer* getTimer();
	
	char *getGuildName(int group);
	char *getHostId(int group);
	int getJoinNum(int group);
	bool getIsPrepare(int group);
	int getCallFreqCtl(int group);
	int getRobTimes(int group);
	int getRobSuccessTimes(int group);
	int getTotalScore(int group);
	int getFlagState(int group);
	char* getFlagOwner(int group);
	void viewOneGroupMsg(int group, char *result);
	
	map<string, RobFlagWarHeroData_T*> *getJoinList(int group);
	
	void setRoomState(int state);
	void setFlagState(int group, int state, char *ownerId = NULL);
	
	void setIsPrepare(int group, bool prepare);
	void setcallFreqCtl(int group);
	void addScore(int group);
	void initOneGroup(int group, int guildRank = 0, char *guildName = NULL, char *hostId = NULL);
	void brushFlag(int group);
	void setWinIndex(int winIndex);
	void setPassword(char *password = NULL);
	void setHostId(int group, char *id);
	
	int groupJudge(char *guildName);
	int heroGroupJudge(char *heroId);
	int judgeWin();
	bool isLock();
	bool pwdCheckOk(char *password);
	
	int addOneMem(int group, char *heroId, char *nickName, char *party, int level);
	int delOneMem(int group, char *heroId);
	
	
};

#endif