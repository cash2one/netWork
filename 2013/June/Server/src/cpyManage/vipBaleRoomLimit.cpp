/************************************************************
	�ļ�����vipBaleRoomLimit.cpp
	�ļ����ã�ʵ����VipBaleRoomLimit��ķ���
	���ߣ�chenzhen
	�������ڣ�2012.12.14
************************************************************/
#include"map_src.h"
#include"vipBaleRoomLimit.h"
#include"hero.h"
extern map<string,Map_Inform*>mapId_connect_map;
extern map<string,Map_Src*> confVipRoom;
extern map<string, Hero*> heroId_to_pHero;
/*vip���ṹ�캯��*/
VipBaleRoomLimit::VipBaleRoomLimit(char *_vipLimitId,char *_vipMapId,int _num,int _vipRank,int _room)
{
	memset(vipMapId,'\0',sizeof(vipMapId));
	memset(vipLimitId,'\0',sizeof(vipLimitId));
	
	strncpy(vipMapId,_vipMapId,strlen(_vipMapId));	
	strncpy(vipLimitId,_vipLimitId,strlen(_vipLimitId));
	
	num = _num;
	vipRank = _vipRank;
	room = _room;	
	
	initVipMap();
}

/*��ʼ��vip����*/
void VipBaleRoomLimit::initVipMap(void)
{
	map<string,Map_Src*>::iterator vipConf_it;
	Map_Src *modleMap,*newVipMap;
	int i;	

	if(room <= 0)
	{
		return;
	}
	
	vipConf_it = confVipRoom.find(vipMapId);	
	if(vipConf_it == confVipRoom.end())
	{
		cout<<"the vipMapId is error:"<<vipMapId<<endl;
		return;
	}	
	modleMap = vipConf_it->second;
	
	for(i = 0;i < room;i++)
	{
		newVipMap = modleMap->copyMap(i);
		if(newVipMap == NULL)
		{
			cout<<"the newVipMap is NULL error the copyMap is error:"<<vipMapId<<endl;
			return;
		}
		initVipRom.push_back(newVipMap);
		asistList.push_back(i);
	}
}

/*���ð���ÿ������İ���ʵ��ָ��*/
void VipBaleRoomLimit::setMapVipRoom(void)
{
	int i;	
	for(i = 0;i < room;i++)
	{
		initVipRom[i]->setIsVipRom(true);
		initVipRom[i]->setVipRoom(this);
	}
}

/*����vip����*/
VipBaleRoomLimit::~VipBaleRoomLimit(void)
{
	
	Map_Src *vipMap;
	int i,length;	
	length = initVipRom.size();
	for(i = 0; i< length;i++)
	{
		vipMap = initVipRom[i];
		delete vipMap;
		vipMap = NULL;		
		initVipRom[i] = vipMap;
	}
		
	initVipRom.clear();
	{
		std::vector<Map_Src*> tmp;
		initVipRom.swap(tmp);
	}
	asistList.clear();
}

/*����vip����*/
void VipBaleRoomLimit::recoverVipRom(int _room)
{
	/*�����Խ��*/
	if(_room < 0 || _room >= room)
	{
		cout<<"the roomNum is error:"<<_room<<endl;
		return;
	}
	/*����Ϊ����״̬*/
	if(!((initVipRom[_room])->getIsVipRomBusy()))
	{
		return;
	}
	
	initVipRom[_room]->initMap();
	asistList.push_front(_room);
}

/*���˽�vip������*/
bool VipBaleRoomLimit::qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason)
{	
	map<string,Hero*>::iterator hero_it;
	char *perNikName,*wagonId,*mapId,*npcMapId;
	int length,i,sizeFail,vipType;	
	Map_Inform *lastMap;	
	Hero *myHero;
	Point piexPt;
	
	
	length = heroId.size();
	
	/*û�пշ���*/
	if(asistList.empty())
	{
		cout<<"three is not resorce to this vipRooms:"<<vipMapId<<endl;		
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
		vipType = myHero->memHero->vipDailyData.stage;
		if(lastMap == NULL ||  mapId == NULL || strlen(mapId) == 0)
		{
			return false;
		}		
		
		/*����vip�ʸ񲻹�*/
		if(vipType < vipRank)
		{
			cout<<"vipType:"<<vipType<<endl;
			cout<<"vipRank:"<<vipRank<<endl;
			
			failure_reason->member[sizeFail].failure_flag = ERROR_VIP_LEVEL;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}			
		
		/*���˲������ֳ���*/
		if(strcmp(mapId,"map_023") != 0 && strcmp(mapId,"map_024") != 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_HAPPY_CITY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}			
		
		/*���˴��ڰ�̯״̬*/
		if(myHero->getHeroState()==5)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_SELL_STATION;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}	
		
		/*���˴���Ѻ��״̬*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_YA_BIAO_STATION;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}		
	}
	return true;
}


/*����vip���᷿��*/
void VipBaleRoomLimit::assignRom(vector<string> &heroId)
{
	int roomNum = asistList.front();
	asistList.pop_front();
	
	/*���䷿��ʧ��*/
	if(!entVipRoom(heroId,roomNum))	
	{
		asistList.push_front(roomNum);
		return;
	}		
	initVipRom[roomNum]->setIsVipRomBusy(true);
}

/*��vip���ắ��*/
bool  VipBaleRoomLimit::entVipRoom(vector<string> &heroId,int _roomNum)  
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
	
	mapNow = initVipRom[_roomNum];
	
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


/*�˳�vip����*/
void VipBaleRoomLimit::exitVipRoomAsist(vector<string> &heroId)
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
	


	