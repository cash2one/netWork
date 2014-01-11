/********************************************************************

    created:   2012/2/24  15:24
	
	�ļ�����	monster_configuration.h

    author:       Tory 

    purpose:  monster_configuration.hͷ�ļ�
	
	�޸ģ�	

*********************************************************************/
#ifndef MONSTER_CONFIGURATION_H
#define MONSTER_CONFIGURATION_H
#include<set>
#include<string>
#include<vector>
#include"wholeDefine.h"
using namespace std;
class Monster_Inform
{
	
	public:
	
	Monster_Inform(char * _typeId, char *_type, char *_kand,double rank,char *_nickName, double _lifeUpperVal, double _lifeVal,\
		int _magicUpperVal,int _magicVal,int  _getHrtSud,double _outHrt,double _inHrt, double _outAttVal, double _inAttVal,\
		double _outDefVal, double _inDefVal, int _defSumVal,double _hit,double _crit,double _voids,double _tenacity,int _moveRange,\
		int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,int _hatVal,int _angVal,\
		vector<string> _skiIdSet,char *genAttId,int _gold,set<string>& _failId,char *_photoId,\
		char* _stage,int _experience,double _cdTime,int _fiveEleInt,int _fiveHurt,\
		int _fiveEleRank,int _goFor,int _expTme,int _monyTme,int _speed,int _ownerAttriType,\
		char* _ownerAttri,double _attackRatio,bool _isInnerAttack,int _radius = 0);

		~Monster_Inform(void);
		
	public:
		char *typeId;		//��������
	
		char *nickName;		//����
		
		char *photoId;
		
		double lifeUpperVal;	//����ֵ����	
		
		double lifeVal;		//��ǰ����ֵ
		
		int magicUpperVal;	//ħ��ֵ����
		
		int magicVal;		//��ǰħ��ֵ
		
		
		int attack_range;	//������Χ
		
		int walk_range;		//���߷�Χ		
		int sum;
		
		
		char *type;         //�������ͣ�������������Ѳ�ߣ�
		
		char *kind;       //�������ࣨ��ͨ����Ӣ��boss��
		
		double rank;         //�ȼ�
		
		
		int hrtSud;      //����
		double outHrt;     //����
		double inHrt;      //����
		double outAttVal;    //�⹦����ֵ
		double inAttVal;    //�ڹ�����ֵ
		double outDefVal;    //�⹦����ֵ
		double inDefVal;    //�ڹ�����ֵ
		int defSumVal;   //����ֵ�ܺ�
		double hit;        //����
		double crit;       //����
		double voids;      //����
		double tenacity;       //����	
		int hatRange;      //��޷�Χ
		int failGoodsLess;   //����������ֵ
		int failGoodsMost;   //����������ֵ
		int hatVal;      //���ֵ
		int gold;       //���		
		
		set<string> failList;  //�����б�
		
		char* stage;
		
		int radius;
		
		double cdTime;    	//cdʱ��		
		
		int experience;     //����
		
		int angVal;         //ŭ��ֵ
		
		vector<string>skiIdSet;   //����id�б�
		
		int speed;
		
		
		int fiveEleInt;      //�������Դ���ֵ
		int fiveEleRank;     //���еȼ�ֵ
		int fiveHurt;        //�����˺�ֵ
		
		
		int goFor;          //�߶�Ƶ��
		
		int expTme;         //���鱶��
		
		int monyTme;        //��Ǯ����
		
		int ownerAttriType;            //���ͣ�����Ϊ1����ӪΪ2���������Ϊ0
		char ownerAttri[SHOR_MID_VALUE_LENGTH + 1];     //���ɣ���Ӫ����
		
		
		char genAttId[SHOR_MID_VALUE_LENGTH + 1];
		
		double attackRatio;          //��ɱ�����ְ���������
		
		bool isInnerAttack;          //ƫ�ڹ�Ϊ�棬ƫ�⹦Ϊ��
		
		char* getstage(void);
		int getgold(void);
		int getrank(void);
		char* getkind(void);
		int getExperience(void);
		
		int getAngVal(void);
		vector<string> getSkiIdSet(void);
		
		int getRank(void);
		
		int getSpeed(void);
		
		void print(char *monKindId);

};	


#endif

