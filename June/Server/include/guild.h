/****************************************************************
 * Filename: guild.h
 * 
 * Description: ����
 *
 * Original Author : bison, 2012-8-13
 *
 ****************************************************************/

#ifndef _GUILD_H_
#define _GUILD_H_
#include<set>
#include<map>
#include<list>
#include<deque>
#include<vector>
#include<string>
#include<iostream>
#include<string.h>
#include"wholeDefine.h"
#include"map_inform.h"
#include"guild_club.h"
using namespace std;

#ifndef INT_MAX
#define INT_MAX 		2147483647
#endif
#define GLORY_2_CONTB	5				//5����ҫ��ת��һ�㹱�׶�
#define MONEY_2_CONTB	5000			//5000��Ϸ��ת��һ�㹱�׶�
#define EXP_2_CONTB		5				//5���ᾭ���һ�ι��׶�
#define DAY_REWARD_MONEY_BASE	10000	//��������Ǯ��������
#define DAY_REWARD_EXP_BASE		20000	//���������齱������
#define DAY_REWARD_GLORY_BASE	2		//�������ﹱ��������
#define WEEK_REWARD_MONEY_BASE	50000	//��������Ǯ��������
#define WEEK_REWARD_EXP_BASE	100000	//���������齱������
#define WEEK_REWARD_GLORY_BASE	10		//�������ﹱ��������

#define MAX_NOTICES_SIZE		151		//��ṫ������150���ַ�
#define MAX_QY_GROUP_SIZE		25		//qqȺ��yyȺ��С
#define MAX_GUILD_MEMBS			100		//��������Ա��
#define MAX_HISTORY_SIZE		1000	//��ʷ����¼��

#define GUILD_USED_FLAG			0x5555ffff		//ռ�ñ�־
#define GUILD_END_FLAG			0xffffFFFF		//������־
#define GUILD_HISTORY_PRE_PAGE 	9				//������ʷÿҳ��ʾ16��
#define GUILD_NUM_PER_PAGE		13

//stringת�ַ�������
// inline void strcpy(char p[], string src)
// {
	// strncpy(p, src.c_str(), src.size() + 1);
// }

typedef struct GuildSkill_S
{
	char skillId[IDL + 1];
	unsigned skillOrder;
	unsigned openNeedGuildMoney;
	unsigned openNeedGuildGlory;
	unsigned addFactor;
	unsigned upNeedGloryFactor;
	unsigned upNeedMoneyFactor;
	unsigned limit[5];
	unsigned upNeedGlory[21];
	unsigned upNeedMoney[21];
	unsigned addAttr[21];
	unsigned addTotal[21];
} Guild_Skill_T;

extern Guild_Skill_T global_guild_skill[10];

//���ɽ�����
typedef struct GuildReward_S
{
	char id[51];
	int brandType;				//������ʷ��������
	int rewardGuildGlory[5];
	int rewardGuildExp[5];
	// int rewardGuildMoney[5];
	int rewardSelfGlory[5];
	int rewardSelfExp[5];
	int rewardSelfMoney[5];
} GuildReward_T;
extern map<string, GuildReward_T> id_2_guildReward;			//���ɽ���

//�����б���
typedef struct ApplyListItem_S
{
	int flag;					//�����־
	int prev;					//ǰһ���±�
	int next;					//��һ���±�
	char heroId[IDL + 1];		//���ID
	char nickName[IDL + 1];		//����ǳ�
	char party[2];				//�������
	int level;					//��ҵȼ�
	ApplyListItem_S(){};
	bool applyInit(char *_heroId, char *_nickName, char *_party, int _level)
	{
		strcpy(heroId, _heroId);
		strcpy(nickName, _nickName);
		strcpy(party, _party);
		level = _level;
	}
} ApplyListItem_T;

