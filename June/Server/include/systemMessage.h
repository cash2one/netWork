#ifndef SYSTEM_MESSAGE_H
#define SYSTEM_MESSAGE_H

#define MSG_LEN 2000
#define systemSendMssage SYSTEM_MESSAGE::systemMssage
#define sendActivityMsg  SYSTEM_MESSAGE::systemActivityMsg

#include "my_timer.h"

class Hero;

//���Ϣ��ṹ
typedef struct systemMsg_S{
	char msg[MSG_LEN];
	int	times;
	int interval_time;
	int level;          //��Ϣ���͵ȼ�Ȩ��
	ev_timer *system_activity_timer;//��ȫʱ�䶨ʱ����
	void init(){
		memset(msg,0,MSG_LEN);
		times=0;
	}
	systemMsg_S(char*_msg,int time,int _interval_time,int _level = 1){
		memcpy(msg,_msg,MSG_LEN);
		times=time;	
		interval_time=_interval_time;
		system_activity_timer =NULL;
		level = _level;
	}
}systemMsg_T;

/**
	Type	0��ϵͳ��
			1������
			2: ��Ӫ
			3�����ɡ�
			4������
			5������
*/
class SYSTEM_MESSAGE{
public:
static void systemMssage(Hero*myHero,char* msg,int Type);

/**
	ȫ����Ϣ
*/
static void systemMssageAllEral(string& _msg,size_t level = 1);

/**
	ȫ�����ʾ��Ϣ
*/
static void systemActivityMsg(char *msg,int time,int _interval_time,int levelLimit = 1);

};

#endif /* LOGGER_H */