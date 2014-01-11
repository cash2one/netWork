/************************************************************
	�ļ�����chatGroup.h
	�ļ����ã�����ChatGroup(Ⱥ���ࣩ�����Ժͳ�Ա
	���ߣ�chenzhen
	�������ڣ�2013.05.10
************************************************************/

#ifndef CHAT_GROUP
#define CHAT_GROUP
#include<iostream>
#include<set>
#include<string>
using namespace std;
const int CHAT_CROUP_ID_LEN = 50;
class ChatGroup
{
	set<string> chatHeroIdSet;
	
	char groupId[CHAT_CROUP_ID_LEN + 1];
	
	size_t index;
	
	public:
	
	ChatGroup(size_t _index);
	
	ChatGroup(const char *heroId1,const char *heroId2,size_t _index);
	
	const set<string>& getChatSet(void) const;
	
	//���뷵��boolֵ
	bool insert(const char *heroId);
	
	//���뷵��boolֵ
	bool erase(const char *heroId);
	
	size_t size(void) const;
	
	bool empty() const;
	
	const char* getGroupId(void) const;
	
	size_t getIndex(void) const;
	
	//������Ϣ
	void sendMsg(const char* chatMsg) const;
	
	//�жϴ����Ƿ���Ⱥ��
	bool isInGroup(const char *heroId) const;
	
	//��������
	~ChatGroup();
	
	private:
	
	//ע�⣬id���Բ��ܳ�ͻ,�ҷ�ֹ�������������ⲿ����
    ChatGroup(const ChatGroup &chatGroup);
	 
	 //ע�⣬id���Բ��ܳ�ͻ,�ҷ�ֹ�������������ⲿ����
	ChatGroup& operator=(const ChatGroup &chatGroup);
	
	void creatGroupId();
	
	void init();
};
#endif
	