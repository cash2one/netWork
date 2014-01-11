/************************************************************
	�ļ�����statuaryBase.cpp
	�ļ����ã�StatuaryBase���ʵ���ļ�
	���ߣ�chenzhen
	�������ڣ�2013.03.01
************************************************************/

#include"statuaryBase.h"
#include"hero.h"


StatuaryBase::StatuaryBase(char* _vocation,map<string,string> &_limitToPhotoId,Point _piexPt,char* _mapId)
{
	memset(vocation,'\0',sizeof(vocation));
	strncpy(vocation,_vocation,strlen(_vocation));
	
	memset(mapId,'\0',sizeof(mapId));
	strncpy(mapId,_mapId,strlen(_mapId));
	
	limitToPhotoId = _limitToPhotoId;
	
	piexPt = _piexPt;
}

/*���ְҵid*/
char* StatuaryBase::getVocation(void)
{
	return vocation;
}

/*��õ�ͼid*/
char* StatuaryBase::getMapId(void)
{
	return mapId;
}

/*������ص�*/
Point StatuaryBase::getPiexPt(void)
{
	return piexPt;
}

/*��ɫӮ�õ���*/
MemStatuaryHero* StatuaryBase::winStatuary(void *memHeros,char* titleId)
{
	char* photoId;
	
	MemHero *memHero = (MemHero*)(memHeros);
	
	if(memHeros == NULL || titleId == NULL)
	{
		cout<<"StatuaryBase::winStatuary the parm is NULL:"<<endl;
		return NULL;
	}
	

	photoId = getPhotoId(titleId);

	if(photoId == NULL)
	{
		cout<<"StatuaryBase::winStatuary the photoId is NULL:"<<endl;
		return NULL;
	}
	
	MemStatuaryHero* winerMemStatuaryHero = new MemStatuaryHero(memHero->identity,memHero->nickName,memHero->basicHeroData.party,\
	memHero->level,memHero->basicHeroData.lifeVal,memHero->basicHeroData.lifeUpperVal+memHero->allBuffDrug[0].effect_value,\
	memHero->basicHeroData.magicVal,memHero->basicHeroData.magicUpperVal,mapId,photoId,titleId,titleId,lastSeconds,piexPt);
	
#if 0	
	MemStatuaryHero* winerMemStatuaryHero = new MemStatuaryHero(winer->getIdentity(),winer->getNickName(),winer->getParty(),\
	winer->getLevel(),winer->getLifeUpperVal(),winer->getLifeVal(),winer->getMagicUpperVal(),winer->getMagicVal(),\
	mapId,photoId,titleId,titleId,lastSeconds,piexPt);
#endif
	return winerMemStatuaryHero;
}

/*���ݲ���require������Ӧ��ͼƬid*/
char* StatuaryBase::getPhotoId(char* require)
{
	map<string,string>::iterator require_it;
	if(limitToPhotoId.empty() || require == NULL)
	{
		cout<<"StatuaryBase::getPhotoId error:"<<endl;
		return NULL;
	}	
	
	require_it = limitToPhotoId.find(require);
	
	if(require_it == limitToPhotoId.end())
	{
		cout<<"StatuaryBase::getPhotoId can not find require error:"<<require<<endl;
		return NULL;
	}
	
	return const_cast<char*>((require_it->second).c_str());
}

/*���ݲ���require������Ӧ��ͼƬid,�����õ�*/
char* StatuaryBase::testGetPhotoId(char* require)
{
	map<string,string>::iterator require_it;
	if(limitToPhotoId.empty() || require == NULL)
	{
		cout<<"StatuaryBase::testGetPhotoId error:"<<endl;
		return NULL;
	}	
	
	require_it = limitToPhotoId.begin();
	
	return const_cast<char*>((require_it->second).c_str());
}




	
	
	

