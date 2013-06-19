#include"monsterPasstrol.h"
#include"timerContainer.h"
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Inform*>mapId_connect_map;  
extern struct ev_loop *loops; 
extern HatValRue *hatValRue;          //���ֵ������ʵ��ָ��
extern TimerContainer<MonsterBase*> *monThkContain;
MonsterPasstrol::MonsterPasstrol(char *_mapId,char *_typeId,char *_nickName,\
char *_identity,char *_type,char *_kind,int _experience,double _cdTime,\
int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,int _getHrtSud,\
int _outHrt,int _inHrt, int _outAttVal, int _inAttVal,int _outDefVal, int _inDefVal,\
int _defSumVal,double _hit,double _crit,int _voids,int _tenacity,int _moveRange,\
int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,int _hatVal,\
int _gold,set<string>& _failId, Point _pt,int _rank,int _speed,int _fiveEleInt,\
int _fiveHurt,int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,\
char *_photoId,vector<string> &skiIdSet,char *_genAttId,double _angVal,int _ownerAttriType,char* _ownerAttri,\
double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager):MonsterBase(_mapId,_typeId,_nickName,_identity,_type,\
_kind,_experience,_cdTime,_lifeUpperVal,_lifeVal,_magicUpperVal,_magicVal,\
_getHrtSud,_outHrt,_inHrt, _outAttVal, _inAttVal,_outDefVal,_inDefVal,_defSumVal,\
_hit,_crit,_voids,_tenacity,_moveRange,_hatRange,_attRange,_failGoodsless,\
_failGoodsmost,	_hatVal,_gold,_failId,_pt,_rank,_speed,_fiveEleInt,_fiveHurt,\
_fiveRank,_forGo,_expTme,_monyTme,stage,_photoId,skiIdSet,_genAttId,_angVal,\
_ownerAttriType,_ownerAttri,_attackRatio,_isInnerAttack,_lveCtnMager)
{
  flgEnd = false;
}

/*
    ������˼���ص�������getRdPt
    ������
    ����ֵ����
*/      

