#include"monsterStill.h"
#include<math.h>
#include<list>
#include"timerContainer.h"
extern struct ev_loop *loops;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Inform*>mapId_connect_map;  
extern HatValRue *hatValRue;          //���ֵ������ʵ��ָ��  
extern TimerContainer<MonsterBase*> *monThkContain;
MonsterStill::MonsterStill(char *_mapId,char *_typeId,char *_nickName,\
char *_identity,char *_type,char *_kind,int _experience,double _cdTime,\
int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,\
int _getHrtSud,int _outHrt,int _inHrt, int _outAttVal,int _inAttVal,\
int _outDefVal, int _inDefVal,int _defSumVal,double _hit,double _crit,\
int _voids,int _tenacity,int _moveRange,int _hatRange,int _attRange,\
int _failGoodsless,int _failGoodsmost,int _hatVal,int _gold,\
set<string>& _failList,Point _pt,int _rank,int _speed,int _fiveEleInt,\
int _fiveHurt,int _fiveEleRank,int _forGo,int _expTme,int _monyTme,\
char *_stage,char *_photoId,vector<string> &skiIdSet,char *_genAttId,\
double _angVal,int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager)\
:MonsterBase(_mapId,_typeId,_nickName,_identity,_type,_kind,_experience,_cdTime,\
_lifeUpperVal,_lifeVal,_magicUpperVal,_magicVal,_getHrtSud,_outHrt,_inHrt, _outAttVal,\
 _inAttVal,_outDefVal,_inDefVal,_defSumVal,_hit,_crit,_voids,_tenacity,_moveRange,_hatRange,\
 _attRange,_failGoodsless,_failGoodsmost,_hatVal,_gold,_failList,_pt,_rank,_speed,_fiveEleInt,\
 _fiveHurt,_fiveEleRank,_forGo,_expTme,_monyTme,_stage,_photoId,skiIdSet,_genAttId,_angVal,\
_ownerAttriType,_ownerAttri,_attackRatio,_isInnerAttack,_lveCtnMager)
{

}	


//��ֹ�ֲ����κ�����
void MonsterStill::response(void)
{		
	return;
	
	StyObj obj(identity,MONSTER_STYLE_TYPE);
	vector<string> herId;		
	Point heroPt;
	Hero *perHero;		
	Nbox *box;
	
	if(map_now == NULL)
	{
		return;
	}
	
	box = map_now->getBox();	
	if(box == NULL || !isAlive)
	{
		return;
	}
	
	/*�ж������Ƿ���*/
	if(judgeTask())
	{
		cout<<"the task mon of the task is illeay:"<<endl;
		return;
	}
	
	if(!isPlayOver())
	{
		// cout<<"it is playCd time:"<<endl;
		return;
	}	
	
	memset(otherMsg,'\0',MONSTER_MSG_LENGTH + 1);
	
	box->getStaInSrcVec(obj);
	
	/*������ʱ�Լ���*/
	hitedSkiFun();
	
	/*��ͼû��,�ж��Ƿ���ѣ��*/
	if(!dizz)     
	{
		stopMove();
		return;
	}	
	
	/*��Ѫ����*/
	recoverBloodSelf();
	
	/*boss����*/
	if(flgRun)    
	{
		/*�ж��Ƿ��Ѷ���*/
		if(!skiBody)
		{
			stopMove();
			return;
		}		
	}
	else
	{			
		/*��޷�Χ��Ѱ*/
		schRge();
		
		/*�������б�Ϊ��*/
		if(!enmityValues.empty())   
		{						
			/*����Ǵӳ���б�����õ������ֵ��������ô�õ��ģ���Ҫ����޼���*/
			perHero = getHero(perHerId);
			
			if(perHero == NULL || !perHero->getLifeStation())
			{
				return;	
			}
			
			heroPt = perHero->getLogPt();
			
			/*���������ж�*/
			int fight_state = attackRangePoint(pt,perHero->getLocation(),attack_range);	
			
			
			if(fight_state != 1)
			{				
				/*�ж��Ƿ��Ѷ���*/
				if(!skiBody)
				{
					stopMove();					
					return;
				}
         
                /*�������û��������ξͲ���Ҫ��Ѱһ��·*/
                if(jdgSmePt(heroPt))
                {					
                    findAttWay(heroPt);						
					isPersuitHero = true;
                }
			}
			
			else
			{			
				stopMove();	
				exchageHat(herId);
				if(attackPoint && useSkill(herId))
				{					
					return;
				}
				attPerHero(otherMsg,sizeof(otherMsg),perHero);					
				box->sentBoxMsg(otherMsg);
			}			
		}
		else
		{
			/*����ϴ�����׷�ˣ�����γ��û�ˣ�������ͣ����*/
			if(isPersuitHero)
			{
				stopMove();
				
				isPersuitHero = false;
			}
		
			/*��λ*/
            if(Rec)
            { 			
				/*�ж��Ƿ��Ѷ���*/
				if(!skiBody)
				{
					stopMove();	
					return;
				}
				
				if(perLstPt == logic_pt)
				{
					Rec = false;
					return;
				}
				
				/*������Ѱ·*/
				if(keyPath.empty())
				{
					findSlfWay(perLstPt);		
				}			
            }		
			
		}
		
	}
	
	if(perLstPt == logic_pt)
	{
		Rec = false;
	}
	else
	{
		Rec = true;
	}		
	
}	
	


MonsterStill::~MonsterStill(void)
{

}

MonsterBase* MonsterStill::copyMon(char *_mapId)
{
	char newIntId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};     
	MonsterBase* newMon;  
	
	
	if(_mapId == NULL || strlen(_mapId) == 0)
	{
		return NULL;
	}
	
	/* ׷�ӵ�ͼid��Ϊ�˱�֤��������id��Ψһ��*/	
	strncpy(newIntId,_mapId,strlen(_mapId));
	strncat(newIntId,"_",strlen("_"));
	strncat(newIntId,identity,strlen(identity));	
	
	vector<string> skiIdSet;
	getSkiIdSet(skiIdSet);
	
	newMon = new MonsterStill(_mapId,typeId,nickName,newIntId,type,kind,experience,\
	cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,outAttVal,\
	inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,walk_ranage,hatRge,\
	attack_range,failGoodsLess,failGoodsMost,hatVal,gold,failList,pt,rank,speed,\
	fiveEleInt,fiveHurt,fiveEleRank,forGo,expTme,monyTme,stage,photoId,skiIdSet,\
	genAttId,angVal,ownerAttriType,ownerAttri,attackRatio,isInnerAttack,lveCtnMager);
	newMon->setIsCallType(isCallType);
	return newMon;
}
	
/*������������*/
void MonsterStill::die(bool flgInit)
{	
	MonsterBase::die(flgInit);
}

/*���ù�������*/
void MonsterStill::initMonsterALL(void)
{
	MonsterBase::initMonsterALL();
}






	

































			




	





			














	



			




