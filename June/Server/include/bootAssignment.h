/******************************************
	�ļ����ͣ�ͷ�ļ�
	
	�ļ����ƣ�bootAssignment.h
	
	�ļ����ã��������������ó�ʼ��ȫ�ֱ���ֵ
*******************************************/
#ifndef BOOT_ASSIGNMENT_H
#define BOOT_ASSIGNMENT_H


#define MAX_REGISTER_SIZE 500000

typedef struct nickNameCheck_S{
	char nickName[MAX_REGISTER_SIZE][32];
	char HeroId[MAX_REGISTER_SIZE][38];
}NickNameCheck_T;

void nickNameCheckValueBootInit();

void saveNickNameCheckValue2Mem();

void updataNickNameCheckValue();

void saveDeleteNickNameValue();

#endif

