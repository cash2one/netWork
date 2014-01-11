#include"bottle.h"
#include"map_inform.h"
#include"hero.h"
#include"otherThingCalBack.h"
#include"dropgoods.h"
extern map<string,Hero*>heroId_to_pHero;
extern struct ev_loop *loops;
Bottle::Bottle(char *_typeId,int _lifeVal,int _hurt,int _brushStyle,double _bloodPre,double _magicPre,char *_name,size_t _dropNum,char* _dropStage,char *_photoId)
{	
	memset(id,'\0',sizeof(id));
	memset(typeId,'\0',sizeof(typeId));
	memset(photoId,'\0',sizeof(photoId));
	memset(name,'\0',sizeof(name));	
	memset(dropStage,'\0',sizeof(dropStage));
	
	strncpy(typeId,_typeId,strlen(_typeId));		
	strncpy(name,_name,strlen(_name));
	strncpy(dropStage,_dropStage,strlen(_dropStage));
	strncpy(photoId,_photoId,strlen(_photoId));
		
	lifeVal = _lifeVal;	
	hurt = _hurt;	
	bruOut = false;
	lifeValUpper = lifeVal;
	brushStyle = _brushStyle;
	bloodPre = _bloodPre;
	magicPre = _magicPre;
	dropNum = _dropNum;
}

/*����ˢ����Ϣ*/
void Bottle::formBornMsg(void)
{
	memset(bornMsg,'\0',IN_VIEW_LENGTH + 1);
	
	sprintf(bornMsg + strlen(bornMsg),"%d%s%d%s%d%s%s%s%s",2,",",9,",",\
			TYPEBOTTLE,",",id,",",name);
	
	sprintf(bornMsg + strlen(bornMsg),"%s%d%s%d%s%d%s%s",",",\
			pt._x,",",pt._y,",",lifeVal,",",photoId);
}

/*���id*/
char* Bottle::getId(void)
{
	return id;
}

/*����������Ϣ*/
void Bottle::formOutMsg(void)
{
	memset(outMsg,'\0',OUT_VIEW_LENGTH + 1);
	
	sprintf(outMsg + strlen(outMsg),"%d%s%d%s%s%s%d",2,",",5,",",id,",",1);
}

/*������ʵ��ָ��*/
Hero* Bottle::getHero(char *heroId)
{
    map<string,Hero*>::iterator hero_it;
    hero_it = heroId_to_pHero.find(heroId);
    if(hero_it == heroId_to_pHero.end())
    {
        return	NULL;
    }
    return hero_it->second;
}

/*���õ�ͼʵ��ָ��*/
void Bottle::setMap(Map_Inform *_map_now)
{
	if(_map_now != NULL)
	{
		map_now = _map_now;
	}
	
	if(map_now != NULL)
	{
		logicPt = MapExchangeLogical(pt);
		logicPt._y += map_now->getBaseDigst();
	}
}

/*����߼������*/
Point Bottle::getLogicPt(void)
{
    return logicPt;
}