//��־��¼��,�����Ϊ��ܶ࣬�;��������ֶΣ�����flag
typedef struct HistoryItem_S
{
	char linkId[IDL + 1];	//������
	char showName[IDL + 1];	//��ʾ��
	int time;				//�¼�ʱ��
	int mainType;			//������
	int brandType;			//������
	int value1;				//����1
	int value2;				//��ֵ2
	int value3;				//��ֵ3
	int value4;				//��ֵ4
	HistoryItem_S(){};
	void historyInit(int curSecond, int type1, int type2, char *id = NULL, char *name = NULL,
		int val1 = -1, int val2 = -1, int val3 = -1, int val4 = -1)
	{
		time = curSecond;
		mainType = type1;
		brandType = type2;
		if (id == NULL)
		{
			memset(linkId, 0, sizeof(linkId));
		} else
		{
			strcpy(linkId, id);
		}
		if (name == NULL)
		{
			memset(showName, 0, sizeof(showName));
		}
		else {
			strcpy(showName, name);
		}
		value1 = val1;
		value2 = val2;
		value3 = val3;
		value4 = val4;
	}
} HistoryItem_T;

typedef enum {
	FLAG,
	TITLE,
	GLORY,
	TOTALGLORY,
	DONATEMONEY,
	DONATEGLORY,
	DAYCONTB,
	WEEKCONTB,
	TOTALCONTB,
	DAYRANKING,
	WEEKRANKING,
	SKILL
} INFO_TYPE_T;

//���������Ϣ
typedef struct MembInfo_S
{
	int flag;			//�����־
	int title;			//ְλ
	int glory;			//��ǰ��ҫ��
	int totalGlory;		//�ۼ���ҫ��
	int donateMoney;	//���׽�Ǯ
	int donateGlory;	//��������ֵ
	int dayContb;		//�չ���
	int weekContb;		//�ܹ���
	int totalContb;		//�ܹ���
	int dayRanking;		//������
	int weekRanking;	//������
	int skillLevel[10];	//���ɼ���
	int expTail;		//�������������һ�㹱�׵�β��
	int gloryTail;		//��ҫ�ȳ���������һ�㹱�׵�β��
	int moneyTail;		//��Ǯ�����������һ�㹱�׵�β��
	int level;			//��ҵȼ�
	unsigned online;	//����������(0:���ߣ���0:�������ʱ��)
	int needRefreshTask;
	char heroId[IDL + 1];	//��ԱID
	char nickName[IDL + 1];	//�����
	char party[2];		//����
	
	MembInfo_S(){
	};
	void membInfoInit(int _title, int _level, char* _heroId, char* _nickName, char* _party, unsigned _online)
	{
		
		//-1��ʾδ�����ᣬ0Ϊ������1Ϊ��������5Ϊ����
		title = _title;
		// heroId = _heroId;
		// nickName = _nickName;
		// party = _party;
		strcpy(heroId, _heroId);
		strcpy(nickName, _nickName);
		strcpy(party, _party);
		level = _level;
		//����ֵ����ʼΪ0
		dayContb = 0;
		weekContb = 0;
		totalContb = 0;
		
		//���׵Ľ�Ǯ����ҫֵҲΪ0
		donateMoney = 0;
		donateGlory = 0;
		
		//��ҫ��ҲΪ0
		glory = 0;
		totalGlory = 0;
		
		//Сβ�Ӷ���Ϊ0
		expTail = 0;
		gloryTail = 0;
		moneyTail = 0;
		
		//��������������Ϊ0,��������
		dayRanking = 0;
		weekRanking = 0;
		
		for (int i = 0; i < 10; i++)
		{
			//���ܲ���ѧ
			skillLevel[i] = -1;
		}
		
		online = _online;			//��Ϊ����
		
		needRefreshTask = 0;
	}
	
	//�ı���Ұ���ְ��
	void changeTitle(int newTitle)
	{
		title = newTitle;
	}
	
	//˫�������������ӣ���һ���Ҳ���ӣ�����ǩ�����������
	int doubleReward(int incGlory, int incExp)
	{
		glory += incGlory;
		totalGlory += incGlory;
		incGlory += gloryTail;						//�����ϴ�û��һ�㹱�׶ȵĶ�������
		gloryTail = incGlory % GLORY_2_CONTB;		//�����µ�β��
		incExp += expTail;							//�����ϴ�û��һ�㹱�׶ȶ��ྭ��
		expTail = incExp % EXP_2_CONTB;				//�����µľ���β��
		int contb = incGlory / GLORY_2_CONTB + incExp / EXP_2_CONTB;
		dayContb += contb;
		weekContb += contb;
		totalContb += contb;
		
		return contb;
	}
	
	//������ֻ����һ����ӻ���
	void oneReward(int incGlory)
	{
		glory += incGlory;
		totalGlory += incGlory;
	}
	
	//���ף�flagΪ0���װ���Ϸ�ң�flagΪ1���װﹱ,���������Ĺ��׶�
	int donate(int val, int flag)
	{
		int contb = 0;
		if (flag == 0)
		{
			donateMoney += val;
			val += moneyTail;
			moneyTail = val % MONEY_2_CONTB;
			contb = val / MONEY_2_CONTB;
		}
		else if (flag == 1)
		{
			//�������ж��Ƿ񹻿�
			glory -= val;
			donateGlory += val;
			val += gloryTail;
			gloryTail = val % GLORY_2_CONTB;
			contb = val / GLORY_2_CONTB;
		}
		else if (flag == 2)
		{
			//���׾���
			val += expTail;
			expTail = val % EXP_2_CONTB;
			contb = val / EXP_2_CONTB;
		}
		
		dayContb += contb;
		weekContb += contb;
		totalContb += contb;
		
		return contb;
	}
	
	//������Ұﹱ��������
	bool skillUpgrade(int val)
	{
		if (glory < val)
		{
			return false;
		}
		
		glory -= val;
		return true;
	}
	
	//����ջ���
	void dayClr()
	{
		dayContb = 0;
	}
	
	//����ܻ���
	void weekClr()
	{
		dayContb = 0;
		weekContb = 0;
	}
	
} MembInfo_T;


