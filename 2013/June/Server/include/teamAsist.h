#ifndef TEAM_ASIST_H
#define TEAM_ASIST_H

#include"team.h"

//����ص�����
void teamBindCal(struct ev_loop *loop,ev_timer *think,int revents);

//����-1����ʾ�쳣��0������ӣ�1����Ա��2���ӳ�,teamMum:��ʾ��������
int judgeHeroTeam(const Hero * heroMem,size_t &teamMum);

#endif

