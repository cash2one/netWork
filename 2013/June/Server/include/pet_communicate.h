#ifndef PET_COMMUNICATE_H
#define PET_COMMUNICATE_H
#include <iostream>
#include "command_other_function_all_over.h"
#include "hero.h"
#include "pet_operator.h"

void petEvolution(char *buffer);
void petSuccinct(char *buffer);
void petStatus(char *buffer);
void petMating_one(char *buffer);
void petRequst(char *buffer);
void petSkillHandle(char *buffer);
void petModifyName(char *buffer);
void petFight(char *buffer);
void petSkillReturn(char *buffer);
void petBoxNum(char *buffer);
void petMatingInvite(char *buffer);
void petMatingInviteAgree(char *buffer);
void petMatingPutOnPet(char *buffer);
void petMatingPutOnGoods(char *buffer);
void petMatingLock(char *buffer);
void petMatingStart(char *buffer);
void petUseFive(char *buffer);//���ʹ��,ʹ�ó������е�
void petMatingPer(char *buffer);	//����˫�˷�ֳ�ɹ���
void petLearnSkillCom(char *buffer);	//����ѧϰ����
void petJingjie(char *buffer);			//�������

#endif