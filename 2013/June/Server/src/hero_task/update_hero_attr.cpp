/***********************************************************
 * �ļ�����update_hero_attr.cpp
 * �ļ�����������Ӣ�����ԣ�ͬʱ��ͻ��˷���hero���±䶯����
 * ʱ�䣺2012.6.6 by bison
 ***********************************************************/

#include<iostream>
#include "hero.h"
#include"command_other_function_all_over.h"

using namespace std;

/**
 * hero_add_exp - Ӣ�����Ӿ���
 * @hero: Ҫ���Ӿ����Ӣ��ָ��
 * @_exp: ���ӵľ���ֵ
 * description: ��Ӣ�۵ĵ�ǰ����������ӣ����û��������ͻ��˷��;���仯��
 * ��������ˣ�����ͻ��˷���ȫ���仯��Ϣ
 */
void hero_add_exp(Hero *hero, unsigned _exp)
{
	string msgHead = "1";
	unsigned oldLevel = hero->getLevel();
	unsigned newLevel;
	string incExpMsg;
	
	incExpMsg = incExpMsg + msgHead + intTostring(ADDEXPRETURN);
	
	hero->setExpNow(_exp);
	newLevel = hero->getLevel();
	if (newLevel == oldLevel)
	{
		incExpMsg  = incExpMsg + intTostring(newLevel) + intTostring(hero->getExpNow());
		send_msg(hero->getFd(), const_cast<char *>(incExpMsg.c_str()));
		cout<<"Send no level up msg"<<endl;
		cout<<incExpMsg<<endl;
		
	} else {
		incExpMsg += intTostring(newLevel);
		incExpMsg += intTostring(hero->getExpForGrow());
		incExpMsg += intTostring(hero->getExpNow());
		incExpMsg += intTostring(hero->getLifeUpperVal());
		incExpMsg += intTostring(hero->getLifeVal());
		incExpMsg += intTostring(hero->getMagicUpperVal());
		incExpMsg += intTostring(hero->getMagicVal());
		incExpMsg += intTostring(hero->getOutAttack());
		incExpMsg += intTostring(hero->getInAttack());
		incExpMsg += intTostring(hero->getOutDefense());
		incExpMsg += intTostring(hero->getInDefense());
		send_msg(hero->getFd(), const_cast<char *>(incExpMsg.c_str()));
		cout<<"Send level up msg"<<endl;
		cout<<incExpMsg<<endl;
	}
	
}

