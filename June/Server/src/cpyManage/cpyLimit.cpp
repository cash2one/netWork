/*
	�ļ�����cpyLimit.cpp
	�ļ����ã�ʵ����CpyLimit��ķ���
	���ߣ�chenzhen
	�������ڣ�2012.06.11
*/
#include"heroCpyRecord.h"
#include"cpyLimit.h"
#include"cpyAsist.h"
#include"cpyManager.h"
#include"hero.h"
#include"towerLayerRecord.h"
#include"team.h"
#include"teamManager.h"
#include"my_mem_group.h"

/*������ͨ����npc���͵�*/
extern Point JLGENPT;

/*������ͨ����npc���͵�*/
extern Point KFGENPT;

/*������ɸ���npc���͵�*/
extern Point KFPARPT;

/*������ɸ���npc���͵�*/
extern Point JLPARPT;

/*��ɫ����ɸ���npc���͵���پ�����ܴ���*/
extern int LIMPRTRAG;

/*��ɫ����ͨ����npc���͵���پ�����ܴ���*/
extern int LIMGENRAG;



extern map<string, Hero*> heroId_to_pHero;
extern CpyManger *cpyManger;
extern Hero* pg_hero;
extern map<string,map<string,string> >towerMapConf;
extern MyMemGroup* mem_group;

CpyLimit::CpyLimit(char *_cpyLimitId,char *_cpyId,char *_name,int _baseGole,int _judgeTme,\
					double _jugGodRat,int _num,int _rank,size_t _costFatigue,int _room)
{
	memset(cpyLimitId,'\0',sizeof(cpyLimitId));
	memset(cpyId,'\0',sizeof(cpyId));
	memset(name,'\0',sizeof(name));
	
	strncpy(cpyLimitId,_cpyLimitId,strlen(_cpyLimitId));	
	strncpy(cpyId,_cpyId,strlen(_cpyId));
	strncpy(name,_name,strlen(_name));
	
	num = _num;
	rank = _rank;
	room = _room;	
	judgeTme = _judgeTme;
	jugGodRat = _jugGodRat;
	baseGole = _baseGole;
	totalSize = room;
	costFatigue = _costFatigue;
	memRecord = NULL;
//	initMemRecord();
}

char *CpyLimit::getCpyId(void)
{
	return cpyId;
}

int CpyLimit::getRoom(void)
{
	return room;
}

void CpyLimit::PushCpy(Cpy *newCpy)
{
	initCpyRom.push_back(newCpy);
	int size = initCpyRom.size() -1;
	asistList.push_back(size);
}

/*���˽��������*/
bool CpyLimit::qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason,bool tolFlg,bool isParty)
{
	
	map<string,Hero*>::iterator hero_it;
	char *perNikName,*wagonId,*mapId,*npcMapId;
	int length,i,sizeFail;	
	HeroCpyRecord *record;
	Map_Inform *lastMap;	
	Guild *myGuild;	
	Hero *myHero;
	Point piexPt;
	
	
	length = heroId.size();
	
	/*û�пշ���*/
	if(asistList.empty())
	{
		if(!borrowCpyFun())
		{
			char failReason[100] = "6,13,";
			char idTset[10]={'\0'};
			strncpy(idTset,cpyId,strlen(cpyId) -2);			
			if(pg_hero == NULL)
			{
				return false;
			}
			sprintf(failReason + strlen(failReason),"%s",idTset);
			send_msg(pg_hero->getFd(), failReason);
			cout<<"three is not resorce to this cpy:"<<idTset<<endl;		
			return false;
		}		
	}
	
	/*��������*/
	if(length < num) 
	{
		
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
		record = myHero->getCpyRecord();
		perNikName = myHero->getNickName();
		lastMap = myHero->getMap();
		wagonId = myHero->memHero->wagonId;	
		piexPt = myHero->getLocation();
		mapId = lastMap->getMapId();
		
		if(i == 0)
		{
			npcMapId = lastMap->getMapId();
		}
		
		if(lastMap == NULL || record == NULL || mapId == NULL || strlen(mapId) == 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_OTHER;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
			failure_reason->size += 1;
			return false;
		}
		
		/*���Ѿ��ڶ������Ҳ��Ƕӳ�*/
		if(length == 1 && !SingleOrTeamLeader(myHero->getIdentity()))
		{			
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_TEAM;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
			failure_reason->size += 1;			
			return false;
		}
		/*���˴��ڰ�̯״̬*/
		if(myHero->getHeroState()==5)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_SELL;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}	
#if 0
		/*����ͬһ�ŵ�ͼ*/
		if(strcmp(mapId,npcMapId) != 0 )
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_MAIN_CITY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}	
		/*���˲�������*/
		if(strcmp(mapId,"map_001") != 0 && strcmp(mapId,"map_010") != 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_MAIN_CITY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}	
