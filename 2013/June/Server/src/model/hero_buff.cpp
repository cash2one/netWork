#include<iostream>
#include<map>
#include <string.h>
#include"hero.h"
#include "hero_fight.h"
#include"move_asist.h"

extern map<string, HeroSkill*> skillId_2_heroSkill;		//��ɫ����

void buff_debuff_cb(struct event_base* loop, ev_timer *think, int index);
//buffЧ����ʼ���߽���
int Hero::startBufOrDebuffTimer(char *heroId, char *skillId, int skillLevel)
{
	cout<<"[BisonShow] start buf or debuf timer skillId is "<<skillId<<endl;
	cout<<"skillLevel is "<<skillLevel<<endl;
	map<string, Buff_debuff_conf_T*>::iterator it;
	it = buf_debuf_conf.find(skillId);
	if (it == buf_debuf_conf.end())
	{
		return -1;
	}
	Buff_debuff_conf_T *conf = it->second;
	int effect = conf->effect;
	int index = 0;
	while (!(effect & 0x1))
	{
		effect >>= 1;
		index++;
	}
	//�Ѿ��й����debuff״̬���µĸ��Ǿɵġ�������������
	if (skillBuffState & conf->effect)
	{
		ev_timer_stop(loops, skillBuff[index].timer);
	}
	
	skillBuffState |= conf->effect;
	
	strncpy(skillBuff[index].skillId, skillId, sizeof(skillBuff[index].skillId));
	strncpy(skillBuff[index].atkerId, heroId, sizeof(skillBuff[index].atkerId));
	skillBuff[index].skillLevel = skillLevel;
	skillBuff[index].lastTime = conf->lastTimeFactor * skillLevel + conf->lastTimeBase;	//����ʱ��
	skillBuff[index].leftTime = skillBuff[index].lastTime;								//ʣ��ʱ��
	//һ�㼼��Ч��������һ��ʼʱֻ����һ��
	skillBuff[index].totalVal = conf->effectIncFactor * skillLevel + conf->effectBase;	//Ч��ֵ
	cout<<"totalval is "<<skillBuff[index].totalVal<<"factor is "<<conf->effectIncFactor<<" "<<conf->effectBase<<endl;
	
	skillBuff[index].perVal = skillBuff[index].totalVal;
	
	//�ж���һ�β���Ѫ���������Ѫ�������С��0����Ϊ1
	if (index == 9)
	{
		if  (memHero->basicHeroData.lifeVal <= skillBuff[index].perVal)
		{
			memHero->basicHeroData.lifeVal = 1;
		}
		else {
			setLifeVal(memHero->basicHeroData.lifeVal - skillBuff[index].perVal);
		}
		
	} else if (index == 12) {	
		//���з籩
		cout<<"Happpy happy haopppjd sdfa come jufengpo!!!!!!!!"<<endl;
		cout<<"Happpy happy haopppjd sdfa come jufengpo!!!!!!!!"<<endl;
		cout<<"Happpy happy haopppjd sdfa come jufengpo!!!!!!!!"<<endl;
		HeroSkill *p_skill = NULL;
		map<string, HeroSkill*>::iterator it_skill;
		it_skill = skillId_2_heroSkill.find(skillId);
		if (it_skill == skillId_2_heroSkill.end())
		{
			//�޴˼���
			cout<<"There is no this skill:"<<skillId<<" when hero use storm buff"<<endl;
			return -2;
		}
		p_skill = it_skill->second;
		//��ָ����Ⱥ������
		many_hurt_skill_deal(this, p_skill,  skillLevel, 0, NULL, false, skillBuff[index].leftTime);
	} else if (index == 0 || index == 1) {
		//��ѣ�λ��߶����ܣ�������ƶ��У���ֹ��Ⱥ��ͣ����Ϣ
		stopMove();
	} else if (index == 13) {
		hero_move_cb(loops, &moveTimer, 2);
		//�����ٶȸ���lastSpeed
		setLastSpeed(getSpeed());
	}
	
	//����indexֻ������cb��
	ev_timer_stop(loops, skillBuff[index].timer);
	ext_ev_timer_init(skillBuff[index].timer, buff_debuff_cb, 1, index, this);
	ev_timer_start(loops, skillBuff[index].timer);
	char msg[400] = {0};
	sprintf(msg, "26,3,0,%s,%s,%d,%d,%d", skillId, memHero->identity,
		index, skillBuff[index].totalVal, skillBuff[index].leftTime);
	Nbox *box = map_now->getBox();
	if (box != NULL)
	{
		box->sendMsgPiexPt(memHero->basicHeroData.pt, msg);
	} else {	
		send_msg(_fd, msg);
	}
	send_msg_att();
	return index;
}

