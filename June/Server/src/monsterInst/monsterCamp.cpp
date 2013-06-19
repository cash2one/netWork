#include"monsterCamp.h"
#include<math.h>
#include<list>
#include"timerContainer.h"
extern struct ev_loop *loops;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Inform*>mapId_connect_map;  
extern HatValRue *hatValRue;         
extern TimerContainer<MonsterBase*> *monThkContain;
MonsterCamp::MonsterCamp(char *_mapId,char *_typeId,char *_nickName,char *_identity,\
char *_type,char *_kind,int _experience,double _cdTime,int _lifeUpperVal,int _lifeVal,\
int _magicUpperVal,int _magicVal,int _getHrtSud,int _outHrt,int _inHrt, int _outAttVal,\
int _inAttVal,int _outDefVal, int _inDefVal,int _defSumVal,double _hit,double _crit,\
int _voids,int _tenacity,int _moveRange,int _hatRange,int _attRange,\
int _failGoodsless,int _failGoodsmost,int _hatVal,int _gold,set<string>& _failList,\
Point _pt,int _rank,int _speed,int _fiveEleInt,int _fiveHurt,int _fiveEleRank,\
int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,\
vector<string> &skiIdSet,char *_genAttId,double _angVal,\
int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager,int _campFlg):MonsterBase(_mapId,_typeId,_nickName,\
_identity,_type,_kind,_experience,_cdTime,_lifeUpperVal,_lifeVal,\
_magicUpperVal,_magicVal,_getHrtSud,_outHrt,_inHrt, _outAttVal, _inAttVal,\
_outDefVal,_inDefVal,_defSumVal,_hit,_crit,_voids,_tenacity,_moveRange,_hatRange,\
_attRange,_failGoodsless,_failGoodsmost,_hatVal,_gold,_failList,_pt,_rank,_speed,\
_fiveEleInt,_fiveHurt,_fiveEleRank,_forGo,_expTme,_monyTme,_stage,_photoId,skiIdSet,\
_genAttId,_angVal,_ownerAttriType,_ownerAttri,_attackRatio,_isInnerAttack,_lveCtnMager)
{
	campFlg = _campFlg;
	exchgeCampAttriType(campFlg);

}		
		


void MonsterCamp::response(void)
{		
	
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
	//	cout<<"it is playCd time:"<<endl;
		return;
	}
	
	memset(otherMsg,'\0',MONSTER_MSG_LENGTH + 1);
	
	box->getStaInSrcVec(obj);
	
	/*������ʱ�Լ���*/
	hitedSkiFun();
	
	/*�ж��Ƿ���ѣ��*/
	if(!dizz)
	{
		stopMove();
		return;
	}	
	
	/*��ս����Ѫ����*/
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
		schCamp();
		
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
			
			/*��Ѫ����*/
//			recoverBloodSelf();
		
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
					/*Ѱ�Լ���·*/
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
	


MonsterCamp::~MonsterCamp(void)
{

}

MonsterBase* MonsterCamp::copyMon(char *_mapId)
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
	
	newMon = new MonsterCamp(_mapId,typeId,nickName,newIntId,type,kind,experience,\
	cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,outAttVal,\
	inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,walk_ranage,hatRge,\
	attack_range,failGoodsLess,failGoodsMost,hatVal,gold,failList,pt,rank,speed,\
	fiveEleInt,fiveHurt,fiveEleRank,forGo,expTme,monyTme,stage,photoId,skiIdSet,\
	genAttId,angVal,ownerAttriType,ownerAttri,attackRatio,isInnerAttack,lveCtnMager,campFlg);
	newMon->setIsCallType(isCallType);
	return newMon;
}
	
/*������������*/
void MonsterCamp::die(bool flgInit)
{	
	MonsterBase::die(flgInit);
}

/*���ù�������*/
void MonsterCamp::initMonsterALL(void)
{
	MonsterBase::initMonsterALL();
}

/* ��Ѱ�Լ�һ����Ļ�ϵ�hero�����ǲ����ڳ�޷�Χ��*/
void MonsterCamp::schCamp(void) 
{
	set<string>::iterator her_it;
	set<string>HeroIdSet;	
    list<HatVal>new_enmy;	
	Point heroPt;       
	Hero *myHero;
	Nbox *box;
	bool isCpy;
	
	isCpy = false;
	
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	
	box->getCentPtSrcHerIdSet(pt,HeroIdSet);
	
    
	
    for(her_it = HeroIdSet.begin(); her_it != HeroIdSet.end(); her_it++)
    {		
		myHero = heroid_to_hero(*her_it);
        if(myHero == NULL || myHero->getLifeStation() == DEAD || !myHero->getWalkingFlg())
        {
            continue;
        }
		
		if(myHero->getCamp() == campFlg)
		{
			continue;
		}
		
        /*Ϊ�˼������������ж�*/
        heroPt = myHero->getLocation();   
		
		// cout<<"heroPt._x:"<<heroPt._x<<endl;
		// cout<<"heroPt._y:"<<heroPt._y<<endl;
		
		// cout<<"hatRge:"<<hatRge<<endl;
        /*�ж��Ƿ��ڳ�޷�Χ��*/		
		/*�������Գ�����ΪԲ�ģ���޷�Χ�����ĸ�ʽ����*/
		
        if(sqrt(pow(fabs(heroPt._x - born_pt._x),2)+pow(fabs(heroPt._y - born_pt._y),2)) < hatRge)
        {
            HatVal hat(const_cast<char *>((*her_it).c_str()),hatValRue->getHatInRag());
            new_enmy.push_back(hat);
			
			myHero->insertAttList(identity);
        }
    }
	
	if(map_now != NULL && map_now->getFlgCpy())
	{
		isCpy = true;
		enmityValues.swap(new_enmy);
	}
	else
	{
		/*�����³���б�*/
		enmityValues.swap(new_enmy);		
	}
	
	
	int flag;
	/*�������һ�����������г��ֵ�б����Ʒ�������в���*/
	flag = HatFun(enmityValues,new_enmy,perHerId,goodsOwner,identity,isCpy);
	
    /*����б�Ϊ��*/
    if(enmityValues.empty())
    {
        /*�ѵ�ǰĿ���������*/ 
		if(strlen(perHerId) != 0) 
		{
			memset(perHerId,'\0',SHOR_MID_VALUE_LENGTH + 1);
		}
		
		/*�ѵ�ǰ��Ʒ�����������*/
        if(strlen(goodsOwner) != 0)      //add chenzhen 6.8
        {
			memset(goodsOwner,'\0',IDL + 1);
        }
        return;
    }

   
	
    list<HatVal>::iterator hatf_it;  //����б�ͷ��㣨���ֵ���
    list<HatVal>::iterator hats_it;  //����б�ͷ�ڶ���㣨���ֵ�ڶ���

    /*���Ŀ�겻Ϊ�գ���Ŀ�껹�ڳ�޷�Χ��*/
    if(flag > 0)
    {
        /*����б��в�ֹ1����*/
        if(enmityValues.size() >= 2)
        {
            hatf_it = enmityValues.begin();
            hats_it =  hatf_it;
            hats_it ++;

            /*�ж��Ƿ���������������Ŀ��*/
            if((*hats_it).value > (*hatf_it).value * hatValRue->getChageAirPer())
            {
                chageEny(((*hats_it).id));
            }
        }
    } 
	else
    {
        /*����Ŀ��Ϊ����б��ͷ���*/
        chageEny((*(enmityValues.begin())).id);      
    }
}   




	

































			




	





			














	



			




