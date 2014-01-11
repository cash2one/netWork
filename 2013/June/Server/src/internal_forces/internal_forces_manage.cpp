#include "internal_forces_manage.h"
#include "money_operator.h"

static void internalForcesAttrAdd(Hero* hero, InForsLvlAdd_T* nextLvlItem, InForsDat_T* partyItem, int newLevel)
{
	for (int i = 0; i < 10; i++)
	{
		hero->incAttr(i, nextLvlItem->value[i]);
	}
	
	map<int, InForsLvlAdd_T>::iterator it_extAdd = partyItem->level_2_extraAdd.find(newLevel);
	if (it_extAdd != partyItem->level_2_extraAdd.end())
	{
		InForsLvlAdd_T *extAdd = &it_extAdd->second;
		for (int i = 0; i < 10; i++)
		{
			hero->incAttr(i, extAdd->value[i]);
		}
	}
	
}

void internalForcesAttrReCountByLevel(Hero* hero)
{
	char *party = hero->getParty();
	map<string, InForsDat_T>::iterator it_party = party_2_inForsDat.find(party);
	if (it_party == party_2_inForsDat.end())
	{
		cout<<"There isn't inForsDat of this party:"<<party<<endl;
		return;
	}
	InForsDat_T *partyItem = &it_party->second;
	
	int inForsLevel = hero->getInternalForcesLevel();
	map<int, InForsLvlAdd_T>::iterator it_thisLvlItem = partyItem->level_2_nomalAdd.find(inForsLevel);
	if (it_thisLvlItem == partyItem->level_2_nomalAdd.end())
	{
		cout<<"There isn't it_thisLvlItem of this party:"<<party<<" and this level:"<<inForsLevel<<endl;
		return;
	}
	
	InForsLvlAdd_T *thisLvlItem = &it_thisLvlItem->second;
	
	for (int i = 0; i < 10; i++)
	{
		hero->incAttr(i, thisLvlItem->total[i]);
	}
	
}

int internalForcesLvlUp(Hero* hero, int newLevel)
{
	if (hero == 0)
	{
		return 1;
	}
	
	int nowLevel = hero->getInternalForcesLevel();
	
	if (nowLevel >= BASE_INTERNAL_FORCES_LEVEL)
	{
		return 2;
	}
	
	if (nowLevel > newLevel)
	{
		return 3;
	}
	
	if (nowLevel + 1 != newLevel)
	{
		return 4;
	}
	
	map<string, InForsDat_T>::iterator it_partyItem = party_2_inForsDat.find(hero->getParty());
	if (it_partyItem == party_2_inForsDat.end())
	{
		//��internal_forces.xml�����д�
		cout<<"The internal_forces.xml config's party haven't read correct the hero party is "<<hero->getParty()<<endl;
		return 5;
	}
	
	InForsDat_T *partyItem = &it_partyItem->second;
	
	map<int, InForsLvlAdd_T>::iterator it_thisLvlItem = partyItem->level_2_nomalAdd.find(nowLevel);
	if (it_thisLvlItem == partyItem->level_2_nomalAdd.end())
	{
		//�����ô���û������ȼ�
		cout<<"The internal_forces.xml config's normalnextLvlItem haven't read correct the lvl is "<<newLevel<<endl;
		return 6;
	}
	
	InForsLvlAdd_T *thisLvlItem = &it_thisLvlItem->second;
	int needIF = thisLvlItem->needIF;
	
	map<int, InForsLvlAdd_T>::iterator it_nextLvlItem = partyItem->level_2_nomalAdd.find(newLevel);
	if (it_nextLvlItem == partyItem->level_2_nomalAdd.end())
	{
		//�����ô���û������ȼ�
		cout<<"The internal_forces.xml config's normalnextLvlItem haven't read correct the lvl is "<<newLevel<<endl;
		return 7;
	}
	
	InForsLvlAdd_T *nextLvlItem = &it_nextLvlItem->second;
	
	if (!hero->useInternalForces(needIF))
	{
		//�����������
		cout<<"hero doesn't have enough internalForces for levelUp and the newLevel is "<<newLevel<<" needIF is "<<needIF<<" hero have is "<<hero->getInternalForces()<<endl;
		return 7;
	}
	
	internalForcesAttrAdd(hero, nextLvlItem, partyItem, newLevel);
	hero->internalForcesLevelUp();
	hero->setInternalForcesUpgradeNeedExp(nextLvlItem->upgradeNeedExp);
	hero->send_msg_att();
	viewHeroInternalForces(hero);
	
	hero->updataSingleTarget(1,7);
	return 0;
}

