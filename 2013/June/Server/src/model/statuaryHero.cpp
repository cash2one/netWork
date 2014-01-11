/************************************************************
	�ļ�����statuaryHero.cpp
	�ļ����ã�StatuaryHero���ʵ���ļ�
	���ߣ�chenzhen
	�������ڣ�2013.03.01
************************************************************/

#include"statuaryHero.h"
#include"map_src.h"
#include"nbox.h"
extern map<string,Map_Src*>mapId_connect_map;
extern set<Point> statuaryPtSet;
StatuaryHero::StatuaryHero(MemStatuaryHero* _memStatuaryHero)
{	
	set<Point>::iterator pt_it;
	
	memStatuaryHero = _memStatuaryHero;
	
	piexPt._x = memStatuaryHero->piex_x;
	
	piexPt._y = memStatuaryHero->piex_y;
	
	memset(inSeeMsg,'\0',sizeof(inSeeMsg));
	
	memset(outSeeMsg,'\0',sizeof(outSeeMsg));
	
	if(!initMapInform())
	{
		cout<<"StatuaryHero::StatuaryHero initMap is error:"<<endl;
	}
	
	if(statuaryPtSet.empty())
	{
		cout<<"StatuaryHero::StatuaryHero statuaryPtSet is empty is error:"<<endl;
	}
	
	/*��������*/
	pt_it = statuaryPtSet.find(piexPt);
	if(pt_it == statuaryPtSet.end())
	{
		piexPt = *statuaryPtSet.begin();
		statuaryPtSet.erase(statuaryPtSet.begin());
	}
	else
	{
		statuaryPtSet.erase(pt_it);
	}
	
	memStatuaryHero->piex_x = piexPt._x;
	memStatuaryHero->piex_y = piexPt._y;
	
	formInSeeMsg();
	
	cout<<"inSeeMsg:"<<inSeeMsg<<endl;
	
	formOutSeeMsg();
	
}

/*��ù�����ɫid*/
char* StatuaryHero::getHeroId(void)
{
	return memStatuaryHero->heroId;
}

/*���memStatuaryHero*/
MemStatuaryHero* StatuaryHero::getMemStatuaryHero(void)
{
	return memStatuaryHero;
}

/*��������*/
StatuaryHero::~StatuaryHero(void)
{
	delete memStatuaryHero;
	memStatuaryHero = NULL;
	map_now = NULL;
}


/*����������Ϣ*/
void StatuaryHero::formInSeeMsg(void)
{
	snprintf(inSeeMsg,sizeof(inSeeMsg),"2,30,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d",memStatuaryHero->requre,memStatuaryHero->vocation,\
	memStatuaryHero->photoId,memStatuaryHero->heroId,memStatuaryHero->heroName,memStatuaryHero->level,memStatuaryHero->lifeUpperVal,\
	memStatuaryHero->lifeVal,memStatuaryHero->magicUpperVal,memStatuaryHero->magicVal,piexPt._x,piexPt._y);
}	

/*����������Ϣ*/
void StatuaryHero::formOutSeeMsg(void)
{
	strncpy(outSeeMsg,"2,5,1",5);
}

/*���������Ϣ*/
char* StatuaryHero::getInSeeMsg(void)
{
	return inSeeMsg;
}

/*���������Ϣ*/
char* StatuaryHero::getOutSeeMsg(void)
{
	return outSeeMsg;
}

/*��ʼ����ͼʵ��ָ��*/
bool StatuaryHero::initMapInform(void)
{
	map<string,Map_Src*>::iterator map_it;
	map_it = mapId_connect_map.find(memStatuaryHero->mapId);
	
	if(map_it == mapId_connect_map.end())
	{
		cout<<"StatuaryHero::initMapInform is error :"<<memStatuaryHero->mapId<<endl;
		return false;
	}
	
	map_now = map_it->second;
	return true;
}

/*�����������*/
Point StatuaryHero::getPiexPt(void)
{
	return piexPt;
}

/*ˢ������*/
void StatuaryHero::brushMsg(void)
{
	StyObj obj(memStatuaryHero->titleId,STATUARY_STYLE_TYPE);
	Nbox *box;               
	 
	if(map_now == NULL)
	{
		return;
	}
	
	box = map_now->getBox();	
	
	if(box == NULL)
	{
		return;
	}

	map_now->insertID(obj);
	
	box->getStaInSrcVec(obj);	
	
	box->sentBoxMsg(inSeeMsg);

#if 0	
	cout<<"STATUARY_STYLE_TYPE:"<<STATUARY_STYLE_TYPE<<endl;
	cout<<"memStatuaryHero->titleId:"<<memStatuaryHero->titleId<<endl;
	cout<<"inSeeMsg:"<<inSeeMsg<<endl;
#endif
}

/*�ݻٵ���*/
void StatuaryHero::destoryMsg(void)
{
	StyObj obj(memStatuaryHero->titleId,STATUARY_STYLE_TYPE);
	Nbox *box;               
	 
	if(map_now == NULL)
	{
		return;
	}
	
	box = map_now->getBox();	
	
	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);	
	
	box->sentBoxMsg(outSeeMsg);
	
	map_now->deleteID(obj);
	
	/*���������*/
	statuaryPtSet.insert(piexPt);

#if 0	
	cout<<"STATUARY_STYLE_TYPE:"<<STATUARY_STYLE_TYPE<<endl;
	cout<<"memStatuaryHero->titleId:"<<memStatuaryHero->titleId<<endl;
	cout<<"outSeeMsg:"<<outSeeMsg<<endl;
#endif
}

/*�޸�����*/
void StatuaryHero::setPiex(Point _piexPt)
{
	piexPt = _piexPt;
}
	
	

