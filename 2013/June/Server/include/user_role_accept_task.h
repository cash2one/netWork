/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�user_role_accept_task.h
		�ļ����ã������ͻ��˷��͸�����������Ƿ�������񷽷�
		  ʵ���ߣ�Evan
		���ʱ�䣺2012.5.18
*/
#ifndef USER_ROLE_ACCEPT_TASK
#define USER_ROLE_ACCEPT_TASK

#define ACCEPT_TASK_ACCEPTED_FULL_ERROR		1				//�ѽ���������
#define ACCEPT_TASK_NO_THIS_TASK_ERROR		2				//����ID����
#define ACCEPT_TASK_ALREADY_ACCEPT_ERROR	3				//���ѽ������б���
#define ACCEPT_TASK_ALREADY_FINISH_ERROR	4				//�Ѿ���ɵ�����
#define ACCEPT_TASK_TIMES_LIMIT_ERROR		5				//ÿ�����ƴ����ﵽ
#define	ACCEPT_TASK_LEVEL_IS_LOW_ERROR		6				//�ȼ�̫��
#define	ACCEPT_TASK_LEVEL_IS_HIGH_ERROR		7				//�ȼ�̫��
#define ACCEPT_TASK_NOT_JOIN_CAMP_ERROR		8				//δ������Ӫ
#define ACCEPT_TASK_NOT_JOIN_GUILD_ERROR	9				//δ�������
#define ACCEPT_TASK_NOT_THIS_CAMP_ERROR		10				//�ӵ���Ӫ�����Ǳ���Ӫ��
#define ACCEPT_TASK_PRE_NOT_FINISH_ERROR	11				//ǰ������δ���
#define ACCEPT_TASK_PRE_NOT_ACCEPT_ERROR	12				//ǰ������δ�Ӵ���
#define ACCEPT_TASK_BAG_IS_FULL_ERROR		13				//��ұ�����������ʼ�и����ߵ�����
#define ACCEPT_TASK_SERVER_CONF_ERROR		14				//�������������ô���
#define ACCEPT_TASK_TOO_FAR_ERROR			15				//��NPC̫Զ
#define ACCEPT_TASK_SAME_TYPE_ERROR			16				//�ѽ�ͬ���͵�����
#define ACCEPT_TASK_NO_CYCLE_TASK_ERROR		17				//û�����ѭ������ID


void taskAccept(char *buffer);
void GM_accept_one_task(char *buffer);
#endif