int internalForcesIncExp(Hero* hero, int mode)
{
	if (hero == 0)
	{
		//����ǿ��ʧ�ܣ�����ʹ�õ����������  --- return 1
		return 1;
	}
	
	int nowLevel = hero->getInternalForcesLevel();
	
	if (nowLevel < BASE_INTERNAL_FORCES_LEVEL)
	{
		//����ǿ��ʧ�ܣ���ǰ�׶���������ǿ���� --- return 2
		return 2;
	}
	
	if (nowLevel > MAX_INTERNAL_FORCES_LEVEL)
	{
		//����ǿ��ʧ�ܣ������ȼ������� --- return 3
		return 3;
	}
	
	map<string, InForsDat_T>::iterator it_partyItem = party_2_inForsDat.find(hero->getParty());
	if (it_partyItem == party_2_inForsDat.end())
	{
		//��internal_forces.xml�����д�
		cout<<"The internal_forces.xml config's party haven't read correct the hero party is "<<hero->getParty()<<endl;
		//����ǿ��ʧ�ܣ����ó�������ϵC���ͷ�������������Ƿ����ĸ���ȷ���ɡ� --- return 4
		return 4;
	}
	
	InForsDat_T *partyItem = &it_partyItem->second;
	
	int luckTimes = 1;
	int rankNum = rand() % 10000;
	if (rankNum < (int)(100 * partyItem->luckRate))
	{
		luckTimes = partyItem->luckTimes;
	}
	
	int incExp = 0;
	
	if (mode == 0)
	{
		if (hero->getInternalForcesBrushExpTimes() >= partyItem->useInnerTimeLmt)
		{
			//����ǿ��ʧ�ܣ���������ǿ����������!  --- return 5
			return 5;
		}
		int needInner = partyItem->perTimeNeedInner;
		if (!hero->useInternalForces(needInner))
		{
			//����ǿ��ʧ�ܣ���ǰ�������㣡	--- return 6
			return 6;
		}
		incExp = luckTimes * partyItem->useInnerGetExp;
		
	} else if (mode == 1){
		if (hero->getGoldBrushExpTimes() >= partyItem->vipUseGoldTimeLmt[hero->getVipStage()])
		{
			//����ǿ��ʧ�ܣ�����Ԫ��ǿ�������Ѿ�����  --- return 7
			return 7;
		}
		
		if (!useGold(hero, partyItem->thisTimeNeedGold[hero->getGoldBrushExpTimes()]))
		{
			//����ǿ��ʧ�ܣ�Ԫ��ǿ��ʱԪ������	-return 8
			return 8;
		}
		
		incExp = luckTimes * partyItem->useGlodGetExp;
	} else {
		//����ǿ��ʧ�ܣ�����ʹ�õ����������	retun 9
		return 9;
	}
	
	int newLevel = nowLevel + 1;
	map<int, InForsLvlAdd_T>::iterator it_nextLvlItem = partyItem->level_2_nomalAdd.find(newLevel);
	if (it_nextLvlItem == partyItem->level_2_nomalAdd.end())
	{
		//����ǿ��ʧ�ܣ�����ϵ�ͷ�C��������������Ƿ���ڵȼ��ϲ㡣	return 10
		cout<<"The internal_forces.xml config's normalnextLvlItem haven't read correct the lvl is "<<newLevel<<endl;
		return 10;
	}
	
	InForsLvlAdd_T *nextLvlItem = &it_nextLvlItem->second;
	
	int expNow = hero->getInternalForcesExpNow();
	int upgradeNeedExp = hero->getInternalForcesUpgradeNeedExp();
	if (incExp + expNow >= upgradeNeedExp)
	{
		hero->setInternalForcesExpNow(incExp + expNow - upgradeNeedExp);
		hero->internalForcesLevelUp();
		hero->setInternalForcesUpgradeNeedExp(nextLvlItem->upgradeNeedExp);
		internalForcesAttrAdd(hero, nextLvlItem, partyItem, newLevel);
		hero->send_msg_att();
		
		if (newLevel == MAX_INTERNAL_FORCES_LEVEL)
		{
			hero->updataSingleTarget(6,7);
		}
		
	} else {
		hero->setInternalForcesExpNow(incExp + expNow);
	}
	
	if (mode == 0)
	{
		hero->incInternalForcesBrushExpTimes();
	} else if (mode == 1) {
		hero->incGoldBrushExpTimes();
	}
	viewHeroInternalForces(hero, incExp);
	return 0;
}

