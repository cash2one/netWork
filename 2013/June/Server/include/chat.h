/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�chat.h
		�ļ����ã��������캯��������
*/

#ifndef _CHAT_
#define _CHAT_

#include"command_other_function_all_over.h"
#include"hero.h"
#include<map>
#include<vector>

class Hero;
class ChatGroup;
void advertise(char* buffer);

void whisper(char* buffer);

void handsel_flowers(char *buffers);

void find_hero_by_nickName(char *buffers);

void whisperAfter(char* buffer);

//�˳�Ⱥ,����Ҫ�κ���ͬ��
void outGroup(char *buffers);

//��Ӧ�����Ⱥ
void responsePullPerson(char *buffers);

//�����Ⱥ
void pullPerson(char *buffers);

//�����Ⱥ
void pullPersonByNickName(char *buffers);

//�����Ⱥ��������
void asistPull(const Hero* inviter,const ChatGroup* chat,const int type,const vector<string> &pulledIdVec);

//�ͻ��˵�����ǰ�Ľ�����Ϊ����������id
void offNewGroupId(char *buffers);

//��ȡ��������
void gainMsgById(char *buff);

#endif
