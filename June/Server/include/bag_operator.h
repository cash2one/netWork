#ifndef BAG_OPERATOR_H
#define BAG_OPERATOR_H
#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <set>
#include <vector>
#include "droplist_configuration.h"
#include "monster_configuration.h"
#include "monsterBase.h"
#include "hero.h"
#include "ointment.h"
#include "pick.h"
#include "map_inform.h"
#include "nbox.h"
#include "task.h"
#include "user_role_manage_equip.h"
#include "bag.h"
#include "warehouse_operator.h"

void mulityUse(char *buffer);
void testGoods(char *buffer);
void bagArrang(char *buffer);
void bag_operator(char *buffer);
void destoryGoods(char *buffer);
void getEquipInform(char *buffer);
void bagFlagSet(char *buffer);
bool expand(Hero *hero,int num);
void expandReturn(char *buffer);
void useExpTimesReturn(char *buffer);
void bag_useAllGoods(char *buffer);
void setGoodsUnBound(char *buffer);
int getGemType(char* goodsid);
int getGemEffect(char* goodsid);
int goodsReturnInt(char* goodsid,int index);			//ȡ����Ʒ��Ч��,goodsidΪ��Ʒid,indexΪ��ȡ�õĵڼ�λ����,��0��ʼ
int goodsReturnInt(Goods_Config *goods,int index);		//ȡ����Ʒ��Ч��,goodsΪ��Ʒʵ��,indexΪ��ȡ�õĵڼ�λ����,��0��ʼ
void goodsReturnVector(Goods_Config *goods,vector<string> &effects);	//ȡ����Ʒ��Ч��,�������е�effect
int getGoodsType(char* goodsid);
void testPet(char *buffer);
void testMoney(char *buffer);
void modifyCamp(Hero *hero);
void testHeroExp(char *buffer);
void useAllGoods(Hero *hero,char* identity);
bool useRandomGoods(Hero *hero,char* goodsid,int index);
void useRewardBagWithMoney(Hero *hero,char* goodsid,int index);
void useMoneyBox(Hero *hero,char *goodsid,Point pt);
void taskGoodsSpecialPosUse(Hero *hero, char* goodsId, int index);								//��ָ���ص�ʹ�õ�������ߵ�ʹ��
void heroExpDrug(Hero *hero,char* goodsid,int index,int number);
void petExpDrug(Hero *hero,char* goodsid,int index,int number);
void useRandomEquip(Hero *hero,char* goodsid,int index);
void useEquipBag(Hero *hero,char* goodsid,int index);
void useExpTimes(Hero *hero,char *goodsid,int index);										//����ʹ��˫����������������������	
void useRewardBag(Hero *hero,char* goodsid,int index);
void useChunjieBag(Hero *hero,char* goodsid,int index);
void usePopularity(Hero *hero,char* goodsid,int index,int number);
void useDecreaseCrime(Hero *hero,char* goodsid,int index,int number);
void useRideExp(Hero *hero,char* goodsid,int index,int number);
bool usePetAgg(Hero *hero,char* goodsid,int index);											//ʹ�ó��ﵰ
void useMoneyBag(Hero *hero,char* goodsid,int index,int number);											//ʹ��Ǯ��
bool saveGoodsInBag(Hero *hero,char* goodsid,int num,int accountFlag=0);										//����Ʒ�����뱳��	
bool splitGoods(Hero *hero,int index,int num);													//������ֹ���
void destoryBagGoods(Hero *hero,int index,char* identity);										//�ݻ���Ʒ
bool sellGoodsFromBag(Hero *hero,int index,char* id,int &money);											//����Ʒ
bool saveBagGoods(Hero *hero,char* goodsid,int type,int num,char* identity,int accountFlag);					//������Ʒ����
bool saveBagGoods(Hero *hero,char* goodsid,int type,int num,char* identity,int index,int accountFlag);		//������Ʒ����
void destoryAllBagGoods(Hero *hero,char* identity);											//�ݻٱ��������еĸ���Ʒ
int useBagGoods(Hero *hero,char* goodsid,int number);											//ͨ��goodsidʹ����Ʒ
int useBagGoods(Hero *hero,const char* goodsid,int index,int num,bool sendFlag=true);									//ʹ�ñ����е���Ʒ,ɾ����Ʒ
bool useGoodsBoth(Hero *hero,char *goodsid,int number);											//ʹ����Ʒ,���������еĺͲֿ��е�
bool takeOffEquipToBag(Hero *hero,int index,Equipment* equipment);								//��װ��,�ϵ�������
bool takeOffEquipToBag(Hero *hero,Equipment* equipment);										//��װ��,����Ҫ����ȫ���е�����
Equipment* getEquipFromBag(Hero *hero,int _index);												//ȡװ��ʵ��
bool tradeSuccessInsert(Hero *hero,vector<Trade_Goods> goods);									//���׳ɹ�,�򱳰��в�����Ʒ
void send_msg_addgoods(Hero *hero,int num,int type,int index,char* goodsid,char* identity);	//������Ʒ���뱳������Ϣ	
void send_msg_saveError(Hero *hero);															//��Ʒ����ʧ�ܷ�����Ϣ
void send_msg_useSuccess(Hero *hero,int index);													//ʹ����Ʒ�ɹ�,������Ϣ
int getTime();

/*ʹ�õ���ˢ��*/
void useToolBruMon(Hero *hero,char* goodsid,int index);
//��������
void useRideAgg(Hero *hero,char *goodsid,int index);
//��װ��ʵ�����浽������
bool saveEquipIntoBag(Hero *hero,Equipment *equip);
//ʹ�����
bool useGiftBag(Hero *hero,char *goodsid,int index);
#endif