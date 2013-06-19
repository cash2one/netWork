/****************************************************************
 * Filename: five_elements.h
 * 
 * Description: ���������ʵ�ּ������˺�����
 *
 * Original Author : bison, 2012-7-10
 *
 ****************************************************************/
 
#include"five_elements.h"
#include "hero.h"
extern Hero *pg_hero;

extern map<string, Hero*> heroId_to_pHero;
/****************************************************************
 * FiveElem - ���й��캯��
 * @elem: ���е�����ֵ��Ĭ��ΪNOELEM ����������
 * @_level: ���еȼ���Ĭ��Ϊ0
 ****************************************************************/
FiveElem::FiveElem(FIVE_ELEMENT_T elem, int _level)
{
	element = elem;
	level = _level;
	expNow = 0;												//��ǰ����
	expForNext = heroFiveElemConf.upgradeNeedExp[level];	//������һ����Ҫ����ֵ
}

//����memcache�����������ݽ��й���
FiveElem::FiveElem(FiveElementData fiveData)
{
	level = fiveData.level;
	element = (FIVE_ELEMENT_T)fiveData.element;
	expNow = fiveData.expNow;
	expForNext = fiveData.expForNext;
}

/****************************************************************
 * changeElem - �ı���������
 * @elem: ��Ҫ���ĳɵ���������ֵ
 * Return: bool�ͣ�false:������Ч����������ֵ��true:�ı�ɹ�
 ****************************************************************/
bool FiveElem::changeElem(FIVE_ELEMENT_T elem)
{
	//���ﲻ�ܸĳ�NOELEM
	if (elem < 1 || elem > 5)
	{
		return false;
	}
	element = elem;
	return true;
}

//�õ����еȼ�
int FiveElem::getLevel(void)
{
	return level;
}

//�õ����е�����ֵ
FIVE_ELEMENT_T FiveElem::getElem(void)
{
	return element;
}

/*****************************************************************
 * upGrade - ����������ÿ�ε��õȼ���1
 *
 * Return: false:����ʧ�ܣ��Ѿ�����������true:�����ɹ�
 *****************************************************************/
bool FiveElem::upGrade(void)
{
	if ((level + 1) > 60)
	{
		//�������������60��
		return false;
	}
	
	level++;
	
	//������������һ�ȼ���Ҫ�ľ���
	if (level < 60)
	{
		expForNext = heroFiveElemConf.upgradeNeedExp[level];	//������һ����Ҫ����ֵ
	}
	
	
	if (pg_hero->memHero->fiveElementData.level==40||pg_hero->memHero->fiveElementData.level==50||pg_hero->memHero->fiveElementData.level==60)
	{
		char info[1024]={'\0'};
		snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",7,SYSTEM_WARN,"xf012",3,1,pg_hero->getNickName(),pg_hero->getIdentity(),0,0,6,pg_hero->memHero->fiveElementData.element,0,0,0,3,pg_hero->memHero->fiveElementData.level,0,0,0);
		map<string, Hero*>::iterator it_hero;

		for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
		{
			if (it_hero->second!=NULL)
			{						
				send_msg(it_hero->second->getFd(),info);
			}
		}
	}
		
	
	return true;
}

/*****************************************************************
 * getValue - ��ȡ������ֵ
 * Return: ���ص�ǰ������ֵ
 *****************************************************************/
int FiveElem::getValue(void)
{
	int ret;
	if (level == 0 || element == NOELEM)
	{
		ret = 0;
	} else {
		ret = heroFiveElemConf.fiveValue[level];	//������һ����Ҫ����ֵ
	}
	
	return ret;
}

/*****************************************************************
 * getFactor - �����������п���
 * @hitElem: �����ߵ���������
 * Return: ���ر������ߵ����п���ֵ
 *****************************************************************/
double FiveElem::getFactor(FIVE_ELEMENT_T hitElem)
{
	double k;				//������֮�����п���ϵ��
	double ret;				//�������ߵ����п���
#if 0	
	//���������û����������
	if (hitElem == NOELEM)
	{
		//cout<<"BisonTest hit also no elem k is 1.0"<<endl;
		k = 1.0;
	}
	
	//�����������û����������
	 else if (element == NOELEM)
	{
		//cout<<"BisonTest NoElem k is 0.0"<<endl;
		k = 0.0;
	}
	
	
	else if ((hitElem % 5 + 1) == element)
	{
		//����������������Կ��Ʊ���������������
		k = 0.001;
	} else if ((element % 5 + 1) == hitElem)
	{
		//���������������Կ��ƹ�������������
		k = 0.003;
	} else {
		//�����ߺͱ��������������Ի�������
		k = 0.002;
	}

#endif
	k = heroFiveElemConf.defFactor[element - 1][hitElem - 1];
	//cout<<k<<endl;
	if (k == 1.0)
	{
		//�������߶�û���������ԵĹ����߿���Ϊ1
		//cout<<"BisonTest factor ret is 1"<<endl;
		ret = 1;
	} else if (k == 0.0) {
		//�߻�7.17�޸ģ������������������ԣ��ܵ��˺�Ϊ������������ֵ/10
		//cout<<"BisonTest factor ret is 0.9"<<endl;
		ret = 0.0;
	} else {
		//�������п���ϵ���������п���
		int value = getValue();
		ret = k *(value) / (1 + k * (value));
		// ret = k *(value - 500) / (1 + k * (value - 500));
	}
	return ret;
}

/*****************************************************************
 * getHurt - �����˺����㣬��ǰ���й�������Ϊ������
 * @k: ������ֵ�����п���
 * Return: ���������˺�ֵ
 *****************************************************************/
int FiveElem::getHurt(double k)
{
	//�����ߵ�������ֵ
	int value = getValue();
	//�����˺�
	//cout<<"k is "<<k<<endl;
	int ret = value * (1 - k);
	//cout<<"ret is "<<ret<<endl;
	return ret;
}

/*****************************************************************
 * addExp - �������о��飬�����жϱȶ���ȼ���25��������
 * @value: ���ӵľ���ֵ
 * Return: ���Ӿ����Ƿ�ɹ�
 *****************************************************************/
bool FiveElem::addExp(int value)
{
	if (level >= 60)
	{
		//��߼��ľͲ��ڼ���������
		return false;
	}
	
	if (value > 4)
	{
		//���е�һ��һ�ŵĳԣ����ĵ��Ǽ�4��,��˲����ܳ���4��
		return false;
	}
	
	expNow += value;
	if (expNow >= expForNext)
	{
		
		expNow -= expForNext;
		//��һ��
		upGrade();
		//������ƻ�Ҫ��ͻ��˷���Ϣ��֪ͨ�ͻ���
		if (level >= 60)
		{
			//�����ˣ���������
			expNow = expForNext;
		}
		
	}
	
	return true;
}

//��ǰ����
int FiveElem::getExpNow()
{
	/* cout<<"________________________"<<endl;
	cout<<expNow<<endl; */
	return expNow;
}

//������һ����Ҫ�ľ���
int FiveElem::getExpForNext()
{
	/* cout<<expForNext<<endl; */
	return expForNext;
}