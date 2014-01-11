/************************************************************
    �ļ�����brushTower.cpp
    �ļ����ã�ˢ�º�ľ�¸���
    ���ߣ�chenzhen
    �������ڣ�2013.04.22
************************************************************/
#include"cpy_series_command_function.h"
#include"cpyLimit.h"
#include"command_other_function_all_over.h"
#include"cpyAsist.h"
#include"cpyManager.h"
#include"towerLayerRecord.h"
#include "instancing_manage.h"
#include "instancing_communication.h"

extern int sock_fd;
extern int g_msg_len;
extern Hero* pg_hero;
 
/*ˢ������¥����*/
void brushTower(char *buffer)
{
	char *hero_id,failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       
	TowerLayerRecord *towerLayerRecord;
	
	MSG_BEGIN(buffer, g_msg_len);
	
	/*����id*/
	MSG_CHAR(hero_id);	
	
	towerLayerRecord = pg_hero->getTowerLayerRecord();
	
	if(towerLayerRecord == NULL)
	{
		cout<<"brushTower the towerLayerRecord is NULL:"<<endl;
		return;
	}
	
#if 0
	//��ע�͵����ȷ�ΰ����warning����
	//û��Ҫˢ��
	if(!towerLayerRecord->isShouldBrushLayer())
	{
		cout<<"brushTower the towerLayerRecord is not should to brush:"<<endl;
		return;
	}
#endif	
	
	/*ˢ��һ���ݶ�20Ԫ��*/
	if(pg_hero->useMoney(0,20))
	{
		towerLayerRecord->brushLayerFlg();	
	}
}			









	
