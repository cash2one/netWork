/************************************************************
	�ļ�����activeAsist.cpp
	�ļ����ã�ʵ�ֻ��������
	���ߣ�chenzhen
	�������ڣ�2012.10.25
************************************************************/
#include "systemMessage.h"
#include"dailyActive.h"
#include"activeAsist.h"
#include"cpyAsist.h"
#include"partyBaseCampLimit.h"
#include "campWarManagement.h"
#include"guild_war_asist.h"
#include"guild_asist.h"
#include"partyRoomLimit.h"
#include "rob_flag_war_logic.h"
#include "camp_leader_and_chief.h"

extern GuildWarAsist *guildWarManage;			//����ս����

extern char server_name[10];
extern DurCampTme durCampTime; 
extern map<string,DailyActive*> dailyActiveConfMap;
extern map<string,PartyBaseCampLimit*> mapIdToCampRomLimit;
extern campWarManagement campWarController;//��Ӫս�����ࣻ 
extern map<string, Hero*> heroId_to_pHero;
extern map<string,PartyRoomLimit*> mapIdToPartyRomLimit; 
extern bool isSetDishTodayActiveFlg;

/*���͵���ص�*/
bool sendInMapPoint(Map_Inform *mapSend,Point piexPtSend,Hero *myHero)
{
	char activeMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	Map_Inform *map_now;	
	
	if(mapSend == NULL || myHero == NULL)
	{
		cout<<"mapSend of active or hero is NUll:"<<endl;
		return false;
	}
	
	
	if(!mapSend->judgePiex(piexPtSend))
	{
		cout<<"piexPtSend is error:"<<endl;
		cout<<"piexPtSend ._x:"<<piexPtSend._x<<endl;
		cout<<"piexPtSend ._y:"<<piexPtSend._y<<endl;
		return false;
	}
	
	map_now = myHero->getMap();
	
	if(map_now== NULL)
	{
		return false;
	}
	
	if(map_now->getFlgCpy())
	{
		outCpy(myHero);
	}
	
	myHero->quit_scene();
	myHero->setMap(mapSend);
	myHero->setLocation(piexPtSend);
	
	sprintf(activeMsg + strlen(activeMsg),"%d%s%d%s%d%s%s%s%d%s%d",\
			2,",",CHANGE_SCENE,",",SUCCESS,",",mapSend->getMapId(),\
			",",piexPtSend._x,",",piexPtSend._y);
			
	send_msg(myHero->getFd(), activeMsg);
	myHero->enter_scene();
	return true;
}


/*������Ӧ����*/
void activePanelResponse(Hero *owner)
{
	map<string,DailyActive*>::iterator active_it;
	char activeMsg[500] = {'\0'};
	if(owner == NULL)
	{
		cout<<"the owner of the active is NULL:"<<endl;
		return;
	}		
	snprintf(activeMsg,sizeof(activeMsg),"%d,%d",2,16);
	for(active_it = dailyActiveConfMap.begin();active_it !=\
		dailyActiveConfMap.end();++active_it)
	{
		if(owner->getGradeNow() >= active_it->second->getLimitLevel())
		{
			snprintf(activeMsg + strlen(activeMsg),sizeof(activeMsg) - strlen(activeMsg),",%s,%d",active_it->second->getActiveId(),active_it->second->getisOpen());
		}
		else
		{
			snprintf(activeMsg + strlen(activeMsg),sizeof(activeMsg) - strlen(activeMsg),",%s,%d",active_it->second->getActiveId(),0);
		}
		
	}
	send_msg(owner->getFd(),activeMsg);
}

/*��int��ʱ�����ַ���*/
bool timeToStr(int hour,int min,char *tmeStr,int lengStr)
{
	if(tmeStr == NULL || lengStr <= 0)
	{
		cout<<"the tmeStr is NULL or the lengStr is error:"<<endl;
		return false;
	}
	if(hour >= 10)
	{
		if(myMin >= 10)
		{
			snprintf(tmeStr,lengStr,"%d:%d",hour,min);
			return true;
		}		
		snprintf(tmeStr,lengStr,"%d:0%d",hour,min);
	}
	else
	{
		if(myMin >= 10)
		{
			snprintf(tmeStr,lengStr,"0%d:%d",hour,min);
			return true;
		}		
		snprintf(tmeStr,lengStr,"0%d:0%d",hour,min);		
	}	
	return true;
}


