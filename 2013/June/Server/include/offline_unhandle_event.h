/****************************************************************
 * Filename: offline_unhandle_event.h
 * 
 * Description: ��������ڼ�δ�����¼�
 *
 * Original Author : bison, 2012-9-25
 *
 ****************************************************************/

#include<string>
#include<string.h>
#include<time.h>
#include<math.h>
#include "mail_systerm_interface.h"
#include "hero.h"
using namespace std;

#define UNHANDLE_HERO_EXP 			1			//δ�������Ҿ���
#define UNHANDLE_BOUND_GAME_MONEY	2			//δ�������Ұ���Ϸ��
#define UNHANDLE_GAME_MONEY			3			//δ����ķǰ���Ϸ��
#define UNHANDLE_BOUND_GOLD			4			//δ����İ�Ԫ��
#define UNHANDLE_GOLD				5			//δ�����Ԫ��
#define UNHANDLE_GUILD_EXP			6			//δ����İ��ɾ���
#define UNHANDLE_HERO_GLORY			7			//δ�������Ұﹱ
#define UNHANDLE_GOODS				8			//δ�������Ʒ
#define UNHANDLE_LONG_MSG			9			//δ�����ϵͳ����Ϣ

#define UNHANDLE_JOIN_GUILD			10			//�Ӱ���δ�����¼�
#define UNHANDLE_EXIT_GUILD			11			//�˳����ɵ�δ�����¼�
#define UNHANDLE_CHANGE_GUILD_TITLE	12			//δ����İ���ְλ����


//��������δ�����¼��ļ�¼
#define UNHANDLE_FUNC(heroId, type, data) \
	MailSystermInterface::create_mail_data(heroId, type, (int)sizeof(data), (char*)&data)

//�������δ�����¼�֮��Ʒ����
typedef struct UnhandleGoods_S {
	int type;				//��Ϣ����
	char id[25];			//��Ʒid
	int num;				//��Ʒ����
	UnhandleGoods_S(int _type, char* _id, int _num)
	{
		type = _type;
		strncpy(id, _id, strlen(_id) + 1);
		num = _num;
	}
}UnhandleGoods_T;

//�������δ�����¼�֮���Լӳ�����
typedef struct UnhandleAttr_S {
	int type;				//��Ϣ����
	int num;				//���Ա仯ֵ
	UnhandleAttr_S(int _type, int _num)
	{
		type = _type;
		num = _num;
	}
}UnhandleAttr_T;

//�������δ�����¼�֮����Ϣ����
typedef struct UnhandleMsg_S {
	int type;				//��Ϣ����
	char msg[256];			//��Ϣ
	UnhandleMsg_S(int _type, char* _msg)
	{
		type = _type;
		strncpy(msg, _msg, strlen(_msg) + 1);
	}
}UnhandleMsg_T;

//�������δ�����¼�֮�����������
typedef struct UnhandleJoinGuild_S {
	int type;				//��Ϣ����
	char guildName[51];			//��Ϣ
	UnhandleJoinGuild_S(int _type, char* name)
	{
		type = _type;
		strncpy(guildName, name, strlen(name) + 1);
	}
}UnhandleJoinGuild_T;


//�������δ�����¼�֮�˳���������
typedef struct UnhandleExitGuild_S {
	int type;				//��Ϣ����
	UnhandleExitGuild_S(int _type)
	{
		type = _type;
	}
}UnhandleExitGuild_T;

//�������δ�����¼�֮����ְ���������
typedef struct UnhandleChangeGuildTitle_S {
	int type;				//��Ϣ����
	int num;				//���Ա仯ֵ
	UnhandleChangeGuildTitle_S(int _type, int _num)
	{
		type = _type;
		num = _num;
	}
}UnhandleChangeGuildTitle_T;

//�������δ�����¼�֮�Ӻ�������
typedef struct UnhandleFriendApply_S {
	char msg[200];			//��Ϣ
	UnhandleFriendApply_S(char* _msg)
	{
		int size = strlen(_msg) + 1;
		if(size >= 200)
			size = 199;
		strncpy(msg, _msg, size);
		msg[size]='\0';
	}
}UnhandleFriendApply_T;

//�������δ�����¼�֮ɾ������
typedef struct UnhandleDelFriend_S {
	char heroId[200];			//��Ϣ	//�������ѵ�ID��
	UnhandleDelFriend_S(char* _msg)
	{
		int size = strlen(_msg) + 1;
		if(size >= 200)
			size = 199;
		strncpy(heroId, _msg, size);
		heroId[size]='\0';
	}
}UnhandleDelFriend_T;

//�������δ�����¼�֮���Ӻ���
typedef struct UnhandleAddFriend_S {
	char heroId[200];				//�������ѵ�ID��
	FriendInfo_T myFriend;			//������Ϣ��
	UnhandleAddFriend_S(char* _msg,FriendInfo_T _myFriend)
	{
		int size = strlen(_msg) + 1;
		if(size >= 200)
			size = 199;
		strncpy(heroId,_msg,size);
		heroId[size]='\0';
		myFriend=_myFriend;
	}
}UnhandleAddFriend_T;

//������Ϊ5ʱ,���������ص�δ�����¼�
void deal_unhandle_attr_event(char* heroId, char* data);

//������Ϊ6ʱ,�����Ʒ������δ�����¼�����
void deal_unhandle_goods_event(char* heroId, char* data);

//������Ϊ7ʱ,���һ������δ�����¼���Ӧ����Ϣ�Ĵ���
void deal_unhandle_msg_event(char* heroId, char* data);

//������Ϊ8ʱ����Ҽ�����ɵ�δ�����¼�����
void deal_unhandle_join_guild_event(char* heroId, char* data);

//������Ϊ9ʱ,���һ������δ�����¼���������
void deal_unhandle_friend_apply_event(string heroId, char* data);

//������Ϊ10ʱ,���һ������δ�����¼�����ɾ��
void deal_unhandle_del_friend_event(string heroId, char* data);

//������Ϊ11ʱ,���һ������δ�����¼��������
void deal_unhandle_add_friend_event(string heroId, char* data);
