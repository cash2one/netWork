#include<iostream>
#include<map>
#include <string.h>
#include"hero.h"

//����׼��
int Hero::prepareRide()
{
	//��������״̬
	if (memHero->rideState == RIDE_STATE_RIDING)
	{
		prepareRideSecond = 0;
		return 2;
	}
	
	if (ride == NULL)
	{
		//����������
		return 3;
	}
	
	if (ride->ifFull()==false)
	{
		//û�г�ս���
		return 4;	
	}
	
	if (heroState==5)
	{
		//��̯��
		return 6;
	}
	
	//�Ѿ���������״̬
	if (memHero->rideState == RIDE_STATE_PREPARE)
	{
		//�Ѿ�׼����������׼��һ��
		prepareRideSecond = MY_TV_SEC;
		memHero->rideState = RIDE_STATE_PREPARE;
		return 1;
	}
	
	//δ����״̬
	if (memHero->rideState == RIDE_STATE_FREE)
	{	
		//׼����˳ɹ�
		prepareRideSecond = MY_TV_SEC;
		memHero->rideState = RIDE_STATE_PREPARE;
		return 0;
	}
	
	//��ǰ�����״̬����,���о���
	prepareRideSecond = MY_TV_SEC;
	memHero->rideState = RIDE_STATE_PREPARE;
	return 0;
}

//��ϳ������
int Hero::breakRide()
{
	if (memHero->rideState == RIDE_STATE_FREE)
	{
		prepareRideSecond = 0;
		return 0;
	}
	if (memHero->rideState == RIDE_STATE_PREPARE)
	{
		prepareRideSecond = 0;
		memHero->rideState = RIDE_STATE_FREE;
		return 0;
	}
	if (memHero->rideState == RIDE_STATE_RIDING)
	{
		return 1;
	}
	return 2;
}

//��ʼ���
int Hero::startRide()
{
	if (memHero->rideState == RIDE_STATE_RIDING)
	{
		prepareRideSecond = 0;
		return 2;
	}
	
	if (ride == NULL)
	{
		//����������
		return 3;
	}
	
	if (ride->ifFull() == false)
	{
		//û�г�ս���
		return 4;	
	}
	
	if (memHero->rideState == RIDE_STATE_FREE)
	{
		//ǰ��û�г���׼��
		prepareRideSecond = 0;
		return 6;
	}
	
	if (memHero->rideState == RIDE_STATE_PREPARE)
	{
		//�����׼��ʱ���Ƿ��㹻
		if (MY_TV_SEC - prepareRideSecond >= RIDE_PREPARE_TIME)
		{
			prepareRideSecond = 0;
			memHero->rideState = RIDE_STATE_RIDING;
			// lastSpeed = speed;
			
			if (strlen(memHero->wagonId) != 0)
			{
				speed = NORMAL_WAGON_SPEED;
			} else {
				// speed = NORMAL_HERO_SPEED + ride->getActiveMove();
				speed = NORMAL_HERO_SPEED + ride->getMove();
			}
			hero_move_cb(loops, &moveTimer, 2);
			setLastSpeed(getSpeed());
			return 0;
		} else {
			//���׼��ʱ��δ��
			return 7;
		}
	}
	//���״̬�д�
	memHero->rideState = RIDE_STATE_FREE;
	return 8;
}

//����
int Hero::stopRide()
{
	if (memHero->rideState != RIDE_STATE_RIDING)
	{
		return 1;
	}
	else if (strlen(memHero->wagonId) != 0)
	{
		speed = NORMAL_WAGON_SPEED;
	} else {
		speed = NORMAL_HERO_SPEED;
	}
	memHero->rideState = RIDE_STATE_FREE;
	hero_move_cb(loops, &moveTimer, 2);
	setLastSpeed(getSpeed());
	return 0;
}

//��ȡ���״̬
int Hero::getRideState()
{
	return memHero->rideState;
}
