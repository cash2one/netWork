/**************************************************
�ļ����ͣ��������ܹ���

�ļ����ƣ�manage_beidong.cpp

�ļ����ݣ��������ܴ���

����ʱ�䣺2012.5.31

authou��	Evan

******************************************************/
#include<string>
#include<iostream>
#include"user_role_manage_skill.h"
#include"hero.h"
#include"skill.h"
#include"hero_help.h"
using namespace std;
void  beidonglearn(Hero *hero,Skill *skill)
{
	//cout<<"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY"<<endl;
	//cout<<"the id of hero  is :"<<hero->getLifeUpperVal()<<endl;
	//cout<<"the id of skill is :"<<skill->getid()<<endl;
	//cout<<"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY"<<endl;
	int effect = skill->geteffect();
	switch(effect)
	{
		case 1:
				//��������������޾���ֵ
				hero->setLifeUpperVal(hero->getLifeUpperVal()+skill->getsmsxjdz_bd());
				hero->setLifeVal(hero->getLifeVal()+skill->getsmsxjdz_bd());		
				break;
		case 2:
			//���Ծ���ֵ
				hero->setTenacity(hero->getTenacity()+skill->getrxjdz_bd());
				break;
		case 3:
			//���ܾ���ֵ
				hero->setDodge(hero->getDodge()+skill->getsbjdz_bd());
				break;
		case 4:
			//��������ֵ
				hero->setCrit(hero->getCrit()+skill->getbjjdz_bd());
				break;
		case 5:
			//���о���ֵ
				hero->setHited(hero->getHited()+skill->getmzjdz_bd());
				break;
		case 6:
			//�⹦�˺�
				hero->setOutHurt(hero->getOutHurt()+skill->getwgshbfb_bd());
				break;
		case 7:
			//�⹦����
				hero->setOutAttack(hero->getOutAttack()+skill->getwggjbfb_bd());	
				break;
		case 8:
			//�ڹ�����		
				hero->setInAttack( hero->getInAttack()+skill->getnggjbfb_bd());
				break;
		case 9:
			//�⹦����
	
				hero->setOutDefense(hero->getOutDefense()+skill->getwgfybfb_bd());
				break;		
		case 10:
			//�ڹ�����
				hero->setInDefense(hero->getInDefense()+skill->getngfybfb_bd());
				break;	
		
	}
}