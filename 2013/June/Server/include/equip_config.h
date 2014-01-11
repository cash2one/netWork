#ifndef _EQUIP_
#define _EQUIP_
#include<string>
using namespace std;
class Equip_config
{
private:
		char id[20];           //װ��ID
		char name[50];		 //װ������
		int    grade;        //װ���ȼ�
		int order;			//װ������
		int    rank;         //װ������
		int	   type;         //װ������
		char party[10];        //װ������
		int    suit_type;    //��װ���
		char suit_id[20];      //��װID		
		int    life;         //����ֵ
		int    inattack;     //�ڹ�����
		int    outattack;    //�⹦����
		int    indefence;    //�ڹ�����
		int    outdefence;   //�⹦����
		int    genuine;      //����
		int    crit;         //����
		int    hit; 		 //����
		int    dodge;        //����
		int    tenacity; 	 //����
		int	   durability;   //�;ö�
		int priceBound;
		int	   price;        //�۸�
		int goldBound;
		int    gold;		 //Ԫ���۸�
		int sellPrice;
		int time;				//ʱװʱ��
		char photoId[10];		//ͼƬid	
		int move;				//�ƶ��ٶ�
		int culianCost;
		int jinglianCost;
		int hole;
		int attrNumber;
		
public:
		Equip_config(char* _id,char* _name,int _grade,int _order,int _rank,int _type,char* _party,int _suit_type,char* _suit_id,
						int _life,int _inattack,int _outattack,int _indefence,int _outdefence,
						int _genuine,int _crit,int _hit,int _dodge,int _tenacity,int _durability,int _priceBound,int _price,int _goldBound,int _gold,int _sellPrice,\
						int _time,char *_photoId,int _move,int _culianCost,int _jinglianCost,int _hole,int _attrNumber);
		char* getid(void);           //װ��ID
		char* getname(void);		 //װ������
		int    getgrade(void);        //װ���ȼ�
		int getOrder(void);			//װ������
		int    getrank(void);         //װ������
		int	   gettype(void);         //װ������
		char* getparty(void);        //װ������
		int    getsuit_type(void);    //��װ���
		char* getsuit_id(void);      //��װID
		int    getlife(void);         //����ֵ
		int    getinattack(void);     //�ڹ�����
		int    getoutattack(void);    //�⹦����
		int    getindefence(void);    //�ڹ�����
		int    getoutdefence(void);   //�⹦����
		int    getgenuine(void);      //����
		int    getcrit(void);         //����
		int    gethit(void); 		 //����
		int    getdodge(void);        //����
		int    gettenacity(void); 	 //����
		int	   getdurability(void);   //�;ö�
		int	   getMoneyBound(void) ;	
		int	   getMoney(void);        //�۸�
		int		getgoldBound(void) ;
		int 	getgold(void);
		int getPrice(void);
		int getTime(void);
		char *getPhotoId(void);
		int getMove(void);
		int getCulianCost(void);
		int getJinglianCost(void);
		int getHole(void);
		int getAttrNumber(void);
};
#endif
