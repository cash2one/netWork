/*
		�ļ����ͣ�ͷ�ļ�
		
		�ļ����ƣ�game_fight_assist.h
		
		�ļ����ã�����Ϸ�򶷲����������õĺ����Ķ���
*/

#ifndef COMMAND_OTHER_FUNCTION_GAME_FIGHT_H
#define COMMAND_OTHER_FUNCTION_GAME_FIGHT_H

#include"libev.h"

#include"data_structure_struct.h"

#include"monsterBase.h"

#include"hero.h"

#include"skill.h"

class MonsterBase;

class Hero;        //by chenzhen 4.23

class Skill;

int attackRangePoint(Point pt_attack,Point pt_hited,int attack_range);  //�жϹ������뱻������֮��ľ����Ƿ�Ϸ�

void send_success(Hero *attack,Hero *hited,Skill *skill,int redlose);//������ҳɹ���client������Ϣ

void attack_monster_success(Hero *attack,MonsterBase *hited,Skill *skill,int redlose);//��������ɹ�����client��Ϣ
#endif