#endif
		
		if(isParty)
		{
#if 0
			if(strcmp(mapId,"map_001") == 0)
			{
				if(sqrt(pow(fabs(piexPt._x - KFPARPT._x),2)+pow(fabs(piexPt._y - KFPARPT._y),2)) > LIMPRTRAG)
				{
					failure_reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
					strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
					failure_reason->size += 1;
					return false;
				}
			}
			if(strcmp(mapId,"map_010") == 0)
			{
				if(sqrt(pow(fabs(piexPt._x - JLPARPT._x),2)+pow(fabs(piexPt._y - JLPARPT._y),2)) > LIMPRTRAG)
				{
					failure_reason->member[sizeFail].failure_flag = ERROR_IN_JL_NPC;
					strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
					failure_reason->size += 1;
					return false;
				}
			}
#endif			
			myGuild = myHero->getGuild();
			if(myGuild == NULL)
			{
				/*û�м������*/
				failure_reason->member[sizeFail].failure_flag = ERROR_NOT_JOIN_PARTY;
				strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));		
				failure_reason->size += 1;
				return false;
				
			}
			else
			{
				/*���ɵȼ�����*/
				if(myGuild->getLevel() < rank)
				{
					/*���ɵȼ�����*/
					failure_reason->member[sizeFail].failure_flag = IS_PARTY_LEVE_LOW;
					strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
					failure_reason->size += 1;
					return false;			
				}
			}
		}
		else
		{			
	
#if 0
			if(myHero->getLevel() < 40)
			{
				
				if(strcmp(mapId,"map_010") == 0 || !judRange(piexPt,KFGENPT,LIMGENRAG))
				{					
					failure_reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
					strncpy(failure_reason->member[sizeFail].nickName, perNikName,\
					strlen(perNikName));
					failure_reason->size += 1;
					return false;
				
				}	
			}
			else
			{
			
				if(strcmp(mapId,"map_001") == 0)
				{
					if(!judRange(piexPt,KFGENPT,LIMGENRAG))
					{
						failure_reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
						strncpy(failure_reason->member[sizeFail].nickName, perNikName,\
						strlen(perNikName));
						failure_reason->size += 1;
						return false;
					}
				}
				else
				{						
					if(!judRange(piexPt,JLGENPT,LIMGENRAG))
					{
						failure_reason->member[sizeFail].failure_flag = ERROR_IN_JL_NPC;
						strncpy(failure_reason->member[sizeFail].nickName, perNikName,\
						strlen(perNikName));
						failure_reason->size += 1;
						return false;
					}
				}
			}
#endif

#if 1				
			/*�жϸ��������ȼ�������ȼ������*/
			if(myHero->getLevel() < rank)
			{
				failure_reason->member[sizeFail].failure_flag = ERROR_LOWER_RANK;
				strncpy(failure_reason->member[sizeFail].nickName, perNikName,\
				strlen(perNikName));	
				failure_reason->size += 1;	
				return false;
			}
#endif				
			/*����û�п���*/
			if(!record->judUperRank(cpyId))
			{
				failure_reason->member[sizeFail].failure_flag = ERROR_NO_OPEN;
				strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
				failure_reason->size += 1;	
				return false;			
			}			
		}		
			
		cout<<"myHero->memHero->lastStrength:"<<myHero->memHero->lastStrength<<endl;
#if 1
		/*�ж�����ֵ����*/
		if(myHero->memHero->lastStrength < costFatigue)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_LOWER_LAST_POWER;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;	
		}			
#endif		
				
		/*���˴���Ѻ��״̬*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_YA_BIAO;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"enter list threeEvent:"<<endl;
			return false;
		}
		/*���˴��ڸ���״̬*/
		if(lastMap->getFlgCpy())
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_COPY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}
		
		/*���˴���pk״̬*/
		if(lastMap->getWarType() !=1)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_PK;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"enter list fiveLevent:"<<endl;
			return false;
		}
		
		/*���˴������ֵ�ͼ״̬*/
		if(isHappyMap(lastMap->getMapId()))
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_HAPPY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"enter list fiveLevent:"<<endl;
			return false;
		}			
	}
	
	return true;
}

