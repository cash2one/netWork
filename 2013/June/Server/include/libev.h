/*
* �ļ����ƣ�libev.h
* �ļ����ã�����IO����
*/
#ifndef LIBEV_H
#define LIBEV_H	
#include"my_timer.h"

using namespace std;

//��ÿ�����ӵ���Ϣ����ṹ�壬���ڱ�ʶ��װ�ز���������Ϣ
typedef struct _Message_Receive
{
	char	ip_str[16];					//fd��Ӧ��IP
	struct bufferevent*  io_watcher;	//io����
	unsigned char 	t;					//XOR key

    _Message_Receive()
    {
		memset(ip_str, 0, 16);
		io_watcher = NULL;
    }
}Message_Receive;


void run_loop(int port);

void closeConnect(int fd);

void event_cb(struct bufferevent *bev, short what, void *arg);

bool write_log(char* buffer);

bool con_recharge_server();//���ӳ�ֵ��������

bool con_cdkey_server();		//��ʼ��cdkey����������
#endif
