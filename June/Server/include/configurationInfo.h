/******************************************
	�ļ����ͣ�ͷ�ļ�
	
	�ļ����ƣ�configuration.h
	
	�ļ����ã����úͻ�ȡ��ɫ��Ӧ�һ��Ϳ��������;
*******************************************/

#ifndef CONFIGURATION_INFO_H
#define CONFIGURATION_INFO_H
//���ý�ɫ��Ӧ�һ����ݣ�
void setHangUpInfo(char* buffers);

//��ȡ��ɫ��Ӧ�һ����ݣ�
void getHangUpInfo(char* buffers);

//��ȡ��ɫ��������ݣ�
void getShortCutInfo(char* buffers);

//���ý�ɫ��������ݣ�
void setShortCutInfo(char* buffers);

//����ϵͳ�������ݣ�
void setSystemDataInfo(char* buffers);

//��ȡϵͳ�������ݣ�
void getSystemDataInfo(char* buffers);

//���ò����������ݣ�
void setOperationDataInfo(char* buffers);

//��ȡ�����������ݣ�
void getOperationDataInfo(char* buffers);

//��ȡ��ɫ������ݣ�
void getGoldInfo(char* buffers);

#endif