string CpyLimit::enable_enter_cpy(vector<string> &heroId, Failure_Reason* reason ,bool isParty)
{
	map<string,Hero*>::iterator hero_it;	
	char *nickNme,*mapId,*wagonId,*npcMapId;	
	int length,i,sizeFail;	
	HeroCpyRecord *record;
	Map_Inform *lastMap;
	string inst_room_id;
	Guild *myGuild;
	Hero *myHero;	
	Point piexPt;
	
	length = heroId.size();
	
	/*û�пշ���*/
	if(asistList.empty())
	{
		if(!borrowCpyFun())
		{			
			cout<<"three is not resorce to this cpy:"<<cpyId<<endl;		
			return inst_room_id;
		}
	}
		
	for(i = 0;i < length;i++)
	{
		sizeFail = reason->size;
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			continue;
		}
		
		record = myHero->getCpyRecord();
		nickNme = myHero->getNickName();
		wagonId = myHero->memHero->wagonId;	
		lastMap = myHero->getMap();
		mapId = lastMap->getMapId();
		piexPt = myHero->getLocation();
		
		/*���봦��һ�ŵ�ͼ��*/
		if(i == 0)
		{
			npcMapId = lastMap->getMapId();
		}
		
		if(lastMap == NULL || record == NULL || mapId == NULL || strlen(mapId) == 0)
		{
			return inst_room_id;
		}
		
		/*���˴��ڰ�̯״̬*/
		if(myHero->getHeroState()==5)
		{
			reason->member[sizeFail].failure_flag = ERROR_IN_SELL;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}	

#if 0		
		/*����ͬһ�ŵ�ͼ*/
		if(strcmp(mapId,npcMapId) != 0 )
		{
			reason->member[sizeFail].failure_flag = ERROR_IN_MAIN_CITY;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}	
	
		/*���˲�������*/
		if(strcmp(mapId,"map_001") != 0 && strcmp(mapId,"map_010") != 0)
		{
			reason->member[sizeFail].failure_flag = ERROR_IN_MAIN_CITY;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}	
#endif			
		if(isParty)
		{
		
#if 0
			if(strcmp(mapId,"map_001") == 0)
			{
				if(!judRange(piexPt,KFPARPT,LIMPRTRAG))
				{
					reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
					strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
					reason->size += 1;
					return inst_room_id;
				}
			
			}
			else
			{
				if(!judRange(piexPt,JLPARPT,LIMPRTRAG))
				{
					reason->member[sizeFail].failure_flag = ERROR_IN_JL_NPC;
					strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
					reason->size += 1;
					return inst_room_id;
				}
			
			}
#endif
			myGuild = myHero->getGuild();
			if(myGuild == NULL)
			{
				/*û�м������*/
				reason->member[sizeFail].failure_flag = ERROR_NOT_JOIN_PARTY;
				strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));		
				reason->size += 1;
				return inst_room_id;
			}
			else
			{
				/*���ɵȼ�����*/
				if(myGuild->getLevel() < rank)
				{					
					reason->member[sizeFail].failure_flag = IS_PARTY_LEVE_LOW;			
					strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
					reason->size += 1;		//ʧ��������1
					return inst_room_id;	//���ؿշ����
			
				}
			}
		}		
		else
		{
#if 0
			if(myHero->getGradeNow() < 40)
			{
				
				if(strcmp(mapId,"map_010") == 0 || !judRange(piexPt,KFGENPT,LIMGENRAG))
				{					
					reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
					strncpy(reason->member[sizeFail].nickName, nickNme,\
					strlen(nickNme));
					reason->size += 1;
					return inst_room_id;
				
				}	
			}
			else
			{
				if(strcmp(mapId,"map_001") == 0)
				{
					if(!judRange(piexPt,KFGENPT,LIMGENRAG))
					{
						reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
						strncpy(reason->member[sizeFail].nickName, nickNme,\
						strlen(nickNme));
						reason->size += 1;
						return inst_room_id;
					}
				}
				else
				{						
					if(!judRange(piexPt,JLGENPT,LIMGENRAG))
					{
						reason->member[sizeFail].failure_flag = ERROR_IN_JL_NPC;
						strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
						reason->size += 1;
						return inst_room_id;
					}
				}
			}
#endif

#if 1			
			/*�жϸ��������ȼ�������ȼ������*/
			if(myHero->getLevel() < rank)
			{
				
				reason->member[sizeFail].failure_flag = ERROR_LOWER_RANK;
				strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));		
				reason->size += 1;		
				return inst_room_id;
			}
#endif			

#if 1
			/*�жϸ����Ƿ��ѿ���*/
			if(!record->judUperRank(cpyId))
			{
				
				reason->member[sizeFail].failure_flag = ERROR_NO_OPEN;
				strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));		
				reason->size += 1;		
				return inst_room_id;
			}			
#endif			
		}
#if 1		
		/*�ж�����ֵ����*/
		if(myHero->memHero->lastStrength < costFatigue)
		{
				
			reason->member[sizeFail].failure_flag = ERROR_LOWER_LAST_POWER;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));		
			reason->size += 1;		
			return inst_room_id;
		}			
