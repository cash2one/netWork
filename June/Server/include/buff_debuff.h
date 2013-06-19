#include<map>
#include<iostream>
#include"my_timer.h"
using namespace std;

#define NO_BUFF_OR_DEBUF_STATE		0x0				//��buff��debuff״̬
#define DEBUF_DIZZ_STATE			0x1				//ѣ��
#define DEBUF_FORB_MOVE_STATE		0x2				//�����ɲ��������ƶ�
#define DEBUF_FORB_ATTK_STATE		0x4				//��Ѩ�����ƶ�
#define DEBUF_IN_POISON_STATE		0x8				//�ж���������Ѫ
#define	DEBUF_LOSE_HIT_STATE 		0x10			//��ʧ����������
#define DEBUF_LOSE_DF_AT_STATE		0x20			//���𣺼�������
#define DEBUF_LOSE_TENC_STATE		0x40			//��������������
#define BUFF_ADD_CRIT_STATE			0x80			//��ȭ�����ӱ���
#define BUFF_ADD_DODGE_STATE		0x100			//����
#define	BUFF_ADD_SACRF_STATE		0x200			//����������������������
#define BUFF_REFLEX_STATE			0x400			//�����������˺�
#define	BUFF_INVINCIBLE_STATE		0x800			//�޵�
#define BUFF_BLADE_STORM_STATE		0x1000			//���з籩
#define DEBUF_LOSE_SPEED_STATE		0x2000			//�����ƶ��ٶ�
#define BUFF_MAGIC_SHIELD_STATE		0x4000			//ħ����״̬
#define PLAY_ANIMATION_STATE		0x8000			//���Ŷ���״̬
#define MAX_HERO_BUFF_NUM			15				//��ɫ�������buff��debuff����
typedef struct Buff_debuff_conf_S
{
	char skillId[51];
	int effect;
	int lastTimeBase;
	int lastTimeFactor;
	int effectBase;
	int effectIncFactor;
	Buff_debuff_conf_S(char *id, int eft, int timeB, int timeF, int eB, int eF)
	{
		strncpy(skillId, id, sizeof(skillId));
		effect = eft;
		lastTimeBase = timeB;
		lastTimeFactor = timeF;
		effectBase = eB;
		effectIncFactor = eF;
	}
} Buff_debuff_conf_T;

typedef struct SkillBuff_S
{
	char skillId[51];
	unsigned skillLevel;
	char atkerId[51];
	int lastTime;
	int leftTime;
	int perVal;
	int totalVal;
	ev_timer *timer;
	SkillBuff_S()
	{
		timer = new ev_timer;
		memset(skillId, 0, sizeof(skillId));
		memset(atkerId, 0, sizeof(atkerId));
		skillLevel = 0;
		lastTime = 0;
		perVal = 0;
		totalVal = 0;
	}
	~SkillBuff_S()
	{
		delete timer;
	}
}SkillBuff_T;

extern map<string, Buff_debuff_conf_T*> buf_debuf_conf;	//buff��debuff������