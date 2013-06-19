#include"teamAsist.h"
#include"teamManager.h"
#include"hero.h"

extern struct ev_loop *loops;

void teamBindCal(struct ev_loop *loop,ev_timer *think,int revents)
{	
	
	ev_timer_stop(loop,think);
	
	Team *team = (Team *)think->target;
	if(team == NULL)
	{
		return;
	}
	
	team->initCaptureCopyId(true);
}

//����-1����ʾ�쳣��0������ӣ�1����Ա��2���ӳ�
int judgeHeroTeam(const Hero * heroMem,size_t &teamSize)
{	
	if(!heroMem)
	{
		return -1;
	}
	
	if(strlen(heroMem->getTeamerId()) == 0)
	{
		return 0;
	}	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	Team *team = teamManger->getTeamHandle(heroMem->getTeamerId());
		
	if(!team)
	{
		cout<<"judgeHeroTeam team is NULL:"<<endl;
		return -1;
	}
	
	teamSize = team->size();
	
	if(team->isHeader(heroMem->getIdentity()))
	{
		return 2;
	}
	
	if(team->isInTeam(heroMem->getIdentity()))
	{
		return 1;
	}
	
	
	
	return 0;
}