#endif

		/*���˴���Ѻ��״̬*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			reason->member[sizeFail].failure_flag = ERROR_YA_BIAO;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}
			
		/*���˴��ڸ���״̬*/
		if(lastMap->getFlgCpy())
		{
			reason->member[sizeFail].failure_flag = ERROR_IN_COPY;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}		
		/*���˴���pk״̬*/
		if(lastMap->getWarType() !=1)
		{
			reason->member[sizeFail].failure_flag = ERROR_PK;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}				
		
		/*���˴������ֵ�ͼ״̬*/
		if(isHappyMap(lastMap->getMapId()))
		{
			reason->member[sizeFail].failure_flag = ERROR_IN_HAPPY;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}			
	}
	
	
	int roomNum = asistList.front();
	
	asistList.pop_front();
	
	/*�˸������ˣ�����ʱ����*/
	if(initCpyRom[roomNum]->getFlgBusy())
	{
		cout<<"the error roomNum:"<<roomNum<<endl;
		return inst_room_id;
	}
	
	initCpyRom[roomNum]->setFlgBusy(false);
	
	return initCpyRom[roomNum]->getCpyId();

}

/*���䷿�䣬�ҽ�����*/
void CpyLimit::assignRom(vector<string> &heroId,int roomNum)
{	
	if(roomNum >= initCpyRom.size() || roomNum < 0 || !initCpyRom[roomNum])
	{
		cout<<"CpyLimit::assignRom roomNum is error :"<<roomNum<<endl;
		return;
	}
	
	/*�˸������ˣ�����ʱ����*/
	if(initCpyRom[roomNum]->getFlgBusy())
	{
		cout<<"CpyLimit::assignRom roomNum is busy :"<<roomNum<<endl;
		return;
	}

	
	/*���䷿��ʧ��*/
	if(!initCpyRom[roomNum]->entCpy(heroId))	//���ν��븱��
	{
		cout<<"CpyLimit::assignRom assignRom failed :"<<roomNum<<endl;
		asistList.push_front(roomNum);
		return;
	}
		
	initCpyRom[roomNum]->setFlgBusy(true);
	
	/*add chenzhen 20130128 ������븱��*/
	initCpyRom[roomNum]->setIsTeam(true);
}

/*���䷿�䣬�ҽ�����,���˽�*/
void CpyLimit::assignRom(vector<string> &heroId)
{
	int roomNum = asistList.front();
	asistList.pop_front();
	
	
	
	/*�˸������ˣ�����ʱ����*/
	if(initCpyRom[roomNum]->getFlgBusy())
	{
		cout<<"CpyLimit::assignRom room is busy:"<<roomNum<<endl;
		return;
	}
	
	/*���䷿��ʧ��*/
	if(!initCpyRom[roomNum]->entCpy(heroId))	//���ν��븱��
	{
		cout<<"CpyLimit::assignRom room is failed:"<<roomNum<<endl;
		asistList.push_front(roomNum);
		return;
	}
		
	initCpyRom[roomNum]->setFlgBusy(true);
}

/*������������ͼ*/
void CpyLimit::enterRom(int _roomNum,vector<string> &heroId,char *_mapId,Point *pTargetPt)
{
	if(_mapId == 0) return;
	
	/*�жϸ��������Ƿ���Ч*/
	if(!roomExist(_roomNum))
	{
		cout<<"CpyLimit::enterRom the _roomNum is error:"<<_roomNum<<endl;
		return;
	}
	/*�жϷ����Ƿ�Ϊ��*/
	if(initCpyRom[_roomNum]->getFlgBusy())
	{
		
		/*�ҽ�����������ͼ*/
		initCpyRom[_roomNum]->entCpyMap(heroId,_mapId,pTargetPt);
	}
	
}

/*�������շ���*/
void CpyLimit::recoverRom(char *_cpyIdRom)
{
	char numStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char lastStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};		
	int roomNum;	

	if(!dealSerNumStr(_cpyIdRom,numStr,lastStr))
	{
		cout<<" CpyLimit::recoverRom the _cpyIdRom is error:"<<_cpyIdRom<<endl;
		return;
	}
	
	roomNum = atoi(numStr);
	
	/*�жϸ��������Ƿ���Ч*/
	if(!roomExist(roomNum))
	{
		cout<<" CpyLimit::recoverRom the roomNum is error:"<<roomNum<<endl;
		return;
	}
	/*������չ����*/
	if(roomNum >= room)
	{
		recoverBorrowCpy(roomNum);
		return;
	}
	if(initCpyRom[roomNum]->getFlgBusy())
	{
		/*���ֵ����*/
		initCpyRom[roomNum]->setFlgBusy(false);
		
		/*���ո�������*/
		asistList.push_front(roomNum);				
	}
}

/*�˳�����*/
void CpyLimit::exitCpy(int _roomNum,vector<string> &heroId)
{
	if(!roomExist(_roomNum))
	{
		cout<<"CpyLimit::exitCpy the _roomNum is error:"<<_roomNum<<endl;
		return;
	}
	if(initCpyRom[_roomNum]->getFlgBusy())
	{
		/*�˳�����������ͼ*/
		initCpyRom[_roomNum]->exitCpy(heroId);
	}
}