void buff_debuff_cb(struct event_base* loop, ev_timer *think, int index)
{
	Hero *hero = (Hero*) think->target;
	if (hero == NULL)
	{
		return;
	}
	
	if (index == 3)
	{
		send_msg(hero->getFd(), (char*)"41,1,lulaulaluldl");
		hero->skillBuff[index].totalVal += hero->skillBuff[index].perVal;
		Hero *atker = heroid_to_hero(hero->skillBuff[index].atkerId);
		proc_hero_lose_life(atker, hero, hero->skillBuff[index].perVal);
		if (hero->getLifeVal() <= 0)
		{
			hero->send_msg_att();
		}
		
	}
	
	hero->skillBuff[index].leftTime -= 1;
	if (hero->skillBuff[index].leftTime <= 0)
	{
		char msg[400] = {0};
		sprintf(msg, "26,3,1,%s,%s,%d,%d,%d", hero->skillBuff[index].skillId, hero->memHero->identity,
			index, hero->skillBuff[index].totalVal, hero->skillBuff[index].leftTime);
		
		//�����buff
		hero->skillBuffState &= ~(1 << index);
		hero->skillBuff[index].lastTime = 0;
		hero->skillBuff[index].leftTime = 0;
		hero->skillBuff[index].totalVal = 0;
		hero->skillBuff[index].perVal = 0;
		
		//���ټ���
		if (index == 13) {
			hero_move_cb(loops, &hero->moveTimer, 2);
			//�����ٶȸ���lastSpeed
			hero->setLastSpeed(hero->getSpeed());
		}
			
		Map_Inform *mapNow = hero->getMap();
		if (mapNow == NULL)
		{
			hero->skillBuffState &= ~(1 << index);
			return;
		}
		Nbox *box = mapNow->getBox();
		if (box != NULL)
		{
			Point heroPt = hero->getLocation();
			box->sendMsgPiexPt(heroPt, msg);
		} else {	
			send_msg(hero->getFd(), msg);
		}
		hero->send_msg_att();
		return;
	} else {
		
		//���з籩
		if (index == 12)
		{
			HeroSkill *p_skill = NULL;
			map<string, HeroSkill*>::iterator it_skill;
			it_skill = skillId_2_heroSkill.find(hero->skillBuff[index].skillId);
			if (it_skill == skillId_2_heroSkill.end())
			{
				//�޴˼���
				cout<<"There is no this skill:"<<hero->skillBuff[index].skillId<<" when hero use storm buff"<<endl;
				return;
			}
			p_skill = it_skill->second;
			//��ָ����Ⱥ������
			many_hurt_skill_deal(hero, p_skill, hero->skillBuff[index].skillLevel, 0, NULL,
				false, hero->skillBuff[index].leftTime);
		}
	
	}
	ev_timer_start(loops, hero->skillBuff[index].timer);
}

void Hero::stop_buff_debuff_timer(int flag)
{
	skillBuffState = 0;
	for (int i = 0; i < 15; i++)
	{
		skillBuff[i].lastTime = 0;
		skillBuff[i].leftTime = 0;
		skillBuff[i].totalVal = 0;
		skillBuff[i].perVal = 0;
		ev_timer_stop(loops, skillBuff[i].timer);
		if (flag != 0)
		{
			// delete skillBuff[i];
		}
		// cout<<"have come to i: "<<i<<endl;
	}
	//ǰ�ٶȻ���
	setLastSpeed(getSpeed());
}

void Hero::stop_buff_debuff_by_index(int index)
{
	//�����buff
	skillBuffState &= ~(1 << index);
	skillBuff[index].lastTime = 0;
	skillBuff[index].leftTime = 0;
	skillBuff[index].totalVal = 0;
	skillBuff[index].perVal = 0;
	
	char msg[400] = {0};
	sprintf(msg, "26,3,1,%s,%s,%d,%d,%d", skillBuff[index].skillId, memHero->identity,
		index, skillBuff[index].totalVal, skillBuff[index].leftTime);
	//���ټ���
	if (index == 13) {
		hero_move_cb(loops, &moveTimer, 2);
		//�����ٶȸ���lastSpeed
		setLastSpeed(getSpeed());
	}
	
	Map_Inform *mapNow = getMap();
	if (mapNow == NULL)
	{
		return;
	}
	Nbox *box = mapNow->getBox();
	if (box != NULL)
	{
		Point heroPt = getLocation();
		box->sendMsgPiexPt(heroPt, msg);
	} else {	
		send_msg(getFd(), msg);
	}
	send_msg_att();
	return;
}

int Hero::getIndexByState(int state)
{
	int index = 0;
	while (!(state & 0x1))
	{
		state >>= 1;
		index++;
	}
	return index;
}

void anm_timer_cb(struct event_base* loop, ev_timer *think, int index)
{
	Hero *hero = (Hero*)think->target;
	hero->skillBuffState &= ~PLAY_ANIMATION_STATE;
}

int Hero::startHeroSkillAnimationTimer(float time)
{
	if (skillBuffState & PLAY_ANIMATION_STATE)
	{
		return 1;
	}
	skillBuffState |= PLAY_ANIMATION_STATE;
	ev_timer_stop(loops, &skillAnimationTimer);
	double realTime = time / 1000;
	ext_ev_timer_init(&skillAnimationTimer, anm_timer_cb, realTime, 0, this);
	ev_timer_start(loops, &skillAnimationTimer);
	return 0;
}
