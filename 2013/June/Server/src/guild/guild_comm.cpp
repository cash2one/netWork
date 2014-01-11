/****************************************************************
 * Filename: guild_comm.cpp
 * 
 * Description: ����ϵͳ��ͨ��
 *
 * Original Author : bison, 2012-8-15
 *
 ****************************************************************/

#include "command_return_define_data.h"
#include "role.h"
#include "guild_asist.h"
#include <arpa/inet.h>
#include"wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;

extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;

void createGuildComm(char *buffer)
{
	char msg[200] = {0};
	// string msg_head = "12";					//����ͷ12,0
	// msg = msg + msg_head + intTostring(CREATE_GUILD_RETURN);
	
	char *guildName;						//������
	int mode;								//����ģʽ
	int index = 0;								//�������ڱ������±�
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(guildName);
	MSG_INT(mode);
	if (mode == 1)
	{
		MSG_INT(index);
	}
	Hero *hero = pg_hero;
	
	//�������ɷ���
	int ret = createGuild(hero, guildName, mode, index);
	cout<<"Create guild return is "<<ret<<endl;
	if (ret == 0)
	{
		sprintf(msg, "12,0,1");
		// msg = msg + intTostring(SUCCESS);
		send_msg(sock_fd, msg);
	} else {
		// msg = msg + intTostring(FAILED); 
		// msg += intTostring(ret);
		sprintf(msg, "12,0,0,%d", ret);
		send_msg(sock_fd, msg);
	}
}

void viewGuildPageRankComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,1
	// msg = msg + msg_head + intTostring(VIEW_GUILD_RANK_PAGE);
	
	char len_arg;     						//��������
	int count = 6;
	int net;
	int camp = 3;							//��Ӫ
	int page;								//���а�ҳ��
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(camp);
	MSG_INT(page);
	
	//�鿴����ĳҳ���а���Ϣ����
	sprintf(msg, "12,1");
	// sprintf(msg, "12,1");
	int ret = viewGuildRankInfo(page, camp, msg + strlen(msg));
	cout<<"rankInfo is "<<msg<<endl;
	send_msg(sock_fd, msg);
}

//����ĳ������
void searchOneGuildComm(char *buffer)
{
	char msg[20480] = {0};
	char msg1[20480] = {0};
	// string msg_head = "12";					//����ͷ12,2
	// msg = msg + msg_head + intTostring(SEARCH_ONE_GUILD);
	
	char len_arg;     						//��������
	int count = 6;
	int net;
	int camp = 3;							//��Ӫ
	char *guildName;						//������
	
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(camp);
	MSG_CHAR_END(guildName);
	
	cout<<"guildName :"<<guildName<<endl;
	
	//����ĳ������
	// string ret = searchOneGuild(guildName, camp);
	int ret = searchOneGuild(guildName, camp, msg1);
	if (ret != 0)
	{
		sprintf(msg, "12,2,0");
		//msg += intTostring(FAILED);
	} else {
		//msg += intTostring(SUCCESS);
		//msg += ret;
		sprintf(msg, "12,2,1%s", msg1);
	}
	
	send_msg(sock_fd, msg);
}

void applyJoinGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,3
	// msg = msg + msg_head + intTostring(APPLY_JOIN_GUILD);
	
	char *guildName;						//������
	
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(guildName);
	//����������
	int ret = applyJoinGuild(pg_hero, guildName);
	
	if (ret == 0)
	{
		// msg = msg + intTostring(SUCCESS);
		sprintf(msg, "12,3,1");
		send_msg(sock_fd, msg);
	} else {
		sprintf(msg, "12,3,0,%d", ret);
		// msg = msg + intTostring(FAILED); 
		// msg += intTostring(ret);
		send_msg(sock_fd, msg);
	}
}

void viewOneGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,4
	// msg = msg + msg_head + intTostring(VIEW_ONE_GUILD_INFO);
	
	char *guildName;						//������
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(guildName);
	
	//�鿴ĳ��������Ϣ
	sprintf(msg, "12,4");
	int ret = viewOneGuildInfo(guildName, msg + strlen(msg));
	
	// msg += ret;
	send_msg(sock_fd, msg);
}

void viewMyGuildComm(char *buffer)
{
	char msg[4096] = {0};
	memset(msg, 0, sizeof(msg));
	// string msg_head = "12";					//����ͷ12,5
	// msg = msg + msg_head + intTostring(VIEW_MY_GUILD_INFO);

	//�鿴�Լ�������Ϣ
	sprintf(msg, "12,5");
	int ret = viewMyGuildInfo(pg_hero, msg + strlen(msg));
	// msg += ret;
	send_msg(sock_fd, msg);
}

//��������
void upgradeGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,6
	// msg = msg + msg_head + intTostring(GUILD_UPGRADE_RETURN);
	
	//��������
	int ret = upgradeGuild(pg_hero);
	if (ret == 0)
	{
		// msg += intTostring(SUCCESS);
		sprintf(msg, "12,6,1");
	} else {
		sprintf(msg, "12,6,0,%d", ret);
		// msg += intTostring(FAILED);
	}
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
	
}

//��ȡ������������
void getGuildRankRewardComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,7
	// msg = msg + msg_head + intTostring(GET_GUILD_RANK_REWARD);
	
	int index = 0;							//������
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(index);
	
	bool ret = getGuildRankReward(pg_hero, index);
	sprintf(msg, "12,7,%d,%d", ret, index);
	// msg = msg + intTostring(ret);
	send_msg(sock_fd, msg);
}

//�޸Ĺ���
void changeGuildNoticesComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,8
	// msg = msg + msg_head + intTostring(CHANGE_GUILD_NOTICE);
	
	char *notices;							//����
	int flag = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(flag);
	MSG_CHAR(notices);
	
	//���İ��ɹ���
	int ret = changeNotices(pg_hero, notices, flag);
	
	if (ret == 0)
	{
		sprintf(msg, "12,8,1,%d", flag);
		// msg += intTostring(SUCCESS);
	} else {
		sprintf(msg, "12,8,0,%d", ret);
		// msg += intTostring(FAILED);
	}
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
	
}

//�˳�����
void exitGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,9
	// msg = msg + msg_head + intTostring(EXIT_FROM_GUILD);
	
	//�����˳�
	int ret = exitGuild(pg_hero);
	sprintf(msg, "12,9,%d", ret);
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
}

//�鿴���ɳ�Ա��Ϣ
void viewGuildMembsListComm(char *buffer)
{
	char msg[16000] = {0};
	// string msg_head = "12";					//����ͷ12,10
	// msg = msg + msg_head + intTostring(GUILD_MEMBS_LIST);
	
	
	//�鿴���ɳ�Ա��Ϣ
	sprintf(msg, "12,10");
	int ret = viewGuildMembsList(pg_hero, msg + strlen(msg));
	// msg += ret;
	send_msg(sock_fd, msg);
}

//�鿴���������б�
void viewGuildApplyListComm(char *buffer)
{
	char msg[16000] = {0};
	// string msg_head = "12";					//����ͷ12,11
	// msg = msg + msg_head + intTostring(GUILD_APPLY_LIST);
	int flag = 0;							//�������ĸ���巢��������
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(flag);
	
	//�鿴���ɳ�Ա��Ϣ
	sprintf(msg, "12,11,%d", flag);
	int ret = viewGuildApplyList(pg_hero, msg + strlen(msg));
	// msg += intTostring(flag);
	// msg += ret;
	send_msg(sock_fd, msg);
}