/*�жϸ��������Ƿ񳬳��ܷ�����*/
bool CpyLimit::roomExist(int _roomNum)
{
	return _roomNum < initCpyRom.size() && _roomNum >= 0;
	
#if 0
	return _roomNum < newNum && _roomNum >= 0;
#endif
	// return _roomNum < room && _roomNum >= 0;
}

/*��ø���������*/
Cpy* CpyLimit::getRoomCpy(int roomNum)
{
	if(roomExist(roomNum))
	{
		if(initCpyRom[roomNum]->getFlgBusy())
		{
			return initCpyRom[roomNum];
		}
	}
	return NULL;
}
	
/*���Ҫ��ȼ�*/
int CpyLimit::getRank(void)
{
	return rank;
}
	
/*��ø����Ѷ�*/
int CpyLimit::getDiffcult(void)
{
	char numStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char lastStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};		
	int level;	

	if(!dealSerNumStr(cpyId,numStr,lastStr))
	{
		cout<<"CpyLimit::getDiffcult the cpyId is error:"<<cpyId<<endl;
		return -1;
	}
	
	level = atoi(numStr);
}


/*������֮ǰ�������뷿���ȷ��*/
bool CpyLimit::qualifyExamLast(vector<string> &heroId,int &_roomNum)
{

	char *cpyApplyId,numStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char lastStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Hero*>::iterator hero_it;
	HeroCpyRecord *record;	
	int length,i;		
		
	
	if(heroId.empty())
	{
		return false;
	}
	
	hero_it = heroId_to_pHero.find(heroId[0]);
	
	if(hero_it == heroId_to_pHero.end())
	{
			return false;          
	}
	
	cpyApplyId = hero_it->second->getFbRom();
	
	if(cpyApplyId == NULL || strlen(cpyApplyId) == 0)
	{
		return false;
	}
	
	length = heroId.size();
	
	for(i = 1;i < length;i++)
	{
		hero_it = heroId_to_pHero.find(heroId[i]);
		
		if(hero_it == heroId_to_pHero.end())
		{
			return false;          
		}
		
		if(strcmp(cpyApplyId,hero_it->second->getFbRom()) != 0)
		{
			return false;
		}
	}		

	if(!dealSerNumStr(cpyApplyId,numStr,lastStr))
	{
		cout<<"CpyLimit::qualifyExamLast the cpyApplyId is error:"<<cpyApplyId<<endl;
		return false;
	}
	
	_roomNum = atoi(numStr);

	return true;
}

/*�������ʱ��*/
int CpyLimit::getJdgTme(void)
{
	return judgeTme;
}

/*�������ϵ��*/
double CpyLimit::getJdgRat(void)
{
	return jugGodRat;
}


/*��������*/
CpyLimit::~CpyLimit(void)
{
	storeMemRecord();
	
	vector<Cpy*>::iterator cpy_it;
	Cpy *val;
		
	for(cpy_it = initCpyRom.begin();cpy_it != initCpyRom.end();cpy_it++)
	{
		val = *cpy_it;		
		delete val;		
		val = NULL;
	}
	
	initCpyRom.clear();
	
	asistList.clear();
	
	clearWipeOut();
	
}

/*ͨ��room,�Լ�mapId�ҵ�mapʵ��*/
Map_Cpy* CpyLimit::getMapCpy(int roomNum,char *mapId)
{
	if(!roomExist(roomNum))
	{
		cout<<"CpyLimit::getMapCpy cpy roomNum is error:"<<roomNum<<endl;
		return NULL;
	}
	if(mapId == NULL || strlen(mapId) == 0)
	{
		cout<<"CpyLimit::getMapCpy cpy mapId is error:"<<mapId<<endl;
		return NULL;
	}
	
	return initCpyRom[roomNum]->getCpyMap(mapId);
}

/*��չ����*/
bool CpyLimit::borrowCpyFun(void)
{
	/*����ʵ��id��������id����׷����ˮ��*/
	char initCpyId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};        
	Cpy *borrowCpy,*modCpy;
	int flgIndex;
	
	if(initCpyRom.empty())
	{
		cout<<"CpyLimit::borrowCpyFun the initCpyRom is empty:"<<endl;
		return false;
	}
	modCpy = initCpyRom[0];
	borrowCpy = cpyManger->offerCpy(flgIndex);
	if(flgIndex == -1 || borrowCpy == NULL)
	{
		cout<<"CpyLimit::borrowCpyFun it is fail to borrow the cpy:"<<cpyId<<endl;
		return false;
	}

	size_t dynamicIndex;
	
	//û�пף���������׷��
	if(dynamicUseAbleIndex.empty())
	{
		dynamicIndex = totalSize;
		++totalSize;
	}
	
	//�пף������
	else
	{
		dynamicIndex = dynamicUseAbleIndex.front();
	}
	
	strncpy(initCpyId,cpyId,strlen(cpyId));
	strncat(initCpyId,"_",strlen("_"));
	appendNum(initCpyId,dynamicIndex,4);
	
	
	borrowCpy->initBorrowCpy(initCpyId,modCpy->getCpyMapSet(),this);
	
	//��������쳣����Ҫ��
	pair<map<int,int>::iterator,bool> insert_it = dyRomIndexToMagIndex.insert(pair<int,int>(dynamicIndex,flgIndex));
	if(!insert_it.second)
	{
		cout<<"CpyLimit::borrowCpyFun error  the dynamicIndex is exist before:"<<dynamicIndex<<endl;
		return false;
	}
	
	if(initCpyRom.size() <= dynamicIndex)
	{		
		initCpyRom.push_back(borrowCpy);
	}
	else
	{
		initCpyRom[dynamicIndex] = borrowCpy;
		dynamicUseAbleIndex.pop_front();
	}
	
	
	
	asistList.push_front(dynamicIndex);
	
	return true;
}