/*���ַ���ʱ��ת����int��*/
bool tmeStrChgInt(int &hour,int &min,char *timStr)
{
	char hourStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	char minStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	if(timStr == NULL || strlen(timStr) == 0)
	{
		cout<<"the argument timStr is null:"<<endl;
		return false;
	}
	if(!dealSerNumStr(timStr,hourStr,minStr,false,":"))
	{
		cout<<"the argumen timStr is error:"<<timStr<<endl;
		return false;
	}
	hour = atoi(hourStr);
	min = atoi(minStr);
	return true;
}

/*�Ƚ�����ʱ��Ĵ�С�����ǰ��С�ں��ߣ��򷵻���*/
bool timeLess(int &hour1,int &min1,int &hour2,int &min2)
{
	if(hour1 < hour2)
	{
		return true;
	}
	else if(hour1 > hour2)
	{
		return false;
	}
	return min1 < min2;
}

/*�Ƚ�2��ʱ�䣬���ǰ��С���򷵻���*/
bool timeStrLess(char *timStr1,char *timStr2)
{
	int hour1,min1,hour2,min2;
	if(timStr1 == NULL || strlen(timStr1) == 0 || timStr2 == NULL || strlen(timStr2) == 0)
	{
		cout<<"the argument timStr is null:"<<endl;
		return false;
	}
	
	if(!tmeStrChgInt(hour1,min1,timStr1) || !tmeStrChgInt(hour2,min2,timStr2))
	{
		cout<<"the argument timStr is or the timStr2 error:"<<timStr1<<endl;
		return false;
	}
	
	return timeLess(hour1,min1,hour2,min2);
}

/*����������Ŀ�����ر�*/
void controlActiveOpenAndClose(int hour,int min,int whichDay)
{
	map<string,DailyActive*>::iterator active_it; 
	char tmeStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	DailyActive *active;	
	
	if(!timeToStr(hour,min,tmeStr,sizeof(tmeStr)))
	{
		cout<<"the time is error:"<<endl;
		return;
	}
	
	for(active_it = dailyActiveConfMap.begin();\
		active_it != dailyActiveConfMap.end();++active_it)
	{
		active = active_it->second;	
		
		/*�Ƿ�������*/
		if(!active->isRightDay(whichDay))
		{
			
			// cout<<"not the day :"<<whichDay<<" of the activeId:"<<active->getActiveId()<<endl;
			continue;
		}
		
		if(!isSetDishTodayActiveFlg && strcmp(active->getActiveId(), "107") == 0)
		{
			setDishTodayActiveFlg();
			isSetDishTodayActiveFlg = true;
		}
		
		/*��ʾ��Ϣ�ж�*/
		if(active->isOffTme(tmeStr))
		{
			
			// cout<<"it is the time of send the off msg:"<<active->getActiveId()<<endl;
		}
		
		/*�Ƿ��ѿ���*/
		if(active->getisOpen())
		{
			if(!active->isEnd(tmeStr))
			{
				// cout<<"tmeStr:"<<tmeStr<<endl;
				// cout<<"it is not the time to close the acitve:"<<active->getActiveId()<<endl;
				continue;
			}
			closeActive(active);
		}
		/*�Ƿ��ѹر�*/
		else
		{
			if(!active->isBegin(tmeStr))
			{
				// cout<<"tmeStr:"<<tmeStr<<endl;
				// cout<<"it is not the time to open the acitve:"<<active->getActiveId()<<endl;
				continue;
			}
			openActive(active);
		}	
#if 0
		/*���Իʱ��*/
		active->printTme();
		
#endif
	}	
}

