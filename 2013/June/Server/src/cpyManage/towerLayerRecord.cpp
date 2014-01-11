/************************************************************
	�ļ�����towerLayerRecord.cpp
	�ļ����ã�ʵ����TowerLayerRecord��ķ���
	���ߣ�chenzhen
	�������ڣ�2013.04.08
************************************************************/

#include"command_other_function_all_over.h"
#include"towerLayerRecord.h"
#include"stdlib.h"
#include"hero.h"
#include<iostream>
#include"cpyLimit.h"

extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<string,map<string,string> >towerMapConf;
using namespace std;

TowerLayerRecord::TowerLayerRecord(Hero *_owner)
{
	map<string,TowerRecordAsist>::iterator tower_it,layer_it,lay_it;	
	
	if(_owner == NULL)
	{
		cout<<"HeroTowerRecord::HeroTowerRecord the argument _owner is NULL:"<<endl;
		return;
	}
	
	owner = _owner;
	
	/*��ʼ������*/
	initTwoerMap();
	initLayerMap();
	
	tower_it = towerMap.find(_owner->memHero->nowTowerId);
	if(tower_it == towerMap.end())
	{
		cout<<"HeroTowerRecord::HeroTowerRecord the argument towerId is error:"<<_owner->memHero->nowTowerId<<endl;
		return;
	}
	layer_it = layerMap.find(_owner->memHero->nowLayerId);
	if(layer_it == layerMap.end())
	{
		cout<<"HeroTowerRecord::HeroTowerRecord the argument layerId is error:"<<_owner->memHero->nowLayerId<<endl;
		return;
	}
	
	tower_it->second.flg = 1;	
	
	/*��ʼ��ÿһ���Ƿ���Խ���*/
	initLayerCanFlg();
	
#if 0
	for(lay_it = layerMap.begin();lay_it != layer_it;++lay_it)
	{
		lay_it->second.flg = 1;
	}
	layer_it->second.flg = 1;
#endif	
	
	memset(nowTowerId,'\0',sizeof(nowTowerId));
	
	memset(nowLayerId,'\0',sizeof(nowLayerId));
	
	strncpy(nowTowerId,_owner->memHero->nowTowerId,strlen(_owner->memHero->nowTowerId));
	
	strncpy(nowLayerId,_owner->memHero->nowLayerId,strlen(_owner->memHero->nowLayerId));	
	
	initTwoerMsg();
	
	if(isShouldBrushLayer())
	{		
		initLayerMsg(true);
	}
	else
	{
		initLayerMsg();
	}
	
	isSwap = false;
	
	cout<<"TowerLayerRecord::TowerLayerRecord test nowTowerId:"<<nowTowerId<<endl;
	cout<<"TowerLayerRecord::TowerLayerRecord test nowLayerId:"<<nowLayerId<<endl;
	
}

/*���������Ϣ*/
void TowerLayerRecord::initMsg(void)
{
	initTwoerMsg();
	initLayerMsg();
}

/*�����������Ϣ*/
void TowerLayerRecord::initTwoerMsg(void)
{
	
	map<string,TowerRecordAsist>::iterator tower_it;
	
	memset(towerMsg,'\0',sizeof(towerMsg));
	
	sprintf(towerMsg,"%d,%d",TOWER_F,TOWER_S);
	
	for(tower_it = towerMap.begin();tower_it != towerMap.end();++tower_it)
	{
		sprintf(towerMsg + strlen(towerMsg),",%s,%d",tower_it->first.c_str(),tower_it->second.flg);
	}
}

/*���ɲ������Ϣ*/
void TowerLayerRecord::initLayerMsg(bool _isCanBuy)
{
	
	map<string,TowerRecordAsist>::iterator layer_it;
	
	memset(layerMsg,'\0',sizeof(layerMsg));
	
	sprintf(layerMsg,"%d,%d",LAYER_F,LAYER_S);
	
	for(layer_it = layerMap.begin();layer_it != layerMap.end();++layer_it)
	{
		sprintf(layerMsg + strlen(layerMsg),",%s,%d",layer_it->first.c_str(),layer_it->second.flg);
	}
	
	//ˢ�°�ť�Ƿ�����1��Ϊ���Ե��
	if(_isCanBuy)
	{
		sprintf(layerMsg + strlen(layerMsg),",%d",1);
	}
	else
	{
		sprintf(layerMsg + strlen(layerMsg),",%d",0);
	}
}

