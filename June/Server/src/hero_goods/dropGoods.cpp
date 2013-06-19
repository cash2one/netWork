#include "dropgoods.h"
#include "money_operator.h"
#include"team.h"
#include"teamManager.h"

using namespace std;
extern map<string,DropList_Configuration*> id_to_dropgoods;
extern map<string,Monster_Inform*>	monTypeId_connect_property;
extern map<string,Hero*> heroId_to_pHero;
extern map<string,Pick*> goods_to_hero; 
extern map<string,Ointment *> id_to_ointment;
extern map<string,Equip_config*> id_to_equip; 
extern map<string,Map_Inform*> mapId_connect_map;
extern list<string> time_flag;
extern list<string> three_flag;
extern map<string, TaskGoodsInfo*> id2taskGoodsInfo;

int cc;  //��¼��������
void dropgoods(char* drop_goods_id,DropList_Configuration *droplist)		//������Ʒ
{
	int percent=0;
	int drugnum;
	int toolnum;
	int loop;
	int wequipnum;
	int bequipnum; 
	int pequipnum;
	int pkequipnum;
	int oequipnum;
	int drugper=0;
	int drugperdetail=0;
	int toolper=0;
	int toolperdetail=0;
	int wequipper=0;
	int wequipperdetail=0;
	int bequipper=0;
	int bequipperdetail=0;
	int pequipper=0;
	int pequipperdetail=0;
	int pkequipper=0;
	int pkequipperdetail=0;
	int oequipper=0;
	int oequipperdetail=0;
	int randnum;
	int dropper;
	int loopupper;
	int num;
	int interval;
	map<int,string> dropgoodsid;
	map<int,string>::iterator id_it;
	percent=droplist->getpercent();		
	randnum=random_number(1,1000);			//�漴1~1000�������
	
	if (randnum<=percent)			//�漴���������������,�������Ʒ
	{
		drugper=droplist->getdrugper();							//drug�׶ε������
		toolper=drugper+droplist->gettoolper();					//tool�׶ε������
		wequipper=toolper+droplist->getwequipper();				//wequip�׶ε������
		bequipper=wequipper+droplist->getbequipper();			//bequip�׶ε������
		pequipper=bequipper+droplist->getpequipper();			//pequip�׶ε������
		pkequipper=pequipper+droplist->getpkequipper();			//pkequip�׶ε������
		oequipper=pkequipper+droplist->getoequipper();			//oequip�׶ε������		
		drugnum=droplist->getdrugnum();							//drug�׶ε������Ʒ����
		toolnum=droplist->gettoolnum();							//tool�׶ε������Ʒ����
		wequipnum=droplist->getwequipnum();						//wequip�׶ε������Ʒ����
		bequipnum=droplist->getbequipnum();						//bequip�׶ε������Ʒ����
		pequipnum=droplist->getpequipnum();						//pequip�׶ε������Ʒ����
		pkequipnum=droplist->getpkequipnum();					//pkequip�׶ε������Ʒ����
		oequipnum=droplist->getoequipnum();						//oequip�׶ε������Ʒ����
		dropgoodsid=droplist->getdropgoodsid();
		randnum=random_number(1,1000);			//�ٴ��漴����,�жϵ������Ʒ����Ϊʲô����
		if (randnum<=drugper)				
		{
			if (drugnum==0)					//��Ϊ0,���˳����亯��,��ʾΪ��������ߵ���
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{					
				randnum=random_number(1,drugnum);				//�漴��,�ӵ������Ʒ���漴������һ��					
			}
		}
		else if (randnum<=toolper)
		{
			if (toolnum==0)				//��Ϊ0,���˳����亯��,��ʾΪ��������ߵ���
			{
				strncpy(drop_goods_id,"0000",15);
			}
			else
			{	
				toolnum+=drugnum;
				randnum=random_number(drugnum,toolnum);		//�漴��,�ӵ������Ʒ���漴������һ��									
			}
		}
		else if (randnum<=wequipper)
		{
			if (wequipnum==0)			//��Ϊ0,���˳����亯��,��ʾΪ��������ߵ���
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{				
				toolnum+=drugnum;
				wequipnum+=toolnum;
				randnum=random_number(toolnum,wequipnum);		//�漴��,�ӵ������Ʒ���漴������һ��	
			}				
		}
		else if (randnum<=bequipper)
		{
			if (bequipnum==0)			//��Ϊ0,���˳����亯��,��ʾΪ��������ߵ���
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{				
				wequipnum=drugnum+toolnum+wequipnum;
				bequipnum+=wequipnum;
				randnum=random_number(wequipnum,bequipnum);		//�漴��,�ӵ������Ʒ���漴������һ��	
			}					
		}
		else if (randnum<=pequipper)
		{
			if (pequipnum==0)			//��Ϊ0,���˳����亯��,��ʾΪ��������ߵ���
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{
				bequipnum=drugnum+toolnum+wequipnum+bequipnum;	
				pequipnum+=bequipnum;
				randnum=random_number(bequipnum,pequipnum);		//�漴��,�ӵ������Ʒ���漴������һ��	
			}				
		}			
		else if (randnum<=pkequipper)
		{
			if (pkequipnum==0)			//��Ϊ0,���˳����亯��,��ʾΪ��������ߵ���
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{
				pequipnum=drugnum+toolnum+wequipnum+bequipnum+pequipnum;
				pkequipnum+=pequipnum;
				randnum=random_number(pequipnum,pkequipnum);		//�漴��,�ӵ������Ʒ���漴������һ��	
			}				
		}					
		else if (randnum<=oequipper)
		{	
			if (oequipnum==0)			//��Ϊ0,���˳����亯��,��ʾΪ��������ߵ���
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{				
				pkequipnum=drugnum+toolnum+wequipnum+bequipnum+pequipnum+pkequipnum;
				oequipnum+=pkequipnum;
				randnum=random_number(pkequipnum,oequipnum);		//�漴��,�ӵ������Ʒ���漴������һ��	
			}
		}	
		randnum=randnum-1;
		id_it=dropgoodsid.find(randnum);
		if (id_it==dropgoodsid.end())
		{
			sprintf(drop_goods_id,"%s","0000");
		} 
		else
		{
			sprintf(drop_goods_id,"%s",(id_it->second).c_str());
		}		
	} 
	else			//�����������������.�򲻵����κε���
	{
		sprintf(drop_goods_id,"%s","0000");
	}
}

