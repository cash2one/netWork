/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�user_role_zhudong.h
		�ļ����ã������������ܵ�Ч��ʵ��
*/

#ifndef USER_ROLE_ZHUDONG
#define USER_ROLE_ZHUDONG
#include"hero.h"
#include"skill.h"
#include"monsterBase.h"
int heroVShero(Hero *hero,Hero *hited,Skill *skill);
int heroVSmonster(Hero *attack,MonsterBase *hited,Skill *skill);
#endif