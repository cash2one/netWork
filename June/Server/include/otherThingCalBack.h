/************************************************************
	�ļ�����otherThingCalBack.h
	�ļ����ã�����ƿ�ޣ����壬�Լ��ɼ���Ʒ��ˢ��������ʧ�Լ������Ŀ���
	���ߣ�chenzhen
	�������ڣ�2012.07.13
************************************************************/
#ifndef OTHER_THING_CALL_BACK_H
#define OTHER_THING_CALL_BACK_H
#include"libev.h"

/*ƿ�޴��飬�Լ���ˢ����*/
void botThkCalBack(struct ev_loop *loop,ev_timer *think,int revents);

/*����ص�*/
void trapThkCalBack(struct ev_loop *loop,ev_timer *think,int revents);

/*��ժȡ��Ʒ����ʧ�Լ���ˢ����*/
void takeGoodsThkCalBack(struct ev_loop *loop,ev_timer *think,int revents);

/*������ʧ�ص�����*/
void trapDispearCalBack(struct ev_loop *loop,ev_timer *think,int revents);

/*����ʾ���ص�����*/
void trapWarnCalBack(struct ev_loop *loop,ev_timer *think,int revents);

#endif