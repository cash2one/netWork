/****************************************************************
 * Filename: ectype_reward_info.h
 * 
 * Description: ������������Ϣ������������Ʒ�͸�������Ʒ�����ʵ�
 *
 * Original Author : bison, 2012-6-13
 *
 ****************************************************************/

 #include"data_structure_struct.h"
#include"command_other_function_all_over.h"
#include<stdlib.h>
#include<stdarg.h>
#include <string>
#include<vector>
#include<map>
#include<iostream>
using namespace std;
#pragma once
//�������������沨�����ӵĲ���
#define EXP_INC_STEP			5000
//����������Ǯ�沨�����ӵĲ���
#define MONEY_INC_STEP			500
//��������������©�������ٵĲ���
#define SILVER_DEC_STEP			100
//����������ˢ��һ���ֵĻ�������ֵ		added on 6.29
#define TD_BASE_EXP				50000
//����������ˢ��һ���Ļ�����Ǯ����ֵ	added on 6.29
#define TD_BASE_MONEY			2000

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

//��һ����������������������ӵ���
inline string rand3Num(int sum)
{
	int num1, num2, num3;
	int min, max;
	min = MAX(1, sum - 12);
	max = MIN(sum - 2, 6);
	num1 = (max == min) ? max : rand() % (max - min + 1) + min;
	sum -= num1;
	min = MAX(1, sum - 6);
	max = MIN(sum - 1, 6);
	num2 = (max == min) ? max : rand() % (max - min + 1) + min;
	num3 = sum - num2;
	cout<<"num1: "<<num1<<endl;
	cout<<"num2: "<<num2<<endl;
	cout<<"num3: "<<num3<<endl;
	string msg = intTostring(num1) + intTostring(num2) + intTostring(num3);
	return msg;

}

typedef struct EctypeRewardItem_S
{
	char typeId[51];
	double vipRate[50];
} EctypeRewardItem_T;

class Ectype_Reward_Info
{
	private:
		char ectypeId[51];						//id
		int exp;								//���齱��
		int money;								//��Ǯ����
		int silver;								//��������
		int heroSkillExp;						//���＼�ܵ�
		int petSkillExp;						//���＼�ܵ�
		int useGoldRateIndex;					//Ԫ��ˢ�¶�Ӧĳvip�ȼ��ĸ���
		vector<EctypeRewardItem_T> rewardGoods;	//��������Ʒ��Ϣ
		//��ָ��������Ʒ�������ȡһ����Ʒid
		char* getOneGoods(char* typeId);
	public:
	
		Ectype_Reward_Info(char *_ectypeId, int _heroSkill, int _petSkill, int _exp, int _money, int _silver, int useGold);
		void addOneRewardItem(char *typeId, int num, ...);
		void addOneReward(char *typeId, int num, double* rateList);
		void testData();
		
		int getExp();
		int getMoney();
		int getSilver();
		int getPetSkillExp();
		int getHeroSkillExp();
		int getDefendSilver(int missed);
		
		//Ҳ���ⲿ�ò���
		int getUseGoldRateIndex();
		
		char* getGoods(int vipClass = 0);
#if 0		
		//�õ����������ľ���ֵ
		int getExp(ECTYPE_CLASS_T step);
		//�õ����������Ľ�Ǯֵ
		int getMoney(ECTYPE_CLASS_T step);
		//�õ���������������ֵ
		int getSilver(ECTYPE_CLASS_T step);
		//�õ�������������Ʒid, flag(0:��ͨ�����ʣ�1:vip�����ʣ�2:��Ԫ��������)
		char* getGoods(ECTYPE_CLASS_T step, int flag = 0);
		
		//�õ�����������times���ֵľ��齱����ֻ��45�������������ܵ��ô˽ӿ�
		int getDefendExp(ECTYPE_CLASS_T step, int times);
		//�õ�����������times���ֵĽ�Ǯ������ֻ��45�������������ܵ��ô˽ӿ�
		int getDefendMoney(ECTYPE_CLASS_T step, int times);
		//�õ���������©missedֻ�ֵ�����������ֻ��45�������������ܵ��ô˽ӿ�
		int getDefendSilver(ECTYPE_CLASS_T step, int missed);
#endif		
};
