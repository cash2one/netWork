/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�command_game_fight_manage.h
		�ļ����ã�����ս����������ĺ�����ʵ��
*/

#ifndef COMMAND_GAME_FIGHT_MANAGE_H
#define COMMAND_GAME_FIGHT_MANAGE_H
#include<vector>
#include"data_structure_struct.h"
#include"hero.h"
#include"skill.h"
#include"map_inform.h"
#include"monsterBase.h"
/*�����Ե��ͻ��˷������������������*/
void flightAction(char *buffer);     					 	 		 //����һ��ս������
/*�жϹ���������״̬�Լ�������ʹ�õļ����Ƿ���Ϲ���Ҫ��*/
bool isFightStatusOfHero(Hero *hero,Skill *skill);
/*ͨ��heroId����Heroʵ��*/
Hero* findbyheroid(char *heroid);
/*ͨ��skillId����skillʵ��*/
Skill* findbyskillid(Hero *hero,char *skillid);
/*ͨ��monsterId����monsterʵ��*/
MonsterBase* findbymonsterid(Map_Inform *mapinform,char *monsterid);
/*�ж�����Ƿ����ս�������ƶ��������޵У�type=1:ս����type=2���ƶ���type=3���޵У�*/
bool isHeroFightMoveInvincible(Hero *hero,int type);	
/*�ж��ܻ��������ʱ��״̬�Լ����������ܻ���֮��ľ����ж��Ƿ����ս��Ҫ��*/
bool isFightStatusOfHitHero(Hero *hero,Point point1,Hero *hiter,int range);
/*�ж��ܻ����ǹ���ʱ��״̬�Լ����������ܻ���֮��ľ����ж��Ƿ����ս��Ҫ��*/
bool isFightStatusOfHitMonster(Hero *hero,Point point1,MonsterBase *hiter,int range);
/*�����ܻ��������ʱ���ܻ��ߵĿ�Ѫֵ*/
int redloseOfHero(Hero *hero,Hero *hiter,Skill *skill);
/*�����ܻ��������ʱ���ܻ��ߵĿ�Ѫֵ*/
int redloseOfMonster(Hero *hero,MonsterBase *hiter,Skill *skill);
/*�ܻ��������ʱ����ȡ�����ߣ��ܻ���Ѫֵ�۳��Ļ�������*/
int redloseOfHeroManage(Hero *attack,Hero *hited,Skill *skill);
/*�ܻ����ǹ���ʱ����ȡ�����ߣ��ܻ���Ѫֵ�۳��Ļ�������*/
int redloseOfMonsterManage(Hero *attack,MonsterBase *hiter,Skill *skill);
/*�ж��ܻ����Ƿ��������,�����������ܣ����������˺���*/
double  dodgeOfHiterMange(int dodge,int hit);
/*�ж��ܻ����Ƿ���ֱ��������ر�����*/
double critOfHeroMange(int crit,int tenacity);
/*ս�������󣬹������������Եĸı�*/
int PropertyOfAttackerChange(Hero *hero,Skill *skill);
/*ս���������ܻ���Ϊ���ʱ�������Եĸı�*/
int PropertyOfHiterHeroChange(Hero *hero,int redlose);
/*ս���������ܻ���Ϊ����ʱ�����������Եĸı�*/
int PropertyOfHiterMonsterChange(Hero *attack,MonsterBase *hited,int redlose);
/*ս�������󣬽��ܻ���Ϊ��ҵĹ����ɹ�����Ϣ���͸��ͻ���*/
void SendMsg_AttackHero(Hero *attack,Hero *hited,Skill *skill,int redlose);
/*ս�������󣬽��ܻ���Ϊ����Ĺ����ɹ�����Ϣ���͸��ͻ���*/
void SendMsg_AttackMonster(Hero *attack,MonsterBase *hited,Skill *skill,int redlose);
/*�Ź�����ϢȺ���ķ���ʵ��*/
void sendmsg_manage(Hero *attack,string msg);
/*�ͻ��˷�����Ⱥ��������Ϣ����������*/
void qungongskill(char *buffer);
/*���ʩ��Ⱥ��ҽ�Ƶķ���ʵ��,����ɹ����򷵻ط��͸��ͻ��˵���Ϣ*/
string herotreatAll(Hero *hero,Skill *skill,vector<string> hits);
/*���ʩ��Ⱥ�幥���ķ���ʵ�֣�����ɹ����򷵻ط��͸��ͻ��˵���Ϣ*/
string heroattackAll(Hero *hero,char* hiterid,Skill *skill,vector<string> hits);
/*���ʩ��Ⱥ�幥���ļ��ܣ��ܻ��ߵĿ�Ѫ������ʵ��*/
string redloseOfattackAll(Hero *hero,Point pt_hit,int range,Skill *skill,vector<string> hits);
/*���ʩ��buff���ܣ������ͻ��˷�������Ϣ*/
void  attackusebuff(char *buffer);
/*��Ҵ���buff���ܵķ���ʵ��*/
string buffmanage(Hero *hero,Skill *skill);
/*��Ч�ĳ���ʱ�䵽ʱ�Ĵ���*/
void debuffstop(char *buffer);
/*���ս��ǰ���Ա仯��type=1�������ߣ�type=2���ܻ���*/
void HeroPropertybeforeFight(Hero *hero,int type);
/*������˺�ֵ��type=1,�����Ѫ��type=2:��ҷ����˺���type=3������Ƿ��ͷ�Ѫ������*/				
int HeroPropertybackFight(Hero *hero,int type,int redlose);
/*��ս�����������뱻��������������Ըı�:type=1,�ܻ�������ң�type=2,�ܻ����ǹ���*/
int ManagePropertyAttackerAndHiter(Hero *hero,int type,Hero *hiter,MonsterBase *hited,int redlose);
/*��ҳ�����Ѫ�ļ�ʱ����*/
void heroThink(struct ev_loop *loop,ev_timer *think,int revents); 
/*��Ҳ���ս������ʱ�������ƶ�*/
void nomove(Hero *hero,Skill *skill);

/*�����＼������*/
void acceptSkillMsg(char *buffer);
#endif