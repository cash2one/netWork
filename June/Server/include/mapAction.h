#ifndef MAP_ACTION_H
#define MAP_ACTION_H
#include"libev.h"
class Map_Cpy;
class Map_Src;

void MapThkCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*ˢ��Ұ��boss*/
void brushMonsterActiveBoss(void);

/*����Ұ��boss*/
void initMonsterActiveBoss(void);

/*�ҵ�������ͼʵ��*/
Map_Cpy* findCpyMap(char *cpyMapId);

/*�жϵ�ͼidΪ���ֵ�ͼ*/
int IsCpyMap(char *mapId);

/*�ҵ���ͨ��ͼʵ��*/
Map_Src* findSrcMap(char *mapId);

#endif