#ifndef GOODS_CONFIG_H
#define GOODS_CONFIG_H
#include<string>
using namespace std;
class Goods_Config
{
private:
	char* id;				//��Ʒid		
	char* name;			//��Ʒ����
	char* effect;			//��ƷЧ��
	int order; 				//�������
	int repeat;				//�ѵ�����
	int type;				//����
	int levelLimit;			//�ȼ�����
	int gold;				//����Ԫ���۸�
	int goldBound;			//�����Ԫ���۸�
	int money;				//����ǰ���Ϸ�Ҽ۸�
	int moneyBound;			//�������Ϸ�Ҽ۸�
	int price;				//������Ϸ�Ҽ۸�

	
public:
		Goods_Config(char* _id,char* _name,char* _effect,int _order,int _repeat,int _type,int _levelLimit,int _gold,int _goldBound,int _money,int _moneyBound,int _price);
		char* getId(void);           //��Ʒid
		char* getName(void);		 //��Ʒ����
		char* getEffect(void);        //��ƷЧ��
		int getOrder(void);	//�������
		int getRepeat(void);         //�ѵ�����
		int	getType(void);         //����
		int getLevelLimit(void);        //�ȼ�����
		int getGold(void);    //����Ԫ���۸�
		int getGoldBound(void);
		int getMoneyBound(void);
		int getMoney(void);      //������Ϸ�Ҽ۸�
		int getPrice(void);
};
#endif
