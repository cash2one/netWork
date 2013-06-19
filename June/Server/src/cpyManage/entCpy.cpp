/************************************************************
    �ļ�����entCpy.cpp
    �ļ����ã����������ķ���
    ���ߣ�chenzhen
    �������ڣ�2012.06.21
************************************************************/
#include"cpy_series_command_function.h"
#include"cpyLimit.h"
#include"command_other_function_all_over.h"
#include"cpyLimit.h"
#include"cpyAsist.h"

#include"command_user_role_manage.h"
//�������к궨���ͷ�ļ�
#include"other_define_data.h"
//����ͷ����ĺ궨��ͷ�ļ�
#include"command_return_define_data.h"
//�û���ɫ����������ͷ�ļ�
#include"user_role_manage_assist.h"
//���й��ߺ�����ͷ�ļ�
#include"command_other_function_all_over.h"
#include"map_inform.h"
// #include "TD_Instancing.h"
//Tory ����������
#include "instancing_manage.h"
//Tory ��������ͷ�ļ�
#include "instancing_communication.h"

#include"cpyManager.h"

extern int sock_fd;
extern int g_msg_len;
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<int, Role*> fd_to_pRole;
extern map<string, Hero*> heroId_to_pHero;
extern Hero* pg_hero;
extern char server_name[10];
extern CpyManger *cpyManger;
//��������������
extern Instancing_manage *Inst_MNG;  
 			
void entCpy(char *buffer)
{
	char *hero_id,*cpyTyeId,failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       
	
	int cpyRank;       
	
	MSG_BEGIN(buffer, g_msg_len);
	
	/*����id*/
	MSG_CHAR(hero_id);	
	
	//�����������ͺ�
	MSG_CHAR(cpyTyeId);
	
	/*���������Ѷ�*/
	MSG_INT(cpyRank);		
	
	if(strlen(pg_hero->getTeamerId()) == 0)
	{
		entCpyAsist(hero_id,cpyTyeId,cpyRank);
		return;
	}
	
	else
	{
		handleTeamLeaderOperateAsist(hero_id,cpyTyeId,cpyRank);
		return;
	}
}



void entCpyAsist(const char* hero_id,const char* _cpyTyeId,int cpyRank)
{
	char failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       
	map<string,CpyLimit*>::iterator cpyLimt_it;
	bool isParty = false;		
	vector<string> heroId;  
    char cpyTyeId[100] = {'\0'};
	
	if(!hero_id || !_cpyTyeId)
	{
		cout<<"entCpyAsist argument is error:"<<endl;
		return;
	}
	
	strncpy(cpyTyeId,_cpyTyeId,strlen(_cpyTyeId));
	
	heroId.push_back(hero_id);
	
	/*���ɸ���*/
	if (cpyRank == 3)
	{
		isParty = true;
	}	
	strncat(cpyTyeId,"_",strlen("_"));		
	appendNum(cpyTyeId,cpyRank,1);	
	
	/*�����񸱱�����������*/
	if(strcmp(cpyTyeId,"021_0") == 0)
	{
		cout<<"the cpyTyeId is  the taskCpy:"<<cpyTyeId<<endl;
		return;
	}

#if 0	
	if(strncmp(cpyTyeId,"008",3) == 0)	//�ж��ǲ��ǽ���������
	{
		int ret = Inst_MNG->apply_td_inst(pg_hero, cpyTyeId);
		return;	
	}
#endif		
	
    // ������ͨ�����н��в���,�Ҳ������Խ�����������
    cpyLimt_it = cpyId_to_cpyLimit.find(cpyTyeId);
	if(cpyLimt_it == cpyId_to_cpyLimit.end())
	{
		return;
	}
	else
	{
		Failure_Reason* failure_reason = (Failure_Reason*)malloc(sizeof(Failure_Reason));		
		failure_reason->size = 0;

		if(!initFailReson(failure_reason))
		{
			cout<<"failure_reason is NULL:"<<endl;
			return;
		}
	
		if (cpyLimt_it->second == 0) return;
	
		/*�ʸ����*/
		if(!cpyLimt_it->second->qualifyExam(heroId,failure_reason,false,isParty))
		{			
			dealFailRson(failure_reason,failMsg,sizeof(failMsg));
			sendFailMsg(heroId,failMsg);			
			free(failure_reason);			
			return;
		}
		cpyLimt_it->second->assignRom(heroId);
		free(failure_reason); 
	
		/*��¼���븱������ˮ�� jolly 12.11 start*/
		char account_msg[1024]={'\0'};
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",6,0,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),cpyLimt_it->second->getCpyId());
		write_log(account_msg);	
		/*��¼���븱������ˮ�� jolly 12.11 end*/
	}
}
