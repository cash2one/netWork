/* 
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�npc.h
		�ļ����ã�NPCʵ����npc�������Լ������Ķ���
		���ʱ�䣺2012.5.10
		  ����ˣ�Evan
*/

#ifndef NPC_H
#define NPC_H
#include<string>
#include<set>
#include"data_structure_struct.h"
class Npc
{
private:  
	string npc_id;//npcid
	//string npc_name;  //npc����
	char   *mapId;       				//��ͼid
	Point  standpoint;             			//npc���ڵ�ͼ�����ص�/�߼���

public:
	Npc(string _npc_id);
};
#endif

