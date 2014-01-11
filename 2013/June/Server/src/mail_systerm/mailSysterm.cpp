#include <iostream>
#include <stdlib.h>
#include "mailSysterm.h"
//����δ�����¼�
#include "offline_unhandle_event.h"
#include "money_operator.h"
using namespace std;
/** �ʼ����ݴ��·�� added by Tory**/
extern string mail_data_url_T;

extern int g_msg_len;
extern Hero* pg_hero;
extern char g_out_buf[20480];

MailSysterm::MailSysterm()
{
	new_mail = 0;		//tory add 2013.1.7
}

bool MailSysterm::load_mail_infor(Mail_Infor& mail_i)	//�������ʼ����ص�MailSysterm�����й���
{
 	Mail_Infor* m_i = (Mail_Infor*)malloc(sizeof(Mail_Infor));	//��MailSysterm����������free��
	if(m_i == NULL)	return false;
	memmove(m_i, &mail_i, sizeof(Mail_Infor));
	
	string key = m_i->identity;
	//����Mail_Infor�е�data_type�����ʼ��Ĵ洢���ͣ�0���յ����ʼ� 1�����͵��ʼ� 2��������Ϣ����
 	if(m_i->data_type == 0)
	{
		mail_Inbox.insert(map<string, Mail_Infor*>::value_type(key, m_i));
		cout<<"@@Tory MailSysterm::mail_Inbox.size():"<<mail_Inbox.size()<<endl;
	}else if(m_i->data_type == 1)
	{
		mail_Outbox.insert(map<string, Mail_Infor*>::value_type(key, m_i));
		cout<<"@@Tory MailSysterm::mail_Outbox.size():"<<mail_Outbox.size()<<endl;
	}else
	{
		mail_Unhandlebox.insert(map<string, Mail_Infor*>::value_type(key, m_i));
		cout<<"@@Tory MailSysterm::mail_Unhandlebox.size():"<<mail_Unhandlebox.size()<<endl;
	}
	
	Mail_Txt* m_t = (Mail_Txt*)m_i->data;		//tory modify 2013.1.7
	if(m_t->isRead == 1)		//isRead 0:�ռ����ʼ��Ѷ���1���ռ����ʼ�δ��
	{
		new_mail += 1;
	}
	return true;
}

MailSysterm::~MailSysterm()		//��ɫ����ʱ������ɫ��Ӧ���ʼ������ͷŵ�
{
	cout<<"~MailSysterm start"<<endl;
	map<string, Mail_Infor*>::iterator iter_i = mail_Inbox.begin();	//�ռ���
	for(iter_i; iter_i != mail_Inbox.end(); iter_i++)
	{
		Mail_Infor* m_i = iter_i->second;
		if(m_i != NULL)	;
		{
			free(m_i);
		}
	}
	cout<<"free mail_Inbox "<<endl;
	
	map<string, Mail_Infor*>::iterator iter_o = mail_Outbox.begin();	//������
	for(iter_o; iter_o != mail_Outbox.end(); iter_o++)
	{
		Mail_Infor* m_i = iter_o->second;
		if(m_i != NULL)	;
		{
			free(m_i);
		}
	}
	cout<<"free mail_Outbox "<<endl;
	
	map<string, Mail_Infor*>::iterator iter_u = mail_Unhandlebox.begin();	//����ʱ�ܵ�����Ϣ
	for(iter_u; iter_u != mail_Unhandlebox.end(); iter_u++)
	{
		Mail_Infor* m_i = iter_u->second;
		if(m_i != NULL)	;
		{
			free(m_i);
		}
	}
	cout<<"free mail_Unhandlebox "<<endl;
	cout<<"~MailSysterm end"<<endl;
}

