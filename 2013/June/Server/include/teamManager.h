/************************************************************
	�ļ�����TeamManager.h
	�ļ����ã�����TeamManager(��������ࣩ�����Ժͳ�Ա
	���ߣ�chenzhen
	�������ڣ�2013.05.10
************************************************************/

#ifndef TEAM_MANGER_H
#define TEAM_MANGER_H
#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<string>
using namespace std;

class Team;

class TeamManager
{
	vector<Team*> teamVec;
	list<int> usefulIndexlist;	
	
	//����ʱ��̬����
	vector<Team*> dynamicTeamVec;
	
	//�����õĶ�̬�±�
	set<int> usedDynamicIndex;
	
	//ɾ����vector���µĿտ��±�
	list<int> useAbledynamicIndex;
	
	map<string,int> usedTeamIdIndexMap;
	
	//������̬�ģ�����Ⱥ����,ͳ�����ã�����������
	size_t totalSize;
	
	static TeamManager *teamManager;
	
	
	public:	
	
	static void createManagerInst(size_t groupNum);
	
	static TeamManager* getManagerInst();
	
	//���gruopId��Ӧ��Ⱥ���
	Team* getTeamHandle(const char* teamId);
	
	//ռ��һ��Ⱥʵ��������ʵ��id
	const char* captureTeamHandle(const char *teamLeader);
	
	//����һ��Ⱥ
	void recoverTeamHandle(const char* teamId);
	
	//��������
	~TeamManager();
	
	void addAgreeNum();
	
	void initAgreeNum();
	
	size_t size() const;
	
	private:
	
	//��ֹ�ⲿ����
	TeamManager(const TeamManager &teamManagers);
	
	//��ֹ�ⲿ����
	TeamManager& operator=(const TeamManager &teamManagers);
	
	//��ֹ�ⲿ���ã�����ģʽ��
	TeamManager(size_t teamNum);
};
#endif
	