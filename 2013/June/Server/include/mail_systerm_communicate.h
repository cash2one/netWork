/*
* Filename: mail_systerm_communicate.h
* Authof:	Tory
* Date:		2012.9.17 
* Description: ���ڿͻ��˷��ʼ������ʼ���ɾ�ʼ��Ĺ���
*/
#ifndef MAIL_SYSTERM_COMMUNICATE_
#define MAIL_SYSTERM_COMMUNICATE_

#include <string>
#include <iostream>
#include "mail_systerm_interface.h"
using namespace std;

class MailSystermCommunicate
{
public:
	
	static void get_mail_txt_list(char* buffer);		//�ͻ����������ҳ���ȡ�ʼ��б���Ϣ
		
	static void get_mail_content(char* buffer);			//��ȡ�����ʼ�������
		
	static void send_mail(char* buffer);				//�����ʼ� evan add 2012.9.24
		
	static void info_mail_all(char* buffer);			//����ǰ��������ʼ������� evan add 2012.9.25
		
	static void mail_goods_receive(char *buffer);		//��������Ʒ�Ľ��� evan 2012.9.25	in mail_systerm_send.cpp		

};
#endif