int viewHeroInternalForces(Hero* hero, int incExp)
{
	int inForsLevel = hero->getInternalForcesLevel();
	
	char* party = hero->getParty();
	map<string, InForsDat_T>::iterator it_party = party_2_inForsDat.find(party);
	if (it_party == party_2_inForsDat.end())
	{
		cout<<"when viewHeroInternalForces There isn't inForsDat of this party:"<<party<<endl;
		return 1;
	}
	InForsDat_T *partyItem = &it_party->second;
	
	
	map<int, InForsLvlAdd_T>::iterator it_thisLvlItem = partyItem->level_2_nomalAdd.find(inForsLevel);
	if (it_thisLvlItem == partyItem->level_2_nomalAdd.end())
	{
		cout<<"when viewHeroInternalForces There isn't it_thisLvlItem of this party:"<<party<<" and this level:"<<inForsLevel<<endl;
		return 2;
	}
	
	InForsLvlAdd_T *thisLvlItem = &it_thisLvlItem->second;
	
	map<int, InForsLvlAdd_T>::iterator it_nextLvlItem = partyItem->level_2_nomalAdd.find(inForsLevel + 1);
	if (it_nextLvlItem == partyItem->level_2_nomalAdd.end())
	{
		if (inForsLevel <= MAX_INTERNAL_FORCES_LEVEL)
		{
			cout<<"when viewHeroInternalForces There isn't it_nextLvlItem of this party:"<<party<<" and this level:"<<inForsLevel + 1<<endl;
			return 3;
		}
	}
	
	InForsLvlAdd_T *nextLvlItem = &it_nextLvlItem->second;
	
	
	int vipClass = hero->getVipStage();
	int useGoldBrushTimes = hero->getGoldBrushExpTimes();
	
	char result[2048] = {0};
	//�����ȼ�������ֵ���������飬������Ҫ�������飬�����µȼ���Ҫ������ʹ������ˢ����ʣ�������ʹ��Ԫ��ˢ����ʣ�����������ʹ��Ԫ��ˢ����Ҫ��Ԫ����
	sprintf(result, "8,15,1,%d,%d,%d,%d,%d,%d,%d,%d", inForsLevel, hero->getInternalForces(), hero->getInternalForcesExpNow(),
	hero->getInternalForcesUpgradeNeedExp(), thisLvlItem->needIF, partyItem->useInnerTimeLmt - hero->getInternalForcesBrushExpTimes(),
	partyItem->vipUseGoldTimeLmt[vipClass] - useGoldBrushTimes, partyItem->thisTimeNeedGold[useGoldBrushTimes + 1]);
	
	
	for (int i = 0; i < 10; i++)
	{
		sprintf(result + strlen(result), ",%d", thisLvlItem->total[i]);
	}
	
	if (inForsLevel <= MAX_INTERNAL_FORCES_LEVEL)
	{
		for (int i = 0; i < 10; i++)
		{
			sprintf(result + strlen(result), ",%d", nextLvlItem->value[i]);
		}
	} else {
		sprintf(result + strlen(result), ",-1,-1,-1,-1,-1,-1,-1,-1,-1,-1");
	}
	
	sprintf(result + strlen(result), ",%d", incExp);
	send_msg(hero->getFd(), result);
	return 0;
}

bool isInForsCanLvlUp(Hero* hero)
{
	if (hero == 0)
	{
		return false;
	}
	
	int nowLevel = hero->getInternalForcesLevel();
	
	if (nowLevel >= BASE_INTERNAL_FORCES_LEVEL)
	{
		return false;
	}
	
	map<string, InForsDat_T>::iterator it_partyItem = party_2_inForsDat.find(hero->getParty());
	if (it_partyItem == party_2_inForsDat.end())
	{
		//��internal_forces.xml�����д�
		cout<<"The internal_forces.xml config's party haven't read correct the hero party is "<<hero->getParty()<<endl;
		return false;
	}
	
	InForsDat_T *partyItem = &it_partyItem->second;
	
	map<int, InForsLvlAdd_T>::iterator it_thisLvlItem = partyItem->level_2_nomalAdd.find(nowLevel);
	if (it_thisLvlItem == partyItem->level_2_nomalAdd.end())
	{
		//�����ô���û������ȼ�
		// cout<<"The internal_forces.xml config's normalnextLvlItem haven't read correct the lvl is "<<newLevel<<endl;
		return false;
	}
	
	InForsLvlAdd_T *thisLvlItem = &it_thisLvlItem->second;
	int needIF = thisLvlItem->needIF;

	if (hero->getInternalForces() < needIF)
	{
		//�����������
		// cout<<"hero doesn't have enough internalForces for levelUp and the newLevel is "<<newLevel<<" needIF is "<<needIF<<" hero have is "<<hero->getInternalForces()<<endl;
		return false;
	}
	
	return true;
}
