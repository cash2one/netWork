/****************************************************************
 * Filename: dictionary_asist.h
 * 
 * Description: �ֵ��
 *
 * Original Author : bison, 2012-10-16
 *
 ****************************************************************/
 
#ifndef _DICTIONARY_ASIST_H_
#define _DICTIONARY_ASIST_H_

#include"dictionary.h"
#include <iconv.h>
#include<string>
#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <set>
#include <map>
using namespace std;

//��ʼ�����ֵ�
void initDictionary();
//�������
bool isHaveDirtyWords(char* strToCheck);
//���α�����
bool isHaveIllSymbol(char* strToCheck);
//alpha��ʽ�ַ�������
int alphaCharLen(char* strToCheck);
#endif