void MailSysterm::mail_handle(string heroId)		//�����ʼ�����
{
 	map<string, Mail_Infor*>::iterator iter = mail_Unhandlebox.begin();	//����δ������Ϣ
	for(iter; iter != mail_Unhandlebox.end(); iter++)
	{
		Mail_Infor* mail_infor = iter->second;
		//��data_type�����ʼ����ݵĴ���ʽ,������д��mail_systerm_handle.h��
		cout<<"mail_infor->data_type:"<<mail_infor->data_type<<endl;
		switch(mail_infor->data_type)			
		{
			case 2:
					printf("in parse_mail_data, case 0:%s\n", mail_infor->data);
					break;
			case 3:
					break;
		
			case 5:	
					deal_unhandle_attr_event(const_cast<char*>(heroId.c_str()), mail_infor->data);
					break;
					
			case 6: 
					deal_unhandle_goods_event(const_cast<char*>(heroId.c_str()), mail_infor->data);
					break;
					
			case 7: 
					deal_unhandle_msg_event(const_cast<char*>(heroId.c_str()), mail_infor->data);
					break;
					
			case 8: 
					deal_unhandle_join_guild_event(const_cast<char*>(heroId.c_str()), mail_infor->data);
					break;
			case 9:	
					// printf("in parse_mail_data, case 9\n");			//�������� ������9
					deal_unhandle_friend_apply_event(heroId, mail_infor->data);
					break;
			case 10:	
					// printf("in parse_mail_data, case 10\n");		//����ɾ�� ������10
					deal_unhandle_del_friend_event(heroId,mail_infor->data);			
					break;
			case 11:	
					// printf("in parse_mail_data, case 11\n");		//������� ������11
					deal_unhandle_add_friend_event(heroId,mail_infor->data);	
					break;			
			default:
					break;

		}
	} 

}

bool time_compare(const Mail_Infor *first, const Mail_Infor *second)
{
	if(first->mail_time > second->mail_time)
		 return true; 
	else 
		return false;
}

bool MailSysterm::get_mail_list(Hero* myHero, int type)	
{
	if(myHero == NULL)	return false;
	//��ȡ�ռ����б���Ϣ //17,0
	if(type == 0)	
	{
		list<Mail_Infor*> inbox_list;
	 	map<string, Mail_Infor*>::iterator iter = mail_Inbox.begin();	//�ռ���
		for(iter; iter != mail_Inbox.end(); iter++)
		{
			inbox_list.push_back(iter->second);
		}
		//���ʼ��б�ʱ���Ⱥ�˳������(ʱ��ֵ�ɴ�С)���Զ���������compare
		inbox_list.sort(time_compare);
		
		int mail_number = inbox_list.size();
		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 0, type, mail_number);
		
		int index = 0;
		list<Mail_Infor*>::iterator iter_l = inbox_list.begin();
		for(iter_l; iter_l != inbox_list.end(), index < mail_number; iter_l++, index++)
		{
			Mail_Infor* m_i = *iter_l;
			if(m_i == NULL)	return false;
			
			Mail_Txt* mail_text = (Mail_Txt*)m_i->data;	//tory modify 2012.12.29
		//	Mail_Txt* mail_text = (Mail_Txt*)malloc(sizeof(Mail_Txt));		//�ʼ��ı�����
		//	memmove(mail_text, m_i->data, sizeof(Mail_Txt));
			
			time_t seconds =  m_i->mail_time;//�ʼ�������ʱ��
			struct tm *tmp = localtime(&seconds);	
			char time_temp[50] = {0}; 
			sprintf(time_temp, "%02d-%02d",tmp->tm_mon + 1,tmp->tm_mday);			//���ʼ�ʱ��ת��Ϊ�ַ�����
			
			sprintf(g_out_buf+strlen(g_out_buf), ",%d,%s,%s,%s,%d,%s", index, m_i->identity, mail_text->nickName, time_temp, mail_text->isRead, mail_text->theme);
		//	free(mail_text);
		}
		cout<<"@@Tory get_mail_list:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
		return true;
	}else if(type == 1)
	{
		list<Mail_Infor*> outbox_list;
	 	map<string, Mail_Infor*>::iterator iter = mail_Outbox.begin();	//������
		for(iter; iter != mail_Outbox.end(); iter++)
		{
			outbox_list.push_back(iter->second);
		}
		//���ʼ��б�ʱ���Ⱥ�˳������(ʱ��ֵ�ɴ�С)���Զ���������compare
		outbox_list.sort(time_compare);
		
		int mail_number = outbox_list.size();
		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 0, type, mail_number);
		
		int index = 0;
		list<Mail_Infor*>::iterator iter_l = outbox_list.begin();
		for(iter_l; iter_l != outbox_list.end(), index < mail_number; iter_l++, index++)
		{
			Mail_Infor* m_i = *iter_l;
			if(m_i == NULL)	return false;
			
			Mail_Txt* mail_text = (Mail_Txt*)m_i->data;	//tory modify 2012.12.29
		//	Mail_Txt* mail_text = (Mail_Txt*)malloc(sizeof(Mail_Txt));		//�ʼ��ı�����
		//	memmove(mail_text, m_i->data, sizeof(Mail_Txt));
			
			time_t seconds =  m_i->mail_time;//�ʼ�������ʱ��
			struct tm *tmp = localtime(&seconds);	
			char time_temp[50] = {0}; 
			sprintf(time_temp, "%02d-%02d",tmp->tm_mon + 1,tmp->tm_mday);			//���ʼ�ʱ��ת��Ϊ�ַ�����
			
			sprintf(g_out_buf+strlen(g_out_buf), ",%d,%s,%s,%s,%d,%s", index, m_i->identity, mail_text->nickName, time_temp, mail_text->isRead, mail_text->theme);
		//	free(mail_text);
		}
		cout<<"@@Tory get_mail_list:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
		return true;
	}
}

