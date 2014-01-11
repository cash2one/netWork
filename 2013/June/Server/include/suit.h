#ifndef SUIT
#define SUIT
#include<string>
using namespace std;
class Suit{
	private :
		string suit_id;				//��װId
		int	   type;				//��װ���
		string suit_name;			//��װ����
		int	   hp;					//��װ��������ֵ����ֵ
		int    mp;					//��װ��������ֵ����ֵ
		int    outHrt;				//��װ�����⹦�˺�����ֵ
		int    inHrt;				//��װ�����ڹ��˺�����ֵ
		int    outAttVal;			//��װ�����⹦��������ֵ
		int    inAttVal;			//��װ�����ڹ���������ֵ
		int    outDefVal;			//��װ�����⹦��������ֵ
		int    inDefVal;			//��װ�����ڹ���������ֵ
		int    hit;					//��װ���������е���ֵ
		int    crit;				//��װ�����ı�������ֵ
		int    dodge;				//��װ���������ܵ���ֵ
		int    tenacity;			//��װ���������Ե���ֵ
	public :
		Suit(string _suit_id,int _type,string _suit_name,int _hp,int _mp,int _outHrt,int _inHrt,int _outAttVal,int _inAttVal,int _outDefVal,int _inDefVal,
			int _hit,int _crit,int _dodge,int _tenacity);
			
			string getsuit_id(void);			//��װId
			int	   gettype(void);				//��װ���
			string getsuit_name(void);			//��װ����
			int	   gethp(void);					//��װ��������ֵ����ֵ
			int    getmp(void);					//��װ��������ֵ����ֵ
			int    getoutHrt(void);				//��װ�����⹦�˺�����ֵ
			int    getinHrt(void);				//��װ�����ڹ��˺�����ֵ
			int    getoutAttVal(void);			//��װ�����⹦��������ֵ
			int    getinAttVal(void);			//��װ�����ڹ���������ֵ
			int    getoutDefVal(void);			//��װ�����⹦��������ֵ
			int    getinDefVal(void);			//��װ�����ڹ���������ֵ
			int    gethit(void);				//��װ���������е���ֵ
			int    getcrit(void);				//��װ�����ı�������ֵ
			int    getdodge(void);				//��װ���������ܵ���ֵ
			int    gettenacity(void);			//��װ���������Ե���ֵ	
};
#endif