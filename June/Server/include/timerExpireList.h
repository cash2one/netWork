/****************************************************************
 * Filename: timerExpireList.h
 * 
 * Description: ��ʱ������, ����һ������ʽ��������ʱ������
 *				������ʱ�䲻ͬ�Ķ�ʱ��,
 *
 * Original Author : bison, 2012-7-17
 *
 * modified 2012-10-17������Ŀǰ���������ʱ����double�ĳ�int,�����ܲ�����ev_now
 *
 ****************************************************************/
 
#ifndef _TIMER_EXPIRE_LIST_H_
#define _TIMER_EXPIRE_LIST_H_
#include <iostream>
#include"libev.h"
#include"my_time.h"
using namespace std;
extern struct ev_loop *loops;
//��ʱ���ڵ�
template<class T>
struct timerNode_S
{
	struct timerNode_S *next;	//ǰһ�ڵ�
	struct timerNode_S *prev;	//��һ�ڵ�
	int expire; 				//����ʱ��
	T	obj;					//����
	string id;					//����id	ֹͣ���ڽ��еĶ�ʱ��ʱ��Ҫ
	
};

 
template<class T>
class TimerExpireList
{
	private:
	timerNode_S<T> *listHead;			//����ͷ
	
	public:
	TimerExpireList();
	~TimerExpireList();
	//��ǰ����Ҳ���λ�ò�����
	void push_front(int expires, T obj, string objId);
	//�Ӻ�����Ҳ���λ�ò�����
	void push_back(int expires, T obj, string objId);
	//�������絽�ڵĶ�ʱ����Ӧ�Ķ���
	//�����Ƿ��иö���id�Ľڵ�
	T find(string objId);
	//��ȡ��ʱ����ʣ��ʱ��
	int getTimerRemain(string objId);
	T pop_front();
	//δ���ڵĶ�ʱ��ֹͣʱɾ����Ӧ�Ķ���
	T delInRun(string objId);
};

template<class T>
TimerExpireList<T>::TimerExpireList()
{
	listHead = new timerNode_S<T>;
	listHead->next = listHead;
	listHead->prev = listHead;
}

template<class T>
TimerExpireList<T>::~TimerExpireList()
{
	listHead->prev->next = NULL;
	
	timerNode_S<T> *temp;
	while(listHead->next != NULL)
	{
		temp = listHead->next;
		listHead->next = listHead->next->next;
		delete temp;
	}
	
	delete listHead;
}

template<class T>
void TimerExpireList<T>::push_front(int expires, T obj, string objId)
{
	if (find(objId) != NULL)
	{
		//�����ظ�
		return;
	}
	
	cout<<"expires "<<expires<<endl;
	//double expire = expires + ev_now(loops);		//���������ʱ��
	int expire = expires + MY_TV_SEC;				//���������ʱ��
	cout<<"expire "<<expire<<endl;
	timerNode_S<T> *searchPtr = listHead->next;
	
	//Ѱ�Ҹö�ʱ��Ӧ�ò����λ��
	while(searchPtr != listHead)
	{
		if (searchPtr->expire <= expire)
		{
			searchPtr = searchPtr->next;
		}
		else 
		{
			break;
		}
	}
	
	timerNode_S<T> *listPtr = new timerNode_S<T>;
	listPtr->expire = expire;
	listPtr->id = objId;
	listPtr->obj = obj;			//����ȺŲ�֪����û�����⣬�����ָ��Ļ�û������
	//�嵽searchPtrǰ
	listPtr->next = searchPtr;
	listPtr->prev = searchPtr->prev;
	searchPtr->prev->next = listPtr;
	searchPtr->prev = listPtr;
}

template<class T>
void TimerExpireList<T>::push_back(int expires, T obj, string objId)
{
	if (find(objId) != NULL)
	{
		//�����ظ�
		return;
	}
	
	/**
	 * �õ���ʱ�̵�һ�����ô����������50�������ʱ�����Ҫ���㣬ǰ�����ev_now���ܻ����
	 */
	//double expire = expires + ev_now(loops);		//���������ʱ��
	int expire = expires + MY_TV_SEC;		//���������ʱ��
	timerNode_S<T> *searchPtr = listHead->prev;
	
	//Ѱ�Ҹö�ʱ��Ӧ�ò����λ��
	while(searchPtr != listHead)
	{
		if (searchPtr->expire > expire)
		{
			searchPtr = searchPtr->prev;
		}
		else {
			break;
		}
	}
	
	timerNode_S<T> *listPtr = new timerNode_S<T>;
	listPtr->expire = expire;
	listPtr->id = objId;
	listPtr->obj = obj;			//����ȺŲ�֪����û�����⣬�����ָ��Ļ�û������
	//�嵽searchPtr��
	listPtr->prev = searchPtr;
	listPtr->next = searchPtr->next;
	searchPtr->next->prev = listPtr;
	searchPtr->next = listPtr;
}

template<class T>
T TimerExpireList<T>::find(string objId)
{
	timerNode_S<T>* searchPtr = listHead->next;
	while(searchPtr != listHead)
	{
		if (searchPtr->id == objId)
		{
			return searchPtr->obj;
		}
		
		searchPtr = searchPtr->next;
	}
	
	return NULL;
}

template<class T>
int TimerExpireList<T>::getTimerRemain(string objId)
{
	timerNode_S<T>* searchPtr = listHead->next;
	int remain = 0;
	while(searchPtr != listHead)
	{
		if (searchPtr->id == objId)
		{
			remain = searchPtr->expire - MY_TV_SEC;
			break;
		}
		
		searchPtr = searchPtr->next;
	}
	
	return remain;
}

template<class T>
T TimerExpireList<T>::pop_front()
{
	T obj;
	timerNode_S<T> *searchPtr = listHead->next;
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

//ɾ�������еĶ�ʱ��
template<class T>
T TimerExpireList<T>::delInRun(string objId)
{
	timerNode_S<T>* searchPtr = listHead->next;
	while(searchPtr != listHead)
	{
		if (searchPtr->id == objId)
		{
			cout<<"BionTest : have find the run timer to be deleted!"<<endl;
			break;
		}
		
		searchPtr = searchPtr->next;
	}
	
	T obj;
	if (searchPtr != listHead)
	{
		obj = searchPtr->obj;
		searchPtr->next->prev = searchPtr->prev;
		searchPtr->prev->next = searchPtr->next;
		searchPtr->next = searchPtr->prev = NULL;
		delete searchPtr;
		cout<<"BionTest : have find the timer obj to be deleted!"<<endl;
		return obj; 
	}
	cout<<"BisonTest: haven't find the timer obj to be deleted!"<<endl;
	return NULL;
}

#endif