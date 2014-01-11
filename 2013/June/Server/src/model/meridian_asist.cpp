/****************************************************************
 * Filename: meridian_comm.cpp
 * 
 * Description: ����ϵͳ�Ĳ�������
 *
 * Original Author : bison, 2012-7-16
 *
 ****************************************************************/

#include"meridian.h"
#include"meridian_asist.h"
#include "money_operator.h"
#include"hero.h"
#include"my_time.h"

//�����������,����get��set����
// #define addHeroAttr(hero, Item, val) hero->set##Item(hero->get##Item() + val)

extern struct ev_loop *loops;
extern map<string, Hero*> heroId_to_pHero;

static void meridCalBak(struct ev_loop *loop, ev_timer *think, int revents);

//��������Ч����ֻ���ڲ�ʹ�ã����ṩ�ⲿ�ӿ�
static void upgradeEffect(MERID_TYPE_T now, int level, Hero *hero)
{
	if (now < 0 || now > 7 || level <= 0 || level > 90)
	{
		return;
	}
	if (heroMeridConf.item[now].incType1[level] < 100)
	{
		hero->addAttr(heroMeridConf.item[now].incType1[level], heroMeridConf.item[now].incVal1[level]);
	}
	if (heroMeridConf.item[now].incType2[level] < 100)
	{
		hero->addAttr(heroMeridConf.item[now].incType2[level], heroMeridConf.item[now].incVal2[level]);
	}
#if 0
	switch (now)
	{
	//����
	case RENM:
		// addHeroAttr(hero, LifeUpperVal, 320);	//Ѫ���޼�320
		// addHeroAttr(hero, MagicUpperVal, 320);	//ħ���޼�320
		hero->addAttr(0, 320);
		hero->addAttr(1, 320);
		break;
	//����
	case DUM:
		// addHeroAttr(hero, InAttack, 36);		//�ڹ� +36
		// addHeroAttr(hero, InHurt, 16);			//���� +16
		hero->addAttr(5, 36);
		hero->addAttr(11, 36);
		break;
	//����
	case CHONGM:
		// addHeroAttr(hero, OutAttack, 36);		//�⹥ +36
		// addHeroAttr(hero, OutHurt, 16);			//���� +16
		hero->addAttr(4, 36);
		hero->addAttr(10, 16);
		break;
	//����
	case DAIM:
		// addHeroAttr(hero, OutDefense, 36);		//��� +36
		// addHeroAttr(hero, InDefense, 36);		//�ڷ� +36
		hero->addAttr(2, 36);
		hero->addAttr(3, 36);
		break;
	//��ά
	case YINW:
		// addHeroAttr(hero, Hited, 1);			//���� +1
		hero->addAttr(6, 1);
		break;
	//��ά
	case YANGW:
		// addHeroAttr(hero, Crit, 1);			//���� +1
		hero->addAttr(9, 1);
		break;
	//����	
	case YINQ:
		// addHeroAttr(hero, Dodge, 1);			//���� +1
		hero->addAttr(7, 1);
		break;
	//����
	case YANGQ:
		// addHeroAttr(hero, Tenacity, 1);		//���� +1
		hero->addAttr(8, 1);
		break;
	
	default:
		return;
	}
#endif
}