typedef struct GuildInfoData_S
{
	char name[IDL + 1];								//������
	char id[IDL + 1];								//����ID
	char presidName[IDL + 1];						//������
	char presidId[IDL + 1];							//����ID
	char vicePresidName[IDL + 1];					//��������
	char vicePresidId[IDL + 1];						//������ID
	char notices[1024];								//���ɹ���
	char qqGroup[25];								//qqȺ
	char yyGroup[25];								//yyȺ
	char campTitle;									//��Ӫְ��
	int	idNum;										//���ɱ��
	int camp;										//����������Ӫ
	int level;										//���ȼ�
	int expNow;										//��ᾭ��
	int glory;										//��ᷱ�ٶ�
	int money;										//�����ʽ�
	int weekContb;									//����ܹ��׶�
	int totalContb;									//����ܹ��׶�
	int curMembs;									//��ǰ��Ա��
	int limitMembs;									//�����ɳ�Ա��
	int refreshTaskTime;							//ˢ���������
	//int ranking;									//�������
	int rankInAll;									//���������а��ɵ�����
	int rankInCamp;									//��������Ӫ�ڵ�����
	int openSkillFlag[10];							//���ܿ���״̬
	int firstFree_AP;								//��һ�����������б������±�
	int applyHead;									//�����б�ͷ�±�
	int applyTail;									//�����б�β�±�
	ApplyListItem_T applyArr[MAX_GUILD_MEMBS];		//�������ĳ�Ա�б�
	int firstFree_MI;								//��һ�����ó�Ա��Ϣ�б������±�
	MembInfo_T membsInfoArr[MAX_GUILD_MEMBS];		//��Ա��Ϣ����
	int historyStart;								//��һ����ʷ�±�
	int historyEnd;									//���һ����ʷ�±�
	HistoryItem_T historyArr[MAX_HISTORY_SIZE];		//��ʷ����
	
	//���ɻ������ݵĳ�ʼ��
	GuildInfoData_S()
	{
		curMembs = 0;
		expNow = 0;
		glory = 0;
		money = 0;
		weekContb = 0;
		totalContb = 0;
		campTitle = 0;
		initApply();
		initMembsInfo();
		historyStart = GUILD_END_FLAG;
		historyEnd = GUILD_END_FLAG;
		
		for(int i = 0; i < 10; i++)
		{
			openSkillFlag[i] = -1;
		}
		
		refreshTaskTime = 0;
	}
	
	//��ʼ�������б��������
	void initApply()
	{
		firstFree_AP = 0;				//��һ����ʹ�õ������б������±�
		applyHead = GUILD_END_FLAG;		//����ͷָ����±���Ϊ��Ч
		applyTail = GUILD_END_FLAG;		//�����б�β�±�Ҳ��Ϊ��Ч
		
		int i;
		for(i = 0; i < MAX_GUILD_MEMBS - 1; i++)
		{
			applyArr[i].flag = i + 1;
		}
		applyArr[i].flag = GUILD_END_FLAG;
	}
	
	//��ʼ����Ա��Ϣ�б�����
	void initMembsInfo()
	{
		firstFree_MI = 0;				//��һ����ʹ�õĳ�Ա��Ϣ�б������±�
		
		int i;
		for(i = 0; i < MAX_GUILD_MEMBS - 1; i++)
		{
			membsInfoArr[i].flag = i + 1;
		}
		
		membsInfoArr[i].flag = GUILD_END_FLAG;
	}
	
	//����ʱ�ĳ�ʼ��
	void guildInfoDataInit(char* guildId, char* _name, char* heroId, char* nickName, char* party, int heroLevel, int _camp, int _level, int _idNum)
	{
		strcpy(name, _name);
		strcpy(id, guildId);
		strcpy(presidName, nickName);
		strcpy(presidId, heroId);
		memset(vicePresidName, 0, sizeof vicePresidName);
		memset(vicePresidId, 0, sizeof vicePresidId);
		memset(notices, 0, sizeof notices);
		memset(qqGroup, 0, sizeof qqGroup);
		memset(yyGroup, 0, sizeof yyGroup);
		campTitle = 0;
		camp = _camp;
		level = _level;
		idNum = _idNum;
		if (level <= 5)
		{
			// limitMembs = 60;
			limitMembs = 15 + 5 * _level;
		}
		refreshTaskTime = 0;
	}
	
	//����һ�����ɳ�Ա
	int addOneMemb(int _title, int _heroLevel, char* _heroId, char* _nickName, char* _party, unsigned online)
	{
		int temp = firstFree_MI;
		if((temp < 0) || (temp) >= sizeof(membsInfoArr)){
			return GUILD_END_FLAG;
		}
		if (temp == GUILD_END_FLAG){
			//�����˰��ɵ��������
			cout<<"BisonWarn: when you see this, you should expand the size of MAX_GUILD_MEMBS "<<endl;
			return temp;
		}
		else 
		{
			membsInfoArr[temp].membInfoInit(_title, _heroLevel, _heroId, _nickName, _party, online);
			curMembs += 1;
			for (int i = 0; i < 10; i++)
			{
				if (openSkillFlag[i] == 1)
				{
					membsInfoArr[temp].skillLevel[i] = 0;
				}
			}
			firstFree_MI = membsInfoArr[temp].flag;
			membsInfoArr[temp].flag = GUILD_USED_FLAG;
			
			return temp;
		}
	}
	
	//ɾ��һ����Ա���˲���֮ǰҪ�ڳ�Ա���ұ���ɾ����Ӧ��
	void delOneMemb(int index)
	{
		
		if((index < 0) || (index) >= sizeof(membsInfoArr)){
                        return;
                }

		curMembs -= 1;
		membsInfoArr[index].flag = firstFree_MI;
		firstFree_MI = index;	//���������ʹ�ã����ݲ�ɾ������Ϊ����ʱ������
		
		membsInfoArr[index].needRefreshTask = 0;
	}
	
	//����һ�������Ա
	int addOneApply(char* _heroId, char* _nickName, char* _party, int heroLevel)
	{
		int temp = firstFree_AP;
                if((temp < 0) || (temp) >= sizeof(applyArr)){
                        return GUILD_END_FLAG;
                }

		if (temp == GUILD_END_FLAG)
		{
			return temp;
		} else
		{
			if (applyHead == GUILD_END_FLAG)
			{
				//������ǵ�һ��������
				applyArr[temp].prev = applyArr[temp].next = GUILD_END_FLAG;
				applyHead = applyTail = temp;
			} else {
				//���еļ��붼�Ǵ�β������
				applyArr[temp].prev = applyTail;
				applyArr[temp].next = GUILD_END_FLAG;
				applyArr[applyTail].next = temp;
				applyTail = temp;
			}
			applyArr[temp].applyInit(_heroId, _nickName, _party, heroLevel);
			firstFree_AP = applyArr[temp].flag;
			applyArr[temp].flag = GUILD_USED_FLAG;
			return temp;
		}
		
	}
	
	//ɾ��һ�������Ա
	bool delOneApply(int index, char oldHeroId[])
	{
		if((index < 0) || (index) >= sizeof(applyArr)){
                        return false;
                }

		if (applyHead == GUILD_END_FLAG)
		{
			strncpy(oldHeroId, "\0", 2);
			return false;
		}
		applyArr[index].flag = firstFree_AP;
		firstFree_AP = index;
		strncpy(oldHeroId, applyArr[index].heroId, IDL + 1);
		
		int next = applyArr[index].next;
		int prev = applyArr[index].prev;
		if (applyHead == index)
		{
			applyHead = next;
			if (applyHead == GUILD_END_FLAG)
			{
				applyTail = GUILD_END_FLAG;
			} else {
				applyArr[next].prev = GUILD_END_FLAG;
			}
		} else if (applyTail == index) {
			applyTail = prev;
			applyArr[prev].next = GUILD_END_FLAG;
		} else {
			applyArr[next].prev = prev;
			applyArr[prev].next = next;
		}
		return true;
	}
	
	void addOneHistoryItem(int itemTime, int type1, int type2, char* id = NULL, char* name = NULL,
		int val1 = -1, int val2 = -1, int val3 = -1, int val4 = -1)
	{
		if (historyEnd == GUILD_END_FLAG)
		{
			historyStart = 0;
			historyEnd = 0;
		} else {
			historyEnd = (historyEnd + 1) % MAX_HISTORY_SIZE;
			if (historyEnd == historyStart)
			{
				historyStart = (historyStart + 1) % MAX_HISTORY_SIZE;
			}
		}
		historyArr[historyEnd].historyInit(itemTime, type1, type2, id, name, val1, val2, val3, val4);
	}
	
} GuildInfoData_T;