void getexperience(Hero *hero,MonsterBase* monster)
{
	char* monsterid = monster->getTypeId();	
	int teamnum;
	int experience;
	int monsterlevel;
	int herolevel=hero->getLevel();
	int expTime=monster->getExpTme();	
	vector<string> allTeamPerson;
	
	if(strlen(hero->getTeamerId()) == 0)
	{
		teamnum = 1;
	}
	
	else
	{
			
		TeamManager* teamManger = TeamManager::getManagerInst();
			
		if(!teamManger)
		{
			cout<<"getexperience teamManger is NULL:"<<endl;
			return;
		}	
			
		Team *team = teamManger->getTeamHandle(hero->getTeamerId());
		
		if(!team)
		{
			cout<<"getexperience team is NULL:"<<endl;
			return;
		}
		
		team->getTeamMemberId(allTeamPerson);
		
		teamnum = allTeamPerson.size();
	}
	
	map<string,Monster_Inform*>::iterator monster_it;
	monster_it=monTypeId_connect_property.find(monsterid);
	if (monster_it==monTypeId_connect_property.end())
	{
		cout<<"According to monsterid can't find monster inform (dropGoods)"<<endl;
		return;
	} 
	else
	{
		Monster_Inform* monster=monster_it->second;
		monsterlevel=monster->getrank();
	}
	experience=gExp(teamnum,monsterlevel,herolevel);
	if (experience==0)
	{
		experience=1;
	}
	experience=experience*expTime;
	
	char msg[1024]={'\0'};
	
	if (teamnum==1)
	{		
		hero->setExpNow(experience*hero->memHero->expTimes);
		snprintf(msg,sizeof(msg),"%d,%d,%s,%d,%d,%d",9,GET_EXPERIENCE,monsterid,hero->getExpNow(),monsterlevel,hero->getPetBox()->getActivePetIndex());
		
		//�������     by bison
		char monsterId[51];
		sub_str(monsterId, monsterid, 2, 0);
		// if (hero->getTaskState() & TASK_NEED_KILL_MONSTER)
		{
			hero->updateHeroTaskStatus(KILL_TASK_NEED_TYPE, monsterId, monsterlevel);
			hero->updateHeroTaskStatus(KILL_LIMIT_TASK_NEED_TYPE, "-1", monsterlevel);
		}
		if (hero->getPetBox()->getActivePet()!=NULL)
		{
			hero->getPetBox()->getActivePet()->growExp(experience*hero->memHero->expTimes,hero->getLevel(),hero);
			snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",hero->getPetBox()->getActivePet()->getExpNow());
		}
		else 
		{
			snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",0);
		}
		
		if (hero->getRide()!=NULL)
		{
			hero->getRide()->gainExp(hero,experience*hero->memHero->expTimes,1);
			snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d,%d",hero->getRide()->getExpNow(),hero->getRide()->getExpMax());
		}
		else 
		{
			snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",0);
		}
		send_msg(hero->getFd(),msg);
	}
	else
	{		
		if (!allTeamPerson.empty())
		{
			vector<string>::iterator it;
			for (it=allTeamPerson.begin();it!=allTeamPerson.end();it++)
			{			
				memset(msg,'0',sizeof(msg));
				map<string,Hero*>::iterator hero_it;
				hero_it=heroId_to_pHero.find(*it);
				if (hero_it==heroId_to_pHero.end())
				{
					cout<<"this hero is not exist! dropgoods.cpp 439"<<endl;
					continue;
				}
				else
				{
					Hero *teamHero=hero_it->second;
					if (strcmp(hero->getMapId(),teamHero->getMapId())==0)
					{					
						teamHero->setExpNow(experience*teamHero->memHero->expTimes);
						snprintf(msg,sizeof(msg),"%d,%d,%s,%d,%d,%d",9,GET_EXPERIENCE,monsterid,teamHero->getExpNow(),monsterlevel,teamHero->getPetBox()->getActivePetIndex());
						
						//�������     by bison
						char monsterId[51];
						sub_str(monsterId, monsterid, 2, 0);
						// if (teamHero->getTaskState() & TASK_NEED_KILL_MONSTER)
						{
							teamHero->updateHeroTaskStatus(KILL_TASK_NEED_TYPE, monsterId, monsterlevel);
							teamHero->updateHeroTaskStatus(KILL_LIMIT_TASK_NEED_TYPE, "-1", monsterlevel);
						}
						if (teamHero->getPetBox()->getActivePet()!=NULL)
						{
							teamHero->getPetBox()->getActivePet()->growExp(experience*teamHero->memHero->expTimes,teamHero->getLevel(),teamHero);
							snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",teamHero->getPetBox()->getActivePet()->getExpNow());
						}
						else
						{
							snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",0);
						}
						
						if (teamHero->getRide()!=NULL)
						{
							teamHero->getRide()->gainExp(teamHero,experience*teamHero->memHero->expTimes,1);
							snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d,%d",teamHero->getRide()->getExpNow(),teamHero->getRide()->getExpMax());
						}
						else
						{
							snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",0);
						}
						send_msg(teamHero->getFd(),msg);
					}
					else
					{
						cout<<"this hero is in another map dropgoods.cpp 454"<<endl;
						continue;
					}
				}
			}
		}		
	}	
	
	increaseBoundGameMoney(hero,getmoney(monsterid));
}

