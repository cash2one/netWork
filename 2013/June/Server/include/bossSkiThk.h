/************************************************************
	�ļ�����bossSkiThk.h
	�ļ����ã�����Boss��ʱ�ԣ����м�ʱ��������˼������ԭ��
	���ߣ�chenzhen
	�������ڣ�2012.07.13
************************************************************/
#ifndef BOSS_SKILL_THK_H
#define BOSS_SKILL_THK_H
#include"libev.h"

/*����˼������ԭ��,���޵���*/
void monSkiCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*�޵лص�����*/
void monSkiUnEnemyCalBack(struct ev_loop *loop,ev_timer *think,int revents);

/*����cd�Ͳ���ʱ��ص�����*/
void monCdCalBak(struct ev_loop *loop,ev_timer *think,int revents);

#endif