/****************************************************************
* Filename: mail_systerm_interface.h
* Authof:	Tory
* Date:		2012.9.17 
* Description: �ʼ�ϵͳͷ�ļ������ڹ����ʼ����ݵ��Զ���ṹ���ͣ�
			   �ʼ��ⲿ�ļ���ȡ�����ɣ��ʼ����ݵļ��غʹ�����ʵ��
*****************************************************************/
#ifndef MAIL_SYSTERM_INTERFACE_
#define MAIL_SYSTERM_INTERFACE_

#define MAIL_INFOR_CONTENT	2048		//�ʼ�����������󳤶�
#define MAIL_THEME_SIZE		50			//�ʼ�������󳤶ȣ�50�ֽ�
#define MAIL_CONTENT_SIZE	900			//�ı��ʼ����ݳ���,�ͻ��˿ɽ��ܳ���Ϊ444�ֽ�

#include <string>
#include <list>
#include "libev.h"
#include "wholeDefine.h"
using namespace std;


//�ı��ʼ����ʼ��������900���ֽڣ�290�����֣�,�ռ�����ǳ����16���ֽڣ�5�����ģ��������32���ֽڣ�10�����ģ����ṹ��Mail_Txt�ܼ�1040���ֽ�
typedef struct mail_txt
{
	char	mail_id[50];					//this mail_id is useless <tory>
	char	isRead;							//�Ƿ��Ѷ�(0:�ռ����ʼ��Ѷ���1���ռ����ʼ�δ����2�����ʼ�Ϊ���������ʼ�)
	char	nickName[50];					//�������ǳ�
	char 	theme[MAIL_THEME_SIZE];			//�ʼ�����
	char	content[MAIL_CONTENT_SIZE];		//�ʼ�����
	int     money;							//������Ǯ��
	int     gamegold;						//����Ԫ����Ŀ
	char	good1_id[15];					//�����ڵ�һ����Ʒ��Id
    int     good1_num;					 	//�����ڵ�һ����Ʒ����Ŀ
	char    good2_id[15];					//�����ڵڶ�����Ʒ��Id
	int     good2_num;						//�����ڵڶ�����Ʒ����Ŀ
	char    good3_id[15];					//�����ڵ�������Ʒ��Id
	int 	good3_num;						//�����ڵ�������Ʒ����Ŀ
	char	good4_id[15];					//�����ڵ��ļ���Ʒ��Id
	int		good4_num;						//�����ڵ��ļ���Ʒ����Ŀ
	mail_txt();
	mail_txt(char* _nickName, char* _theme, char* _content)
	{
		isRead = 1;			//Ĭ��Ϊδ��
		money = 0;			//Ĭ�Ͻ�ǮΪ0
		gamegold = 0;		//Ĭ�Ͻ��Ϊ0
				
		if((int)strlen(_nickName) < 50)		strncpy(nickName, _nickName, 50);
		else	memset(nickName, 0,50);
		if((int)strlen(_theme) < MAIL_THEME_SIZE-1)		strncpy(theme, _theme, MAIL_THEME_SIZE);
		else	memset(theme, 0, MAIL_THEME_SIZE);
		if((int)strlen(_content) < MAIL_CONTENT_SIZE-1)		strncpy(content, _content, MAIL_CONTENT_SIZE);
		else	memset(content, 0, MAIL_CONTENT_SIZE);
		
		good1_num = 0;
		good2_num = 0;
		good3_num = 0;
		good4_num = 0;	//��Ʒ��ĿΪ0
		memset(good1_id, 0,15);
		memset(good2_id, 0,15);
		memset(good3_id, 0,15);
		memset(good4_id, 0,15);
	}
}Mail_Txt;

//�ʼ�ϵͳ�������õ������ݽṹ�����ڴ洢���ⲿ�ļ��ж�ȡ���ʼ���Ϣ
typedef struct mail_infor
{
	int 	mail_time;					//�ʼ�������ʱ�䣬linuxʱ�䣻����4�ֽ����ʹ洢
	char 	identity[IDL];				//id
	int		data_type;					//�ʼ����ݵĲ������ͣ�0���յ����ʼ� 1�����͵��ʼ� 2��������Ϣ����
	char	data[MAIL_INFOR_CONTENT];	//�ʼ�����,��ֽ�2048
	mail_infor()
	{
		mail_time = 0;
		data_type = 0;
		memset(identity,'\0',sizeof(identity));
		memset(data, 0, MAIL_INFOR_CONTENT);
	}	
}Mail_Infor;


//�ʼ��б����ڴ��浽game server�еĽ�ɫ�ʼ��б�����
typedef struct mail_list
{
	int unhandle_message_size;				//δ������Ϣ��Ŀ
	Mail_Infor mail_unhandle_message[100];	//���ʼ���ʽ��ʾ��δ������Ϣ
	
	int mail_list_size;						//�յ����ı��ʼ���Ŀ
	Mail_Infor mail_txt_infor[100];			//��ɫ�ռ����ʼ�����	
	
	int mail_send_size;						//���͵��ı��ʼ���Ŀ
	Mail_Infor mail_send_infor[100];		//������
}Mail_list;

class MailSystermInterface
{
	public:
		static int createMailDir();
	
		static int load_mail_data(string heroId);		//����ɫID���ⲿ�ļ�������Ӧ���ʼ�������game server��,����ֵ��ʾ�ʼ�����Ŀ������-1��ʾ���ݴ���
	
		static int create_mail_data(string heroId, int data_type, int data_len, char* data);
		
		static int handle_mail_data(string heroId);		//�����ʼ����ݣ������ʼ�����ʽ
				
		static int add_mail_data(Hero* myHero, int data_type, int data_len, Mail_Txt* );	//�����߽�ɫ����ʼ���data_type 0���ռ���data_type 1������
};	

//���½ṹ������mail_systerm_test.cpp�в����ʼ�ϵͳ�ӿڣ�����Ϸ�����У��벻Ҫ���� Tory
typedef struct user_infor
{
	int 	id;
	char	name[16];
	user_infor(int _id, char* _name)
	{
		id = _id;
		strncpy(name, _name, 16);
	}
}User_Infor;

//����mail_systerm_test.cpp�в����ʼ�ϵͳ�ӿڣ���Ϸ������������� Tory
int show_mail_data(char* data, char *outfile);

void show_mail_infor(Mail_Infor &mail_infor);

void show_mail_list(Mail_list &mail_list);
#endif
