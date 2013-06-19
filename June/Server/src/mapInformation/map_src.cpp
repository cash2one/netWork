/************************************************************
	�ļ�����map_inform.cpp
	�ļ����ã���Map_Inform������Ժͷ�����ʵ��
	���ߣ�chenzhen
	�������ڣ�2012.03.11
************************************************************/
#include"map_src.h"
#include"monsterBase.h"
#include <sstream>
#include"user_role_manage_assist.h"
#include"command_other_function_all_over.h"
#include"data_structure_struct.h"
#include"timerContainer.h"
#include"vipBaleRoomLimit.h"
#include"partyRoomLimit.h"
#include"partyBaseCampLimit.h"
extern TimerContainer<Map_Inform*> *mapThkContain;
Map_Src::Map_Src(char *_mapId,char *_mapFilePath,char *_mapName,\
int _mapWidth,int _mapHeight,int _row,int _col,int _baseDigst,\
Point _entPt,Point _outPt,Point _tribesPt,Point _religionPt,\
Point _rangerPt,map<string,MonsterBase *>& _monId_connect_monster,\
map<string,const jumpId_infor*>&_jumpId_connect_jumpInfo,\
map<string,TakeGoods*> &_takeGoodsMap,map<string,Bottle*> &_botInMap,\
map<string,Trap*> &_trapInstMap,set<Point> _dishPtSet,Point _centerPt,size_t _radius,bool _flgCpy,\
int _warType,int _changePkType,int _mapType,int _campEntFlag,\
int _levelLowerLimit,int _levelUpperLimit):Map_Inform(_mapId,\
_mapFilePath,_mapName,_mapWidth,_mapHeight,_row,_col,_baseDigst,\
_entPt,_outPt,_tribesPt,_religionPt,_rangerPt,\
_monId_connect_monster,_jumpId_connect_jumpInfo,\
_takeGoodsMap,_botInMap,_trapInstMap,_dishPtSet,_centerPt,_radius,_flgCpy,_warType,\
_changePkType,_mapType,_campEntFlag,_levelLowerLimit,_levelUpperLimit)
{
	isVipRom = false;
	isVipRomBusy = false;
	vipRoom = NULL;
	vipRoomNum = -1;
	
	partyRoom = NULL;
	partyRoomNum = -1;
	isPartyRom = false;
	isPartyRomBusy = false;
	
	campRoom = NULL;
	campRoomNum = -1;
	isCampRom = false;
	isCampRomBusy = false;
	
}

/*��ͼ˼���ص�����*/
void Map_Src::mapThkCalBak(void)
{
	if(heroFd.size() == 0 && flgThk == -1)
	{
		return;
	}
	
	if(heroFd.size() > 0 && flgThk == -1)
	{
		entMap();
	}
	
	stopThk();	
	
	/*�����ͼ�Ѿ���ͣ˼��*/
	if(flgThk == 1)
	{
		return;
	}	
	
	bruMonFun();	
}

/*ˢ�ֽӿ�*/
void Map_Src::bruMonFun(void)
{		
	/*һ��ˢһ��,ֱ��ˢ��Ϊֹ*/
	brushRedMon();
	
	// if(!ctlTme(8))
	// {
		// return;
	// }		
}

/*��һ�ν��볡��ˢ��*/
void Map_Src::entMap(void)
{	

#if 0

	/*������Ӫ��Դ�̳����*/
	brushTakeSource(10,true);

#endif

#if 0

	/*���Ե����*/
	initMonStatuary();
	
#endif	

	loopBruMon(true);
	
	/*ˢ��ƿ����Ϣ*/
	brushBotMsg();
	
	/*ˢ��������Ϣ*/
	brushTrapMsg();	
	
	/*ˢ����ժȡ��Ʒ*/
	bruTakeMsg();
	
}

/*��������*/
Map_Src::~Map_Src(void)      
{
	vipRoom = NULL;
	partyRoom = NULL;
	campRoom = NULL;

}

/*����ˢ��Ƶ��*/
bool Map_Src::ctlTme(int lveTme)
{
	ctnReBruDieMon++;
	
	if(ctnReBruDieMon % lveTme == 0)
	{
		ctnReBruDieMon = 0;
		return true;
	}
	return false;
}


