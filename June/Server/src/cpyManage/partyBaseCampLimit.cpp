/************************************************************
	�ļ�����partyBaseCampLimit.cpp
	�ļ����ã�ʵ����partyBaseCampLimit��ķ���
	���ߣ�chenzhen
	�������ڣ�2012.12.14
************************************************************/
#include"map_src.h"
#include"partyBaseCampLimit.h"
#include"hero.h"


extern map<string,Map_Inform*>mapId_connect_map;
extern map<string,Map_Src*> confCampRoom;
extern map<string, Hero*> heroId_to_pHero;

/*���ɴ�Ӫ���캯��*/
PartyBaseCampLimit::PartyBaseCampLimit(char *_campLimitId,char *_campMapId,int _num,int _partyRank,int _room)
{
	memset(campLimitId,'\0',sizeof(campLimitId));
	memset(campMapId,'\0',sizeof(campMapId));
	
	strncpy(campLimitId,_campLimitId,strlen(_campLimitId));	
	strncpy(campMapId,_campMapId,strlen(_campMapId));
	
	num = _num;
	partyRank = _partyRank;
	room = _room;	
	isOpen = true;
	initCampMap();
}

/*��ʼ�����ɴ�Ӫ����*/
void PartyBaseCampLimit::initCampMap(void)
{
	map<string,Map_Src*>::iterator campConf_it;
	Map_Src *modleMap,*newCampMap;
	int i;	

	if(room <= 0)
	{
		return;
	}
	
	campConf_it = confCampRoom.find(campMapId);	
	if(campConf_it == confCampRoom.end())
	{
		cout<<"the campMapId is error:"<<campMapId<<endl;
		return;
	}	
	modleMap = campConf_it->second;
	
	for(i = 0;i < room;i++)
	{
		newCampMap = modleMap->copyMap(i);
		if(newCampMap == NULL)
		{
			cout<<"the newPartyMap is NULL error the copyMap is error:"<<campMapId<<endl;
			return;
		}
		initCampRom.push_back(newCampMap);
		asistList.push_back(i);
	}
}

/*�������ɴ�Ӫ*/
PartyBaseCampLimit::~PartyBaseCampLimit(void)
{
	
	Map_Src *campMap;
	int i,length;	
	length = initCampRom.size();
	for(i = 0; i< length;i++)
	{
		campMap = initCampRom[i];
		delete campMap;
		campMap = NULL;		
		initCampRom[i] = campMap;
	}
		
	initCampRom.clear();
	{
		std::vector<Map_Src*> tmp;
		initCampRom.swap(tmp);
	}
	asistList.clear();
}

/*���ð��ɴ�Ӫÿ������İ���ʵ��ָ��*/
void PartyBaseCampLimit::setMapCampRoom(void)
{
	int i;	
	for(i = 0;i < room;i++)
	{
		initCampRom[i]->setIsCampRom(true);
		initCampRom[i]->setCampRoom(this);
	}
}

/*���˽����ɴ�Ӫ������*/
bool PartyBaseCampLimit::qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason,bool _enterFlg)
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
		cout<<"three is not resorce to this campRooms:"<<campMapId<<endl;		
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
			failure_reason->member[sizeFail].failure_flag = CAMP_ERROR_NOT_PARTY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}			
		parRank = myGuild->getLevel();
		
		/*���˰��ɵȼ��ʸ񲻹�*/
		// if(parRank < partyRank)
		// {			
			// failure_reason->member[sizeFail].failure_flag = CAMP_ERROR_RANK_LEVEL;
			// strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			// failure_reason->size += 1;
			// return false;
		// }			
		
		/*���˴��ڰ�̯״̬*/
		if(myHero->getHeroState() == 5)
		{
			failure_reason->member[sizeFail].failure_flag = CAMP_ERROR_IN_SELL_STATION;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}	
		
		/*���˴���Ѻ��״̬*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			failure_reason->member[sizeFail].failure_flag =CAMP_ERROR_IN_YA_BIAO_STATION;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}
		/*̽Ӫʱ�仹û�е�*/
		if(_enterFlg && !isOpen)
		{
			failure_reason->member[sizeFail].failure_flag = CAMP_ERROR_TIME_NOT_OPEN;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}
	}
	return true;
}

/*������ɰ��᷿��*/
void PartyBaseCampLimit::assignRom(vector<string> &heroId,char *partyId)
{
	int roomNum;
	map<string,int>::iterator num_it;
	num_it = partyIdToRoomNum.find(partyId);
	
	if(num_it == partyIdToRoomNum.end())
	{
		roomNum = asistList.front();
		asistList.pop_front();
	
		/*���䷿��ʧ��*/
		if(!entCampRoom(heroId,roomNum))	
		{
			asistList.push_front(roomNum);
			return;
		}		
		initCampRom[roomNum]->setIsCampRomBusy(true);
		partyIdToRoomNum[partyId] = roomNum;
		roomNumToPartyId[roomNum] = partyId;
	}
	
	else
	{
		entCampRoom(heroId,num_it->second);
	}
	
}

/*�����ɰ��ắ��*/
bool PartyBaseCampLimit::entCampRoom(vector<string> &heroId,int _roomNum)  
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
	
	mapNow = initCampRom[_roomNum];
	
	mapId = mapNow->getMapId();
	
	enterPt = mapNow->getEntPt();
	
	/*�����ͼid���Ա�ͻ���ʶ��*/
	strncpy(mapRealId,mapId,strlen(mapId) - 5);
	
	/*��ʼ�����л�������Ϣ*/
	sprintf(chageSre,"%d,%d,%d,%s,%d,%d,%d,%d,%d",SELECT_HERO_RETURN,\
	CHANGE_SCENE,SUCCESS,mapRealId,enterPt._x,enterPt._y,\
	mapNow->getWarType(),mapNow->getChangePkType(),\
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
void PartyBaseCampLimit::exitCampRoomAsist(vector<string> &heroId)
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
		snprintf(chageSre,sizeof(chageSre),"%d,%d,%d,%s,%d,%d,%d,%d,%d",SELECT_HERO_RETURN,CHANGE_SCENE,SUCCESS,mainSrcId,beforePiexPt._x,\
		beforePiexPt._y,mainSrcMap->getWarType(),\
		mainSrcMap->getChangePkType(),mainSrcMap->getMapType());
		
		send_msg(myHero->getFd(),chageSre); 
		
		myHero->setWalkingFlg(false);		
		
		myHero->enter_scene();
	}
}


/*���հ��ɰ���*/
void PartyBaseCampLimit::recoverCampRom(int _room)
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
	if(!((initCampRom[_room])->getIsCampRomBusy()))
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
	
	initCampRom[_room]->initMap();
	asistList.push_front(_room);
}

/*���ÿ������ֵ*/
void PartyBaseCampLimit::setOpenFlg(bool _openFlg)
{
	isOpen = _openFlg;
}


/*��ÿ������ֵ*/
bool PartyBaseCampLimit::getOpenFlg(void)
{
	return isOpen;
}

	