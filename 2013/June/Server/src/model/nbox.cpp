/********************************************************************

    created:   2012/2/24  
	
	�ļ�����	nbox.cpp

    author:     cookie 

    purpose:  �Ź����ʵ���ļ���
			  ���ڽ�����Ӧ��ͼ�߼���ߵľŹ��񣬲����Ź����set�����У�ID�б������ɾ��ID
	
	�޸ģ�	2012.2.27��Tory��
	
	�޸ģ�  2012.5.15 ��Cookie�����캯��
	��д��  2012.08.23��chenzhen�������ĵ�
*********************************************************************/

#include"nbox.h"
#include"map_inform.h"
#include"game_move.h"
#include"takeGoods.h"
extern map<string, Hero*> heroId_to_pHero;

Nbox::Nbox(Map_Inform *_map_now,Point _scrSizePiexPt)
{
	map_now = _map_now;
	
	/*��Ļ��С*/
	scrSizePiexPt = _scrSizePiexPt;
	
	Point mapSize(map_now->getWidth(),map_now->getHeight());	
	
	/*�����Ļ������ݳ���*/
	MapScrPtSize = mapLogToSrcPtv(mapSize,1);	
	
	/*��ʼ����Ļ����*/
	initScrVec();
	
	clearSet();
	
}
Nbox::~Nbox()
{
	map_now = NULL;
}

/*���Ը����Ÿ��������*/
void Nbox::testAllkindScr(void)
{
	cout<<"test the all kind  sreen in box begin:"<<endl;
	
	cout<<"test the newSrcPtSet sreen in box begin:"<<endl;
	testKindSet(newSrcPtSet);
	cout<<"test the newSrcPtSet sreen in box end:"<<endl;
	
	cout<<"test the oldSrcPtSet sreen in box begin:"<<endl;
	testKindSet(oldSrcPtSet);
	cout<<"test the oldSrcPtSet sreen in box end:"<<endl;
	
	cout<<"test the sameSrcPtSet sreen in box begin:"<<endl;
	testKindSet(sameSrcPtSet);
	cout<<"test the sameSrcPtSet sreen in box end:"<<endl;
	
	cout<<"test the diffOldSrcPtSet sreen in box begin:"<<endl;
	testKindSet(diffOldSrcPtSet);
	cout<<"test the diffOldSrcPtSet sreen in box end:"<<endl;
	
	cout<<"test the diffNewSrcPtSet sreen in box begin:"<<endl;
	testKindSet(diffNewSrcPtSet);
	cout<<"test the diffNewSrcPtSet sreen in box end:"<<endl;
	
	
	cout<<"test nine sreen in box end:"<<endl;
}

/*���Ը����Ÿ��������*/
void Nbox::testKindSet(set<Point> &SrcPtSet)
{
	set<Point>::iterator srcPt_it;
	Point srcPT;
	for(srcPt_it = SrcPtSet.begin();srcPt_it != SrcPtSet.end();srcPt_it++)
	{
	
		srcPT = *srcPt_it;
		
		cout<<"test the srcPt._x:"<<srcPT._x<<" srcPt._y:"<<srcPT._y<<" begin:"<<endl;
		
		testMapSet(herOrMonIdVec[srcPT._x][srcPT._y]);
		
		cout<<"test the srcPt._x:"<<srcPT._x<<" srcPt._y:"<<srcPT._y<<" end:"<<endl;
	}
}

/*���Ը����Ÿ��������*/
void Nbox::testMapSet(OneScreen &idSet)
{
	ScreenPrint(idSet);
}


/*��ʼ����Ļ����*/
void Nbox::initScrVec(void)
{
	int width,heigth;
	
	vector <OneScreen> widthVec; 
	
	OneScreen screen;		

	for(width = 0;width < MapScrPtSize._y;width++)
	{				
		widthVec.push_back(screen);	 		
	}
	
	for(heigth = 0;heigth < MapScrPtSize._x;heigth++)
	{	
		herOrMonIdVec.push_back(widthVec);			
	}
}

/*��þŹ�����ʵ������������*/
bool Nbox::getObjpT(StyObj &obj,Point &piexPt)
{
	if(map_now == NULL)
	{
		return false;
	}
	return map_now->getPtNow(obj,piexPt);
}


/*�ж���Ļ�����Ƿ�Ϸ�*/
bool Nbox::judgeSCrIndex(Point &srcPt)
{
	if(srcPt._x >= MapScrPtSize._x || srcPt._x < 0)
	{
		return false;
	}
	if(srcPt._y >= MapScrPtSize._y || srcPt._y < 0)
	{
		return false;
	}
	return true;
}

/*�������ľŹ���srcPtΪ��Ļ���꣩*/
void Nbox::getStaInSrcVec(Point &srcPt,set<Point> &SrcPtSet)
{
	Point tempPoint;
	for (int i = -1; i < 2; i++)
	{
		tempPoint._y = srcPt._y + i;
		for (int j = -1; j < 2; j++)
		{
			tempPoint._x = srcPt._x + j;
			if(judgeSCrIndex(tempPoint))
			{
				SrcPtSet.insert(tempPoint);
			}
		}
	}
}

