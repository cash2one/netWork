#include"equip_config.h"
#include <string.h>

Equip_config::Equip_config(char* _id,char* _name,int _grade,int _order,int _rank,int _type,char* _party,int _suit_type,char* _suit_id,
						int _life,int _inattack,int _outattack,int _indefence,int _outdefence,
						int _genuine,int _crit,int _hit,int _dodge,int _tenacity,int _durability,int _priceBound,int _price,int _goldBound,int _gold,int _sellPrice,\
						int _time,char *_photoId,int _move,int _culianCost,int _jinglianCost,int _hole,int _attrNumber)
{
	strncpy(id , _id,sizeof(id));
	strncpy(name , _name,sizeof(name));
	grade = _grade;
	order = _order;
	rank = _rank;
	type = _type;
	strncpy(party , _party,sizeof(party));
	suit_type = _suit_type;
	strncpy(suit_id , _suit_id,sizeof(suit_id));
	life = _life;
	inattack = _inattack;
	outattack = _outattack;
	indefence = _indefence;
	outdefence = _outdefence;
	genuine = _genuine;
	crit = _crit;
	hit = _hit;
	dodge = _dodge;
	tenacity = _tenacity;
	durability = _durability;
	priceBound=_priceBound;
	price = _price;
	goldBound=_goldBound;
	gold=_gold;
	sellPrice=_sellPrice;
	time=_time;
	strncpy(photoId , _photoId,sizeof(_photoId));
	move=_move;
	culianCost=_culianCost;
	jinglianCost=_jinglianCost;
	hole=_hole;
	attrNumber=_attrNumber;
}
char* Equip_config::getid(void)           //װ��ID
{
		return id;
}
char* Equip_config::getname(void)		 //װ������
{
		return name;
}
int    Equip_config::getgrade(void)        //װ���ȼ�
{
		return grade;
}
int Equip_config::getOrder(void)			//װ������
{
	return order;
}
int	   Equip_config::getrank(void)         //װ������
{
	return rank;
}
int    Equip_config::gettype(void)         //װ������
{
	return type;
}
char*  Equip_config::getparty(void)        //װ������
{
	return party;
}
int    Equip_config::getsuit_type(void)    //��װ���
{
	return suit_type;
}
char* Equip_config::getsuit_id(void)      //��װID
{
	return suit_id;
}
int    Equip_config::getlife(void)         //����ֵ
{
	return life;
}
int    Equip_config::getinattack(void)     //�ڹ�����
{
	return inattack;
}
int    Equip_config::getoutattack(void)    //�⹦����
{
	return outattack;
}
int    Equip_config::getindefence(void)    //�ڹ�����
{
	return indefence;
}
int    Equip_config::getoutdefence(void)   //�⹦����
{
	return outdefence;
}
int    Equip_config::getgenuine(void)      //����
{
	return genuine;
}
int    Equip_config::getcrit(void)         //����
{
	return crit;
}
int    Equip_config::gethit(void) 		 //����
{
	return hit;
}
int    Equip_config::getdodge(void)        //����
{
	return dodge;
}
int    Equip_config::gettenacity(void) 	 //����
{
	return tenacity;
}
int	   Equip_config::getdurability(void)   //�;ö�
{
	return durability;
}
int	   Equip_config::getMoneyBound(void) 
{
	return priceBound;
}
int	   Equip_config::getMoney(void)        //�۸�
{
	return price;
}
int		Equip_config::getgoldBound(void)  
{
	return goldBound;
}
int		Equip_config::getgold(void)  
{
	return gold;
}

int Equip_config::getPrice(void)      //������Ϸ�Ҽ۸�
{
	return sellPrice;
}

int Equip_config::getTime(void)
{
	return time;
}

char *Equip_config::getPhotoId(void)
{
	return photoId;
}

int Equip_config::getMove(void)
{
	return move;
}

int Equip_config::getCulianCost(void)
{
	return culianCost;
}

int Equip_config::getJinglianCost(void)
{
	return jinglianCost;
}

int Equip_config::getHole(void)
{
	return hole;
}
int Equip_config::getAttrNumber(void)
{
	return attrNumber;
}