/*ѭ��ˢ�ֺ���*/
void Map_Src::loopBruMon(bool isFirst)
{

	map<string,MonsterBase *>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		
		if(strcmp(mon_it->second->getType(),"AttRedMon") == 0)
		{
			continue;
		}
#if 1		
		/*�����*/
		if(mon_it->second->getOwnerAttriType() == 3 || mon_it->second->getOwnerAttriType() == 4)
		{
			continue;
		}
#endif

#if 1
		/*�ٻ���*/
		if(mon_it->second->getIsCallType())
		{
			continue;
		}
#endif
		
		if(mon_it->second->getLifeStation())
		{
			mon_it->second->brushMon();
			
			if(mon_it->second->getOwnerAttriType() == 3)
			{
				cout<<"Map_Src::loopBruMon(bool isFirst) begin:"<<mon_it->second->getIdentity()<<endl;
				cout<<"mon_it->second->getBshMsg:"<<mon_it->second->getBshMsg()<<endl;
				cout<<"Map_Src::loopBruMon(bool isFirst) end:"<<mon_it->second->getIdentity()<<endl;
			}
		}
	}
}
	

/*��ͣ�˵�ͼ����ˢ���ֵ�˼��*/
void Map_Src::stopAllLveMonThk(void)
{
	map<string,MonsterBase *>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		mon_it->second->stopThk();
	}
}

/*��ͣ�˵�ͼ����ˢ���ֵ�˼��*/
void Map_Src::reSetAllLveMonThk(void)
{
	map<string,MonsterBase *>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		mon_it->second->resetTimer();
	}
}



/*���Ƶ�ͼ��Ϣ����������Ϊ�����ָ����еĹֵ�id*/
Map_Src* Map_Src::copyMap(int roomNum)
{
	map<string,MonsterBase*> newMonInt;
	 
	map<string,const jumpId_infor*> newjumpId_connect_jumpInfo;
	
	map<string,Bottle*> _botInMap;
	
	map<string,TakeGoods*> _takeGoodsMap;
	
	map<string,Trap*> _trapInstMap;
	
	char newMapId[100] = {0};
	
	Map_Src *newMap;
	
	strncpy(newMapId,mapId,strlen(mapId));
	
	strncat(newMapId,"_",strlen("_"));
	
	appendNum(newMapId,roomNum,4);	//�����µ�ͼid
	
	copyMapMon(newMonInt,newMapId,newjumpId_connect_jumpInfo);
	
	
	/*����ƿ�޺���*/
	copyBotInMap( _botInMap,newMapId);
	
	/*���ƿ�ժȡ��Ʒ*/
	copyTakeGoods(_takeGoodsMap,newMapId);
	
	/*��������*/
	copyTrapVec(_trapInstMap,newMapId);
	
	/*���ù��캯��������һ����ͼʵ��*/
	newMap = new Map_Src(newMapId,mapFilePath,mapName,\
	mapWidth,mapHeight,row,col,baseDigst,entPt,outPt,tribesPt,\
	religionPt,rangerPt,newMonInt,newjumpId_connect_jumpInfo,\
	_takeGoodsMap,_botInMap,_trapInstMap,dishPtSet,centerPt,radius,flgCpy,warType,\
	changePkType,mapType,campEntFlag,levelLowerLimit,levelUpperLimit);
							
	/*�����ϰ���Ϣ*/
	newMap->setMapHinder(map_hinder);
	
	/*��ʼ���Ź���*/
	newMap->InitBox();
	
	/*���ô˵�ͼ�Ϲ���ĵ�ͼʵ��ָ��*/
	newMap->setMonMap();
	
	/*����ƿ�޵�ͼʵ��ָ��*/
	newMap->setBotMap();
	
	/*����ƿ�޵�ͼʵ��ָ��*/
	newMap->setTrapMap();
	
	/*���ÿ�ժȡ��ͼʵ��ָ��*/
	newMap->setTakeGoodsMap();
	
	return newMap;
}

/*�������ŵ�ͼ��Ϣ*/
void Map_Src::initMap(void)
{		
	/*��ͣ��ʱ��*/
	ev_timer_stop(loops,&timer);
	
	/*���ü�ʱ�����ֵ*/
	flgThk = -1;	
	
	/*����������Ϣ*/
	initTrap();
	
	/*����ƿ����Ϣ*/
	initBot();
	
	/*��ͣ��ͼ�����ж����Ķ�ʱ��*/
	stopThk();		
	
	/*���ù������ˢ��ʱ������*/
	initMonLvMager();	
	
	/*�����ͼ����Ĳɼ���*/
	initTakeGoods();	
	
	/*��վŹ����е�����*/
	clearBox();
	
	/*���᷿����Ϊ����*/
	isVipRomBusy = false;
	
	/*���ɷ�����Ϊ����*/
	isPartyRomBusy = false;
	
	/*���ɴ�Ӫ������Ϊ����*/
	isCampRomBusy = false;
	
	/*ɾ����ͼ�����л�û�м�ĵ�����Ʒ*/
	clearDropMap();	
	
	/*�����ϯ*/
	clearDish();
}