//�Ƴ�����
void removeFromGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,12
	// msg = msg + msg_head + intTostring(REMOVE_FROM_GUILD);
	
	char *heroId;							//���Ƴ���Id
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	
	
	//���������
	int ret = driveOutGuild(pg_hero, heroId);
	if (ret == 0)
	{
		sprintf(msg, "12,12,1,%d", ret);
		// msg += intTostring(SUCCESS);
	} else {
		// msg += intTostring(FAILED);
		sprintf(msg, "12,12,0,%d", ret);
	}
	
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
	
}

//ͬ��������
void agreeJoinGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,13
	// msg = msg + msg_head + intTostring(AGREE_JOIN_GUILD);
	char *heroId;							//��ͬ����Id

	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	
	//ͬ��������
	int ret = agreeOneJoinGuild(pg_hero, heroId);
	if (ret == 0)
	{
		sprintf(msg, "12,13,1,%d", ret);
		// msg += intTostring(SUCCESS);
	} else {
		// msg += intTostring(FAILED);
		sprintf(msg, "12,13,0,%d", ret);
	}
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
	
}

//�ܾ��������
void disagreeJoinGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,14
	// msg = msg + msg_head + intTostring(DISAGREE_JOIN_GUILD);
	
	char *heroId;							//���ܾ���Id

	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	
	//�ܾ��������
	int ret = disagreeJoinGuild(pg_hero, 0, heroId);
	sprintf(msg, "12,14,%d", ret);
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
	
}

//��հ��������б�
void clrGuildApplyListComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,15
	// msg = msg + msg_head + intTostring(CLEAR_APPLY_LIST);
	
	//��հ��������б�
	bool ret = disagreeJoinGuild(pg_hero, 1);
	// msg += intTostring(ret);
	sprintf(msg, "12,15,%d", ret);
	send_msg(sock_fd, msg);
}

//ͬ�������������
void agreeGuildAllApplyComm(char *buffer)
{
	char msg[6400] = {0};
	char msg1[6400] = {0};
	// string msg_head = "12";					//����ͷ12,26
	// msg = msg + msg_head + intTostring(AGREE_GUILD_ALL_APPLY);
	char *heroId;							//����ID
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	
	//ͬ�����������߼������
	int ret = agreeAllApply(pg_hero, msg1);
	
	if (ret != 0)
	{
		sprintf(msg, "12,26,0");
		// msg += intTostring(0);
	} else {
		// msg += ret;
		sprintf(msg, "12,26,1%s", msg1);
	}
	
	send_msg(sock_fd, msg);
	
}

//�鿴���ɼ�����Ϣ
void viewGuildSkillInfoComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,16
	// msg = msg + msg_head + intTostring(VIEW_GUILD_SKILL_INFO);
	
	//��հ��������б�
	sprintf(msg, "12,16");
	int ret = viewGuildSkillInfo(pg_hero, msg + strlen(msg));
	send_msg(sock_fd, msg);
}

//������ɼ���
void openGuildSkillComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,17
	// msg = msg + msg_head + intTostring(OPEN_GUILD_SKILL);
	
	int index = 0;							//������
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(index);
	cout<<"open guild skill and index is "<<index<<endl;
	
	int ret = openGuildSkill(pg_hero, index);
	if (ret == 0)
	{
		sprintf(msg, "12,17,1,%d", index);
		// msg += intTostring(SUCCESS);
		// msg += intTostring(index);
	} else {
		// msg += intTostring(FAILED);
		// msg = msg + intTostring(ret);
		sprintf(msg, "12,17,0,%d", ret);
	}
	send_msg(sock_fd, msg);
}

//�������ɼ���
void upgradeGuildSkillComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,18
	// msg = msg + msg_head + intTostring(UPGRADE_GUILD_SKILL);
	
	int index = 0;							//������
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(index);
	
	int ret = upgradeGuildSkill(pg_hero, index);
	if (ret == 0)
	{
		sprintf(msg, "12,18,1");
		// msg += intTostring(SUCCESS);
	} else {
		// msg += intTostring(FAILED);
		// msg = msg + intTostring(ret);
		sprintf(msg, "12,18,0,%d", ret);
	}
	send_msg(sock_fd, msg);
}

