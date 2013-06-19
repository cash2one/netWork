/************************************************************
    �ļ�����enterPartyCamp.cpp
    �ļ����ã����������ķ���
    ���ߣ�chenzhen
    �������ڣ�2012.06.21
************************************************************/
#include"cpyAsist.h"
#include"partyBaseCampLimit.h"
#include "instancing_manage.h"
#include"cpy_series_command_function.h"
#include"guild_asist.h"
extern map<string,PartyBaseCampLimit*> mapIdToCampRomLimit;
extern map<int,string> levelToMapId;   
extern int g_msg_len;
extern Hero* pg_hero;

/*������ɴ�Ӫ*/
void enterCampRom(char *buffer)
{
	char failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,PartyBaseCampLimit*>::iterator camp_it;
	map<int,string>::iterator level_it;
	vector<string> herIdVec;
	char *heroId,*campMapId,*partyid,*partyId;
	Failure_Reason* failure_reason;	
	Guild *myGuild;	
	Map_Src *mapNow;
	Hero *myHero;
	int parRank;
	bool enterFlg;
	
	enterFlg = false;
	
	MSG_BEGIN(buffer, g_msg_len);
	
	MSG_CHAR_END(partyId);	
	
	myHero = pg_hero;
	
	heroId = myHero->getIdentity();
	
	herIdVec.push_back(heroId);	
	
		
	
	cout<<"go here now first :"<<endl;
	if(heroId == NULL || strlen(heroId) == 0)
	{
		cout<<"the heroId is NULL:"<<endl;
		return;
	}
	
	cout<<"go here now second :"<<endl;
	myGuild = myHero->getGuild();
	
	if(myGuild == NULL)
	{
		cout<<"you have not take party in any party:"<<endl;
		return;
	}
	partyid = myGuild->getId();
	
	if(strcmp(partyid,partyId) != 0)
	{
		enterFlg = true;
		myGuild = getGuildWithName(partyId);
		if(myGuild == NULL)
		{
			cout<<"the myGuild is NULL:"<<endl;
			return;
		}		
	}
	parRank = myGuild->getLevel();
	/*�ҵ���Ӧ���ɵȼ�����Ӧ�Ĵ�Ӫ��ͼid*/
	level_it = levelToMapId.find(parRank);	
	if(level_it == levelToMapId.end())
	{
		cout<<"the level of the party is error:"<<partyid<<endl;
		return;
	}	
	cout<<"go here now thrid :"<<endl;
	/*�ҵ���Ӧ��Ӫ��ͼid����Ӧ�Ĵ�Ӫ����ʵ��ָ��*/
	camp_it = mapIdToCampRomLimit.find(level_it->second);	
	if(camp_it == mapIdToCampRomLimit.end())
	{
		cout<<"can not find the campLimitInst:"<<level_it->second<<endl;
		return;
	}
	cout<<"go here now fore :"<<endl;
	
	/*��ʼ��ʧ��ԭ��ṹ��*/
	failure_reason = (Failure_Reason*)malloc(sizeof(Failure_Reason));		
	failure_reason->size = 0;
	
	if(!initFailReson(failure_reason))
	{
		free(failure_reason);
		cout<<"failure_reason is NULL:"<<endl;
		return;
	}	
	
	cout<<"go here now five :"<<endl;
	
	/*����ʸ�*/
	if(!camp_it->second->qualifyExam(herIdVec,failure_reason,enterFlg))
	{
		dealFailRson(failure_reason,failMsg,sizeof(failMsg),3);
		sendFailMsg(herIdVec,failMsg);				
		free(failure_reason);			
	    return;
	}
	
	cout<<"go here now six :"<<endl;
	
	camp_it->second->assignRom(herIdVec,partyid);
	free(failure_reason);
}	