/*���ĵ�ǰ����id*/
bool TowerLayerRecord::changeTowerId(void)
{	
	map<string,TowerRecordAsist>::iterator tower_it,temp_it;
	
	tower_it = towerMap.find(nowTowerId);
	
	temp_it = tower_it;
	++temp_it;
	
	if(tower_it == towerMap.end())
	{
		cout<<"TowerLayerRecord::changeTowerId the nowTowerId is not exist or it up to top of the tower:"<<nowTowerId<<endl;
		return false;
	}
	
	if(temp_it == towerMap.end())
	{
		/*��������¥����ͷ�Σ�����ֱǰ*/
		if(owner)
		{
			owner->addTitle("T053");
			
			owner->updataSingleTarget(7,7);
		}
		
		
		cout<<"TowerLayerRecord::changeTowerId get the top tower:"<<nowTowerId<<endl;
		return false;
	}
	
	/*�ϲ����û�*/
	tower_it->second.flg = 0;
	
	++tower_it;
	
	/*�²�������*/
	tower_it->second.flg = 1;
	
	/*���ĵ�ǰ��id*/
	memset(nowTowerId,'\0',sizeof(nowTowerId));
	
	strncpy(nowTowerId,const_cast<char*>(tower_it->first.c_str()),tower_it->first.size());
	
	/*��memcached*/
	memset(owner->memHero->nowTowerId,'\0',sizeof(owner->memHero->nowTowerId));
	
	strncpy(owner->memHero->nowTowerId,nowTowerId,strlen(nowTowerId));
	
	return true;
}

/*�����֮��ͨ��һ�㺯��*/
void TowerLayerRecord::changeLayerId(void)
{	
	char *choiceLayerId = owner->getChoiseLayerId();	
	
	if(strcmp(choiceLayerId,nowLayerId) != 0)
	{
		chgLayerFlg(choiceLayerId,0);
		
		/*���ɲ����Ϣ*/
		initLayerMsg(true);
		
		send_msg(owner->getFd(), getLayerMsg());
		
		cout<<"TowerLayerRecord::changeLayerId enter the lowerLayer:"<<choiceLayerId<<endl;
		return;
	}
	
	if (owner != NULL)
	{
		char taskNeedCheck[20];
		sprintf(taskNeedCheck, "%s_%s", nowTowerId, nowLayerId);
		if(owner->updateHeroTaskStatus(PASS_TOWER_LAYER_TASK_NEED_TYPE, taskNeedCheck))
		{
			cout<<"Tower001 and layer001 task check ok ,you have finished it!!!!!!!!"<<endl;
			cout<<"Tower001 and layer001 task check ok ,you have finished it!!!!!!!!"<<endl;
			cout<<"Tower001 and layer001 task check ok ,you have finished it!!!!!!!!"<<endl;
		}
		owner->clrTskStSomeBit(TASK_NEED_PASS_TOWER_LAYER);
	}
	
	//���һ�㣬���һ����
	if(strncmp(nowTowerId,"tower_010",9) == 0 && strncmp(nowLayerId,"layer_005",9) == 0)
	{
		lastLayer();
		return;
	}
	
	
	map<string,TowerRecordAsist>::iterator layer_it,temp_it;
	
	layer_it = layerMap.find(nowLayerId);
	
	/*���ݳ���*/
	if(layer_it == layerMap.end() || owner == NULL)
	{
		cout<<"TowerLayerRecord::changeLayerId the nowLayerId is not exist or owner is NULL :"<<nowLayerId<<endl;
		return;
	}
	
	temp_it = layer_it;
	++temp_it;
	
	/*���һ��*/
	if(temp_it == layerMap.end())
	{
		/*��һ������*/
		if(!changeTowerId())
		{
			return;		
		}
		
		/*���ò������*/
		initLayerFlg();
		
		/*���������Ͳ����Ϣ*/
		initMsg();
		
		coverChgeLayerFlg();
		
		if(owner)
		{
			storeData();
			send_msg(owner->getFd(), getTowerMsg());
			send_msg(owner->getFd(), getLayerMsg());			
		}	
		return;
	}
	
	//��ǰ��رգ���һ�㿪����
	chgLayerFlg(nowLayerId,0);
	
	++layer_it;
	
	layer_it->second.flg = 1;

	memset(nowLayerId,'\0',sizeof(nowLayerId));
		
	strncpy(nowLayerId,const_cast<char*>(layer_it->first.c_str()),layer_it->first.size());
	
	chgLayerFlg(nowLayerId,1);
	
	/*���ɲ����Ϣ*/
	initLayerMsg(true);
	
	storeData();
	
	send_msg(owner->getFd(), getLayerMsg());
	
	return ;	
}