bool MailSysterm::get_mail_content(Hero* myHero, int type, string mail_id)	
{
	if(myHero == NULL)	return false;
	//��ȡ�ռ����б���Ϣ //17,1
	if(type == 0)	
	{//�ռ����ʼ�
		map<string, Mail_Infor*>::iterator iter = mail_Inbox.find(mail_id);
		if(iter == mail_Inbox.end())	return false;	
		
		Mail_Infor* m_i = iter->second;
		if(m_i == NULL)	return false;
			
		Mail_Txt* mail_text = (Mail_Txt*)m_i->data;	//tory modify 2012.12.29
	//	Mail_Txt* mail_text = (Mail_Txt*)malloc(sizeof(Mail_Txt));
	//	memmove(mail_text, m_i->data, sizeof(Mail_Txt));
		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 1, type, 1);
		sprintf(g_out_buf+strlen(g_out_buf),",%s,%s,%s,%s,%d,%d,%s,%d,%s,%d,%s,%d,%s,%d", m_i->identity,mail_text->nickName,mail_text->theme,\
												mail_text->content,\
												mail_text->money,mail_text->gamegold,\
												mail_text->good1_id, mail_text->good1_num,\
												mail_text->good2_id, mail_text->good2_num,\
												mail_text->good3_id, mail_text->good3_num,\
												mail_text->good4_id, mail_text->good4_num);
		
		mail_text->isRead = 0;		//��Ϊ���Ķ�
	//	free(mail_text);
		cout<<"@@Tory get_mail_content:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
		return true;
	}else if(type == 1)
	{
		map<string, Mail_Infor*>::iterator iter = mail_Outbox.find(mail_id);
		if(iter == mail_Outbox.end())	return false;	
		
		Mail_Infor* m_i = iter->second;
		if(m_i == NULL)	return false;
			
		Mail_Txt* mail_text = (Mail_Txt*)m_i->data;		//tory modify 2012.12.29
		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 1, type, 1);
		sprintf(g_out_buf+strlen(g_out_buf),",%s,%s,%s,%s,%d,%d,%s,%d,%s,%d,%s,%d,%s,%d", m_i->identity,mail_text->nickName,mail_text->theme,\
												mail_text->content,\
												mail_text->money,mail_text->gamegold,\
												mail_text->good1_id, mail_text->good1_num,\
												mail_text->good2_id, mail_text->good2_num,\
												mail_text->good3_id, mail_text->good3_num,\
												mail_text->good4_id, mail_text->good4_num);
		
		mail_text->isRead = 0;		//��Ϊ���Ķ�
		cout<<"@@Tory get_mail_content:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
		return true;
	}
}
	
bool MailSysterm::delet_mail_infor(int type, string mail_id)//ɾ���ʼ�����
{

}


bool MailSysterm::save_mail_data(string heroId)	//��ɫ����ʱ�������ʼ�����
{
	string mail_data_url = mail_data_url_T;
	mail_data_url += "//"+heroId;
	mail_data_url += ".bin";
	cout<<"mail_data_url:"<<mail_data_url<<endl;

	FILE *out;
	// if((out = fopen(mail_data_url.c_str(), "wb")) == NULL){
	if((out = fopen(mail_data_url.c_str(), "ab+")) == NULL){	//��׷��ģʽ���ʼ��ļ�����ֹ��;ϵͳ���û������ʼ�������
		fprintf(stderr, "fopen file %s to append write error!\n", mail_data_url.c_str());
		return -1;
	}

	map<string, Mail_Infor*>::iterator iter_i = mail_Inbox.begin();	//�ռ���
	for(iter_i; iter_i != mail_Inbox.end(); iter_i++)
	{
		Mail_Infor* m_i = iter_i->second;
		if(m_i == NULL)	continue;
		
		//size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
		if(fwrite((void*)m_i, sizeof(Mail_Infor), 1, out) != 1)
		{
			fprintf(stderr, "fwrite data to mail_data error!\n", mail_data_url.c_str());
			return false;	
		}
	}
	
	map<string, Mail_Infor*>::iterator iter_o = mail_Outbox.begin();	//������
	for(iter_o; iter_o != mail_Outbox.end(); iter_o++)
	{
		Mail_Infor* m_i = iter_o->second;
		if(m_i == NULL)	continue;
		
		//size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
		if(fwrite((void*)m_i, sizeof(Mail_Infor), 1, out) != 1)
		{
			fprintf(stderr, "fwrite data to mail_data error!\n", mail_data_url.c_str());
			return false;	
		}
	}	
	
	if(fclose(out) != 0)
	{
		fprintf(stderr, "fclose file %s error!\n", mail_data_url.c_str());
		return false;
	} 
	return true;

}

