#ifndef FUNCTION_READ_CONFIGURATION_FILES_H
#define FUNCTION_READ_CONFIGURATION_FILES_H

#include<string.h>

int read_main_config(char *fileName);		//��ȡ�������ļ����õ����������ļ�·��

int read_scene_config(char *fileName);		//��ȡ���������ļ�����ó��������ļ���·��

int read_files_map(char *fileName);

int read_files_monster(char *fileName);

//int read_files_skill(char *fileName);     //ԭ���ļ��ܶ�ȡ�����ļ�����  evan add 2012.5.25

int read_files_five(char *fileName);

int read_files_hatValRue(char *fileName);

int read_files_equip(char *fileName);

int read_files_cpy(char *cpyName);

int read_files_task(char *fileName);   //��ȡ����������ļ��ķ���

int read_files_npc(char *fileName);    //��ȡNPC�������ļ��ķ���

int read_files_droplist(char *fileName); //��ȡ�����б������ļ��ķ���

int read_files_touch(char *fileName);  //��ȡ�������������ļ��ķ�������  evan add 2012.5.24

int read_files_zhudong(char * fileName); //�����������͵ļ��ܻ������ݵĶ�ȡ  evan add 2012.5.25

int read_files_yiliao(char * fileName); //ҽ�����͵ļ��ܻ������ݵĶ�ȡ  evan add 2012.5.25

int read_files_buff(char * fileName); //buff���͵ļ��ܻ������ݵĶ�ȡ  evan add 2012.5.25

int read_files_beidong(char * fileName); //�������͵ļ��ܻ������ݵĶ�ȡ  evan add 2012.5.25

int read_ectype_reward_goods(char *fileName); //����������Ʒ��Χ����	added by bison 6.13

int read_ectype_reward_info(char *fileName);	//��ȡ��������������Ϣ	added by bison	6.13

int read_files_cpyLimit(char *fileName);   //��ȡ����������         chenzhen add 2012.06.11 

int parseTowerDefence(char *fileName);		//��ȡ�������������ļ� 

int read_files_ointment(char *fileName); //��ȡҩ��������� cookie 2012.6.14

int read_files_groupBrush(char *fileName); //��ȡ����ˢ�ֻ������� cookie 2012.07.06

int read_task_goods_info(char *fileName);	//��ȡ����������� added by bison 7.6

int read_monster_skill(char *fileName);	//��ȡBoss���� added by ���� 7.10

int read_files_pet(char *fileName);	//��ȡ������Ϣ added by jolly 7.13

int read_files_jumpId(char *fileName);  //��ȡ��ת��ID��Ӧ����Ϣ��  added by xhm 2012.07.18

int read_files_petSkill(char *fileName);	//��ȡ���＼����Ϣ  add by jolly 7.31

int read_files_goods(char *fileName);		//��ȡ������Ʒ����Ϣ add by jolly 8.14

int read_files_suit(char *fileName);		//��ȡ��װ����Ϣ add by evan 2012.8.30

int read_take_goods(char *fileName);		//��ȡ��ժȡ�������

int read_wagon(char *fileName);		//��ȡ���������

int read_files_reward_level(char *fileName);			//��ȡ�ȼ���������Ϣ add by jolly 2012.9.10

int read_files_reward_recharge(char *fileName);			//��ȡ��ֵ������Ϣ add by jolly 2012,9.10

int read_files_reward_time(char *fileName);				//��ȡ����ʱ�佱����Ϣ add by jolly 2012.9.10

int read_bottle(char *fileName);					//��ȡƿ�޵���

int read_trap(char *fileName);						//��ȡƿ�޵���

int read_npc(char *fileName);	  					//npc ����  cookie

int read_guild_activity_info(char *fileName);		//��ȡ���ɻ��Ϣ

int read_cycle_limit_info(char *fileName);			//��ȡѭ����Ŀ

int read_vip(char *fileName);						//cookie��ȡvip

int read_files_update(char *fileName);

int read_copyCause(char *fileName);					//��ȡ������

int read_pitchTerm(char *fileName);

int read_files_revival(char *fileName);				//��ȡ�����λ����Ϣ jolly 9.25

int read_title(char *fileName);

int read_files_mysteriousBussiness(char *fileName);		//��ȡ�������������ļ�

int read_dirty_words(char *fileName);					//��ȡ���

