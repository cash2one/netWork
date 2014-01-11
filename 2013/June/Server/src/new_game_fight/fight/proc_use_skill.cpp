#include "hero_fight.h"
#include"wagon.h"

#define USE_HERO_SKILL_SUCCESS					0				//ʹ�ü��ܳɹ�
#define USE_SKILL_FAILED_ATK_DEAD				1				//����ʹ�����Ѿ�����
#define USE_SKILL_FAILED_ATK_IN_ANMT			2				//������һ���ܶ���
#define USE_SKILL_FAILED_ATK_IN_DIZZ			3				//�����ѣ����
#define USE_SKILL_FAILED_NO_THIS_SKILL			4				//û�д˼���
#define USE_SKILL_FAILED_STATIC_SKILL			5				//��������
#define USE_SKILL_FAILED_SKILL_CONF_ERROR		6				//�������¼Ӽ���
#define USE_SKILL_FAILED_NOT_UPGRADE			7				//δ�����ü���
#define USE_SKILL_FAILED_IN_CD_TIME				8				//������CD��
#define USE_SKILL_FAILED_NO_ENOUGH_MP			9				//û���㹻ħ��
#define USE_SKILL_FAILED_CAN_NOT_ATK_SELF		10				//ָ���Թ������ܲ��ܹ����Լ�
#define USE_SKILL_FAILED_NOT_FIND_ATKED_OBJ		11				//��������Ҳ�����
#define USE_SKILL_FAILED_ATKED_HERO_DIED		12				//�������Ѿ�����
#define USE_SKILL_FAILED_ATKED_HERO_INVINC		13				//����������޵�״̬
#define USE_SKILL_FAILED_ATKED_IN_DIFF_MAP		14				//��������Ҳ���ͬһ��ͼ
#define USE_SKILL_FAILED_CAN_NOT_ATK_FRIEND		15				//���ܹ����ѷ���λ
#define USE_SKILL_FAILED_CAN_NOT_CURE_ENEMY		16				//�������Ƶз���λ
#define USE_SKILL_FAILED_CAN_NOT_CURE_MON		17				//�������ƹ���
#define USE_SKILL_FAILED_ATKED_MON_INVINC		18				//���������ﴦ���޵�״̬
#define USE_SKILL_FAILED_ATKED_MON_DIED			19				//�����������Ѿ�����
#define USE_SKILL_FAILED_ATKED_TOO_FAR			20				//�����߾���̫Զ
#define	USE_SKILL_FAILED_HAS_BARR_BETWEEN		21				//��漼���м����ϰ�
#define USE_SKILL_FAILED_WAGON_DEAD				22				//���������Ѿ�����
#define USE_SKILL_FAILED_ATK_SELF_WAGON			23				//���ܹ����Լ�����
#define	USE_SKILL_FAILED_ATKED_BOTT_BROKEN		24				//������ƿ���Ѿ�������
#define USE_SKILL_FAILED_PEACE_ATK_WAGON		25				//��ƽͼģʽ�²��ܹ�����

extern map<string, HeroSkill*> skillId_2_heroSkill;		//��ɫ����
extern map<string,Wagon*> wagonInstMap;						//��ʵ��
//�����ͷ���״̬���
int skill_owner_check(Hero *owner, HeroMemSkill_T* &p_memSkill, HeroSkill* &p_skill, char *skillId, int &remainCD);
//�������ö�����
int skill_aimed_obj_check(Hero *owner, unsigned skill_flag, unsigned &obj_flag,
	char *objId, void * &obj, Point &obj_loc);
//������
int skill_distance_check(Point ownerPt, Point objPt, int skillType, unsigned distance, Map_Inform *mapNow);

