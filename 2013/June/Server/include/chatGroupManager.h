/************************************************************
	�ļ�����ChatGroupManager.h
	�ļ����ã�����ChatGroupManager(����Ⱥ���ࣩ�����Ժͳ�Ա
	���ߣ�chenzhen
	�������ڣ�2013.05.10
************************************************************/

#ifndef CHAT_GROUP_MANAGER_H
#define CHAT_GROUP_MANAGER_H
#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<string>
using namespace std;

class ChatGroup;

class ChatGroupManager
{
	vector<ChatGroup*> groupVec;
	list<int> usefulIndexlist;	
	
	//����ʱ��̬����
	vector<ChatGroup*> dynamicGroupVec;
	
	//�����õĶ�̬�±�
	set<int> usedDynamicIndex;
	
	//ɾ����vector���µĿտ��±�
	list<int> useAbledynamicIndex;
	
	map<string,int> usedGroupIdIndexMap;
	
	//������̬�ģ�����Ⱥ����,ͳ�����ã�����������
	size_t totalSize;
	
	static ChatGroupManager *chatGroupManager;
	
	
	public:	
	
	static void createManagerInst(size_t groupNum);
	
	static ChatGroupManager* getManagerInst();
	
	//���gruopId��Ӧ��Ⱥ���
	ChatGroup* getChatGroupHandle(const char* groupId);
	
	//ռ��һ��Ⱥʵ��������ʵ��id
	const char* campGroupHandle(const char* heroIdOwner);
	
	//����һ��Ⱥ
	void recoverGroupHandle(const char* groupId);
	
	//��������
	~ChatGroupManager();
	
	private:
	
	//��ֹ�ⲿ����
	ChatGroupManager(const ChatGroupManager &groupManager);
	
	//��ֹ�ⲿ����
	ChatGroupManager& operator=(const ChatGroupManager &groupManager);
	
	//��ֹ�ⲿ���ã�����ģʽ��
	ChatGroupManager(size_t groupNum);
};
#endif
	