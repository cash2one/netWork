#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <map>
#include <time.h>
#include "my_time.h"

#include "mailSysterm.h"

#include "mail_systerm_interface.h"

//����δ�����¼�
#include "offline_unhandle_event.h"
using namespace std;

extern map<string, MailSysterm*> mail_map;	//tory add 

/** �ʼ����ݴ��·�� added by Tory**/
extern string mail_data_url_T;

// ����������ʱ���ȼ���ʼ������ļ����Ƿ����,�������򴴽���������-1���ɹ�����0
int MailSystermInterface::createMailDir()	
{
	if(access(mail_data_url_T.c_str(), F_OK) < 0)
	{
		if(mkdir(mail_data_url_T.c_str(), 0755) < 0)
		{
			cout<<"@@Tory mkdir error"<<endl;
			return -1;
		}
		cout<<"@@Tory createMailDir success:"<<mail_data_url_T<<endl;
		return 0;
	}
	return 0;
}	
/*
* author: 	Tory
* date	:	2012/9/17 
* ���������heroId ��ɫID
* ����ֵ��	int��ֵ����ʾ�ʼ�����Ŀ������-1��ʾ���ݴ���
* Description: ��ɫ����ʱ�����ⲿ�ļ������ʼ����ݣ�.bin�ļ�Ϊ��ɫ�������߷�����Ϊ�䱣����ʼ����ݣ�.bin.bak�ļ�Ϊ�������쳣�Ͽ������ݵ��ʼ����ݣ�
			   ���������쳣�Ͽ��󣬲���ʹ��ϵͳ�����ʼ��Ĺ��ܣ����򽫵����ʼ����ݶ�ʧ<tory> 2013.3.12
*/
int MailSystermInterface::load_mail_data(string heroId)
{
	FILE *in;
	string mail_data_url = mail_data_url_T;
	mail_data_url += "//"+heroId;
	mail_data_url += ".bin";
	
	bool need_rename = true;	//���ʼ������ⲿ�ļ��Ƿ������������ݣ�Ĭ��Ϊtrue
	MailSysterm* m_s = new MailSysterm();

	//��鵱ǰ�û��Ƿ���Ҫ��.bak�лָ��ʼ�����
	if(access(mail_data_url.c_str(), R_OK) < 0)
	{
		mail_data_url += ".bak";	//mail_data_url��Ϊ��.bak�ж�ȡ����
		if(access(mail_data_url.c_str(), R_OK) < 0)	
		{
			fprintf(stdout,"no mail_data to read\n", mail_data_url.c_str());
			mail_map.insert(map<string, MailSysterm*>::value_type(heroId, m_s));
			cout<<"@@Tory mail_map.size():"<<mail_map.size()<<endl;
			return 0;
		}	
		need_rename = false;
	}
	
	if((in = fopen(mail_data_url.c_str(), "r")) == NULL)
	{
		fprintf(stderr, "fopen file %s to read error!\n", mail_data_url.c_str());
		mail_map.insert(map<string, MailSysterm*>::value_type(heroId, m_s));
		cout<<"@@Tory mail_map.size():"<<mail_map.size()<<endl;
		return -1;
	}

	Mail_Infor mail_infor;
	while(fread((void*)&mail_infor, sizeof(Mail_Infor), 1, in) == 1)
	{
	//	show_mail_infor(mail_infor);
		m_s->load_mail_infor(mail_infor);
	}

	mail_map.insert(map<string, MailSysterm*>::value_type(heroId, m_s));
	
	if(fclose(in) != 0)
	{
		fprintf(stderr, "fclose file %s error!\n", mail_data_url.c_str());
		return -1;
	}
	
	if(need_rename == true)//�ʼ���������������
	{
		string mail_data_url_new = mail_data_url + ".bak";
		if(rename(mail_data_url.c_str(), mail_data_url_new.c_str()) < 0 )
		{
			fprintf(stderr, "rename file %s error!\n", mail_data_url.c_str());
			return -1;
		}
	}	
}