/*�����*/
void openActive(DailyActive *active)
{
	string msg;
	char *activeId;
	
	if(active == NULL)
	{
		cout<<"the active is NUll:"<<endl;
		return;
	}	
	
	activeId = active->getActiveId();
	
	/*������ť���ҷ���ȫ����Ϣ*/
	active->setisOpen(true);		
	active->formOpenMsg();
	msg = active->getOpenMsg();		
	active->setOffType(false);
	SYSTEM_MESSAGE::systemMssageAllEral(msg,active->getLimitLevel());
	// cout<<"openActive msg:"<<msg<<endl;
//	SYSTEM_MESSAGE::systemActivityMsg(const_cast<char *>(msg.c_str()),5,60);	
	
	/*�boss*/
	if(strcmp(activeId,"103") == 0)
	{			
		// cout<<"open the bossActive:"<<endl;
		brushMonsterActiveBoss();
	}		
	/*��Ӫս����*/
	else if(strcmp(activeId,"302") == 0)
	{
		/*֮��Ĵ���*/
	}
	/*��Ӫ���ֶ�*/
	else if(strcmp(activeId,"303") == 0)
	{
		/*֮��Ĵ���*/
		// cout<<"[XHM MSG] STAET startOrdinaryCampWar"<<endl;
		campWarController.startOrdinaryCampWar(time(NULL));
	}
	/*��Ӫ����վ*/
	else if(strcmp(activeId,"304") == 0)
	{
		/*֮��Ĵ���*/
		campWarController.startLeaderCampWar(time(NULL));
	}
	/*��������*/
	else if(strcmp(activeId,"305") == 0)
	{
		/*֮��Ĵ���*/
		campWarController.startChiefCampWar(time(NULL));	
	}	
	/*����ʱ��*/
	else if(strcmp(activeId,"306") == 0)
	{
		/*֮��Ĵ���*/
		cout<<"[XHM TEST] ********************************************** activity.cpp ***********************************"<<endl;
		campWarController.startApplyLeaderCampWar(time(NULL));	//TODO ���Ȱ���Ӫͳ��ս�����ŵ�����������ļ������󣬷ŵ����������£������� RTX xhm;	
	}
	//����ս����
	else if (strcmp(active->getActiveId(), "202") == 0 && robFlagWarManage != NULL)
	{
		robFlagWarManage->setIsInRobFlagWarTime(true);
	}
	
	//����ս����
	else if (strcmp(active->getActiveId(), "307") == 0)
	{
		campWarController.setInCampResWarTime(true);
	}
	
	/*ϵͳ��Է�*/
	else if (strcmp(active->getActiveId(), "107") == 0 )
	{
		openDishActive();
	}
	
	//���µ�һ¥����ʱ�俪��
	else if (!strcmp(active->getActiveId(), "104"))
	{
		isInFirstRoomHappyTime = true;
	}
	
	//�����˼�����ʱ�俪��
	else if (!strcmp(active->getActiveId(), "105"))
	{
		isInSecondRoomHappyTime = true;
	}
	
}	

/*�رջ*/
void closeActive(DailyActive *active)
{
	string msg;
	char *activeId;
	if(active == NULL)
	{
		cout<<"the active is NUll:"<<endl;
		return;
	}	
	
	activeId = active->getActiveId();
	
	/*������ť���ҷ���ȫ����Ϣ*/
	active->setisOpen(false);		
	active->formOpenMsg();
	msg = active->getOpenMsg();
	active->setOffType(true);
	
	SYSTEM_MESSAGE::systemMssageAllEral(msg,active->getLimitLevel());
	
	cout<<"closeActive msg:"<<msg<<endl;
	
//	SYSTEM_MESSAGE::systemActivityMsg(const_cast<char *>(msg.c_str()),5,60);
	
	/*�boss*/
	if(strcmp(activeId,"103") == 0)
	{			
		initMonsterActiveBoss();
	}
	/*��Ӫս����*/
	else if(strcmp(activeId,"302") == 0)
	{
		/*֮��Ĵ���*/
	}
	/*��Ӫ���ֶ�*/
	else if(strcmp(activeId,"302") == 0)
	{
		/*֮��Ĵ���*/
	}
	/*��Ӫ����վ*/
	else if(strcmp(activeId,"304") == 0)
	{
		/*֮��Ĵ���*/
	}
	/*��������*/
	else if(strcmp(activeId,"305") == 0)
	{
		/*֮��Ĵ���*/
		// campWarController.startChiefCampWar(time(NULL));	
	}	
	/*����ʱ��*/
	else if(strcmp(activeId,"306") == 0)
	{
		/*֮��Ĵ���*/

		// campWarController.startApplyLeaderCampWar(time(NULL));	//TODO ���Ȱ���Ӫͳ��ս�����ŵ�����������ļ������󣬷ŵ����������£������� RTX xhm;	
	}	
	//����ս�����
	else if (strcmp(active->getActiveId(), "202") == 0 && robFlagWarManage != NULL)
	{
		robFlagWarManage->setIsInRobFlagWarTime(false);
	}
	else if (strcmp(active->getActiveId(), "307") == 0)
	{
		campWarController.setInCampResWarTime(false);
	}
	
	else if (strcmp(active->getActiveId(), "204") == 0)
	{
		rankGuildWarScore(); 
	}
	else if (strcmp(active->getActiveId(), "205") == 0)
	{
		chooseLeaderAndChief();
	}
	else if (strcmp(active->getActiveId(), "206") == 0)
	{
		clearLastWeekGuildWarScore();
	}
	/*ϵͳ��Է�*/
	else if (strcmp(active->getActiveId(), "107") == 0 )
	{
		closeDishActive();
	}
	
	//���µ�һ¥����ʱ��ر�
	else if (!strcmp(active->getActiveId(), "104"))
	{
		isInFirstRoomHappyTime = false;
	}
	
	//�����˼�����ʱ��ر�
	else if (!strcmp(active->getActiveId(), "105"))
	{
		isInSecondRoomHappyTime = false;
	}
}				
	


	
/*����������ʱ���ж���Щ�Ӧ�ÿ���*/
void controlActiveOpenStartServer(int hour,int min,int whichDay)
{
	map<string,DailyActive*>::iterator active_it; 
	char tmeStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	DailyActive *active;	
	
	if(!timeToStr(hour,min,tmeStr,sizeof(tmeStr)))
	{
		cout<<"the time is error:"<<endl;
		return;
	}
	
	for(active_it = dailyActiveConfMap.begin();\
		active_it != dailyActiveConfMap.end();++active_it)
	{
		active = active_it->second;			
		
		/*�Ƿ�������*/
		if(!active->isRightDay(whichDay))
		{
			
			// cout<<"not the day :"<<whichDay<<" of the activeId:"<<active->getActiveId()<<endl;
			continue;
		}
		
		/*ϵͳ��Է�*/
		if(!isSetDishTodayActiveFlg && strcmp(active->getActiveId(), "107") == 0)
		{
			setDishTodayActiveFlg();
			
			isSetDishTodayActiveFlg = true;
		}
		
		/*�Ƿ��ѿ���*/
		if(!active->getisOpen())
		{	
			if(!active->isMidTme(tmeStr))
			{
				cout<<"tmeStr:"<<tmeStr<<endl;
				cout<<"it is not the time to open the acitve:"<<active->getActiveId()<<endl;
				continue;
			}
			cout<<"open the active:"<<active->getActiveId()<<endl;
			openActive(active);
		}
		

		/*���Իʱ��*/
		active->printTme();

	}

}

	

