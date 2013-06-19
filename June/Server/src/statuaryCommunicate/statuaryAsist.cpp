/************************************************************
    �ļ�����statuaryAsist.cpp
    �ļ����ã�������ظ�������
    ���ߣ�chenzhen
    �������ڣ�2013.03.04
************************************************************/
#include"statuaryBase.h"
#include"statuaryHero.h"
#include"statuaryCommunicate.h"
#include "my_memcached.h"
#include"statuaryAsist.h"
#include"command_other_function_all_over.h"
#include"my_mem_group.h"

extern map<string,StatuaryBase*> vocationToStatuaryBaseConf;
extern map<string,StatuaryHero*> statuaryTypeToStatuaryHero;
extern MyMemGroup* mem_group;
extern list<string> strtuaryTitleIdList;
extern set<Point> statuaryPtSet;

/*����������ʱ���ӻ���������ȡ������Ϣ*/
void openServerStatuaryMsg(void)
{
	list<string>::iterator title_it;
	
	initStrtuaryTitleIdList();
	
	for(title_it = strtuaryTitleIdList.begin();title_it != strtuaryTitleIdList.end();++title_it)
	{
		int where = -1,size = 0;
		StatuaryHero* newStatuaryHero;
		
		char *statuaryMem = mem_group->get_data(const_cast<char *>((*title_it).c_str()), &size,&where);

//		char *statuaryMem = mem_operate->get_mem_data(const_cast<char *>((*title_it).c_str()), &size);
		
		if(size != sizeof(MemStatuaryHero) || statuaryMem == NULL || where != 0)
		{
			cout<<"openServerStatuaryMsg the statuaryMem is NULL:"<<endl;
			continue;
		}
		
		printStatuaryPt();
		
		MemStatuaryHero *mem_statuary_data = (MemStatuaryHero*)malloc(sizeof(MemStatuaryHero));
		memset(mem_statuary_data, '\0', sizeof(MemStatuaryHero));
		
		memcpy(mem_statuary_data, statuaryMem, size);
		free(statuaryMem);
		
		newStatuaryHero = new StatuaryHero(mem_statuary_data);
		
		if(newStatuaryHero == NULL)
		{
			cout<<"openServerStatuaryMsg newStatuaryHero is NULL error:"<<endl;
			return;
		}
		
		statuaryTypeToStatuaryHero[*title_it] = newStatuaryHero;
		
		newStatuaryHero->brushMsg();		
	}
}


/*�رշ�����ʱ������������������Ϣ*/
void closeServerStatuaryMsg(void)
{
	map<string,StatuaryHero*>::iterator statuaty_it;	
	
	for(statuaty_it = statuaryTypeToStatuaryHero.begin();statuaty_it != statuaryTypeToStatuaryHero.end();++statuaty_it)
	{
		MemStatuaryHero *mem_statuary_data = statuaty_it->second->getMemStatuaryHero();
		
		bool isSuccess = mem_group->set_data(const_cast<char *>((statuaty_it->first).c_str()),\
		(char*)mem_statuary_data,(int)sizeof(MemStatuaryHero),PUBLIC_MEMCACHED_INDEX);
	
		if(isSuccess == true)
		{
			cout<<"closeServerStatuaryMsg set newMemStatuaryHero into memcached server success"<<endl;
		}	
		else
		{
			cout<<"closeServerStatuaryMsg set newMemStatuaryHero into memcached server failure"<<endl;
		} 
		
		delete statuaty_it->second;
		statuaty_it->second = NULL;		
	}
	statuaryTypeToStatuaryHero.clear();
}

/*��ʼ�������Ӧ�����б����ǵ��񻺴�ļ�*/
void initStrtuaryTitleIdList(void)
{
	strtuaryTitleIdList.clear();
	
	char titleId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	/*��һ����һ������������*/
	strncpy(titleId,"SH_T024",7);	
	strtuaryTitleIdList.push_back(titleId);

#if 0	

	/*�ڶ�����һ������Ӫͳ��*/	
	memset(titleId,'\0',sizeof(titleId));		
	strncpy(titleId,"SH_T025",7);
	strtuaryTitleIdList.push_back(titleId);
	
	
	/*��3����һ��*/
	memset(titleId,'\0',sizeof(titleId));
	
	strncpy(titleId,"SH_T026",7);
	
	strtuaryTitleIdList.push_back(titleId);
	
	/*��4����һ��*/
	memset(titleId,'\0',sizeof(titleId));
	
	strncpy(titleId,"fisrt_D",7);
	
	strtuaryTitleIdList.push_back(titleId);
#endif
}

