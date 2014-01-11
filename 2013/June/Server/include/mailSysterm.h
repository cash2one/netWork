/*
* Authof:	Tory
* Date:		2012.12.19 
* Description: �ʼ�ϵͳ	,		   
*/
#ifndef _MAIL_SYS_H
#define _MAIL_SYS_H

#include "mail_systerm_interface.h"
#include <list>
using namespace std;
class MailSysterm
{
private:
	map<string, Mail_Infor*> 	mail_Inbox;		//�ռ���
	map<string, Mail_Infor*> 	mail_Outbox;	//������	
	map<string, Mail_Infor*> 	mail_Unhandlebox;	//����δ������Ϣ
	int new_mail;		//���ʼ�����
public:
	MailSysterm();
	~MailSysterm();		//��ɫ����ʱ������ɫ��Ӧ���ʼ������ͷŵ�
	
	bool load_mail_infor(Mail_Infor& mail_infor);	//�������ʼ��ⲿ���ݼ��ص�MailSysterm�����й���
	void load_mail_list(Mail_list& mail_list);		//��������ɫ���ʼ�����ȫ�����ص�MailSysterm�����й���
	void mail_handle(string);	//�����ʼ�����
	bool delet_mail_infor(int type, string mail_id);//ɾ���ʼ�����
	bool save_mail_data(string heroId);	//��ɫ����ʱ�������ʼ�����
	
	bool get_mail_list(Hero* myHero, int type);
	bool get_mail_content(Hero* myHero, int type, string mail_id);
	
	bool getMailListNum(Hero* myHero); //describe:�����ʼ�ϵͳ�У���/��������ʼ���Ŀ
	bool mail_goods_receive(Hero* myHero, string mail_id);
};

bool time_compare(const Mail_Infor* first, const Mail_Infor* second); //�Զ���list�ȽϺ���������list����Ƚ�
#endif
