#ifndef COMMAND_USER_ROLE_MANAGE_H
#define COMMAND_USER_ROLE_MANAGE_H

#include"role.h"

#define DEFAULT_DB	1				//Ĭ�ϵ�ǰ���Զ�������1�Ż�����������������ɿͻ���ѡ�� tory

void loginUser(char *buffer);       		//�����½�����

void login_from_web(char* buffer);			//��web��¼

void exit_accident(int sock_fd);           	//����������˳������

void exit_normal(char *buffer);           	//���������˳������

void createHero(char *buffer);				//��ɫ����������

void selectHero(char *buffer);				//��ɫѡ������

void deleteHero(char *buffer);				//ɾ����ɫ cookie

void heroLearnSkill(char *buffer);          //��ɫѧϰ����

void change_scene(char *buffer);			//�����л�

void closeServerDeal(Hero *myHero);  		//�������رմ���

void doneline_operate(char *buffer);		//��ɫ���ߣ�

void temp_guest_change_name(char* buffer);	//�����û�����������ʱ�û���Ч��

#endif 
