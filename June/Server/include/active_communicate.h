/*
		�ļ����ͣ�ʵ���ļ�
		�ļ����ƣ�active_communicate.h"
		�ļ����ã���ͻ��˺ͷ�����������������
		�޸��ˣ�chenzhen
		�޸�ʱ�䣺2012.10.24
*/
#ifndef ACTIVE_COMMIMUCATION_H
#define ACTIVE_COMMIMUCATION_H
void activeAccept(char *buffers);
void takePartActive(char *buffers);

/*������Ľ���*/
void acceptActiveCode(char *buffers);

//������cdkey Server���ص���Ϣ
void acceptCdkeySrvSuccess(char *buffer);

//������cdkey Server���ص���Ϣ
void acceptCdkeySrv(char *buffer);

#endif