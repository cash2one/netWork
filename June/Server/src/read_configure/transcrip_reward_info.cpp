/****************************************************************
 * Filename: transcrip_reward_info.cpp
 * 
 * Description: ������������Ϣ�Ĺ��캯���ͽ�����Ϣ��ȡ�����Ķ���
 *
 * Original Author : bison, 2012-6-11
 *
 ****************************************************************/
 
#include "transcrip_reward_info.h"
#include<cstdlib>
#include<ctime>
using namespace std;

/************************************************************************/
/* Transcrip_Reward_Info -- ����������Ϣ���캯��
/* @_EntLevel: �����ȼ�
/* @_wEqps: ���ܽ����İ�ɫװ��id�б�
/* @_bEqps: ���ܽ�������ɫװ��id�б�
/* @_pEqps: ���ܽ�������ɫװ��id�б�
/* @_yEqps: ���ܽ����Ļ�ɫװ��id�б�
/* @_oEqps: ���ܽ����ĳ�ɫװ��id�б�
/* @_petEggs: ���ܽ����ĳ��ﵰid�б�
/* @_others: ���ܽ�����������Ʒid�б�
/* @_reserve: Ԥ�����ܽ�����Ʒid�б�
/* @_Normal: ��ͨ��������ֵ��Ϣ
/* @_Middle: �е��Ѷȸ�������ֵ��Ϣ
/* @_Hard:	���Ѹ�������ֵ��Ϣ0
/************************************************************************/
Transcrip_Reward_Info::Transcrip_Reward_Info(int _EntLevel, vector<string> _wEqps,
	vector<string> _bEqps,vector<string> _pEqps, vector<string> _yEqps, vector<string> _oEqps,
	vector<string> _petEggs, vector<string> _others, vector<string> _reserve,
	ectypeClas_T _Normal, ectypeClas_T _Middle, ectypeClas_T _Hard)
{
	EntLevel = _EntLevel;
	wEqps = _wEqps;
	bEqps = _bEqps;
	pEqps = _pEqps;
	yEqps = _yEqps;
	oEqps = _oEqps;
	petEggs = _petEggs;
	others = _others;
	reserve = _reserve;
	Normal = _Normal;
	Middle = _Middle;
	Hard = _Hard;
}

/************************************************************************/
/* getExp -- ���ݸ����ѶȻ�ø�����������
/* @level: �����Ѷȵȼ�
/* @return: ���ظ�����������ֵ
/************************************************************************/
int Transcrip_Reward_Info::getExp(ECTYPE_LEVLE_T level)
{
	int rewardExp = 0;
	switch (level)
	{
	case NORMAL_LEVEL:
		rewardExp = Normal.exp;
		break;
	case MIDDLE_LEVEL:
		rewardExp = Middle.exp;
		break;
	case HARD_LEVEL:
		rewardExp = Hard.exp;
		break;
	default:
		rewardExp = 0;
		break;
	}
	return rewardExp;
}

/************************************************************************/
/* getMoney -- ���ݸ����ѶȻ�ø���������Ǯ
/* @level: �����Ѷȵȼ�
/* @return: ���ظ���������Ǯֵ
/************************************************************************/
int Transcrip_Reward_Info::getMoney(ECTYPE_LEVLE_T level)
{
	int rewardMoney = 0;
	switch (level)
	{
	case NORMAL_LEVEL:
		rewardMoney = Normal.money;
		break;
	case MIDDLE_LEVEL:
		rewardMoney = Middle.money;
		break;
	case HARD_LEVEL:
		rewardMoney = Hard.money;
		break;
	default:
		rewardMoney = 0;
		break;
	}
	return rewardMoney;
}