int getmoney(char* monster_typeid)	//ɱ���ֻ�õĽ�Ǯ
{
	int gold;
	map<string,Monster_Inform*>::iterator monster_it;
	monster_it=monTypeId_connect_property.find(monster_typeid);
	if (monster_it==monTypeId_connect_property.end())
	{
		cout<<"!!!!!!!!!!!!!!no monster!!!!!!!!!!!!!gold"<<endl;
	} 
	else
	{
		Monster_Inform *monster;
		monster=monster_it->second;		
		gold=monster->gold;
		int moneyTime=monster->monyTme;
		gold=gold*moneyTime;
		return gold;
	}
}

vector<Point> drop_location(Point monsterPoint,int number,Map_Inform *dropmap)	//����λ���ж�
{	
	Point tempPoint=monsterPoint;
	vector<Point> dropPoint;
	dropPoint.clear();
	if (dropmap==NULL)
	{
		return dropPoint;
	}
	int usedNumber;
	int randNumber;
	cout<<"monsterPoint: x: "<<monsterPoint._x<<" y: "<<monsterPoint._y<<endl;
	// //srand(MY_TV_USEC);
	int locationRandomx;
	int locationRandomy;
	for (int i=0;i<number;i++)
	{		
		locationRandomx=random_number(0,128);			//�漴�����ص�x����	
		locationRandomy=random_number(0,64);			//�漴�����ص�x����	
		
		monsterPoint._x=monsterPoint._x+locationRandomx-64;
		monsterPoint._y=monsterPoint._y+locationRandomy-32;
		
		int digst=dropmap->getBaseDigst();
		Point temp=MapExchangeLogical(monsterPoint);
		Point logPoint;
		logPoint._x=temp._x;
		logPoint._y=temp._y+digst;
		
		//�ж��Ƿ����ϰ���.�����������漴
		if (!dropmap->judgeLogPtHind(logPoint))
		{
			cout<<"jolly:this point is hind point in dropgoods 382"<<endl;
			monsterPoint=tempPoint;
		}
		dropPoint.push_back(monsterPoint);
	}	
	cout<<"dropPoint: x:"<<monsterPoint._x<<" y: "<<monsterPoint._y<<endl;
	return dropPoint;
}

