/************************************************************
	�ļ�����asistFun.h
	�ļ����ã�������������
	���ߣ�chenzhen
	�������ڣ�2013.04.01
************************************************************/
#ifndef ASIST_FUN_H
#define ASIST_FUN_H

#include"numStr.h"

/*�ַ���Ϊ�մ���*/
const int ERROR_EMPTY = 1;

/*�ַ������з������ַ�����*/
const int ERROR_DIGST = 2;

/*�ַ������з������ַ�����*/
const int ERROR_OTHRE = 3;



/*���س˺�*/
const NumStr operator* (const NumStr& numStrF,const NumStr& numStrS);

/*����ײ㺯��*/
void loopFor(NumStr& numStr);

/*���ش��ڵ��ں�*/
bool operator >= (const NumStr &numStrL,const NumStr &numStrR);

/*����С�ں�*/
bool operator < (const NumStr &numStrL,const NumStr &numStrR);

/*��������*/
void errorDealFun(int errorType);

#endif
	
