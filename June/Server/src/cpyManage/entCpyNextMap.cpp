/************************************************************
	�ļ�����entCpyNextMap.cpp
	�ļ����ã����������ķ���
	���ߣ�chenzhen
	�������ڣ�2012.06.27
************************************************************/
#include"command_other_function_all_over.h"
#include"cpy_series_command_function.h"
#include"cpyLimit.h"
#include"cpyAsist.h"
#include"hero.h"

extern int g_msg_len;
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<string, Hero*> heroId_to_pHero;

void entCpyNextMap(char *buffer)
{  
	char *mapId,*fbRom,*hero_id,room[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char fbId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,CpyLimit*>::iterator cpyLimt_it;
	map<string, Hero*>::iterator roleId_it;
	vector<string> heroId;   
	int roomNum;     	
	
	
	
	MSG_BEGIN(buffer, g_msg_len);
	
	/*���������Ѷ�*/
	MSG_CHAR(hero_id);
	
	/*����id*/
	MSG_CHAR_END(mapId);	
	
	/*�Ž�����*/
	heroId.push_back(hero_id);	
	
	/*���heroʵ��ָ���Լ�������Ϣ*/
	roleId_it = heroId_to_pHero.find(hero_id);
	if(roleId_it == heroId_to_pHero.end())
	{
		return;
	}	
	
	fbRom = roleId_it->second->getFbRom();
	if(!dealSerNumStr(fbRom,room,fbId))
	{
		cout<<"the fbRom is error:"<<fbRom<<endl;
	}
	
	roomNum = atoi(room);
	
	if(roomNum < 0)
	{
		cout<<"the fb room is error:"<<roomNum<<endl;
		return;
	}

	cout<<"mapIdNext:"<<mapId<<endl;
	/*�ڸ�����ͼ����׷�ӷ���ţ��γɸ����ض������ͼid*/
	strncat(mapId,"_",strlen("_"));		
	appendNum(mapId,roomNum,4);
	

	/*���Ҹ���*/
	cpyLimt_it = cpyId_to_cpyLimit.find(fbId);
	if(cpyLimt_it == cpyId_to_cpyLimit.end())
	{
		return;
	}
	
	cpyLimt_it->second->enterRom(roomNum,heroId,mapId);
}
	
	
	