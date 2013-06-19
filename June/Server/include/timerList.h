/****************************************************************
 * Filename: timerList.h
 * 
 * Description: ��ʱ������, ������ʱ�䲻ͬ�Ķ�ʱ����
 *				����ʱ��ʣ��ʱ������
 *
 * Original Author : bison, 2012-7-17
 *
 ****************************************************************/
 
#ifndef _TIMER_LIST_H_
#define _TIMER_LIST_H_

#include"libev.h"

//��ʱ���ڵ�
template<class T>
struct timerNode
{
	struct timerNode *next;	//ǰһ�ڵ�
	struct timerNode *prev;	//��һ�ڵ�
	double remaining;			//ʣ��ʱ��
	ev_timer *timer;			//��ʱ��
	T	obj;					//����
	string id;					//����id	ֹͣ���ڽ��еĶ�ʱ��ʱ��Ҫ
	
};

template<class T>
class TimerList
{
	private:
	timerNode<T> *listHead;			//����ͷ
	
	public:
	TimerList();
	~TimerList();
	
	//�����Ƿ��иö���id�Ľڵ�
	bool find(string objId);
	//��ǰ����Ҳ���λ�ò�����
	void push_front(ev_timer *timer, T obj, string objId);
	//�������絽�ڵĶ�ʱ����Ӧ�Ķ���
	T pop_front();
	//δ���ڵĶ�ʱ��ֹͣʱɾ����Ӧ�Ķ���
	T delInRun(string objId);
};

template<class T>
TimerList<T>::TimerList()
{
	listHead = new timerNode<T>;
	listHead->next = listHead;
	listHead->prev = listHead;
}

template<class T>
TimerList<T>::~TimerList()
{
	listHead->prev->next = NULL;
	
	timerNode<T> *temp;
	while(listHead->next != NULL)
	{
		temp = listHead->next;
		listHead->next = listHead->next->next;
		delete temp;
	}
	
	delete listHead;
}

template<class T>
void TimerList<T>::push_front(ev_timer *timer, T obj, string objId)
{
	if (find(objId) != false)
	{
		//�����ظ�
		return;
	}
	
	double remain =  ev_timer_remaining(loops, timer);
	timerNode<T> *searchPtr = listHead->next;
	
	//�Ҳ���λ��ǰ�ȸ��µ�һ���ڵ�Ķ�ʱ��ʣ��ʱ��
	if (searchPtr != listHead)
	{
		searchPtr->remaining = ev_timer_remaining(loops, searchPtr->timer);
	}
	
	bool done = true;
	//Ѱ�Ҹö�ʱ��Ӧ�ò����λ��
	while( done && searchPtr != listHead)
	{
		if (searchPtr->remaining <= remain)
		{
			remain -= searchPtr->remaining;
			searchPtr = searchPtr->next;
		} else {
			searchPtr->remaining -= remain;
			done = false;
		}
	}
	
	timerNode<T> *listPtr = new timerNode<T>;
	listPtr->remaining = remain;
	listPtr->id = objId;
	listPtr->obj = obj;			//����ȺŲ�֪����û�����⣬�����ָ��Ļ�û������
	//�嵽searchPtrǰ
	listPtr->next = searchPtr;
	listPtr->prev = searchPtr->prev;
	searchPtr->prev->next = listPtr;
	searchPtr->prev = listPtr;
}

template<class T>
bool TimerList<T>::find(string objId)
{
	timerNode<T>* searchPtr = listHead->next;
	while(searchPtr != listHead)
	{
		if (searchPtr->id == objId)
		{
			return true;
		}
		
		searchPtr = searchPtr->next;
	}
	
	return false;
}

template<class T>
T TimerList<T>::pop_front()
{
	T obj;
	timerNode<T> *searchPtr = listHead->next;
	if (searchPtr != listHead)
	{
		obj = searchPtr->obj;
		listHead->next = searchPtr->next;
		searchPtr->next->prev = listHead;
		searchPtr->next = searchPtr->prev = NULL;
		delete searchPtr;
		
		return obj; 
	}
	
	return NULL;
}

template<class T>
T TimerList<T>::delInRun(string objId)
{
	timerNode<T>* searchPtr = listHead->next;
	while(searchPtr != listHead)
	{
		if (searchPtr->id == objId)
		{
			break;
		}
		
		searchPtr = searchPtr->next;
	}
	
	T obj;
	if (searchPtr != listHead)
	{
		obj = searchPtr->obj;
		
		//�������searchPtr���滹�нڵ㣬��ʣ�ൽ��ʱ��ӵ�����
		if (searchPtr->next != listHead)
		{
			searchPtr->next->remaining += searchPtr->remaining;
		}
		searchPtr->next->prev = searchPtr->prev;
		searchPtr->prev->next = searchPtr->next;
		searchPtr->next = searchPtr->prev = NULL;
		delete searchPtr;
		
		return obj; 
	}
	return NULL;
}

#endif