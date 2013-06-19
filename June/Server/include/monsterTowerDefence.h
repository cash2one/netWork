/*
* author: 	Tory
* date	:	2012/8/21  
* Description:������������̳��ڹ������ 
*/
#ifndef MONSTER_TOWER_DEFENCE
#define MONSTER_TOWER_DEFENCE

#include "map_inform.h"
#include "monsterBase.h"			//�������ͷ�ļ�
#include "instancing_manage.h"
#include "TD_Instancing.h"	//����������ͷ�ļ�
#include"command_other_function_all_over.h"
#define	OFFSET_SIZE 3
#define MON_SPEED	60				//����ÿ˼��һ���ߵ����ص�
// ������������������
extern map<string, TD_Conf_T> id_2_tdConf;

class StateException{
	public:
		StateException(int x, int y):x(x), y(y){}
		inline int get_x(){return x;}	
		inline int get_y(){return y;}	
	private:
		int x, y;
}; 

class monsterTowerDefence;

//״̬����
class State
{
public:
    virtual void walk(monsterTowerDefence* mon)=0;
    virtual void attack(monsterTowerDefence* mon)=0;
    virtual void stop(monsterTowerDefence* mon)=0;
};

class monsterTowerDefence:public MonsterBase
{
	public :
		//���캯��
		monsterTowerDefence(char *_mapId,char *_typeId,char *_nickName,char *_identity, char *_type,char *_kind, int _experience, double _cdTime,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,int _getHrtSud, int _outHrt,int _inHrt, int _outAttVal, int _inAttVal,int _outDefVal,int _inDefVal,int _defSumVal,double _hit, double _crit,int _voids,int _tenacity,int _moveRange,int _hatRange,int _attRange,int _failGoodsless, int _failGoodsmost,int _hatVal,int _gold,set<string>& _failId, Point _pt,int _rank,int _speed, int _fiveEleInt,int _fiveHurt,int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,vector<string> &skiIdSet,char *_genAttId, double _angVal,int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool isInnerAttack,LveCtnManger _lveCtnMager);	

        //��������
        ~monsterTowerDefence(void); 
        //����˼������
        virtual void response(void);
        //����һ�����ֵ
        virtual void InpushEnmityValues(HatVal &hatva); 
        //�������
        virtual MonsterBase* copyMon(char *_mapId);
        //���diedNoThink��ֵ
        virtual bool getDiedNoThink(void);          //added by bison 7.4	
        //������������
        virtual void die(bool flgInit = false); 
		//�������ض��ӿڣ�����˳��ͨ�صĸ�����		
		bool addTowerDefLostCount(void);			
		
		int reStart;   

		void resetRoute();				
    private:    
        bool 			diedNoThink;         //���������ˣ����ٽ���˼��	added by bison 7.4
        int 			count4route;		
        int 			cur_position;		
        int 			forSelf;        //˼������
        bool 			flgRec;         //��λǰ��״ֵ̬
        State           *state;			//״̬��ָ��ʵ��
    public: 
		vector<Point>   route;          //·������
		Instancing_strategy td_strategy;        
    private:
            MonsterBase& walk(){
                state->walk(this);
                return (*this);
            }
            MonsterBase& attack(){
                state->attack(this);
                return (*this);
            }
            MonsterBase& stop(){
                state->stop(this);
                return (*this); 
            } 	 
    public:			
            void GoStraight();
            void reAttack();
			virtual void disappear();
			virtual void StandStill();
    private:
        class StopState:public State{
        public:
             virtual void walk(monsterTowerDefence* mon){
                delete mon->state;
                mon->state = new WalkState();
                mon->GoStraight();
								
 				Point ptEnd;
 				if(mon->count4route < mon->route.size())
					ptEnd = mon->route[mon->count4route];
				else
					ptEnd = mon->route.back();
				
				Point cur_pt = getCurrenPt(mon->pt, ptEnd, 60, 1, mon->map_now);//ͨ�������ȡ��ǰ���ص�cur_pt				
				mon->setLocation(cur_pt);
				if(cur_pt._x == ptEnd._x && cur_pt._y == ptEnd._y)	//���ߵ���ǰ��Ŀ���
				{
				//	cout<<"@@Tory mon->count4route:"<<mon->count4route<<endl;
					mon->count4route += 1;
                } 
			//	cout<<"stop--->walk"<<endl;
            };  
            virtual void attack(monsterTowerDefence* mon){
                delete mon->state;
                mon->state = new AttackState();
                cout<<"stop--->attack"<<endl;
            };
            virtual void stop(monsterTowerDefence* mon){
                cout<<"this monster still stop"<<endl;
            };
        };
        class AttackState:public State{
        public:
            virtual void walk(monsterTowerDefence* mon){
                delete mon->state;
                mon->state = new WalkState();
				mon->GoStraight();
                
 				Point ptEnd;
 				if(mon->count4route < mon->route.size())
					ptEnd = mon->route[mon->count4route];
				else
					ptEnd = mon->route.back();
				
				Point cur_pt = getCurrenPt(mon->pt, ptEnd, 60, 1, mon->map_now);//ͨ�������ȡ��ǰ���ص�cur_pt				
				mon->setLocation(cur_pt);
				if(cur_pt._x == ptEnd._x && cur_pt._y == ptEnd._y)	//���ߵ���ǰ��Ŀ���
				{
					cout<<"@@Tory mon->count4route:"<<mon->count4route<<endl;
					mon->count4route += 1;
                } 
                cout<<"attack--->walk"<<endl;
            }; 
            virtual void attack(monsterTowerDefence* mon){
                cout<<"this monster still attack"<<endl; 
                mon->reAttack();
            };
            virtual void stop(monsterTowerDefence* mon){
                delete mon->state;
                mon->state = new StopState();
				if(mon->addTowerDefLostCount())
					cout<<"Warning:(monsterTowerDefence.cpp)::the add lost monster is ERROR!"<<endl;
				mon->disappear();
                cout<<"attack--->stop"<<endl;
            };
        };
        class WalkState:public State{
        public:
            virtual void walk(monsterTowerDefence* mon){				
   				//�߶������У�ÿ���������λ��ͬ��
				if(mon->forSelf%4 == 0)
					mon->GoStraight();  
   
				Point ptEnd;
 				if(mon->count4route < mon->route.size())
					ptEnd = mon->route[mon->count4route];
				else
					ptEnd = mon->route.back();
				
				Point cur_pt = getCurrenPt(mon->pt, ptEnd, 60, 1, mon->map_now);//ͨ�������ȡ��ǰ���ص�cur_pt				
				mon->setLocation(cur_pt);
				if(cur_pt._x == ptEnd._x && cur_pt._y == ptEnd._y)	//���ߵ���ǰ״̬�µ�Ŀ���
				{
				//	cout<<"@@Tory mon->count4route:"<<mon->count4route<<endl;
					mon->count4route += 1;
					mon->GoStraight();
                }
			//	cout<<"@@Tory still walk,cur_pt._x:"<<cur_pt._x<<" "<<cur_pt._y<<endl;
            }; 
            virtual void attack(monsterTowerDefence* mon){
                delete mon->state;
                mon->state = new AttackState();           
                mon->reAttack();
				cout<<"walk--->attack"<<endl;
            };
            virtual void stop(monsterTowerDefence* mon){
                delete mon->state;
                mon->state = new StopState();
				if(!mon->addTowerDefLostCount())
					cout<<"Warning:(monsterTowerDefence.cpp)::the add lost monster is ERROR!"<<endl;
				mon->disappear();
			//	cout<<"walk--->stop"<<endl;
            };
        };
};

#endif