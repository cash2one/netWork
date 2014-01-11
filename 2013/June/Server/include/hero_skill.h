/****************************************************************
 * Filename: hero_skill.h
 * 
 * Description: ���＼��
 *
 * Original Author : bison, 2012-11-14
 *
 ****************************************************************/
#ifndef _HERO_SKILL_H_
#define _HERO_SKILL_H_

#include<iostream>
#include"my_timer.h"
using namespace std;

#define HERO_SKILL_MAX_NUM					14		//�����������
#define HERO_SKILL_TOP_LEVEL				20		//��ɫ�������ȼ�

//��������Type 	0:������������1:������ħ�����ޣ�2:�������⹦������3:�������ڹ�����
//				4:�������⹦������5:�������ڹ�������6:���������У�7�����������ܣ�
//				8:���������ԣ�9:�����ӱ�����10:�������⹦�˺���11:�������ڹ��˺�
#define HERO_SKILL_MIN_STATIC_TYPE			0		//��ɫ������������ֵ��Χ����
#define HERO_SKILL_MAX_STATIC_TYPE			11		//��ɫ������������ֵ��Χ����
#define HERO_SKILL_NORMAL_TYPE				100		//��ͨ����
#define HERO_SKILL_SINGLE_HURT_TYPE			101		//����������������
#define	HERO_SKILL_RUSH_TYPE				102		//��漼��
#define HERO_SKILL_BUFF_TYPE				103		//Ӣ��buff�༼��
#define HERO_SKILL_SINGLE_TREAT_TYPE		104		//����ҽ��
#define HERO_SKILL_MANY_HURT_NO_AIM_TYPE 	105		//Ⱥ����ָ��
#define	HERO_SKILL_MANY_HURT_WITH_AIM_TYPE	106		//Ⱥ����ָ��
#define HERO_SKILL_MANY_TREAT_TYPE			107		//Ⱥ��ҽ��
#define HERO_SKILL_MIN_DYNAMIC_TYPE			100		//������������ֵ��Χ����
#define HERO_SKILL_MAX_DYNAMIC_TYPE			107		//������������ֵ��Χ����

typedef struct HeroMemSkill_S
{
	char skillId[10];
	unsigned level;
	unsigned lastUsedTime;
} HeroMemSkill_T;
extern HeroMemSkill_T M_SkillBase[HERO_SKILL_MAX_NUM];
extern HeroMemSkill_T H_SkillBase[HERO_SKILL_MAX_NUM];
extern HeroMemSkill_T G_SkillBase[HERO_SKILL_MAX_NUM];
extern HeroMemSkill_T X_SkillBase[HERO_SKILL_MAX_NUM];

typedef struct HeroSkill_S
{
	char skillId[10];					//����ID
	unsigned type;						//��������
	unsigned buffType;					//���ܸ���buff����
	unsigned attackRange;				//������Χ
	unsigned hurtRange;					//�˺���Χ
	float	 animationTime;				//����ʱ��
	float	 partyFactor;				//�����˺�ϵ��
	unsigned upgradeNeedHeroLevel[20];	//������Ҫ�Ľ�ɫ�ȼ�
	unsigned upgradeNeedMoney[20];		//������Ҫ��Ǯ
	unsigned upgradeNeedExp[20];		//������Ҫ����
	unsigned cdTime[20];				//CDʱ��
	unsigned needMagic[20];				//�ͷż�������ħ��
	unsigned value[20];					//������ֵ
	unsigned totalVal[20];				//����������ֵ
	unsigned attkNum[20];				//���ܹ���Ŀ����
	float 	 factor[20];				//�����˺�/ҽ��ϵ��
	unsigned attkType;					//��������
} HeroSkill_T;

class HeroSkill
{
private:
	char skillId[10];					//����ID
	unsigned type;						//��������
	unsigned buffType;					//���ܸ���buff����
	unsigned attackRange;				//������Χ
	unsigned hurtRange;					//�˺���Χ
	float	 animationTime;				//����ʱ��
	float	 partyFactor;				//�����˺�ϵ��
	unsigned upgradeNeedHeroLevel[20];	//������Ҫ�Ľ�ɫ�ȼ�
	unsigned upgradeNeedMoney[20];		//������Ҫ��Ǯ
	unsigned upgradeNeedExp[20];		//������Ҫ����
	unsigned cdTime[20];				//CDʱ��
	unsigned needMagic[20];				//�ͷż�������ħ��
	unsigned value[20];					//������ֵ
	unsigned totalVal[20];				//����������ֵ
	unsigned attkNum[20];				//���ܹ���Ŀ����
	float 	 factor[20];				//�����˺�/ҽ��ϵ��
	unsigned attkType;					//��������
public:
	HeroSkill(HeroSkill_T &skillData);
	
	//���ܻ�������
	char *getId();
	unsigned getType();
	unsigned getBuffType();
	//����Ч������
	unsigned getAttackRange();
	unsigned getHurtRange();
	float getAnimationTime();
	float getPartyFactor();
	unsigned getAttkType();
	
	unsigned getCdTime(unsigned level);
	unsigned getNeedMagic(unsigned level);
	unsigned getValue(unsigned level);
	unsigned getTotalVal(unsigned level);
	float getFactor(unsigned level);
	unsigned getAttkNum(unsigned level);
	//������������
	unsigned getUpgradeNeedHeroLevel(unsigned level);
	unsigned getUpgradeNeedMoney(unsigned level);
	unsigned getUpgradeNeedExp(unsigned level);
};
#endif