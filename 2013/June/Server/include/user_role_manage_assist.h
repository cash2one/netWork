/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�command_other_function_user_manage.h
		�ļ����ã����а���һЩ���û���ɫ�������������õĺ���
*/

#ifndef COMMAND_OTHER_FUNCTION_USER_MANAGE
#define COMMAND_OTHER_FUNCTION_USER_MANAGE

#include"data_structure_struct.h"

#include"hero.h"

#include"hero_configuration.h"

int stringToint(string value);

void sendLogMsg(Hero *myHero);   //add chenzhen 5.14 

void revival(char *buffer);		//add jolly 7.12

void onlineReturn(Hero *hero);	//add jolly 10.10

void heroWearEquip(char *buffer);		//add jolly 10.14

void heroWearEquipDestory(char *buffer);		//add jolly 10.14

void showCampSelect(char *buffer);		//add jolly 

void sendRevivalMsg(Hero *hero, int flag);	//��������͸�����Ϣ

#endif
