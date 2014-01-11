/****************************************************************
 * Filename: guild_war_comm.cpp
 * 
 * Description: ��ս����ͨ��
 *
 * Original Author : bison, 2012-9-23
 *
 ****************************************************************/

#include"guild_war_asist.h"

#include "command_return_define_data.h"

#include "user_role_manage_assist.h"

#include "role.h"
#include <arpa/inet.h>
#include"wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;

extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;
extern GuildWarAsist *guildWarManage;			//����ս����


void viewGuildWarRoomInfoComm(char *buffer)
{
	char msg[4000] = {0};
	// string msg_head = "18";					//����ͷ18,0
	// msg = msg + msg_head + intTostring(VIEW_GUILD_WAR_ROOM);
	puts("111111111111111111111111111111111");
	//��fd��heroʵ��
	Hero *hero = pg_hero;
	if (hero->getGuildTitle() != 0)
	{	
		cout<<"BisonTest: viewGuildWarRoomInfo is one permission of guild leader"<<endl;
		return;
	}
	puts("22222222222222222222222222222222222");
	//�鿴����ս����״̬
	sprintf(msg, "18,%d", VIEW_GUILD_WAR_ROOM);
	int ret = guildWarManage->viewRoomState(hero, msg+strlen(msg));
	puts("33333333333333333333333333333333333333");
	// msg += ret;
	send_msg(sock_fd, msg);
}

//��������ս����ͨ��
void createGuildWarRoomComm(char *buffer)
{
	char msg[4000] = {0};
	// string msg_head = "18";					//����ͷ18,1
	// msg = msg + msg_head + intTostring(CREATE_GUILD_WAR_ROOM);
	
	int flag = 0;							//��������ģʽ
	char *password;							//����
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(flag);
	if (flag == 1)
		MSG_CHAR_END(password);
	
	//��fd��heroʵ��
	Hero *hero = pg_hero;
	
	//������ս����
	int ret;
	if (flag == 0)
	{
		ret = guildWarManage->hostHoldGuildWarRoom(hero, flag);
	
	} else if (flag == 1)
	{
		ret = guildWarManage->hostHoldGuildWarRoom(hero, flag, password);
	
	} else {
		return;
	}
	
	if (ret != 0)
	{
		// msg += intTostring(FAILED);
		// msg += intTostring(ret);
		sprintf(msg, "18,1,0,%d", ret);
	} else {
		// msg += intTostring(SUCCESS);
		sprintf(msg, "18,1,1");
	}
	
	send_msg(sock_fd, msg);
}

//��ս��սͨ��
void challengeGuildWarComm(char *buffer)
{
	char msg[64] = {0};
	// string msg_head = "18";					//����ͷ18,2
	// msg = msg + msg_head + intTostring(CHALLENGE_GUILD_WAR);
	
	int flag = 0;							//��ս�ķ����Ƿ�������ı�־
	char *roomId;							//��ս����Id
	char *password;							//����
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(flag);
	MSG_CHAR(roomId);
	if (flag == 1)
	{
		MSG_CHAR_END(password);
	}
	
	//��ս����ս
	int ret = -1;
	if (flag == 0)
	{
		ret = guildWarManage->guestHoldGuildWarRoom(pg_hero, roomId);
	
	} else if (flag == 1)
	{
		ret = guildWarManage->guestHoldGuildWarRoom(pg_hero, roomId, password);
	
	} else {
	
	}
	
	//ʧ����Ϣ�������淢���ɹ���Ϣ�������淢
	if (ret != 0)
	{
		// msg += intTostring(FAILED);
		// msg += intTostring(ret);
		sprintf(msg, "18,2,0,%d", ret);
		send_msg(sock_fd, msg);
	}
	
}

//�ٻ��������ս
void callJoinGuildWarComm(char *buffer)
{
	guildWarManage->callJoinWar(pg_hero);
	
}

//���ڼ������ս
void JoinGuildWarComm(char *buffer)
{
	char *roomId;							//��ս����Id
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(roomId);
	
	int ret = guildWarManage->JoinGuildWar(pg_hero, roomId);
	char msg[64] = {0};
	sprintf(msg, "18,3,0,%d", ret);
}

//����׼������ս
void prepareGuildWarComm(char *buffer)
{
	guildWarManage->managerPrepare(pg_hero);
}

//����ս�˳�
void exitGuildWarComm(char *buffer)
{
	//����ս�˳�
	guildWarManage->exitGuildWar(pg_hero, false);
}

//����ս�и���
void revivalInGuildWar(char *buffer)
{	
	int flag;
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(flag);
	
	cout<<"come from here ???? I don't think so!!!!"<<endl;
	sendRevivalMsg(pg_hero, flag);
}