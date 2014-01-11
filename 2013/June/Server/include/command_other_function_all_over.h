/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�command_other_function_all_over
		�ļ����ã���һЩ��������Ϸ�ж�����õĵĺ����Ķ���
*/
#ifndef COMMAND_OTHER_FUNCTION_ALL_OVER
#define COMMAND_OTHER_FUNCTION_ALL_OVER
#include"data_structure_struct.h"
#include"libev.h"
#include<time.h>
#include<list>
#include<string.h>
#include<stdio.h>
#include<uuid.h>
#include<stdlib.h>
#include<iostream>
#include"map_inform.h"
#include"hero.h"
#include"role.h"
#include"wagon.h"
#include"trap.h"
#include"bottle.h"
#include<map>

class Pet;
class Hero;
class Map_Inform;
class Pick;
class MonsterBase;
class Wagon;
class TakeGoods;
class Bottle;
class Pet;
class Pick;
class BruMonInfor;
class Equipment;
class StatuaryHero;
void init_command_map(void);      												//��ʼ�������������

void sendMsg_Nine(Hero *hero,string msg);										//������ҾŹ����ڵ����������Ϣ evan add 2012.8.23
Point MapExchangeLogical(Point pointOfmap);

Point LogicalExchangeMap(Point pointOflogical);

string intTostring(int value);                                               //int����ת��Ϊstring

string charTostring(char *value);                                            //char*����ת��Ϊstring

string itos(int i);															//int to string by Cookie

bool send_msg(int fd, char *msg_body);	

bool send_msg(int fd, string &msg_body);

bool ComFun(const HatVal &hat1,const HatVal &hat2);

int HatFun(list<HatVal> &hat1,list<HatVal> &hat2,char *perHerId,char *goodsOwner,\
			char *monId,bool isCopy = false);								//���ڷ�������ͻ�����Ϣ�ķ���ʱ

char *cid();																//��ȡuuid by Cookie
char *cidOtherWay();

/*��id����׷����ˮ�ţ��Ҳ���byteSumλ* add chenzhen 2012.06.11*/
void appendNum(char *id,int num,int byteSum);    


/*���볡������*/
void enter_scenes(Hero *myHero, Map_Inform *map_now,int entOlder = 1);     

/*�˳���������*/
void quit_scene(Hero *myHero, Map_Inform *map_now);  

Hero* fd_to_hero();

/*�ж�һ�ŵ�ͼ��������ֱ��֮���Ƿ����ϰ���*/
bool hasBarrier(Point ptStart,Point ptEnd,Map_Inform* mapInfo);

/*��ñ��������ʵ��ָ��*/
Hero* heroid_to_hero(string heroId);

//��ó���ʵ��
Pet* id_to_getActivePet(char* petid);

//��ñ���ʵ��
Pick* id_to_getPick(string pickid);
 
/*��ȡ����ʵ��*/
Wagon* getInstWgon(string wagonId);

/*ȡ�����*/
int random_number(int begin,int end);
 
class CreateMessage
{
	public:
		static string come_into_scene(Hero *myHero);
		//Ӣ�۽�������״̬��Ϣ���� added by tory
		static string inst_record_infor(Hero *myHero);
		//���ڹ㲥��������ң����½�ɫ������Ұ��Χ
		static string come_into_view(Hero *myHero);
		
		static string out_of_view(Hero *myHero);
		
		//ˢ�����״̬
		static string brushHeroTeamStation(Hero *myHero);
		
};

void   mysort(int   a[],int   iLen) ;

bool viewStyleHero(Hero *self,Hero *other,int style);

/*������Ϣ*/
bool viewStyleMon(Hero *self,MonsterBase *other,int style);

/*����Ϣ*/
bool viewStyleWagon(Hero *self,Wagon *other,int style);

/*��ժȡ��Ʒ��Ϣ*/
bool viewStyleTakeGoods(Hero *self,TakeGoods *other,int style);

/*���壬������Ϣ*/
bool viewStyleTrap(Hero *self,Trap *other,int style);

/*ƿ����Ϣ*/
bool viewStyleBottle(Hero *self,Bottle *other,int style);

/*������Ϣ*/
bool viewStylePet(Hero *self,Pet *other,int style);

/*������Ϣ*/
bool viewStylePick(Hero *self,Pick *other,int style);

/*����װ����Ϣ*/
bool viewStyleEquip(Hero *self,Equipment *other,int style);

/*ȥ������ŵĸ���id*/
string dealCpyId(string _cpyId);
void dealCpyId(char* _cpyId);

void msg_error(char *msg,int flag);					//������Ϣ����
/*�ڶ�ȡ��ͼ�����ļ�������*/
void deleteBruRec(map<string,BruMonInfor*> &bruRecod);


//�ַ���֤�������� ����ture ��Ϸ�  ����false���Ϸ�
bool charsCheckingChat(const char *c);
//�ַ���֤��������
bool charsCheckingName(const char *c);

void initPlayerNumber(void);

//substr
void sub_str(char *dest, char *src, int start, int cnt = 0);
//string::find
int findChar(const char *src, char key, int srcLen);

static void heroVerify(struct ev_loop *loop,ev_timer *think,int revents);

 bool send_msg(int fd, char* msg_body);
 
 bool send_msg(int fd, const char *msg_body);
 
 /*�������ܣ���ȡuuid*/				
bool cidOtherWay(char *data,int length);

Point getCurrenPt(Point _ptStart, Point _ptEnd, int v, int t, Map_Inform* mapInfo);


/*��ȡ����װ��*/
Equipment* getEquipInst(string equipId);

/*ɾ������װ����ȫ������*/
bool reaseEquip(string equipId);

/*��õ���ˢ������ʵ��ָ��*/
MonsterBase* getToolMonster(char *monId);


/*��ɱ����boss,ȫ���㲥
**heroΪɱboss���һ�������ʵ��,monsterNameΪ����boss�ĺ�������
*/
void killGlobalBossAdvertise(Hero *hero,char *monsterName);

//������Ϣ��cdkey Server
bool send_msg_to_cdkey(char *msgbody);

//�ж��Ƿ����ϰ��㣻
bool has_barrier(Point _ptStart,Point _ptEnd,Map_Inform* mapInfo);

/*������Ϣ*/
bool viewStyleStatuary(Hero *self,StatuaryHero *other,int style);

#endif
