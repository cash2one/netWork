#include"ointment.h"
#include<iostream>
using namespace::std;
Ointment::Ointment(string _id,string _name,int _cd,int _sellPriceBoundGold,int _ointmentType,			
		int _sellPriceNoBoundGold,int _sellPriceBoundMoney,int _sellPriceNoBoundMoney,
		int _levelLimits,int _pileUp,int _type,int _value,int _level,int _factor)	
		{
			id=_id;															
			name=_name;	
			cd=_cd;  
			sellPriceBoundGold	=_sellPriceBoundGold;		//npc���۳��۸�	��Ԫ��				
			sellPriceNoBoundGold=_sellPriceNoBoundGold;	 //npc���۳��۸�	�ǰ�Ԫ��
			sellPriceBoundMoney=_sellPriceBoundMoney;	//npc���۳��۸�	����Ϸ��
			sellPriceNoBoundMoney	=_sellPriceNoBoundMoney;//npc���۳��۸�	�ǰ���Ϸ��
			levelLimits	=_levelLimits;	//�ȼ�����							
			pileUp=_pileUp;//�ѵ�����	
			type=_type;//ҩƷ����	
			ointmentType=_ointmentType;
			value=_value;//ҩƷӰ���ɫ������ֵ
			level = _level;//ҩƷ�ȼ�
			factor=_factor;
		}
string Ointment::getId(void)
{
	return	id;
}		
string Ointment::getIdentity(void)
{
	return	id;
}													
string Ointment::getName(void)
{
	return name;
}	
int Ointment::getCd(void)
{
	return cd;
}	          			
int Ointment::getSellPriceBoundGold(void)
{
	return sellPriceBoundGold;
}					
int Ointment::getSellPriceNoBoundGold(void)
{
	return sellPriceNoBoundGold;
}	
int Ointment::getSellPriceBoundMoney(void)
{
	return sellPriceBoundMoney;
}	
int Ointment::getSellPriceNoBoundMoney(void)
{
	return sellPriceNoBoundMoney;
}	
int Ointment::getLevelLimits(void)
{
	return levelLimits;
}							
int Ointment::getPileUp(void)
{
	return pileUp;
}	
int Ointment::getType(void)
{
	return type;
}	
int Ointment::getOintmentType(void)
{
	return ointmentType;
}	
int Ointment::getValue(void)
{
	return value;
}	
int Ointment::getLevel(void)
{
	return level;
}

int Ointment::getFactor(void)
{
	return factor;
}