/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�other_define_data.h
		�ļ����ã����������Ķ���
*/

#ifndef OTHER_DEFINE_DATA_H
#define OTHER_DEFINE_DATA_H
#include<string>
#define MAXLEN 1023          	//��󻺴�ռ�
#define PORT 8090          		//�˿ں�
#define MAX_NAME_LEN 50       	//�û�������󳤶�
#define MAX_WORD_LEN 50       	//�������󳤶�
#define HERO_ID_LEN 38			//��ɫID����
/* #define FLAGLEN		2			//���ڴ�� */

#define MAX_TYPE_COMMAND 100      	//�������������
#define MAX_EACH_TYPE_COMMAND 50   	// ÿ�����͵�����������

#define EFFECT_COMMAND_RANGE MAX_EACH_TYPE_COMMAND*MAX_TYPE_COMMAND          //���������������Ŀ

#define DEAD 0                  //����״̬
#define LIVE 1                  //���״̬

#define SKILL_COLL_DOWN_TIME  0.01         //������ȴʱ��
#define SKILL_COOL 1           //������ȴ״̬
#define SKILL_HOT 0            //������״̬
#define MONSTER_THINK_TIME 0.5
#define MONSTER_EACH_WALK_STEP 3
#define HERO_TYPE "H"
#define MONSTER_TYPE "M"

#define MAP_THINK_TIME 1         //add by chenzhen 

#define ATTACK_TYPE "000"     

#define MON_ATT_TYPE "000"   //ADD by chnzhen 4.23

#define ATTACK_VOID_BASE_NUM 0.0001
#define VOID_BASE_NUM 500
#define VOID_BASE 0.5

#define HANG_UP_DATA_SIZE 200			//�һ�������󳤶ȣ�
#define PARTY_LEN	2					//�������ֵ�����ɱ�������һ���ַ��ɱ�ʾ������hero�����õ����ַ���������ֻ�ܶ���2���ַ��أ�������RTX xhm;
#define MAX_FRIEND_COUNTS 200			//xhm ��� ��������Ŀ��	������RTX xhm
#define HERO_MAME_LEN 32				//��Ϸ�ǳ���󳤶ȣ� 		������RTX xhm
#define SHORT_CUT_BAR_DATA_SIZE 500		//�����������󳤶ȣ�		������RTX xhm
#define SYSTEM_SET_DATA_SIZE 200		//ϵͳ���û������ݳ��ȣ�	������RTX xhm
#define OPERATION_SET_DATA_SIZE 300		//�������û������ݳ��ȣ�	������RTX xhm
#define MAX_MESSAGE_DATA_LEN 1000		//������Ϣ��󳤶ȣ�		������RTX xhm

#define WAGON_WALK_TIME 1800            //������ʱ��

#define COPY_SUM_LEVEL   49             //��������<���渱�������ӣ���Ҳ����>

#define COPY_SUM_FLG   19             	//��������

#define FIGHT_FRIST_HEAD 26              //������һ��ͷ����
#define FIGHT_SECOND_HEAD 2              //�����ڶ���ͷ����
#define FIGHT_SECOND_BUFF 3              //buff���ܵڶ���ͷ����
#define OPEN_BUFF 0                      //buff���ܿ���
#define CLOSE_BUFF 1                      //buff���ܹر�

#define MONSTER_TASK_LIVE_TIME 180         //����ִ��ʱ��
#endif
