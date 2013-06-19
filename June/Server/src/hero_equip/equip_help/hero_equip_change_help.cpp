#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
using namespace std;
/*
	������ݣ���Ҵ�װ���ĸ�������ʵ��
	���ʱ�䣺2012.8.23
	����ˣ�Evan
*/
void wearEquip(Hero *hero,Equipment *equip)
{
	/*��һ���ж���ҵ�ǰ��λ�Ƿ��Ѿ�����װ��*/
	// int type = equip->gettype();	
	//���������Ӧ��λ����װ��
						
	/*�ڶ��������������Ҫ����װ��*/
	equip->setBound(1);									//��װ������Ϊ��״̬
	
	int iswear = 1;
	equip->setisbag(iswear);							//װ���Ƿ������� 0���ڱ����ڣ�1�������� evan add 2012.8.31
	
	// hero->setWearEquip(type,equip);	//��Ҫ����װ����ӵ��Ѵ�װ������
	// cout<<"*******the type:"<<type<<endl;
	// cout<<"size:"<<hero_equipment_map.size()<<endl;
	int type_num = 1;
	ChangeEquipToHero(hero,equip,type_num);				//�ı��ɫ����
	/*�����ȥ��װ���Ƿ��������������װ��һ����  evan add 2012.8.31*/
	int type_n = 1;//��Ҵ�װ��
	SuitManage(hero,equip,type_n);
	
}
/*
	������ݣ����������װ�Ĺ���,type=1����Ҵ�װ����type=2�������װ��
	���ʱ�䣺2012.8.31
	����ˣ�Evan
*/
int  SuitManage(Hero *hero,Equipment *equip,int type)
{
	string suit_id = equip->getsuit_id();
	if(suit_id != "0")
	{cout<<"*****************suit start start************************************"<<endl;
		int number = 0;
		string msg = "3";
		msg = msg + intTostring(HERO_SUIT_NUMBER); 
		map<string,int> suits = hero->getsuitlist();
		cout<<"suits_size:"<<suits.size()<<endl;
		map<string,int>::iterator suits_iter;
		suits_iter = suits.find(suit_id);
		if(suits_iter == suits.end())
		{//�������û�д�����װ
			number = 1;
		}else{
		//������ϴ��д�����װ
			number = suits_iter->second;
			switch(type)
			{
				case 1:
					//��Ҵ�װ��
					number = number + 1;
					break;
				case 2:
					//�����װ��
					number = number - 1;
					break;
			}
		}
		suits[suit_id] = number;
		hero->setsuitlist(suits);
		msg = msg + "," + suit_id;
		msg = msg + intTostring(number);
		send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));  //���͸���ǰ���
		cout<<"suits_size:"<<suits.size()<<endl;
		cout<<"msg:"<<msg<<endl;
		cout<<"********************suit end end*********************************"<<endl;
	}
	return 0;
}		
/*
	������ݣ�����װ����������������Ըı�ķ���ʵ�֣�type=-1����װ����type=1:��װ����
	���ʱ�䣺2012.8.23
	����ˣ�Evan
*/
void ChangeEquipToHero(Hero *hero,Equipment *equip,int type)
{   
	MemHero* memHero = hero->memHero;
	if(memHero == NULL)
	{
		return ;
	}

	hero->setLifeUpperVal(memHero->basicHeroData.lifeUpperVal + type*(equip->getlife()));		//��������ֵ
	hero->setMagicUpperVal(memHero->basicHeroData.magicUpperVal + type*(equip->getMagic()));		//ħ������ֵ
	hero->setOutAttack(memHero->basicHeroData.outattack + type*(equip->getoutattack()));		//�⹦����
	hero->setInAttack(memHero->basicHeroData.inattack + type*(equip->getinattack())); 			//�ڹ�����
	hero->setOutDefense(memHero->basicHeroData.outdefense + type*(equip->getoutdefence()));		//�⹦����
	hero->setInDefense(memHero->basicHeroData.indefense + type*(equip->getindefence()));		//�ڹ�����
	hero->setHited(memHero->basicHeroData.hited + type*(equip->gethit()));						//����
	hero->setCrit(memHero->basicHeroData.crit + type*(equip->getcrit()));						//����
	hero->setDodge(memHero->basicHeroData.dodge + type*(equip->getdodge()));					//����
	hero->setTenacity(memHero->basicHeroData.tenacity + type*(equip->gettenacity()));			//����	
}
