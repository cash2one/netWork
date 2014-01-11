#include<iostream>
#include<map>
#include <string.h>
#include"hero.h"
#include "campWarManagement.h"
#include "guild_war_asist.h"
#include "rob_flag_war_logic.h"

extern GuildWarAsist *guildWarManage;			//����ս����
extern map<string,TakeGoods*> takeGoodsMap;
extern campWarManagement campWarController;//��Ӫս����ʵ����
void collect_cb(struct event_base* loop, ev_timer *think, int revents);
void deal_collect_success(Hero* hero, char* collectId);
int deal_collect_fail(Hero* hero, char* collectId, int reason);
//��ʼ�ɼ���ʱ��
int Hero::startCollectTimer(int collectTime, char* collectId)
{
	heroState = 7;
	ext_ev_timer_init(&collectTimer, collect_cb, collectTime, 0, this, collectId);
	ev_timer_start(loops, &collectTimer);
	return 0;
}

bool Hero::isInCollecting()
{
	return ev_timer_is_running(loops, &collectTimer);
}

//reason=1���ƶ���ϣ�reason=2:������ϣ�reason=3:��������ϣ�reason=4:������ϣ�reason=5:��̯���; reason=6:���ߵ��ߴ��; reason=7:������ϣ���Ϊ�вɼ�����������ϣ�
int Hero::stopCollectTimer(int reason)
{
	char msg[64] = {0};
	if (ev_timer_is_running(loops, &collectTimer))
	{	
		int ret = deal_collect_fail(this, collectTimer.targetId, reason);
		if (ret != 0)
		{
			cout<<"Can't stop this kind of collectTimer"<<endl;
			return 1;
		}
		ev_timer_stop(loops, &collectTimer);
		
		sprintf(msg, "28,1,0,%d", reason);
		send_msg(getFd(), msg);
		heroState = 0;
	}
	return 0;
}

void collect_cb(struct event_base* loop, ev_timer *think, int revents)
{
	char msg[64] = {0};
	Hero* hero = (Hero*)think->target;
	char *collectId = think->targetId;
	cout<<"herehereherehere"<<endl;
	hero->setHeroState(0);
	deal_collect_success(hero, collectId);

	sprintf(msg, "28,1,1");
	send_msg(hero->getFd(), msg);
}

void deal_collect_success(Hero* hero, char* collectId)
{
	Map_Inform* heroMap = hero->getMap();
	//ʵ��ID�ҵ�ʵ��ָ��
	TakeGoods *take = heroMap->getTakeObj(collectId);
	if (take == NULL)
	{
		cout<<"BisonWarning: there is no takeGoods!"<<endl;
		return;
	}
	
	take->clearOwner(hero->getIdentity());
	
	int type = take->getTaskStyle();
	int brandType = take->getBrandType();
	//�����ƷID
	char *goodsId = take->getGoodsId();
	//����ɼ�����
	if (type == 1)
	{
		//hero�½ӵ����ռ����ߵ�����
		if (strlen(goodsId) != 16)
		{
			//��ƷID�����������
			return;
		}

		if (brandType == 0)
		{
			//�ɼ���Ʒ���ɼ��ɹ�����Ʒ�ŵ�������
			if (saveGoodsInBag(hero, goodsId, 1))
			{
				heroMap->disperTakeGood(collectId);
				//�����������ݣ�����Ϊ�ɼ�
				hero->updateHeroTaskStatus(PICKUP_TASK_NEED_TYPE, goodsId);
			} else {
				//��Ʒ����������ɹ�
				return;
			}
		} else if (brandType == 1)
		{
			//�ɼ��󲻻�õ���Ʒ���ͣ��������������
			heroMap->disperTakeGood(collectId);
			//�����������ݣ�����Ϊ�ɼ�
			hero->updateHeroTaskStatus(RESCUE_TASK_NEED_TYPE, goodsId);
		} else if (brandType == 2)
		{
			//����ǲر�ͼ���񣬴򿪱���Ҫ���һ����Ʒ����
			if (useRandomGoods(hero, goodsId, -1))
			{
				heroMap->disperTakeGood(collectId);
				//�����������ݣ�����Ϊ�ɼ�
				hero->updateHeroTaskStatus(TREASURE_MAP_TASK_NEED_TYPE, goodsId);
			}
		}
		else if (brandType == 3)
		{
			heroMap->disperTakeGood(collectId);
			//�����������ݣ�����Ϊ�ɼ�
			hero->updateHeroTaskStatus(RESCUE_TASK_NEED_TYPE, goodsId);
			heroMap->brushTaskMon(hero, take->getTypeId(), 4);
		}
		return;
		
	}
	else if (type == 2)
	{
		if (hero->getGuild()!=NULL)
		{
			hero->getGuild()->eatGuildFeast(hero,collectId);
		}
		else 
		{
			msg_error(g_out_buf,102);
			send_msg(hero->getFd(),g_out_buf);
		}
	}
	else if (type == 4)
	{
		if (useBagGoods(hero,"b_cl_132_100",1)==0||useBagGoods(hero,"f_cl_132_100",1)==0)
		{		
			cout<<"useGoods success"<<endl;
			heroMap->disperTakeGood(collectId);
			int spe=take->getBrandType();			//ȡ������
			spe=spe-2;
			cout<<"spe:"<<spe<<endl;
			char petAgg[20]={0};
			int number=random_number(0,9);
			cout<<"random number:"<<number<<endl;
			if (number<2)
			{
				snprintf(petAgg,sizeof(petAgg),"f_dj_106_1%d%d",1,spe);
				cout<<"petAgg:"<<petAgg<<endl;
			}
			else
			{
				snprintf(petAgg,sizeof(petAgg),"f_dj_106_1%d%d",2,spe);
				cout<<"petAgg:"<<petAgg<<endl;
			}
			hero->updateHeroTaskStatus(PICKUP_TASK_NEED_TYPE, "pet");
			saveGoodsInBag(hero,petAgg,1);
			
			cout<<"saveGoodsInBag Finish"<<endl;
		}	
	}
	else if (type == 5)
	{
		campWarController.campResWarCollect(hero);
		heroMap->disperTakeGood(collectId);
	} else if (type == 3)
	{
		// guildWarManage->finishPickFlag(hero, brandType);
		// take->changeName(hero->getNickName(), hero->getGuildName());
		int ret = robFlagWarManage->finishPick(hero, brandType);
		if (ret == 0)
		{
			heroMap->disperTakeGood(collectId);
		}
	}
}

int deal_collect_fail(Hero* hero, char* collectId, int reason)
{
	Map_Inform* heroMap = hero->getMap();
	//ʵ��ID�ҵ�ʵ��ָ��
	TakeGoods *take = heroMap->getTakeObj(collectId);
	if (take == NULL)
	{
		cout<<"BisonWarning: there is no takeGoods!"<<endl;
		return 0;
	}
	
	if (reason == 3 && !take->IsInterrupt())
	{
		return 2;
	}
	
	int type = take->getTaskStyle();
	if (type == 3)
	{
		if (reason == 3)
		{
			return 1;
		}
		
		int brandType = take->getBrandType();
		robFlagWarManage->stopPicking(hero);
	}
	take->clearOwner(hero->getIdentity());
	return 0;
}