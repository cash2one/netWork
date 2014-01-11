#include "teamOperator.h"
#include "wholeDefine.h"
#include"command_other_function_all_over.h"
#include"teamManager.h"
#include"team.h"

extern int g_msg_len;
extern Hero* pg_hero;

//�����Լ��Ƿ��Ѵ�������
void acceptTeamState(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *heroId;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	const char *teamId = pg_hero->getTeamerId();
	
	//û�ж���
	if(strlen(teamId) == 0)
	{
		sprintf(teamMsg,"37,0,%d",0);
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	TeamManager* teamManger = TeamManager::getManagerInst();
			
	if(!teamManger)
	{
		cout<<"acceptTeamState teamManger is NULL:"<<endl;
		return;
	}
			
	Team *team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"acceptTeamState team is NULL:"<<endl;
		return;
	}

	//����ʱ�����ߵ���
	if(!team->isInTeam(pg_hero->getIdentity()))
	{
		sprintf(teamMsg,"37,0,%d",0);
		send_msg(pg_hero->getFd(),teamMsg);
		pg_hero->initTeamerId();
		return;
	}
	team->formTeamMemMsg();
	send_msg(pg_hero->getFd(),team->getTeamMemMsg());
	
	//�����Լ������״̬
	pg_hero->brushTeamStation();
	
	return;	
	
	
}
	
//��������Ƿ��Ѵ�������
void acceptOtherHeroTeamState(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *otherHeroId;
	int teamFlg = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(otherHeroId);
	
	Hero *otherHero = heroid_to_hero(otherHeroId);
	
	if(!otherHero)
	{
		return;
	}
	
	const char *teamId = otherHero->getTeamerId();
	
	//û�ж���
	if(strlen(teamId) != 0)
	{
		teamFlg = 1;		
	}
	
	sprintf(teamMsg,"37,1,%s,%d",otherHeroId,teamFlg);
	send_msg(pg_hero->getFd(),teamMsg);
	return;
	
}