static void upgradeHeroMerid(Hero *hero)
{

	//�������
	Meridian *merid = hero->getMerid();
	merid->upgrade();
	MERID_TYPE_T now = merid->getNow();
	upgradeEffect(now, merid->getLevel(), hero);
	hero->send_msg_att();
	if (now==YANGQ&&hero->memHero->meridData.level==MAX_MERIDIAN_LEVEL)
	{
		// hero->updataSingleTarget(44);
	}
	
	merid->setTimerBusy(false);			//��������ʱ��Ϊ����״̬
	hero->memHero->meridData.now = now;
	hero->memHero->meridData.level = merid->getLevel();
	hero->memHero->meridData.timerBusy = false;
	hero->memHero->meridData.remainTime = 0;
	hero->memSet();
	
	if(hero->memHero->meridData.level==40||hero->memHero->meridData.level==50||hero->memHero->meridData.level==60)
	{		
		char info[1024]={'\0'};
		snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",7,SYSTEM_WARN,"xf013",3,1,hero->getNickName(),hero->getIdentity(),0,0,5,now,0,0,0,3,hero->memHero->meridData.level,0,0,0);
		map<string, Hero*>::iterator it_hero;

		for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
		{
			if (it_hero->second!=NULL)
			{						
				send_msg(it_hero->second->getFd(),info);
			}
		}
	}

	//���ͻ��˷���һ����Ϣ������������Ӧ��Ҫ�ȼ���now�ڵ�
	char msg[64] = {0};
	int level = merid->getLevel();
	int i;
	sprintf(msg, "8,2");
	for (i = 0; i <= now; i++)
	{
		// msg += intTostring(level);
		sprintf(msg + strlen(msg), ",%d", level);
	}
	for (i = now; i < 7; i++)
	{
		// msg += intTostring(level - 1);
		sprintf(msg + strlen(msg), ",%d", level - 1);
	}
	// send_msg(hero->getFd(), msg);
}

//����memcache�����ľ���ʣ��ʱ��Ծ������д���
void restartMeridStudy(Hero *hero)
{
	//cout<<"BisonDon'twantyoutocomehere!!!!!!!!!"<<endl;
	if (hero == NULL || !hero->memHero->meridData.timerBusy)
	{
		return;
	}
	MeridData_T meridData = hero->memHero->meridData;
	Meridian *merid = hero->getMerid();
	int awayTime = MY_TV_SEC - hero->memHero->offlineTime;
	//cout<<"Bison merid remain Time is "<<meridData.remainTime<<endl;
	//cout<<"Bison merid remain Time is "<<meridData.timerBusy<<endl;
	//��ʱ����ʹ�û��߾�����������
	if (!meridData.timerBusy || merid->getLevel() >= MAX_MERIDIAN_LEVEL)
	{
		return;
		
	} else if (awayTime >= meridData.remainTime) {
		//�������, ֻ���������ж�
		upgradeHeroMerid(hero);
		return;
		
	}	else {
		int remain = meridData.remainTime - awayTime;
		ev_timer *meridTimer = merid->getTimer();
		ext_ev_timer_init(meridTimer, meridCalBak, remain, 0, hero);
		//��Ҫ����Ķ���ӵ���������
		//timers4meridian->push_front(wait, hero, heroId);
		//timers4meridian->push_front(remain, hero, hero->getIdentity());
		ev_timer_start(loops, meridTimer);
		merid->setTimerBusy(true);
		
		//cout<<"###########################you can t come here OK!"<<endl;
		return;
	}
}