/*�����¾ɾŹ���Ľ����Ľ��������ƶ���Ϣ*/
void Nbox::ctnSmeValSet(void)
{
	set<Point>::iterator idNewSet_it;
	set<Point>::iterator idOldSet_it;
	sameSrcPtSet.clear();
	{
		std::set<Point> tmp;   
		sameSrcPtSet.swap(tmp);
	}
	// cout<<"test in ctn begin:"<<endl;
		
	// cout<<"test the newSrcPtSet sreen in box begin:"<<endl;
	// testKindSet(newSrcPtSet);
	// cout<<"test the newSrcPtSet sreen in box end:"<<endl;
	
	// cout<<"test the oldSrcPtSet sreen in box begin:"<<endl;
	// testKindSet(oldSrcPtSet);
	// cout<<"test the oldSrcPtSet sreen in box end:"<<endl;
	
	for(idNewSet_it = newSrcPtSet.begin();idNewSet_it != newSrcPtSet.end();idNewSet_it++)
	{
		idOldSet_it = oldSrcPtSet.find(*idNewSet_it);
		if(idOldSet_it != oldSrcPtSet.end())
		{
			sameSrcPtSet.insert(*idNewSet_it);
			// sameSrcPtSet[idNewSet_it->first] = idNewSet_it->second;
		}
	}
	
	// cout<<"test the sameSrcPtSet sreen in box begin:"<<endl;
	// testKindSet(sameSrcPtSet);
	// cout<<"test the sameSrcPtSet sreen in box end:"<<endl;
	
	// cout<<"test in ctn end:"<<endl;
}

/*�������¾Ź������¾ɾŹ���Ľ����Ĳ���ȷ���½��Ϣ���ٷ��ƶ���Ϣ*/
void Nbox::ctnDiffNewValSet(void)
{
	set<Point>::iterator idNewSet_it;
	set<Point>::iterator idSmeValSet_it;
	diffNewSrcPtSet.clear();
	{
		std::set<Point> tmp;   
		diffNewSrcPtSet.swap(tmp);
	}

	for(idNewSet_it = newSrcPtSet.begin();idNewSet_it != newSrcPtSet.end();idNewSet_it++)
	{
		idSmeValSet_it = sameSrcPtSet.find(*idNewSet_it);
		if(idSmeValSet_it == sameSrcPtSet.end())
		{
			diffNewSrcPtSet.insert(*idNewSet_it);
			// diffNewSrcPtSet[idNewSet_it->first] = idNewSet_it->second;
		}
	}
}

/*�����þɾŹ������¾ɾŹ���Ľ����Ĳ����������Ϣ*/
void Nbox::ctnDiffOldValSet(void)
{
	set<Point>::iterator idOldSet_it;
	set<Point>::iterator idSmeValSet_it;
	diffOldSrcPtSet.clear();
	{
		std::set<Point> tmp;   
		diffOldSrcPtSet.swap(tmp);
	}
	// cout<<"test in ctn begin:"<<endl;
		
	// cout<<"test the oldSrcPtSet sreen in box begin:"<<endl;
	// testKindSet(oldSrcPtSet);
	// cout<<"test the oldSrcPtSet sreen in box end:"<<endl;
	
	// cout<<"test the sameSrcPtSet sreen in box begin:"<<endl;
	// testKindSet(sameSrcPtSet);
	// cout<<"test the sameSrcPtSet sreen in box end:"<<endl;
	
	for(idOldSet_it = oldSrcPtSet.begin();idOldSet_it != oldSrcPtSet.end();idOldSet_it++)
	{
		idSmeValSet_it = sameSrcPtSet.find(*idOldSet_it);
		if(idSmeValSet_it == sameSrcPtSet.end())
		{
			// diffOldSrcPtSet.insert(pair<string,Point>(idOldSet_it->first,idOldSet_it->second));
			diffOldSrcPtSet.insert(*idOldSet_it);
		}
	}
	// cout<<"test the diffOldSrcPtSet sreen in box begin:"<<endl;
	// testKindSet(diffOldSrcPtSet);
	// cout<<"test the diffOldSrcPtSet sreen in box end:"<<endl;
	
	// cout<<"test in ctn end:"<<endl;
}

/*�жϴ˽�ɫ���Ƴ���ǰ��Ļ,�Ƴ�������false��ľ����true*/
bool Nbox::judgeOutSrc(Point &oldSrcPt,Point &newSrcPt)
{
	return oldSrcPt == newSrcPt;
}



/*�ƶ�������Ҳ���ԣ����ľŹ�������*/
bool Nbox::MovePt(StyObj &obj,Point &newPt)
{	
	Point oldPt;
	Point oldSrcPt,newSrcPt;
	
	clearSet();
	/*��ý�ɫ���߹�����߼�����*/	
	if(!getObjpT(obj,oldPt))
	{
		/*û���ҵ�heroʵ��ָ��*/
		cout<<"can not find the objId:"<<obj.objId<<endl;
		cout<<"can not find the objId of the type:"<<obj.type<<endl;
		return false;
	}
	/*�Ѿɵ�ͼ�߼���ת������Ļ�����*/
	oldSrcPt = mapLogToSrcPtv(oldPt);
	
	/*���µ�ͼ�߼���ת������Ļ�����*/
	newSrcPt = mapLogToSrcPtv(newPt);
	
	/*�ж���Ļ�����Ƿ�Ϸ�*/
	if(!judgeSCrIndex(oldSrcPt) || !judgeSCrIndex(newSrcPt))
	{
		/*�߼�����Ƿ�*/
		cout<<"objId of piexPt is illeay:"<<obj.objId<<endl;	
		cout<<"objId of piexPt is illeay of the type:"<<obj.type<<endl;
		return false;
	}
	// cout<<"[BisonShow] oldSrcPt["<<oldSrcPt._x<<","<<oldSrcPt._y<<"] newSrcPt["<<newSrcPt._x<<","<<newSrcPt._y<<"]"<<endl;
	/*���ľ���Ƴ���ǰ��Ļ,��ֻ�û�õ�ǰ�Ź��񣬷����ƶ���Ϣ*/
	if(judgeOutSrc(oldSrcPt,newSrcPt))
	{
		/*����¾Ź�������*/
		getStaInSrcVec(newSrcPt,newSrcPtSet);				
		return true;
	}
	
	/*������Ƴ���ǰ��Ļ,���û�õ�ǰ�Ź���ԭ���Ź����Լ����ǵĽ������Ͳ�������Ͳ�ͬ��Ϣ*/
	
	/*��þɾŹ�������*/
	getStaInSrcVec(oldSrcPt,oldSrcPtSet);

	/*����¾Ź�������*/
	getStaInSrcVec(newSrcPt,newSrcPtSet);
	
	/*�����¾ɾŹ���Ľ����Ľ��������ƶ���Ϣ*/
	ctnSmeValSet();
	
	/*�������¾Ź������¾ɾŹ���Ľ����Ĳ���ȷ���½��Ϣ���ٷ��ƶ���Ϣ*/
	ctnDiffNewValSet();
	
	/*�����þɾŹ������¾ɾŹ���Ľ����Ĳ����������Ϣ*/
	ctnDiffOldValSet();
	
	
	/*�Ӿ�����ɾ��*/
	deleteInOldSrc(oldSrcPt,obj);
	
	/*�������в���*/
	inputInOldSrc(newSrcPt,obj);
	
	return true;
}

