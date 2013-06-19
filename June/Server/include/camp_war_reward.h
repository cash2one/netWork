#ifndef INCLUDE_CAMP_WAR_REWARD_
#define INCLUDE_CAMP_WAR_REWARD_
#include "other_define_data.h"

#define ORD_REWARD 0
#define WIN_LEADER_REWARD 1 
#define FAI_LEADER_REWARD 2
#define FIRST_CHIEF_REWARD 3
#define SECOND_CHIEF_REWARD 4
#define THIRD_CHIEF_REWARD 5

#define CAMP_WAR_REWARD_SIZE 6

#define FIRST_TITLE "T029"								//����ͷ��ID
#define SECOND_TITLE "T030"								//��ʥͷ��ID
#define THIRD_TITLE "T031"								//����ͷ��ID

#define CAMP_LEADER_TITLE "T025"						//ͳ��ͷ��ID
#define CAMP_CHIEF_TITLE "T024"							//����ͷ��ID

/*
 *��Ӫս�����ṹ�壬������RTX xhm
*/
typedef struct CampRewardData_S{
	int gold_base_value;		//�󶨽�һ�׼���ݣ���һ���������ֵ)
	int gold_dec_value;			//�󶨽�ҵݼ���С(ÿ����һ�����ٽ�Ҵ�С)
	int prestige_base_value;	//������׼����
	int prestige_dec_value;		//�����ݼ���С
	int guidGlory_base_value;	//�ﹱ��׼����
	int guidGlory_dec_value;	//�ﹱ�ݼ���С
	int guidExp_base_value;		//���ɾ����׼����
	int guidExp_dec_value;		//���ɾ���ݼ���С
	int rank_limit_value;		//�����ݼ����ƴ�С(���ڻ���С��������Σ��������ݼ���												��rank_limit_value-1���ν�����ͬ)
	
	CampRewardData_S(){
		gold_base_value=0;		
		gold_dec_value=0;			
		prestige_base_value=0;	
		prestige_dec_value=0;		
		guidGlory_base_value=0;	
		guidGlory_dec_value=0;	
		guidExp_base_value=0;		
		guidExp_dec_value=0;		
		rank_limit_value=0;			
	}

}CampRewardData_T;

#endif