/*�������*/
void setUpStatuary(char* heroId,char* titleId)
{
	map<string,StatuaryBase*>::iterator vocation_it;
	
	map<string,StatuaryHero*>::iterator statuary_it;
	
	MemStatuaryHero* newMemStatuaryHero;
	
	StatuaryHero* newStatuaryHero;
	
	Hero* myHero;
	
	MemHero *memHero;
	
	if(heroId == NULL || titleId == NULL)
	{
		cout<<"setUpStatuary the parm is NULL:"<<endl;
		return;
	}
	
	myHero = heroid_to_hero(heroId);
	
	if(!myHero)
	{
		int size = 0;
		int where = 0;
		char *pmem = mem_group->get_data(heroId, &size, &where);
		if(pmem == NULL)
		{
			cout<<"setUpStatuary(char* heroId,char* titleId) the pmem is NULL:"<<heroId<<endl;
			return;
		}
	
		memHero = (MemHero *)malloc(sizeof(MemHero));
		memset(memHero, '\0', sizeof(MemHero));
    
		size = size < sizeof(MemHero) ? size : sizeof(MemHero);
		memcpy(memHero, pmem, size);
		free(pmem);
	}
	else
	{
		memHero = myHero->memHero;
	}
	
	statuary_it = statuaryTypeToStatuaryHero.find(titleId);
	if(statuary_it != statuaryTypeToStatuaryHero.end())
	{
		cout<<"setUpStatuary is exist before:"<<endl;
		return;
	}
	
	vocation_it = vocationToStatuaryBaseConf.find(memHero->basicHeroData.party);
	
	if(vocation_it == vocationToStatuaryBaseConf.end())
	{
		cout<<"setUpStatuary vocation_it is equip vocationToStatuaryBaseConf.end():"<<memHero->basicHeroData.party<<endl;
		return;
	}
	
	newMemStatuaryHero = vocation_it->second->winStatuary((void*)memHero,titleId);
	
	if(newMemStatuaryHero == NULL)
	{
		cout<<"setUpStatuary the newMemStatuaryHero is NULL:"<<endl;
		return;
	}
	
	printStatuaryPt();
	
	newStatuaryHero = new StatuaryHero(newMemStatuaryHero);
	
	statuaryTypeToStatuaryHero[titleId] = newStatuaryHero;
	
	newStatuaryHero->brushMsg();
	
	bool isSuccess = mem_group->set_data(titleId, (char*)newMemStatuaryHero, (int)sizeof(MemStatuaryHero),PUBLIC_MEMCACHED_INDEX);
	
	if(isSuccess == true)
	{
		cout<<"setUpStatuary set newMemStatuaryHero into memcached server success"<<endl;
	}	
	else
	{
		 cout<<"setUpStatuary set newMemStatuaryHero into memcached server failure"<<endl;
	} 
	printStatuaryPt();
}


/*�ݻٵ���*/
void destoryStatuary(char* titleId)
{	
	map<string,StatuaryHero*>::iterator statuary_it;
	
	MemStatuaryHero* newMemStatuaryHero;
	
	StatuaryHero* newStatuaryHero;
	
	if(titleId == NULL)
	{
		cout<<"destoryStatuary the parm is NULL:"<<endl;
		return;
	}
	
	statuary_it = statuaryTypeToStatuaryHero.find(titleId);
	if(statuary_it == statuaryTypeToStatuaryHero.end())
	{
		cout<<"destoryStatuary is not exist before:"<<endl;
		return;
	}	
	newStatuaryHero = statuary_it->second;
	
	printStatuaryPt();
	
	newStatuaryHero->destoryMsg();
	
	bool isSuccess = mem_group->delete_data(titleId,PUBLIC_MEMCACHED_INDEX);
	
	if(isSuccess == true)
	{
		cout<<"destoryStatuary  newMemStatuaryHero into memcached server success"<<endl;
	}	
	else
	{
		 cout<<"destoryStatuary newMemStatuaryHero into memcached server failure"<<endl;
	} 
	
	delete newStatuaryHero;
	newStatuaryHero = NULL;
	statuaryTypeToStatuaryHero.erase(statuary_it);	
	printStatuaryPt();
}


/*���Դ�*/
void testInStatuary(void)
{
	
	char titleId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	/*��һ����һ��*/
	
	strncpy(titleId,"SH_T024",7);
	
	bool isSuccess = mem_group->set_data(titleId, "testnewMemStatuaryHero", (int)strlen("testnewMemStatuaryHero"),PUBLIC_MEMCACHED_INDEX);
	
	if(isSuccess == true)
	{
		cout<<"testStatuary set newMemStatuaryHero into memcached server success"<<endl;
	}	
	else
	{
		 cout<<"testStatuary set newMemStatuaryHero into memcached server failure"<<endl;
	}
}

/*����ȡ*/
void testOutStatuary(void)
{	
	
	char titleId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	/*��һ����һ��*/	
	strncpy(titleId,"SH_T024",4);		

	int where = -1,size = 0;
	char *statuaryMem = mem_group->get_data(titleId, &size,&where);
	if(statuaryMem == NULL)
	{
		cout<<"testOutStatuary get newMemStatuaryHero into memcached server failure"<<endl;
	}
	else
	{
		 cout<<"testOutStatuary get newMemStatuaryHero into memcached server success:"<<statuaryMem<<endl;
	}

}


/*������*/
void destroyAllStatuary(void)
{	
	
	char titleId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	/*��һ����һ��*/	
	strncpy(titleId,"SH_T024",7);		
	destoryStatuary(titleId);
	
	cout<<"destroyAllStatuary here before:"<<titleId<<endl;
	/*��2����һ��*/	
	memset(titleId,'\0',sizeof(titleId));	
	strncpy(titleId,"SH_T025",7);		
	destoryStatuary(titleId);
	cout<<"destroyAllStatuary here end:"<<titleId<<endl;
	
	/*��3����һ��*/	
	memset(titleId,'\0',sizeof(titleId));	
	strncpy(titleId,"SH_T026",7);		
	destoryStatuary(titleId);

}

/*���Ե��������*/
void printStatuaryPt(void)
{
	set<Point>::iterator pt_it;
	
	cout<<"test printStatuaryPt begin:"<<endl;
	for(pt_it = statuaryPtSet.begin();pt_it != statuaryPtSet.end();++pt_it)
	{
		cout<<"statuaryPtSet._x:"<<(*pt_it)._x<<"  statuaryPtSet._y:"<<(*pt_it)._y<<endl;
	}
	cout<<"test printStatuaryPt end:"<<endl;
}
	


	
	
	