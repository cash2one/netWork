/************************************************************
	�ļ�����activeAsist.h
	�ļ����ã�������������
	���ߣ�chenzhen
	�������ڣ�2012.10.25
************************************************************/

#ifndef ACTIVE_ASIST_H
#define ACTIVE_ASIST_H
#include"hero.h"
#include"map_inform.h"
class DailyActive;


typedef struct DurCampTme
{
	/*��Ӫս�������ʱ��*/
	int campBatFldOlder;
	
	/*���ֶ�����ʱ��*/
	int camphappyFight;
	
	/*��Ӫ����ս����ʱ��*/
	int campcompeteFight;
	
	/*������������ʱ��*/
	int kungFuMaster;
	
	/*��������ʱ��*/
	int takePartDurTme;
	
	/*��Ӫ����ս��ƽʱ��*/
	int campPeaceTme;
	
	/*��������ս��ƽʱ��*/
	int kungPeaceTme;
	
	DurCampTme(int odlerTme = 0,int fightTme = 0,int competeTme = 0,\
	int masterTme = 0,int _takeTme = 0,int _campPeaceTme = 0,\
	int _kungPeaceTme = 0)
	{
		campBatFldOlder = odlerTme;
		camphappyFight = fightTme;
		campcompeteFight = competeTme;
		kungFuMaster = masterTme;
		takePartDurTme = _takeTme;
		campPeaceTme = _campPeaceTme;
		kungPeaceTme = _kungPeaceTme;
	}
	
	/*���Դ�ӡ����*/
	void printDurTme(void)
	{
		cout<<"test the struct DurCampTme begin:"<<endl;
		cout<<"campBatFldOlder:"<<campBatFldOlder<<endl;
		cout<<"camphappyFight:"<<camphappyFight<<endl;
		cout<<"campcompeteFight:"<<campcompeteFight<<endl;
		cout<<"kungFuMaster:"<<kungFuMaster<<endl;
		cout<<"campPeaceTme:"<<campPeaceTme<<endl;
		cout<<"kungPeaceTme:"<<kungPeaceTme<<endl;
		cout<<"test the struct DurCampTme end:"<<endl;
	}
		
}DurCampTme;

/*���͵���ص�*/
bool sendInMapPoint(Map_Inform *mapSend,Point piexPtSend,Hero *myHero);

/*������Ӧ����*/
void activePanelResponse(Hero *owner);

/*��int��ʱ�����ַ���*/
bool timeToStr(int hour,int min,char *tmeStr,int lengStr);

/*���ַ���ʱ��ת����int��*/
bool tmeStrChgInt(int &hour,int &min,char *timStr);

/*�Ƚ�����ʱ��Ĵ�С�����ǰ��С�ں��ߣ��򷵻���*/
bool timeLess(int &hour1,int &min1,int &hour2,int &min2);

/*�Ƚ�2��ʱ�䣬���ǰ��С���򷵻���*/
bool timeStrLess(char *timStr1,char *timStr2);

/*����������Ŀ�����ر�*/
void controlActiveOpenAndClose(int hour,int min,int whichDay);

/*�����*/
void openActive(DailyActive *active);

/*�رջ*/
void closeActive(DailyActive *active);

/*����������ʱ���ж��ڴ�ʱ����Щ�Ӧ�ÿ�ʼ*/
void controlActiveOpenStartServer(int hour,int min,int whichDay);

/*����������ʱ����ʼ����Ӫ��ĳ���ʱ��*/
void initCampeDurTme(void);

/*��������̽Ӫ�*/
void openCampActive(void);

/*�رհ���̽Ӫ�*/
void closeCampActive(void);

//ˢ��ȫ���ճ�
void refreshSrvDaily();

/*��������ʢ��*/
void openDishActive(void);

/*�رհ���ʢ��*/
void closeDishActive(void);

/*���ð���ʢ���Ƿ�Ϊ����ı��ֵ*/
void setDishTodayActiveFlg(void);

/*���ùرհ���ʢ���Ƿ�Ϊ����ı��ֵ*/
void setCloseDishTodayActiveFlg(void);

/*���ùرհ���ʢ���Ƿ�Ϊ����ı��ֵ,������*/
void setCloseDishTodayActiveFlgTset(void);

#endif