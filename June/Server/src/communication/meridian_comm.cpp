/****************************************************************
 * Filename: meridian_comm.cpp
 * 
 * Description: ����ϵͳģ����ͻ��˵�ͨ��
 *
 * Original Author : bison, 2012-7-16
 *
 ****************************************************************/
 
#include "command_return_define_data.h"
#include "role.h"
#include "meridian_asist.h"
#include"timerExpireList.h"
#include <arpa/inet.h>
#include"wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;

extern map<string, Hero*> heroId_to_pHero;
extern int sock_fd;
extern struct ev_loop *loops;

//�ͻ�����������Ϣ
void  applyMeridInfoComm(char *buffer);

//���Ҫ���ǰ������д
//��ʼ��������ͨ��
void  startMeridComm(char *buffer)
{
	char msg[160];
	// string msg_head = "8";					//����ͷ8,3
	// msg = msg + msg_head + intTostring(START_MERID_RETURN);
	int index;								//��������
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(index);
	Hero *hero = pg_hero;
	
	//�����Ƿ�ɹ�
	char result[32] = {0};
	int ret = startMeridStudy(hero, index, result);
	if (ret == 0)
	{
		// msg = msg + intTostring(SUCCESS); 
		// msg += temp;
		sprintf(msg, "8,3,1%s", result);
		send_msg(sock_fd, msg);
		return ;
	} else {
		sprintf(msg, "8,3,0,%d", ret);
		// msg = msg + intTostring(FAILED); 
		send_msg(sock_fd, msg);
		return ;
	}
	
}

//����ǿ��
void strenMeridComm(char *buffer)
{
	char msg[160];
	// string msg_head = "8";					//����ͷ8,4
	// msg = msg + msg_head + intTostring(STREN_MERID_RETURN);
	
	//��fd��heroʵ��
	Hero *hero = pg_hero;
	
	//ǿ���Ƿ�ɹ�
	char result[32];
	int temp = strenMerid(hero, result);
	if (temp == 0)
	{
		// msg = msg + intTostring(SUCCESS); 
		// msg += temp;
		sprintf(msg, "8,4,1,%s", result);
		send_msg(sock_fd, msg);
		return ;
	} else {
		
		// msg = msg + intTostring(FAILED); 
		sprintf(msg, "8,4,0");
		send_msg(sock_fd, msg);
		return ;
	}
	
}

void decMeridTimeComm(char *buffer)
{
	char msg[160] = {0};
	char msg1[160] = {0};
	int flag;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(flag);
	int temp = decMeridTimeWithGold(pg_hero, flag, msg1);
	if (temp == 0)
	{
		// applyMeridInfoComm(msg1);
		sprintf(msg, "8,3,1%s", msg1);
		send_msg(sock_fd, msg);
	}
	else
	{
		sprintf(msg, "8,3,0,%d", temp);
		send_msg(sock_fd, msg);
	}
}

//���е�����������ʱ��
void useGoodsMeridComm(char *buffer)
{
	char msg[160];
	// string msg_head = "8";					//����ͷ8,15
	// msg = msg + msg_head + intTostring(USE_MERID_RETURN);
	int index;								//�����ڱ������±�
	int num;								//ʹ�õ�����
	char *goodsId;							//��ƷId
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(index);
	MSG_INT(num);
	MSG_CHAR_END(goodsId);
	Hero *hero = pg_hero;
	
	cout<<"useMeridianGoods id is "<<goodsId<<endl;
	
	// string tempGoodsId = goodsId;
	if (strcmp(goodsId, "f_cl_116_100") && strcmp(goodsId, "b_cl_116_100"))
	{
		// cout<<"The hero use the error goods to reduce meridianTime ! the need id is f/b_cl_116_100 and the give id is "<<tempGoodsId<<endl;
		return;
	}
	
	//ʹ�õ����Ƿ�ɹ�
	int temp = useMeridGoods(hero, goodsId, index, num, msg);
	if (temp == 0)
	{
		char p[2] = "a";
		applyMeridInfoComm(p);
		// msg = msg + intTostring(SUCCESS); 
		// msg += temp;
		// send_msg(sock_fd, msg);
	} else {
		
		// msg = msg + intTostring(FAILED); 
		// send_msg(hero->getFd(),msg);
	}
	
}

//�ͻ�����������Ϣ
void  applyMeridInfoComm(char *buffer)
{
	char msg[64];
	// string msg_head = "8";					//����ͷ8,2
	// msg = msg + msg_head + intTostring(APPLY_MERID_INFO_RETURN);

	//�ͻ��˲�����ɫID��
	//��fd��heroʵ��
	Hero *hero = pg_hero;
	
	Meridian *merid = hero->getMerid();
	if (merid == NULL)
	{
		cout<<"[BisonWarn] how can it happen when he has no merid!"<<endl;
		return;
	}
	ev_timer* timer = merid->getTimer();
	MERID_TYPE_T now = merid->getNow();
	int level = merid->getLevel();
	int i;
	sprintf(msg, "8,2");
	for (i = 0; i <= now; i++)
	{
		// msg += intTostring(level);
		sprintf(msg + strlen(msg), ",%d", level);
	}
	for (i = now; i < 7; i++)
	{
		// msg += intTostring(level - 1);
		sprintf(msg + strlen(msg), ",%d", level - 1);
	}
	
	if (merid->getTimerBusy())
	{
		int remain = ev_timer_remaining(loops, timer);
		// msg += intTostring((now + 1) % 8);
		// msg += intTostring(remain);
		// msg += intTostring(((now == 7) ? level : level - 1));
		sprintf(msg + strlen(msg), ",%d,%d,%d", (now + 1) % 8, remain, ((now == 7) ? level : level - 1));
	}
	
	send_msg(sock_fd, msg);
	send_msg(sock_fd, "hello world!");
}
