#include"monsterEscape.h"
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Inform*>mapId_connect_map;  
extern struct ev_loop *loops; 
extern HatValRue *hatValRue;          //���ֵ������ʵ��ָ��
MonsterEscape::MonsterEscape(char *_mapId,char *_typeId,char *_nickName,\
char *_identity,char *_type,char *_kind,int _experience,double _cdTime,\
int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,\
int _getHrtSud,int _outHrt,int _inHrt, int _outAttVal, int _inAttVal,\
int _outDefVal, int _inDefVal,int _defSumVal,double _hit,\
double _crit,int _voids,int _tenacity,int _moveRange,\
int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,\
int _hatVal,int _gold,set<string>& _failId, Point _pt,int _rank,\
int _speed,int _fiveEleInt,int _fiveHurt,int _fiveRank,int _forGo,\
int _expTme,int _monyTme,char *_stage,char *_photoId,\
vector<string> &skiIdSet,char *_genAttId,double _angVal,\
int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager,list<Point> _endListPt)\
:MonsterBase(_mapId,_typeId,_nickName,_identity,_type,_kind,_experience,\
_cdTime,_lifeUpperVal,_lifeVal,_magicUpperVal,_magicVal,_getHrtSud,\
_outHrt,_inHrt, _outAttVal,_inAttVal,_outDefVal,_inDefVal,_defSumVal,\
_hit,_crit,_voids,_tenacity,_moveRange,_hatRange,_attRange,\
_failGoodsless,_failGoodsmost,_hatVal,_gold,_failId,_pt,_rank,_speed,\
_fiveEleInt,_fiveHurt,_fiveRank,_forGo,_expTme,_monyTme,_stage,_photoId,\
skiIdSet,_genAttId,_angVal,_ownerAttriType,_ownerAttri,_attackRatio,_isInnerAttack,_lveCtnMager)
{
  flgEnd = false;
  
  endListPt = _endListPt;  
  
  runDurTme = 50;
  
  runCtn = 0;
	
  if(endListPt.empty())
  {
	cout<<"endListPt it is empty:"<<endl;
  }
  
  isRun = false;
  
  /*��������*/
  // lifeUpperVal = 100000;
	
  // lifeVal = lifeUpperVal;

}

/*
    ������˼���ص�������getRdPt
    ������
    ����ֵ����
*/      

void MonsterEscape::response(void)
{
	StyObj obj(identity,MONSTER_STYLE_TYPE);	
	vector<string> herId;	
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
	
	/*�ж��Ƿ���������*/
	if(!isRun)
	{
		if(istimeRun())
		{
			goEscape();
		}
	}
	
	/*����ܵ��յ�*/
	if(endFinPt == logic_pt)
	{
		isRun = false;
	}
	
	
}

/*���һ���Ӵܵ�*/
void MonsterEscape::randEscapePt(void)
{
	int _indexPt;
	list<Point>::iterator indexPt_it; 
	indexPt_it = endListPt.begin();
	 _indexPt = rand() % endListPt.size();
	advance(indexPt_it,_indexPt);	
	endFinPt = *indexPt_it;
	
	if(endFinPt == pt)                                                         
	{
		endFinPt = born_pt;
	}
	endFinPt = MapExchangeLogical(endFinPt);
	endFinPt._y += map_now->getBaseDigst();

}



/*���һ���Ӵܵ�*/
void MonsterEscape::getEscapePt(void)
{
	if(map_now == NULL)
	{
		return;
	}
	map_now->randEscapePt(endFinPt);
	endFinPt = MapExchangeLogical(endFinPt);
	endFinPt._y += map_now->getBaseDigst();
	
	endFinPt._x = 162;
	endFinPt._y = 83;
	
	cout<<"endPt._x:"<<endFinPt._x<<endl;
	cout<<"endPt._y:"<<endFinPt._y<<endl;

}

/*�Ӵ�*/
void MonsterEscape::goEscape(void)
{
	stopMove();
	getEscapePt();
	// randEscapePt();
	findAttWay(endFinPt,false);	
}
			

