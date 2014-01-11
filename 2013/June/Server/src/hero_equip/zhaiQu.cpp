#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"hero.h"
#include"equipment.h"
using namespace std;
extern char g_out_buf[20480];
bool EquipOperateZQ(Hero *hero, Equipment *equipment, char* goodsid,int index)
{		
	if (hero==NULL||equipment==NULL)
	{
		return 0;
	}

	if(strlen(goodsid) != 12)	
	{
		return false;
	}
	
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		cout<<"jolly:bag is null in zhaiqu.cpp 27"<<endl;
		return false;
	}
	
	int num = equipment->getBsNumByTy(goodsid);
	cout<<"num:"<<num<<endl;
	if(num!=1)	//��ʾ�����쳣
	{
		cout<<"same jewel is error:"<<num<<endl;
		return 0; 
	}
	
	if (!bag->bagIsFull(1))
	{
		if (equipment->testDiamon(index,goodsid))
		{
			if (saveGoodsInBag(hero,goodsid,1)) //��ժȡ��ı�ʯ�ŵ�������
			{
				equipment->delBsNumByTy(goodsid);
				
				equipment->diamonOff(hero,index);
				//����Ǵ������ϵ�װ����������Ƕ����ͬʱ�޸���������,װ���Ƿ������� 0:�ڱ����ڣ�1:������
				if(equipment->getIsBag() == 1)
				{
					hero->send_msg_att();	//���¿ͻ��˵������������
				}				
				
				memset(g_out_buf,0,sizeof(g_out_buf));
				equipment->msg_return_equipInform(g_out_buf, sizeof(g_out_buf));
				send_msg(hero->getFd(), g_out_buf);	
			
				if (goodsid[10] - '0' == 3)
				{
					equipment->zhaiQuFourDiamon();
				}
				
				return true;
			}
			else 
			{
				cout<<"jolly:savegoodsinbag in zhaiqu.cpp 48"<<endl;
				return false;
			}
		}
		else
		{
			cout<<"jolly: testDiamon error in zhaiqu.cpp 55"<<endl;
			return false;
		}		
	}
	else
	{
		cout<<"jolly:bag is full in zhaiqu.cpp 59"<<endl;
		return false;
	}
}