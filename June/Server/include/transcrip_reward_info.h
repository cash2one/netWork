/****************************************************************
 * Filename: transcrip_reward_info.h
 * 
 * Description: ������������Ϣ������������Ʒ�͸�������Ʒ�����ʵ�
 *
 * Original Author : bison, 2012-6-11
 *
 ****************************************************************/
 
#pragma once
#include <string>
#include<vector>
#include<iostream>
using namespace std;

//�����ѶȲ㼶����
typedef struct ectypeClass_S 
{
	int level;					//�����ѶȲ㼶
	int exp;					//��������
	int money;					//������Ǯ
	double wEqpRate;			//��ɫװ�����н���
	double bEqpRate;			//��ɫװ�����н���
	double pEqpRate;			//��ɫװ�����н���
	double yEqpRate;			//��ɫװ�����н���
	double oEqpRate;			//��ɫװ�����н���
	double petEggRate;			//���ﵰ���н���
	double otherRate;			//������Ʒ�н���
	double reserveRate;			//Ԥ��
	//�����ѶȲ㼶�Ĺ���
	ectypeClass_S(int _level, int _exp, int _money, double _white, double _blue, double _purple,
		double _yellow, double _orange, double _pet, double _other, double _reserve)
	{
		level = _level;
		exp = _exp;
		money = _money;
		wEqpRate = _white;
		bEqpRate = _blue;
		pEqpRate = _purple;
		yEqpRate = _yellow;
		oEqpRate = _orange;
		petEggRate = _pet;
		otherRate = _other;
		reserveRate = _reserve;
	}
	//�չ���
	ectypeClass_S(){};
}ectypeClas_T;

//������Ʒ������
typedef enum{WHITE,BLUE,PURPLE,YELLOW,ORANGE,PETEGG,OTHER,RESERVE}GOODS_TYPE_T;

//�������Ѷ�ֵ
typedef enum{NORMAL_LEVEL = 1, MIDDLE_LEVEL, HARD_LEVEL} ECTYPE_LEVLE_T;

class Transcrip_Reward_Info
{
private:
	int EntLevel;				//���븱���ȼ�Ҫ��
	//������Ʒ��Χ
	vector<string> wEqps;		//��ɫװ���б�
	vector<string> bEqps;		//��ɫװ���б�
	vector<string> pEqps;		//��ɫװ���б�
	vector<string> yEqps;		//��ɫװ���б�
	vector<string> oEqps;		//��ɫװ���б�
	
	vector<string> petEggs;		//���ﵰid�б�
	vector<string> others;		//����������Ʒid�б�
	vector<string> reserve;		//Ԥ��
	
	ectypeClas_T Normal;		//���Ѷ�
	ectypeClas_T Middle;		//�е��Ѷ�
	ectypeClas_T Hard;			//�����Ѷ�
	
	//��typeָ������Ʒ���Ͷ�Ӧ����Ʒ�б����漴����һ����Ʒ
	string getOneGoods(GOODS_TYPE_T type);

public:
	Transcrip_Reward_Info(int _EntLevel, vector<string> _wEqps, vector<string> _bEqps,
		vector<string> _pEqps, vector<string> _yEqps, vector<string> _oEqps,
		vector<string> _petEggs, vector<string> _others, vector<string> _reserve,
		ectypeClas_T _Normal, ectypeClas_T _Middle, ectypeClas_T _Hard);
	
	//�õ�������������
	int getExp(ECTYPE_LEVLE_T level);
	//�õ�����������Ǯ
	int getMoney(ECTYPE_LEVLE_T level);
	//�õ�����������Ʒid
	string getGoods(ECTYPE_LEVLE_T level);

	~Transcrip_Reward_Info(void);
};