class GuildClub;
class Guild
{
private:

	GuildInfoData_T guildInfoData;
	map<string, int> applyArrFindMap;
	map<string, int> membsInfoArrFindMap;
	map<string,GuildClub*> guildFeastMap;		//����ʢ���
	
	//���ö�Ӧ���ܿ��Լ���
	void setCanOpenSkill();
	bool isInGuildWar;
	char guildWarRoomId[51];
public:
	//��memcache�������ݻ�ԭ����
	Guild(GuildInfoData_T newGuildMemData);
	void memSet(void);
	//��ṹ��
	Guild(char* guildId, char* _name, char* heroId, char* nickName, char* party, int level, int camp, int _level);
	
	//������������
	void cardingGuild();
	//�������
	int applyJoin(char* heroId, char* nickName, char* party, int level);
	//����������ĳһ��
	bool removeOneApply(char* heroId);
	//�������
	void removeAllApply(void);
	//������
	int join(char* heroId, char* nickName, char* party, int level, unsigned online);
	//�뿪���
	void exit(char* heroId);
	
	//���Ӱ���ʽ�.
	void addMoney(int val);
	//���Ӱ�ᾭ��
	bool addExp(int val);
	//���Ӱ�ᷱ�ٶ�
	void addGlory(int val);
	//���Ѱ����ʽ�
	bool useMoney(int val);
	//���Ѱ��ɷ��ٶ�
	bool useGlory(int val);
	//����ֻ������ʱ�ã�����ʱ�򲻻��ã���˲�����ʹ�þ���Ľӿ�
	