#if 0
/*��ɫ��������*/
void Nbox::heroPollTme(Hero *hero,char *moveMsg,bool isNewRod)
{	
	bool flgChg;
	string logStr,downStr;
	char *heroId;
	if(hero == NULL || moveMsg == NULL || strlen(moveMsg) == 0)
	{
		return;
	}
	heroId = hero->getIdentity();
	// send_msg(hero->getFd(), moveMsg); 
	flgChg = false;
	/*�ж��¾ɾŹ����Ƿ��غ�*/
	if(!oldSrcPtSet.empty() && !newSrcPtSet.empty())
	{
		flgChg = true;
	}
		
	/*�µļ�ȥ�¾ɵĽ����ļ���*/
	if(!diffNewSrcPtSet.empty())
	{
		logStr = CreateMessage::come_into_view(hero);
		sentBoxViewMsg(diffNewSrcPtSet,const_cast<char *>(logStr.c_str()),hero,1);
		sentBoxMsg(diffNewSrcPtSet,moveMsg,heroId);
	}	
		
	/*�ɵļ�ȥ�¾ɵĽ����ļ���*/
	if(!diffOldSrcPtSet.empty())
	{
		downStr = CreateMessage::out_of_view(hero);
		// cout<<"test in time poll begin:"<<endl;
		// testKindSet(diffOldSrcPtSet);	
		// cout<<"test in time poll end:"<<endl;
		sentBoxViewMsg(diffOldSrcPtSet,const_cast<char *>(downStr.c_str()),hero,2);
	}		
	/*�¾��غ�����µļ���*/
	if(flgChg)
	{
		/*�Ƿ�Ϊ��·��*/
		if(isNewRod)
		{
			sentBoxMsg(newSrcPtSet,moveMsg,heroId);
		}
	}	
		
	/*�¾ɵĽ����ļ���*/
	if(!sameSrcPtSet.empty())
	{
		if(isNewRod)
		{
			sentBoxMsg(sameSrcPtSet,moveMsg,heroId);
		}
	}
}
#endif

/*��ɫ��������*/
void Nbox::heroPollTme(Hero *hero,char *moveMsg,bool isNewRod)
{
	
	bool flgChg;
	string logStr,downStr;
	char *heroId;
	if(hero == NULL || moveMsg == NULL || strlen(moveMsg) == 0)
	{
		return;
	}
	heroId = hero->getIdentity();
	
	flgChg = false;
	/*�ж��¾ɾŹ����Ƿ��غ�*/
	if(!oldSrcPtSet.empty())
	{
		flgChg = true;
	}
	
	if (isNewRod)
	{	
		send_msg(hero->getFd(), moveMsg); 
	}
	if (flgChg)
	{
		/*�µļ�ȥ�¾ɵĽ����ļ���*/
		if(!diffNewSrcPtSet.empty())
		{
			logStr = CreateMessage::come_into_view(hero);
			sentBoxViewMsg(diffNewSrcPtSet,const_cast<char *>(logStr.c_str()),hero,1);
			sentBoxMsg(diffNewSrcPtSet,moveMsg,heroId);
		}	
			
		/*�ɵļ�ȥ�¾ɵĽ����ļ���*/
		if(!diffOldSrcPtSet.empty())
		{
			downStr = CreateMessage::out_of_view(hero);
			// cout<<"test in time poll begin:"<<endl;
			// cout<<"-------------------BisonTest--------------------"<<endl;
			// cout<<"-------------------BisonTest--------------------"<<endl;
			// cout<<"test diffOldSrcPtSet###########"<<endl;
			// testKindSet(diffOldSrcPtSet);	
			// cout<<"test diffOldSrcPtSet###########"<<endl;
			// testKindSet(diffNewSrcPtSet);	
			// cout<<"test diffOldSrcPtSet###########"<<endl;
			// testKindSet(sameSrcPtSet);	
			// cout<<"test diffOldSrcPtSet###########"<<endl;
			// testKindSet(newSrcPtSet);	
			// cout<<"test diffOldSrcPtSet###########"<<endl;
			// testKindSet(oldSrcPtSet);	
			 // cout<<"test in time poll end:"<<endl;
			 // cout<<"-----------------BisonTest----------------------"<<endl;
			 // cout<<"-----------------BisonTest----------------------"<<endl;
			sentBoxViewMsg(diffOldSrcPtSet,const_cast<char *>(downStr.c_str()),hero,2);
		}
	
		/*�¾ɵĽ����ļ���*/
		if(!sameSrcPtSet.empty() && (isNewRod))
		{
			sentBoxMsg(sameSrcPtSet,moveMsg,heroId);
		}
	} else {
		if (isNewRod)
		{	
			sentBoxMsg(newSrcPtSet,moveMsg,heroId);
		}
	}	
	
}

