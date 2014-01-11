/************************************************************
	�ļ�����cpyAsist.h
	�ļ����ã���������������
	���ߣ�chenzhen
	�������ڣ�2012.06.29
************************************************************/

#ifndef CPY_ASIST_H
#define CPY_ASIST_H

#include "instancing_manage.h"
#include<vector>
#include<string>

using namespace std;
class Hero;

//������߶ӳ�Ϊ��
bool SingleOrTeamLeader(const char* memberId);

/*�ж��Ƿ�Ϊͬһ�����ɵ���*/
bool judgeSameParty(vector<string> &heroId,char *partyId = NULL);

/*���븱��ʧ��ԭ��������Ϣ*/	
void dealFailRson(Failure_Reason* failure_reason,char *failMsg,int lengthStr,int entType = 0);

/*���븱��ʧ��ԭ����*/
void sendFailMsg(vector<string> &heroId,char *failMsg);

/*���ڴ��������ˮ�ŵ��ַ���<��Ҫ��id>���Ҳ��ı�ԭ����*/
bool dealSerNumStr(char *resore,char *last,char *ahead,bool isLast = true,char *tok = "_");

/*�˳�����*/
void outCpy(Hero *myHero);

/*���������Ӧ��������*/
void cpyPanelResponse(Hero *owner);

/*�ж�������֮��ľ���*/
bool judRange(Point &piexA,const Point &piexB,int const range);

/*��ʼ��������ʧ�ܽṹ������*/
bool initFailReson(Failure_Reason *reason);

/*������ɳԷ��ĵط�<������>*/
void enterPartyEat(char *heroId,char *mapEatId);

/*����ȼ���Ӧ�İ��ɴ�Ӫ��ͼ*/
bool insertCampMap(int key,string &values);

/*����ȼ���Ӧ�İ��ɴ�Ӫ��ͼ*/
void insertLevelCampMap(int level,string &values);

/*����ȼ���Ӧ�İ��ɴ�Ӫ��ͼ*/
void testPrintLevelCampMap(void);

/*������ߵȼ���Ӧ�İ��ɴ�Ӫ��ͼ*/
void insertHightestLevelCampMap(void);

/*�˳����ɴ�Ӫ*/
bool outCampMap(Hero *myHero);

/*�������񸱱�����������*/
void entTaskCpy(char *heroid,char *cpyTyeId);

/*����ֵ�����Ӧ��������*/
void fatigueResponse(Hero *owner);

/*��������ֵ*/
void purchaseFatigue(char *buffer);

/*�ж��Ƿ�Ϊ���ֵ�ͼ20130412 chenzhen*/
bool isHappyMap(char *newMap);

/*��ľ�¸��������Ӧ��������*/
void towerLayerCpyResponse(Hero *owner);


void entCpyAsist(const char* hero_id,const char* _cpyTyeId,int cpyRank);

void initCpyLimitMemRecord();

void storeCpyLimitMemRecord();

void outSomeWhere(Hero *myHero);

#endif
