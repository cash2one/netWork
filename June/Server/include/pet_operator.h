#ifndef PET_OPERATOR_H
#define PET_OPERATOR_H
#include<string>
#include<time.h>
#include"pet.h"
#include"bag.h"
using namespace std;

bool petMating(Hero *hero,Pet *pet1,Pet *pet2,int index1,int index2,int num);									//���ﷱֳ���ܺ���

void matingSon(char* goodsid,int decide_level,int decide_quality,int male_type,int generation,int luckNum);	
//�����ӱ���id

int decideSonQuality(int decide_level,int decide_quality,int luckNum);				//�����ӱ��ĳ���Ʒ��

bool levelDecidePercent(int level,int luckNum);										//���ݵȼ��鿴���ﷱֳ�Ƿ������Ʒ��

bool compareNum(int num,int percent);									//�ȽϺ���

int random(int begin,int end);											//�漴begin��end�������

bool MatingCondition(Hero *hero,Pet *pet1,Pet *pet2);							//�ж��Ƿ����㷱ֳ����

void petFiveEleExp(Hero *hero,char* goodsid,int index);				//ʹ�ó������о��鵤

bool petLevelUp(Pet *pet,Hero *hero,int exp);				//��������

bool doublePetMating(Hero *hero1,Hero *hero2,Pet *pet1,Pet *pet2);	

bool doubleMatingCondition(Hero *hero1,Hero *hero2,Pet *pet1,Pet *pet2);							//�ж��Ƿ����㷱ֳ����

#endif

