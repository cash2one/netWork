#include"suit.h"
Suit::Suit(string _suit_id,int _type,string _suit_name,int _hp,int _mp,int _outHrt,int _inHrt,int _outAttVal,int _inAttVal,int _outDefVal,int _inDefVal,
			int _hit,int _crit,int _dodge,int _tenacity)
{
	suit_id = _suit_id;				//��װId
	type = _type;					//��װ���
	suit_name = _suit_name;			//��װ����
	hp = _hp;						//��װ��������ֵ����ֵ
	mp = _mp;						//��װ��������ֵ����ֵ
	outHrt = _outHrt;				//��װ�����⹦�˺�����ֵ
	inHrt = _inHrt;					//��װ�����ڹ��˺�����ֵ
	outAttVal = _outAttVal;			//��װ�����⹦��������ֵ
	inAttVal = _inAttVal;			//��װ�����ڹ���������ֵ
	outDefVal = _outDefVal;			//��װ�����⹦��������ֵ
	inDefVal = _inDefVal;			//��װ�����ڹ���������ֵ
	hit = _hit;						//��װ���������е���ֵ
	crit = _crit;					//��װ�����ı�������ֵ
	dodge = _dodge;					//��װ���������ܵ���ֵ
	tenacity = _tenacity;			//��װ���������Ե���ֵ

}
string Suit::getsuit_id(void)			//��װId
{
	return suit_id;
}
int	   Suit::gettype(void)				//��װ���
{
	return type;
}
string Suit::getsuit_name(void)			//��װ����
{
	return suit_name;
}
int	   Suit::gethp(void)					//��װ��������ֵ����ֵ
{
	return hp;
}
int    Suit::getmp(void)					//��װ��������ֵ����ֵ
{
	return mp;
}
int    Suit::getoutHrt(void)				//��װ�����⹦�˺�����ֵ
{
	return outHrt;
}
int    Suit::getinHrt(void)				//��װ�����ڹ��˺�����ֵ
{
	return inHrt;
}
int    Suit::getoutAttVal(void)			//��װ�����⹦��������ֵ
{
	return outAttVal;
}
int    Suit::getinAttVal(void)			//��װ�����ڹ���������ֵ
{
	return inAttVal;
}
int    Suit::getoutDefVal(void)			//��װ�����⹦��������ֵ
{
	return outDefVal;
}
int    Suit::getinDefVal(void)			//��װ�����ڹ���������ֵ
{
	return inDefVal;
}
int    Suit::gethit(void)				//��װ���������е���ֵ
{
	return hit;
}
int    Suit::getcrit(void)				//��װ�����ı�������ֵ
{
	return crit;
}
int    Suit::getdodge(void)				//��װ���������ܵ���ֵ
{
	return dodge;
}
int    Suit::gettenacity(void)			//��װ���������Ե���ֵ
{
	return tenacity;
}