/**********************************************
*	author	��	Tory
*	date	:	2012.3.26
*	�ļ����ƣ�	game_move.h
*	�ļ����ã�	��ɫ�ƶ���Ϣ�Ĺ㲥���������º����Ķ���
*********************************************/
#ifndef GAME_MOVE
#define GAME_MOVE
#include "pet.h"

/*�ƶ������*/
void move_get_road(char *buffer);        //�����ƶ�����

/*������������*/
void timePoll(char* buffer);			//����������

/*�ƶ���������*/
void objMoveAsist(int objTpe,char *objId,Point &newPiexPt,char *moveMsg);

/*�����ƶ�*/
void petMoveAsist(char *objId,Point &newPiexPt,char *moveMsg);

/*���ƶ�*/
void wagonMoveAsist(char *objId,Point &newPiexPt,char *moveMsg);


#endif