//�������
void applyForInTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *otherHeroId;
	int teamFlg = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(otherHeroId);
	
	Hero *otherHero = heroid_to_hero(otherHeroId);
	
	//������
	if(!otherHero)
	{
		cout<<"applyForInTeam the otherHero is NULL:"<<endl;
		sprintf(teamMsg,"37,0,3");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;		
	}
	
	const char *teamId = otherHero->getTeamerId();
	
	//�Է�û�ж���
	if(strlen(teamId) == 0)
	{
		cout<<"applyForInTeam you have not team :"<<otherHero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,4");
		send_msg(pg_hero->getFd(),teamMsg);		
		return;		
	}
	
	//���������Ѿ��ڶ�����
	if(strlen(pg_hero->getTeamerId()) != 0)
	{
		sprintf(teamMsg,"37,0,5");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	Team *team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"applyForInTeam team is NULL:"<<endl;
		return;		
	}
	
	//�����Ա����
	if(team->size() == Team::TEAM_NUM_SIZE)
	{
		sprintf(teamMsg,"37,0,12");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	Map_Inform *mapNow1 = otherHero->getMap();
	
	Map_Inform *mapNow2 = pg_hero->getMap();
	
	if(!mapNow1 || !mapNow2)
	{
		cout<<"applyForInTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//�Է��ڸ����У�����ʧ��
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,6");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	//���ڸ����У�����ʧ��
	if(mapNow2->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	Hero *headerHero = heroid_to_hero(team->getHeader());
	
	//�ӳ���Ȼ�����ߣ�����Ц
	if(!headerHero)
	{
		return;
	}
	

	//��������������Ϣ
	sprintf(teamMsg,"37,2,%s,%s,2",pg_hero->getIdentity(),pg_hero->getNickName());
	send_msg(headerHero->getFd(),teamMsg);	
	return;	
}


//ͬ���������
void agreeApplyForInTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *otherHeroId;
	int responseFlg = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(responseFlg);
	MSG_CHAR_END(otherHeroId);
	
	Hero *otherHero = heroid_to_hero(otherHeroId);
	
	//������Ҳ�����
	if(!otherHero)
	{
		cout<<"agreeApplyForInTeam the otherHero is NULL:"<<endl;
		sprintf(teamMsg,"37,0,3");
		send_msg(pg_hero->getFd(),teamMsg);		
		return;
	}
	
	//�ܽ�
	if(responseFlg == 0)
	{
		sprintf(teamMsg,"37,2,%d,%s",0,pg_hero->getNickName());
		send_msg(otherHero->getFd(),teamMsg);
		return;
	}	
	
	const char *teamId = pg_hero->getTeamerId();
	
	//�������Ѿ��ڶ�����
	if(strlen(otherHero->getTeamerId()) != 0)
	{
		sprintf(teamMsg,"37,2,8");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	//��������û�ж���
	if(strlen(teamId) == 0)
	{
		cout<<"agreeApplyForInTeam you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,9");
		send_msg(pg_hero->getFd(),teamMsg);		
		return;		
	}
	
	Map_Inform *mapNow1 = otherHero->getMap();
	
	Map_Inform *mapNow2 = pg_hero->getMap();
	
	if(!mapNow1 || !mapNow2)
	{
		cout<<"agreeApplyForInTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//�Է��ڸ����У�����ʧ��
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,6");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	//���ڸ����У�����ʧ��
	if(mapNow2->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	Team *team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"aggreApplyForInTeam team is NULL:"<<endl;
		return;		
	}
	
	//�����Ա����
	if(team->size() == Team::TEAM_NUM_SIZE)
	{
		sprintf(teamMsg,"37,0,12");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
		
	teamId = team->join(otherHero->getIdentity());
	
	if(!teamId)
	{
		return;
	}
	
	team->formTeamMemMsg();
	
	team->sendMsg(team->getTeamMemMsg());	
	
	otherHero->setTeamerId(teamId);
	
	team->initCaptureCopyId(true);
	
	return;	
}



//����"���"
void inviteHeroJoinTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *joinHeroId;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(joinHeroId);
	
	Hero *joinHero = heroid_to_hero(joinHeroId);
	
	//�������˲�����
	if(!joinHero)
	{
		sprintf(teamMsg,"37,0,3");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	const char *teamId = joinHero->getTeamerId();
	
	
	//���������Ѿ��ڶ�����
	if(strlen(teamId) != 0)
	{
		sprintf(teamMsg,"37,0,8");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	Map_Inform *mapNow1 = joinHero->getMap();
	
	Map_Inform *mapNow2 = pg_hero->getMap();
	
	if(!mapNow1 || !mapNow2)
	{
		cout<<"inviteHeroJoinTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//�Է��ڸ����У�����ʧ��
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,6");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	//���ڸ����У�����ʧ��
	if(mapNow2->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	teamId = pg_hero->getTeamerId();
	if(strlen(teamId) != 0)
	{
		TeamManager* teamManger = TeamManager::getManagerInst();
		Team *team = teamManger->getTeamHandle(teamId);
		
		if(!team)
		{
			cout<<"inviteHeroJoinTeam team is NULL:"<<endl;
			return;		
		}
		
		//���Ƕӳ���������
		if(!team->isHeader(pg_hero->getIdentity()))
		{
			cout<<"inviteHeroJoinTeam you are not header :"<<pg_hero->getIdentity()<<endl;
			sprintf(teamMsg,"37,0,10");
			send_msg(pg_hero->getFd(),teamMsg);	
			return;
		}
	}
	
	//��������������Ϣ
	sprintf(teamMsg,"37,2,%s,%s,1",pg_hero->getIdentity(),pg_hero->getNickName());
	send_msg(joinHero->getFd(),teamMsg);
	return;
}
				
//����"���"��Ӧ
void responseInviteHeroJoinTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *inviteHeroId;
	int responseFlg;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(responseFlg);
	MSG_CHAR_END(inviteHeroId);	
	
	//������
	Hero *inviteHero = heroid_to_hero(inviteHeroId);
	
	//�����߲�����
	if(!inviteHero)
	{
		cout<<"responseInviteHeroJoinTeam the inviteHero is NULL:"<<endl;
		sprintf(teamMsg,"37,0,3");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	
	
	//�ܽ�
	if(responseFlg == 0)
	{
		sprintf(teamMsg,"37,2,%d,%s",0,inviteHero->getNickName());
		send_msg(inviteHero->getFd(),teamMsg);
		return;
	}
	
	
	//�Ѿ��ڶ�����
	if(strlen(pg_hero->getTeamerId()) != 0)
	{
		sprintf(teamMsg,"37,0,5");
		send_msg(inviteHero->getFd(),teamMsg);
		return;
	}
	
	
	Map_Inform *mapNow1 = inviteHero->getMap();
	
	Map_Inform *mapNow2 = pg_hero->getMap();
	
	if(!mapNow1 || !mapNow2)
	{
		cout<<"responseInviteHeroJoinTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//�Է��ڸ����У�����ʧ��
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,6");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	//���ڸ����У�����ʧ��
	if(mapNow2->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	const char *teamId = inviteHero->getTeamerId();
	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//û�ж���
	if(strlen(teamId) == 0)
	{
		if(!teamManger)
		{
			cout<<"responseInviteHeroJoinTeam teamManger is NULL:"<<endl;
			return;
		}
		
		teamId = teamManger->captureTeamHandle(inviteHero->getIdentity());
		
		if(!teamId)
		{
			cout<<"responseInviteHeroJoinTeam teamId is NULL:"<<endl;
			return;
		}		
	}		
	
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"responseInviteHeroJoinTeam team is NULL:"<<endl;
		return;		
	}	
	
	//�����Ա����
	if(team->size() == Team::TEAM_NUM_SIZE)
	{
		sprintf(teamMsg,"37,0,12");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	teamId = team->join(pg_hero->getIdentity());
	
	if(!teamId)
	{
		return;
	}
	
	team->formTeamMemMsg();
	
	team->sendMsg(team->getTeamMemMsg());
	
	if(strlen(inviteHero->getTeamerId()) == 0)
	{
		inviteHero->setTeamerId(teamId);
	}
	
	pg_hero->setTeamerId(teamId);	
	
	team->initCaptureCopyId(true);
	
	pg_hero->brushTeamStation();

}
					
//�˳�
void offTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *offHeroId;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(offHeroId);	
	

	
	const char *teamId = pg_hero->getTeamerId();
	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//û�ж���
	if(strlen(teamId) == 0)
	{
		cout<<"offTeam you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,9");
		send_msg(pg_hero->getFd(),teamMsg);		
		return;
	}
	
	
	Map_Inform *mapNow1 = pg_hero->getMap();
	
	if(!mapNow1)
	{
		cout<<"offTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//���ڸ����У��˳�ʧ��
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	if(!teamManger)
	{
		cout<<"offTeam teamManger is NULL:"<<endl;
		return;
	}
	
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"offTeam team is NULL:"<<endl;
		return;		
	}
	
	
	if(!team->eraseMemSet(pg_hero->getIdentity()))
	{
		cout<<"offTeam fail :"<<pg_hero->getIdentity()<<endl;
		return;
	}
		
	if(team->memOnLineSize() == 0)
	{
		teamManger->recoverTeamHandle(teamId);
	}
	else
	{	
		team->formTeamMemMsg();
		team->sendMsg(team->getTeamMemMsg());
	}
	
	//�˳��ɹ�
	sprintf(teamMsg,"37,0,%d,%d",0,0);
	
	send_msg(pg_hero->getFd(),teamMsg);	
	
	pg_hero->initTeamerId();
	
	team->initCaptureCopyId(true);
	
	pg_hero->brushTeamStation();
}

//��ɢ
void disMissTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *disMissHeroId;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(disMissHeroId);
	
	const char *teamId = pg_hero->getTeamerId();
	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//û�ж���
	if(strlen(teamId) == 0)
	{
		cout<<"disMissTeam you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,9");
		send_msg(pg_hero->getFd(),teamMsg);			
		return;
	}
	
	
	Map_Inform *mapNow1 = pg_hero->getMap();
	
	if(!mapNow1)
	{
		cout<<"disMissTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//���ڸ����У���ɢʧ��
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	if(!teamManger)
	{
		cout<<"disMissTeam teamManger is NULL:"<<endl;
		return;
	}
	
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"disMissTeam team is NULL:"<<endl;
		return;		
	}
	
	//���Ƕӳ���û��Ȩ��
	if(!team->isHeader(pg_hero->getIdentity()))
	{
		cout<<"disMissTeam you are not header :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,10");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
		
	
	
	//��ɢ��Ϣ
	sprintf(teamMsg,"%d,%d,%d,%d",37,0,0,2);
	
	team->disMissTeam(teamMsg);
	
	team->initCaptureCopyId(true);
	
	teamManger->recoverTeamHandle(team->getTeamId());
	
}


//ת��
void transferTeamLeader(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *offerHeroId;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(offerHeroId);	
	
	Hero *offHero = heroid_to_hero(offerHeroId);
	
	//�Է�������
	if(!offHero)
	{
		cout<<"transferTeamLeader the offHero is NULL:"<<endl;
		sprintf(teamMsg,"37,0,3");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	const char *teamId = pg_hero->getTeamerId();
	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//û�ж���
	if(strlen(teamId) == 0)
	{
		cout<<"transferTeamLeader you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,9");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
	
	if(!teamManger)
	{
		cout<<"transferTeamLeader teamManger is NULL:"<<endl;
		return;
	}
		
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"transferTeamLeader team is NULL:"<<endl;
		return;		
	}
	
	//û��Ȩ��
	if(!team->isHeader(pg_hero->getIdentity()))
	{
		cout<<"transferTeamLeader you are not header :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,10");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
	
	//��ѡ�߲��ڶ�����
	if(!team->isInTeam(offerHeroId))
	{
		cout<<"transferTeamLeader offerHeroId is not in team :"<<offerHeroId<<endl;
		sprintf(teamMsg,"37,0,11");
		send_msg(pg_hero->getFd(),teamMsg);
		return;		
	}
	
	if(!team->passHeader(offerHeroId))
	{
		cout<<"transferTeamLeader fail :"<<offerHeroId<<endl;
		return;
	}
	
	team->formTeamMemMsg();
	team->sendMsg(team->getTeamMemMsg());
	
	team->initCaptureCopyId(true);
	
	pg_hero->brushTeamStation();
	
	offHero->brushTeamStation();
	
#if 0	
	//ת�ò���Ҫͬ��
	
	//ת����Ϣ
	sprintf(teamMsg,"%d,%d",37,8,);
	
	//�ӳ�������
	Hero *offHero = heroid_to_hero(offerHeroId);
	
	send_msg(offHero->getFd(),teamMsg);
	
#endif
	
}


//ת�û�Ӧ
void transferTeamLeaderResponse(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *offerHeroId;
	int responseFlg;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(responseFlg);
	MSG_CHAR_END(offerHeroId);	
	

	
	const char *teamId = pg_hero->getTeamerId();
	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//û�ж���
	if(strlen(teamId) == 0)
	{
		cout<<"transferTeamLeaderResponse you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,5");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
	
	if(!teamManger)
	{
		cout<<"transferTeamLeaderResponse teamManger is NULL:"<<endl;
		return;
	}
		
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"transferTeamLeaderResponse team is NULL:"<<endl;
		return;		
	}
	
	if(!team->isInTeam(offerHeroId))
	{
		cout<<"transferTeamLeaderResponse offerHeroId is not in team :"<<offerHeroId<<endl;
		return;		
	}
	
	Hero *teamLeader = heroid_to_hero(team->getHeader());
	
	if(!teamLeader)
	{
		cout<<"transferTeamLeaderResponse teamLeader is NULL :"<<offerHeroId<<endl;
		return;
	}
		
	if(responseFlg == 0)
	{
		//�ܾ�ת��
		sprintf(teamMsg,"37,8,0,%s,%s",pg_hero->getIdentity(),pg_hero->getNickName());
		send_msg(teamLeader->getFd(),teamMsg);
		return;
	}
	
	
	if(!team->passHeader(pg_hero->getIdentity()))
	{
		cout<<"transferTeamLeaderResponse fail :"<<offerHeroId<<endl;
		return;
	}
	team->formTeamMemMsg();
	team->sendMsg(team->getTeamMemMsg());
}


//����
void kickOutTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *kickedHeroId;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(kickedHeroId);	
	
	const char *teamId = pg_hero->getTeamerId();
		
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//û�ж���
	if(strlen(teamId) == 0)
	{
		cout<<"kickOutTeam you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,5");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
	
	if(!teamManger)
	{
		cout<<"kickOutTeam teamManger is NULL:"<<endl;
		return;
	}
		
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"kickOutTeam team is NULL:"<<endl;
		return;		
	}
	
	//���Ƕӳ�
	if(!team->isHeader(pg_hero->getIdentity()))
	{
		cout<<"kickOutTeam you are not header :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,10");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
	
	//�Է����ڶ�����
	if(!team->isInTeam(kickedHeroId))
	{
		cout<<"kickOutTeam kickedHeroId is not in team :"<<kickedHeroId<<endl;
		sprintf(teamMsg,"37,0,11");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;		
	}
	
	Hero *kickedHero = heroid_to_hero(kickedHeroId);
	
#if 0
	//�Է�������(������Ҳ�����ߣ�
	if(!kickedHero)
	{
		cout<<"kickOutTeam kickedHero is NULL :"<<kickedHeroId<<endl;
		sprintf(teamMsg,"37,0,5");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
#endif	
	
	Map_Inform *mapNow1 = pg_hero->getMap();
	
	if(!mapNow1)
	{
		cout<<"kickOutTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//���ڸ����У���������
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	
	if(!team->eraseMemSet(kickedHeroId))
	{
		cout<<"kickOutTeam fail :"<<kickedHeroId<<endl;
		return;
	}
	
	//����
	sprintf(teamMsg,"37,0,2,%s,%s",pg_hero->getIdentity(),pg_hero->getNickName());
	
	team->formTeamMemMsg();
	team->sendMsg(team->getTeamMemMsg());
	
	if(kickedHero)
	{		
		send_msg(kickedHero->getFd(),teamMsg);	
		kickedHero->initTeamerId();
	}
		
	team->initCaptureCopyId(true);
}

	
	
	
