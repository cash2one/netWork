/************************************************************
	�ļ�����partyRoomLimit.cpp
	�ļ����ã�ʵ����PartyRoomLimit��ķ���
	���ߣ�chenzhen
	�������ڣ�2012.12.14
************************************************************/
#include"map_src.h"
#include"partyRoomLimit.h"
#include"hero.h"
#include"guild_asist.h"

extern map<string,Map_Inform*>mapId_connect_map;
extern map<string,Map_Src*> confPartyRoom;
extern map<string, Hero*> heroId_to_pHero;

/*���ɷ��乹�캯��*/
PartyRoomLimit::PartyRoomLimit(char *_partyLimitId,char *_partyMapId,int _num,int _partyRank,int _room)
{
	memset(partyLimitId,'\0',sizeof(partyLimitId));
	memset(partyMapId,'\0',sizeof(partyMapId));
	
	strncpy(partyMapId,_partyMapId,strlen(_partyMapId));	
	strncpy(partyLimitId,_partyLimitId,strlen(_partyLimitId));
	
	num = _num;
	partyRank = _partyRank;
	room = _room;	
	activeFlg = false;
	initPartyMap();
	todayActiveFlg = false;
}

/*��ʼ�����ɷ���*/
void PartyRoomLimit::initPartyMap(void)
{
	map<string,Map_Src*>::iterator partyConf_it;
	Map_Src *modleMap,*newPartyMap;
	int i;	

	if(room <= 0)
	{
		return;
	}
	
	partyConf_it = confPartyRoom.find(partyMapId);	
	if(partyConf_it == confPartyRoom.end())
	{
		cout<<"the partyMapId is error:"<<partyMapId<<endl;
		return;
	}	
	modleMap = partyConf_it->second;
	
	for(i = 0;i < room;i++)
	{
		newPartyMap = modleMap->copyMap(i);
		if(newPartyMap == NULL)
		{
			cout<<"the newPartyMap is NULL error the copyMap is error:"<<partyMapId<<endl;
			return;
		}
		initPartyRom.push_back(newPartyMap);
		asistList.push_back(i);
	}
}

/*�������ɷ���*/
PartyRoomLimit::~PartyRoomLimit(void)
{
	
	Map_Src *partyMap;
	int i,length;	
	length = initPartyRom.size();
	for(i = 0; i< length;i++)
	{
		partyMap = initPartyRom[i];
		delete partyMap;
		partyMap = NULL;		
		initPartyRom[i] = partyMap;
	}
		
	initPartyRom.clear();
	{
		std::vector<Map_Src*> tmp;
		initPartyRom.swap(tmp);
	}
	asistList.clear();
}

/*���ð���ÿ������İ���ʵ��ָ��*/
void PartyRoomLimit::setMapPartyRoom(void)
{
	int i;	
	for(i = 0;i < room;i++)
	{
		initPartyRom[i]->setIsPartyRom(true);
		initPartyRom[i]->setPartyRoom(this);
	}
}

