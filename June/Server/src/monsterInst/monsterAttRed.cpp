#include"monsterAttRed.h"
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Inform*>mapId_connect_map;  
extern struct ev_loop *loops; 
extern HatValRue *hatValRue;          //���ֵ������ʵ��ָ��
MonsterAttRed::MonsterAttRed(char *_mapId,char *_typeId,char *_nickName,\
char *_identity,char *_type,char *_kind,int _experience,double _cdTime,\
int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,int _getHrtSud,\
int _outHrt,int _inHrt, int _outAttVal, int _inAttVal,int _outDefVal,int _inDefVal,\
int _defSumVal,double _hit,double _crit,int _voids,int _tenacity,int _moveRange,\
int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,int _hatVal,\
int _gold,set<string>& _failId, Point _pt,int _rank,int _speed,int _fiveEleInt,\
int _fiveHurt,int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,\
char *_photoId,vector<string> &skiIdSet,char *_genAttId,double _angVal,int _ownerAttriType,char* _ownerAttri,\
double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager,list<Point> _endListPt):MonsterBase(_mapId,_typeId,\
_nickName,_identity,_type,_kind,_experience,_cdTime,_lifeUpperVal,_lifeVal,\
_magicUpperVal,_magicVal,_getHrtSud,_outHrt,_inHrt, _outAttVal,_inAttVal,\
_outDefVal,_inDefVal,_defSumVal,_hit,_crit,_voids,_tenacity,_moveRange,_hatRange,\
_attRange,_failGoodsless,_failGoodsmost,_hatVal,_gold,_failId,_pt,_rank,_speed,\
_fiveEleInt,_fiveHurt,_fiveRank,_forGo,_expTme,_monyTme,_stage,_photoId,skiIdSet,\
_genAttId,_angVal,_ownerAttriType,_ownerAttri,_attackRatio,_isInnerAttack,_lveCtnMager)
{
  flgEnd = false;
  
  endListPt = _endListPt;

}

/*
    ������˼���ص�������getRdPt
    ������
    ����ֵ����
*/      

void MonsterAttRed::response(void)
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

	/*��Ѫ����*/
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
		
		/*�վ�����ר������� add by chenzhen 201301300950*/
		redSchRge();
		
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
			
			/*��Ѫ����*/
	//		recoverBloodSelf();	
		
			if(Rec && !isInPatrol)
			{					
				/*�ж��Ƿ��Ѷ���*/
				if(!skiBody)
				{
					stopMove();	
					return;
				}
				if(logic_pt == perLstPt)
				{
					Rec = false;
					return;	
				}
				
				/*������Ѱ·*/
				if(keyPath.empty())
				{
					findAttWay(perLstPt,false);			
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
				getEnd();  
				
				if(logic_pt == endFinPt)
				{
					Rec = true;
					isInPatrol = false;
					return;
				}
				
				/*������Ѱ·*/
				if(keyPath.empty())
				{
					findSlfWay(endFinPt);		
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
MonsterAttRed::~MonsterAttRed(void)
{
}

MonsterBase* MonsterAttRed::copyMon(char *_mapId)
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
	newMon = new MonsterAttRed(_mapId,typeId,nickName,newIntId,type,kind,experience,\
	cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,outAttVal,\
	inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,walk_ranage,hatRge,\
	attack_range,failGoodsLess,failGoodsMost,hatVal,gold,failList,pt,rank,speed,\
	fiveEleInt,fiveHurt,fiveEleRank,forGo,expTme,monyTme,stage,photoId,skiIdSet,\
	genAttId,angVal,ownerAttriType,ownerAttri,attackRatio,isInnerAttack,lveCtnMager,endListPt);
	newMon->setIsCallType(isCallType);
	return newMon;
}

/*������������*/
void MonsterAttRed::die(bool flgInit)
{
	MonsterBase::die(flgInit);
}	

/* ������id��������ӣ�û�������*/
void MonsterAttRed::InpushEnmityValues(HatVal &hatva)
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
void MonsterAttRed::getEnd(void)
{
	if(flgEnd || endListPt.empty())
	{
		return;
	}
	
	endFinPt = endListPt.front();	
    endFinPt = MapExchangeLogical(endFinPt);
    endFinPt._y += map_now->getBaseDigst();
    if(map_now->getMapHinder()[endFinPt._x][endFinPt._y] == 1 && endFinPt._x > 0 && endFinPt._x < map_now->getRow() && endFinPt._y > 0 && endFinPt._y < map_now->getCol())
    {
       cout<<"[chenzhen warning]: it is hinder of this point:"<<identity<<endl;
		flgEnd = false;
		return;
    }
	flgEnd = true;
}  

/*���ù�������*/
void MonsterAttRed::initMonsterALL(void)
{
	flgEnd = false;  
	
	MonsterBase::initMonsterALL();
}


#if 0

/* ��Ѱ�Լ�һ����Ļ�ϵ�hero�����ǲ����ڳ�޷�Χ��*/
void MonsterAttRed::redSchRge(void) 
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
        /*Ϊ�˼������������ж�*/
        heroPt = myHero->getLocation();   
		
		// cout<<"heroPt._x:"<<heroPt._x<<endl;
		// cout<<"heroPt._y:"<<heroPt._y<<endl;
		
		// cout<<"hatRge:"<<hatRge<<endl;
        /*�ж��Ƿ��ڳ�޷�Χ��*/		
		/*�������Գ�����ΪԲ�ģ���޷�Χ�����ĸ�ʽ����*/
		
        if(sqrt(pow(fabs(heroPt._x - pt._x),2)+pow(fabs(heroPt._y - pt._y),2)) <= hatRge)
        {
            HatVal hat(const_cast<char *>((*her_it).c_str()),hatValRue->getHatInRag());
            new_enmy.push_back(hat);
			
			myHero->insertAttList(identity);
        }
    }
	
	if(map_now != NULL && map_now->getFlgCpy())
	{
		//isCpy = true; copy and wild same. by benliao 2012.12.09
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
            if(perHerId != NULL && strcmp(perHerId,(*hatf_it).id) == 0 && (*hats_it).value > (*hatf_it).value * hatValRue->getChageAirPer())
            {
                chageEny(((*hats_it).id));
            }
			else
			{
				/*����Ŀ��Ϊ����б��ͷ���*/
				chageEny((*hatf_it).id);  
			}
//			cout<<"(*hats_it).value:"<<(*hats_it).value<<endl;
//			cout<<"(*hats_it).id:"<<(*hats_it).id<<endl;
//			cout<<"(*hatf_it).value + :"<<(*hatf_it).value * hatValRue->getChageAirPer()<<endl;
//			cout<<"(*hatf_it).id:"<<(*hatf_it).id<<endl;
			
        }
    } 
	else
    {
        /*����Ŀ��Ϊ����б��ͷ���*/
        chageEny((*(enmityValues.begin())).id);      
    }
}   

