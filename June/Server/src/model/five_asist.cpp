/****************************************************************
 * Filename: five_asist.h
 * 
 * Description: ���в�������
 *
 * Original Author : bison, 2012-7-19
 *
 ****************************************************************/
 
#include"five_asist.h"

#include "money_operator.h"

extern map<string, Hero*> heroId_to_pHero;
/***************************************************************************
 * openFiveElem - ������ɫ��������
 * @hero: ��Ҫ�����Ľ�ɫָ��
 * @elem: ��Ҫ��ʼ����������
 * @index: �������±ꡣΪ-1ʱ��ʾ������������,
 *		   �����Ƕ���ҳ������е�index���������
 * Return: true:��ʼ�ɹ���false:��ʼʧ��
 ***************************************************************************/
bool openFiveElem(Hero *hero, FIVE_ELEMENT_T elem, int index)
{
	FiveElem *fiveElement = NULL;
	if (index == 20)
	{
		//��ɫ����25�����ܿ�����������
		if (hero->getLevel() < heroFiveElemConf.startLevel)
		{
			return false;
		}
		fiveElement = hero->getFiveElem();
		
	}
	else {
		//index ��Ϊ-1�����������ǶԳ������
		Pet_Box *pet_box = hero->getPetBox();
		Pet *pet = pet_box->getPet(index);
		if (pet == NULL)
		{
			return false;
		} else if(pet->getLevel() < heroFiveElemConf.startLevel) {
			return false;
		}
		
		fiveElement = pet->fiveElem;
	}
	
	if(fiveElement==NULL)
	{
		return false;
	}
	
	//�Ѿ����������Բ����ٳ�ʼ
	if ((fiveElement->getElem() != NOELEM))
	{
		return false;
	}
	//����������NOELEM-->elem
	fiveElement->changeElem(elem);
	
	//���еȼ���0-->1
	fiveElement->upGrade();
	
	//�޸�����浽memcache�е�����
	if (index == 20)
	{
		hero->memHero->fiveElementData.element = elem;
		hero->memHero->fiveElementData.level += 1;
		hero->memHero->fiveElementData.expForNext = 4;		//����1����ʱ��������Ҫ��
		hero->memSet();
	}
	return true;
}

/***************************************************************************
 * changeFiveElem - ��ʼ����ɫ��������
 * @elem: ��Ҫ���ĳɵ���������
 * @hero: ��Ҫ�����Ľ�ɫָ��
 * @index: �������±ꡣΪ-1ʱ��ʾ������������,
 *		   �����Ƕ���ҳ������е�index���������
 * @order: ���и��ĵ��ڱ����е�λ��
 * Return: true:���ĳɹ���false:����ʧ��
 ***************************************************************************/
bool changeFiveElem(Hero *hero, FIVE_ELEMENT_T elem, int index, int order)
{
	// Money *gold = hero->getMoney();
	FiveElem *fiveElement;
	Bag *bag = hero->getBag();
	
	if (elem < 1 || elem > 5)
	{
		cout<<"BisonTest: elem is out range "<<elem <<endl;
		return false;
	}
	char *goodsId = "f_cl_100_100";
	if (useBagGoods(hero,goodsId, order, 1))
	{
		cout<<"BisonTest: use goods Fail������"<<endl;
		return false;
	}
	
	if (index == 20)
	{
		fiveElement = hero->getFiveElem();
	} else {
		//index ��Ϊ-1�����������ǶԳ������
		Pet_Box *pet_box = hero->getPetBox();
		Pet *pet = pet_box->getPet(index);
		if (pet == NULL)
		{
			cout<<"BisonTest: NO PET YOU specifed send!"<<endl;
			return false;
		}
		fiveElement = pet->fiveElem;
	}	
	
	fiveElement->changeElem(elem);
	if (index == 20)
	{
		hero->memHero->fiveElementData.element = elem;
		hero->memSet();
	}
	return true;
}

