/****************************************************************
 * Filename: guild_war_asist.cpp
 * 
 * Description: ��ս���丨����
 *
 * Original Author : bison, 2012-8-28
 *
 ****************************************************************/
 
#include"guild_war_asist.h"

#define NORMAL_VESION_FOR_GUILD_WAR

extern map<string,Map_Src*> mapId_connect_map;
extern MapType_T mapTypeInfo;		//Ĭд�����ͼ��ID��
//��ս�����๹��
GuildWarAsist::GuildWarAsist()
{
	int i;
	Map_Src  *warMap = NULL;	
	map<string,Map_Src*>::iterator it_map;
	
	// char* scene_id = mapTypeInfo.guidWarMapId;  //����ս��ͼID��
	it_map = mapId_connect_map.find(mapTypeInfo.guidWarMapId);
	if(it_map == mapId_connect_map.end()){
		return ;
	}
	warMap = it_map->second;
	
	for(i = MAX_GUILD_WAR_ROOM_NUM - 1; i >= 0; i--)
	{
		Map_Src *scene = NULL;
		//���õ�ͼ����ĸ��Ʒ���
		scene = warMap->copyMap(i);
		
		GuildWarRoom *room = new GuildWarRoom(i, scene);
		
		//cout<<"BisonShow : all thing is OK!"<<endl;
		//�ӵ����а�ս���������
		allGuildWarRooms.insert(pair<string, GuildWarRoom*>(room->getId(), room));
		//���뵽���з�������
		idleGuildWarRooms.push_back(room);
	}
//	isInGuildWarTime = false; //set to true for test benliao 20121126
#if defined(NORMAL_VESION_FOR_GUILD_WAR)
	isInGuildWarTime = false;
#else
	isInGuildWarTime = true;
#endif
}

//����ռ���ս��������λ��
int GuildWarAsist::hostHoldGuildWarRoom(Hero *manager, int mode, char* password)
{
#if defined(NORMAL_VESION_FOR_GUILD_WAR)
	if (!isInGuildWarTime)
	{
		//���ڰ�ս����ʱ��
		return 5;
	}
#endif
#if 0
	if (!manager->canJoinGuildWar())
	{
		//��ҽ����Ѿ��μӹ�����ս
		return 7;
	}
#endif

	if (strlen(manager->memHero->wagonId) != 0)
	{
		//����������У����ܽ���
		return 6;
	}
	if(idleGuildWarRooms.size() == 0)
	{
		//û�п��з�����Դ
		return 1;
	}
	
	if (manager->isInGuildWarRoom())
	{
		//����Ѿ��ڰ�ս�������ˣ������ٴ������뷿��
		return 2;
	}
	
	
	if (mode == 1 && (password == NULL || strlen(password) == 0))
	{
		//ѡ��ԼսҪ�跿�䱣������
		return 4;
	}
	
	int title = manager->getGuildTitle();
	if (title != 0 && title != 1)
	{
		//ֻ�а�����ռ�췿��
		return 3;
	}
	
	Guild *guild = getGuildWithName(manager->getGuildName());
	if (guild == NULL)
	{
		return 8;
	}
	if (guild->isInGuildWarRoom())
	{
		return 9;
	}
	
	//���ڰ��ɻ�û�вμӰ�ս
	guild->setJoinGuildWar(true);
	
	GuildWarRoom *room = idleGuildWarRooms.back();
	idleGuildWarRooms.pop_back();

	//���·���״̬
	room->setRoomState(GWR_ONE);
	//����ռ�췿��
	
	//cout<<"BisonTest cout<<!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	room->holdRoom(manager);
	
	//cout<<"BisonTest cout<<^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
	if (mode == 1)
	{
		//Լսģʽ
		room->lockRoom(password);
		room->startLockTimer();
	}
	//cout<<"BisonTest cout<<$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	return 0;
}