//�鿴������ʷ��Ϣ
void viewGuildHistoryInfoComm(char *buffer)
{
	char msg[3096] = {0};
	// string msg_head = "12";					//����ͷ12,19
	// msg = msg + msg_head + intTostring(VIEW_GUILD_HISTORY_INFO);
	
	int page = 1;							//�鿴��ҳ��
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(page);
	
	//��հ��������б�
	cout<<"1219. "<<page<<endl;
	sprintf(msg, "12,19");
	int ret = viewGuildHistory(pg_hero, page, msg+strlen(msg));
	// msg += ret;
	send_msg(sock_fd, msg);
}

/**
 * sendJoinGuildMsg - ��������ɵ���ҷ���ͬ�������ɻ��߱��ܾ�������ɵ���Ϣ
 * @hero: ������ɵ����
 * @guildName:	������
 * @guildLevel: ���ɵȼ�������ʧ�ܷ��صĵȼ�Ϊ0
 * Return: �޷���ֵ
 */
void sendJoinGuildMsg(char* heroId, char* guildName, int guildLevel)
{
	//��ɫid�õ���ɫʵ��
	Hero *hero;
	map<string, Hero*>::iterator it_hero;
	it_hero = heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		return;
	}
	hero = it_hero->second;
	
	char msg[2048] = {0};
	// = "12";
	// msg += intTostring(JOIN_GUILD_RETURN);
	// msg += intTostring(guildLevel);
	// msg += "," + guildName;
	sprintf(msg, "12,20,%d,%s", guildLevel, guildName);
	send_msg(hero->getFd(), msg);
}

void viewGuildActivityComm(char *buffer)
{
	char msg[16000] = {0};
	// string msg_head = "12";					//����ͷ12,21
	// msg = msg + msg_head + intTostring(VIEW_GUILD_ACTIVITY);
	
	// msg += viewGuildActivity(hero);
	sprintf(msg, "12,21");
	int ret = viewGuildActivity(pg_hero, msg + strlen(msg));
	send_msg(sock_fd, msg);
}

//��ȡ����ǩ������
void getGuildSignRewardComm(char *buffer)
{
	char msg[2048] = {0};
	char msg1[200] = {0};
	// string msg_head = "12";					//����ͷ12,22
	// msg = msg + msg_head + intTostring(GET_GUILD_SIGN_REWARD);
	
	int mode = 1;							//ǩ��ģʽ��0:��ͨǩ����1��ʹ�õ���ǩ��
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(mode);
	
	int err;
	//��ȡǩ������
	int ret = getGuildSignReaward(pg_hero, mode, &err, msg1);
	if (err == 0)
	{
		sprintf(msg, "12,22,1%s", msg1);
		// msg += intTostring(SUCCESS);
		// msg += ret;
	} else {
		sprintf(msg, "12,22,0,%d", err);
		// msg += intTostring(FAILED);
		// msg += intTostring(err);
	}
	send_msg(sock_fd, msg);
}

//����ɾ��׵�ͨ��
void guildDonateComm(char *buffer)
{
	char msg[2048] = {0};
	char msg1[64] = {0};
	// string msg_head = "12";					//����ͷ12,23
	// msg = msg + msg_head + intTostring(GUILD_DONATE_RETURN);
	
	int mode = 1;							//���ױ�־��0:���װ��ɣ�1��������Ϸ��
	int val;								//���׵�ֵ
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(mode);
	MSG_INT(val);
	int ret;
	if (mode == 0)
	{
		//���װﹱ
		ret = donateGloryToGuild(pg_hero, val, msg1);
		
	} else if (mode == 1) {
		//�����ʽ�
		ret = donateMoneyToGuild(pg_hero, val, msg1);
	}
	
	if (ret != 0)
	{
		//msg += intTostring(FAILED);
		sprintf(msg, "12,23,0,%d,%d", mode, ret);
	}else {
		// msg += intTostring(SUCCESS);
		// msg += ret;
		sprintf(msg, "12,23,1,%d,%s", mode, msg1);
	}
	send_msg(sock_fd, msg);
}