//������������
int changeFiveElemNew(Hero *hero, FIVE_ELEMENT_T elem, int index)
{
	FiveElem *fiveElement;
	if (elem < 1 || elem > 5)
	{
		cout<<"BisonTest: elem is out range "<<elem <<endl;
		return 1;
	}
	
	if (index == 20)
	{
		if (hero->getLevel() < heroFiveElemConf.startLevel)
		{
			return 3;
		}
		fiveElement = hero->getFiveElem();
	} else {
		//index ��Ϊ-1�����������ǶԳ������
		Pet_Box *pet_box = hero->getPetBox();
		Pet *pet = pet_box->getPet(index);
		if (pet == NULL)
		{
			cout<<"BisonTest: NO PET YOU specifed send!"<<endl;
			return 2;
		}
		if (pet->getLevel() < heroFiveElemConf.startLevel)
		{
			return 3;
		}
		fiveElement = pet->fiveElem;
	}	
	
	if (fiveElement == NULL)
	{
		return 3;
	}
	if (!useGold(hero, heroFiveElemConf.changeNeedGold))
	{
		return 4;
	}
	
	fiveElement->changeElem(elem);
	if (index == 20)
	{
		hero->memHero->fiveElementData.element = elem;
		hero->memSet();
	}
	return 0;
}

/*****************************************************************************
 * upGradeFiveElem - ���ʹ�����е��������еȼ��ӿ�
 * @hero: ��Ҫ�����Ľ�ɫָ��
 * @index: �������±ꡣΪ-1ʱ��ʾ������������,
 *		   �����Ƕ���ҳ������е�index���������
 * Return: true:�����ɹ���false:����ʧ��
 *****************************************************************************/
/*
bool upGradeFiveElem(Hero *hero, int index)
{
	int level = hero->getLevel();
	FiveElem *fiveElement = hero->getFiveElem();
	if (index == -1)
	{
		level = hero->getLevel();
		fiveElement = hero->getFiveElem();
	} else {
		//index ��Ϊ-1�����������ǶԳ������
		Pet *pet = hero->getPet(index);
		if (pet == NULL)
		{
			return false;
		}
		level = pet->getLevel();
		FiveElem *fiveElement = pet->getFiveElem();
	}
	
	Bag *bag = hero->bag;
	if ((level - fiveElement->getLevel()) < 25)
	{
		//���еȼ����ҲҪ��Ӣ�۵ȼ���20��
		return false;
	}
//�������е���Ʒ��û�У��������ٴ�
#if 0
	int thirdPillNum = bag->getGoodsNum(thirdPill);			//�������е�����
	int secondPillNum = bag->getGoodsNum(secondPill);		//�������е�����
	int firstPillNum = bag->getGoodsNum(firstPill);			//һ�����е�����
	
	if (thirdPillNum >= 1)
	{
		//һ���������е�����һ��
		if (fiveElement->upGrade())
		{
			//�����ɹ��۳��������е�һ��
			bag->useGoods(thirdPill, 1);
			return true;
		}
	} else if (secondPillNum >= 4) {
		//�ĸ��������е�����һ��
		if (fiveElement->upGrade())
		{
			bag->useGoods(secondPill, 4);
			return true;
		}
	} else if ((secondPillNum * 4 + firstPillNum) >= 16) {
		if (fiveElement->upGrade())
		{
			//��۶������е���һ�����е�
			bag->useGoods(secondPill, secondPillNum);
			bag->useGoods(firstPill, 16 - secondPillNum * 4);
			return true;
		}
	}
#endif

	return false;
}
*/

/*****************************************************************************
 * useFiveElemGoods - ���ʹ�����е��������о���
 * @hero: ��Ҫ�����Ľ�ɫָ��
 * @goodsId: ʹ�õ����е�ID
 * @order: ���е��ڱ����е�λ��
 * @index: �������±ꡣΪ-1ʱ��ʾ������������,
 *		   �����Ƕ���ҵĳ�ս�������
 * Return: true:���Ӿ���ɹ���false:���Ӿ���ʧ��
 *****************************************************************************/