/*����ʱ��ʼ���������*/
void TowerLayerRecord::initLayerFlg(void)
{
	
	map<string,TowerRecordAsist>::iterator layer_it;	
	
	for(layer_it = layerMap.begin();layer_it != layerMap.end();++layer_it)
	{
		layer_it->second.flg = 0;
	}
	
	layer_it = layerMap.begin();
	
	layer_it->second.flg = 1;
	
	memset(nowLayerId,'\0',sizeof(nowLayerId));
	
	strncpy(nowLayerId,const_cast<char*>(layer_it->first.c_str()),layer_it->first.size());
	
	/*��memcached*/
	memset(owner->memHero->nowLayerId,'\0',sizeof(owner->memHero->nowLayerId));
	
	strncpy(owner->memHero->nowLayerId,nowLayerId,strlen(nowLayerId));
}	

/*�ж��Ƿ�Ϊ��ǰ��*/
bool TowerLayerRecord::isRightTower(char *towerId)
{
	if(towerId == NULL)
	{
		cout<<"TowerLayerRecord::isRightTower the argument is NULL:"<<endl;
		return false;
	}
	
	if(strncmp(nowTowerId,towerId,strlen(nowTowerId)) == 0)
	{
		return true;
	}
	
	return false;
}

/*�жϲ��Ƿ���*/
bool TowerLayerRecord::isRightLayer(char *layerId)
{
	map<string,TowerRecordAsist>::iterator layer_it;	
	
	if(layerId == NULL)
	{
		cout<<"TowerLayerRecord::isRightLayer the argument is NULL:"<<endl;
		return false;
	}
		
	layer_it = layerMap.find(layerId);
	if(layer_it == layerMap.end())
	{
		cout<<"TowerLayerRecord::isRightLayer the layerId is not found:"<<layerId<<endl;
		return false;
	}
	
	if(layer_it->second.flg == 1)
	{
		return true;
	}
	
	return false;
}

/*��������*/
TowerLayerRecord::~TowerLayerRecord(void)
{
	owner = NULL;
}

/*��ʼ����ľ����������*/
void TowerLayerRecord::initTwoerMap(void)
{
	map<string,map<string,string> >::iterator towerConf_it;
	if(towerMapConf.empty())
	{
		cout<<"TowerLayerRecord::initTwoerMap the towerMapConf is empty ,it to say the towerMargin.xml is error,please stop the progress to check the towerMargin.xml now:"<<endl;
		exit(1);
		return;
	}
	for(towerConf_it = towerMapConf.begin();towerConf_it != towerMapConf.end();++towerConf_it)
	{
		TowerRecordAsist temp(const_cast<char*>(towerConf_it->first.c_str()));
		towerMap[towerConf_it->first] = temp;
	}
}

/*��ʼ����ľ�²������*/
void TowerLayerRecord::initLayerMap(void)
{
	map<string,map<string,string> >::iterator towerConf_it;
	map<string,string>::iterator layer_conf;
	towerConf_it = towerMapConf.begin();
	
	if(towerConf_it->second.empty())
	{
		cout<<"TowerLayerRecord::initLayerMap the towerConf_it->second is empty ,it to say the towerMargin.xml is error,please stop the progress to check the towerMargin.xml now:"<<endl;
		exit(1);
		return;
	}
	
	for(layer_conf = towerConf_it->second.begin();layer_conf != towerConf_it->second.end();++layer_conf)
	{
		TowerRecordAsist temp(const_cast<char*>(layer_conf->first.c_str()));
		layerMap[layer_conf->first] = temp;
	}
}

/*������Ŀ�����Ϣ*/
char* TowerLayerRecord::getTowerMsg(void)
{
	return towerMsg;
}