//����ռ���ս����Ͱ�λ��
int GuildWarAsist::guestHoldGuildWarRoom(Hero *manager, char* roomId, char* password)
{
#if defined(NORMAL_VESION_FOR_GUILD_WAR)
	if (!isInGuildWarTime)
	{
		//���ڰ�ս����ʱ��
		return 6;
	}
#endif	
#if 0	
	if (!manager->canJoinGuildWar())
	{
		//��ҽ����Ѿ��μӹ�����ս
		return 8;
	}
#endif
	if (strlen(manager->memHero->wagonId) != 0)
	{
		//����������У����ܽ���
		return 7;
	}
	int title = manager->getGuildTitle();
	if (title != 0 && title != 1)
	{
		//ֻ�а�����ռ�췿��
		return 1;
	}
	
	if (manager->isInGuildWarRoom())
	{
		//�ð����Ѿ���һ����ս��������
		return 2;
	}
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return 3;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	unsigned roomState = room->getRoomState();
	if (!(roomState & GWR_ONE))
	{
		//������δ�����������ɣ��޷���ս
		return 12;
	}
	
	if (roomState & GWR_TWO)
	{
		//�����Ѿ�����������ռ��
		return 4;
	}
	
	if ((roomState & GWR_LOCK) && ( (password == NULL || strlen(password) == 0) || !room->isPassOK(password)))
	{
		//����ķ������벻��ȷ
		return 5;
	}
	
	Guild *guild = getGuildWithName(manager->getGuildName());
	if (guild == NULL)
	{
		//��ҵİ��ɲ�����
		return 10;
	}
	if (guild->isInGuildWarRoom())
	{
		//��ҵİ������ڲμӰ�ս��
		return 11;
	}
	
	//���·���״̬
	room->setRoomState(GWR_TWO);
	//����ռ�췿��
	int ret = room->holdRoom(manager);
	if (ret != 0)
	{
		//������ս�Լ�����
		return 9;
	}
	
	//���ڰ��ɻ�û�вμӰ�ս
	guild->setJoinGuildWar(true);
	
	//����hero�Ѿ��ڰ�ս����
	manager->setInGuildWarRoom(true, room->getId());
	
	
	//���俪ʼ�ٻ�����
	return 0;
}

//���ڽ����ս����
int GuildWarAsist::JoinGuildWar(Hero *hero, char* roomId)
{
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//û�а��ɵ���
		return 1;
	}

#if 0	
	if (!hero->canJoinGuildWar())
	{
		//��ҽ����Ѿ��μӹ�����ս
		return 5;
	}
#endif

	if (strlen(hero->memHero->wagonId) != 0)
	{
		//����������У����ܽ���
		return 4;
	}
	
	if (hero->isInGuildWarRoom())
	{
		//������Ѿ��ڰ�ս������
		return 2;
	}
	
	Guild *guild = getGuildWithName(hero->getGuildName());
	if (guild == NULL)
	{
		//��ҵİ����Ѿ������ڻ������δ�������
		return 6;
	}
	if (!guild->isInGuildWarRoom())
	{
		//��ҵİ���û�����ڲ�ս
		return 7;
	}
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return 3;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	//0�ǳɹ���-1������ڰ���δռ��÷���
	return room->joinRoom(hero);
}

//����ս�˺�ͳ��
int GuildWarAsist::hurtCount(Hero *hero, int value)
{
	if (!hero->isInGuildWarRoom())
	{
		return 1;
	}
	
	string roomId = hero->getGuildWarRoomId();
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return 2;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	room->guildWarAddHurtCount(hero, value);
	return 0;
}

//ɱ����ͳ��
int GuildWarAsist::killCount(Hero *hero)
{
	if (!hero->isInGuildWarRoom())
	{
		return 1;
	}
	
	string roomId = hero->getGuildWarRoomId();
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return 2;
	}
	
	GuildWarRoom *room;
	room = it->second;
	room->guildWarAddOneHeroKillNum(hero);
	return 0;
}

//�鿴��ս����״̬
int GuildWarAsist::viewRoomState(Hero *hero, char* result)
{
	// char* viewResult;
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.begin();
	
	//������
	// viewResult += intTostring(isInGuildWarTime);
	// viewResult += intTostring(allGuildWarRooms.size());
	sprintf(result + strlen(result), ",%d,%d", isInGuildWarTime, (int)(allGuildWarRooms.size()));
	//�����������״̬
	for (it; it != allGuildWarRooms.end(); it++)
	{
		GuildWarRoom* room;
		room = it->second;
		int state = room->getRoomState();
		
		int remain = 0;
		if (state & GWR_LOCK)
		{
			remain = room->getRemainTime();
		}
		// viewResult += "," + room->getId();
		//remainΪ0��������δ����
		// viewResult += intTostring(remain);
		sprintf(result + strlen(result), ",%s,%d", room->getId(), remain);
		for (int i = 0; i < 2; i++)
		{
			Hero *hero = room->getHost(i);
			if (hero != NULL)
			{
				sprintf(result + strlen(result), ",%s", hero->getGuildName());
				// viewResult += "," + hero->getGuildName();
			} else {
				// viewResult += ",";
				sprintf(result + strlen(result), ",");
			}
		}
	}
	
	return 0;
}

