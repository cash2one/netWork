/************************************************************
	�ļ�����statuaryAsist.h
	�ļ����ã�������ظ�������
	���ߣ�chenzhen
	�������ڣ�2013.03.04
************************************************************/


#ifndef STATUARY_ASIST_H
#define STATUARY_ASIST_H

/*����������ʱ���ӻ���������ȡ������Ϣ*/
void openServerStatuaryMsg(void);

/*�رշ�����ʱ������������������Ϣ*/
void closeServerStatuaryMsg(void);

/*��ʼ�������Ӧ�������б����ǵ��񻺴�ļ�*/
void initStrtuaryTitleIdList(void);

/*���Դ�*/
void testInStatuary(void);

/*����ȡ*/
void testOutStatuary(void);

/*�������*/
void setUpStatuary(char* heroId,char* titleId);

/*�ݻٵ���*/
void destoryStatuary(char* titleId);

/*������*/
void destroyAllStatuary(void);

/*���Ե��������*/
void printStatuaryPt(void);

#endif   