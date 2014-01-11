/****************************************************************
 * Filename: consume_reward.h
 * 
 * Description: ���ѽ���
 *
 * Original Author : xhm, 2012-12-27
 *
 ****************************************************************/

#ifndef MY_CONSUME_REWARD_H_
#define MY_CONSUME_REWARD_H_

#include<map>
#include<string>

using namespace std;

class Consume_reward{
public:
	Consume_reward();
	~Consume_reward();
	
	bool send_reward(void);//�������͵��ʼ���
	bool init_consume_reward(void);//��ʼ���������ݣ�
	
	bool save_consume_reward_info(void);//�����������ݣ�
	bool del_from_reward_team(char *myHeroId);//ɾ������
	int add_to_reward_team(char *myHeroId,int size);//��ӵ���������

public:
	bool isActivity;//�Ƿ��ڻʱ���ڣ�
	int min_consume_size;//��Сֵ�����ģ�
	map<string,int> consume_reward_heroId;//����Id;
	
private:
	map<string,int>::iterator reward_iter;// �����õ������� 
	pair< map< string,int>::iterator,bool > reward_insert_ret;//����insert�ķ���ֵ���ж�insert�Ƿ�ɹ���
};
#endif