void MonsterPasstrol::response(void)
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
	
	/*�жϵ�ͼ�Ƿ����ˣ������Ƿ���ѣ��*/
	if(!dizz)
	{
		stopMove();
		return;
	}
	
	/*��ս����Ѫ����*/
	recoverBloodSelf();
	
    /*����Ǵӳ���б�����õ������ֵ��������ô�õ��ģ���Ҫ����޼���*/	
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
		PasSchRge();
		if(!enmityValues.empty())
		{
			chageEny(((*(enmityValues.begin())).id)); 

			/*����Ǵӳ���б�����õ������ֵ��������ô�õ��ģ���Ҫ����޼���*/
			perHero = getHero(perHerId); 
			if(perHero == NULL || !perHero->getLifeStation())
			{
				return;
			}
			
			heroPt = perHero->getLogPt();
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
				
				isInPatrol = false;
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
			if(Rec && !isInPatrol)
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
			else
			{
				if(!isInPatrol)
				{
					/*ģ����Ӧ*/
					if(!judgeGoFor())
					{
						stopMove();	
						return;
					}	
				}
				
				/*�ж��Ƿ��Ѷ���*/
				if(!skiBody)
				{
					stopMove();	
					return;
				}
				
				/*����Ѱ·�յ�*/
				getEnd(endFinPt);  
				
				if(logic_pt == endFinPt)
				{
					Rec = true;
					isInPatrol = false;
					return;
				}
				
				/*������Ѱ·*/
				if(keyPath.empty())
				{
					/*Ѱ�Լ���·*/
					findSlfWay(endFinPt);	//by benliao 20121224,it resoult by chenzhne 12.31	
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


/* 
    �����������ȵ��ü̳е�����������֮�����ͷ�������е���Դ
*/
MonsterPasstrol::~MonsterPasstrol(void)
{
}

MonsterBase* MonsterPasstrol::copyMon(char *_mapId)
{
	char newIntId[SHOR_MID_VALUE_LENGTH + 1] = {0}; 
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
	
	newMon = new MonsterPasstrol(_mapId,typeId,nickName,newIntId,type,kind,\
	experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,\
	outHrt,inHrt, outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,\
	voids,tenacity,walk_ranage, hatRge,attack_range,failGoodsLess,failGoodsMost,\
	hatVal,gold,failList,pt,rank,speed,fiveEleInt,fiveHurt,fiveEleRank,\
	forGo,expTme,monyTme,stage,photoId,skiIdSet,genAttId,angVal,ownerAttriType,\
	ownerAttri,attackRatio,isInnerAttack,lveCtnMager);
	newMon->setIsCallType(isCallType);
	return newMon;
}

/* �����ֵĳ�޷�Χ��Ѱ����*/
void MonsterPasstrol::PasSchRge(void) 
{
    list<HatVal>::iterator hatVal_it;
	map<string,Hero*>::iterator hero_it;
	Point heroPt;
	Hero *hero;
	bool flgGods;
	flgGods = true;
	
	
	for(hatVal_it = enmityValues.begin(); hatVal_it != enmityValues.end();)
	{
		hero_it = heroId_to_pHero.find((*hatVal_it).id);
		if(hero_it == heroId_to_pHero.end())
        {
			if(flgGods)
			{
				if(strlen(goodsOwner) > 0 && strcmp(goodsOwner,(*hatVal_it).id) == 0)
				{
					flgGods = false;
				}
			}
			if(perHerId != NULL && strlen(perHerId) != 0 && strcmp(perHerId,(*hatVal_it).id) == 0)
			{
				memset(perHerId,'\0',SHOR_MID_VALUE_LENGTH + 1);
			}
			
			hatVal_it = enmityValues.erase(hatVal_it);
            continue;
        }
		/*�����ʹӳ���б����*/
		if(hero_it->second->getLifeStation() == DEAD || !hero_it->second->getWalkingFlg())
		{
			if(flgGods)
			{
				if(strlen(goodsOwner) > 0 && strcmp(goodsOwner,(*hatVal_it).id) == 0)
				{
					flgGods = false;
				}
			}
			if(perHerId != NULL && strlen(perHerId) != 0 && strcmp(perHerId,(*hatVal_it).id) == 0)
			{
				memset(perHerId,'\0',SHOR_MID_VALUE_LENGTH + 1);
			}
			hatVal_it = enmityValues.erase(hatVal_it);
			continue;
		}
		/*Ϊ�˼������������ж�*/
        heroPt = hero_it->second->getLocation();   

        /*�ж��Ƿ��ڳ�޷�Χ��*/		
		/*�������Գ�����ΪԲ�ģ���޷�Χ�����ĸ�ʽ����*/
		
        if(sqrt(pow(fabs(heroPt._x - born_pt._x),2)+pow(fabs(heroPt._y - born_pt._y),2)) > hatRge)
        {
			hero = getHero(const_cast<char *>((*hatVal_it).id));
			if(hero != NULL)
			{				
				hero->deleteAttList(identity);
			}
			if(flgGods)
			{
				if(strlen(goodsOwner) > 0 && strcmp(goodsOwner,(*hatVal_it).id) == 0)
				{
					flgGods = false;
				}
			}
			
			if(perHerId != NULL && strlen(perHerId) != 0 && strcmp(perHerId,(*hatVal_it).id) == 0)
			{
				memset(perHerId,'\0',SHOR_MID_VALUE_LENGTH + 1);
			}
			
            hatVal_it = enmityValues.erase(hatVal_it);
            continue;                       
        }
		hatVal_it++;
	}
		
	 /*����б�Ϊ��*/
    if(enmityValues.empty())
    {
        /*�ѵ�ǰĿ���������*/
        if(perHerId != NULL && strlen(perHerId) != 0)
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
	
	if(!flgGods)
	{
		memset(goodsOwner,'\0',IDL + 1);
	}
	else
	{
		if(strlen(goodsOwner) == 0)
		{
			strncpy(goodsOwner,(*(enmityValues.begin())).id,\
					strlen((*(enmityValues.begin())).id));
		}
	}
	
	
    list<HatVal>::iterator hatf_it;  //����б�ͷ��㣨���ֵ���
    list<HatVal>::iterator hats_it;  //����б�ͷ�ڶ���㣨���ֵ�ڶ���

    /*���Ŀ�겻Ϊ�գ���Ŀ�껹�ڳ�޷�Χ��*/
    if(perHerId != NULL && strlen(perHerId) != 0)
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
        chageEny(((*(enmityValues.begin())).id));      
    }
}   

/*������������*/
void MonsterPasstrol::die(bool flgInit)
{
	MonsterBase::die(flgInit);
	
	isInPatrol = false;
}	

/* ������id��������ӣ�û�������*/
void MonsterPasstrol::InpushEnmityValues(HatVal &hatva)
{
    Hero *hero;
    list<HatVal>::iterator enmityValues_it;
    for(enmityValues_it = enmityValues.begin();enmityValues_it != enmityValues.end();enmityValues_it++)
    {
        if(strcmp((*enmityValues_it).id, hatva.id) == 0)
		{
            (*enmityValues_it).value += hatva.value;    
             break;
        }		
    }
    if(enmityValues_it == enmityValues.end())
    {
        enmityValues.push_back(hatva);
    }
	hero = getHero(hatva.id);
	if(hero != NULL)
	{				
		hero->insertAttList(identity);
	}
    enmityValues.sort(ComFun);
   
}

/*���Ѳ���յ�*/
void MonsterPasstrol::getEnd(Point _logicPt)
{
	if(flgEnd)
	{
		return;
	}
	
	
	// endFinPt._x = logic_pt._x + 2;
	// endFinPt._y = logic_pt._y + 2;
	
	endFinPt = born_pt;
	endFinPt._x += 50;
	endFinPt._y += 50;
	
    endFinPt = MapExchangeLogical(endFinPt);
    endFinPt._y += map_now->getBaseDigst();
    if(!map_now->judgeLogPtHind(endFinPt))
    {
       // cout<<"it is hinder:"<<endl;
		flgEnd = false;
		return;
    }
	flgEnd = true;
}  

/*���ù�������*/
void MonsterPasstrol::initMonsterALL(void)
{
	flgEnd = false;  
	
	MonsterBase::initMonsterALL();
}