/*��չ��������*/
void CpyLimit::recoverBorrowCpy(int romIndex)
{
	map<int,int>::iterator index_it = dyRomIndexToMagIndex.find(romIndex);
	if(index_it == dyRomIndexToMagIndex.end())
	{
		cout<<"CpyLimit::recoverBorrowCpy the romIndex is not lend :"<<romIndex<<endl;
		return;
	}	
	
	Cpy *borrowCpy = initCpyRom[romIndex];
	borrowCpy->recoverBorrowCpy();	
	if(!cpyManger->recover(borrowCpy,index_it->second))
	{
		cout<<"CpyLimit::recoverBorrowCpy it is error to recover borrowCpy:"<<cpyId<<endl;
	}
	
	dynamicUseAbleIndex.push_front(romIndex);
	
	dyRomIndexToMagIndex.erase(index_it);
	
	//�ѿն��ÿ�ֵ����
	initCpyRom[romIndex] = NULL;
}

/*��û�����*/
int CpyLimit::getBaseGole(void)
{
	return baseGole;
}

/*��Ӻ��ж�Ա��ͬ��֮�󣬻����Ǹ�Ԥ���ķ����*/
void CpyLimit::recoverRom(int roomNum)
{
	
	/*�жϸ��������Ƿ���Ч*/
	if(!roomExist(roomNum))
	{
		cout<<"CpyLimit::recoverRom the roomNum is error:"<<roomNum<<endl;
		return;
	}
	/*������չ����*/
	if(roomNum >= room)
	{
		recoverBorrowCpy(roomNum);
		return;
	}
	/*���ֵ����*/
	initCpyRom[roomNum]->setFlgBusy(false);
	
	/*���ո�������*/
	asistList.push_front(roomNum);	
}

/*ֻ�ܵ��˽����񸱱����*/
bool CpyLimit::taskCpyQualifyExam(vector<string> &heroId,Failure_Reason* failure_reason)
{
	
	map<string,Hero*>::iterator hero_it;
	char *perNikName,*wagonId,*mapId,*npcMapId;
	int length,i,sizeFail;	
	HeroCpyRecord *record;
	Map_Inform *lastMap;	
	Guild *myGuild;	
	Hero *myHero;
	Point piexPt;
	string teamId;         //����id
	Team *team;
	map<string,Team*>::iterator team_it;
	
	length = heroId.size();
	
	/*û�пշ���*/
	if(asistList.empty())
	{
		if(!borrowCpyFun())
		{
			char failReason[100] = "6,13,";
			char idTset[10]={'\0'};
			strncpy(idTset,cpyId,strlen(cpyId) -2);			
			if(pg_hero == NULL)
			{
				return false;
			}
			sprintf(failReason + strlen(failReason),"%s",idTset);
			send_msg(pg_hero->getFd(), failReason);
			cout<<"three is not resorce to this cpy:"<<idTset<<endl;		
			return false;
		}		
	}
	
	/*��������*/
	if(length < num) 
	{
		cout<<"If you want enter it, you must have "<<num<<" members and you only have "<<length<<endl;
		return false;
	}
		
	for(i = 0;i < length;i++)
	{

		sizeFail = failure_reason->size;
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			cout<<"one of the heroid in hero vector is invalid"<<endl;
			return false;
		}
		record = myHero->getCpyRecord();
		perNikName = myHero->getNickName();
		lastMap = myHero->getMap();
		wagonId = myHero->memHero->wagonId;	
		piexPt = myHero->getLocation();
		mapId = lastMap->getMapId();
		
		
		/*���ǵ��˽�*/
		if(length > 1)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"the cpy only need one hero if he want come in"<<endl;
			return false;
		}

		
		const char *teamId = myHero->getTeamerId();
		if(strlen(teamId) != 0)
		{	
			failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
			failure_reason->size += 1;
			cout<<"CpyLimit::taskCpyQualifyExam This map forbidden coming with any partners"<<endl;
			return false;
			
	#if 0			
			/*Ϊ�˼�����ֻҪ��ӣ������þͽ�*/
			TeamManager* teamManger = TeamManager::getManagerInst();
			
			Team *team = teamManger->getTeamHandle(teamId);
		
			if(!team)
			{
				cout<<"CpyLimit::taskCpyQualifyExam team is NULL:"<<endl;
				return false;
			}
			
			if(team->size() > 1)
			{
				failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
				strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
				failure_reason->size += 1;
				return false;
			}
		
			team->sendMsg(msg_buf);
	#endif				
		}
		
		/*���˴��ڰ�̯״̬*/
		if(myHero->getHeroState()==5)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_SELL;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"This hero is in bussines state"<<endl;
			return false;
		}	
				
		/*���˴���Ѻ��״̬*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_YA_BIAO;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"The hero mustn't come in with a wagon"<<endl;
			return false;
		}
		/*���˴��ڸ���״̬*/
		if(lastMap->getFlgCpy())
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_COPY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"This hero is already in a cpy map!"<<endl;
			return false;
		}
		
		/*���˴���pk״̬*/
		if(lastMap->getWarType() !=1)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_PK;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"enter list fiveLevent:"<<endl;
			cout<<"The hero mustn't come from a PK map!"<<endl;
			return false;
		}			
	}
	return true;
}	


