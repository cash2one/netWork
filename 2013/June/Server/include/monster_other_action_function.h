#ifndef MONSTER_OTHER_ACTION_FUNCTION_H
#define MONSTER_OTHER_ACTION_FUNCTION_H
#include"libev.h"
void monThkCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*���Թ���˼����������,������*/
void printMonThk(void);

/*���︴��*/
void monReLifeCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*�����Ѫ*/
void monRecoverBooldCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*�������ص�����*/
void monTaskCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*����cd�ص�����*/
void monCdCalBal(struct ev_loop *loop,ev_timer *think,int revents);

#endif




	
