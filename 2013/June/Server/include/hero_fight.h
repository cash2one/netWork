#ifndef _HERO_FIGHT_H_
#define _HERO_FIGHT_H_

#include"hero.h"
#include"math.h"
#include"bottle.h"
#include"wagon.h"

#define MAX_HERO_CRIT_VALUE		20000000	//�����󱩻�ֵ
#define MAX_HERO_TENACITY_VALUE	20000000	//����������ֵ
#define MAX_HERO_HIT_VALUE		20000000	//����������ֵ
#define MAX_HERO_DODGE_VALUE	20000000	//����������ֵ

#define PEACE_MODE				1
#define ALL_WAR_MODE			2
#define CAMP_WAR_MODE			3
#define GUILD_WAR_MODE			4

//������������
#define BASIC_HURT_CAL(atkA, hurtA, defB)	(2 * (atkA) * (hurtA) / ((hurtA) + (defB)))
#define REFLECT_HURT_CAL(hero, hurt) ((hurt) *	\
((hero)->skillBuff[hero->getIndexByState(BUFF_REFLEX_STATE)].totalVal) / 1000)

#define GET_HERO_SKILL_FACTOR(p_skill, level) (p_skill->getPartyFactor() * p_skill->getAnimationTime()\
	+ p_skill->getFactor(level))

#define GET_DISTANCE_SQR(ptA, ptB)	(((ptA)._x - (ptB)._x) * ((ptA)._x - (ptB)._x)\
									+ ((ptA)._y - (ptB)._y) * ((ptA)._y - (ptB)._y))
#define GET_DISTANCE(ptA, ptB)	sqrt(GET_DISTANCE_SQR(ptA, ptB))
		
#define IS_OUT_RANGE(ptA, ptB, dist)	((dist) < (GET_DISTANCE(ptA, ptB)))

#define JUDGE_WILL_LIFE(obj, hurt)	((obj->getLifeVal() <= hurt) ? 0 : (obj->getLifeVal() - hurt))

typedef struct FightConst_S
{
	float attkFactor;
	float defFactor;
	float hitFactor;
	float critFactor;
	float tencFactor;
	float critBase;
	float tencBase;
	float tencMax;
	float critDivisor;
	float critTimes;
}FightConst_T;

extern FightConst_T fightConst;

//basic_cal
//��������
int crit_cal(unsigned &atkCrit, unsigned &tenacity, bool &isCrit, float &critTimes);
//���ܼ���
int dodge_cal(unsigned &atkHit, unsigned &batkdDodge, bool &isHited, float &hitTimes);
//�Ƿ񱩻�
bool isTouchCrit(int critA, int tencB);
//�Ƿ�����
bool isTouchHit(int hitA, int dodgeB);

//fight_val_cal
//�Ƿ�����
bool is_hited_judge(Hero *atker, unsigned obj_flag, void *obj, float &hitTimes, bool forbidDodge);
//��ɫ�ܻ�����
int attack_hero_cal(Hero* atker, Hero* atked, float hitTimes,
	HeroSkill *p_skill, unsigned level, bool &isCrit);
//�����ܻ�����
int attack_monster_cal(Hero* atker, MonsterBase* atked, float hitTimes,
	HeroSkill *p_skill, unsigned level, bool &isCrit);
//ҽ�ƻظ�ֵ����
unsigned cure_life_cal(Hero *hero, HeroSkill *p_skill, unsigned skillLevel);
//���˴���
void decHurtBuffDeal(Hero* atked, int &lifeHurt, int &reflectHurt);

//proc_lose_life
//��ҿ�Ѫͳһ����
void proc_hero_lose_life(Hero* atker, Hero* hero, unsigned lifeHurt);
//�����Ѫͳһ����
void proc_mon_lose_life(Hero *atker, MonsterBase* mon, unsigned lifeHurt);
//����Ѫͳһ����
void proc_wagon_lose_life(Hero* atker, Wagon* wagon, int lifeHurt);
//ƿ�ӿ�Ѫͳһ����
void proc_bottle_lose_life(Hero* atker, Bottle* bottInst, int lifeHurt);

//hero_skill_deal
//��ͨ����ָ���Լ���
void single_aimed_skill_deal(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void* obj, char *objId, float animationTime);
//����ָ����֮���
void single_aimed_rush_skill_deal(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void *obj, char *objId, float animationTime);
//Ⱥ�弼�� flag = true:Ⱥ��ָ���Լ��ܣ�flag = false:��ָ����
void many_hurt_skill_deal(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void *obj, bool flag, float animationTime);
//����ҽ�Ƽ���
void single_cure_skill_deal(Hero* owner, HeroSkill* p_skill, unsigned skillLevel, float animationTime);
//Ⱥ��ҽ�Ƽ���
void many_cure_skill_deal(Hero* owner, HeroSkill* p_skill, unsigned skillLevel, float animationTime);

//proc_use_skill
//�����ж�
int relationCheck(Hero *heroA, Hero* heroB, Map_Inform* map);
//ʹ�ü��ܴ���
int proc_use_skill(Hero* owner, char *skillId, char *objId, int &remainCD);
//������Ϊ���ģ����;Ź�����Ϣ
void send_nine_msg(Hero *hero, char* msg);

//use_skill_comm
//ʹ�ü���ͨ��
void use_skill_comm(char *buffer);
#endif