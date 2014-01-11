#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <iostream>
#include <string>
#include <map>
#include "hero.h"
#include "equipment.h"
#include "data_structure_struct.h"
#include "command_return_define_data.h"

using namespace std;

class Equipment;
class Warehouse
{
private:
	// Goods_Inform goods_inform[108];								//��Ʒ��Ϣ�ṹ��	
	WarehouseData warehousedata;								//���ڱ���memcached�Ľṹ��
	map<string,Equipment*> equip;								//ͨ��memcached��ʼ��ʱ,�ݴ�װ��ʵ��������,��ת�浽������,������ɾ��
	
public:
	Warehouse();												//���캯��
	Warehouse(WarehouseData _warehousedata);					//ͨ��memcached�Ĺ��캯��
	~Warehouse(void);
	int getGridNum(void);										//ȡ�ֿ��������
	void setGridNum(int _gridNum);								//���òֿ��������
	int getExpandNeedGold(void);								//ȡ������չ����Ҫ��Ԫ������
	void setExpandNeedGold(int _expandNeedGold);				//������һ����չ����Ҫ��Ԫ������
	char* getGridGoodsid(int index);							//ȡ�ø������µ���Ʒid
	int getGoodsNum(char* goodsid);							//ȡ�ø���Ʒ����������
	int getGridGoodsNum(int index);								//ȡ�ø������µ���Ʒ����
	bool saveGoodsInWarehouse(char*  goodsid,int number,int index);//������Ʒ��id������,��ŵĲֿ��ָ��������
	bool saveGoodsInWarehouse(char*  goodsid,int number);		//������Ʒ��id������,��ŵ��ֿ�ĵ�һ��Ϊ�յĸ�����
	int fullOrEmpty(char*  goodsid,int repeatNum,int number);				//������Ʒ��id�ʹ洢����,�жϲֿ��Ƿ��Ѿ���
	int findSaveIndex(char*  goodsid,int repeatNum);			//������Ʒ��id�ʹ洢����,������Ʒ���Դ�ŵ�����
	int getEmptyGrid(void);										//ȡ�õ�һ���յĸ���
	void initGrid(int index);									//��ʼ���������ĸ���
	bool verify(int index,char*  goodsid);						//��֤�������·ŵ���Ʒ �Ƿ���ͬ
	bool expand(int num);										//��չnum�����ĸ���
	bool isGridExistGoods(int index);							//�жϸø������Ƿ������Ʒ
	void msg_expand_success(char *msg);							//������չ�ɹ�����Ϣ
	void msg_expand_failed(char *msg);								//������չʧ�ܵ���Ϣ
	void msg_delete_goods(char *msg,int type,int index,char*  goodsid);	//����ɾ����Ʒ����Ϣ
	void msg_expand_needGold(char *msg,int num);							//������չ�ֿ�����Ҫ��Ԫ������Ϣ
	void msg_drag_success(char *msg,int len,int index1,int index2);								//�϶��ɹ���Ϣ����
	void msg_drag_failed(char *msg);								//�϶�ʧ����Ϣ����
	void saveInStruct(void);									//����memcached�ṹ��
	WarehouseData getMemStruct(void);							//����Ҫ����memcached�Ľṹ��
	// map<string,Equipment*> getEquipMap(void);					//ȡ�����װ������ʱ����
	int showWarehouseData(WarehouseData *obj, char *outfile);
	Goods_Inform getGoods_Inform(int _index);	
	void setMemStruct(WarehouseData _warehousedata);
};
#endif