/*�����ƶ�����*/
void Nbox::petMove(Pet *pet,char *moveMsg, bool isNewRoad, char *ownerId)
{		
	char logStr[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	char downStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	bool flgChg;
	
	if(pet == NULL || moveMsg == NULL || strlen(moveMsg) == 0)
	{
		return;
	}
	
	flgChg = false;
	/*�ж��¾ɾŹ����Ƿ��غ�*/
	if(!oldSrcPtSet.empty())
	{
		flgChg = true;
	}
	
	if (flgChg)
	{
		/*�µļ�ȥ�¾ɵĽ����ļ���*/
		if(!diffNewSrcPtSet.empty())
		{
			pet->msg_active(logStr,sizeof(logStr));
			sentBoxMsg(diffNewSrcPtSet,logStr);
			sentBoxMsg(diffNewSrcPtSet, moveMsg, ownerId);
		}	
			
		/*�ɵļ�ȥ�¾ɵĽ����ļ���*/
		if(!diffOldSrcPtSet.empty())
		{
			pet->msg_downline(downStr,sizeof(downStr));
			sentBoxMsg(diffOldSrcPtSet, downStr, ownerId);
			
		}
		/*�¾ɵĽ����ļ���*/
		if(!sameSrcPtSet.empty() && isNewRoad)
		{		
			sentBoxMsg(sameSrcPtSet, moveMsg, ownerId);		
		}
	}
	else
	{
		if (isNewRoad)
		{
			sentBoxMsg(newSrcPtSet, moveMsg, ownerId);
		}
	}
	
}


/*���ƶ�����*/
void Nbox::wagonMove(Wagon *wagon, char *moveMsg, bool isNewRoad, char *ownerId)
{	
	bool flgChg;
	string logStr,downStr;
	
	if(wagon == NULL || moveMsg == NULL || strlen(moveMsg) == 0)
	{
		cout<<"111111111111111111111111111111111"<<endl;
		return;
	}
	Hero *hero = wagon->getOwner();
	if ( hero == NULL)
	{
	}
	flgChg = false;
	/*�ж��¾ɾŹ����Ƿ��غ�*/
	if(!oldSrcPtSet.empty())
	{
		flgChg = true;
	}
	if (flgChg)
	{	
		/*�µļ�ȥ�¾ɵĽ����ļ���*/
		if(!diffNewSrcPtSet.empty())
		{
			wagon->formBornMsg();
			logStr = wagon->getOnlineMsg();
			sentBoxMsg(diffNewSrcPtSet,const_cast<char *>(logStr.c_str()));
			sentBoxMsg(diffNewSrcPtSet,moveMsg,ownerId);
		}	
			
		/*�ɵļ�ȥ�¾ɵĽ����ļ���*/
		if(!diffOldSrcPtSet.empty())
		{
			wagon->formOutMsg();
			downStr = wagon->getOfflineMsg();
			sentBoxMsg(diffOldSrcPtSet,const_cast<char *>(downStr.c_str()),ownerId);
			
		}
			
		/*�¾ɵĽ����ļ���*/
		if(!sameSrcPtSet.empty() && isNewRoad)
		{		
			sentBoxMsg(sameSrcPtSet,moveMsg,ownerId);		
		}
	}
	else if (isNewRoad)
	{		
		sentBoxMsg(newSrcPtSet,moveMsg,ownerId);	
	}	
		
}

/*�����ƶ�����*/
void Nbox::monsterMove(MonsterBase *monster,char *moveMsg, bool isNewRod)
{	
	bool flgChg;
	string logStr,downStr;
	// if(strcmp(monster->getIdentity(),"ectype_map_028_0_004_0_0000_MPwhcl_pt_101_2") == 0)
	{
		// cout<<"moveMsg:"<<moveMsg<<endl;
		// cout<<"test the diffOldSrcPtSet sreen in box begin:"<<endl;
		// testAllkindScr();
		// testKindSet(diffOldSrcPtSet);
		// cout<<"test the diffOldSrcPtSet sreen in box end:"<<endl;
	}
	
	// if(monster == NULL || moveMsg == NULL || strlen(moveMsg) == 0)
	// {
		// return;
	// }
	
	if(monster == NULL)
	{
		return;
	}
	
	flgChg = true;
	/*�ж��¾ɾŹ����Ƿ��غ�*/
	if(oldSrcPtSet.empty() && !newSrcPtSet.empty())
	{
		flgChg = false;
	}
	
	if (flgChg)
	{
		/*�µļ�ȥ�¾ɵĽ����ļ���*/
		if(!diffNewSrcPtSet.empty())
		{
			monster->formBshMsg();		
			logStr = monster->getBshMsg();
			sentBoxMsg(diffNewSrcPtSet,const_cast<char *>(logStr.c_str()));
			sentBoxMsg(diffNewSrcPtSet,moveMsg);
		}	
			
		/*�ɵļ�ȥ�¾ɵĽ����ļ���*/
		if(!diffOldSrcPtSet.empty())
		{
			monster->formOutMsg();
			downStr = monster->getOutMsg();
			sentBoxMsg(diffOldSrcPtSet,const_cast<char *>(downStr.c_str()));
			
		}
		if(!sameSrcPtSet.empty())
		{	if (isNewRod)
			{
				sentBoxMsg(sameSrcPtSet,moveMsg);
			}
		}
	} else {
		if (isNewRod)
		{
			sentBoxMsg(newSrcPtSet,moveMsg);
		}
	}
}


/*���ƶ��ƶ�����*/
void Nbox::takeGoodsMove(TakeGoods *takeGoods,char *moveMsg, bool isNewRod)
{	
	bool flgChg;
	string logStr,downStr;
	
	if(takeGoods == NULL || moveMsg == NULL || strlen(moveMsg) == 0)
	{
		return;
	}
	
	flgChg = true;
	/*�ж��¾ɾŹ����Ƿ��غ�*/
	if(oldSrcPtSet.empty() && !newSrcPtSet.empty())
	{
		flgChg = false;
	}
	
	if (flgChg)
	{
		/*�µļ�ȥ�¾ɵĽ����ļ���*/
		if(!diffNewSrcPtSet.empty())
		{
			takeGoods->formBornMsg();		
			logStr = takeGoods->getBronMsg();
			sentBoxMsg(diffNewSrcPtSet,const_cast<char *>(logStr.c_str()));
			sentBoxMsg(diffNewSrcPtSet,moveMsg);
		}	
			
		/*�ɵļ�ȥ�¾ɵĽ����ļ���*/
		if(!diffOldSrcPtSet.empty())
		{
			takeGoods->formOutMsg();
			downStr = takeGoods->getOutMsg();
			sentBoxMsg(diffOldSrcPtSet,const_cast<char *>(downStr.c_str()));
			
		}
		if(!sameSrcPtSet.empty())
		{	if (isNewRod)
			{
				sentBoxMsg(sameSrcPtSet,moveMsg);
			}
		}
	} 
	else 
	{
		if (isNewRod)
		{
			sentBoxMsg(newSrcPtSet,moveMsg);
		}
	}
	
}



/*��װ����Ϣ���ͺ������ԾŹ�����*/
void Nbox::sentBoxMsg(set<Point> &SrcPtSet,char *msg,char *heroId)
{
	set<Point>::iterator newSet_it;
	
	if(SrcPtSet.empty() || msg == NULL || strlen(msg) == 0)
	{
		return;
	}
	
	Point srcPT;
	for(newSet_it = SrcPtSet.begin();newSet_it != SrcPtSet.end();newSet_it++)
	{
		srcPT = *newSet_it;
		SendMsgClass::sentBoxMsg(herOrMonIdVec[srcPT._x][srcPT._y].heroSet,msg,heroId);
	}
}

/*��װ����Ϣ���ͺ������ԾŹ�����*/
void Nbox::sentBoxMsg(char *msg,char *heroId)
{
	set<Point>::iterator newSet_it;	
	
	if(newSrcPtSet.empty() || msg == NULL || strlen(msg) == 0)
	{
		return;
	}
	
	Point srcPT;
	for(newSet_it = newSrcPtSet.begin();newSet_it != newSrcPtSet.end();newSet_it++)
	{
		srcPT = *newSet_it;
		SendMsgClass::sentBoxMsg(herOrMonIdVec[srcPT._x][srcPT._y].heroSet,msg,heroId);
	}
}
		
	
/*��װ����Ϣ���ͺ������ԾŹ�����,Ϊ�໥������,��Ҫ������ҵ���Ϣ����*/
void Nbox::sentBoxViewMsg(set<Point> &SrcPtSet,char *msg,Hero *myHero,int style)
{
	set<Point>::iterator newSet_it;	
	Point srcPT;
	
	if(SrcPtSet.empty() || msg == NULL || strlen(msg) == 0)
	{
		return;
	}
	
	for(newSet_it = SrcPtSet.begin(); newSet_it != SrcPtSet.end();newSet_it++)
	{
		srcPT = *newSet_it;
		SendMsgClass::sentBoxViewMsg(herOrMonIdVec[srcPT._x][srcPT._y],msg,map_now,myHero,style);
	}
}


/*�ӾɾŹ�������ɾ��,���ߺ��е�ͼʱ���Ż��ⲿ����*/
bool Nbox::deleteInOldSrc(StyObj &obj)
{
	Point objPt;
	Point srcPt;
	
	/*��ý�ɫ���߹������������*/	
	if(!getObjpT(obj,objPt))
	{
		cout<<"can not find the objId:"<<obj.objId<<endl;	
		cout<<"can not find the objId of the type:"<<obj.type<<endl;
		return false;
	}
	/*�Ѿɵ�ͼ���ص�ת������Ļ�����*/
	srcPt = mapLogToSrcPtv(objPt);
	
	/*�ж���Ļ�����Ƿ�Ϸ�*/
	if(!judgeSCrIndex(srcPt))
	{
		cout<<"objId of piexPt is illeay:"<<obj.objId<<endl;
		cout<<"objId of piexPt is illeay of the type:"<<obj.type<<endl;
		return false;
	}
	
	/*ɾ��*/
	bool ret = ScreenDel(herOrMonIdVec[srcPt._x][srcPt._y], obj);
	if (ret == false)
	{
		// cout<<"[BisonWarn] del the obj failed!!!!!!!! obj id is "<<obj.objId<<"obj type is "<<obj.type<<endl;
	}
	return ret;
}

/*����Ź�������,���ߺ��е�ͼʱ���Ż��ⲿ����*/
bool Nbox::inputInOldSrc(StyObj &obj)
{
	Point objPt;
	Point srcPt;
	map<string,StyObj>::iterator oldSet_it;
	
	/*��ý�ɫ���߹������������*/	
	if(!getObjpT(obj,objPt))
	{
		/*û���ҵ�����ʵ��ָ��*/
		cout<<"can not find the objId:"<<obj.objId<<endl;	
		cout<<"can not find the objId of the type:"<<obj.type<<endl;
		return false;
	}
	/*�Ѿɵ�ͼ�߼���ת������Ļ�����*/
	srcPt = mapLogToSrcPtv(objPt);
	
	/*�ж���Ļ�����Ƿ�Ϸ�*/
	if(!judgeSCrIndex(srcPt))
	{
		/*��������Ƿ�*/
		cout<<"objId of piexPt is illeay:"<<obj.objId<<endl;
		cout<<"can not find the objId of the type:"<<obj.type<<endl;
		return false;
	}
//	cout<<"srcPt._x:"<<srcPt._x<<" srcPt._y:"<<srcPt._y<<endl;
	/*����*/
	return ScreenInsert(herOrMonIdVec[srcPt._x][srcPt._y], obj);
}


/*�ӾɾŹ�������ɾ��,���أ����ڲ�����*/
bool Nbox::deleteInOldSrc(Point &srcPt,StyObj &obj)
{
	if(!judgeSCrIndex(srcPt))
	{
		/*��������Ƿ�*/
		cout<<"objId of piexPt is illeay:"<<obj.objId<<endl;
		cout<<"can not find the objId of the type:"<<obj.type<<endl;
		return false;
	}
	/*ɾ��*/
	return ScreenDel(herOrMonIdVec[srcPt._x][srcPt._y], obj);
}

/*����Ź�������,���أ����ڲ�����*/
bool Nbox::inputInOldSrc(Point &srcPt,StyObj &obj)
{
	if(!judgeSCrIndex(srcPt))
	{
		/*��������Ƿ�*/
		cout<<"objId of piexPt is illeay:"<<obj.objId<<endl;
		cout<<"can not find the objId of the type:"<<obj.type<<endl;
		return false;
	}
	return ScreenInsert(herOrMonIdVec[srcPt._x][srcPt._y], obj);
}

/*��ͼ���ص�ת������Ļ����*/
Point Nbox::mapLogToSrcPtv(Point &piexPt,int flg)
{
	Point scrPt;
	if(flg == 1)
	{	
		/*��һ�λ��ֵ�ͼ�Ź���ʱ����*/
		scrPt._x=ceil((1.0 * piexPt._x)/scrSizePiexPt._x);	
		scrPt._y=ceil((1.0 * piexPt._y)/scrSizePiexPt._y);
	}
	else
	{
		/*����ʱ�����*/
		scrPt._x = piexPt._x/scrSizePiexPt._x;	
		scrPt._y = piexPt._y/scrSizePiexPt._y;
	}
		
	return scrPt;
}

/*���ػ�þŹ������ݺ�����ͨ��id*/
void Nbox::getStaInSrcVec(StyObj &obj)
{
	Point oldPt;
	Point oldSrcPt;
	
	clearSet();
	
	/*��ý�ɫ���߹�����߼�����*/	
	if(!getObjpT(obj,oldPt))
	{
		return;
	}
	/*�Ѿɵ�ͼ�߼���ת������Ļ�����*/
	oldSrcPt = mapLogToSrcPtv(oldPt);
	
	/*�ж���Ļ�����Ƿ�Ϸ�*/
	if(!judgeSCrIndex(oldSrcPt))
	{
		return;
	}	
	
	/*����¾Ź�������*/
	getStaInSrcVec(oldSrcPt,newSrcPtSet);	

}	

/*�ж�һ�����Ƿ�Ϸ�������������Ļ����*/
void Nbox::testInSrc(Point &piexPt)
{
	cout<<"test the piexPt._x;"<<piexPt._x<<" piexPt._y:"<<piexPt._y<<" in Src begin :"<<endl;
	Point srcPt;
	srcPt = mapLogToSrcPtv(piexPt);
	cout<<"test the srcPt._x;"<<srcPt._x<<" srcPt._y:"<<srcPt._y<<endl;
	if(!judgeSCrIndex(srcPt))
	{
		cout<<"the logic is illeal:"<<endl;
	}
	cout<<"test the piexPt._x;"<<piexPt._x<<" piexPt._x:"<<piexPt._y<<" in Src end :"<<endl;
}


/*ͨ��piexPtΪ���������þŹ���*/
void Nbox::getNineSrcByLogPt(Point &piexPt)
{
	Point srcPt;
	
	clearSet();	
	
	/*�Ѿɵ�ͼ���ص�ת������Ļ�����*/
	srcPt = mapLogToSrcPtv(piexPt);	
	
	getStaInSrcVec(srcPt,newSrcPtSet);
	
	
}

/*����ͨ���±�����*/
void Nbox::testIndex(Point &srcPt)
{
	cout<<"test begin int srcpt._x:"<<srcPt._x<<" srcpt._x:"<<srcPt._y<<endl;
	if(!judgeSCrIndex(srcPt))
	{
		cout<<"the index is wrong:"<<endl;
	}
	ScreenPrint(herOrMonIdVec[srcPt._x][srcPt._y]);
	cout<<"test end int srcpt._x:"<<srcPt._x<<" srcpt._x:"<<srcPt._y<<endl;
}

/*��վŹ����е�����*/
void Nbox::clearBox(void)
{
	int width,heigth;
	for(width = 0;width < MapScrPtSize._x;width++)
	{		
		for(heigth = 0;heigth < MapScrPtSize._y;heigth++)
		{	
			ScreenClear(herOrMonIdVec[width][heigth]);
		} 		
	}
}


/*�������*/
void Nbox::clearSet(void)
{
	oldSrcPtSet.clear();
	{
		std::set<Point> tmp;   
		oldSrcPtSet.swap(tmp);
	}
	
	newSrcPtSet.clear();
	{
		std::set<Point> tmp;   
		newSrcPtSet.swap(tmp);
	}
	
	sameSrcPtSet.clear();
	{
		std::set<Point> tmp;   
		sameSrcPtSet.swap(tmp);
	}
	
	diffOldSrcPtSet.clear();
	{
		std::set<Point> tmp;   
		diffOldSrcPtSet.swap(tmp);
	}
	
	diffNewSrcPtSet.clear();
	{
		std::set<Point> tmp;   
		diffNewSrcPtSet.swap(tmp);
	}
}

/*��ɫ������˳���Ұ*/
void Nbox::heroEnter(Hero *hero,int style)
{
	string heroMsg;	
	
	// testAllkindScr();
	if(hero == NULL || newSrcPtSet.empty())
	{
		return;
	}
	if(style == 1)
	{
		
		heroMsg = CreateMessage::come_into_view(hero); 
		sentBoxViewMsg(newSrcPtSet,const_cast<char *>(heroMsg.c_str()),hero,1);
	}
	else
	{
		heroMsg = CreateMessage::out_of_view(hero);
		sentBoxViewMsg(newSrcPtSet,const_cast<char *>(heroMsg.c_str()),hero,2);
	}
	 
}

/*��þŹ��������*/
set<Point>& Nbox::getNewSrcPtSet(void)
{
	return newSrcPtSet;
}

/*ͨ������������һ�����ļ���*/
OneScreen& Nbox::getOneSrcMap(Point &piexPt)
{
	Point srcPt;
	// OneScreen emptyMap;
	srcPt = mapLogToSrcPtv(piexPt);	
	if(judgeSCrIndex(srcPt))
	{
		return herOrMonIdVec[srcPt._x][srcPt._y];
	}
	else
	{
		return *((OneScreen*)0);
	}
}


/*ͨ�����������þ�����heroid����*/
void Nbox::getNineSrcHerIdSet(Point &piexPt,set<string> &heroIdSet)
{
	Point srcPt;
	set<Point>SrcPtSet;
	srcPt = mapLogToSrcPtv(piexPt);	
	if(!judgeSCrIndex(srcPt))
	{
		return;
		
	}
	getStaInSrcVec(srcPt,SrcPtSet);
	mapSrcPtToHerIdSet(SrcPtSet,heroIdSet);
}

/*ͨ�����������þ�����heroid����*/
void Nbox::mapSrcPtToHerIdSet(set<Point> &SrcPtSet,set<string> &heroIdSet)
{
	set<Point>::iterator srcPt_it;
	Point srcPT;
	for(srcPt_it = SrcPtSet.begin();srcPt_it != SrcPtSet.end();srcPt_it++)
	{
	
		srcPT = *srcPt_it;
		mapSrcPtToHerIdSet(srcPT,heroIdSet);
	}
}

/*�ռ�һ���������id*/
void Nbox::mapSrcPtToHerIdSet(Point &SrcPt,set<string> &heroIdSet)
{
	set<string>::iterator obj_it;
	if(!judgeSCrIndex(SrcPt) || herOrMonIdVec[SrcPt._x][SrcPt._y].heroSet.empty())
	{
		return;
	}
	for(obj_it = herOrMonIdVec[SrcPt._x][SrcPt._y].heroSet.begin();obj_it !=\
		herOrMonIdVec[SrcPt._x][SrcPt._y].heroSet.end();obj_it++)
	{
		heroIdSet.insert(*obj_it);
	}
}

void Nbox::getObjInRange(Point &srcPt, int distSqr, set<string> &heroIdSet, set<string> &monsterSet)
{
	set<string>::iterator obj_it;
	Point temp;
	if(!judgeSCrIndex(srcPt))
	{
		return;
	}
	if (!herOrMonIdVec[srcPt._x][srcPt._y].heroSet.empty())
	{
		for(obj_it = herOrMonIdVec[srcPt._x][srcPt._y].heroSet.begin();obj_it !=\
		herOrMonIdVec[srcPt._x][srcPt._y].heroSet.end();obj_it++)
		{
			Hero *hero = heroid_to_hero(*obj_it);
			if (hero == NULL)
			{
				continue;
			}
			temp = hero->getLocation();
			if (abs(temp._x - srcPt._x) * (temp._x - srcPt._x)
				+ (temp._y - srcPt._y) * (temp._y - srcPt._y) <= distSqr)
			{
				heroIdSet.insert(*obj_it);
			}
		}
	}
	if (!herOrMonIdVec[srcPt._x][srcPt._y].monsterSet.empty())
	{
		for(obj_it = herOrMonIdVec[srcPt._x][srcPt._y].monsterSet.begin();obj_it !=\
		herOrMonIdVec[srcPt._x][srcPt._y].monsterSet.end();obj_it++)
		{
			MonsterBase *mon;
			mon = map_now->getMonsterObj(*obj_it);
			if (mon == NULL)
			{
				continue;
			}
			temp = mon->getLocation();
			if (abs(temp._x - srcPt._x) * (temp._x - srcPt._x)
				+ (temp._y - srcPt._y) * (temp._y - srcPt._y) <= distSqr)
			{
				monsterSet.insert(*obj_it);
			}
		}
	}
	
}
	






/*��Ļ����ת����string��*/
//string Nbox::ptToStr(Point srcPt)
void Nbox::ptToStr(const Point &srcPt, string& ptStr)
{
	
	ptStr = intTostring(srcPt._x);
	ptStr += intTostring(srcPt._y);
	ptStr.erase(ptStr.begin());
	// cout<<"srcPt._x:"<<srcPt._x<<endl;
	// cout<<"srcPt._y:"<<srcPt._y<<endl;
	// cout<<"success:"<<ptStr<<endl;
}
	

/*ͨ���������귢�;Ź�������*/
void Nbox::sendMsgPiexPt(Point &piexPt,char *msg)
{	
	getNineSrcByLogPt(piexPt);
	// clearSet();
	// getStaInSrcVec(srcPt,newSrcPtSet);
	sentBoxMsg(newSrcPtSet,msg);
	
}

/*��ȫͼɾ��һ��obj*/
bool Nbox::deleteObj(StyObj &obj)
{
	int width,heigth;
	bool result;
	
	for(width = 0;width < MapScrPtSize._x;width++)
	{		
		for(heigth = 0;heigth < MapScrPtSize._y;heigth++)
		{	
			result = deletObjHerVec(herOrMonIdVec[width][heigth],obj);
			if(result)
			{
				return true;
			}
		} 		
	}
	return false;	
}

/*��һ��������ɾ��һ��obj*/
bool Nbox::deletObjHerVec(OneScreen& idSet,StyObj &obj)
{
	return ScreenDel(idSet, obj);
}
	
void Nbox::getNeighbour(Point pixPt, set<Point> &nbSet)
{
	//��Ļ����
	Point stayPt =  mapLogToSrcPtv(pixPt);
	
	//�Լ�Ҳ���Լ����ھӣ����뼯��
	//�ж���Ļ�����Ƿ�Ϸ�
	if (judgeSCrIndex(stayPt))
	{
		nbSet.insert(stayPt);
	} else {
		return;
	}
	//��Ļ���ĵ���������
	Point centPt((stayPt._x + 0.5 ) * scrSizePiexPt._x, (stayPt._y + 0.5) * scrSizePiexPt._y);
	int xFlag = 0, yFlag = 0;
	if ( pixPt._x < centPt._x)
	{
		xFlag = -1;
	} else if (pixPt._x > centPt._x) {
		xFlag = 1;
	}
	
	if (pixPt._y < centPt._y)
	{
		yFlag = -1;
	} else if (pixPt._y > centPt._y) {
		yFlag = 1;
	}
	
	Point 	pt1(stayPt._x + xFlag, stayPt._y),
			pt2(stayPt._x, stayPt._y + yFlag),
			pt3(stayPt._x + xFlag, stayPt._y + yFlag);
	
	//�ж���Ļ�����Ƿ�Ϸ�
	if (judgeSCrIndex(pt1))
	{
		nbSet.insert(pt1);
	}
	if (judgeSCrIndex(pt2))
	{
		nbSet.insert(pt2);
	}
	if (judgeSCrIndex(pt3))
	{
		nbSet.insert(pt3);
	}
}

//��ȡ��Ļ��������Ļ	
void Nbox::getNeighbour(Point pixPt, OneScreen **screens)
{
	//��Ļ����
	Point stayPt =  mapLogToSrcPtv(pixPt);
	
	//�Լ�Ҳ���Լ����ھӣ����뼯��
	//�ж���Ļ�����Ƿ�Ϸ�
	if (judgeSCrIndex(stayPt))
	{
		//nbSet.insert(stayPt);
		screens[0] = &herOrMonIdVec[stayPt._x][stayPt._y];
	} else {
		return;
	}
	//��Ļ���ĵ���������
	Point centPt((stayPt._x + 0.5 ) * scrSizePiexPt._x, (stayPt._y + 0.5) * scrSizePiexPt._y);
	int xFlag = 0, yFlag = 0;
	if ( pixPt._x < centPt._x)
	{
		xFlag = -1;
	} else if (pixPt._x > centPt._x) {
		xFlag = 1;
	}
	
	if (pixPt._y < centPt._y)
	{
		yFlag = -1;
	} else if (pixPt._y > centPt._y) {
		yFlag = 1;
	}
	
	Point 	pt1(stayPt._x + xFlag, stayPt._y),
			pt2(stayPt._x, stayPt._y + yFlag),
			pt3(stayPt._x + xFlag, stayPt._y + yFlag);
	if (xFlag == 0 && yFlag == 0)
	{
		return;
	} else if (xFlag == 0 && yFlag == 1)
	{
		if (judgeSCrIndex(pt2))
		{
			// nbSet.insert(pt2);
			screens[1] = &herOrMonIdVec[pt2._x][pt2._y];
		}
		return;
	} else if (xFlag == 1 && yFlag == 0)
	{
		if (judgeSCrIndex(pt1))
		{
			// nbSet.insert(pt1);
			screens[1] = &herOrMonIdVec[pt1._x][pt1._y];
		}
		return;
	} else {
		//�ж���Ļ�����Ƿ�Ϸ�
		if (judgeSCrIndex(pt1))
		{
			// nbSet.insert(pt1);
			screens[1] = &herOrMonIdVec[pt1._x][pt1._y];
		}
		if (judgeSCrIndex(pt2))
		{
			// nbSet.insert(pt1);
			screens[2] = &herOrMonIdVec[pt2._x][pt2._y];
		}
		if (judgeSCrIndex(pt3))
		{
			// nbSet.insert(pt1);
			screens[3] = &herOrMonIdVec[pt3._x][pt3._y];
		}
	}
}

void Nbox::getOneScreen(OneScreen * &screen, Point scrPt)
{
	screen = &herOrMonIdVec[scrPt._x][scrPt._y];
}

/*ͨ�������������������긽������heroid����*/
void Nbox::getCentPtSrcHerIdSet(Point &piexPt,set<string> &heroIdSet)
{
	OneScreen *neighborScrs[4] = {0},*oneScr = NULL;
	
	getNeighbour(piexPt, neighborScrs);	
	
	for (int i = 0; i < 4; i++)
	{
		oneScr = neighborScrs[i];
		if (oneScr == NULL)
		{
			continue;
		}
		heroIdSet.insert(oneScr->heroSet.begin(),oneScr->heroSet.end());
	}
}





