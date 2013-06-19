/****************************************************************
 * Filename: five_elements.h
 * 
 * Description: ����
 *
 * Original Author : bison, 2012-7-10
 *
 ****************************************************************/

#ifndef _FIVE_ELEMENTS_H_
#define _FIVE_ELEMENTS_H_
#include "data_structure_struct.h"
#include <iostream>
using namespace std;

//���г�Ա
typedef enum{
	METAL = 1,		//������
	WOOD,			//ľ����
	EARTH,			//������
	WATER,			//ˮ����
	FIRE,			//������
	NOELEM			//û������
}FIVE_ELEMENT_T;

typedef struct FiveElemConf_S
{
	int startLevel;
	int changeNeedGold;
	double defFactor[6][6];
	int needHeroLevel[100];
	int upgradeNeedExp[100];
	int fiveValue[100];
} FiveElemConf_T;

extern FiveElemConf_T heroFiveElemConf; 		//������������

class FiveElem
{
	private:
		int level;					//���еȼ�
		FIVE_ELEMENT_T element;		//���е�����
		int expNow;					//��ǰ�ۻ�����
		int expForNext;				//������һ������Ҫ�ľ���
		
	public:
		//���еĹ��캯��
		FiveElem(FIVE_ELEMENT_T elem = NOELEM, int level = 0);
		//memcached�ָ����ù���
		FiveElem(FiveElementData fiveData);
		//������������
		bool changeElem(FIVE_ELEMENT_T elem);
		//��������
		bool upGrade(void);
		//������еȼ�
		int getLevel(void);
		//�����������
		FIVE_ELEMENT_T getElem(void);
		//��ȡ������ֵ
		int getValue(void);
		//��ñ����������п���
		double getFactor(FIVE_ELEMENT_T hitElem);
		//��ȡ�����˺�ֵ
		int getHurt(double k);
		//����������������
		bool addExp(int value);
		//��ǰ����
		int getExpNow();
		//������һ����Ҫ�ľ���
		int getExpForNext();
		
};

#endif	
	