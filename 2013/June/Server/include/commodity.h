#ifndef COMMODITY_
#define COMMODITY_

typedef struct StallGoods_T
{
	char typeId[20];//����id
	char goodsId[40];  //����Ʒʵ��id
	int number; //��Ʒ����
	int type; //��Ʒ����
	int price; //��Ʒ�۸�
	int goodsIndexInBag; //����Ʒ�ڱ����е�
	int priceFlag;		//�۸��־ 1Ϊ���� 2ΪԪ��
	StallGoods_T()
	{
		strncpy(typeId,"0",sizeof(typeId));
		typeId[sizeof(typeId)-1]='\0';
		strncpy(goodsId,"0",sizeof(goodsId));
		typeId[sizeof(goodsId)-1]='\0';
		number=0;
		type=0;
		price=0;
		goodsIndexInBag=-1;
		priceFlag=0;
	}
	void initStallGoods(void)
	{
		strncpy(typeId,"0",sizeof(typeId));
		typeId[sizeof(typeId)-1]='\0';
		strncpy(goodsId,"0",sizeof(goodsId));
		typeId[sizeof(goodsId)-1]='\0';
		number=0;
		type=0;
		price=0;
		priceFlag=0;
		goodsIndexInBag=-1;
	}
}StallGoods;
//����̯λ
typedef struct PrivateStall_T
{
	char privateStallName[50]; //̯λ��
	StallGoods stallGoods[24];
	Point pt;  //���̵�����㼴̯���ĵ�ǰλ��
	int number;			//��̯��������
	void initPrivateStall(void)
	{
		strncpy(privateStallName,"0",sizeof(privateStallName));
		number=0;
	}
}PrivateStall;
#endif