/************************************************************************/
/* getGoods -- ���ݸ����ѶȻ�ø���������Ʒid
/* @level: �����Ѷȵȼ�
/* @return: ���ظ���������Ʒid
/************************************************************************/
string Transcrip_Reward_Info::getGoods(ECTYPE_LEVLE_T level)
{
	string goodsId;
	unsigned temp = 0;          //�����ۼ�ֵ
	ectypeClas_T classTemp;		//�����ѶȲ㼶

	switch (level)
	{
	case NORMAL_LEVEL:
		classTemp = Normal;
		break;
	case MIDDLE_LEVEL:
		classTemp = Middle;
		break;
	case HARD_LEVEL:
		classTemp = Hard;
		break;
	default:
		//DEBUGMSG();
		return goodsId;
	}

	double wEqpRate = classTemp.wEqpRate;			//��ɫװ�����н���
	double bEqpRate = classTemp.bEqpRate;			//��ɫװ�����н���
	double pEqpRate = classTemp.pEqpRate;			//��ɫװ�����н���
	double yEqpRate = classTemp.yEqpRate;			//��ɫװ�����н���
	double oEqpRate = classTemp.oEqpRate;			//��ɫװ�����н���
	double petEggRate = classTemp.petEggRate;		//���ﵰ���н���
	double otherRate = classTemp.otherRate;			//������Ʒ�н���
	double reserveRate = classTemp.reserveRate;		//Ԥ��

	//srand((unsigned)time(NULL));
	unsigned rand_value = rand() % 10000;

	if (rand_value < (temp += (unsigned)(wEqpRate * 100)))
	{
		goodsId = getOneGoods(WHITE);

	} else if (rand_value < (temp += (unsigned)(bEqpRate * 100))) {
		goodsId = getOneGoods(BLUE);

	} else if (rand_value < (temp += (unsigned)(pEqpRate * 100))) {
		goodsId = getOneGoods(PURPLE);

	} else if (rand_value < (temp += (unsigned)(yEqpRate * 100))) {
		goodsId = getOneGoods(YELLOW);

	} else if (rand_value < (temp += (unsigned)(oEqpRate * 100))) {
		goodsId = getOneGoods(ORANGE);

	} else if (rand_value < (temp += (unsigned)(petEggRate * 100))) {
		goodsId = getOneGoods(PETEGG);

	} else if (rand_value < (temp += (unsigned)(otherRate * 100))) {
		goodsId = getOneGoods(OTHER);

	} else if (rand_value < (temp += (unsigned)(reserveRate * 100))) {
		goodsId = getOneGoods(RESERVE);
	}

	return goodsId;
}

/************************************************************************/
/* getOneGoods -- ��ָ�����͵���Ʒid����������õ�һ��
/* @type: ������Ʒ��ָ������
/* @return: ���������Ʒ��id
/************************************************************************/
string Transcrip_Reward_Info::getOneGoods(GOODS_TYPE_T type)
{
	string GoodsId;					//���ص���Ʒid
	vector<string> idsTemp;			//������Ʒ��ĳһ����
	int size = 0;					//��Ӧ��ĳһ������Ʒ���е�����

	switch (type)
	{
	case WHITE:
		idsTemp = wEqps;            //��Ʒ��������ȡ��ɫװ��
		break;
	case BLUE:
		idsTemp = bEqps;			//��Ʒ��������ȡ��ɫװ��
		break;
	case PURPLE:
		idsTemp = pEqps;			//��Ʒ��������ȡ��ɫװ��
		break;
	case YELLOW:
		idsTemp = yEqps;			//��Ʒ��������ȡ��ɫװ��
		break;
	case ORANGE:
		idsTemp = oEqps;			//��Ʒ��������ȡ��ɫװ��
		break;
	case PETEGG:
		idsTemp = petEggs;          //��Ʒ��������ȡ���ﵰ��
		break;
	case OTHER:
		idsTemp = others;           //��Ʒ��������ȡ������Ʒ
		break;
	case RESERVE:
		idsTemp = reserve;			//Ԥ��
		break;
	default:
		return GoodsId;				//����Ʒ���Ͳ�������
	}

	size = idsTemp.size();
	//srand((unsigned)time(NULL));
	unsigned rand_value = rand() % size;		//�������һ����������Ʒ����������������

	GoodsId = idsTemp[rand_value];
	return GoodsId;
}
Transcrip_Reward_Info::~Transcrip_Reward_Info(void)
{
}