#endif


/* ��Ѱ�Լ�һ����Ļ�ϵ�hero�����ǲ����ڳ�޷�Χ��*/
void MonsterAttRed::redSchRge(void) 
{
	set<string>::iterator her_it;
	set<string>HeroIdSet;	
    list<HatVal>new_enmy;	
	Point heroPt;       
	Hero *myHero;
	Nbox *box;
	bool isCpy;
	
	isCpy = false;
	
	/*���˳���б�*/
	PasSchRge();
	
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	
	box->getCentPtSrcHerIdSet(pt,HeroIdSet);
	
    for(her_it = HeroIdSet.begin(); her_it != HeroIdSet.end(); ++her_it)
    {		
		myHero = heroid_to_hero(*her_it);
		
		if(myHero == NULL || myHero->getLifeStation() == DEAD || !myHero->getWalkingFlg() ||\
		!myHero->getisRedName())
        {
            continue;
        }
#if 0		
        if(myHero == NULL || myHero->getLifeStation() == DEAD || !myHero->getWalkingFlg())
        {
            continue;
        }
#endif
        /*Ϊ�˼������������ж�*/
        heroPt = myHero->getLocation();   
		
	
        /*�ж��Ƿ��ڳ�޷�Χ��*/		
		/*�������Ե�ǰ���������ΪԲ�ģ���޷�Χ���ĸ�ʽ����*/
		
        if(sqrt(pow(fabs(heroPt._x - pt._x),2)+pow(fabs(heroPt._y - pt._y),2)) < hatRge)
        {
            HatVal hat(const_cast<char *>((*her_it).c_str()),hatValRue->getHatInRag());
            new_enmy.push_back(hat);
			
			myHero->insertAttList(identity);
        }
    }
	
	/*add by chenzhen 201301311533 */
	if(!new_enmy.empty())
	{
	
		if(map_now != NULL && map_now->getFlgCpy())
		{
			//isCpy = true; copy and wild same. by benliao 2012.12.09
			enmityValues.swap(new_enmy);
		}
		else
		{
			/*�����³���б�*/
			enmityValues.swap(new_enmy);		
		}
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



/* ���˳���б��еĽ�ɫ*/
void MonsterAttRed::PasSchRge(void) 
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
		
		/*���������ʹӳ���б����*/
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
		
     
        if(sqrt(pow(fabs(heroPt._x - pt._x),2)+pow(fabs(heroPt._y - pt._y),2)) > hatRge) //by benliao,not follow hero in all the copy map.
        {
			hero = getHero(((*hatVal_it).id));
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
			
			if(perHerId != NULL && strcmp(perHerId,(*hatVal_it).id) == 0)
			{
				memset(perHerId,'\0',SHOR_MID_VALUE_LENGTH + 1);
			}
			
            hatVal_it = enmityValues.erase(hatVal_it);
            continue;                       
        }
		hatVal_it++;
	}
}      