/*���ù�������*/
void Map_Src::initMon(void)
{	
	map<string,MonsterBase*>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		mon_it->second->die();
	}
}

/*��ͼ��ͣ˼������*/
void Map_Src::stopThk(void)
{
	set<string>::iterator lve_it;
	MonsterBase *mon;
	
	/*�����ͼû��*/
	if(heroFd.size() == 0)
	{
		/*����˵�ͼ�Ĺ����Ѿ���ͣ˼��*/
		if(flgThk == 1)
		{
			return;
		}		
		/*��ͣ�˵�ͼ����ˢ���ֵ�˼��*/		
		stopAllLveMonThk();
		
		/*��ͣ�����ʱ��*/
		stopTrapThk();
		
		/*���õ�ͼ˼�����ֵΪ�����Ѿ���ͣ˼��*/
		flgThk = 1; 
		return;
	}
	else
	{
		/*��������Ѿ�����ͣ˼��*/
		if(flgThk == 1)
		{
			/*��������˼��*/
			reSetAllLveMonThk();
			
			/*���������ʱ��*/
			reSetTrapThk();
		}
		/*���õ�ͼ˼�����ֵΪ�������Ѿ�˼��*/
		flgThk = 0;
	}
}

/*���ɹ�����Ŀ��Ϣ*/
char* Map_Src::getSumMonMsg(void)	
{
	return NULL;
}

/*����Ƿ�Ϊvip�����־*/
bool Map_Src::getIsVipRom(void)
{
	return isVipRom;
}

/*����Ƿ�Ϊ����*/
void Map_Src::setIsVipRom(bool _busy)
{
	isVipRom = _busy;
	
	ctnTheVipRoomNum();
}

/*���vip�����Ƿ�ռ�ñ�־*/
bool Map_Src::getIsVipRomBusy(void)
{
	return isVipRomBusy;
}

/*���vip�����Ƿ�ռ�ñ�־*/
void Map_Src::setIsVipRomBusy(bool _busy)
{
	isVipRomBusy = _busy;
}


/*����vip����������ʵ��ָ��*/
void Map_Src::setVipRoom(VipBaleRoomLimit *_vipRoom)
{
	if(_vipRoom == NULL)
	{
		cout<<"set the vipRoom is error NULL:"<<mapId<<endl;
		return;
	}
	if(!isVipRom)
	{
		cout<<"the map is not vipMapId:"<<mapId<<endl;
		vipRoom = NULL;
		return;
	}		
	vipRoom = _vipRoom;
}

/*���᳡����ͼ˼������*/
bool Map_Src::vipCallBack(void)
{
	if(heroFd.empty())
	{
		if(vipRoom == NULL)
		{
			return true;
		}
		vipRoom->recoverVipRom(vipRoomNum);
		return true;
	}
	return false;
}


/*���᳡����ͼ˼������*/
bool Map_Src::partyCallBack(void)
{
	if(heroFd.empty())
	{
		if(partyRoom == NULL)
		{
			return true;
		}
		partyRoom->recoverPartyRom(partyRoomNum);
		return true;
	}
	return false;
}

/*����vip����*/
void Map_Src::enterVipRoomFirst(void)
{
	ext_ev_timer_init(&timer,MapThkCalBak,MAP_THINK_TIME,0,this,mapId);
	ev_timer_start(loops,&timer);
}

/*������ɰ���*/
void Map_Src::enterPartyRoomFirst(void)
{
	ext_ev_timer_init(&timer,MapThkCalBak,MAP_THINK_TIME,0,this,mapId);
	ev_timer_start(loops,&timer);
}

/*����õ�vip�����*/
void Map_Src::ctnTheVipRoomNum(void)
{
	char numStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	strncpy(numStr,mapId + strlen(mapId) - 4,4);
	vipRoomNum = atoi(numStr);
}

/*�˳�vip����*/
void Map_Src::exitVipRoom(vector<string> &heroVec)
{
	if(heroVec.empty() || vipRoom == NULL)
	{
		cout<<"the heroVec is empty or the vipRoom is NULL:"<<mapId<<endl;
		return;
	}
	vipRoom->exitVipRoomAsist(heroVec);
}


/*����Ƿ�Ϊ���ɰ����־*/
bool Map_Src::getIsPartyRom(void)
{
	return isPartyRom;
}

