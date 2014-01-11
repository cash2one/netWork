#ifndef _DAY_LIMIT_ITEM_H_
#define _DAY_LIMIT_ITEM_H_

#include<map>
#include<string>
using namespace std;
#define MAX_DAY_LMT_ITEM_SIZE 400

//ÿ�ն�����µ�ÿ���д������Ƶ���Ŀ����ǩ�����ո��»���ճ����񣬰��������
typedef struct DayLimitItem_S
{
	char id[32];				//��ĿId
	int limit;				//��Ŀÿ������ƴ���, limitҪ���Ǵ���0
	int value;				//������Ŀ�Ѿ������Ĵ���
	
	DayLimitItem_S(char* _id, int _limit)
	{
		//id = _id;
		memset(id, 0, sizeof(id));
		strncpy(id, _id, strlen(_id));
		limit = _limit;
		value = 0;
	}
	
	//�չ���
	DayLimitItem_S(){};
	
	//�ȺŲ���
	void operator =(const DayLimitItem_S &data)
	{
		memset(id, 0, sizeof(id));
		strncpy(id, data.id, sizeof(data.id));
		limit = data.limit;
		value = data.value;
	}
	
	//�Ƿ�ﵽ������
	bool isFull()
	{
		cout<<"BisonShow id is "<<id<<endl;
		cout<<"limit is "<<limit<<" current value is "<<value<<endl;
		if (limit > value)
		{
			return false;
		}
		return true;
	}
	
	//���������Ĵ���
	bool incVal()
	{
		if (value < limit)
		{
			value++;
			return true;
		}
		return false;
	}
	
	//ÿ�յ�һ�ε�½��ʱ������Ѿ�������������Ϊ0
	void clrVal()
	{
		value = 0;
	}
	
}DayLimitItem_T;

//��������Ŀ������
typedef struct DayLmtFindGroup_S
{
	map<string, int> findMap;								//���������д����
	DayLimitItem_T dayLmtItemArr[MAX_DAY_LMT_ITEM_SIZE];	//ֻ������
	int lastUsedIndex;
	DayLmtFindGroup_S()
	{
		lastUsedIndex = 0;
	}
	void addOneItem(DayLimitItem_T item)
	{
		dayLmtItemArr[lastUsedIndex] = item;
		findMap.insert(pair<string, int>(item.id, lastUsedIndex));
		lastUsedIndex++;
	}
	
	//����ĳ�� ���ظ�������±꣬����-1ʱ��������ʧ��
	int incOneItem(string id)
	{
		map<string, int>::iterator it;
		it = findMap.find(id);
		int index = ((it == findMap.end()) ? -1 : it->second);
		if (index == -1)
		{
			return -1;
		}
		if (dayLmtItemArr[index].incVal())
		{
			return index;
		
		} else {
			return -1;
		}
	}
	
	//�ж�ĳ���Ƿ�ﵽ����
	int isOneItemFull(string id)
	{
		map<string, int>::iterator it;
		it = findMap.find(id);
		int index = ((it == findMap.end()) ? -1 : it->second);
		if (index == -1)
		{
			cout<<"BisonShow "<<id<<" is not day limit item!"<<endl;
			return -1;
		}
		return dayLmtItemArr[index].isFull();
	}
	
	int clrOneItemVal(string id)
	{
	
		map<string, int>::iterator it;
		it = findMap.find(id);
		int index = ((it == findMap.end()) ? -1 : it->second);
		if (index == -1)
		{
			cout<<"BisonShow "<<id<<" is not day limit item!"<<endl;
			return -1;
		}
		cout<<"BisonShow: the day limit item of "<<id<<" val now clear to 0"<<endl;
		dayLmtItemArr[index].clrVal();
		return index;
	}
	
	//ÿ�յ�һ�ε�½������е�valֵ
	void clrAllItemVal()
	{
		for(int i = 0; i < lastUsedIndex; i++)
		{
			dayLmtItemArr[i].clrVal();
		}
	}
	
	void items2group(DayLimitItem_T arr[], int size)
	{
		if (size > MAX_DAY_LMT_ITEM_SIZE)
		{
			//������Ҫ���ѵ���size
			return;
		}
		
		for(int i = 0; i < size; i++)
		{
			addOneItem(arr[i]);
		}
	}
	
	void group2item(DayLimitItem_T &item, int index)
	{
		item = dayLmtItemArr[index];
	}
	
	//�ȺŲ���
	void operator =(const DayLmtFindGroup_S &data)
	{
		findMap.clear();
		findMap = data.findMap;
		memcpy(dayLmtItemArr, data.dayLmtItemArr, sizeof(dayLmtItemArr));
		lastUsedIndex = data.lastUsedIndex;
	}
}DayLmtFindGroup_T;

#endif