//�ٻ�����
void GuildWarAsist::callJoinWar(Hero *hero)
{
	if (!hero->isInGuildWarRoom())
	{
		return;
	}
	
	// if (hero->getGuildTitle() != 0)
	// {
		//���ǰ����������ٻ��������д�����--����������˲��ǰ�������
		// return;
	// }
	
	char* roomId = hero->getGuildWarRoomId();
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	room->callJoin(hero);
}

//����׼��
int GuildWarAsist::managerPrepare( Hero *hero)
{
	if (!hero->isInGuildWarRoom())
	{
		return 1;
	}
	
	// if (hero->getGuildTitle() != 0)
	// {
		//���ǰ��������ܴ����������д�����--����������˲��ǰ�������
		// return 2;
	// }
	
	char* roomId = hero->getGuildWarRoomId();
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
		cout<<"BisonWarn: you record the wrong guildWarRoom Id"<<endl;
		cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
		return 3;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	room->prepareGuildWar(hero);
}

//����ս�˳�
void GuildWarAsist::exitGuildWar(Hero *hero, bool offlineFlag)
{
	if (!hero->isInGuildWarRoom())
	{
		return;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return;
	}
	
	GuildWarRoom *room;
	room = it->second;
	//������Ϊ���ߵ��˳�
	room->exit(hero, offlineFlag);
	hero->setInGuildWarRoom(false, NULL);
}

//�ͷ�һ��������Դ
void GuildWarAsist::freeOneRoom(GuildWarRoom *room)
{
	room->resetRoom();
	idleGuildWarRooms.push_back(room);
}

//�����Ƿ��ڰ�սʱ��
void GuildWarAsist::setIsInGuildWarTime(bool start)
{
	isInGuildWarTime = start;
}
//�鿴�Ƿ��ڰ���ս������
bool GuildWarAsist::getIsInGuildWarTime()
{
	return isInGuildWarTime;
}

//�鿴������ڰ���ս�����״̬
int GuildWarAsist::getOneRoomState(Hero* hero)
{
	char* roomId = hero->getGuildWarRoomId();
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return 0;
	}
	
	GuildWarRoom *room;
	room = it->second;
	return room->getRoomState();
}

int GuildWarAsist::guildWarRevival(Hero* hero)
{
	
	char* roomId = hero->getGuildWarRoomId();
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return 1;
	}
	
	GuildWarRoom *room;
	room = it->second;
	int ret = room->revival(hero);
	return ret;
}

//�Ƿ���Բɼ�����
/**
 * ����ʧ��ԭ��
	1:���ڰ���ս������
	2:���ڰ�ս����ʱ��
	3:������ڰ�ս���䲻����
	4:��սδ����ʼ״̬
	-1:�ɼ���Ʒ���Ͳ�Ϊ��ս��
	-2:�������ڱ��ɼ���
	-3:�����Ѿ���ռ��
	-4:�����ѱ��Լ����ɲɼ�
	-5:�������������챻ռ�ݺ�ɲ�
 */
int GuildWarAsist::isHeroPickFlagOk(Hero *hero, int type)
{
	//����ս����
	if(!hero->isInGuildWarRoom())
	{
		//���ڰ���ս�����в��ܲɼ�������
		return 1;
	}

	if (!isInGuildWarTime)
	{
		//���ڰ�ս����ʱ��
		return 2;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return 3;
	}
	
	GuildWarRoom *room;
	room = it->second;
	int roomState = room->getRoomState();
	if (!(roomState & GWR_START))
	{
		return 4;
	}
	
	int ret = room->isPickFlagOk(hero, type);
	return ret;
	
}

//����
int GuildWarAsist::finishPickFlag(Hero *hero, int type)
{
	//����ս����
	if(!hero->isInGuildWarRoom())
	{
		//���ڰ���ս�����в��ܲɼ�������
		return 1;
	}

	if (!isInGuildWarTime)
	{
		//���ڰ�ս����ʱ��
		return 2;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return 3;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	int ret = room->finishPickFlag(hero, type);
	return ret;
}

//ֹͣ����
int GuildWarAsist::stopPickFlag(Hero *hero, int type)
{
	//����ս����
	if(!hero->isInGuildWarRoom())
	{
		//���ڰ���ս�����в��ܲɼ�������
		return 1;
	}
	
	
	char* roomId = hero->getGuildWarRoomId();
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//û�и÷���Id��Ӧ�ķ���
		return 2;
	}
	
	GuildWarRoom *room;
	room = it->second;
	int ret = room->stopPickFlag(type);
	return ret;
}
