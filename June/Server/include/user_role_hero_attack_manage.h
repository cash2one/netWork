/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�user_role_hero_attack_manage.h
		�ļ����ã���ҽ�ɫ��ս��ʱʹ�ü��ܵ��õļ��ܷ���
*/

#ifndef USER_ROLE_HERO_ATTACK_MANAGE
#define USER_ROLE_HERO_ATTACK_MANAGE
#include"hero.h"
#include"skill.h"
int general_attack(Hero *attack,Hero *hited,Skill *skill);
int oneToone_attack(Hero *attack,Hero *hited,Skill *skill);
#endif