/*��ò�Ŀ�����Ϣ*/
char* TowerLayerRecord::getLayerMsg(void)
{
	return layerMsg;
}

/*���Ժ�ľ�¶�ȡ�����Ƿ���ȷ*/
void testTowerLayerConf(void)
{
	map<string,map<string,string> >::iterator tower_conf;
	for(tower_conf = towerMapConf.begin();tower_conf != towerMapConf.end();++tower_conf)
	{
		// cout<<"test the towerId before:"<<tower_conf->first<<endl;
		testTowerLayerConfAsist(tower_conf->second);
		// cout<<"test the towerId end:"<<tower_conf->first<<endl;
	}
}	

/*���Ը�������*/
void testTowerLayerConfAsist(map<string,string> &conf)
{
	map<string,string>::iterator tower_conf;
	for(tower_conf = conf.begin();tower_conf != conf.end();++tower_conf)
	{
		// cout<<"layerId :"<<tower_conf->first<<" cpyId :"<<tower_conf->second<<endl;
	}
}	


/*��memcached�涫��*/
void TowerLayerRecord::storeData(void)
{
	memset(owner->memHero->nowTowerId,'\0',sizeof(owner->memHero->nowTowerId));
	memset(owner->memHero->nowLayerId,'\0',sizeof(owner->memHero->nowLayerId));
		
	strncpy(owner->memHero->nowTowerId,nowTowerId,strlen(nowTowerId));
	strncpy(owner->memHero->nowLayerId,nowLayerId,strlen(nowLayerId));
}

/*���õ�ɨ������*/
void TowerLayerRecord::bornSwapOutRewardSet(void)
{
	map<string,TowerRecordAsist>::iterator layer_it,layer_its;
	
	swapLayerId.clear();
	
	layer_it = layerMap.find(nowLayerId);
	if(layer_it == layerMap.end())
	{
		cout<<"TowerLayerRecord::bornSwapOutRewardSet not find the nowLayerId:"<<nowLayerId<<endl;
		return;
	}
	for(layer_its = layerMap.begin();layer_its != layer_it;++layer_its)
	{
		swapLayerId.insert(layer_its->first);
	}
}

/*����ɨ���������*/
void TowerLayerRecord::beginSwapOutReward(void)
{
	if(isSwap)
	{
		cout<<"TowerLayerRecord::beginSwapOutReward you have swaped:"<<endl;
		return;
	}
	
	bornSwapOutRewardSet();
	
	if(swapLayerId.empty())
	{
		cout<<"TowerLayerRecord::beginSwapOutReward the swapLayerId is empty:"<<endl;
		return ;
	}	
	set<string>::iterator layer_it;
	map<string,CpyLimit*>::iterator cpyLimt_it;	
	char *ownerId = owner->getIdentity();
	
	map<string,map<string,string> >::iterator tower_it;
	map<string,string>::iterator layerCpy_it;
	tower_it = towerMapConf.find(nowTowerId);
	if(tower_it == towerMapConf.end())
	{
		cout<<"TowerLayerRecord::beginSwapOutReward the nowTowerId is not exist:"<<nowTowerId<<endl;
		return;
	}
	
	for(layer_it = swapLayerId.begin();layer_it != swapLayerId.end();++layer_it)
	{
		layerCpy_it = tower_it->second.find(*layer_it);
		if(layerCpy_it == tower_it->second.end())
		{
			cout<<"TowerLayerRecord::beginSwapOutReward the layerCpy_it is error:"<<*layer_it<<endl;
			return;
		}
		
		cpyLimt_it = cpyId_to_cpyLimit.find(layerCpy_it->second);
		if(cpyLimt_it == cpyId_to_cpyLimit.end())
		{		
			cout<<"TowerLayerRecord::beginSwapOutReward the layer_it is error:"<<*layer_it<<endl;
			return;
		}
		cpyLimt_it->second->insertWipeOut(ownerId);
	}	
	
	isSwap = true;
}


