#include "festivalActive.h"
#include "bag_operator.h"
using namespace std;
extern Hero *pg_hero;
extern char g_out_buf[20480];
extern FestivalGoods festivalGoods;

void XmasRewardReceive(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	// MSG_CHAR_END(char *goodsid)							//�ͻ��˷����������id,Ŀǰ������û�������ļ�,����ôд,�ȷ��������������ļ���ɾ��
	
	if (pg_hero->getFestivalRewardFlag()==0)			//ʥ������û����ȡ
	{
		if (saveGoodsInBag(pg_hero,"b_dj_119_100",1))			//�������������
		{			
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,XMAS_REWARD,2);
			send_msg(pg_hero->getFd(),g_out_buf);
			pg_hero->setFestivalRewardFlag(1);
		}		
	}
}

void XmasRewardResponse(char *buffer)					//����ʥ�������Ƿ������ȡ
{
	if (pg_hero->getFestivalRewardFlag()==1)			//ʥ�������Ѿ���ȡ����
	{		
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,XMAS_REWARD,0);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else												//ʥ��������δ��ȡ
	{	
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,XMAS_REWARD,1);
		send_msg(pg_hero->getFd(),g_out_buf);		
	}
}

void XmasFasionReceive(char *buffer)
{
	int index[6];
	MSG_BEGIN(buffer,g_msg_len)
	
	cout<<"9,19";
	
	for (int i=0;i<festivalGoods.num;i++)
	{
		MSG_INT_MAX(index[i],95);
		cout<<","<<index[i];
	}
	cout<<endl;
	
	Bag *bag=pg_hero->getBag();
	
	if (bag==NULL)
	{
		return;
	}
	
	for (int i=0;i<festivalGoods.num;i++)
	{
		if (!bag->test(index[i],festivalGoods.goods[i]))
		{
			cout<<"jolly:"<<festivalGoods.goods[i]<<" is not verify festivalActive 57"<<endl;
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,XMAS_FASION,0);
			send_msg(pg_hero->getFd(),g_out_buf);
			return;
		}
	}

	for (int i=0;i<festivalGoods.num;i++)
	{
		useBagGoods(pg_hero,festivalGoods.goods[i],index[i],1);
	}
	if (saveGoodsInBag(pg_hero,festivalGoods.rewardGoods,1))
	{								
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,XMAS_FASION,1);
		send_msg(pg_hero->getFd(),g_out_buf);
	}	
}