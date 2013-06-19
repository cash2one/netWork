#include "configurationInfo.h"
#include "hero.h"
#include "my_memcached.h"
extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;

//���ò���ϵͳ�������ݣ�
void setOperationDataInfo(char* buffers)
{
	char size;                         						/*����ÿ�����ݽ�ȡ�ĳ���*/
	int offset=6;											/*������Ϣ��ȡƫ����*/                 
	int dataLen=0;
	int retType=0;
	char ret_OperDataInfo[SHORT_CUT_BAR_DATA_SIZE+20]={0};	

	
	/*��ȡӢ��ID*/
	size=buffers[offset++];
	char hero_id[size+1];
	memmove(hero_id,buffers+offset,size);
	hero_id[size]='\0';
	
	
	
	offset+=size;   
	offset++;
	// size=buffers[offset++]; 						//���ݳ��ȿ��ܴ���128�����������ֵ��
	dataLen = strlen(buffers+offset);
	
	if(dataLen > OPERATION_SET_DATA_SIZE)
		dataLen = OPERATION_SET_DATA_SIZE;
		
	char operationSetData[dataLen+1];
	memmove(operationSetData,buffers+offset,dataLen);
	operationSetData[dataLen]='\0';
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(hero_id);
	if(iter==heroId_to_pHero.end())					//��Ӣ��id�����ڣ�
	{
		retType=1;
	}else{	
		memset(iter->second->memHero->operationSetData,'\0',strlen(iter->second->memHero->operationSetData));
		memmove(iter->second->memHero->operationSetData,operationSetData,dataLen);
	}

	sprintf(ret_OperDataInfo,"21,7,%d,%s",retType,operationSetData);
	send_msg(sock_fd,ret_OperDataInfo);	
}

//��ȡ����ϵͳ�������ݣ�
void getOperationDataInfo(char* buffers)
{
	char size;                         					/*����ÿ�����ݽ�ȡ�ĳ���*/
	int offset=6;										/*������Ϣ��ȡƫ����*/                 
	int retType=0;
	char ret_OperDataInfo[SHORT_CUT_BAR_DATA_SIZE+20]={0};	
	
	/*��ȡӢ��ID*/
	size=buffers[offset++];
	char hero_id[size+1];
	memmove(hero_id,buffers+offset,size);
	hero_id[size]='\0';
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(hero_id);
	if(iter==heroId_to_pHero.end())						//��Ӣ��id�����ڣ�
	{
		retType=1;		
		return;
	}
	Hero*msgSender=iter->second;
	
	/*��ȡϵͳ��������.*/
	char operationSetData[OPERATION_SET_DATA_SIZE+1];
	memset(operationSetData,'\0',OPERATION_SET_DATA_SIZE+1);
	if(!retType)
		if(iter->second->memHero)
			memcpy(operationSetData,iter->second->memHero->operationSetData,strlen(iter->second->memHero->operationSetData));
	operationSetData[OPERATION_SET_DATA_SIZE]='\0';	

	sprintf(ret_OperDataInfo,"21,8,%d,%s",retType,operationSetData);
	send_msg(msgSender->getFd(),ret_OperDataInfo);	
}