/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�user_role_hero_attack_manage.h
		�ļ����ã���ҽ�ɫ��ս��ʱʹ�ü��ܵ��õļ��ܷ���
*/

#ifndef USER_ROLE_HERO_ATTACK_MANAGE
#define USER_ROLE_HERO_ATTACK_MANAGE
#include"hero.h"
#include"monsterBase.h"
#include"skill.h"
#include"dropgoods.h"
int general_attack_monster(Hero *attack,MonsterBase *hited,Skill *skill);

int heroTomonster_attack(Hero *attack,MonsterBase *hited,Skill *skill);

int hq(int _dj,int _rdj);			//����ֵ������㹫ʽ,cookieʵ��
#endif