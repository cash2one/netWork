#ifndef TEAM_OPERATION
#define TEAM_OPERATION
#include "team.h"
#include"hero.h"
#include"user_role_manage_assist.h"
#include"command_other_function_all_over.h"

void cTeam(char *buff);				//��������

void invited(char *buff);			//��������������
	
void backInvited(char *buff);		//��������ˣ��Ƿ�ͬ�����룬�������
	
void request(char *buff);			//����������
	
void backRequest(char *buff);		//�ӳ��Ƿ�ͬ�������ʹ��������
	
void kick(char *buff);				//��������
		
void leave(char *buff);				//�˳���������

void detail(char *buff);		    //���������Ϣ		

void refresh(char *buff);			//ˢ�������Ϣ

void dismiss(char *buff);			//�ӳ���ɢ����

void assignment(char *buff);		//ת�öӳ�

bool deleteTeamId(string aim,string teamId);

void acceptStateBack(char *buff);	//�������ǰ���Ա���������ӻ��������״̬����
#endif
