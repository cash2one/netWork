/************************************************************
	�ļ�����bruType.h
	�ļ����ã�����BruType�����Ժͺ���
	���ߣ�chenzhen
	�������ڣ�2012.08.14
************************************************************/
#ifndef BRUSH_MONSTER_TYPE_H
#define BRUSH_MONSTER_TYPE_H
#include"groupBrush.h"		
#include<map>
#include<string>
#include"bruMonInfor.h"
class Map_Inform;
class MonsterBase;
using namespace std;

class BruType
{
	double time;      //���೤ʱ��ˢһ��
	int mapTmeCtn;    //����ɵ�ͼ˼������
	int starCtn;      //������
	bool apply;       //����ˢ��ģʽ��trueΪ�ǣ������ǣ�
	bool allFlg;      //ȫˢ���ֵ��trueΪȫˢ�������ǣ�
	int sum;          //ÿ��������
	MonGroNum monBruNumSdu;   //ˢ�ָ���Ŀ��׼
	MonGroNum eachBru;        //ÿ��ˢ����Ŀ
	GroupBrush *groupBrush;     //����ˢ����ָ��
	map<string,MonsterBase*>monId_connect_monster;  //��ͼ������Ϣ
	map<string,BruMonInfor*>brushMonInform;          //ˢ�ּ�¼��
	bool againBru;
	/*ˢ�ּ�¼�����������סÿ��ˢ�ֵ�*/
	map<string,BruMonInfor*>::iterator bruMon_it;    
	
	/*һ����ȫˢ��*/
	void brushAllMon(void);
	
	/*ͨ����������жϺ�����������Ӧint�͵����ͺ�*/
	int typeMatchInt(MonsterBase *mon,bool _flgKind = true);
	
	/*ͨ����������жϹ������ͺ�*/
	bool judgebrushMonTpy(int _monTyp);
	
	/*��ģʽˢ��*/
	void brushMonByModle(void);
	
	/*�ж�ˢ��ʱ���Ƿ���*/
	bool judgeTme(void);   

	/*�жϾ�Ӣ�������Ƿ�ˢ��*/
	bool judgeGenerNum(void);
	
	/*�жϾ�Ӣ�������Ƿ�ˢ��*/
	bool judgeEliteNum(void);
	
	/*�ж������������Ƿ�ˢ��*/
	bool judgeActiveNum(void);
	
	/*�жϱ����������Ƿ�ˢ��*/
	bool judgePassNum(void);
	
	/*�ж�Ѳ�߹������Ƿ�ˢ��*/
	bool judgePatNum(void);
	
	/*�ж�BOSS�������Ƿ�ˢ��*/
	bool judgeBossNum(void);
	
	/*�ж����й������Ƿ�ˢ��*/
	bool judgeSum(void);	
	
public:
	BruType(map<string,MonsterBase *>& _monId_connect_monster,\
			map<string,BruMonInfor*>& _brushMonInform,double _time,\
			bool _allFlg = true,bool _apply = false,GroupBrush *groupBrush = NULL);
				 
	/*ˢ���ⲿ�ӿ�,����ͼ����*/
	void brushMonFun(int _Cpyflg);
	
	/*ͨ������id��ù���ʵ��ָ��*/
	MonsterBase* getMon(char *monId);
	
	/*��ʼ��ˢ�ּ�¼��ĵ�����*/		
	void initBruIt(void); 
	
	/*��ʼ��ˢ�ָ���Ŀ��׼*/
	void initMonBruStu(void);
	
	/*����ˢ��ģʽ*/
	BruType* copyBruTpy(char *newMapId);
	
	/*���õ�ͼˢ�ּ�¼����Ϣ*/
	void initBrushRed(void);
	
	/*������Щ�����ŵĹ���*/
	void initLveMon(void);
	
	/*���ƹ���ʵ���Լ���ˢ�ּ�¼��*/	
	void copyMapMon(map<string,MonsterBase*> &newMonIn,\
					map<string,BruMonInfor*> &newBrushInt,\
					char *newMapId);
	
	/*��ԭˢ��ģʽ*/
	void initBruTpy(void);
	
	/*��������*/
	~BruType(void);
	
	/*��ͣ�˵�ͼ�����йֵ�˼��,����Ҳ����ԾŹ���Ϊ��λ*/
	void stopMonThk(void);
	
	/*�����˵�ͼ�����йֵ�˼��,����Ҳ����ԾŹ���Ϊ��λ*/
	void reSetMonThk(void);
	
	/*����ִ��ֵ�����*/
	int getLveMonNum(void);
	
	/*����ֵܹ�����*/
	int getAllMonNum(void);
	
	/*��ӡ���Թ�����Ϣ*/
	void printMonsterInform(void);
	
	/*���������ڴ˵�ͼ�ϵĹֵĵ�ͼָ��*/
	void setMonMap(Map_Inform *map);
	
	/*��ô˵�ͼ���й�������id����*/
	void getTypeMonOneMap(set<string> &monAllType);
	
	/*�������������Ϣ*/
	// map<string,MonsterBase*>& getMonId_connect_monster(void);
	
	/*��ù����¼��*/
	// map<string,BruMonInfor*>& getBrushMonInform(void);
	
	/*�������������Ϣ*/
	void getAllMonObj(vector<MonsterBase*> &monObj);
	
	/*�����������������,�Ž���������������*/
	bool monIdInputDie(char *monTypId,char *monId);
	
	/*����������������ã�ɾ���ڵ�ͼ�������Ϣ*/
	bool EraInMap(char *monId);
	
	/*�����������������,ֱ��ɾ��*/
	bool monIdErase(char *monTypId,char *monId);
	
	/*��ͨ�������︴��*/
	void exchageDieMon(void);

};	
#endif
	
	
	
	
	