	//���İ��֪ͨ
	bool changeNotice();
	
	//ת�ð���
	void setPresident(char* heroId, char* nickName);
	//����������
	bool setVicePresident(char* heroId, char* nickName);
	//�����߲�
	void setManager(char* heroId, char* nickName, int title);
	//�߲�ж��
	bool managerRetired(char* heroId, int title);
	
	//���Ұ���
	char* getPresident();
	//���Ҹ�����
	char* getVicePresident();
	//�����ID
	char* getPresidId();
	//�鸱����ID
	char* getVicePresidId();
	//������Ӫ
	int getCamp();
	
	//���ɵȼ�
	int getLevel();
	int getMoney();
	int getGlory();
	int getExp();
	int getTotalContb();
	int getCurMembs();
	//int getRankNum();
	//��ȡ�����а����е�����
	int getRankInAll();
	//��ȡ����Ӫ�ڵ�����
	int getRankInCamp();
	int getIdNum();
	char* getName();
	char* getId();
	bool getNotices(char *result, int flag = 0);
	//��ð��ɳ�Ա�б�
	set<string> getMembsList();
	//��ȡ�����Ա�б�
	vector<string> getApplyMembsList();
	
	//�ⲿ�������ð�������
	//�����������е�����
	void setRankInAll(int rankNum);
	//���ð�������Ӫ�ڵ�����
	void setRankInCamp(int rankNum);
	//void setRankNum(int rankNum);
	//�޸Ĺ���
	void setNotices(char* newNotices, int flag = 0);
	//����һ����ʷ��¼���ӵ���¼��ͷ��
	void makeHistory(int type1, int type2, char* id = NULL, char* name = NULL, 
		int val1 = -1, int val2 = -1, int val3 = -1, int val4 = -1);
	//��ȡǩ��������mode�����Ƿ�ʹ�õ���
	int getSignInReward(char* heroId, char* nickName, int mode, char *result);
	//��ȡ���ɻ����, index�ǰ��������±�
	int getTaskReward(char* heroId, char* nickName, GuildReward_T* p_guildReward, float rewardTimes, char *result);