int proc_use_skill(Hero* owner, char *skillId, char *objId, int &remainCD)
{
	owner->stopCollectTimer(2);				//���ʹ�ü��ܴ�ϲɼ�
	int ret = 0;
	//��һ�׶Σ���鼼��ʹ������Ϣ
	HeroMemSkill_T *p_memSkill = NULL;
	HeroSkill *p_skill = NULL;
	ret = skill_owner_check(owner, p_memSkill, p_skill, skillId, remainCD);
	if (ret != 0)
	{
		return ret;
	}

	unsigned skill_flag = 0;		//��������		0��������1��ҽ��
	unsigned obj_flag = 0;			//����������	0:�޹���Ŀ�ꣻ1:�����ˣ�2:��������
	unsigned aim_flag = 0;
	unsigned skillType = p_skill->getType();
	if (skillType == HERO_SKILL_SINGLE_TREAT_TYPE || skillType == HERO_SKILL_MANY_TREAT_TYPE)
	{
		skill_flag = 1;
	}
	if (skillType == HERO_SKILL_NORMAL_TYPE						//�չ�
		|| skillType == HERO_SKILL_SINGLE_HURT_TYPE				//������������
		|| skillType == HERO_SKILL_RUSH_TYPE					//��漼��
		|| skillType == HERO_SKILL_MANY_HURT_WITH_AIM_TYPE)		//��ָ��Ⱥ�弼��
	{
		aim_flag = 1;
	}
	
	//�ڶ��׶μ��
	Point obj_loc;
	void *obj = NULL;
	if (aim_flag)			//�����Ҫ�й�������ļ���
	{
		ret = skill_aimed_obj_check(owner, skill_flag, obj_flag, objId, obj, obj_loc);
		if (ret != 0)
		{
			return ret;
		}
	}
	//�����׶Σ�������,��̼��ܵ��Ƿ����ϰ����Ҳ������
	unsigned distance = p_skill->getAttackRange();
	
	Point ownerPt = owner->getLocation();
	Map_Inform *mapNow = owner->getMap();
	ret = skill_distance_check(ownerPt, obj_loc, skillType, distance, mapNow);
	if (ret != 0)
	{
		return ret;
	}
	
	unsigned level = p_memSkill->level;
	int needMagic = p_skill->getNeedMagic(level);
	float animationTime = p_skill->getAnimationTime();
	//����ħ��
	owner->setMagicVal(owner->getMagicVal() - needMagic);
	//���ok
	//��¼�¼��ܵ�ǰʹ��ʱ�䣬һ���´�ʹ�õ�CD�ж�
	p_memSkill->lastUsedTime = MY_TV_SEC;
	owner->startHeroSkillAnimationTimer(animationTime);
	//��������
	if (skill_flag == 0)
	{
		if (obj_flag != 0)	
		{	
			//��ָ����
			if (skillType == HERO_SKILL_SINGLE_HURT_TYPE || skillType == HERO_SKILL_NORMAL_TYPE)	
			{
				//��ͨ����ָ���Լ���
				single_aimed_skill_deal(owner, p_skill, level, obj_flag, obj, objId, animationTime);
				
			} else if (skillType == HERO_SKILL_RUSH_TYPE)	
			{
				//����ָ����֮���
				single_aimed_rush_skill_deal(owner, p_skill, level, obj_flag, obj, objId, animationTime);
				
			} else if (skillType == HERO_SKILL_MANY_HURT_WITH_AIM_TYPE)
			{
				//Ⱥ��ָ���Լ���
				many_hurt_skill_deal(owner, p_skill, level, obj_flag, obj, true, animationTime);
				
			} else {
				cout<<"When you see this may be it caused by the follow three resons:"<<endl;
				cout<<"1:The client have send error comm msg without following the rule!"<<endl;
				cout<<"2:The client's hero skills conf is error"<<endl;
				cout<<"3:The server's hero skills conf is error and the skillId is "<<skillId<<endl;
				return USE_SKILL_FAILED_SKILL_CONF_ERROR;
			}
		} else {
			//��ָ�򹥻�����
			if (skillType == HERO_SKILL_BUFF_TYPE)
			{
				//buff���ͼ���
				char msg[400] = {0};
				sprintf(msg, "26,2,1,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d", skillId, (int)ceil(animationTime),
					owner->getIdentity(), owner->getLifeVal(), owner->getLifeUpperVal(),
					owner->getMagicVal(), owner->getMagicUpperVal(), 0, 0, 0, 0);
				send_nine_msg(owner, msg);
				owner->startBufOrDebuffTimer(owner->getIdentity(), skillId, level);
				return 0;
				
			} else if (skillType == HERO_SKILL_MANY_HURT_NO_AIM_TYPE) {
				//��ָ����Ⱥ������
				many_hurt_skill_deal(owner, p_skill, level, obj_flag, obj, false, animationTime);
			} else {
				cout<<"When you see this may be it caused by the follow three resons:"<<endl;
				cout<<"1:The client have send error comm msg without following the rule!"<<endl;
				cout<<"2:The client's hero skills conf is error"<<endl;
				cout<<"3:The server's hero skills conf is error and the skillId is "<<skillId<<endl;
				return USE_SKILL_FAILED_SKILL_CONF_ERROR;
			}
		}
	} else {
		//ҽ�ƴ���
		if (skillType == HERO_SKILL_SINGLE_TREAT_TYPE)
		{
			//����ҽ�Ƽ���
			single_cure_skill_deal(owner, p_skill, level, animationTime);
			
		} else if (skillType == HERO_SKILL_MANY_TREAT_TYPE)
		{
			//Ⱥ��ҽ�Ƽ���
			many_cure_skill_deal(owner, p_skill, level, animationTime);
			
		} else {
			cout<<"When you see this may be it caused by the follow three resons:"<<endl;
			cout<<"1:The client have send error comm msg without following the rule!"<<endl;
			cout<<"2:The client's hero skills conf is error"<<endl;
			cout<<"3:The server's hero skills conf is error and the skillId is "<<skillId<<endl;
			return USE_SKILL_FAILED_SKILL_CONF_ERROR;
		}
		
	}
	return USE_HERO_SKILL_SUCCESS;
}

