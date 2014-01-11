#include "hero.h"
#include "money_operator.h"
#define	UPGRADE_SKILL_SUCCESS					0	//�������ܳɹ�
#define UPGRADE_SKILL_FAILED_ERROR_SKILLID		1	//������ID
#define UPGRADE_SKILL_FAILED_BORN_SKILL			2	//�չ����ܲ�������
#define UPGRADE_SKILL_FAILED_CONF_MORE_SKILL	3	//�����¼Ӽ��ܴ���δ��Ӧ
#define UPGRADE_SKILL_FAILED_LEVEL_FULL			4	//��Ҽ����Ѿ�����
#define UPGRADE_SKILL_FAILED_HERO_LEVEL_LIMIT	5	//��ҵȼ�����
#define	UPGRADE_SKILL_FAILED_EXP_NOT_ENOUGH		6	//��Ҿ��鲻��
#define	UPGRADE_SKILL_FAILED_MONEY_NOT_ENOUGH	7	//��ҽ�Ǯ����

extern map<string, HeroSkill*> skillId_2_heroSkill;

int upgrade_hero_skill(Hero *hero, char *skillId, char *msg)
{
	char *p = skillId;
	HeroSkill* skill;
	map<string, HeroSkill*>::iterator it_skill;
	it_skill = skillId_2_heroSkill.find(skillId);
	if (it_skill == skillId_2_heroSkill.end())
	{
		cout<<"Hero upgrade skill but the skillId "<<skillId<<" client sent is error"<<endl;
		return UPGRADE_SKILL_FAILED_ERROR_SKILLID;
	}
	
	p++;
	unsigned index = atoi(p);
	if (index == 0)
	{
		cout<<"The born skill needn't to learn!"<<endl;
		return UPGRADE_SKILL_FAILED_BORN_SKILL;
	}
	//(�������13)
	if (index > HERO_SKILL_MAX_NUM)
	{
		cout<<"warning: there is more skills in config , please enLarge the HERO_SKILL_MAX_NUM!!"<<endl;
		return UPGRADE_SKILL_FAILED_CONF_MORE_SKILL;
	}
	
	HeroMemSkill_T *memSkill = &hero->memHero->skills[index];
	
	//�ü������� (20��)
	if (memSkill->level >= HERO_SKILL_TOP_LEVEL)
	{
		cout<<"The hero's skill is already top level, no need to upgrade!"<<endl;
		return UPGRADE_SKILL_FAILED_LEVEL_FULL;
	}
	
	//����������
	skill = it_skill->second;
	//������Ҫ����ҵȼ����
	if (skill->getUpgradeNeedHeroLevel(memSkill->level) > hero->getLevel())
	{
		cout<<"The hero's level is not enough to study this skill"<<endl;
		return UPGRADE_SKILL_FAILED_HERO_LEVEL_LIMIT;
	}
	
	//������Ҫ�ľ�����
	unsigned needExp = skill->getUpgradeNeedExp(memSkill->level);
	if (hero->getHeroSkillExp() < needExp)
	{
		cout<<"The hero doesn't have enough exp to upgrade this skill"<<endl;
		return UPGRADE_SKILL_FAILED_EXP_NOT_ENOUGH;
	}
	
	//������Ҫ��Ǯ���
	unsigned needMoney = skill->getUpgradeNeedMoney(memSkill->level);
	if (!useBoundGameMoney(hero, needMoney))
	{
		cout<<"The hero doesn't have enough bound money to upgrade this skill"<<endl;
		return UPGRADE_SKILL_FAILED_MONEY_NOT_ENOUGH;
	}
	
	//������������
	// hero->useExpNow(needExp);
	hero->useHeroSkillExp(needExp);
	hero->memHero->skills[index].level += 1;
	hero->memHero->skills[index].lastUsedTime = 0;
	int nowLevel = hero->memHero->skills[index].level;
	//����Ǳ������ܣ�heroҪ���϶�Ӧ����
	unsigned type = skill->getType();
	if (type >= 0 && type <= 11)
	{
		// hero->incAttr(type, skill->getValue(nowLevel));
		hero->addAttr(type, skill->getValue(nowLevel));
		hero->send_msg_att();
	}

	hero->updataSingleTarget(0,3);
	
	int k = 0;
	int skillMaxFlag=0;
	for ( k; k < HERO_SKILL_MAX_NUM; k++)
	{
		if (hero->memHero->skills[k].level == 0)
		{
			break;
		}
		else if (hero->memHero->skills[k].level == 20)
		{
			skillMaxFlag++;
		}
	}
	
	if(k >= 2)
	{
		hero->addTitle("T009");//���ͷ�Σ�ѧϰ��һ������
	}
	
	if(k >= 6)
	{
		hero->addTitle("T010");//���ͷ�Σ�ѧϰ��5������,����Ѿ�
	}
	
	if (k == HERO_SKILL_MAX_NUM)
	{
		hero->addTitle("T011");//���ͷ�Σ�ѧϰ���м���,��ѧ��ʦ
		hero->updataSingleTarget(6,5);
	}
	if (skillMaxFlag == HERO_SKILL_MAX_NUM)
	{
		hero->updataSingleTarget(7,5);
	}
	
	sprintf(msg, "%s,%d,%d,%d,%d,%d", skillId, nowLevel, skill->getNeedMagic(nowLevel),
		skill->getUpgradeNeedHeroLevel(nowLevel), skill->getUpgradeNeedExp(nowLevel),
		skill->getUpgradeNeedMoney(nowLevel));
	return UPGRADE_SKILL_SUCCESS;
}