	//��Ҿ�����Ϸ��
	int donateMoney(char* heroId, int val);
	//��Ҿ�������
	int donateGlory(char* heroId, int val);
	//���װ��ɾ���
	int donateExp(char* heroId, int val);
	//�չ����������ܹ�������
	void rankInGuild(int mode);	
	//��ȡ���ջ�����������
	int getRankOrder(char* heroId, int mode);
	//��ȡ����������rewardGlory��Ҷ�Ӧ�ﹱ��flag����������������������
	void getRankReward(char* heroId, int rewardGlory, int flag);
	//������Ҹ��˵İ���glory
	int addGloryOfHero(char* heroId, int val);
	//��������
	int upgrade();
	
	//�������ɼ���
	int openSkill(int index);
	//������ҵİ��ɼ���
	int upgradeSkill(char* heroId, int index);
	//��ȡ��ҵİ��ɼ��ܵȼ�
	int getSkillLevel(char* heroId, int index);
	//�鿴��ҵİ��ɼ�����Ϣ������ǰ���������Ҫ���ϼ����Ƿ���Լ���ı�־
	int viewSkillInfo(char* heroId, bool managerFlag, char* result);
	
	void changeMembsInfo(char* heroId, int index, int val);
	
	//�鿴���ɵĻ�����Ϣ
	int viewGuildInfo(char* result, int title);
	//�鿴��ҵĻ�����Ϣ
	int viewHeroInfo(char* heroId, char* result);
	//�鿴������ʷ��ĳҳ��Ϣ
	int viewHistory(int page, char* result);
	//�鿴���ɳ�Ա��Ϣ
	int viewGuildMembsListInfo(char* result);
	//�鿴�����б���Ϣ
	int viewGuildApplyListInfo(char* result);
	//�鿴�������Ƿ��иó�Ա
	bool checkIsInGuild(char* heroId);
	//��ȡһ����Աͷ��
	int getHeroTitle(char* heroId);
	//���İ���������ǳ�
	void changeHeroNickName(char *heroId, char* newNickName);
	//��ȡ����ǳƣ���֤����Ҳ����ߵ�ʱ����ã�Ҳ�ܲ鵽����ǳ�
	char* getHeroNickName(char* heroId);
	//��ȡ�����򸱰������ǳ�
	char* getPresidNickName(int flag);
	//�����������
	void setHeroOnline(char* heroId, bool online);
	
