// #ifndef PETSKILL_H
// #define PETSKILL_H
// #include<iostream>
// #include<string>
// #include<map>
// #include"pet.h"
// #include"petSkill_config.h"
// using namespace std;


// class Pet;
// class PetSkill_Config;
// class PetSkill
// {
// private:  
	// string identity;												//���＼��ʵ��id
	// string id;														//���＼��id
	// int flag;														//���＼������
	// int effect;														//���＼��Ч��
	// int increaseRatio;												//���＼��Ч��������
	// int limit;														//ѧϰ���ܳ�����Ҫ�ĵȼ�
	// int needMoney;													//���＼������������
	// int needExp;													//���＼���������辭��
	// int level;														//���＼�ܵȼ�
	
	// Pet *pet;														//ӵ�д˼��ܵĳ���ʵ��ָ��
	// PetSkillData petskilldata;

// public:
	// PetSkill(PetSkill_Config *_petSkill_config,Pet *_pet);
	// PetSkill(PetSkillData _petskilldata);
	// void initSkill(PetSkill_Config *petSkill_config,int _index);
	// bool skillLevelUpNeedExp(int _index);										//������＼���������辭��
	// bool skillLevelUpNeedMoney(int _index);									//������＼������������
	// bool skillLevelUp(int _index);												//���＼������
	// void triggerPassiveSkill(int _flag);									//������������
	// void removePassiveSkill(int _flag);									//ȥ�����＼�ܵ�Ч��
	// void increaseEffect(int _index);										//������������
	// int getAttRatio(int _index);											//��ù�������
	// string getSkillId(int _index);												//��ü���id
	// string getSkillIdentity(int _index);
	// void saveInStruct(int _index);
	// PetSkillData getStruct(int _index);
	// int getSkillLevel(int _index);
	// int getSkillNeedMoney(int _index);
	// int getSkillNeedExp(int _index);
	// int getSkillLimit(int _index);
	// int getSkillFlag(int _index);
	// void setPet(Pet *_pet);	
// };
// #endif