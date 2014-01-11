/****************************************************************
 * Filename: five_elem_comm.cpp
 * 
 * Description: ����ϵͳģ����ͻ��˵�ͨ��
 *
 * Original Author : bison, 2012-7-12
 *
 ****************************************************************/
#include "command_return_define_data.h"
#include "role.h"
#include "five_asist.h"
#include <arpa/inet.h>

#include"wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;

//����ת������ֵ
#define int2FiveElem(a) ((0 < (a) && (a) < 6) ? (FIVE_ELEMENT_T)(a) : NOELEM)

extern map<string, Hero*> heroId_to_pHero;
extern int sock_fd;
//��ȡ��������
void viewFiveElemComm(char *buffer);

//��������п�����ϵͳĬ�Ͽ�����ֻ��������������ѡ����
void openFiveElemComm(char *buffer)
{
	int elem;					//��������
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(elem);
	Hero *hero = pg_hero;
	
	char msg[64];
	//����ͷ8.8
	// string msg_head = "8";
	// msg = msg + msg_head + intTostring(OPEN_FIVE_ELEM_RETURN);
	
	if (openFiveElem(hero, int2FiveElem(elem), 20))
	{
		//�����ɹ�
		// msg = msg + intTostring(SUCCESS); 
		sprintf(msg, "8,%d,1", OPEN_FIVE_ELEM_RETURN);
		send_msg(sock_fd, msg);
		//FiveElem *fiveElement = hero->getFiveElem();
		
		viewFiveElemComm(NULL);
	} else {
		//����ʧ��
		// msg = msg + intTostring(FAILED); 
		sprintf(msg, "8,%d,0", OPEN_FIVE_ELEM_RETURN);
		send_msg(sock_fd, msg);
		
	}
	
}

//�����������Ե�ͨ��
void changFiveElemComm(char *buffer)
{
	int elem;					//��������
	int index;					//��Ҫ�����ĳ����ڳ������±꣬ Ϊ-1ʱ�Ƕ�hero����
	// int order;					//�����������Ե��ڱ����е��±�
	
	char msg[64];
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT_MAX(index, 20);
	MSG_INT(elem);
	// MSG_INT(order);
	Hero *hero = pg_hero;
	
	// string msg_head = "8";
	// msg = msg + msg_head + intTostring(CHANGE_FIVE_ELEM_RETURN);
	
	// if (changeFiveElem(hero, int2FiveElem(elem), index, order))
	int ret = changeFiveElemNew(hero, int2FiveElem(elem), index);
	if (ret == 0)
	{
		//�����������Գɹ�
		if (index == 20)
		{
			// msg = msg + intTostring(SUCCESS);
			sprintf(msg, "8,%d,1", CHANGE_FIVE_ELEM_RETURN);
			send_msg(hero->getFd(), msg);
			char p[] = "dd";
			viewFiveElemComm(p);
		}
	} else {
		//����ʧ��
		// msg = msg + intTostring(FAILED); 
		sprintf(msg, "8,%d,0,%d", CHANGE_FIVE_ELEM_RETURN, ret);
		send_msg(hero->getFd(),msg);
		
	}
	
}

//ʹ�����е�ҩ�������еȼ�
void useFiveElemGoodsComm(char *buffer)
{
	char len_arg;     			//��������
	int count = 6;
	int index;					//��Ҫ�����ĳ����ڳ������±꣬ Ϊ-1ʱ�Ƕ�hero����
	char *goodsId;				//���е�ID
	int order;					//���е��ڱ�����λ��
	int net;
	
	char msg[16];
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT_MAX(index, 20);
	MSG_CHAR(goodsId);
	MSG_INT_MAX(order, 95);
	Hero *hero = pg_hero;
	
	//����ͷ3,12
	// string msg_head = "3";
	// msg = msg + msg_head + intTostring(USE_FIVE_ELEM_RETURN);
	
	if (useFiveElemGoods(hero, goodsId, order, index))
	{
		//�����������Գɹ�
		// msg = msg + intTostring(SUCCESS); 
		// sprintf(msg,"3,12,1");
		// send_msg(hero->getFd(), msg);
		viewFiveElemComm(NULL);
		
	} else {
		//����ʧ��
		// msg = msg + intTostring(FAILED); 
		// sprintf(msg,"3,12,0");
		// send_msg(hero->getFd(), msg);
		
	}
	
}

//�������� ���� 
void viewFiveElemComm(char *buffer)
{
	Hero *hero = pg_hero;
	FiveElem *fiveElement = hero->getFiveElem();
	// string viewMsg = "8";
	char viewMsg[400];
	// viewMsg += intTostring(VIEW_FIVE_ELEM_INFO);
	if (fiveElement == NULL)
	{
		//��һ�û����������
		cout<<"BisonWarning: hero has no fiveElem when viewFive Elem!"<<endl;
		return;
	}
	
	if (fiveElement->getLevel() == 0)
	{
		// return;
	}
	
	// viewMsg += intTostring(fiveElement->getElem())
			 // + intTostring(fiveElement->getLevel())
			 // + intTostring(fiveElement->getExpNow())
			 // + intTostring(fiveElement->getExpForNext())
			 // + intTostring(fiveElement->getValue())
			 // + intTostring(fiveElement->getFactor(int2FiveElem(1)) * 100)
			 // + intTostring(fiveElement->getFactor(int2FiveElem(2)) * 100)
			 // + intTostring(fiveElement->getFactor(int2FiveElem(3)) * 100)
			 // + intTostring(fiveElement->getFactor(int2FiveElem(4)) * 100)
			 // + intTostring(fiveElement->getFactor(int2FiveElem(5)) * 100);
	sprintf(viewMsg, "8,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", VIEW_FIVE_ELEM_INFO, fiveElement->getElem(),
		fiveElement->getLevel(), fiveElement->getExpNow(), fiveElement->getExpForNext(), fiveElement->getValue(),
		int(fiveElement->getFactor(int2FiveElem(1)) * 100), int(fiveElement->getFactor(int2FiveElem(2)) * 100),
		int(fiveElement->getFactor(int2FiveElem(3)) * 100), int(fiveElement->getFactor(int2FiveElem(4)) * 100),
		int(fiveElement->getFactor(int2FiveElem(5)) * 100));
	send_msg(hero->getFd(), viewMsg);
	
}
