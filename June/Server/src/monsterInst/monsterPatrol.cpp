#include"monsterPatrol.h"
#include<math.h>
#include "instancing_manage.h"
#include <assert.h>
extern int Rd;         
extern Instancing_manage *Inst_MNG;
extern map<string, Hero*> heroId_to_pHero;

MonsterPatrol::MonsterPatrol(char *_mapId,char *_typeId,char *_nickName,\
char *_identity,char *_type,char *_kind,int _experience,double _cdTime,\
int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,\
int _getHrtSud,int _outHrt,int _inHrt,int _outAttVal, int _inAttVal,\
int _outDefVal, int _inDefVal,int _defSumVal,double _hit,double _crit,\
int _voids,int _tenacity,int _moveRange, int _hatRange,int _attRange,\
int _failGoodsless,int _failGoodsmost,int _hatVal,int _gold,set<string>\
& _failId, Point _pt,int _rank,int _speed,int _fiveEleInt,int _fiveHurt,\
int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,\
vector<string> &skiIdSet,char *_genAttId,double _angVal,int _ownerAttriType,\
char* _ownerAttri,double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager,\
Point logicPt,int _radius):MonsterBase(_mapId,_typeId,_nickName,_identity,_type,_kind,\
_experience,_cdTime,_lifeUpperVal,_lifeVal,_magicUpperVal,_magicVal,_getHrtSud,\
_outHrt,_inHrt, _outAttVal, _inAttVal,_outDefVal,_inDefVal,_defSumVal,_hit,_crit,\
_voids,_tenacity,_moveRange,_hatRange,_attRange,_failGoodsless,_failGoodsmost,\
_hatVal,_gold,_failId,_pt,_rank,_speed,_fiveEleInt,_fiveHurt,_fiveRank,_forGo,\
_expTme,_monyTme,_stage,_photoId,skiIdSet,_genAttId,_angVal,_ownerAttriType,\
_ownerAttri,_attackRatio,_isInnerAttack,_lveCtnMager)
{

    radius = _radius;        //Ѱ·�뾶 

    endFinPt = logicPt;    //Ѱ·�յ�
	
	flgEnd = false;
	
	
}

/*
    ������˼���ص�������response
    ������
    ����ֵ����
*/  
void MonsterPatrol::response(void)
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
//		cout<<"it is playCd time:"<<endl;
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
	
    /*Boss����*/
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
        /*��޷�Χ����*/
        schRge();

        /*�������б�Ϊ��*/
        if(enmityValues.empty())   //�Լ�Ѳ��
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
				
				if(logic_pt == perLstPt)
				{
					Rec = false;
					return;						
				}	
				
				/*������Ѱ·*/
				if(keyPath.empty())
				{
					/*Ѱ�Լ���·*/
					findAttWay(perLstPt);
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
					findSlfWay(endFinPt);	
				}					
			}
			
        }
        else
        {
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
			
			if(perLstPt == logic_pt)
			{
				Rec = false;
			}
			else
			{
				Rec = true;
			}
			
        }
    }
}

/*��ͼ����������*/
MonsterBase* MonsterPatrol::copyMon(char *_mapId)
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

    newMon = new MonsterPatrol(_mapId,typeId,nickName,newIntId,type,kind,experience,\
	cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,outAttVal,\
	inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,walk_ranage,hatRge,\
	attack_range,failGoodsLess,failGoodsMost,hatVal,gold,failList,pt,rank,speed,\
	fiveEleInt,fiveHurt,fiveEleRank,forGo,expTme,monyTme,stage,photoId,skiIdSet,\
	genAttId,angVal,ownerAttriType,ownerAttri,attackRatio,isInnerAttack,lveCtnMager,endFinPt,radius);    
	newMon->setIsCallType(isCallType);
    return newMon;
}

/*��������*/
MonsterPatrol::~MonsterPatrol(void)
{

}

/*���Ѳ���յ�*/
void MonsterPatrol::getEnd(Point _logicPt)
{
	if(flgEnd)
	{
		return;
	}
	endFinPt = born_pt;
	
	endFinPt._x += 50;
	endFinPt._y += 50;
	
    endFinPt = MapExchangeLogical(endFinPt);
    endFinPt._y += map_now->getBaseDigst();
    if(!map_now->judgeLogPtHind(endFinPt))
    {
        //cout<<"it is hinder:"<<endl;
		flgEnd = false;
		return;
    }
	flgEnd = true;
}  

/*������������*/
void MonsterPatrol::die(bool flgInit)
{

    MonsterBase::die(flgInit);
}   

/*���ù�������*/
void MonsterPatrol::initMonsterALL(void)
{
	
	flgEnd = false;
	
	MonsterBase::initMonsterALL();
}







 