int monstertype(MonsterBase *hit)
{	
	char* kind=hit->getKind();
	cout<<"monster kind is "<<kind<<endl;
	int loop=1;
	if (strcmp(kind,"Boss")==0)
	{
		loop=8;
	}
	else
	{
		loop=1;
	}
	cout<<"monster loop is "<<loop<<endl;
	return loop;
}

void monsterDropGoods(char *heroId,MonsterBase *monster)			//��ֵ���
{	
	char* monster_typeid=monster->getTypeId();			//ͨ��MonsterBase ��Monster_Inform,��粻��stage����ͨ��MonsterBase��,����������
	map<string,Monster_Inform*>::iterator monster_it;
	monster_it=monTypeId_connect_property.find(monster_typeid);
	Monster_Inform *monster_inform = NULL;
	if (monster_it==monTypeId_connect_property.end())				//�Ҳ�����Monster_Inform,����
	{
		cout<<"jolly:According to the monsterid can't find the monster inform dropGoods.cpp 647"<<endl;
		return;
	}
	else
	{		
		monster_inform=monster_it->second;
		char* stage=monster_inform->getstage();				//ȡ����ĵ���׶�
				int bound=0;					//��״̬/*�bossû��������*/
		if(strcmp(monster->getType(),"ActiveBossMon") == 0)
		{			
			bound=2;
		}
		saveInPick(heroId,monster->getMap(),monstertype(monster),stage,monster->getLocation(),bound,0);
	}
}
	
void saveInPick(char* heroId,Map_Inform *dropmap,int loop,char *stage,Point deadPoint,int bound,int accountFlag)
{			
	if (dropmap==NULL)
	{
		return;
	}
	
	char* uuid=cid();				//����ʵ��id,һ����һ��
	char flag[40]={'\0'};
	strncpy(flag,uuid,sizeof(flag));
	free(uuid);
	int count=0;					//��������
	
	char pt_flag[15]={'\0'};		//���ڱ���pickʵ���е�k-v�Ե�key
	char goodsid[8][20];			//����8������,ÿ�����ߵ�id���Ȳ��ᳬ��20;Ŀǰд��
	int i;
	
	char temp[20]={0};
	
	Pick *pick = NULL;
	
	memset(g_out_buf,0,sizeof(g_out_buf));	
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%s",9,0,heroId,bound,flag);		

	map<string,DropList_Configuration*>::iterator it;	
	it=id_to_dropgoods.find(stage);	
	if (it==id_to_dropgoods.end())			//�Ҳ��������б� ����
	{
		cout<<"have no stage! and stage is:: "<<stage<<endl;
		return;
	}
	else
	{
		DropList_Configuration *droplist=it->second;
		for (i=0;i<loop;i++)
		{				
			dropgoods(temp,droplist);
			if (strcmp(temp,"0000")!=0)					//�����صĲ���0000,�����������Ʒ,����ͳ��++
			{
				// cout<<"goodsid["<<i<<"]:"<<goodsid[i]<<endl;
				strncpy(goodsid[count],temp,sizeof(goodsid[count]));
				count++;
			}
			if(i==7&&count<4)									//��i����=7��,�����������boss,Ȼ��boss�������4��,��������ͳ��С��4��,���ѭ��һ��
			{
				i--;
			}
		}
		if (count==0)				//û�е�����Ʒ,����
		{
			cout<<"count==0"<<endl;
			return;
		}
		else
		{
			vector<Point> pt=drop_location(deadPoint,count,dropmap);
			if (pt.size()==0)
			{
				cout<<"pt.size()==0"<<endl;
				return;
			}
			
			pick=new Pick(flag,heroId,count,dropmap,bound,deadPoint);
			for (i=0;i<count;i++)
			{		
				cout<<"11111111111111111111111111111111111111"<<endl;
				snprintf(pt_flag,sizeof(pt_flag),",%d,%d",pt[i]._x,pt[i]._y);					//�ϳ�ptflag
				snprintf(g_out_buf+strlen(g_out_buf), sizeof(g_out_buf)-strlen(g_out_buf),",%d,%d,%s", pt[i]._x, pt[i]._y, goodsid[i]);
				pick->insertDropGoods(pt_flag,goodsid[i]);				//ÿ��������Ʒ�����뵽pick��			
			}							
			cout<<"g_out_buf:"<<g_out_buf<<endl;
			dropmap->insertDropInst(pick);
			send_msg_dropGoods(g_out_buf,flag,dropmap);
		}			
	}
}

