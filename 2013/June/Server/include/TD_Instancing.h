#ifndef TD_INST_
#define TD_INST_

#include<string>
#include <vector>
#include <iostream>

#include "libev.h"
#include "map_cpy.h"
#include "ectype_reward_set.h"
#include "data_structure_struct.h"

class CpyLimit;
/**
*˵�������º궨��Ϊ����������¼�����ݵ�������ʶ�����ڻ�ȡ/�޸�����������¼�����Ӧ��ֵ�Ĵ������
*���ú�����	int  getInstancingStatus(DATA_CHOICE_INT data_choice);
*			bool setInstancingStatus(DATA_CHOICE_INT data_choice);
*/
typedef int DATA_CHOICE_INT;

#define INST_STATUS_ISPOLL 				1
#define INST_STATUS_ISSYSATTACKOPEN 	2
#define INST_STATUS_POLL_COUNT 			3
#define INST_STATUS_LOSE_COUNT 			4
#define INST_STATUS_MONSTER_COUNT 		5
#define INST_STATUS_MONSTER_DISAPPEAR 	6
#define INST_STATUS_ROTATE_COUNT 		7
#define INST_STATUS_CUR_LIVE_COUNT 		8
#define INST_STATUS_HELP_VAL 			9

#define ALL_MAX_LOSE					5	//©������������Ŀ

/**�����������������*/
typedef struct{
	int 	open_flag;				//����������������֤��ͬ�Ѷȵȼ��ĸ����Ľ���
	int 	level;					//�ȼ�Ҫ��
	int 	free_limit;				//ÿ�ս������
}Instancing_require;


/**��������������Ϣ*/
typedef struct{
	string 	id;
	string 	name;
	int 	degree;					//��ǰ�������Ѷȵȼ���0--->��ͨ��1--->������2--->Ӣ�ۣ�
}Instancing_infor;


/**��������������Ϣ*/
typedef struct{	
	int		attractMonNum;			//���������������
	int 	single_frequency;		//��������ˢ�����
	int		unit_frequency;			//��������ˢ�����
	vector<int>		time_gap;		//ÿ�����������
 	vector<Point> 	route_left;		//�����ƶ�����·��(���)
	vector<Point> 	route_right;	//�����ƶ�����·��(�Ҳࣩ
	vector<Point> 	stand_point;	//��ɫ����ʱ��վ���� 
}Instancing_strategy;


//����״̬��¼��
typedef struct Instancing_record{
	bool	isPoll;					//�Ƿ�������
	bool 	sysAttackOpen;			//ϵͳ�������﹦���Ƿ��ѿ���
	int		poll_count;				//��ѯ�Ĵ���
	int		lose_count;				//˳���ܵ�Ŀ���Ĺ���
	int  	monster_count;			//��ˢ���Ĺ������
	int		monster_disappear;		//��Ϊ�ߵ��յ�򱻹����������Ĺ�����Ŀ�����������Ը�ʵ��������ʧ����
	int		rotate_count;			//��������
	int		cur_live_count;			//��ǰ�����д����������
	int		help_val;				//����ֵ
	
	int 	cur_max_monster_num;	//�ڵ�ǰ�����£�����ˢ������������Ŀ
	int		time_gap_sum;			//��ǰ���������£����ʱ����ܺͣ�������һ���εĹ���ˢ����Ҫ������ʱ��
	
	Instancing_record(){
		data_reset();
	}
	
	void data_reset(){
		isPoll = false;
		sysAttackOpen = false;
		poll_count = 0;
		lose_count = 0;
		monster_count = 0;
		monster_disappear = 0;
		rotate_count = 0;
		cur_live_count = 0;		
		help_val = 0;
		
		cur_max_monster_num = 0;
		time_gap_sum = 0;
	}
}Instancing_record;


//����������������Ϣ
typedef struct TD_Conf_S {
	Instancing_infor		infor;				//��������������Ϣ
	Instancing_require		require;			//���븱��Ҫ��
	Instancing_strategy		strategy;			//�����淨����������Ϣ
	vector<string>			scenes_id_vec;		//�����а����ĳ���ID����
	
	TD_Conf_S(Instancing_infor _infor, Instancing_require _require,
		Instancing_strategy _strategy, vector<string> _scenes_id_vec)
	{
		infor = _infor; 
		require = _require;
		strategy = _strategy;
		scenes_id_vec = _scenes_id_vec;
	}
	
	TD_Conf_S(){};
	
} TD_Conf_T;

void show_TD_Conf_S(TD_Conf_T obj, char *outfile);

/*
 * int2str - ������ת���ɹ̶����ȵ��ַ�����λ�������Ĳ���
 * author: bison
 * @val: ��Ҫת����������
 * @figure: ��Ҫת���ɵ��ַ���λ��
 * Return: ����ת�����ַ�������figureΪ4ʱ,23��ת��"0023"
 */
inline string int2str(int val, int figure)
{
	string str;
	while(figure--)
	{
		str.insert(str.begin(), (char)('0' + val % 10));
		val /= 10;
	}
	return str;
}


class TD_Instancing
{
	private:		
		/**ʵ��������ʱ���ʼ������*/
		Map_Cpy*	mapNow;
		vector<MonsterBase *>	monster_store;		//�����������Ĺ�������,�ɵ�ͼʵ������
	
		Instancing_record		record;				//������¼��
		EctypeRewardSet *		rewardSet;			//������������
		
		list<MonsterBase *>     currMonster;		//��ǰ�����Ĺ��Ｏ��
		vector< vector<string> > 	mon_vec;		//ˢ������

	public:
		/**�����ļ��ṩ����Ϣ*/
		Instancing_infor		infor;			//��������������Ϣ
		Instancing_require		require;		//���븱��Ҫ��
		Instancing_strategy		strategy;		//�����淨����������Ϣ
		
		string		td_inst_id;		//����ʵ��id
		int			roomNum;		
		vector<Hero*> heroPtr_vec;	//��ǰ��������Ҽ���
		bool		isSingleChall;	//�Ƿ�����սģʽ
	public:
		TD_Instancing(int roomNum);	
		~TD_Instancing();
		bool reset(void);											//��������ʵ�����ýӿڣ�	
		bool loadNewInstance(const TD_Conf_T &tdConf, Map_Cpy* scene);
		int  response(void);	
		void stopMonThk();
		
		void setHeroLocation(Hero* heroWillEnt,int _index);			//���ý�ɫ�ڸ����е�λ��
		string get_instancing_id(void);								//�õ�����ʵ����id���
		string get_instancing_confId(void);							//�õ���������id
		Instancing_strategy getInstancing_strategy(void);			//��ø����Ĳ�����Ϣ
		Instancing_require	getInstancing_require(void);			//���븱��Ҫ��
				
		int  getInstancingStatus(DATA_CHOICE_INT data_choice);		
		bool AddSelfInstancingStatus(DATA_CHOICE_INT data_choice);
		void start_systerm_attack(vector<Hero *> team_unit);		//����ϵͳ�������﹦��		
				
		ev_timer *timer;											//�����ⲿ����
		EctypeRewardSet* getRewardSet(void);						//�õ���������
							
		//describe: �������������е����н�ɫ�㲥��Ϣ
		void sendMsgInTower(char *msg2Send);

};

//���ڸ���ע����poll������ͨ���¼��ص������Ⱥ�˳��ִ����Ӧ�ĸ���response
void inst_poll_callback(struct ev_loop *loop,ev_timer *think,int revents);

CpyLimit* getLimitInst(const char* cpyType);
#endif