/*��ȡɨ������*/
void TowerLayerRecord::endSwapOutReward(void)
{
	if(!isSwap)
	{
		cout<<"TowerLayerRecord::endSwapOutReward have not born the beginSwapOutReward:"<<endl;
		return;
	}
	
	if(swapLayerId.empty())
	{
		cout<<"TowerLayerRecord::endSwapOutReward the swapLayerId is empty:"<<endl;
		return;
	}	
	set<string>::iterator layer_it;
	map<string,CpyLimit*>::iterator cpyLimt_it;	
	char *ownerId = owner->getIdentity();
	
	for(layer_it = swapLayerId.begin();layer_it != swapLayerId.end();++layer_it)
	{
		cpyLimt_it = cpyId_to_cpyLimit.find(*layer_it);
		if(cpyLimt_it == cpyId_to_cpyLimit.end())
		{		
			cout<<"TowerLayerRecord::beginSwapOutReward the layer_it is error:"<<*layer_it<<endl;
			return;
		}
		cpyLimt_it->second->eraseWipeOut(ownerId);
	}
	
	isSwap = false;
	swapLayerId.clear();
}

/*��ʼ�����Ƿ���Խ���*/
void TowerLayerRecord::initLayerCanFlg(void)
{
	map<string,TowerRecordAsist>::iterator layer_it = layerMap.begin();
	int len = sizeof(owner->memHero->layerFlg)/sizeof(owner->memHero->layerFlg[0]);	
	for(size_t length = 0; length < len && layer_it != layerMap.end();++length,++layer_it)
	{
		layer_it->second.flg = owner->memHero->layerFlg[length];
	}
}


/*����ÿ���־��������*/
void TowerLayerRecord::chgLayerFlg(char *layerId,int flag)
{
	if(layerId == NULL || strlen(layerId) == 0)
	{
		cout<<"chgLayerFlg the layerId is NULL:"<<endl;
		return;
	}
	
	/*��0�㿪ʼ*/
	size_t index = *(layerId + strlen(layerId) - 1) - '0' - 1;
	
	owner->memHero->layerFlg[index % 5] = flag;
	
	map<string,TowerRecordAsist>::iterator layer_it; 
	
	layer_it = layerMap.find(layerId);
	
	if(layer_it == layerMap.end())
	{
		cout<<"TowerLayerRecord::chgLayerFlg the layerId is error:"<<endl;
		return;
	}
	
	layer_it->second.flg = flag;
	
}


/*����ʱ���Ĳ��־������*/
void TowerLayerRecord::coverChgeLayerFlg(void)
{	
	map<string,TowerRecordAsist>::iterator layer_it = layerMap.begin();
	int len = sizeof(owner->memHero->layerFlg)/sizeof(owner->memHero->layerFlg[0]);	
	for(size_t length = 0; length < len && layer_it != layerMap.end();++length,++layer_it)
	{
		owner->memHero->layerFlg[length] = layer_it->second.flg;
	}
}


/*ˢ�²��־������*/
void TowerLayerRecord::brushLayerFlg(void)
{	
	size_t index = *(nowLayerId + strlen(nowLayerId) - 1) - '0' - 1;	
	index %= 5;
	
	map<string,TowerRecordAsist>::iterator layer_it = layerMap.begin();
	for(size_t length = 0; length <= index && layer_it != layerMap.end();++length,++layer_it)
	{
		owner->memHero->layerFlg[length] = 1;
		layer_it->second.flg = 1;
	}
	
	/*���ɲ����Ϣ*/
	initLayerMsg();
		
	send_msg(owner->getFd(), getLayerMsg());
}

/*�ж��Ƿ��б�Ҫˢ�����Ϊ�棬��ʾ����ˢ�£����򣬱�ʾû��Ҫˢ��*/
bool TowerLayerRecord::isShouldBrushLayer(void)
{	
	size_t index = *(nowLayerId + strlen(nowLayerId) - 1) - '0' - 1;	
	index %= 5;
	
	map<string,TowerRecordAsist>::iterator layer_it = layerMap.begin();
	for(size_t length = 0; length <= index && layer_it != layerMap.end();++length,++layer_it)
	{		
		if(layer_it->second.flg == 0)
		{
			return true;
		}
		
	}
	return false;
}


/*�������һ�㣬���һ�����󣬿����Ǹ�ˢ�°�ť*/
void TowerLayerRecord::lastLayer(void)
{	
	if(owner)
	{
		if(isShouldBrushLayer())
		{
			initLayerMsg(true);
		}
		else
		{
			initLayerMsg(false);				
		}
			
		send_msg(owner->getFd(), getTowerMsg());
		send_msg(owner->getFd(), getLayerMsg());	
	}
}



	
	


