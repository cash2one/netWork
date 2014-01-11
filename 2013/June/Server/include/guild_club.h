#ifndef GUILDCLUB_H
#define GUILDCLUB_H

#include<iostream>
#include"my_timer.h"
#include"guild.h"
#include"guild_club_assist.h"
#include"map_inform.h"
#include"command_other_function_all_over.h"

typedef struct GuildFeastConf_S
{
	char id[IDL + 1];			//��ϯ����ID
	int cost;					//��ϯ����Ԫ����
	int lastTime;				//��ϯ����ʱ��
	int contb;					//�����߶԰��ɹ��׶�
	int hostMoney;				//�����߻�ý�Ǯֵ
	int hostGlory;				//�����߻�ðﹱֵ
	int hostReputation;			//�����߻������ֵ
	int joinMoney;				//�����߻�ý�Ǯֵ
	int joinGlory;				//�����߻�ðﹱֵ
	int joinReputation;			//�����߻������ֵ
	GuildFeastConf_S(char* _id, int cst, int last, int ctb, int hm, int hg, int hr, int jm, int jg, int jr)
	{
		strncpy(id, _id, sizeof(id));
		cost = cst;
		lastTime = last;
		contb = ctb;
		hostMoney = hm;
		hostGlory = hg;
		hostReputation = hr;
		joinMoney = jm;
		joinGlory = jg;
		joinReputation = jr;
	}
}GuildFeastConf_T;
class Map_Inform;
class Guild;
class GuildClub
{
	private:
		char identity[50];
		char invitePerson[IDL + 1];							//������
		set<string> invitedPerson;							//�Ѿ����������б�													
		ev_timer feastTimer;		
		char typeId[IDL + 1];			//��ϯ����ID				
		int beginTime;				//��ʼʱ��
		int totalTime;					//��ʱ��
		Map_Inform *mapNow;
		//��ϯ����
		int joinMoney;				//�����߻�ý�Ǯֵ
		int joinGlory;				//�����߻�ðﹱֵ
		int joinReputation;			//�����߻������ֵ
	public:
		// GuildClub(char* guildId, char* guildName, Map_Src *clubMap);
		GuildClub(void);
		// int enter(Hero *hero);
		// int exit(Hero *hero);
		
		void setIdentity(char *_identity);
		char *getIdentity(void);
		
		Map_Inform *getMap(void);
		void setMap(Map_Inform *_mapNow);
		//���
		void treat(Hero *hero, char* typeId,Guild *guild,char *_identity);
		//����
		void joinDinner(Hero *hero,Guild *guild);
		//ʢ�����
		void end_feast(void);
		//ʢ���Ƿ�ʼ
		bool feastStart(void);
		//����ʣ��ʱ��
		int getRemainTime(void);
		//���ؿ�ʢ������
		char *getInvitePerson(void);
		//�ж��ǲ������ʢ��
		bool isThisDish(char *_identity);
		//�ж��Ƿ��������ʢ��
		bool canEatDish(Hero *hero);
		//ϵͳ���
		void sysTreat(Map_Inform *_mapNow,char* _typeId,Guild *guild);
		
		~GuildClub(void);
};
#endif