//����ְ�����
void changeGuildTitleComm(char *buffer)
{
	cout<<"#####################################"<<endl;
	cout<<"buffer is "<<buffer<<endl;
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,24
	// msg = msg + msg_head + intTostring(CHANGE_GUILD_TITLE);
	
	int mode = 3;							//����ѡ��
	char *heroId;							//��ɫ��
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(mode);
	MSG_CHAR_END(heroId);
	
	
	int managerTitle = pg_hero->getGuildTitle();
	cout<<"###############################"<<endl;
	
	cout<<"heroId :"<<heroId<<endl;
	cout<<"mode is "<<mode<<endl;
	cout<<"managerTitle is "<<managerTitle<<endl;
	
	if (managerTitle == 0 && mode == 0)
	{
		//��������
		if (demiseGuildTitle(pg_hero, heroId))
		{
			sprintf(msg, "12,24,1");
			// msg += intTostring(SUCCESS);
		} else {
			// msg += intTostring(FAILED);
			sprintf(msg, "12,24,0");
		}
		
	} else if (managerTitle == 0 && mode == 1)
	{
		//��������������
		if (appointGuildTitle(pg_hero, heroId))
		{
			sprintf(msg, "12,24,1");
			// msg += intTostring(SUCCESS);
		} else {
			// msg += intTostring(FAILED);
			sprintf(msg, "12,24,0");
		}
	} else if (managerTitle == 1 && mode  == 1)
	{
		//������ת��
		if (demiseGuildTitle(pg_hero, heroId))
		{
			// msg += intTostring(SUCCESS);
			sprintf(msg, "12,24,1");
		} else {
			// msg += intTostring(FAILED);
			sprintf(msg, "12,24,0");
		}
	} else {
		// msg += intTostring(FAILED);
		sprintf(msg, "12,24,0");
	}
	
	send_msg(sock_fd, msg);
}

//��ɢ����
void disbandGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//����ͷ12,25
	// msg = msg + msg_head + intTostring(DISBAND_GUILD_RETURN);
	
	//��հ��������б�
	bool ret = disbandGuild(pg_hero);
	sprintf(msg, "12,25,%d",ret);
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
}

void inviteJoinGuildComm(char* buffer)
{
	char msg[2048] = {0};
	char* heroId;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	
	int ret = inviteJoinGuild(pg_hero, heroId);
	
	sprintf(msg, "12,27,%d", ret);
	send_msg(pg_hero->getFd(), msg);
}

void guildGameComm(char* buffer)
{
	char msg[16000] = {0};
	int camp = 0;
	int num = 0;
	int page = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(camp);
	MSG_INT(page);
	MSG_INT(num);
	sprintf(msg, "12,31,%d", page);
	int ret = viewGuildGameInfo(camp, num, page, msg + strlen(msg));
	if (ret != 0)
	{
		sprintf(msg + strlen(msg), ",%d", ret);
	}
	send_msg(pg_hero->getFd(), msg);
}

void refreshGuildTaskComm(char* buffer)
{
	int ret = refreshGuildTaskForAll(pg_hero);
	char msg[2048] = {0};
	if (ret != 0)
	{
		sprintf(msg, "12,35,0,%d", ret);
	} else {
		sprintf(msg, "12,35,1");
	}
	
	send_msg(pg_hero->getFd(), msg);
}

void viewFreshGuildTaskInfoComm(char* buffer)
{
	char msg[2048] = {0};
	sprintf(msg, "12,37");
	viewFreshGuildTaskInfo(pg_hero, msg);
	send_msg(pg_hero->getFd(), msg);
	
}
