/****************************************************************
 * Filename: guild_war_asist.h
 * 
 * Description: ��ս���丨����
 *
 * Original Author : bison, 2012-8-28
 *
 ****************************************************************/
#ifndef _GUILD_WAR_ASIST_H_
#define _GUILD_WAR_ASIST_H_

#include"guild_war_room.h"
#include<list>

#define MAX_GUILD_WAR_ROOM_NUM			50				//����ս������

class GuildWarAsist
{
private:
	map<string, GuildWarRoom*>	allGuildWarRooms;
	vector<GuildWarRoom*> idleGuildWarRooms;				//���а���ս����
	bool isInGuildWarTime;									//�Ƿ��ڰ�սʱ��
	
public:
	//��ս����ĳ�ʼ��
	GuildWarAsist();

	//����ռ���ս��������λ��
	int hostHoldGuildWarRoom(Hero *manager, int mode, char* password = NULL);
	//����ռ���ս����Ͱ�λ��
	int guestHoldGuildWarRoom(Hero *manager, char* roomId, char* password = NULL);
	//���ڽ����ս����
	int JoinGuildWar(Hero *hero, char* roomId);
	//����ս�˺�ͳ��
	int hurtCount(Hero *hero, int value);
	//ɱ����ͳ��
	int killCount(Hero *hero);
	//�鿴��ս����״̬
	int viewRoomState(Hero *hero, char* result);
	//�ٻ�����
	void callJoinWar(Hero *hero);
	//����׼��
	int managerPrepare(Hero *hero);
	//����ս�˳�
	void exitGuildWar(Hero *hero, bool offlineFlag);
	//�ͷ�һ��������Դ
	void freeOneRoom(GuildWarRoom *room);
	//�����Ƿ��ڰ�սʱ��
	void setIsInGuildWarTime(bool start);
	//�鿴�Ƿ��ڰ���ս������
	bool getIsInGuildWarTime();
	//�鿴������ڰ���ս�����״̬
	int getOneRoomState(Hero* hero);
	//��ս����
	int guildWarRevival(Hero* hero);
	//�Ƿ���Բɼ�����
	int isHeroPickFlagOk(Hero *hero, int type);
	//ֹͣ����
	int stopPickFlag(Hero *hero, int type);
	//�������
	int finishPickFlag(Hero *hero, int type);
};

#endif