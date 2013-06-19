#ifndef MONSTER_BY_HERO_H
#define MONSTER_BY_HERO_H
#include"monsterBase.h"

/*�����������������Եı���*/
typedef struct ValueRatio
{
	double lifeUpperValRatio;	//����ֵ����ϵ��			
	double lifeValRatio;		//��ǰ����ֵϵ��	
	double outHrtRatio;    	   //����ϵ��
	double inHrtRatio;      	  //����ϵ��
	double outAttValRatio;    //�⹦����ֵϵ��
	double inAttValRatio;    //�ڹ�����ֵϵ��
	double outDefValRatio;   //�⹦����ֵϵ��
	double inDefValRatio;    //�ڹ�����ֵϵ��
	
	double hitRatio;        //����ϵ��
	double critRatio;       //����ϵ��
	double voidsRatio;      //����ϵ��
	double tenacityRatio;   //����ϵ��	
	double rankRatio;       //�ȼ�ϵ��
	
	ValueRatio(double _lifeUpperValRatio = 0,double _lifeValRatio = 0,double _outHrtRatio = 0,double _inHrtRatio = 0,\
	double _outAttValRatio = 0,double _inAttValRatio = 0,double _outDefValRatio = 0,double _inDefValRatio = 0,\
	double _hitRatio = 0,double _critRatio = 0,double _voidsRatio = 0,double _tenacityRatio = 0,double _rankRatio = 0)
	{
		lifeUpperValRatio = _lifeUpperValRatio;
		
		lifeValRatio = _lifeValRatio;
		
		outHrtRatio = _outHrtRatio;
		
		inHrtRatio = _inHrtRatio;
		
		outAttValRatio = _outAttValRatio;
		
		inAttValRatio = _inAttValRatio;
		
		outDefValRatio = _outDefValRatio;
		
		inDefValRatio = _inDefValRatio;
		
		hitRatio = _hitRatio;
		
		critRatio = _critRatio;
		
		voidsRatio = _voidsRatio;
		
		tenacityRatio = _tenacityRatio;
		
		rankRatio = _rankRatio;
	}		
	
}ValueRatio;


class Map_Inform;
class MonsterByHero : public MonsterBase
{
	ValueRatio valueRatio;

public :
	MonsterByHero(char *_mapId,char *_typeId,char *_nickName,char *_identity,\
	char *_type,char *_kind,int _experience,double _cdTime,int _lifeUpperVal,\
	int _lifeVal,int _magicUpperVal,int _magicVal,int _getHrtSud,int _outHrt,\
	int _inHrt, int _outAttVal, int _inAttVal,int _outDefVal, int _inDefVal,\
	int _defSumVal,double _hit,double _crit,int _voids,int _tenacity,int _moveRange,\
	int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,int _hatVal,\
	int _gold,set<string>& _failId,Point _pt,	int _rank,int _speed,int _fiveEleInt,\
	int _fiveHurt,int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,\
	char *_photoId,vector<string> &skiIdSet,char *_genAttId,double _angVal,\
	int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool isInnerAttack,\
	LveCtnManger _lveCtnMager,ValueRatio valueRatio);
	
	
	
	/*��������*/
	~MonsterByHero(void);
	
	
	/*����˼������*/
	void response(void);	
	

	
	/*�������*/
	MonsterBase* copyMon(char *_mapId);	
	
	/*������������*/
	void die(bool flgInit = false);
	
	/*����������������*/
	void initMonsterALL(void);	
	
	/*���ݽ�ɫ���ɹ�������*/
	void initMonsterValuesByHero(Hero *enterHero);
};
#endif
