#include "hero_fight.h"

/*******************************************************
 * crit_cal -- ��������
 * @atkCrit:	�����߱���ֵ
 * @tenacity:	������������
 * @isCrit:		�Ƿ񴥷�����
 * @critTimes:	��������
 * Return:	����ʧ��ԭ��
 *******************************************************/
int crit_cal(unsigned &atkCrit, unsigned &tenacity, bool &isCrit, float &critTimes)
{
	//�����߱���ֵ�Ƿ�
	if (atkCrit > MAX_HERO_CRIT_VALUE)
	{
		cout<<"the attacker hero's crit value is error! max value is "<<MAX_HERO_CRIT_VALUE<<" and his is "<<atkCrit<<endl;
		return 1;
	}
	
	//������������ֵ�Ƿ�
	if (tenacity > MAX_HERO_TENACITY_VALUE)
	{
		cout<<"the attacked hero's tenacity value is error! max value is "<<MAX_HERO_TENACITY_VALUE<<" and his is "<<tenacity<<endl;
		return 2;
	}
	
	//���㱩���ʼ���������
	float critFactor = 0.0f;
	if (atkCrit <= tenacity)
	{
		critFactor = 0.1f;
		critTimes = 1.1f;
	} else {
		critFactor = 0.1 + 0.9 * ((atkCrit - tenacity) * 0.002 / ( 1 + (atkCrit - tenacity) * 0.002));
		critTimes = 1.1 + 0.002 * (atkCrit - tenacity);
	}
	
	//�߽�ֵ
	unsigned rank = rand() % 10000;
	unsigned boundary = unsigned(critFactor * 10000);
	
	//�Ƿ񱩻�
	if (rank < boundary)
	{
		isCrit = true;
	} else {
		isCrit = false;
		critTimes = 1.0f;
	}
	return 0;
}

/*******************************************************
 * dodge_cal -- ��������
 * @atkHit:		����������ֵ
 * @batkdDodge:	������������
 * @isHited:	�Ƿ񴥷�����
 * @hitFactor:	�����˺�����
 * Return:		����ʧ��ԭ��
 *******************************************************/
int dodge_cal(unsigned &atkHit, unsigned &batkdDodge, bool &isHited, float &hitTimes)
{
	//����������ֵ�Ƿ�
	if (atkHit > MAX_HERO_HIT_VALUE)
	{
		cout<<"the attacker hero's hit value is error! max value is "<<MAX_HERO_HIT_VALUE<<" and his is "<<atkHit<<endl;
		return 1;
	}
	
	//������������ֵ�Ƿ�
	if (batkdDodge > MAX_HERO_DODGE_VALUE)
	{
		cout<<"the attacked hero's dodge value is error! max value is "<<MAX_HERO_DODGE_VALUE<<" and his is "<<batkdDodge<<endl;
		return 2;
	}
	
	//���������ʼ������˺�����
	float dodgeFactor = 0.0f;
	if (atkHit > batkdDodge)
	{
		// dodgeFactor = 0.05f;
		// hitTimes = 1.0 + 0.0002 * (atkHit + 500 - batkdDodge);
		dodgeFactor = 0.05 * (1 - 0.02 * (atkHit - batkdDodge)) / (1 + 0.02 * (atkHit - batkdDodge));
		hitTimes = 1.0f;
	} else {
		dodgeFactor = 0.05 + 0.95 * ((batkdDodge - atkHit) * 0.002 / ( 1 + (batkdDodge - atkHit) * 0.002));
		hitTimes = 1.0f;
	}
	
	//�߽�ֵ
	unsigned rank = rand() % 10000;
	unsigned boundary = unsigned((1 - dodgeFactor) * 10000);
	
	//�Ƿ�����
	if (rank < boundary)
	{
		isHited = true;
	} else {
		isHited = false;
	}
	return 0;
}

bool isTouchHit(int hitA, int dodgeB)
{
	float factor = (hitA * fightConst.hitFactor) / (hitA * fightConst.hitFactor + dodgeB);
	unsigned rank = rand() % 10000;
	unsigned boundary = unsigned (factor * 10000);
	if (rank < boundary)
	{
		return true;
	} else {
		return false;
	}
}

//����ϵ�� =��15+A����/K��*��100-��5+B����/K����/10000
bool isTouchCrit(int critA, int tencB)
{
	float factor = (fightConst.critBase + critA / fightConst.critFactor) * (fightConst.tencMax - (fightConst.tencBase + tencB / fightConst.tencFactor)) / fightConst.critDivisor;
	
	unsigned rank = rand() % 10000;
	unsigned boundary = unsigned (factor * 10000);
	if (rank < boundary)
	{
		return true;
	} else {
		return false;
	}
}