//������
int skill_distance_check(Point ownerPt, Point objPt, int skillType, unsigned distance, Map_Inform *mapNow)
{
	if (skillType == HERO_SKILL_SINGLE_HURT_TYPE				//������������
		|| skillType == HERO_SKILL_RUSH_TYPE					//��漼��
		|| skillType == HERO_SKILL_MANY_HURT_WITH_AIM_TYPE)		//��ָ��Ⱥ�弼��
	{
		cout<<"222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"<<endl;
		cout<<"222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"<<endl;
		cout<<"atkRange is "<<distance<<" and distance from the obj is "<<GET_DISTANCE(ownerPt, objPt)<<endl;
		printf("ownerPt(%d,%d) and objPt(%d,%d)", ownerPt._x, ownerPt._y, objPt._x, objPt._y);
		if (distance < GET_DISTANCE(ownerPt, objPt))
		{
			//�������벻��
			cout<<"The attacked obj is out of hero skill attack range!"<<endl;
			return USE_SKILL_FAILED_ATKED_TOO_FAR;
		}
#if 0		
		if (skillType == HERO_SKILL_RUSH_TYPE)
		{
			//��漼�ܣ��м����ϰ��㲻�ܳ��
			if (hasBarrier(ownerPt, objPt, mapNow))//TODO 
			{
				return USE_SKILL_FAILED_HAS_BARR_BETWEEN;
			}
		}
#endif		
	}
	return 0;
}

