#ifndef PET_BOX_H
#define PET_BOX_H
#include<iostream>
#include<string>
#include<map>
#include"pet.h"
using namespace std;

class Pet;
class Pet_Box
{
private:  		
	// int number;								//Я���ĳ�������   ��pet_boxdata.nuber����
	// int maxNumber;							//��Я���ĳ�����������	 ��pet_boxdata.maxNumber����
	// int index;								//��ǰ��ս���������   ��pet_boxdata.index����
	Pet_BoxDataNew* pet_boxdata;
	Pet *pets[12];
	
public:
	Pet_Box();	
	Pet_Box(Pet_BoxDataNew *_pet_boxdata);
	~Pet_Box(void);
	Pet* getPet(int _index);							//ȡ��������indexλ�ĳ���ʵ��
	Pet* getActivePet(void);							//ȡ������ս���ĳ���ʵ��
	int getNumber(void);								
	int getMaxNumber(void);
	void usePetAgg(Pet *_pet);							//ʹ�ó��ﵰ
	void carryNum(int heroLevel);						//Я�������ж�
	int getActivePetIndex(void);						//ȡ�ó�ս���������
	void setActivePetIndex(int _index);
	void send_msg_add(char* msg,Pet *pet,int len);
	void send_msg_list(char *msg,int len);
	bool verification(int _index,char* identity);		//��֤����
	bool deletePet(int _index);
	// void saveInstruct(int _index);
	Pet_BoxDataNew getMemStruct(void);
	int getIndex(char* identity);						//���ݳ���ʵ��id ���ҳ�������
	void onlineSetActive(void);
	int showPetData(Pet_BoxDataNew *obj, char *outfile);	
	void msg_maxNumber(char *msg,int len);
};
#endif