/*���˽���ľ�¸������*/
bool CpyLimit::qualifyExamTowerLayerCopy(vector<string> &heroId,Failure_Reason* failure_reason)
{
	
	map<string,Hero*>::iterator hero_it;
	char *perNikName,*wagonId,*mapId,*npcMapId;
	int length,i,sizeFail;	
	HeroCpyRecord *record;
	Map_Inform *lastMap;	
	Guild *myGuild;	
	Hero *myHero;
	Point piexPt;
	map<string,Team*>::iterator team_it;
	
	length = heroId.size();
	
	/*û�пշ���*/
	if(asistList.empty())
	{
		if(!borrowCpyFun())
		{
			char failReason[100] = "6,13,";
			char idTset[10]={'\0'};
			strncpy(idTset,cpyId,strlen(cpyId) -2);			
			if(pg_hero == NULL)
			{
				return false;
			}
			sprintf(failReason + strlen(failReason),"%s",idTset);
			send_msg(pg_hero->getFd(), failReason);
			cout<<"CpyLimit::qualifyExamTowerLayerCopy three is not resorce to this cpy:"<<idTset<<endl;		
			return false;
		}		
	}
	
	/*��������*/
	if(length < num) 
	{
		cout<<"CpyLimit::qualifyExamTowerLayerCopy If you want enter it, you must have "<<num<<" members and you only have "<<length<<endl;
		return false;
	}
		
	for(i = 0;i < length;i++)
	{

		sizeFail = failure_reason->size;
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			cout<<"CpyLimit::qualifyExamTowerLayerCopy one of the heroid in hero vector is invalid"<<endl;
			return false;
		}
		record = myHero->getCpyRecord();
		perNikName = myHero->getNickName();
		lastMap = myHero->getMap();
		wagonId = myHero->memHero->wagonId;	
		piexPt = myHero->getLocation();
		mapId = lastMap->getMapId();
		
		/*���ǵ��˽�*/
		if(length > 1)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy the cpy only need one hero if he want come in"<<endl;
			return false;
		}	
		
		const char *teamId = myHero->getTeamerId();
		if(strlen(teamId) != 0)
		{	
			failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy This map forbidden coming with any partners"<<endl;
			return false;
			
	#if 0			
			/*Ϊ�˼�����ֻҪ��ӣ������þͽ�*/
			TeamManager* teamManger = TeamManager::getManagerInst();
			
			Team *team = teamManger->getTeamHandle(teamId);
		
			if(!team)
			{
				cout<<"CpyLimit::qualifyExamTowerLayerCopy team is NULL:"<<endl;
				return false;
			}
			
			if(team->size() > 1)
			{
				failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
				strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
				failure_reason->size += 1;				
				return false;
			}
		
			team->sendMsg(msg_buf);
	#endif				
		}
		
		/*���˴��ڰ�̯״̬*/
		if(myHero->getHeroState()==5)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_SELL;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy This hero is in bussines state"<<endl;
			return false;
		}	
				
		/*���˴���Ѻ��״̬*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_YA_BIAO;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy The hero mustn't come in with a wagon"<<endl;
			return false;
		}
		/*���˴��ڸ���״̬*/
		if(lastMap->getFlgCpy())
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_COPY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy This hero is already in a cpy map!"<<endl;
			return false;
		}
		
		/*���˴���pk״̬*/
		if(lastMap->getWarType() !=1)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_PK;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy The hero mustn't come from a PK map!"<<endl;
			return false;
		}	
		
