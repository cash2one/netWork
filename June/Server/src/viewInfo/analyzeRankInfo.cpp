/*************************************************

Copyright: xhm

Author:xhm

Date:2012-12-7 

Description:�ͻ��������������ݽ������֣�

**************************************************/
#include "analyzeRankInfo.h"
#include "rankInfoAsist.h"

extern int sock_fd;
extern Hero* pg_hero;
extern int g_msg_len;
extern map<string, Hero*> heroId_to_pHero;


/*��ȡ������Ϣ ��Ϣ�ĸ�ʽ--> 11��11��type	1�Ƹ�����
											2�����
											3ս������
											4ɱ¾����
											5��ɱ��������
											6��������
												    */
void getRankInfo(char* buffers)
{
	MSG_BEGIN(buffers,g_msg_len)
	MSG_INT(int type);										/*��ȡ���а������.*/	
	MSG_INT(int page);					//ҳ��
	
	cout<<"11,11,"<<type<<","<<page<<endl;
	int number=type*4+page;
	cout<<"number:"<<number<<endl;
	char *msg=getRankInfo(number);						
	if(msg != NULL)
	{
		send_msg(sock_fd,msg);
	}
}
