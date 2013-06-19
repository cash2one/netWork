#ifndef MONSTER_STATUARY_H
#define MONSTER_STATUARY_H
#include"monsterBase.h"
#include"statuaryBase.h"
class Map_Inform;
class MonsterStatuary : public MonsterBase
{
	char heroId[SHOR_MID_VALUE_LENGTH + 1];          //���һ����
	

public :
	MonsterStatuary(char *_mapId,char *_typeId,char *_nickName,char *_identity,\
	char *_type,char *_kind,int _experience,double _cdTime,int _lifeUpperVal,\
	int _lifeVal,int _magicUpperVal,int _magicVal,int _getHrtSud,int _outHrt,\
	int _inHrt, int _outAttVal, int _inAttVal,int _outDefVal, int _inDefVal,\
	int _defSumVal,double _hit,double _crit,int _voids,int _tenacity,int _moveRange,\
	int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,int _hatVal,\
	int _gold,set<string>& _failId,Point _pt,	int _rank,int _speed,int _fiveEleInt,\
	int _fiveHurt,int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,\
	char *_photoId,vector<string> &skiIdSet,char *_genAttId,double _angVal,\
	int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool isInnerAttack,LveCtnManger _lveCtnMager);	
	
	
	/*��������*/
	~MonsterStatuary(void);
	
	/*����˼������*/
	void response(void);	
	
	/*�������*/
	MonsterBase* copyMon(char *_mapId);	
	
	/*������������*/
	void die(bool flgInit = false);
	
	/*����������������*/
	void initMonsterALL(void);	
	
	/*�������һ����*/
	void setHeroId(char *_heroId);
	
	/*���õ��������*/
	void setStatuaryAttrit(void);
	
	/*���õ��������*/
	void setStatuaryAttrit(MemStatuaryHero* memStatuaryHero);
	
	/*�ϳɵ����ͼƬ*/
	void composPhotoId(void);
	
	/*���õ��������ͨ����ɫ*/
	void setStatuaryAttritByHero(Hero *hero);
};
#endif