/*���˽����ɰ�����*/
bool PartyRoomLimit::qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason)
{	
	map<string,Hero*>::iterator hero_it;
	char *perNikName,*wagonId,*mapId,*npcMapId;
	int length,i,sizeFail,parRank;	
	Map_Inform *lastMap;	
	Hero *myHero;
	Point piexPt;
	Guild *myGuild;	
	
	length = heroId.size();
	
	/*û�пշ���*/
	if(asistList.empty())
	{
		cout<<"three is not resorce to this partyRooms:"<<partyMapId<<endl;		
		return false;		
	}
	
	/*��������*/
	if(length < num) 
	{
		cout<<"the person num is less:"<<length<<endl;
		return false;
	}
		
	for(i = 0;i < length;i++)
	{
		sizeFail = failure_reason->size;
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			return false;
		}
		perNikName = myHero->getNickName();
		lastMap = myHero->getMap();
		wagonId = myHero->memHero->wagonId;	
		mapId = lastMap->getMapId();
		myGuild = myHero->getGuild();
		
		
		if(lastMap == NULL ||  mapId == NULL || strlen(mapId) == 0)
		{
			return false;
		}		
		
		/*û�м������*/
		if(myGuild == NULL)
		{
			cout<<"you have not take part in any party:"<<endl;			
			failure_reason->member[sizeFail].failure_flag = PARMAP_ERROR_NOT_PARTY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}			
		parRank = myGuild->getLevel();
		/*���˰��ɵȼ��ʸ񲻹�*/
		if(parRank < partyRank)
		{			
			failure_reason->member[sizeFail].failure_flag = PARMAP_ERROR_RANK_LEVEL;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}			
		
		/*���˴��ڰ�̯״̬*/
		if(myHero->getHeroState()==5)
		{
			failure_reason->member[sizeFail].failure_flag = PARMAP_ERROR_IN_SELL_STATION;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}	
		
		/*���˴���Ѻ��״̬*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			failure_reason->member[sizeFail].failure_flag = PARMAP_ERROR_IN_YA_BIAO_STATION;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}		
	}
	return true;
}

/*������ɰ��᷿��*/
void PartyRoomLimit::assignRom(vector<string> &heroId,char *partyId)
{
	int roomNum;
	map<string,int>::iterator num_it;
	num_it = partyIdToRoomNum.find(partyId);
	
	cout<<"PartyRoomLimit::assignRom begin:"<<partyId<<endl;
	if(num_it == partyIdToRoomNum.end())
	{
		roomNum = asistList.front();
		asistList.pop_front();
	
		/*���䷿��ʧ��*/
		if(!entPartyRoom(heroId,roomNum))	
		{
			asistList.push_front(roomNum);
			return;
		}
		else
		{
		
#if 0
			cout<<"todayActiveFlg:"<<activeFlg<<endl;
			
			cout<<"todayActiveFlg:"<<todayActiveFlg<<endl;
			
			cout<<"initPartyRom[roomNum]->getIsActiveDishBru() first:"<<initPartyRom[roomNum]->getIsActiveDishBru()<<endl;			
	
			/*�л���һ��ǵ�һ��ˢ*/
			if(activeFlg && !initPartyRom[roomNum]->getIsActiveDishBru())
			{
				cout<<"systemDish begin:"<<partyId<<endl;		
			
				/*ϵͳ���*/
				systemDish(initPartyRom[roomNum],partyId);
			
				initPartyRom[roomNum]->setIsActiveDishBru(true);
			
				cout<<"systemDish end:"<<partyId<<endl;
			}
#endif	
		
			initPartyRom[roomNum]->setIsPartyRomBusy(true);
			partyIdToRoomNum[partyId] = roomNum;
			roomNumToPartyId[roomNum] = partyId;
		}
		
		
	}
	
	else
	{
		entPartyRoom(heroId,num_it->second);
		
		roomNum = num_it->second;
	}
	
#if 0
	/*�����л���һ��ǵ�һ��ˢ*/
	if(todayActiveFlg && !initPartyRom[roomNum]->getIsActiveDishBru())
	{
		cout<<"systemDish in PartyRoomLimit::assignRom begin:"<<partyId<<endl;		
			
		/*ϵͳ���*/
		systemDish(initPartyRom[roomNum],partyId);
			
		initPartyRom[roomNum]->setIsActiveDishBru(true);
		
		cout<<"systemDish in PartyRoomLimit::assignRom end:"<<partyId<<endl;
	}
#endif		

	
	/*��Կ�ʼ���һ��ǵ�һ��ˢ*/
	if(activeFlg && !initPartyRom[roomNum]->getIsActiveDishBru())
	{
		cout<<"systemDish in PartyRoomLimit::assignRom begin:"<<partyId<<endl;		
			
		/*ϵͳ���*/
		systemDish(initPartyRom[roomNum],partyId);
			
		initPartyRom[roomNum]->setIsActiveDishBru(true);
		
		cout<<"systemDish in PartyRoomLimit::assignRom end:"<<partyId<<endl;
	}
	
	cout<<"PartyRoomLimit::assignRom end:"<<partyId<<endl;
	
}

/*�����ɰ��ắ��*/
bool PartyRoomLimit::entPartyRoom(vector<string> &heroId,int _roomNum)  
{
	char chageSre[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	char mapRealId[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Hero*>::iterator hero_it;
	Point beforePiexPt,enterPt;
	char* mainSrcId,*mapId;
	Map_Inform *oldMap;	
	Map_Src *mapNow;	
	Hero *myHero;	
	int length,i;
	
	mapNow = initPartyRom[_roomNum];
	
	/*ˢ��4��������*/
	mapNow->brushTable();
	
	mapId = mapNow->getMapId();
	
	enterPt = mapNow->getEntPt();
	
	/*�����ͼid���Ա�ͻ���ʶ��*/
	strncpy(mapRealId,mapId,strlen(mapId) - 5);
	
	/*��ʼ�����л�������Ϣ*/
	sprintf(chageSre,"%d,%d,%d,%s,%d,%d,%d,%d,%d",SELECT_HERO_RETURN,CHANGE_SCENE,SUCCESS,\
			mapRealId,enterPt._x,enterPt._y,mapNow->getWarType(),mapNow->getChangePkType(),\
			mapNow->getMapType());
	
	length = heroId.size();		
	
	/*�޸���ҽ�ɫ��Ϣ*/
	for(i = 0;i < length;i++)
	{
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			continue;
		}		
		oldMap = myHero->getMap();
		mainSrcId = oldMap->getMapId();
		myHero->setMainSrc(mainSrcId);
		
		/*��ס������֮ǰ�ĵ�*/
		beforePiexPt = myHero->getLocation();
		myHero->setBeforePiexPt(beforePiexPt);
		
		/*�˳�ԭ����ͼ*/
		myHero->quit_scene();		
		
		/*������ͼ*/
		myHero->setMap(mapNow);
		
		myHero->setLocation(enterPt);
		 
		send_msg(myHero->getFd(),chageSre); 
		
		myHero->setWalkingFlg(false);		
		
		myHero->enter_scene();
	}	
	return true;
}


/*�˳����ɰ���*/
void PartyRoomLimit::exitPartyRoomAsist(vector<string> &heroId)
{		
	char *mainSrcId,chageSre[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Map_Inform*>::iterator mainSrc_it;
	map<string,Hero*>::iterator hero_it;
	Map_Inform *mainSrcMap;
	Point beforePiexPt;
	int length,i;	
	Hero *myHero;		
	
	if(heroId.empty())
	{
		return;
	}	
	
	length = heroId.size();
	
	/*�޸���ҽ�ɫ��Ϣ*/
	for(i = 0;i < length;i++)
	{
		memset(chageSre,'\0',sizeof(chageSre));
		hero_it = heroId_to_pHero.find(heroId[i]);
		if(hero_it == heroId_to_pHero.end())
		{
			continue;           
		}
		
		myHero = hero_it->second;
		
		mainSrcId = myHero->getMainSrc();	
		
		mainSrc_it = mapId_connect_map.find(mainSrcId);
		
		if(mainSrc_it == mapId_connect_map.end())
		{
			/*�Ҳ���������֮ǰ�ĵ�ͼ*/
			continue;
		}
		
		mainSrcMap = mainSrc_it->second;
		
		/*�˳�ԭ����ͼ*/
		myHero->quit_scene();
		
		/*���븱����ͼ*/
		myHero->setMap(mainSrcMap);
		
		beforePiexPt = myHero->getBeforePiexPt();
		
		myHero->setLocation(beforePiexPt);
		
		/*��ʼ�����л�������Ϣ*/
		snprintf(chageSre,sizeof(chageSre),"%d,%d,%d,%s,%d,%d,%d,%d,%d",SELECT_HERO_RETURN,\
		CHANGE_SCENE,SUCCESS,mainSrcId,beforePiexPt._x,beforePiexPt._y,\
		mainSrcMap->getWarType(),mainSrcMap->getChangePkType(),mainSrcMap->getMapType());
		
		send_msg(myHero->getFd(),chageSre); 
		
		myHero->setWalkingFlg(false);		
		
		myHero->enter_scene();
	}
}


/*���հ��ɰ���*/
void PartyRoomLimit::recoverPartyRom(int _room)
{
	map<string,int>::iterator partyId_it;
	map<int,string>::iterator room_it;  
	
	/*�����Խ��*/
	if(_room < 0 || _room >= room)
	{
		cout<<"the roomNum is error:"<<_room<<endl;
		return;
	}
	/*����Ϊ����״̬*/
	if(!((initPartyRom[_room])->getIsPartyRomBusy()))
	{
		return;
	}
	
	room_it = roomNumToPartyId.find(_room);
	if(room_it == roomNumToPartyId.end())
	{
		cout<<"it is error of the _room:"<<_room<<endl;
		return;
	}

	partyId_it = partyIdToRoomNum.find(room_it->second);
	if(partyId_it == partyIdToRoomNum.end())
	{
		cout<<"it is error of the partyId:"<<room_it->second<<endl;
		return;
	}
	
	roomNumToPartyId.erase(room_it);
	partyIdToRoomNum.erase(partyId_it);
	
	initPartyRom[_room]->initMap();
	asistList.push_front(_room);
}

/*ϵͳ���*/
void PartyRoomLimit::systemDish(Map_Src *treatMap,char *myGuildId)
{
	char *dishTypeId;
	
	cout<<"PartyRoomLimit::systemDish before:"<<myGuildId<<endl;
	
	if(myGuildId == NULL || strlen(myGuildId) == 0 || treatMap == NULL)
	{
		cout<<"the myGuildId or the treatMap is NULL:"<<endl;
		return;
	}
	
	dishTypeId = treatMap->getSystemTreatId();
	
	if(dishTypeId == NULL)
	{
		cout<<"the dishTypeId  is NULL:"<<endl;
		return;
	}
	
	systemTreatGuild(treatMap,dishTypeId,myGuildId);
	
	cout<<"PartyRoomLimit::systemDish end:"<<myGuildId<<endl;
}

/*����Ƿ�Ϊϵͳ��˱��ֵ*/
bool PartyRoomLimit::getActiveFlg(void)
{
	return activeFlg;
}

/*�����Ƿ�Ϊϵͳ��˱��ֵ*/
void PartyRoomLimit::setActiveFlg(bool _isActiveFlg)
{
	activeFlg = _isActiveFlg;
}


/*����Ƿ����Ϊϵͳ��˱��ֵ*/
bool PartyRoomLimit::getTodayActiveFlg(void)
{
	return todayActiveFlg;
}

/*�����Ƿ����Ϊϵͳ��˱��ֵ*/
void PartyRoomLimit::setTodayActiveFlg(bool _todayActiveFlg)
{
	todayActiveFlg = _todayActiveFlg;
}

/*����ϵͳ��ϯΪ�ɳ�״̬*/
void PartyRoomLimit::setSystemDishState(int _dishState)
{
	map<string,int>::iterator room_it;
		
	cout<<"PartyRoomLimit::setSystemDishState begin:"<<_dishState<<endl;
	for(room_it = partyIdToRoomNum.begin();room_it != partyIdToRoomNum.end();++room_it)
	{	
		initPartyRom[room_it->second]->setSystemDishState(_dishState);
	}
	cout<<"PartyRoomLimit::setSystemDishState end:"<<_dishState<<endl;
}

/*����ϵͳ��ϯΪû��ˢ��״̬*/
void PartyRoomLimit::setIsActiveDishBru(void)
{
	map<string,int>::iterator room_it;
	
	cout<<"PartyRoomLimit::setIsActiveDishBru begin:"<<endl;
	for(room_it = partyIdToRoomNum.begin();room_it != partyIdToRoomNum.end();++room_it)
	{	
		initPartyRom[room_it->second]->setIsActiveDishBru(false);
	}
	cout<<"PartyRoomLimit::setIsActiveDishBru end:"<<endl;
}

/*����ϵͳ��ϯΪ��ˢ��״̬*/
void PartyRoomLimit::setIsActiveDishBruTrue(void)
{
	map<string,int>::iterator room_it;
	
	cout<<"PartyRoomLimit::setIsActiveDishBruTrue begin:"<<endl;
	for(room_it = partyIdToRoomNum.begin();room_it != partyIdToRoomNum.end();++room_it)
	{	
		initPartyRom[room_it->second]->setIsActiveDishBru(true);
	}
	cout<<"PartyRoomLimit::setIsActiveDishBruTrue end:"<<endl;
}


/*ϵͳ��ϯ,��Щ�Ѿ�*/
void PartyRoomLimit::isTmeToDinner(void)
{
	map<string,int>::iterator party_it;
	int roomNum;
	for(party_it = partyIdToRoomNum.begin();party_it != partyIdToRoomNum.end();++party_it)
	{
		roomNum = party_it->second;		
		
		/*ϵͳ���*/
		systemDish(initPartyRom[roomNum],const_cast<char*>((party_it->first).c_str()));
		
		initPartyRom[roomNum]->setIsActiveDishBru(true);		
	}
}

/*�ر�ϵͳ����*/
void PartyRoomLimit::closeSystemDish(void)
{
	map<string,int>::iterator room_it;
	for(room_it = partyIdToRoomNum.begin();room_it != partyIdToRoomNum.end();++room_it)
	{	
		initPartyRom[room_it->second]->activeCloseDish();
	}
}

	

	