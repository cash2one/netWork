/************************************************************
	�ļ�����statuaryBase.h
	�ļ����ã�����StatuaryBase��
	���ߣ�chenzhen
	�������ڣ�2013.03.01
************************************************************/

#ifndef STATUARY_BASE_H
#define STATUARY_BASE_H
#include"wholeDefine.h"
#include"data_structure_struct.h"
#include<string>
#include<map>
#include"statuaryHero.h"
using namespace std;

class StatuaryBase
{
	char vocation[SHOR_MID_VALUE_LENGTH + 1];      //ְҵid
	map<string,string>limitToPhotoId;                 //����map����Ϊint�ͣ�ֵΪ��ӦͼƬid
	Point piexPt;                                  //��������
	char mapId[SHOR_MID_VALUE_LENGTH + 1];             //��ͼid
	int lastSeconds;                               //����ʱ��	
	
	public:
	
	StatuaryBase(char* _vocation,map<string,string> &_limitToPhotoId,Point _piexPt,char* _mapId);
	
	/*���ְҵid*/
	char* getVocation(void);
	
	/*��õ�ͼid*/
	char* getMapId(void);
	
	/*������ص�*/
	Point getPiexPt(void);
	
	/*���ݲ���require������Ӧ��ͼƬid*/
	char* getPhotoId(char* require);
	
	/*��ɫӮ�õ���*/
	MemStatuaryHero* winStatuary(void* memHero,char* titleId);
	
	/*���ݲ���require������Ӧ��ͼƬid,�����õ�*/
	char* testGetPhotoId(char* require);
};
#endif