/* �޸ĵ�ǰ����ֵ*/
void MonsterEscape::setLifeVal(int _lifeVal)
{
    lifeVal = _lifeVal;
}
	
	

/* 
    �����������ȵ��ü̳е�����������֮�����ͷ�������е���Դ
*/
MonsterEscape::~MonsterEscape(void)
{
}

MonsterBase* MonsterEscape::copyMon(char *_mapId)
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
	newMon = new MonsterEscape(_mapId,typeId,nickName,newIntId,type,kind,experience,\
	cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
	outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,\
	tenacity,walk_ranage, hatRge,attack_range,failGoodsLess,failGoodsMost,hatVal,gold,\
	failList,pt,rank,speed,fiveEleInt,fiveHurt,fiveEleRank,forGo,expTme,monyTme,\
	stage,photoId,skiIdSet,genAttId,angVal,ownerAttriType,ownerAttri,attackRatio,isInnerAttack,lveCtnMager,endListPt);
	newMon->setIsCallType(isCallType);
	return newMon;
}

/*������������*/
void MonsterEscape::die(bool flgInit)
{
	MonsterBase::die(flgInit);
	isRun = false;
}	

/* ������id��������ӣ�û�������*/
void MonsterEscape::InpushEnmityValues(HatVal &hatva)
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
void MonsterEscape::getEnd(void)
{
	if(flgEnd || endListPt.empty())
	{
		return;
	}
	
	endFinPt = endListPt.front();	
	cout<<"endFinPt._x:"<<endFinPt._x<<endl;
	cout<<"endFinPt._y:"<<endFinPt._y<<endl;
    endFinPt = MapExchangeLogical(endFinPt);
    endFinPt._y += map_now->getBaseDigst();
	cout<<"the red mon begin:"<<endl;
	cout<<"logic_pt._x:"<<logic_pt._x<<endl;
	cout<<"logic_pt._y:"<<logic_pt._y<<endl;
	cout<<"endFinPt._x:"<<endFinPt._x<<endl;
	cout<<"endFinPt._y:"<<endFinPt._y<<endl;
	cout<<"the red mon end:"<<endl;
    if(!map_now->judgeLogPtHind(endFinPt))
    {
       cout<<"[chenzhen warning]: it is hinder of this point:"<<identity<<endl;
		flgEnd = false;
		return;
    }
	flgEnd = true;
}  

/*���ù�������*/
void MonsterEscape::initMonsterALL(void)
{
	flgEnd = false;  
	
	MonsterBase::initMonsterALL();
	
	runCtn = 0;
	
	isRun = false;
}



/* ��Ѱ�Լ�һ����Ļ�ϵ�hero�����ǲ����ڳ�޷�Χ��*/
void MonsterEscape::redSchRge(void) 
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
		
		if(myHero == NULL || myHero->getLifeStation() == DEAD ||\
		!myHero->getWalkingFlg() ||	!myHero->getisRedName())
        {
            continue;
        }
		
        // if(myHero == NULL || myHero->getLifeStation() == DEAD || !myHero->getWalkingFlg())
        // {
            // continue;
        // }
        /*Ϊ�˼������������ж�*/
        heroPt = myHero->getLocation();   
		
		// cout<<"heroPt._x:"<<heroPt._x<<endl;
		// cout<<"heroPt._y:"<<heroPt._y<<endl;
		
		// cout<<"hatRge:"<<hatRge<<endl;
        /*�ж��Ƿ��ڳ�޷�Χ��*/		
		/*�������Ե�ǰ���������ΪԲ�ģ���޷�Χ���ĸ�ʽ����*/
		
        if(sqrt(pow(fabs(heroPt._x - pt._x),2)+pow(fabs(heroPt._y - pt._y),2)) < hatRge)
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


/*�Ƿ�����*/
bool MonsterEscape::istimeRun(void)
{
	int runRand;
	
	srand ( time(NULL) );
    runRand = rand()%10;
	
	runCtn++;
	
	if(runCtn >= runDurTme || runRand == runDurTme)
	{
		isRun = true;
		runCtn = 0;
		return true;
	}
	return false;
}
	