/*
* author: 	Tory
* date	:	2012/9/18 
* ���������heroId, data_type:�������� data_len:���ݴ�С��С��2048�� data:��������������
* ����ֵ��	int����ֵ����ʾ�ʼ�����Ŀ������-1��ʾ���ݴ���
* Description: ����ɫID���ⲿ�ļ�д���ʼ����ݣ���������ݴ�С������2048�ֽ�
*/
int MailSystermInterface::create_mail_data(string heroId, int data_type, int data_len, char* data)
{
	//����̫�󣬴洢���ɹ�
	if(data_len > MAIL_INFOR_CONTENT)
	{
		fprintf(stderr, "data_len error\n");
		return -1;
	}
	
	string mail_data_url = mail_data_url_T;
	mail_data_url += "//"+heroId;
	mail_data_url += ".bin";
	cout<<"mail_data_url:"<<mail_data_url<<endl;

	FILE *out;
	//����ļ����ڣ���׷��ģʽ�򿪣�������ļ������ڣ��򴴽�
	if((out = fopen(mail_data_url.c_str(), "ab+")) == NULL){
		fprintf(stderr, "fopen file %s to read error!\n", mail_data_url.c_str());
		return -1;
	}

	Mail_Infor mail_infor;
	mail_infor.mail_time = MY_TV_SEC;	//��¼ʱ��
	
	char* uuid = cid();		//must release by caller <tory>
	strncpy(mail_infor.identity, uuid, IDL + 1);	//����id
	free(uuid); 
		
	mail_infor.data_type = data_type;	//�ʼ���������
	memmove(mail_infor.data, data, MAIL_INFOR_CONTENT);
	
	// memmove(mail_infor.data, data, strlen(data));
	
	//size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
	if(fwrite((void*)&mail_infor, sizeof(Mail_Infor), 1, out) != 1)
	{
		fprintf(stderr, "fwrite data to mail_data error!\n", mail_data_url.c_str());
		return -1;	
	}

	if(fclose(out) != 0)
	{
		fprintf(stderr, "fclose file %s error!\n", mail_data_url.c_str());
		return -1;
	} 
	

}

/*
* author: 	Tory
* date	:	2012/9/18 
* ���������heroId, data_type:�ʼ��������ͣ�data_type 0���ռ���data_type 1������ data_len:���ݴ�С��С��2048�� data:��������
* ����ֵ��	int����ֵ����ʾ�ʼ�����Ŀ������-1��ʾ���ݴ���
* describe: �����߽�ɫ��MailSysterm����ʼ���data_type 0���ռ���data_type 1��������ͬʱ���ʼ�����д��.bak�ļ�����ֹ����������Ͽ������������µ��ʼ�������.bin��
* 
*/
int MailSystermInterface::add_mail_data(Hero* myHero, int data_type, int data_len, Mail_Txt* m_t)
{
	//����̫�󣬴洢���ɹ�
	if(data_len > MAIL_INFOR_CONTENT || myHero == NULL)
	{
		fprintf(stderr, "data_len error or myHero is NULL\n");
		return -1;
	}
	
	string heroId = myHero->getIdentity();
	map<string, MailSysterm*>::iterator iter = mail_map.find(heroId);
	if(iter == mail_map.end())	
	{
		fprintf(stderr, "data_len error\n");
		return -1;
	}
	MailSysterm* m_s = iter->second;
	
	Mail_Infor mail_infor;
	mail_infor.mail_time = MY_TV_SEC;	//��¼ʱ��
	
	char* uuid = cid();		//must release by caller <tory>
	strncpy(mail_infor.identity, uuid, IDL+1);	//����Mail_Infor id
	free(uuid); 
		
	mail_infor.data_type = data_type;	//�ʼ��������ͣ�data_type 0���ռ���data_type 1������
	memmove(mail_infor.data, (void*)m_t, data_len);
	
	/* �Ƚ��µ��ʼ����ݼ��ؽ�game_server���̵��ڴ� */
	if(!m_s->load_mail_infor(mail_infor))	
	{
		fprintf(stderr, "load_mail_infor error\n");
		return -1;
	}	
	// fprintf(stderr, "load_mail_infor to game_server success\n");
	
	/* �ٴ��ⲿ�ļ������µ��ʼ�����д������.bakΪ��׺���ⲿ�ļ��У���ֹ����������Ͽ��������µ�game_server�е��ʼ���ʧ  2013.3.12 tory*/
	string mail_data_url = mail_data_url_T;
	mail_data_url += "//" + heroId;
	mail_data_url += ".bin.bak";
	cout<<"mail_data_url:"<<mail_data_url<<endl;

	FILE *out;
	//����ļ����ڣ���׷��ģʽ�򿪣�������ļ������ڣ��򴴽�
	if((out = fopen(mail_data_url.c_str(), "ab+")) == NULL){
		fprintf(stderr, "fopen file %s to read error!\n", mail_data_url.c_str());
		return -1;
	}
		
	//size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
	if(fwrite((void*)&mail_infor, sizeof(Mail_Infor), 1, out) != 1)
	{
		fprintf(stderr, "fwrite data to mail_data error!\n", mail_data_url.c_str());
		return -1;	
	}

	if(fclose(out) != 0)
	{
		fprintf(stderr, "fclose file %s error!\n", mail_data_url.c_str());
		return -1;
	}
	
	
	/*�����߽�ɫ���ռ���������ʼ��ɹ����ұ������ⲿ�ļ��ɹ������µ��ʼ���17,5���͸��ռ��� */
 	if(data_type == 0)
	{
		time_t seconds = mail_infor.mail_time;//�ʼ�������ʱ��
		struct tm *tmp = localtime(&seconds);	
			
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d", 17, 5, 1);
		sprintf(g_out_buf+strlen(g_out_buf),",%s,%s,%s,%02d-%02d", mail_infor.identity, m_t->nickName,m_t->theme,tmp->tm_mon + 1,tmp->tm_mday);
		cout<<"@@Tory 100000 recevier message:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
	}
	/*���Լ��ķ���������ʼ��ɹ����ұ������ⲿ�ļ��ɹ������ռ�����ʼ���17,3,1���ظ��Լ� */
	if(data_type == 1)
	{
		time_t seconds = mail_infor.mail_time;//�ʼ�������ʱ��
		struct tm *tmp = localtime(&seconds);	
			
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d", 17, 3, 1);
		sprintf(g_out_buf+strlen(g_out_buf),",%s,%s,%s,%02d-%02d", mail_infor.identity, m_t->nickName,m_t->theme,tmp->tm_mon + 1,tmp->tm_mday);
		cout<<"@@Tory 200000 recevier message:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
	}
	return 0;	

}