//��ʼ��������
int startMeridStudy(Hero *hero, int index, char* result)
{
	if (hero->getLevel() < heroMeridConf.startLevel)
	{
		//����δ����
		return 1;
	}
	Meridian *merid = hero->getMerid();
	int level = merid->getLevel();
	ev_timer *meridTimer = merid->getTimer();
	MERID_TYPE_T now = merid->getNow();
	int willLevel = level;
	if (now == YANGQ)
	{
		willLevel += 1;
	}
	int currLevel = willLevel - 1;
	int willMerid = (now + 1) % 8;
	if (heroMeridConf.item[willMerid].needHeroLevel[willLevel] > hero->getLevel())
	// if (now == YANGQ && level >= hero->getLevel() - 15)
	{
		//����ȼ�������������ǰ�ȼ�����
		return 2;
	}
	if (now == YANGQ && currLevel == MAX_MERIDIAN_LEVEL)
	{
		//�����Ѿ��ﵽ���ȼ�
		return 3;
	}
	if (merid->getTimerBusy())
	{
		//��������
		cout<<"The hero already has the studying merid now!"<<endl;
		return 4;
	}
	
#if 0	
	if (willMerid != index)
	{
		//ѡ�еľ������ǵ�ǰ��������һ��
		cout<<"selected merid is not the next to study!"<<endl;
		return 5;
	}
#endif	

	//������һ����ʱ��������
	// if (now != YANGQ)
	// {
		// level -= 1;
	// }
	
	//��������ʱ����ڵȼ�������
	// int wait = level * level * level;
	cout<<"now is "<<willMerid<<" level is "<<currLevel<<" time is"<<heroMeridConf.item[willMerid].time[currLevel]<<endl;
	int wait = heroMeridConf.item[willMerid].time[currLevel];
	
	// ret += intTostring((now + 1) % 8);
	// ret += intTostring(wait);
	// ret += intTostring(level);
	// cout<<"111111111111111111111111111111111111111111111111111"<<endl;
	sprintf(result, ",%d,%d,%d", willMerid, wait, currLevel);
	// cout<<result<<endl;
	if (wait == 0)
	{	
		//�������
		upgradeHeroMerid(hero);
		
		merid->setTimerBusy(false);			//��������ʱ��Ϊ����״̬
	} else {
		ext_ev_timer_init(meridTimer, meridCalBak, wait, 0, hero);
		//��Ҫ����Ķ���ӵ���������
		//timers4meridian->push_front(wait, hero, heroId);
		//timers4meridian->push_front(wait, hero, hero->getIdentity());
		ev_timer_start(loops, meridTimer);
		merid->setTimerBusy(true);
		
		hero->memHero->meridData.now = now;
		hero->memHero->meridData.level = merid->getLevel();
		hero->memHero->meridData.timerBusy = true;
		hero->memHero->meridData.remainTime = wait;
		hero->memSet();
	}
	
	//jolly add wulintarget 12.4 start
	// hero->updataSingleTarget(8);
	//jolly add wulintarget 12.4 end
	
	
	return 0;
}

//�����������ڻص�������ֻ���ڲ�ʹ�ã����ṩ�ⲿ�ӿ�
static void meridCalBak(struct ev_loop *loop, ev_timer *think, int revents)
{
	ev_timer_stop(loop, think);
	
	//Hero *hero = timers4meridian->pop_front();
	Hero *hero = (Hero *)think->target;
	if (hero == NULL)
	{
		cout<<"BisonTest at meridian_asist.cpp:38: The timerList pop hero obj error!"<<endl;
		return;
	}
	
	upgradeHeroMerid(hero);
	
}


//�������ʱֹͣ������ʱ��
void stopMeridianTimer(char* heroId)
{
	//Hero *hero = timers4meridian->find(heroId);
	Hero *hero = heroid_to_hero(heroId);
	if (hero == NULL)
	{
		return;
	}
	if (!hero->memHero->meridData.timerBusy)
	{
		return;
	}
	Meridian *merid = hero->getMerid();
	ev_timer* timer = merid->getTimer();
	//int remain = timers4meridian->getTimerRemain(heroId);//��ʱ����ʣ���ʱ��
	int remain = (int)ev_timer_remaining(loops, timer);
	//timers4meridian->delInRun(heroId);					//ɾ��δ������ʱ����Ӧ�Ķ���ڵ�
	ev_timer_stop(loops, timer);							//ֹͣ��ʱ��
	
	//ת��int������1��ľͲ�����
	if ((int)remain <= 0)
	{
		//������ɻص�
		meridCalBak(loops, timer, 0);
		
	} else {
		hero->memHero->meridData.now = merid->getNow();
		hero->memHero->meridData.level = merid->getLevel();
		hero->memHero->meridData.timerBusy = true;
		hero->memHero->meridData.remainTime = remain;
		hero->memSet();
	}
}

