#ifndef RIDE_H
#define RIDE_H
#include <iostream>
#include <map>
#include <vector>
#include "hero.h"
#include "data_structure_struct.h"
#include "ride_config.h"
using namespace std;

class Ride
{
private:
	RideData ridedata;
public:
	Ride(void);
	Ride(RideData rideData);
		
	void createRide(Ride_Config *ride_config,char *id);										//ʹ������
		
	RideData getMemStruct(void);															//ȡ���ṹ��
	
	int getExpNow(void);
	int getExpMax(void);
	char *getEquipmentIdentity(int index);
	int getCost(void);	
	char* getPhotoId(void);
	int getMove(void);
	int getFinalGrid(void);
	int getFinalSkillStage(void);
	int getQuality(void);
	char *getIdentity(void);
	char *getNickName(void);
	int getLevel(void);
	int getHp(void);
	int getMp(void);
	int getOutAttVal(void);
	int getInAttVal(void);
	int getInDefVal(void);
	int getOutDefVal(void);
	int getHit(void);
	int getCrit(void);
	int getDodge(void);
	int getTenacity(void);
	
	int getRefreshMoney(int number);														//����ˢ�����ռ������ĵ�Ǯ
	
	void gainExp(Hero *hero,int exp,int flag);												//��þ���,ֻ�г�ս������ܻ�þ���
	void equalAtt(Ride_Config *ride_config);
	void minusAtt(Ride_Config *ride_config);
	void decreaseAtt(Hero *hero);															//ȥ�����������ӵ�����
	void increaseAtt(Hero *hero);															//�������������ӵ�����	
	bool ifFull(void);																		//�ж������Ƿ��������� �����ﷵ��true û�з���false
	bool judgeEquipWear(int index);															//�ж������Ƿ���װ�� ���˷���true û�з���false
	void wearEquip(Equipment *equipment,int index);											//���ﴩװ��,�ı���������
	void takeOffEquip(Equipment *equipment,int index);										//������װ��,�ı���������
	bool evolutionIncrease(int number,Hero *hero);											//�����ý��׵�,���Խ��׷���true,���ܽ��׷���false
	void initCost(void);																	//��ʼ��������׻���Ԫ��
	void evolutionIncreaseCost(void);														//�������ʹ��Ԫ������
	void refreshSkill(vector<int> flag,Hero *hero);											//ϴ������
	void learnFinalSkill(void);																//�յ�7��ѧϰ���ռ���
	void openOneSkillGrid(void);															//�������ռ��ܵĿ�
	void finalSkillEffect(void);															//���ռ��ܴ���Ч��
	void finalSkilldisapear(void);															//���ռ�����ʧЧ��
	int countPower(void);																	//������ս��
	
	void ride_msg_return(char *msg,int len,Hero *hero);										//ʹ�����ﷵ��������ϸ��Ϣ
	void ride_wear_equip(char *msg,int len,int index,char *identity,char *id);				//���ﴩװ������
	void ride_takeoff_equip(char *msg,int len,int index,char *identity,char *id);			//������װ������
	void ride_evolution_return(char *msg,int len,int number);								//���������Ϣ����
	void ride_finalSkill_return(char *msg,int len);											//����ϴ������,��Ϣ����
};

#endif