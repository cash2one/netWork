/************************************************************
    �ļ�����enterTowerLayerCopy.cpp
    �ļ����ã�����ľ�¸���
    ���ߣ�chenzhen
    �������ڣ�2013.04.09
************************************************************/
#include"cpy_series_command_function.h"
#include"cpyLimit.h"
#include"command_other_function_all_over.h"
#include"cpyAsist.h"
#include"cpyManager.h"
#include"towerLayerRecord.h"
#include "instancing_manage.h"
#include "instancing_communication.h"

extern int sock_fd;
extern int g_msg_len;
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern Hero* pg_hero;
extern map<string,map<string,string> >towerMapConf;
 			
void enterTowerLayerCopy(char *buffer)
{
	char *hero_id,*towerId,*layerId,*perNikName,failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       
	map<string,CpyLimit*>::iterator cpyLimt_it;	
	map<string,map<string,string> >::iterator tower_it;
	map<string,string>::iterator layer_it;	
	vector<string> heroId;  
	TowerLayerRecord *towerLayerRecord;
	
	MSG_BEGIN(buffer, g_msg_len);
	
	/*����id*/
	MSG_CHAR(hero_id);	
	
#if 0
	/*������ľ����id*/
	MSG_CHAR(towerId);		
	
	cout<<"towerId:"<<towerId<<endl;

#endif
	
	towerId = pg_hero->memHero->nowTowerId;
	
	/*������ľ�²�id*/
	MSG_CHAR(layerId);		
    
	cout<<"layerId:"<<layerId<<endl;
	
	heroId.push_back(hero_id);
	
	Failure_Reason* failure_reason = (Failure_Reason*)malloc(sizeof(Failure_Reason));	
	
	if(!initFailReson(failure_reason))
	{
		cout<<"enterTowerLayerCopy failure_reason is NULL:"<<endl;
		free(failure_reason); 
		return;
	}
	
	failure_reason->size = 0;	
	
	size_t sizeFail = failure_reason->size;
	
	perNikName = pg_hero->getNickName();
	
#if 1	
	tower_it = towerMapConf.find(towerId);
	if(tower_it == towerMapConf.end())
	{
		failure_reason->member[sizeFail].failure_flag = TOWER_LAYER_COPY_TOWER_ERROR;
		strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
		failure_reason->size += 1;
		
		dealFailRson(failure_reason,failMsg,sizeof(failMsg));
		sendFailMsg(heroId,failMsg);			
		free(failure_reason);	
		
		cout<<"enterTowerLayerCopy the towerId is error:"<<towerId<<endl;
		return;
	}
#endif
	
	layer_it = tower_it->second.find(layerId);
	if(layer_it == tower_it->second.end())
	{
		failure_reason->member[sizeFail].failure_flag = TOWER_LAYER_COPY_LAYER_ERROR;
		strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
		failure_reason->size += 1;
		
		dealFailRson(failure_reason,failMsg,sizeof(failMsg));
		sendFailMsg(heroId,failMsg);			
		free(failure_reason);	
		
		cout<<"enterTowerLayerCopy the layerId is error:"<<layerId<<endl;
		return;
	}
	
	towerLayerRecord = pg_hero->getTowerLayerRecord();
	if(towerLayerRecord == NULL)
	{
		cout<<"enterTowerLayerCopy the towerLayerRecord is NULL:"<<pg_hero->getIdentity()<<endl;
		return;
	}
	
#if 1	
	/*������*/
	if(!towerLayerRecord->isRightTower(towerId))
	{
		failure_reason->member[sizeFail].failure_flag = TOWER_LAYER_COPY_TOWER_CLOSED;
		strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
		failure_reason->size += 1;
		
		dealFailRson(failure_reason,failMsg,sizeof(failMsg));
		sendFailMsg(heroId,failMsg);			
		free(failure_reason);	
		
		cout<<"enterTowerLayerCopy the towerId is closed :"<<towerId<<endl;
		return;
	}
#endif
	
	/*�����*/
	if(!towerLayerRecord->isRightLayer(layerId))
	{
		failure_reason->member[sizeFail].failure_flag = TOWER_LAYER_COPY_LAYER_ERROR;
		strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
		failure_reason->size += 1;
		
		dealFailRson(failure_reason,failMsg,sizeof(failMsg));
		sendFailMsg(heroId,failMsg);			
		free(failure_reason);	
		
		cout<<"enterTowerLayerCopy the layerId is closed :"<<layerId<<endl;
		return;
	}		
	
    cpyLimt_it = cpyId_to_cpyLimit.find(layer_it->second);
	if(cpyLimt_it == cpyId_to_cpyLimit.end())
	{
		failure_reason->member[sizeFail].failure_flag = TOWER_LAYER_COPY_COPY_ERROR;
		strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
		failure_reason->size += 1;
		
		dealFailRson(failure_reason,failMsg,sizeof(failMsg));
		sendFailMsg(heroId,failMsg);			
		free(failure_reason);		
		
		cout<<"enterTowerLayerCopy the copyLimit  is not find error:"<<layer_it->second<<endl;
		return;
	}	
	
	/*�ʸ����*/
	if(!cpyLimt_it->second->qualifyExamTowerLayerCopy(heroId,failure_reason))
	{			
		dealFailRson(failure_reason,failMsg,sizeof(failMsg));
		sendFailMsg(heroId,failMsg);			
		free(failure_reason);			
		return;
	}
	
	cpyLimt_it->second->assignRom(heroId);
	free(failure_reason); 
	pg_hero->setChoiseLayerId(layerId);
	char towerNameMsg[100] = {'\0'};
	sprintf(towerNameMsg,"6,15,%s",cpyLimt_it->second->getName());
	send_msg(pg_hero->getFd(),towerNameMsg);
	pg_hero->updataSingleTarget(0,1);			//����Ŀ��
}			









	