/*����������ʱ����ʼ����Ӫ��ĳ���ʱ��*/
void initCampeDurTme(void)
{
	map<string,DailyActive*>::iterator active_it; 	
	DailyActive *active;		
	char *activeId;
	int durSeconsTme;
	
	for(active_it = dailyActiveConfMap.begin();\
		active_it != dailyActiveConfMap.end();++active_it)
	{
		active = active_it->second;	
		activeId = active->getActiveId();
		if(activeId == NULL ||strlen(activeId) == 0)
		{
			continue;
		}		
		
		/*��Ӫս����*/
		else if(strcmp(activeId,"302") == 0)
		{
			durSeconsTme = active->getdurTme();
			if(durSeconsTme > 0)
			{				
				durCampTime.campBatFldOlder = durSeconsTme;
			}
		}
		/*��Ӫ���ֶ�*/
		else if(strcmp(activeId,"303") == 0)
		{
			durSeconsTme = active->getdurTme();
			if(durSeconsTme > 0)
			{
				durCampTime.camphappyFight = durSeconsTme;
			}
		}
		/*��Ӫ����վ*/
		else if(strcmp(activeId,"304") == 0)
		{
			durSeconsTme = active->getdurTme();
			if(durSeconsTme > 0)
			{
				durCampTime.campcompeteFight = durSeconsTme;
			}
			durSeconsTme = active->getPeaceTme();
			if(durSeconsTme > 0)
			{
				durCampTime.campPeaceTme = durSeconsTme;
			}
		}
		/*��������*/
		else if(strcmp(activeId,"305") == 0)
		{
			durSeconsTme = active->getdurTme();
			if(durSeconsTme > 0)
			{
				durCampTime.kungFuMaster = durSeconsTme;
			}
			durSeconsTme = active->getPeaceTme();
			if(durSeconsTme > 0)
			{
				durCampTime.kungPeaceTme = durSeconsTme;
			}
		}
		/*����ʱ��*/
		else if(strcmp(activeId,"306") == 0)
		{
			durSeconsTme = active->getdurTme();
			if(durSeconsTme > 0)
			{
				durCampTime.takePartDurTme = durSeconsTme;
			}
		}
	}	
	/*���Դ�ӡ*/
	durCampTime.printDurTme();
}

/*��������̽Ӫ�*/
void openCampActive(void)
{
	map<string,PartyBaseCampLimit*>::iterator camp_it;
	for(camp_it = mapIdToCampRomLimit.begin();camp_it != mapIdToCampRomLimit.end();++camp_it)
	{
		camp_it->second->setOpenFlg(true);
	}
}

