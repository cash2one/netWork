/************************************************************
	�ļ�����cpy_series_command_function.h
	�ļ����ã���������������ϵ�д�����
	���ߣ�chenzhen
	�������ڣ�2012.06.21
************************************************************/


#ifndef CPY_SERISE_COMMAND_FUNCTION_H
#define CPY_SERISE_COMMAND_FUNCTION_H

/*������*/
void entCpy(char *buffer);    

/*����������*/
void entCpyNextMap(char *buffer);  

/*�˳���������*/
void exitCpy(char *buffer);  

/*������Ӧ����*/
void  enterScenResponse(char *buffer);

/*ʹ�õ��߽�����*/
void enterCpyByTool(char *buffer);

/*�����������*/
void panelResponse(char *buffers);

/*���*/
void olderDish(char *buffer);

/*��ҵ����ʢ��*/
void pickGuildFeast(char *buffer);

/*������ɴ�Ӫ*/
void enterCampRom(char *buffer);

/*�����ľ�¸���*/
void enterTowerLayerCopy(char *buffer);

/*��ʼɨ������¥*/
void swapTowerLayerCopy(char *buffer);

/*ˢ������¥����*/
void brushTower(char *buffer);
#endif   