/****************************************************************
 * Filename: deal_offline_unhandle_event.cpp
 * 
 * Description: ������������ڼ�δ�����¼�
 *
 * Original Author : bison, 2012-9-25
 *
 ****************************************************************/
 
#include "offline_unhandle_event.h"
#include"command_other_function_all_over.h"
#include "guild_asist.h"
#include "money_operator.h"
#include "systemMessage.h"

extern map<string, Hero*> heroId_to_pHero;

//������Ϊ5ʱ,���������ص�δ�����¼�
void deal_unhandle_attr_event(char* heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"BisonShow mail give a null message to UNHANDLE to deal!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//ǿת�ɿɴ���ṹ��
	UnhandleAttr_T *event = (UnhandleAttr_T*)data;
	cout<<"BisonShow you can see is event val OK: type is "<<event->type<<" num is "<<event->num<<endl;
	Guild *guild = hero->getGuild();
	switch(event->type)
	{
		case UNHANDLE_HERO_EXP:						//δ�����Ӣ�۾���
			hero->setExpNow(event->num);
			break;
			
		case UNHANDLE_BOUND_GAME_MONEY:				//δ����İ���Ϸ��
			increaseBoundGameMoney(hero,event->num);
			break;
			
		case UNHANDLE_GAME_MONEY:					//δ����ķǰ���Ϸ��
			increaseGameMoney(hero,event->num);
			break;
			
		case UNHANDLE_BOUND_GOLD:					//δ����İ�Ԫ��
			increaseBoundGold(hero,event->num);
			break;
			
		case UNHANDLE_GOLD:							//δ�����Ԫ��
			increaseGold(hero,event->num);
			break;
		
		case UNHANDLE_GUILD_EXP:					//δ�������Ҹ����ɼӵİﹱ
			if (guild != NULL)
			{
				char* guildName = hero->getGuildName();
				addGuildExp(guildName, heroId, event->num);
			}
			break;
			
		case UNHANDLE_HERO_GLORY:					//δ�������Ұﹱ
			if(guild != NULL)
			{
				char* guildName = hero->getGuildName();
				addMyGuildGlory(guildName, heroId, event->num);
			}
			break;
		
		default:
			cout<<"BisonWarning: unhandle event type is error"<<endl;
			break;
	}
}


//������Ϊ6ʱ,�����Ʒ������δ�����¼�
void deal_unhandle_goods_event(char* heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"BisonShow mail give a null message to UNHANDLE to deal!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//ǿת�ɿɴ���ṹ��
	UnhandleGoods_T *event = (UnhandleGoods_T*)data;
	cout<<"BisonShow you can see is event val OK: type is "<<event->type<<" num is "<<event->num<<endl;
	cout<<"And the event goods id is "<<event->id<<endl;
	Bag *bag = hero->getBag();
	
	if(event->type != UNHANDLE_GOODS)
	{
		cout<<"BisonWarning: get unhandle event from mail doesn't match the unhandle goods event!"<<endl;
		return;
	}
	//�����ɹ����ɹ���ֻ����һ�Σ���Ұ������Ļ�������ù
	saveGoodsInBag(hero,event->id, event->num);
}


//������Ϊ7ʱ,���һ������δ�����¼���Ӧ����Ϣ
void deal_unhandle_msg_event(char* heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"BisonShow mail give a null message to UNHANDLE to deal!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//ǿת�ɿɴ���ṹ��
	UnhandleMsg_T *event = (UnhandleMsg_T*)data;
	cout<<"BisonShow you can see is event val OK: type is "<<event->msg<<endl;
	
	//���Ƿ���Ϣ������
	if(event->type != UNHANDLE_LONG_MSG)
	{
		cout<<"BisonWarning: get unhandle event from mail doesn't match the unhandle msg event!"<<endl;
		return;
	}
	//�������ʱ������ĳ��������ص��¼�������ҷ�����¼��Ľ��
	systemSendMssage(hero, event->msg, 0);
}

//������Ϊ8ʱ����Ҽ�����ɵ�δ�����¼�����
void deal_unhandle_join_guild_event(char* heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"BisonShow mail give a null message to UNHANDLE to deal!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//ǿת�ɿɴ���ṹ
	UnhandleJoinGuild_T *event = (UnhandleJoinGuild_T*)data;
	cout<<"BisonShow you can see is event val OK: type is "<<event->type<< " "<<event->guildName<<endl;
	
	//���Ƿ���Ϣ������
	if(event->type != UNHANDLE_JOIN_GUILD)
	{
		cout<<"BisonWarning: get unhandle event from mail doesn't match the unhandle msg event!"<<endl;
		return;
	}
	
	Guild *guild = getGuildWithName(event->guildName);
	if (guild == NULL)
	{
		return;
	}
	
	int guildTitle = guild->getHeroTitle(heroId);
	if (guildTitle == -1)
	{
		//���ɲ��޴���
		return;
	}
	//ok,���´󼪣�������ҵİ�����Ϣ
	hero->setGuildInfo(guild, guildTitle);
	
}

//������Ϊ9ʱ,���һ������δ�����¼���������
void deal_unhandle_friend_apply_event(string heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"BisonShow mail give a null message to UNHANDLE to deal!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"in the deal_offerline_unhandle_event.cpp--> the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//ǿת�ɿɴ���ṹ��
	UnhandleFriendApply_T* event = (UnhandleFriendApply_T*)data;
	// cout<<"BisonShow you can see is event val OK: type is "<<event->msg<<endl;
	string msg = event->msg;
	send_msg(hero->getFd(), msg);
}

//������Ϊ10ʱ,���һ������δ�����¼�����ɾ��
void deal_unhandle_del_friend_event(string heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"in the deal_offerline_unhandle_event.cpp-->BisonShow mail give a null message to UNHANDLE to deal friend_apply!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"in the deal_offerline_unhandle_event.cpp--> the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//ǿת�ɿɴ���ṹ��
	UnhandleDelFriend_T* event = (UnhandleDelFriend_T*)data;
	// cout<<"BisonShow you can see is event val OK: type is "<<event->heroId<<endl;
	hero->getFriendInfo()->delFromFriendlist(event->heroId);
}

//������Ϊ11ʱ,���һ������δ�����¼��������
void deal_unhandle_add_friend_event(string heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"in the deal_offerline_unhandle_event.cpp-->BisonShow mail give a null message to UNHANDLE to deal friend_apply!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"in the deal_offerline_unhandle_event.cpp--> the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//ǿת�ɿɴ���ṹ��
	UnhandleAddFriend_T* event = (UnhandleAddFriend_T*)data;
	if(hero->getFriendInfo() == NULL)
		return;
		
	hero->getFriendInfo()->add2Friendlist2(event->heroId,event->myFriend);
}

