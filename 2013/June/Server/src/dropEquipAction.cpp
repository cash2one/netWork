/************************************************************
	�ļ�����dropEquipAction.cpp
	�ļ����ã�������ɱ����װ�ص�����
	���ߣ�chenzhen
	�������ڣ�2012.12.3
************************************************************/
#include"dropEquipAction.h"
#include"equipment.h"
#include"libev.h"
extern map<string,Equipment*> dropEquipMent;
void dropEquipCalBak(struct ev_loop *loop,ev_timer *think,int revents)
{
	map<string,Equipment*>::iterator equip_it;
	Equipment *timeOutEquip;
	
	/*����ͣ*/
	ev_timer_stop(loop,think);		
	
	/*���˼������ָ��*/
	timeOutEquip = (Equipment *)think->target;
	
	
	/*�ж�˼������ָ���Ƿ�Ϊ��*/
	if(timeOutEquip == NULL)
	{
		return;
	}	
	
	
	timeOutEquip->disperMsg();
	
	equip_it = dropEquipMent.find(timeOutEquip->getentityid());
	if(equip_it != dropEquipMent.end())
	{
		dropEquipMent.erase(equip_it);
	}		
	delete timeOutEquip;
	timeOutEquip = NULL;
}
	
