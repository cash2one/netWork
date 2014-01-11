#include "configurationInfo.h"
#include "hero.h"
#include "my_memcached.h"
extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;

//���ý�ɫ��Ӧ��ݲ������ݣ�
void setShortCutInfo(char* buffers)
{
	char size;                         					/*����ÿ�����ݽ�ȡ�ĳ���*/
	int offset=6;										/*������Ϣ��ȡƫ����*/                 
	int dataLen;
	int retType=0;
	char ret_shortCutData[SHORT_CUT_BAR_DATA_SIZE+20]={0};	
	
	/*��ȡӢ��ID*/
	size=buffers[offset++];
	char hero_id[size+1];
	memmove(hero_id,buffers+offset,size);
	hero_id[size]='\0';
	
	offset+=size;   
	offset++;
	// size=buffers[offset++]; 						//���ݳ��ȿ��ܴ���128�����������ֵ��
	dataLen = strlen(buffers+offset);
	
	if(dataLen > SHORT_CUT_BAR_DATA_SIZE)
		dataLen = SHORT_CUT_BAR_DATA_SIZE;
		
	char shortCutData[dataLen+1];
	memmove(shortCutData,buffers+offset,dataLen);
	shortCutData[dataLen]='\0';
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(hero_id);
	if(iter==heroId_to_pHero.end())		//��Ӣ��id�����ڣ�
	{
		retType=1;
	}else{	
		/*��ȡ���������.*/
		memset(iter->second->memHero->shortCutData,'\0',strlen(iter->second->memHero->shortCutData));
		memmove(iter->second->memHero->shortCutData,shortCutData,dataLen);
	}
	
	sprintf(ret_shortCutData,"21,2,%d,%s",retType,shortCutData);
	send_msg(sock_fd,ret_shortCutData);	
}

//��ȡ��ɫ��Ӧ��ݲ������ݣ�
void getShortCutInfo(char* buffers)
{
	char size;                         					/*����ÿ�����ݽ�ȡ�ĳ���*/
	int offset=6;										/*������Ϣ��ȡƫ����*/                 
	int retType=0;
	char ret_shortCutData[SHORT_CUT_BAR_DATA_SIZE+20]={0};		
	
	
	/*��ȡӢ��ID*/
	size=buffers[offset++];
	char hero_id[size+1];
	memmove(hero_id,buffers+offset,size);
	hero_id[size]='\0';
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(hero_id);
	if(iter==heroId_to_pHero.end())		//��Ӣ��id�����ڣ�
	{
		retType=1;
	}
	
	/*��ȡ��ݲ�������.*/
	char shortCutData[SHORT_CUT_BAR_DATA_SIZE+1];
	memset(shortCutData,'\0',SHORT_CUT_BAR_DATA_SIZE+1);
	if(!retType)
		if(iter->second->memHero)
			memcpy(shortCutData,iter->second->memHero->shortCutData,strlen(iter->second->memHero->shortCutData));
	shortCutData[SHORT_CUT_BAR_DATA_SIZE]='\0';	
	
	sprintf(ret_shortCutData,"21,3,%d,%s",retType,shortCutData);
	send_msg(sock_fd,ret_shortCutData);	
}