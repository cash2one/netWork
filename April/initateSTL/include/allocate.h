/************************************************************
	�ļ�����allocate.h
	�ļ����ã���Allocate������Ժͷ���������
	���ߣ�chenzhen
	�������ڣ�2013.04.01
************************************************************/

#ifndef ALLOCATE_H
#define ALLOCATE_H
#include<stdlib.h>
using namespace std;

template<typename Tp>
inline void _construct(Tp *ptr,const Tp& values)
{
	new(ptr) Tp(values);
}

template<typename Tp>
inline void _delete(Tp *ptr)
{
	ptr->~Tp();
}

template<typename Tp>
struct Allocate
{
	typedef Tp* point_type;
	
	Tp* allocate(size_t n)
	{
		Tp *start = (Tp*)malloc(sizeof(Tp) * n);
		return start;
	}
	
	Tp* allocate(void)
	{
		Tp *start = (Tp*)malloc(sizeof(Tp));
		return start;
	}
	
	void deallocate(Tp *ptr)
	{
		free(ptr);
	}
};

#endif