/*�رհ���̽Ӫ�*/
void closeCampActive(void)
{
	map<string,PartyBaseCampLimit*>::iterator camp_it;
	for(camp_it = mapIdToCampRomLimit.begin();camp_it != mapIdToCampRomLimit.end();++camp_it)
	{
		camp_it->second->setOpenFlg(false);
	}
}

void refreshSrvDaily()
{
	map<string, Hero*>::iterator it_hero = heroId_to_pHero.begin();
	for (it_hero; it_hero != heroId_to_pHero.end(); it_hero++)
	{
		Hero* hero = it_hero->second;
		if (hero != 0)
		{
			hero->updateHeroDaily();
			
			char refreshTask_msg[1024]={'\0'};
			snprintf(refreshTask_msg, sizeof(refreshTask_msg), "%d,%d,%s,%d,%s,%s,",17,0, server_name, (int)MY_TV_SEC, hero->getIdentity(), hero->getNickName());
			write_log(refreshTask_msg);	
		}
	}
}



/*��������ʢ��*/
void openDishActive(void)
{
	map<string,PartyRoomLimit*>::iterator dishActive_it;
	cout<<"open the openDishActive bofore:"<<endl;
	for(dishActive_it = mapIdToPartyRomLimit.begin();dishActive_it != mapIdToPartyRomLimit.end();++dishActive_it)
	{
		cout<<"open the openDishActive begin:"<<endl;
		dishActive_it->second->setActiveFlg(true);
//		dishActive_it->second->setSystemDishState(2);
		dishActive_it->second->isTmeToDinner();
		cout<<"open the openDishActive end:"<<endl;
	}
	cout<<"open the openDishActive last:"<<endl;
}

/*�رհ���ʢ��*/
void closeDishActive(void)
{
	map<string,PartyRoomLimit*>::iterator dishActive_it;
	cout<<"close the closeDishActive bofore:"<<endl;
	for(dishActive_it = mapIdToPartyRomLimit.begin();dishActive_it != mapIdToPartyRomLimit.end();++dishActive_it)
	{
		dishActive_it->second->setActiveFlg(false);
		dishActive_it->second->closeSystemDish();
//		dishActive_it->second->setSystemDishState(0);
	}
	cout<<"close the closeDishActive end:"<<endl;
}


/*���ÿ�������ʢ���Ƿ�Ϊ����ı��ֵ*/
void setDishTodayActiveFlg(void)
{
	map<string,PartyRoomLimit*>::iterator dishActive_it;
	
	cout<<"setDishTodayActiveFlg open bofore:"<<endl;
	for(dishActive_it = mapIdToPartyRomLimit.begin();dishActive_it != mapIdToPartyRomLimit.end();++dishActive_it)
	{		
		dishActive_it->second->setTodayActiveFlg(true);			
	}
	cout<<"setDishTodayActiveFlg open last:"<<endl;
}

/*���ùرհ���ʢ���Ƿ�Ϊ����ı��ֵ*/
void setCloseDishTodayActiveFlg(void)
{
	map<string,PartyRoomLimit*>::iterator dishActive_it;
	
	cout<<"setCloseDishTodayActiveFlg bofore:"<<endl;
	for(dishActive_it = mapIdToPartyRomLimit.begin();dishActive_it != mapIdToPartyRomLimit.end();++dishActive_it)
	{
		cout<<"setCloseDishTodayActiveFlg begin:"<<endl;
		dishActive_it->second->setTodayActiveFlg(true);		
		dishActive_it->second->setIsActiveDishBru();
		cout<<"setCloseDishTodayActiveFlg end:"<<endl;
	}
	cout<<"setCloseDishTodayActiveFlg last:"<<endl;
}


/*���ùرհ���ʢ���Ƿ�Ϊ����ı��ֵ,������*/
void setCloseDishTodayActiveFlgTset(void)
{
	map<string,PartyRoomLimit*>::iterator dishActive_it;
	
	cout<<"setCloseDishTodayActiveFlg bofore:"<<endl;
	for(dishActive_it = mapIdToPartyRomLimit.begin();dishActive_it != mapIdToPartyRomLimit.end();++dishActive_it)
	{
		cout<<"setCloseDishTodayActiveFlg begin:"<<endl;
		dishActive_it->second->setTodayActiveFlg(false);		
		dishActive_it->second->setIsActiveDishBruTrue();
		cout<<"setCloseDishTodayActiveFlg end:"<<endl;
	}
	cout<<"setCloseDishTodayActiveFlg last:"<<endl;
}