/*�����Ƿ�Ϊ���ɵ�ͼ*/
void Map_Src::setIsPartyRom(bool _busy)
{
	isPartyRom = _busy;
	
	ctnThePartyRoomNum();
}

/*���vip�����Ƿ�ռ�ñ�־*/
bool Map_Src::getIsPartyRomBusy(void)
{
	return isPartyRomBusy;
}

/*���vip�����Ƿ�ռ�ñ�־*/
void Map_Src::setIsPartyRomBusy(bool _busy)
{
	isPartyRomBusy = _busy;
}


/*����õ����ɰ����*/
void Map_Src::ctnThePartyRoomNum(void)
{
	char numStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	strncpy(numStr,mapId + strlen(mapId) - 4,4);
	partyRoomNum = atoi(numStr);
}

/*���ð��ɰ���������ʵ��ָ��*/
void Map_Src::setPartyRoom(PartyRoomLimit *_partyRoom)
{
	if(_partyRoom == NULL)
	{
		cout<<"set the partyRoom is error NULL:"<<mapId<<endl;
		return;
	}
	if(!isPartyRom)
	{
		cout<<"the map is not partyMapId:"<<mapId<<endl;
		partyRoom = NULL;
		return;
	}		
	partyRoom = _partyRoom;
}

PartyRoomLimit* Map_Src::getPartyRoomLimit(void)
{
	return partyRoom; 
}

/*���ð��ɴ�Ӫ����������ʵ��ָ��*/
void Map_Src::setCampRoom(PartyBaseCampLimit *_campRoom)
{
	if(_campRoom == NULL)
	{
		cout<<"set the partyRoom is error NULL:"<<mapId<<endl;
		return;
	}
	if(!isCampRom)
	{
		cout<<"the map is not campMapId:"<<mapId<<endl;
		campRoom = NULL;
		return;
	}		
	campRoom = _campRoom;
}

/*��ð��ɰ����Ƿ�ռ�ñ�־*/
bool Map_Src::getIsCampRomBusy(void)
{
	return isCampRomBusy;
}

/*��ð��ɰ����Ƿ�ռ�ñ�־*/
void Map_Src::setIsCampRomBusy(bool _busy)
{
	isCampRomBusy = _busy;
}

/*����õ����ɴ�Ӫ�����*/
void Map_Src::ctnTheCampRoomNum(void)
{
	char numStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	strncpy(numStr,mapId + strlen(mapId) - 4,4);
	campRoomNum = atoi(numStr);
}

/*�˳����ɴ�Ӫ����*/
void Map_Src::exitCampRoom(vector<string> &heroVec)
{
	if(heroVec.empty() || campRoom == NULL)
	{
		cout<<"the heroVec is empty or the campRoom is NULL:"<<mapId<<endl;
		return;
	}
	campRoom->exitCampRoomAsist(heroVec);
}


/*����Ƿ�Ϊ���ɴ�Ӫ�����־*/
bool Map_Src::getIsCampRom(void)
{
	return isCampRom;
}

/*�����Ƿ�Ϊ���ɴ�Ӫ��ͼ*/
void Map_Src::setIsCampRom(bool _busy)
{
	isCampRom = _busy;
	
	ctnTheCampRoomNum();
}


/*���ɴ�Ӫ���᳡����ͼ˼������*/
bool Map_Src::campCallBack(void)
{
	if(heroFd.empty())
	{
		if(campRoom == NULL)
		{
			return true;
		}
		campRoom->recoverCampRom(partyRoomNum);
		return true;
	}
	return false;
}

/*������ɴ�Ӫ����*/
void Map_Src::enterCampRoomFirst(void)
{
	ext_ev_timer_init(&timer,MapThkCalBak,MAP_THINK_TIME,0,this,mapId);
	ev_timer_start(loops,&timer);
}


/*ϵͳ��͸�������*/
bool Map_Src::systemTreat(TakeGoods *newDish)
{
	
	cout<<"Map_Src::systemTreat begin:"<<endl;
	
	if(newDish == NULL)
	{
		return false;
	}
	
	if(partyRoom == NULL)
	{
		return false;
	}
	
	/*add chenzhen 20130325 ���÷���ͼƬ*/
	newDish->setIsDished(true);
	
#if 0	
	if(partyRoom->getActiveFlg())
	{
		cout<<"the time of treat is on:"<<endl;
		
		newDish->setDishState(2);
	}

	else
	{
		cout<<"the time of treat is not on:"<<endl;
		
		newDish->setDishState(1);
	}	
#endif		
	newDish->brushMsg();
	
	cout<<"Map_Src::systemTreat end:"<<endl;
	
	return true;
}
