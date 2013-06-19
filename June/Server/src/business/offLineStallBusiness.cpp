#include"anyBusiness.h"

extern map<string ,PrivateStall* > offLineStall;//����̯λ
extern map<string, Hero> heroId_to_pHero;
extern int sock_fd;
//��������
void askFaceplate(char *buff)
{
	Role* role=fd_to_pRole.find(sock_fd)->second;
	Hero* hero=heroId_to_pHero.find(role->getActive_heroId())->second;
	if(hero->useBoundGold())
	{
		//�����success
	}
	else
	{
		//fail
	}
}

//��̯
void offLineCreateStall(char *buff)
{
	
	string heroId;
	string goodsId;
	PrivateStall *privateStall=new PrivateStall();
	//��ȡgoodsId�ֱ�ʵ������Ʒ����̯λ����
	for()
	{
		Commodity stallCommodity;
		stallCommodity.num;
		stallCommodity.money;
		stallCommodity.comId;
		privateStall->container.insert(pair<string ,Commodity>(goodsId,stallCommodity));
	}
	offLineStall.insert(pair<string ,*PrivateStall>(heroId,privateStall));

}
//��������
void offLineStallBusiness(char *buff)
{
	string buyHeroId;  //�������id
	string buyGoodsId; //������Ʒid
	int buyGoodsNum; //������Ʒ����
	string sellerId; //����id
	extern map<string, Hero*> heroId_to_pHero;
	
	map<string ,PrivateStall *>::iterator stallIter=offLineStall.find(sellerId);
	if(stallIter==offLineStall.end())
	{
		cout<<"there is no this offLineStall in  stallBusiness.cpp :34"<<endl;
		return;
	}
	
	map<string,StallCommodity>container; //��Ʒ����
	set<AuctionCommodity>record; //�۳���¼
	PrivateStall *privateStall=stallIter->second;
	set<StallCommodity > ::iterator iterContainer=privateStall->container.find(buyGoodsId);
	if(iterContainer==privateStall->container.end())
	{
		cout<<"there is no this Commodity in  stallBusiness.cpp :45"<<endl;
		return;
	}
	StallCommodity stallCommodity=iterContainer->second();//��Ҫ������Ʒ
	map<string, Hero *>::iterator heroIter=heroId_to_pHero.find(buyHeroId);
	if(heroIter==heroId_to_pHero.end())
	{
		cout<<"there is no buyer in  stallBusiness.cpp :52"<<endl;
		return;
	}
	Hero *buyer=heroIter->second;//������
		//�������
	if(goods->boundGold)
	{
		if(hero->money->useBoundGold())
		{
			//���׳ɹ�
			//�����ұ�������Ʒת������ұ���
		}	
		else
		{
			//ʧ��
			//������ҽ���ʧ�ܣ�Ǯ������
		}
	}
	if(goods->gold)
	{
		if(hero->money->useGold())
		{
		
		}
		else
		{
		
		}
	}
	if(goods->boundMoney)
	{
		if(hero->money->useBoundGameMoney())
		{
		
		}
		else
		{
		
		}
	}
	if(goods->money)
	{
		if(hero->money->useGameMoney())
		{
		
		}
		else
		{
		
		}
	}
}

//��Ʒ�ļ�
void offLineChangeStallCommodityPrice(char *buff)
{
	string stallCommodityId;
	string heroId;
	
	//��Ϣ����
	
	if(offLineStall.find(heroId)==offLineStall.end())
	{
		cout<<"cant find this privateStall   in stallBusiness.cpp:120"<<endl;
	}
	PrivateStall *privateStall=offLineStall.find(heroId)->second;
	if(privateStall->container.find(stallCommodityId)==privateStall->container.end())
	{
		
	}
	StallCommodity stallCommodity=privateStall->container.find(stallCommodityId)->second;
	stallCommodity.num=num; //�޸���Ʒ����
		int num;
	int boundGold;				//�޸���Ʒ�۸�
	int gold;
	int boundMoney;
	int money;
	
}

//��Ʒ�¼�
void offLineDeleteStallCommodity(char *buff)
{
	string stallCommodityId;
	string heroId;
	
	//��Ϣ����
	
	if(offLineStall.find(heroId)==offLineStall.end())
	{
		cout<<"cant find this privateStall   in stallBusiness.cpp:120"<<endl;
		return;
	}
	PrivateStall *privateStall=offLineStall.find(heroId)->second;
	if(privateStall->container.find(stallCommodityId)==privateStall->container.end())
	{
		cout<<"error"<<endl;
		return;
	}
	privateStall->container.erase(stallCommodityId);
	string msg;//success
	send(msg,sock_fd);
}

//��̯
void offLineDeleteStall(char *buff)
{
	string heroId;
	if(offLineStall.find(heroId)==offLineStall.end())
	{
		return;
	}
	offLineStall.erase(offLineStall.find(heroId));
}
