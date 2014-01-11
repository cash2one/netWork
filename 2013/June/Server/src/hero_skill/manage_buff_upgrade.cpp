/*      
������void buffupgrade(Hero *hero,Skill *skill)     
���ã�buff��������
����ֵ��void
����ˣ�Evan
���ʱ�䣺2012.6.15
*/
#include<map>
#include<string>
#include<iostream>
#include"hero.h"
#include"skill.h"
#include"skill_struct.h"
#include"user_role_manage_skill.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include "money_operator.h"
using namespace std;
void buffupgrade(Hero *hero,Skill *skill)
{
	string msg = "3";
	msg = msg + intTostring(HERO_SKILL_UPGRADE);
	int num_value;
	map<string,Skill*> skill_list;
	skill_list = hero->getSkill_list();
	
	int skill_grade = skill->getskill_grade();
	skill_grade = skill_grade + 1;

	int control_grade = skill->getcontrol_grade();		
	if(skill_grade == 2)
	{
		control_grade += 2;
	}
	int useup_money = skill->getuseup_money();
	unsigned int useup_exp = skill->getuseup_exp();
	
	int level =hero->getLevel();
	int money = hero->getMoney()->money_getBoundGameMoney();
	unsigned int expNow = hero->getExpNow();	
	if(level<(control_grade+1))
	{cout<<"the grade is not"<<endl;
		return;
	}
	// cout<<"the money of hero:"<<money<<endl;
	// cout<<"the money of skill:"<<useup_money<<endl;
	if(money < useup_money)
	{
		num_value = 3;
		msg = msg + intTostring(num_value);
		send_msg(hero->getFd(),const_cast<char *>(msg.c_str()));
		return ;
	}	
	if(expNow < useup_exp)
	{
		num_value = 2;
		msg = msg + intTostring(num_value);
		send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));
		return ;
	}
	useBoundGameMoney(hero,useup_money);		//�ӱ�����ɾ����Ϸ��
	hero->setExpNow(expNow-useup_exp, 1);	
	
	control_grade = control_grade+2;
	
	if(control_grade == 4)
	{
		useup_money = skillneedmoney(level,skill_grade,control_grade -1);
	}
	else
	{
		useup_money = skillneedmoney(level,skill_grade,control_grade);
	}
	
	// useup_money = skillneedmoney(level,skill_grade,control_grade);
	useup_exp = skillneedexp(control_grade);
	skill->setcontrol_grade(control_grade);
	skill->setuseup_money(useup_money);
	skill->setuseup_exp(useup_exp);
	skill->setskill_grade(skill_grade);
	
	string id = skill->getid();           					//����Id
	/*
	int genuine = skill->getgenuine(); 						//����
	int cxsjcz_buff = skill->getcxsjcz_buff();				//����ʱ���ֵ
	int cxsjcz_growup_buff = skill->getcxsjcz_growup_buff();//����ʱ����������
	
	int smxh_buff = skill->getsmxh_buff();					//����ֵ����
	int zjngshbfb_buff = skill->getzjngshbfb_buff();		//�ڹ��˺�
	int zjwgshbfb_buff = skill->getzjwgshbfb_buff();		//�⹦�˺�
	int	consumer_growth = skill->getconsumer_growth();		//�������ĳɳ�����
	int xg_growup_buff = skill->getxg_growup_buff();	    //����Ч���ɳ�
	
	int zjsmsx_buff = skill->getzjsmsx_buff();    		    //buff������������
	
	int cd_time = skill->getcd_time();						//����CD
	int cd_growup_buff = skill->getcd_growup_buff();        //����cd�ɳ�����
	*/
	int effect = skill->geteffect();
	switch(effect)
	{
		case 1:			
			skill->setgenuine(skill->getgenuine() + 190);    //�����ɳ�
			skill->setcxsjcz_buff(skill->getcxsjcz_buff() + skill->getcxsjcz_growup_buff()); //����ʱ���ֵ�ɳ�
			break;
		case 2:			
			skill->setsmxh_buff(skill->getsmxh_buff() + skill->getconsumer_growth());         //����ֵ���ĳɳ�			
			skill->setzjngshbfb_buff(skill->getzjngshbfb_buff() + skill->getxg_growup_buff());//�ڹ��˺��ɳ�			
			skill->setzjwgshbfb_buff(skill->getzjwgshbfb_buff() + skill->getxg_growup_buff());//�⹦�˺��ɳ�
			break;
		case 3:		
			skill->setgenuine(skill->getgenuine() + 510);	//�����ɳ�
			skill->setcxsjcz_buff(skill->getcxsjcz_buff() + skill->getcxsjcz_growup_buff()); //����ʱ���ֵ�ɳ�
			break;
		case 4:
			skill->setgenuine(skill->getgenuine() + 319);	//�����ɳ�
			skill->setzjsmsx_buff(skill->getzjsmsx_buff() + skill->getxg_growup_buff());//buff�����������޳ɳ�
			break;
		case 5:
			skill->setgenuine(skill->getgenuine() + 151);	//�����ɳ�
			skill->setcd_time(skill->getcd_time() - skill->getcd_growup_buff());//����cd�ɳ�
			break;
	}
	
	skill_list[id] = skill;
	hero->setSkill_list(skill_list);
	num_value = 1;			//���������ɹ�
	msg = msg + intTostring(num_value);
	msg = msg + "," + id;
	msg = msg + intTostring(skill_grade);
	msg = msg + intTostring(control_grade);
	msg = msg + intTostring(skill->getgenuine());//evan add 2012.9.26
	msg = msg + intTostring(useup_money);
	msg = msg + intTostring(useup_exp);//evan add 2012.10.13
	send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));
	cout<<"the buff skill upgrade:"<<msg<<endl;
	skill->newmem();
	MemSkill *memskill = skill->getmemskill();
	MemHero *memhero = hero->memHero;
	int num = memhero->skilllists.size;
	for(int i=0;i<num;i++)
	{
		
		string id2 = memhero->skilllists.skills[i].id;
		cout<<"have id:"<<id2<<endl;
		if(id==id2)
		{
			memcpy(memhero->skilllists.skills+i, memskill, sizeof(MemSkill));
			break;
		}
	}
	cout<<"_____________________________________________________________"<<endl;
}