bool useFiveElemGoods(Hero *hero, char* goodsId, int order, int index)
{
	char msg[64] = {0};
	int ret = 0;
	int level;
	FiveElem *fiveElement;
	int val;							//��ҩ�������еľ���ֵ
	
	Bag *bag = hero->getBag();
	
	if (index == 20)
	{
		//�Ƕ�Ӣ��ʹ��
		level = hero->getLevel();
		fiveElement = hero->getFiveElem();
		
		//�������ʹ����������е�ҩ
		if (!strcmp(goodsId, "f_dj_100_102") || !strcmp(goodsId, "b_dj_100_102"))
		{
			val = 4;
		} else if (!strcmp(goodsId, "f_dj_100_101") || !strcmp(goodsId, "b_dj_100_101")) {
			val = 2;
		} else if (!strcmp(goodsId, "f_dj_100_100") || !strcmp(goodsId, "b_dj_100_100")) {
			val = 1;
		} else {
			//��������ʹ�õ����е�
			cout<<"BisonTest: It is not the five pills for hero using"<<endl;
			//������ȷ��̫��������Id
			ret = 1;
			return false;
		}
	} else {
		//index ��Ϊ-1����ʹ�����е����ǶԳ������
		//Pet *pet = hero->getPet(index);
		//��Ϊ���ڲ߻��涨���е�ֻ�ڱ����гԣ�������Ĭ�ϸ���ս�����
		Pet_Box *pet_box = hero->getPetBox();
		Pet *pet = pet_box->getActivePet();
		if (pet == NULL)
		{
			cout<<"BisonTest: No this Pet with this index when eat five pills"<<endl;
			//����޳���
			ret = 2;
			return false;
		}
		level = pet->getLevel();
		FiveElem *fiveElement = pet->fiveElem;
		//�������ʹ�ó�������е�ҩ
		if (!strcmp(goodsId, "f_dj_101_102") || !strcmp(goodsId, "b_dj_101_102"))
		{
			val = 4;
		} else if (!strcmp(goodsId, "f_dj_101_101") || !strcmp(goodsId, "b_dj_101_101")) {
			val = 2;
		} else if (!strcmp(goodsId, "f_dj_101_100") || !strcmp(goodsId, "b_dj_101_100")) {
			val = 1;
		} else {
			//���ǳ���ʹ�õ����е�
			cout<<"BisonTest: It is not the five pills for pet using"<<endl;
			ret = 3;
			return false;
		}
	}
	if (fiveElement->getLevel() == 0)
	{
		//���л�û��ʼ����
		ret = 4;
		return false;
	}
	//���еȼ����ҲҪ��Ӣ�۵ȼ���25��ʱ�ſ�������
	if (level < heroFiveElemConf.needHeroLevel[fiveElement->getLevel()] || fiveElement->getLevel() >= 60)
	{
		cout<<"BisonTest: level limit to use fiveElement Exp Pills"<<endl;
		ret = 5;
		return false;
	}
	
	if (useBagGoods(hero,goodsId, order, 1))
	{
		cout<<"BisonTest: use goods fail when eat fiveElem pills"<<endl;
		ret = 6;
		return false;
	}
	
	fiveElement->addExp(val);
	
	if (index == 20)
	{
		hero->memHero->fiveElementData.expNow = fiveElement->getExpNow();
		hero->memHero->fiveElementData.level = fiveElement->getLevel();
		hero->memHero->fiveElementData.expForNext = fiveElement->getExpForNext();
		
		hero->memSet();
	}
	sprintf(msg, "8,9,0,%d", ret);
	send_msg(hero->getFd(), msg);
	return true;
}

/*****************************************************************************
 * getFiveElemHurt - �����˺�����
 * @fiveHit: �����ߵ�����
 * @fiveHited: �������ߵ�����
 * Return: ��������˺�
 *****************************************************************************/
int getFiveElemHurt(FiveElem *fiveHit, FiveElem *fiveHited)
{

	//cout<<"fiveHit "<<fiveHit->getLevel()<<" "<<fiveHit->getValue()<<" " <<fiveHit->getElem()<<endl;
	//cout<<"fiveHit "<<fiveHited->getLevel()<<" "<<fiveHited->getValue()<<" " <<fiveHited->getElem()<<endl;
	//�������߶Թ����ߵ����п���
	double k = fiveHited->getFactor(fiveHit->getElem());
	//cout<<"BisonTest k is "<<k<<endl;
	//�����ߴ򱻹����߸��ӵ������˺�
	int hurt = fiveHit->getHurt(k);
	
	return hurt;
}