int skill_aimed_obj_check(Hero *owner, unsigned skill_flag, unsigned &obj_flag,
	char *objId, void * &obj, Point &obj_loc)
{
	Map_Inform* mapNow = owner->getMap();
	char *ownerMapId = owner->getMapId();
	
	if (skill_flag == 0)				//��ָ�򹥻��Լ���
	{
		//����ʱ���ö�����Ϊ�Լ�
		if (!strcmp(objId, owner->getIdentity()))
		{
			cout<<"the hero can't use skill to attack himself!"<<endl;
			return USE_SKILL_FAILED_CAN_NOT_ATK_SELF;
		}
	}
		
	Hero* obj_hero = heroid_to_hero(objId);
	if (obj_hero != NULL)
	{
		obj_flag = 1;			//��������Ϊ��
		if (obj_hero->getLifeVal() <= 0)
		{
			cout<<"the hero_skill aimed hero is dead!"<<endl;
			return USE_SKILL_FAILED_ATKED_HERO_DIED;
		}
		
		if (obj_hero->skillBuffState & BUFF_INVINCIBLE_STATE)
		{
			cout<<"the attacked hero is in invincible state(forbiden attack)"<<endl;
			return USE_SKILL_FAILED_ATKED_HERO_INVINC;
		}
		
		char *mapId = obj_hero->getMapId();
		if (strcmp(ownerMapId, mapId) != 0)
		{
			//����ͬһ�ŵ�ͼ��
			cout<<"the skill owner and the obj_hero is not in the same map!"<<endl;
			return USE_SKILL_FAILED_ATKED_IN_DIFF_MAP;
		}
		int rc = relationCheck(owner, obj_hero, mapNow);
		//���ܹ����ѷ���λ/��ƽ��ͼ�����໥����
		if (skill_flag == 0 && rc <= 1)
		{
			cout<<"the hero can't attack his friend or he can't fight in peace city!"<<endl;
			return USE_SKILL_FAILED_CAN_NOT_ATK_FRIEND;
		}
		
		//���ܸ��з���λ��Ѫ
		if (skill_flag == 1 && rc == 2)
		{
			cout<<"the hero can't cure his enemy!"<<endl;
			return USE_SKILL_FAILED_CAN_NOT_CURE_ENEMY;
		}
		obj_loc = obj_hero->getLocation();
		obj = obj_hero;
		return 0;
		// return USE_SKILL_FAILED_NOT_FIND_ATKED_HERO;
	} else {
		//ָ����ҽ�Ƽ��ܲ��������ڷǽ�ɫ����
		if (skill_flag == 1)			//ҽ�Ƽ��ܲ���ҽ�ƹ���
		{
			cout<<"the monsters are your enemy forever, so you can't cure them!"<<endl;
			return USE_SKILL_FAILED_CAN_NOT_CURE_MON;
		}
		//ָ���Թ������ܣ�ֻ��鹥���˺͹����֣���������ﶼ�Ҳ��������ж�����ʧ��
		MonsterBase *obj_mon = mapNow->getMonsterObj(objId);
		if (obj_mon != NULL)
		{
			if (obj_mon->getLifeVal() <= 0 || !obj_mon->getLifeStation())
			{
				//�����Ѿ�����
				cout<<"The hero attacked monster has been died!"<<endl;
				return USE_SKILL_FAILED_ATKED_MON_DIED;
			}
			if (obj_mon->getUnEnemySta())
			{
				//���ﴦ���޵�״̬
				cout<<"The monster is invinc for attack"<<endl;
				return USE_SKILL_FAILED_ATKED_MON_INVINC;
			}
				
			obj_flag = 2;			//��ǹ�������Ϊ����
			obj = obj_mon;
			obj_loc = obj_mon->getLocation();
			return 0;
		}
		
		Wagon *wagon = NULL;
		map<string,Wagon*>::iterator it_wagon;
		it_wagon = wagonInstMap.find(objId);
		if (it_wagon != wagonInstMap.end())
		{
			wagon = it_wagon->second;
			if (wagon->getLifeVal() <= 0)
			{
				cout<<"attacked wagon has died!"<<endl;
				return USE_SKILL_FAILED_WAGON_DEAD;
			}
			//�Ƚ����������ǲ���������
			Hero *wagonOwner = wagon->getOwner();
			if(wagonOwner == NULL)	//tory add 2013.1.10
			{
				return USE_SKILL_FAILED_ATK_SELF_WAGON;
			}
			if (owner != NULL && strcmp(wagonOwner->getIdentity(), owner->getIdentity()) == 0)
			{
				cout<<"use skill failed for can't attack self's wagon"<<endl;
				return USE_SKILL_FAILED_ATK_SELF_WAGON;
			}
			
			if (owner->gethero_PK_status() == PEACE_MODE)
			{
				//��ƽͼģʽ�²��ܹ�����
				cout<<"can't atk wagon in peace mode!"<<endl;
				return USE_SKILL_FAILED_PEACE_ATK_WAGON;
			}
			
			Map_Inform* wagonMap = wagon->getMap();
			char *wagonMapId = wagonMap->getIdentity();
			if (strcmp(wagonMapId, ownerMapId) != 0)
			{
				cout<<"use skill fail for attack wagon is not in the same map!"<<endl;
				return USE_SKILL_FAILED_ATKED_IN_DIFF_MAP;
			}
			
			obj_flag = 3;			//��ǹ�������Ϊ��
			obj = wagon;
			obj_loc = wagon->getLocation();
			return 0;
		}
		//��鹥�������Ƿ�Ϊƿ��
		Bottle *bottInst = NULL;
		bottInst = mapNow->getBotInst(objId);
		if (bottInst != NULL)
		{
			if (bottInst->getLifeVal() <= 0)
			{
				cout<<"The atked bottle has already been broken!"<<endl;
				return USE_SKILL_FAILED_ATKED_BOTT_BROKEN;
			}
			obj_flag = 4;			//��ǹ�������Ϊƿ��
			obj = bottInst;
			obj_loc = bottInst->getPiexPt();
			return 0;
		}
		cout<<"can't find the atked obj when use aimed skill!!!!"<<endl;
		return USE_SKILL_FAILED_NOT_FIND_ATKED_OBJ;
		
	}
}