//ʹ�õ���,���ж�ʹ�õ��߿��Գɹ���
int useMeridGoods(Hero *hero, char* goodsId, int index, int num, char* result)
{
	Bag *bag = hero->getBag();
	char* heroId = hero->getIdentity();
	// string ret;
	
	//��Ԥ��ʹ�õ��߿ɷ�ɹ�
	if (!bag->test(index, goodsId))
	{
		cout<<"BisonTest: no this goodsId in bag when use MeridGoods"<<endl; 
		return 1;
	}
	
	if (bag->getGridNum(index) < num)
	//if (bag->getGridNum(index) < 1)
	{
		cout<<"BisonTest: num is not enough when use MeridGoods"<<endl;
		return 2;
	}
	
	//����Ԥ�У����߿���ʹ�óɹ�
	//�Ծ�����ʱ�����в���
	
	Meridian* merid = hero->getMerid();
	ev_timer* timer = merid->getTimer();
	
	int remain = ev_timer_remaining(loops, timer);		//��ʱ����ʣ���ʱ��
	if (remain <= 0)
	{
		//ָ����Ӣ�۵ľ�����ʱ�����ڼ�ʱ
		cout<<"BisonTest: hero has no meridianTimer in timers4meridian when use meridian goods!"<<endl;
		return 3;
	}
	
	//ֻҪ�ܽ��뵽�����һ����ʹ�óɹ�
	useBagGoods(hero,goodsId, index, num); 
	//useBagGoods(hero,goodsId, index, 1); 
	
	MERID_TYPE_T now = merid->getNow();	//��ǰ����
	
	ev_timer_stop(loops, timer);							//ֹͣ��ʱ��
	//���߼��ٵ�����ʱ��
	int dec = 10 * 60 * num;						//����ֻ��һ�ִ������-�ػ���
	//int dec = 10 * 60 * 1;						//����ֻ��һ�ִ������-�ػ��� 
	// if (goodsId == "small_jm_dan")
	// {
		// dec = 10.;
	// } else if (goodsId =="mid_jm_dan") {
		// dec = 50.;
	// } else if (goodsId =="big_jm_dan") {
		// dec = 100.;
	// }
	
	
	//ʹ�õ��ߺ�ʣ���ʱ��
	remain -= dec;
	if ((remain) <= 0)
	{
		//ʹ����Ʒ���������
		remain = 0;
		//meridCalBak(loops, timer, 0);
		upgradeHeroMerid(hero);
		
	} else {
		//������ٵ�ʱ�仹������ʹ��ʱ������
		ev_timer_set(timer, remain, 0);
		ev_timer_start(loops, timer);
		
		hero->memHero->meridData.timerBusy = true;
		hero->memHero->meridData.remainTime = remain;
		hero->memSet();
	}
	
	int level = merid->getLevel();		//�����ȼ�
	
	// ret += intTostring((now + 1) % 8);		
	// ret += intTostring(remain);
	// ret += intTostring(level);
	sprintf(result, ",%d,%d,%d", (now + 1) % 8, remain, level);
	return 0;
}

//ȡ������ѧϰ
bool cancelMeridStudy(char* heroId)
{
	//��ɫid�õ���ɫʵ��
	Hero *hero = heroid_to_hero(heroId);

	//ָ����Ӣ�۲����ڣ�
	if (hero == NULL)
	{
		cout<<"BisonTest at meridian_asist.cpp:175: can't find the specified timer!"<<endl;
		return false;
	}
	//������ʱ�����ڼ�ʱ
	Meridian *merid = hero->getMerid();
	ev_timer *timer = merid->getTimer();
	int remain = ev_timer_remaining(loops, timer);
	if (remain <= 0)
	{
		ev_timer_stop(loops, merid->getTimer());
	}
	merid->setTimerBusy(false);
	
	hero->memHero->meridData.timerBusy = false;
	hero->memHero->meridData.remainTime = 0;
	hero->memSet();
	return true;
	
}