int read_server_config(char *fileName);				//��ȡ���ӻ���������������ļ�

int read_monsterActiveBoss(char *fileName);         //��ȡҰ��boss�������ļ�

int read_dailyActive(char *fileName);               //��ȡ������ļ�

int read_cpyPassOlder(char *fileName);              //��ȡ����ͨ������

int read_files_guildBussiness(char *fileName);              //��ȡ�����̵�

int read_files_midasTouchReward(char *fileName);              //��ȡ��ʯ�ɽ���

int read_guild_feast_info(char *fileName);					//��ȡ����ʢ����Ϣ

int read_server_config(char *fileName);

int read_files_reward_online(char *fileName);				//��ȡ���߽��������ļ�

int read_happy_map(char *fileName);							//��ȡ���ֵ�ͼ����

int read_guild_skill(char *fileName);						//��ȡ���ɼ���

int read_files_shengWangBussiness(char *fileName);						//��ȡ�����̵�

int read_files_reward_target(char *fileName);						//��ȡ����Ŀ�꽱��

int read_buff_debuff(char *fileName);								//��ȡbuff��debuff������

int read_tool_brush_monster(char *fileNme);                //��ȡ����ˢ���ļ�

int read_campWar_reward_conf(char *fileNme);				//��ȡ��Ӫս���������ļ���

int read_files_vipBaleRomLimit(char *fileName);           //��ȡVIP����������  

int read_files_partyRomLimit(char *fileName);             //��ȡ����������  

int read_fight_const_value(char* fileName);					//��ս����ʽ����

int read_hero_skill(char *fileName);						//��ȡ���＼������

int read_hero_conf(char *fileName);						//��ȡ����������������

int read_recharge_reward_conf(char *fileName);			//��ȡ��ֵ���������ļ���

int read_guild_reward(char *fileName);					//��ȡ���ɽ���

int read_Npc_cpy_pt(char *fileName);                    //��ȡ����npc����

int read_files_reward_useGold(char *fileName);           //��ȡ����npc����

int read_party_base_camp(char *fileName);                //��ȡ���ɴ�Ӫ

int read_consume_reward_conf(char *fileName);			//��ȡ���ѽ��������ļ� xhm added;

int read_heCheng_config(char *fileName);				//��ȡ��ʯ�ϳ�����������ļ�

int read_factor_reward(char *fileName);					//��ȡ���齱�������ļ�

int read_outer_active_code(char *fileName);             //��ȡ�ⲿ�����������ļ�

int read_inner_active_code(char *fileName);            	//��ȡ�ڲ������������ļ�

int read_festivalGoods(char *fileName);               	//��ȡ���Ʒƥ�������ļ�

int read_five_elem_conf(char *fileName);				//����������

int read_merid_conf(char *fileName);					//����������

int read_internal_forces(char *fileName);				//����

int read_active_double(char *fileName);					//������˫�������ļ�

int read_good_use_reward_conf(char *fileName);			//��ȡ��Ʒʹ�ü�¼��

int read_files_ride(char *fileName);					//��ȡ��Ʒʹ�ü�¼��

int read_statuaryBase(char *fileName);              //��ȡ������������ļ�

int read_mem_group_config(char* fileName);				//��ȡ����������������б�

int read_files_vip(char* fileName);				//��ȡvip�����ļ�

int read_files_rideSkill(char* fileName);				//��ȡ���＼�������ļ�

int read_files_rideSpecialSkill(char* fileName);				//��ȡ�������⼼�������ļ�

int read_camp_res_war_control(char *fileName);

int read_guild_war_control(char *fileName);

int read_rob_flag_war_control(char *fileName);

int read_files_petRange(char *fileName);				//��ȡ����ս�� �Ѿ�ˢ�µ������ļ�

int read_black_margin(char *fileName);                 //��ȡ��ľ�������ļ�

int read_files_equipOperator(char *fileName);                 //��ȡװ�����������ļ�

int read_global(char *fileName);

int read_files_rankReward(char *fileName);			//��ȡ��������

int read_files_words(char *fileName);			//��ȡ����������

int read_files_everyDaySignReward(char *fileName);			//��ȡÿ��ǩ������

int read_cycle_task_reward_info(char *fileName);			//ÿ������ѭ����������ѭ�����Ӽ���

int read_files_cdkey(char *fileName);			//cdkey�һ����������ļ�


#endif