int relationCheck(Hero *heroA, Hero* heroB, Map_Inform* map)
{
	int mapMode = heroA->gethero_PK_status();
	switch(mapMode)
	{
	case GUILD_WAR_MODE:	//��սģʽ������ͬһ��ľ��ǵ���
		if (!strcmp(heroA->getGuildName(), heroB->getGuildName()) && strlen(heroA->getGuildName()) != 0)
		{
			//��ͬ���
			cout<<"The two hero in same guild!!!!!!!!"<<endl;
			return 1;
		} else {
			cout<<"The two hero not in same guild!!!!!!!!"<<endl;
			if (!strcmp(heroA->getTeamerId(), heroB->getTeamerId()) && strlen(heroA->getTeamerId()) != 0)
			{
				cout<<"The two hero in same team!!!!!!"<<endl;
				return 1;
			} 
			return 2;
		}
	case CAMP_WAR_MODE:		//��Ӫսģʽ
		if (heroA->getCamp() == heroB->getCamp() && heroA->getCamp() != -1)
		{
			//��ͬ��Ӫ
			cout<<"The two hero in same camp!!!!!!!!"<<endl;
			return 1;
		} else {
			if (!strcmp(heroA->getTeamerId(), heroB->getTeamerId()) && strlen(heroA->getTeamerId()) != 0)
			{
				cout<<"The two hero in same team!!!!!!"<<endl;
				return 1;
			} 
			cout<<"The two hero not in same camp!!!!!!!!"<<endl;
			return 2;
		}
	case PEACE_MODE:		//��ƽģʽ
	case 0:
		return 0;
	default:
		if (!strcmp(heroA->getTeamerId(), heroB->getTeamerId()) && strlen(heroA->getTeamerId()) != 0)
		{
			cout<<"The two hero in same team!!!!!!"<<endl;
			return 1;
		} else {
			cout<<"The two hero not in same team!!!!!!!!"<<endl;
			return 2;
		}
	}
}