	//��ɢ���
	//bool disband();
	~Guild();
	
	static int count;						//���ɱ��
	static int totalPages[4];				//������ҳ��
	
	//�鿴��������ϸ��Ϣ
	int viewPresidInfo(char *result);
	/*�ж��Ƿ�Ϊ�˰��ɳ�Ա*/
	bool isNumber(const char*herId);
	//��ȡ��ҵİﹱ
	int getHeroGlory(const char* heroId);
	
	int getHeroTotalGlory(const char* heroId);
	//������ҵİﹱ
	bool decHeroGlory(const char* heroId, int val);
	//������ҹ��׶�
	bool addHeroContb(const char* heroId, int val);
	//������Ӫͷ��
	void setCampTitle(char title, int flag = 0);
	//��ȡ��Ӫͷ��
	char getCampTitle();
	//������ҵȼ�
	void setHeroLevel(char *heroId, int newLevel);
	//��ҽ������ʢ���ͼ,����ҷ���,��ͼ��,ʢ�����ϸ��Ϣ
	void send_msg_feast(void);
	//��ҿ�����ʢ��
	void beginGuildFeast(Hero *hero,char* id,char *_identity);	
	//��ҳ԰���ʢ��
	void eatGuildFeast(Hero *hero,char *id);
	//���ɻ���
	long getGuildScore();
	//�ж�����Ƿ���Գ԰���ʢ��
	bool ifHeroCanEatFeast(Hero *hero,char *id);
	//����ʢ��ʵ��id ����ʢ��ʵ��
	GuildClub *getGuildClub(char *guildClubId);
	//����ʢ�����,ɾ���������
	void deleteGuildClub(char *guildClubId);
	//�ж�����Ƿ���Կ�ʢ��
	bool isCanOpenFeast(void);
	//�жϸð����Ƿ������ڰ���ս��
	bool isInGuildWarRoom();
	//���òμ��˰���ս
	void setJoinGuildWar(bool flag, char *roomId = NULL);
	//�������ڵİ�ս����Id
	char *getGuildWarRoomId();
	//ϵͳ��Ͱ���ʢ��
	void systemTreat(Map_Inform *_mapNow,char* _typeId);
	//ˢ�°�������
	void refreshGuildTask();
	int getRefreshGuildTaskTime();
	void resetRefreshGuildTaskTime();
	void clrHeroRefreshTaskNeed(char *heroId);
	bool getHeroRefreshTaskNeed(char *heroId);
	int checkHeroGuildSkill(char *heroId);
	
};

//���ɱȽ�
class CompGuild
{
	public:
	bool operator()(Guild *guild1, Guild *guild2)
	{
		int level1 = guild1->getLevel();
		int level2 = guild2->getLevel();
		if (level1 > level2)
		{
			return true;
		}
		int exp1 = guild1->getExp();
		int exp2 = guild2->getExp();
		if (level1 == level2 && exp1 > exp2)
		{
			return true;
		}
		
		int glory1 = guild1->getGlory();
		int glory2 = guild2->getGlory();
		if (level1 == level2 && exp1 == exp2 && glory1 > glory2)
		{
			return true;
		
		}
		
		int num1 = guild1->getCurMembs();
		int num2 = guild2->getCurMembs();
		if (level1 == level2 && exp1 == exp2 && glory1 == glory2 && num1 > num2)
		{
			return true;
		
		}
				
		//�����أ��жϰ���ʽ�,�ٷֲ���ʤ���Ͳ�����
		int money1 = guild1->getMoney();
		int money2 = guild2->getMoney();
		if (level1 == level2 && exp1 == exp2 && glory1 == glory2 && num1 > num2 && money1 >= money2)
		{
			return true;
		}
		return false;
	}
};

#endif