/* 
* author: tory
* date: 2012.12.29
* describe:�����ʼ�ϵͳ�У���/��������ʼ���Ŀ
*/
bool MailSysterm::getMailListNum(Hero* myHero)
{
	if(myHero == NULL)	return false;
	
	int in_num = mail_Inbox.size();
	int out_num = mail_Outbox.size();
	
	memset(g_out_buf, 0, 20480);	
	sprintf(g_out_buf, "%d,%d,%d,%d,%d", 17, 4, in_num, out_num, new_mail);
	cout<<"@@Tory: getMailListNum:"<<g_out_buf<<endl;
	send_msg(myHero->getFd(), g_out_buf);

	return true;	
}

/* 
* author: tory
* date: 2012.12.29
* describe:��ȡ�ʼ��е���Ʒ
*/
bool MailSysterm::mail_goods_receive(Hero* myHero, string mail_id)
{
	if(myHero == NULL)	return false;
	map<string, Mail_Infor*>::iterator iter = mail_Inbox.find(mail_id);
	if(iter == mail_Inbox.end())	return false;	
		
	Mail_Infor* m_i = iter->second;
	if(m_i == NULL)	return false;
			
	Mail_Txt* m_t = (Mail_Txt*)m_i->data;		//tory modify 2012.12.29
	
	if(mail_id.compare(m_i->identity) != 0)
	{
		cout<<"mail_goods_receivep��the mail id is not same"<<endl;
		return false;
	}

	int all_number = m_t->good1_num + m_t->good2_num + m_t->good3_num + m_t->good4_num;
	
	//jolly add 1.25  for bagfull
	int count=0;
	if (m_t->good1_num!=0)
	{
		count++;
	}
	if (m_t->good2_num!=0)
	{
		count++;
	}
	if (m_t->good3_num!=0)
	{
		count++;
	}
	if (m_t->good4_num!=0)
	{
		count++;
	}
	
	if(myHero->getBag()->bagIsFull(count))
	{//�����ڸ���������
		cout<<"mail_goods_receivep��the bag is not null"<<endl;
		return false;
	} 
	
	//����Ʒ���ڵ�������
	if(m_t->good1_num > 0)
	{
		saveGoodsInBag(myHero, m_t->good1_id, m_t->good1_num);	
		strncpy(m_t->good1_id, "0", 15);
		m_t->good1_num = 0;
	}
	if(m_t->good2_num > 0)
	{
		saveGoodsInBag(myHero, m_t->good2_id, m_t->good2_num);	
		strncpy(m_t->good2_id, "0", 15);
		m_t->good2_num = 0;
	}
	if(m_t->good3_num > 0)
	{
		saveGoodsInBag(myHero, m_t->good3_id, m_t->good3_num);	
		strncpy(m_t->good3_id, "0", 15);
		m_t->good3_num = 0;
	}
	if(m_t->good4_num > 0)
	{
		saveGoodsInBag(myHero, m_t->good4_id, m_t->good4_num);	
		strncpy(m_t->good4_id, "0", 15);
		m_t->good4_num = 0;
	}	
	
	//����Ϸ����ǰ�Ԫ�����ص�������
	increaseGameMoney(myHero, m_t->money);
	m_t->money = 0;
	
	increaseGold(myHero, m_t->gamegold);	
	m_t->gamegold = 0;
	
	int index = 0;
	memset(g_out_buf, 0, 20480);	
	sprintf(g_out_buf, "17,6,1,%d,%s", index, mail_id.c_str());
	cout<<"@@Tory, mail_goods_receive:"<<g_out_buf<<endl;
	send_msg(myHero->getFd(), g_out_buf);
}