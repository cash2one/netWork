/****************************************************************
 * Filename: guild_asist.h
 * 
 * Description: ���ɹ��ܲ���
 *
 * Original Author : bison, 2012-8-13
 *
 ****************************************************************/
#ifndef _GUILD_ASIST_H_
#define _GUILD_ASIST_H_

#include"guild.h"
#include"hero.h"
#include "guild_club.h"	


//������
typedef pair<string, Guild*> GuildSortItem;

//�õ�������ID
char* getGuildVicePresidId(char* guildName);

//�õ�����ID
char* getGuildPresidId(char* guildName);

//�������ֵõ�������
int getGuildRankInCamp(char* guildId, int camp = 3);

//������� 
int createGuild(Hero *hero, char* name, int mode, int index = 0);

//���������
int applyJoinGuild(Hero *hero, char* guildName);

//ͬ�ⵥ�˼�����
int agreeOneJoinGuild(Hero *manager, char* heroId);
//ͬ�����������߼�����
int agreeAllApply(Hero *manager, char* result);
//��ͬ�������
bool disagreeJoinGuild(Hero *manager, int mode, char* heroId = NULL);

//����˳����
bool exitGuild(Hero *hero);
//��������
int driveOutGuild(Hero *manager, char* heroId);

//����
bool appointGuildTitle(Hero *manager, char* heroId);
//��ְ
bool deposeGuildTitle(Hero *manager, char* heroId);
//��ְ
bool resignGuildTitle(Hero *manager);
//����
bool demiseGuildTitle(Hero *manager, char* heroId);

//���׶�����
void guildRank(int mode);
//�鿴������ɵĸ���
int viewRankGuildRewardInfo(Hero *hero, int mode, char *result);
//��ȡ���ɸ�����mode=0:��ȡ��������������mode = 1:��ȡ������������
bool getGuildRankReward(Hero *hero, int mode);
//��ȡ������������index�����������±�
int getGuildTaskReward(Hero *hero, char* taskId, char *result, float rewardTimes);
//��ȡǩ������,mode����ǩ��ʱ�Ƿ�ʹ�õ���
int getGuildSignReaward(Hero *hero, int mode, int *err, char *result);
//����Ϸ��
int donateMoneyToGuild(Hero *hero, int val, char *result);
//��ﹱ
int donateGloryToGuild(Hero *hero, int val, char *result);

//�������
int upgradeGuild(Hero *manager);

//������index + 1�����ɼ���
int openGuildSkill(Hero *manager, int index);
//������index+1�����ɼ���
int upgradeGuildSkill(Hero *hero, int index);
//�鿴��Ҷ�Ӧ�İ��ɼ�����Ϣ
int viewGuildSkillInfo(Hero *hero, char *result);

//����������
void allGuildRank();
#if 0			//�߻�˵���������Ȳ�Ҫ
//�����ɵȼ�����
void guildRankByLevel();
//�����ɵ�ǰ�����������������û����ã����Ǿ��鲻��
void guildRankByExp();
//�����ɰﹱ����
void guildRankByGlory();
//�������ʽ�����
void guildRankByMoney();
//��������������
void guildRankByMembsNum();
#endif

//�鿴��pageҳ��������Ϣ
int viewGuildRankInfo(int page, int camp, char *result);
//����ĳ������
int searchOneGuild(char* guildName, int camp, char *result);
//�鿴�Լ�������Ϣ
int viewMyGuildInfo(Hero *hero, char *result);
//�鿴ĳ��������Ϣ
int viewOneGuildInfo(char* guildName, char *result);

//���İ�ṫ��
int changeNotices(Hero *manager, char* newNotices, int flag = 0);
//�鿴������ʷ��¼
int viewGuildHistory(Hero *hero, int page, char *result);
//�鿴���ɳ�Ա��Ϣ
int viewGuildMembsList(Hero *hero, char *result);
//�鿴�����Ա�б�
int viewGuildApplyList(Hero *hero, char *result);

//���Ӱ��ɾ���
int addGuildExp(char* guildName, char* heroId, int expVal);
//���Ӹ��˰ﹱ
int addMyGuildGlory(char* guildName, char* heroId, int glory);

//�鿴���ɻ��Ϣ
int viewGuildActivity(Hero *hero, char *result);

//��������ɵ���ҷ���ͬ�������ɻ��߱��ܾ�������ɵ���Ϣ
void sendJoinGuildMsg(char* heroId, char* guildName, int guildLevel);
//��ɢ����
bool disbandGuild(Hero *manager);

//�ɰ������õ�����ʵ��
Guild *getGuildWithName(char* guildName);

//����Id���Ұ���ʵ��
Guild *getGuildWithId(char* guildId);

//��һ������ID�浽memcached�е����еİ������б�
void saveOneGuildIdToMemc(char* guildId);
//��ʼ�����д��ڵİ���
void initAllExistGuild();

//�鿴һ����Ӫ�еİ����б�
int viewAllPresidInCamp(int camp, char *result);

//�鿴�����򸱰����ǳ�
char* viewGuildPresidNick(int flag, char* guildName);

//���а������Ĵ洢
void saveAllGuildIdToMemc();

//�Ѱ���ϵͳ��Ϣ���浽memcached
void saveGuildSystemToMemc();

void sendGuildMsg(char* guildName, char* msg);

//����������
int inviteJoinGuild(Hero* manager, char *heroId);

bool GM_disbandGuildByName(char* guildName);

bool GM_disbandGuildByRank(int camp, int rank);

int viewGuildGameInfo(int camp, int num, int page, char *result);

//ϵͳ��� �Է�
void systemTreatGuild(Map_Inform *mapNow,char *typeId,char *guildId);

//�ж�guildName�Ƿ����ϵİ��������ڲ�ֻ���Ƿ��жϣ�guildName�Ϸ����ж����ڵ���֮ǰ����
bool isOldGuildName(char* guildName);

int refreshGuildTaskForAll(Hero* hero);

void viewFreshGuildTaskInfo(Hero* hero, char* result);

bool GM_setGuildPresid(char* heroId);
#endif
