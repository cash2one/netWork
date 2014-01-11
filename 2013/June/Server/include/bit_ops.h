/****************************************************************
 * Filename: bit_ops.h
 * 
 * Description: λͼ��һЩ��������
 *
 * Original Author : bison, 2012-6-18
 *
 ****************************************************************/
 
  
#ifndef BIT_OPS_H_
#define BIT_OPS_H_

#include<iostream>
#include <sstream>
using namespace std;

//int��λ��ƫ����
#define OFFSET 5
//���͹���
#define INT_MASK 31

typedef enum {
	SET_BIT,
	CLEAR_BIT,
	CHANGE_BIT
} BIT_OPS_T;

/********************************************************************
 * bit_ops - �����ƵĻ���λ����
 * @index:  ��Ҫ������λ
 * @bitMap: ��Ҫ������λͼ
 * @op:     ��Ҫ���Ĳ�����SET_BIT:��1��CLEAR_BIT:��0��CHANGE_BIT:ȡ��
 ********************************************************************/
inline void bit_ops(int index, void *bitMap, BIT_OPS_T op)
{
	int mask;
	unsigned *temp = (unsigned *)bitMap;
	temp += index >> OFFSET;			//unsigned λ
	mask = 1 << (index & INT_MASK);		//������λ
	switch (op)
	{
	case SET_BIT:			//��1
		*temp |= mask;
		break;
	case CLEAR_BIT:			//��0
		*temp &= ~mask;
		break;
	case CHANGE_BIT:		//ȡ��
		*temp ^= mask;
		break;
	default:
		break;
	}
}

/********************************************************************
 * test_bit - ����ĳһλ��ֵ
 * @index: 	��Ҫ���Ե�λ
 * @bitMap: ��Ҫ���Ե�λͼ
 * Return:  �����Ե�λ��ֵ
 ********************************************************************/
inline int test_bit(int index, const void *bitMap)
{
	return 1UL & (((const unsigned *) bitMap)[index >> OFFSET] >> (index & INT_MASK));
}

/********************************************************************
 * ffs - find first set,�ӵ�λ����������һ������1��λ
 * @x: �����ҵ���
 * Return: ���ص�һ������1��λ��λ��
 ********************************************************************/
inline int ffs(int x)
{
	int r = 1;
	if (!x)
	{
		return 0;
	}
	if (!(x & 0xffff))
	{
		x >>= 16;
		r += 16;
	}
	if (!(x & 0xff))
	{
		x >>= 8;
		r += 8;
	}
	if (!(x & 0xf))
	{
		x >>= 4;
		r += 4;
	}
	if (!(x & 0x3))
	{
		x >>= 2;
		r += 2;
	}
	if (!(x & 0x1))
	{
		x >>= 1;
		r += 1;
	}
	return r;
}

/********************************************************************
 * fls - find last set:�ҵ����һ������1λ��λ��
 * @x: ��Ҫ���ҵ�����
 * Return: ���һ������1��λ��λ��
 ********************************************************************/
inline int fls(int x)
{
	int r = 32;
	
	if(!x)
	{
		return 0;
	}
	if (!(x & 0xffff0000u))
	{
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u))
	{
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u))
	{
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u))
	{
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u))
	{
		x <<= 1;
		r -= 1;
	}
	return r;
}

/*************************************************************
 * ffz - find first zero:�ҵ���һ��Ϊ0��λ��
 * @x: ��Ҫ���ҵ�ֵ
 * Return: ��һ��Ϊ0��λ��
 *************************************************************/
inline int ffz(int x)
{
	int r = 0;
	while (x & 1)
	{
		x >>= 1;
		r += 1;
	}
	return r;
}


inline int ffz(long x)
{
	int r = 0;
	while (x & 1)
	{
		x >>= 1;
		r += 1;
	}
	return r;
}
/***********************************************************
 * string2int - �ַ���ת�������ͣ�����ǰ���0
 * @str: ��Ҫת�����ַ���
 * Return: ����ת������������"0023"ת������Ϊ23,"00"ת��0
 ***********************************************************/
inline int string2int(string str)
{
	int i = 0, ret = str.size();
	string dst;
	
	for (; i < ret && str[i] == '0'; i++){}
	
	if (i == ret)
	{
		return 0;
	}
	
	dst = str.substr(i);
	istringstream is(dst);
	is>>ret;
	
	return ret;
}

#endif