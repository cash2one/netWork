/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�command_other_function_user_manage.h
		�ļ����ã����а���һЩ���û���ɫ�������������õĺ���
*/

#ifndef COMMAND_OTHER_FUNCTION_USER_MANAGE
#define COMMAND_OTHER_FUNCTION_USER_MANAGE

#include"data_structure_struct.h"

#include"role.h"

#include"hero.h"

#include"hero_configuration.h"

int checkOut(UserInform &user);      	//��ע���û��ĺϷ��Խ��м��

char* getLocalTime(char *time_string);

bool send_msg(int fd, string &msg_body);

Hero* create_hero(char *nickname);		//����Hero����
#endif