/*
* author: 	Tory
* date	:	2012/9/18 
* @@heroId: ��ɫID
* ����ֵ��	������-1���ɹ�����0
* Description: ����ɫID��game server��mail_map�л�ø����ʼ����ݣ������ɫ�����ڼ��ܵ����ʼ�
*/
int MailSystermInterface::handle_mail_data(string heroId)		
{
	map<string, MailSysterm*>::iterator iter = mail_map.find(heroId);
	if(iter == mail_map.end())
		return -1;
	
	MailSysterm* m_s = iter->second;
	m_s->mail_handle(heroId);

}

//���������������ڲ����ʼ����� Tory
void show_mail_infor(Mail_Infor &mail_infor)
{
	//��ʱ�䣨�룩ת���ɱ��ظ�ʽ���磺2012-09-22 15:22:17
	time_t seconds =  mail_infor.mail_time;
	struct tm *tmp = localtime(&seconds);	
//	printf("%d-%02d-%02d %02d:%02d:%02d\n",	tmp->tm_year + 1900, tmp->tm_mon + 1,tmp->tm_mday,tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
	char url[50] = {0};
	sprintf(url,"mail%d_%d_%d.txt",tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
//	printf("mail_infor.data_type:%d\n", mail_infor.data_type);
//	printf("mail_infor.data:%s\n", mail_infor.data);
	show_mail_data(mail_infor.data, url);
}

int show_mail_data(char* data, char *outfile)
{
	FILE *out;
	if((out = fopen(outfile, "w+")) == NULL){
		fprintf(stderr, "fopen file %s error!\n", outfile);
		return -1;
	//	exit(EXIT_FAILURE);
	}
 	fprintf(out, "test HeroData isRead:%d\n", ((Mail_Txt*)data)->isRead);
	fprintf(out, "test HeroData nickName:%s\n", ((Mail_Txt*)data)->nickName);
	fprintf(out, "test HeroData theme:%s\n", ((Mail_Txt*)data)->theme);
	fprintf(out, "test HeroData content:%s\n", ((Mail_Txt*)data)->content);fprintf(out, "test HeroData money:%d\n", ((Mail_Txt*)data)->money);fprintf(out, "test HeroData gamegold:%d\n", ((Mail_Txt*)data)->gamegold);
	fprintf(out, "test HeroData good1_id:%s\n", ((Mail_Txt*)data)->good1_id);
	fprintf(out, "test HeroData good1_num:%d\n", ((Mail_Txt*)data)->good1_num);
	fprintf(out, "test HeroData good2_id:%s\n", ((Mail_Txt*)data)->good2_id);
	fprintf(out, "test HeroData good2_num:%d\n", ((Mail_Txt*)data)->good2_num);
	fprintf(out, "test HeroData good3_id:%s\n", ((Mail_Txt*)data)->good3_id);
	fprintf(out, "test HeroData good3_num:%d\n", ((Mail_Txt*)data)->good3_num);
	fprintf(out, "test HeroData good4_id:%s\n", ((Mail_Txt*)data)->good4_id);
	fprintf(out, "test HeroData good4_num:%d\n", ((Mail_Txt*)data)->good4_num);		

	if(fclose(out) != 0){
		fprintf(stderr, "fclose file error!\n");
		return -1;	
	//	exit(EXIT_FAILURE);
	} 	

	return 0;

}