/*����ƿ��*/
Bottle* Bottle::copyBottle(char *_mapId)
{	
	char newIntId[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       //�µ�ͼid;
	Bottle* newBottle;
	
	/* ׷�ӵ�ͼid��Ϊ�˱�֤��������id��Ψһ��*/	
	strncpy(newIntId,_mapId,strlen(_mapId));
	strncat(newIntId,"_",strlen("_"));	
	strncat(newIntId,id,strlen(id));
		
	
	newBottle = new Bottle(typeId,lifeVal,hurt,brushStyle,bloodPre,magicPre,name,dropNum,dropStage,photoId);	
	newBottle->setPiexPt(pt);
	newBottle->setInstId(newIntId);	
	return newBottle;
}

/*����ƿ��<���غ������ڶ�ȡ��ͼ�����ļ�������>*/
Bottle* Bottle::copyBottle(Point _pt)
{
	char _id[MONSTER_MID_LENGTH + 1] = {'\0'};	
	Bottle* newBottle;	
	newBottle = new Bottle(typeId,lifeVal,hurt,brushStyle,bloodPre,magicPre,name,dropNum,dropStage,photoId);
	
	strncpy(_id,typeId,strlen(typeId));
	strncat(_id,"_",strlen("_"));	
	
	count++;
	appendNum(_id,count,4);		
	
	newBottle->setPiexPt(_pt);
	newBottle->setInstId(_id);
	
	return newBottle;
}

/*������������*/
void Bottle::setPiexPt(Point _pt)
{
	pt = _pt;
}

/*���ժȡ��Ʒid*/
char* Bottle::getBottleId(void)
{
	return id;
}

/*����ʵ��id*/
void Bottle::setInstId(char *_id)
{
	if(_id == NULL)
	{
		return;
	}
	memset(id,'\0',sizeof(id));
	strncpy(id,_id,strlen(_id));
}

/*ˢ��ƿ��*/
void Bottle::brushMsg(void)
{
	StyObj obj(id,BOTTLE_STYLE_TYPE);
	Nbox *box;
	
	if(bruOut)
	{
		return;		
	}
	
	formBornMsg();
	
	formOutMsg();                  
	                   
	box = map_now->getBox();	
	
	if(box == NULL)
	{
		return;
	}
	
	map_now->insertID(obj);
	
	box->getStaInSrcVec(obj);	
	
	box->sentBoxMsg(bornMsg);
	
	bruOut = true;

}

/*ƿ�޴ӵ�ͼ����*/
void Bottle::disperMsg(void)
{
	StyObj obj(id,BOTTLE_STYLE_TYPE);
	Nbox *box;
	
	formOutMsg();                  
	                   
	box = map_now->getBox();	
	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(outMsg);
	
	map_now->deleteID(obj);
	
	lifeVal = lifeValUpper;
	
	bruOut = false;
	
}

Bottle::~Bottle(void)
{	
	map_now = NULL;	
	
	memset(bornMsg,'\0',IN_VIEW_LENGTH + 1);
	
	memset(outMsg,'\0',OUT_VIEW_LENGTH + 1);
	
	ev_timer_stop(loops,&think_timer);
}

/*���ƿ�޵�����ֵ*/
int Bottle::getLifeVal(void)
{
	return lifeVal;
}

/*����ƿ�޵�����ֵ*/
void Bottle::setLifeVal(int _lifeVal)
{
	if(_lifeVal < 0)
	{
		cout<<"the bottle blood is less 0:"<<id<<endl;
		return;
	}
	lifeVal = _lifeVal;
}

/*����ƿ�޵�����ֵ*/
void Bottle::beAttack(const char* attackId)
{
	if(hurt >= lifeVal)
	{
		lifeVal = 0;
		
		if(attackId && strlen(dropStage) > 0 && dropNum >= 1)
		{		
			// cout<<""
			saveInPick(const_cast<char*>(attackId),map_now,dropNum,dropStage,pt,0);
		}
		
		ev_timer_stop(loops,&think_timer);
		
		ext_ev_timer_init(&think_timer,botThkCalBack,2,0, this);

		ev_timer_start(loops,&think_timer);

	}
	else
	{
		lifeVal -= hurt;
	}
}

/*���ƿ���˺�ֵ*/
int Bottle::getHurt(void)
{
	return hurt;
}

/*���������Ϣ*/
char* Bottle::getBronMsg(void)
{
	return bornMsg;
}

/*���������Ϣ*/
char* Bottle::getOutMsg(void)
{
	return outMsg;
}


/*�����������*/
Point Bottle::getPiexPt(void)
{
	return pt;
}

/*�Ѵ�������־*/
bool Bottle::dieOutFlg(void)
{
	if(bruOut && lifeVal == 0)
	{
		return true;
	}
	return false;
}

/*�Ѵ�������־*/
bool Bottle::aliveFlg(void)
{
	return !bruOut;
}

/*ȡ��ͼʵ��ָ��*/
Map_Inform* Bottle::getMap(void)
{
	return map_now;
}

/*ȡ����id*/
char* Bottle::getTypeId(void)
{
	return typeId;
}

/*���ˢ��ģʽֵ*/
int Bottle::getBrushStyle(void)
{
	return brushStyle;
}

/*����ƿ������*/
void Bottle::initBot(void)
{
	ev_timer_stop(loops,&think_timer);	
	
	lifeVal = lifeValUpper;
	
	bruOut = false;
}

//Ѫֵ����
int Bottle::getLifeUpperVal()
{
	return lifeValUpper;
}

/*�����߻�Ѫ�İٷֱ�*/
double Bottle::getBloodPre(void)
{
	return bloodPre;
}

/*�����߻����İٷֱ�*/
double Bottle::getMagicPre(void)
{
	return magicPre;
}

const char* Bottle::getDropStage(void) const
{
	return dropStage;
}
	
	
		
		