//����ǿ��
int strenMerid(Hero *hero, char* result)
{
	// string ret;
	/*
	Hero *hero;
	map<string, Hero*>::iterator iter;
	iter = heroId_to_pHero.find(heroId);
	if(iter == heroId_to_pHero.end())
	{
		return false;
	}
	hero = iter->second;
	*/
	Meridian *merid = hero->getMerid();
	
	//�ж���ҵ�Ǯ��������
	Money *heroMoney = hero->getMoney();
	if (heroMoney->money_getGold() < merid->getLevel())
	{
		return 1;
	}
	
	if(!merid->strengthen())
	{
		return 2;
	}
	
	useGold(hero,merid->getLevel());
	MERID_TYPE_T now = merid->getNow();
	int level = merid->getLevel();
	
	upgradeEffect(now, level, hero);
	// ret += intTostring(now);
	// ret += intTostring(level);
	sprintf(result, ",%d,%d", now, level);
	hero->memHero->meridData.now = now;
	hero->memHero->meridData.level = level;
	hero->memSet();
	
	return 0;
}

int getTotalLevel(Hero *hero)
{
	if(NULL == hero)
		return 0;
		
	Meridian *merid = hero->getMerid();
	int now = merid->getNow();
	int level = merid->getLevel();
	int totalLevel = (now + 1) * level + (7 - now) * (level - 1);
	return totalLevel;
}

//��Ԫ�����پ�������ʱ��
int decMeridTimeWithGold(Hero *hero, int flag, char *result)
{
	if (flag != 0 && flag != 1)
	{
		//ʹ��Ԫ���ͻ��˷��͵�ģʽ�д�(0:Ԫ��������1:һ������)
		return 6;
	}
	char* heroId = hero->getIdentity();
	Meridian* merid = hero->getMerid();
	if (merid == NULL)
	{
		//���δ��������
		return 7;
	}
	ev_timer* timer = merid->getTimer();
	if (!merid->getTimerBusy())
	{
		//��Ҿ�������������
		return 8;
	}
	
	int remain = ev_timer_remaining(loops, timer);		//��ʱ����ʣ���ʱ��
	if (remain <= 0)
	{
		//ָ����Ӣ�۵ľ�����ʱ�����ڼ�ʱ
		cout<<"BisonTest: hero has no meridian in study!!!"<<endl;
		//��Ҿ��������Ѿ����ڹ�
		return 9;
	}
	
	Money *heroMoney = hero->getMoney();
	if (flag == 0)
	{
		if (!useBoundGold(hero, heroMeridConf.needBoundGoldPerFiveMin))
		{
			//���Ԫ������
			return 10;
#if 0		
			int boundGold = heroMoney->getBoundGold();
			if (boundGold < 0)
			{
				//boundGoldΪ��ֵ�����ǻ��˺���
				return 5;
			}
			if (!heroMoney->useGold(5 - boundGold))
			{
				return 6;
			}
			
			heroMoney->useBoundGold(boundGold);
#endif
		}
		
		if (remain <= 300)
		{
			upgradeHeroMerid(hero);
			remain = 0;
		}
		else
		{
			remain -= 300;
			//������ٵ�ʱ�仹������ʹ��ʱ������
			ev_timer_set(timer, remain, 0);
			ev_timer_start(loops, timer);
			
			hero->memHero->meridData.timerBusy = true;
			hero->memHero->meridData.remainTime = remain;
			hero->memSet();
		}
	}
	//һ��������������ʱ�䶼����
	else if (flag == 1)
	{
		unsigned num = remain / 300 + ((remain % 300) ? 1 : 0);
		unsigned needGold = num * heroMeridConf.needBoundGoldPerFiveMin;
		if (!useBoundGold(hero,needGold))
		{
			//���Ԫ������
			return 10;
#if 0		
			int boundGold = heroMoney->getBoundGold();
			if (boundGold < 0)
			{
				return 5;
			}
			if (!heroMoney->useGold(needGold - boundGold))
			{
				return 6;
			}
			
			heroMoney->useBoundGold(boundGold);
#endif
		}
		
		upgradeHeroMerid(hero);
		remain = 0;
	}
	
	int level = merid->getLevel();		//�����ȼ�
	int now = merid->getNow();
	sprintf(result, ",%d,%d,%d", (now + 1) % 8, remain, level);
	return 0;
}