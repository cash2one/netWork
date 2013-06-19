/************************************************************
	�ļ�����chatGroupManager.cpp
	�ļ����ã�ʵ��ChatGroupManager(Ⱥ���ࣩ
	���ߣ�chenzhen
	�������ڣ�2013.05.10
************************************************************/
#include"chatGroupManager.h"
#include"chatGroup.h"
extern ChatGroupManager *chatManager;
ChatGroupManager* ChatGroupManager::chatGroupManager = NULL;
ChatGroupManager::ChatGroupManager(size_t groupNum)
{
	for(size_t index = 0;index < groupNum;++index)
	{
		try
		{
			ChatGroup *newGroup = new ChatGroup(index);
			groupVec.push_back(newGroup);
			usefulIndexlist.push_back(index);
		}
		catch(exception e)
		{
			throw e;
		}
	}
	
	totalSize = groupNum;
}

ChatGroupManager::ChatGroupManager(const ChatGroupManager &groupManager)
{

}


ChatGroupManager& ChatGroupManager::operator=(const ChatGroupManager &groupManager)
{
	return *this;
}

//��������
void ChatGroupManager::createManagerInst(size_t groupNum)
{
	if(!chatGroupManager)
	{
		try
		{
			chatGroupManager = new ChatGroupManager(groupNum);
		}
		catch(exception e)
		{
			throw e;
		}
	}
}

//����һ������ʵ��ָ��
ChatGroupManager* ChatGroupManager::getManagerInst()
{	
	return chatGroupManager;
}

//ռ��һ��Ⱥʵ��������ʵ��id
const char* ChatGroupManager::campGroupHandle(const char* heroIdOwner)
{
	if(!heroIdOwner)
	{
		return NULL;
	}
	
	if(!usefulIndexlist.empty())
	{
		size_t index = usefulIndexlist.front();
		ChatGroup* camp = groupVec[index];				
		pair<map<string,int>::iterator,bool> inset_it = usedGroupIdIndexMap.insert(pair<string,int>(camp->getGroupId(),index));
		
		if(!inset_it.second)
		{
			cout<<"the gruop is camped or the index  before error:"<<endl;
			return NULL;
		}
		usefulIndexlist.pop_front();
		camp->insert(heroIdOwner);
		return camp->getGroupId();
	}
	else
	{
		size_t damamicIndex;
		ChatGroup *newGroup = NULL;
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
			cout<<"ChatGroupManager::campGroupHandle the dynamicIndex is camped or the index  before error:"<<damamicIndex<<endl;
			return NULL;
		}
		
		try
		{
			newGroup = new ChatGroup(damamicIndex);				
		}
		catch(exception e)
		{
			throw e;
		}
		
		pair<map<string,int>::iterator,bool> inset_it = usedGroupIdIndexMap.insert(pair<string,int>(newGroup->getGroupId(),damamicIndex));
		//�����쳣
		if(!inset_it.second)
		{
			cout<<"ChatGroupManager::campGroupHandle the index is exist before :"<<damamicIndex<<endl;
			delete newGroup;
			newGroup = NULL;
			return NULL;
		}
		
		//���տ�
		if(damamicIndex - groupVec.size() < dynamicGroupVec.size())
		{
			dynamicGroupVec[damamicIndex] = newGroup;
			
			//�������õĿտ�������һ��ѽ
			useAbledynamicIndex.pop_front();
		}
		//����׷��
		else
		{
			dynamicGroupVec.push_back(newGroup);
		}		
		
		newGroup->insert(heroIdOwner);
		return newGroup->getGroupId();		
	}
}

//���gruopId��Ӧ��Ⱥ���
ChatGroup* ChatGroupManager::getChatGroupHandle(const char* groupId)
{
	if(!groupId)
	{
		return NULL;
	}
	map<string,int>::iterator index_it;
	index_it = usedGroupIdIndexMap.find(groupId);
	if(index_it == usedGroupIdIndexMap.end())
	{
		return NULL;
	}
	if(index_it->second < groupVec.size())
	{
		return groupVec[index_it->second];
	}
	
	return dynamicGroupVec[index_it->second - groupVec.size()];
}

//����һ��Ⱥ
void ChatGroupManager::recoverGroupHandle(const char* groupId)
{
	if(!groupId)
	{
		return;
	}
	
	map<string,int>::iterator index_it;
	index_it = usedGroupIdIndexMap.find(groupId);
	if(index_it == usedGroupIdIndexMap.end())
	{
		cout<<"ChatGroupManager::recoverGroupHandle the groupId is error:"<<endl;
		return;
	}
	
	if(index_it->second < groupVec.size())
	{
		usefulIndexlist.push_front(index_it->second);
	}
	else
	{		
		ChatGroup *danamicNewGroup = dynamicGroupVec[index_it->second - groupVec.size()] ;	
		delete danamicNewGroup;
		danamicNewGroup = NULL;
		dynamicGroupVec[index_it->second - groupVec.size()] = NULL;
		size_t flg = usedDynamicIndex.erase(index_it->second);		
		//��������쳣���Ǿ���ԭ���
		if(flg == 0)
		{
			cout<<"ChatGroupManager::recoverGroupHandle erase the index is error:"<<index_it->second<<endl;
		}		
		useAbledynamicIndex.push_front(index_it->second);
	}		
	usedGroupIdIndexMap.erase(index_it);
}

//��������
ChatGroupManager::~ChatGroupManager()
{
	for(vector<ChatGroup*>::iterator chat_it = groupVec.begin();chat_it != groupVec.end();++chat_it)
	{
		delete *chat_it;
		*chat_it = NULL;
	}
	
	for(vector<ChatGroup*>::iterator chat_it = dynamicGroupVec.begin();chat_it != dynamicGroupVec.end();++chat_it)
	{
		delete *chat_it;
		*chat_it = NULL;
	}
	groupVec.clear();
	dynamicGroupVec.clear();
	usefulIndexlist.clear();
	usedDynamicIndex.clear();
	useAbledynamicIndex.clear();
	usedGroupIdIndexMap.clear();
	chatGroupManager = NULL;	
}
	