int skill_owner_check(Hero *owner, HeroMemSkill_T* &p_memSkill, HeroSkill * &p_skill, char *skillId, int &remainCD)
{
	//����ʹ���ߴ�������״̬
	if (owner->getLifeVal() == 0)
	{
		cout<<"The hero is dead so he is forbiden to use skills!"<<endl;
		return USE_SKILL_FAILED_ATK_DEAD;
	}
	//��鼼��ʹ����״̬���Ƿ�����ͷż��ܻ򹥻�
	if (owner->skillBuffState & PLAY_ANIMATION_STATE)
	{
		//������һ���ܶ���
		cout<<"The hero can't use this skill when last skill's animation is not finished!"<<endl;
		return USE_SKILL_FAILED_ATK_IN_ANMT;
	}
	if ((owner->skillBuffState & DEBUF_DIZZ_STATE) || (owner->skillBuffState & DEBUF_FORB_ATTK_STATE))
	{
		//ѣ�λ��ߵ�Ѩ״̬
		cout<<"The hero is in the forbiden_attack state when he wants to use skill!"<<endl;
		return USE_SKILL_FAILED_ATK_IN_DIZZ;
	}
	
	map<string, HeroSkill*>::iterator it_skill;
	it_skill = skillId_2_heroSkill.find(skillId);
	if (it_skill == skillId_2_heroSkill.end())
	{
		//�޴˼���
		cout<<"There is no this skill:"<<skillId<<" when hero use skill"<<endl;
		return USE_SKILL_FAILED_NO_THIS_SKILL;
	}
	p_skill = it_skill->second;
	if (p_skill->getType() < 100)
	{
		//�������ܣ��޷�ʹ��
		cout<<"The hero is try to use static skill, but it's no need to use! the skill type is "<<p_skill->getType()<<endl;
		return USE_SKILL_FAILED_STATIC_SKILL;
	}
	
	unsigned index = atoi(skillId + 1);
#if defined(PERFECTLY_CHECK)	//this normally wouldn't happen, just for perfectly check
	if (index >= HERO_SKILL_MAX_NUM)
	{
		cout<<"[System warning] the system should enlarge the val of HERO_SKILL_MAX_NUM for there more skills in conf and the skillId is "<<skillId<<endl;
		return USE_SKILL_FAILED_SKILL_CONF_ERROR;
	}
#endif	
	p_memSkill = &owner->memHero->skills[index];

#if defined(PERFECTLY_CHECK)	//this normally wouldn't happen, just for perfectly check
	if (strcmp(p_memSkill->skillId, skillId))
	{
		cout<<"owner's skills in memHero is error!!"<<endl;
		return USE_SKILL_FAILED_SKILL_CONF_ERROR;
	}
#endif

	if (index != 0 && p_memSkill->level == 0)
	{
		cout<<"The hero hasn't learn this skill when he want to use it!"<<endl;
		return USE_SKILL_FAILED_NOT_UPGRADE;
	}
	
	//CDʱ����(����ͨ����)
	if (index != 0 && p_memSkill->lastUsedTime + p_skill->getCdTime(p_memSkill->level) > MY_TV_SEC)
	{
		remainCD = p_memSkill->lastUsedTime + p_skill->getCdTime(p_memSkill->level) - MY_TV_SEC;
		cout<<"lastUsedTime is "<<p_memSkill->lastUsedTime<<" CD Time is "<<p_skill->getCdTime(p_memSkill->level)<<"now is "<<MY_TV_SEC<<endl;
		cout<<"The hero skill can't be used now for it is in CD time!"<<endl;
		return USE_SKILL_FAILED_IN_CD_TIME;
	}
	
	//�Ƿ����ͷż�������Ҫ��Ѫ����ħ�����
	if (owner->getMagicVal() < p_skill->getNeedMagic(p_memSkill->level))
	{
		return USE_SKILL_FAILED_NO_ENOUGH_MP;
	}
	//��Ѫ�������������ɹ�����ʹѪ�������Ҳ������һ��Ѫ
	//check ok
	return 0;
}