#if 1
		/*�жϸ��������ȼ�������ȼ������*/
		if(myHero->getLevel() < rank)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_LOWER_RANK;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}
#endif
			
	}
	return true;
}	


/*����ɨ����������*/
void CpyLimit::insertWipeOut(char *heroId)
{	
	if(heroId == NULL || strlen(heroId) == 0)
	{
		cout<<"CpyLimit::insertWipeOut the heroId is NULL:"<<endl;
		return ;
	}
	
	map<string,EctypeRewardSet*>::iterator swap_it;
	swap_it = swapHeroRewardMap.find(heroId);
	if(swap_it != swapHeroRewardMap.end())
	{
		cout<<"CpyLimit::insertWipeOut the heroId is exist:"<<endl;
		return ;
	}
	char *goleStr = "towerCopy";
	vector<string>herVec;
	herVec.push_back(heroId);
	char cpyNowId[6] = {'\0'};
	strncpy(cpyNowId,cpyId,5);
	EctypeRewardSet *reward = helpNewEctypeReward(cpyNowId, herVec, goleStr); 
	if(reward == NULL)
	{
		cout<<"CpyLimit::insertWipeOut the reward is NULL:"<<endl;
		return;
	}
	swapHeroRewardMap[heroId] = reward;	
}	


/*ɾ��ɨ����������*/
void CpyLimit::eraseWipeOut(char *heroId)
{	
	if(heroId == NULL || strlen(heroId) == 0)
	{
		cout<<"CpyLimit::eraseWipeOut the heroId is NULL:"<<endl;
		return ;
	}
	
	map<string,EctypeRewardSet*>::iterator swap_it;
	swap_it = swapHeroRewardMap.find(heroId);
	if(swap_it == swapHeroRewardMap.end())
	{
		cout<<"CpyLimit::eraseWipeOut the heroId is not exist:"<<heroId<<endl;
		return;
	}
	
	delete swap_it->second;
	swap_it->second = NULL;
	swapHeroRewardMap.erase(swap_it);
}

/*���ɨ����������*/
void CpyLimit::clearWipeOut(void)
{	
	if(swapHeroRewardMap.empty())
	{
		cout<<"CpyLimit::clearWipeOut the swapHeroRewardMap is empty:"<<endl;
		return;
	}
	
	map<string,EctypeRewardSet*>::iterator swap_it;
	for(swap_it = swapHeroRewardMap.begin();swap_it != swapHeroRewardMap.end();++swap_it)
	{
		delete swap_it->second;
		swap_it->second = NULL;
	}
	
	swapHeroRewardMap.clear();
}

const char* CpyLimit::getName() const
{
	return name;
}

size_t CpyLimit::getCostFatigue() const
{
	return costFatigue;
}

CpyMemRecord* CpyLimit::getRecord()
{
	return memRecord;
}
	
//ȡ
void CpyLimit::initMemRecord()
{
	int where = -1,size = 0;
		
	char *MemRecord = mem_group->get_data(cpyLimitId, &size,&where);
		
	if(size != sizeof(CpyMemRecord) || MemRecord == NULL || where != 0)
	{
		cout<<"CpyLimit::initMemRecord is NULL:"<<endl;
		
		memRecord = new CpyMemRecord();
		
		return;
	}
		
		
	CpyMemRecord *_memRecord = (CpyMemRecord*)malloc(sizeof(CpyMemRecord));
	
	memRecord = new CpyMemRecord(*_memRecord);		
	
	free(_memRecord);
}

//��
void CpyLimit::storeMemRecord()
{
		
	bool isSuccess = mem_group->set_data(cpyLimitId,(char*)memRecord,(int)sizeof(CpyMemRecord),PUBLIC_MEMCACHED_INDEX);
	
	if(isSuccess)
	{
		cout<<"CpyLimit::storeMemRecord() set memRecord into memcached server success"<<endl;
	}	
	else
	{
		cout<<"CpyLimit::storeMemRecord() set memRecord into memcached server failure"<<endl;
	} 
}

void CpyLimit::recordLessTme(const char* recordHeroId,size_t secondstimes)
{
	if(!recordHeroId)
	{
		cout<<"CpyLimit::recordLessTme the recordHeroId is NULL:"<<endl;
		return;
	}
	Hero *recordHero = heroid_to_hero(recordHeroId);
	if(!recordHero)
	{
		cout<<"CpyLimit::recordLessTme the recordHero is NULL:"<<endl;
		return;
	}	
	if(!memRecord)
	{
		cout<<"CpyLimit::recordLessTme the memRecord is NULL:"<<endl;
		return;
	}
	if(memRecord->changeRecord(recordHero,secondstimes))
	{
		cout<<"CpyLimit::recordLessTme  the cpyLimitId the :"<<cpyLimitId<<" recordHeroId :"<<recordHeroId<<" brush the new record:"<<secondstimes<<endl;
	}
}
	
		
	