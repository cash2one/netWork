
#include"teamManager.h"
#include"team.h"
TeamManager* TeamManager::teamManager = NULL;
TeamManager::TeamManager(size_t teamNum)
{
	for(size_t index = 0;index < teamNum;++index)
	{
		try
		{
			Team *newTeam = new Team(index);
			teamVec.push_back(newTeam);
			usefulIndexlist.push_back(index);
		}
		catch(exception e)
		{
			throw e;
		}
	}
	
	totalSize = teamNum;
}

TeamManager::TeamManager(const TeamManager &teamManagers)
{

}


TeamManager& TeamManager::operator=(const TeamManager &teamManagers)
{
	return *this;
}

//��������
void TeamManager::createManagerInst(size_t teamNum)
{
	if(!teamManager)
	{
		try
		{
			teamManager = new TeamManager(teamNum);
		}
		catch(exception e)
		{
			throw e;
		}
	}
}

//����һ������ʵ��ָ��
TeamManager* TeamManager::getManagerInst()
{	
	if(!teamManager)
	{
		createManagerInst(100);
	}
	return teamManager;
}

//ռ��һ��Ⱥʵ��������ʵ��id
const char* TeamManager::captureTeamHandle(const char *teamLeader)
{
	if(!teamLeader)
	{
		return NULL;
	}
	
	if(!usefulIndexlist.empty())
	{
		size_t index = usefulIndexlist.front();
		Team* team = teamVec[index];				
		pair<map<string,int>::iterator,bool> inset_it = usedTeamIdIndexMap.insert(pair<string,int>(team->getTeamId(),index));
		
		if(!inset_it.second)
		{
			cout<<"TeamManager::captureTeamHandle is camped or the index  before error:"<<index<<endl;
			return NULL;
		}
		usefulIndexlist.pop_front();
		
		return team->captureTeam(teamLeader);
	}
	else
	{
		size_t damamicIndex;
		Team *team = NULL;
		if(useAbledynamicIndex.empty())
		{
			damamicIndex = totalSize;
			++totalSize;
		}
		else
		{
			damamicIndex = useAbledynamicIndex.front();			
		}
				
		//����ʹ�õ��±��ֶ���һ��
		pair<set<int>::iterator,bool> insert_it = usedDynamicIndex.insert(damamicIndex);
		
		//��������쳣
		if(!insert_it.second)
		{
			cout<<"TeamManager::captureTeamHandle the dynamicIndex is camped or the index  before error:"<<damamicIndex<<endl;
			return NULL;
		}
		
		try
		{
			team = new Team(damamicIndex);				
		}
		catch(exception e)
		{
			throw e;
		}
		
		pair<map<string,int>::iterator,bool> inset_it = usedTeamIdIndexMap.insert(pair<string,int>(team->getTeamId(),damamicIndex));
		//�����쳣
		if(!inset_it.second)
		{
			cout<<"TeamManager::captureTeamHandle the index is exist before :"<<damamicIndex<<endl;
			delete team;
			team = NULL;
			return NULL;
		}
		
		//���տ�
		if(damamicIndex - teamVec.size() < dynamicTeamVec.size())
		{
			dynamicTeamVec[damamicIndex] = team;
	
			//�������õĿտ�������һ��ѽ
			useAbledynamicIndex.pop_front();
		}
		//����׷��
		else
		{
			dynamicTeamVec.push_back(team);
		}		
		
		return team->captureTeam(teamLeader);	
	}
}

//���gruopId��Ӧ��Ⱥ���
Team* TeamManager::getTeamHandle(const char* teamId)
{
	if(!teamId)
	{
		cout<<"TeamManager::getTeamHandle teamId is NULL:"<<endl;
		return NULL;
	}
	map<string,int>::iterator index_it;
	index_it = usedTeamIdIndexMap.find(teamId);
	if(index_it == usedTeamIdIndexMap.end())
	{
		cout<<"TeamManager::getTeamHandle teamId is not found:"<<teamId<<endl;
		return NULL;
	}
	if(index_it->second < teamVec.size())
	{
		return teamVec[index_it->second];
	}
	
	return dynamicTeamVec[index_it->second - teamVec.size()];
}

//����һ��Ⱥ
void TeamManager::recoverTeamHandle(const char* teamId)
{
	cout<<"TeamManager::recoverTeamHandle begin the  team resoure teamId:"<<teamId<<endl;
	
	if(!teamId)
	{
		return;
	}
	
	map<string,int>::iterator index_it;
	index_it = usedTeamIdIndexMap.find(teamId);
	if(index_it == usedTeamIdIndexMap.end())
	{
		cout<<"TeamManager::recoverTeamHandle the teamId is error:"<<teamId<<endl;
		return;
	}
	
	if(index_it->second < teamVec.size())
	{
		teamVec[index_it->second]->init();
		usefulIndexlist.push_front(index_it->second);
	}
	else
	{		
		Team *danamicNewTeam = dynamicTeamVec[index_it->second - teamVec.size()] ;	
		delete danamicNewTeam;
		danamicNewTeam = NULL;
		dynamicTeamVec[index_it->second - teamVec.size()] = NULL;
		size_t flg = usedDynamicIndex.erase(index_it->second);		
		//��������쳣���Ǿ���ԭ���
		if(flg == 0)
		{
			cout<<"TeamManager::recoverTeamHandle erase the index is error:"<<index_it->second<<endl;
		}		
		useAbledynamicIndex.push_front(index_it->second);
	}
	cout<<"TeamManager:: recoverTeamHandle success the  team resoure teamId:"<<teamId<<" index:"<<index_it->second<<endl;
	usedTeamIdIndexMap.erase(index_it);
}

//��������
TeamManager::~TeamManager()
{
	for(vector<Team*>::iterator team_it = teamVec.begin();team_it != teamVec.end();++team_it)
	{
		delete *team_it;
		*team_it = NULL;
	}
	
	for(vector<Team*>::iterator team_it = dynamicTeamVec.begin();team_it != dynamicTeamVec.end();++team_it)
	{
		delete *team_it;
		*team_it = NULL;
	}
	teamVec.clear();
	dynamicTeamVec.clear();
	usefulIndexlist.clear();
	usedDynamicIndex.clear();
	useAbledynamicIndex.clear();
	usedTeamIdIndexMap.clear();
	teamManager = NULL;	
}	

size_t TeamManager::size() const
{
	return totalSize;
}