void dropTaskGoods(Hero *attack, MonsterBase *hit)
{
	if (attack==NULL)
	{
		return;
	}
	char* monsterid=hit->getTypeId();
	char monid[100] = {0};
	if (strncmp(monsterid,"MP",2)==0)
	{
		strncpy(monid,monsterid+2,strlen(monsterid)-2);
	}
	// cout<<"bison bison bison bison bison bison bison bison bison"<<endl;
	// cout<<"bison bison identity:"<<attack->getIdentity()<<endl;
	list<Task*> map_task=attack->getAccepted_Task_List();
	if (!map_task.empty())
	{
		// cout<<"bison 11111111111111111"<<endl;
		list<Task*>::iterator task_it;
		for (task_it=map_task.begin();task_it!=map_task.end();task_it++)
		{
			Task* task=(*task_it);
			char* task_goods=task->getTaskGoods();
			if (task_goods != NULL)
			{
				// cout<<"[BisonTest drop task goods] taskgoods is "<<task_goods<<endl;
				map<string, TaskGoodsInfo*>::iterator task_goods_it;
				task_goods_it=id2taskGoodsInfo.find(task_goods);
				if (task_goods_it!=id2taskGoodsInfo.end())
				{
					// cout<<"bison 222222222222222222222"<<endl;
					TaskGoodsInfo* task_goods_info=task_goods_it->second;
					//modified by bison
					if (task_goods_info->isMonsterDrop(monid) && task_goods_info->dropTaskGoodsOk())
					{
						// cout<<"bison 3333333333333333333333333"<<endl;
						Bag* bag=attack->getBag();
						//Modified by bison
						if (saveGoodsInBag(attack,task_goods,1))
						{
							// cout<<"bison 4444444444444444444444444444444"<<endl;
							attack->updateHeroTaskStatus(COLLECT_TASK_NEED_TYPE, task_goods);
						}
					}
				}
			}
		}
	}	
}


//����ƿ�޵���
void dropTaskGoods(Hero *attack, Bottle *hit)
{
	if (attack==NULL)
	{
		return;
	}
	char* bottleid=hit->getTypeId();
	char botid[100] = {0};
	
	// cout<<"bison bison bison bison bison bison bison bison bison"<<endl;
	// cout<<"bison bison identity:"<<attack->getIdentity()<<endl;
	list<Task*> map_task=attack->getAccepted_Task_List();
	if (!map_task.empty())
	{
		// cout<<"bison 11111111111111111"<<endl;
		list<Task*>::iterator task_it;
		for (task_it=map_task.begin();task_it!=map_task.end();task_it++)
		{
			Task* task=(*task_it);
			char* task_goods=task->getTaskGoods();
			if (task_goods != NULL)
			{
				// cout<<"[BisonTest drop task goods] taskgoods is "<<task_goods<<endl;
				map<string, TaskGoodsInfo*>::iterator task_goods_it;
				task_goods_it=id2taskGoodsInfo.find(task_goods);
				if (task_goods_it!=id2taskGoodsInfo.end())
				{
					// cout<<"bison 222222222222222222222"<<endl;
					TaskGoodsInfo* task_goods_info=task_goods_it->second;
					//modified by bison
					if (task_goods_info->isMonsterDrop(bottleid) && task_goods_info->dropTaskGoodsOk())
					{
						// cout<<"bison 3333333333333333333333333"<<endl;
						Bag* bag=attack->getBag();
						//Modified by bison
						if (saveGoodsInBag(attack,task_goods,1))
						{
							// cout<<"bison 4444444444444444444444444444444"<<endl;
							attack->updateHeroTaskStatus(COLLECT_TASK_NEED_TYPE, task_goods);
						}
					}
				}
			}
		}
	}	
}

void send_msg_dropGoods(char* msg,char *flag,Map_Inform *map_now)
{	
	if(map_now == NULL||msg==NULL||flag==NULL)
	{
		cout<<"send_msg_dropGoods error   dropGoods.cpp"<<endl;
		return;
	}
	
	Nbox *box;		////////////////////////////////////////�������Ź���///////////////////////
	box=map_now->getBox();  
	if(box == NULL)
	{
		cout<<"box null  dropGoods.cpp"<<endl;
		return;
	}
	
	StyObj obj(flag,PICK_STYLE_TYPE);	
	map_now->insertID(obj);		
	box->getStaInSrcVec(obj);
	cout<<"here in send_msg_dropgoods"<<endl;
	cout<<"msg:"<<msg<<endl;
	box->sentBoxMsg(msg);	
	cout<<"end in send_msg_dropgoods"<<endl;
}



