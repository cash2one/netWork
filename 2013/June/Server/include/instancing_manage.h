#ifndef __INSTANCING_MANAGE__
#define __INSTANCING_MANAGE__
#include <iostream>
#include<list>
#include "hero.h"
#include "data_structure_struct.h"
#include "TD_Instancing.h"
#include"libev.h"

//describe:��ʼ����������������
void initInstManage();

//describe: ��������ʱ�䵽�ں�Ļص�����
void cpyOutOfLockCB(struct ev_loop *loop, ev_timer *watcher, int revents);

typedef struct failure_member
{
	int 	failure_flag;				//������븱��ʧ�ܴ��ţ�0���ȼ�������1������������2���Ѷȵȼ�����,��
	char 	nickName[IDL+1];			//��Ӧ��ɫ���ǳ�	
}Failure_Member;

typedef struct _Failure_Reason
{
	int				size;
	Failure_Member	member[4];
}Failure_Reason;


class Instancing_manage{
	public:
		Instancing_manage();	
		TD_Instancing* id2tdRoom(string roomId);			//��������������ʵ��ָ��		
		
		//�ӳ����������������������ɹ��������Ա������ս���������룻������ӳ��������븱��ʧ�ܵ�ԭ��
		int apply_td_inst(Hero* leader, char* td_inst_id);
		
		int enableEnter(Hero *myHero, char *inst_typeId);
		
		string gain_towerDefTeam_roomId(string inst_typeId);
		
		bool enter_inst_room(Hero *heroWillEnter,string tdRoom,int _index);		//��ҽ���ָ����������	
		int	 teamEnter(Team*);
		
		bool start_instancing(TD_Instancing* tdPtr);		//����ָ�������Ķ�ʱ��
		bool stop_instancing(TD_Instancing* tdPtr);			//�ر�ָ�������Ķ�ʱ��
		bool start_instancing(string);	//����ָ�������Ķ�ʱ��
		bool stop_instancing(string);	//�ر�ָ�������Ķ�ʱ��	
		
		bool exit_inst_room(Hero *heroWillQuit, TD_Instancing*);					//�˳�����������
		
	public:
		map<string, TD_Instancing*> instId2totalRooms;	//��������ʵ��
		list<TD_Instancing*> idleRooms;					//�����������з���
};
#endif