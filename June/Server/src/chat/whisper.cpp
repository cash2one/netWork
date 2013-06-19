/*
		�ļ����ͣ�ʵ���ļ�
		�ļ����ƣ�whisper.cpp
		�ļ����ã�ʵ��˽�ĵ���Ϣ���ͣ�
		�޸��ˣ�xhm
		�޸�ʱ�䣺2012.8.30 13:56
*/

#include"chat.h"
//���������������
#include "my_mem_group.h"

#include"chatGroupManager.h"
#include"chatGroup.h"

extern ChatGroupManager *chatManager;
extern int sock_fd;
extern Hero* pg_hero;
extern int g_msg_len;
extern set<string> ban_speak;
extern map<string, Hero*> heroId_to_pHero;

//�����ǳƼ�黺��Ĳ�����ָ��ʵ����������
extern MyMemcache* mem_operate_nickname_inspection;
extern MyMemGroup* mem_group;

static char whisperInfo[2048];



void whisper(char *buffers)
{	
    /*
	   �����ͻ��˷��͹������ݣ����ҽ����͸��ͻ��˵����ݱ��浽msg�������棻
    */
	Hero* wisperHero=NULL;//˽�Ķ����heroʵ����

	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(char* my_hero_id);//��ȡ��������Ϣ��
	MSG_CHAR(char* desHeroId);//��ȡ˽�Ķ����ID��
	MSG_CHAR_END(char* msgInfo);//��ȡ��Ϣ���ݣ�
	
	/*add chenzhen 20130312,�Լ����������Լ�����*/
	if(strncmp(my_hero_id,desHeroId,strlen(my_hero_id)) == 0)
	{
		snprintf(whisperInfo,2047,"4,23,7");//�Լ����������Լ����죻
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}
	if(MAX_MESSAGE_DATA_LEN < strlen(msgInfo))
	{
		snprintf(whisperInfo,2047,"4,21,2");//���ݴ���
		send_msg(pg_hero->getFd(),whisperInfo);		
		cout<<"[XHM WARNING] The whisper msgInfo is more than MAX_MESSAGE_DATA_LEN<whisper.cpp>!"<<endl;
		return;
	}	
	
	//���ӽ����жϣ�
	set<string>::iterator iterSet = ban_speak.find(my_hero_id);
	if(iterSet != ban_speak.end())
	{
		cout<<"[XHM WARNING] The whisper hero in the ban_speak<whisper.cpp>!"<<endl;
		snprintf(whisperInfo,2047,"4,23,1");//���ӽ��ԣ�
		send_msg(pg_hero->getFd(),whisperInfo);		
		return;
	}
	
	map<string,Hero*>::iterator iter=heroId_to_pHero.find(desHeroId);
	if(iter==heroId_to_pHero.end())
	{
		snprintf(whisperInfo,2047,"4,23,2");//��Ҳ�����
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}	
	
	wisperHero=iter->second;
	if(!wisperHero->getFriendInfo())
	{
		cout<<"void whisper(char *buffers) getFriendInfo is NULL:"<<endl;
		return;
	}
	
	if(wisperHero->getFriendInfo()->isInBlack(pg_hero->getIdentity()))
	{
		cout<<"void whisper(char *buffers) the you is in his blackList:"<<endl;
		return;
	}
	
	
	snprintf(whisperInfo,2047,"4,11,%s,%s,%s",my_hero_id,pg_hero->getNickName(),msgInfo);	
	if(NULL != wisperHero)//������Ϣ��
		send_msg(wisperHero->getFd(),whisperInfo);	
	
}



//����˽�ģ�����Ⱥ�ģ�����������캯����������ԭ�Ǻ�����ǰ��ģ�����ά����������
void whisperAfter(char *buffers)
{
	char* my_hero_id,*msgInfo,*chatId;
	

	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);//��ȡ��������Ϣ��
	MSG_CHAR(chatId); //��ȡ����id��
	MSG_CHAR_END(msgInfo);//��ȡ��Ϣ���ݣ�
	
	if(MAX_MESSAGE_DATA_LEN < strlen(msgInfo))
	{
		snprintf(whisperInfo,2047,"35,0,1");//���ݴ���
		send_msg(pg_hero->getFd(),whisperInfo);		
		cout<<"[XHM WARNING] The whisper msgInfo is more than MAX_MESSAGE_DATA_LEN<whisper.cpp>!"<<endl;
		return;
	}	
	
	//���ӽ����жϣ�
	set<string>::iterator iterSet = ban_speak.find(my_hero_id);
	if(iterSet != ban_speak.end())
	{
		cout<<"[XHM WARNING] The whisper hero in the ban_speak<whisper.cpp>!"<<endl;
		snprintf(whisperInfo,2047,"35,0,2");//���ӽ��ԣ�
		send_msg(pg_hero->getFd(),whisperInfo);		
		return;
	}	
	
	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);
	
	if(!chat)
	{
		cout<<"chat is NULL:"<<chatId<<endl;
		return;
	}
	
	//����Ⱥ��
	if(!chat->isInGroup(my_hero_id))
	{
		snprintf(whisperInfo,2047,"35,0,3");
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}
	
	snprintf(whisperInfo,2047,"35,1,1,%s,%s,%s,%s",my_hero_id,pg_hero->getNickName(),chatId,msgInfo);	
	
	//������Ϣ
	chat->sendMsg(whisperInfo);
}


//�ͻ��˵�����ǰ�Ľ�����Ϊ����������id
void offNewGroupId(char *buffers)
{
	char* my_hero_id,*pulledId;	

	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);//��ȡ��������Ϣ
	MSG_CHAR_END(pulledId); //˽��id��
	
	char *chatId = const_cast<char*>(chatManager->campGroupHandle(my_hero_id));
	if(!chatId)
	{
		cout<<"pullPerson the chatId is NULL:"<<endl;
		return;
	}	

	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);		
	pg_hero->insertGroupId(chatId);
	chat->insert(my_hero_id);
	chat->insert(pulledId);
	
	//���ÿͻ��˵��������id
	snprintf(whisperInfo,2047,"35,2,0,%s",chatId);
	send_msg(pg_hero->getFd(),whisperInfo);			
	
	return;	

}

/* 
* describe:�Ϸ���Ҫ�鿴�ǳƶ�Ӧ�Ľ�ɫ��Ϣ����ָ���ǳ����ڵ��� db_zone
*/
void find_hero_by_nickName(char *buffers){

	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR_END(char* nick_name);//��ȡ��Ϣ���ݣ�
	cout<<"[XHM TEST] find_hero_by_nickName:"<<nick_name<<endl;	

	//TODO �����������Ҫɾ����
 	int nickname_inspection_size = 0;
	char* result = mem_operate_nickname_inspection->get_mem_data(nick_name, &nickname_inspection_size); 
	if(result != NULL)
	{
		map<string,Hero*>::iterator iter=heroId_to_pHero.find(result);
		if(iter==heroId_to_pHero.end())
		{	
			//������������һ��
			int size = 0;
			int where = 0;
			// MemHero* myHeroData=(MemHero*)mem_operate->get_mem_data(result,&size); tory modify 2013.3.18
			MemHero* myHeroData = (MemHero*)mem_group->get_data(result, &size, &where);
			if(NULL != myHeroData)
			{	
				sprintf(whisperInfo, "4,24,1,%s,%s,%d,%d",result,myHeroData->basicHeroData.party,myHeroData->level,myHeroData->camp);//�����ߣ�	���ɣ��ȼ�����Ӫ��״̬�� 
			}else{
				sprintf(whisperInfo, "4,24,3,%s,N,0,-1",result);//�����ߣ�	���ɣ��ȼ�����Ӫ��״̬�� 			
			}
		}else{
			sprintf(whisperInfo, "4,24,0,%s,%s,%d,%d",result,(iter->second)->getParty(),(iter->second)->getGradeNow(),(iter->second)->getCamp());//���ߣ�				
		}
		free(result);
	}else{
		sprintf(whisperInfo, "4,24,2",result);//�����ڣ�
		
	}
	
	send_msg(sock_fd, whisperInfo); 
}

//�����Ⱥ
void pullPerson(char *buffers)
{
	int num;
	char *my_hero_id,*pulledHeroId,*chatId;
	vector<string> pulledIdVec;
	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);
	MSG_INT(num);         //��������������
	for(size_t person = 0;person < num;++person)
	{
		MSG_CHAR(pulledHeroId);//����������������id
		pulledIdVec.push_back(pulledHeroId);
	}
	MSG_CHAR_END(chatId);//����Ⱥid
	
	if(pulledIdVec.empty())
	{
		cout<<"pullPerson pulledIdVec is emmpty:"<<endl;
		return;
	}
	
	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);
	
	if(!chat)
	{
		snprintf(whisperInfo,2047,"35,0,7");//��Ⱥ������
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;
	}
	
	if(!chat->isInGroup(my_hero_id))
	{
		snprintf(whisperInfo,2047,"35,0,6");//�����˵����û���ڴ�Ⱥ��
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;				
	}
	
	asistPull(pg_hero,chat,1,pulledIdVec);
	
}

//�����Ⱥ
void pullPersonByNickName(char *buffers)
{
	int num;
	char *my_hero_id,*chatId,*nickName;
	vector<string> pulledNickNameVec;
	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);
	MSG_INT(num);         //��������������
	for(size_t person = 0;person < num;++person)
	{
		MSG_CHAR(nickName);//�����������������ǳ�
		pulledNickNameVec.push_back(nickName);
	}
	MSG_CHAR_END(chatId);//����Ⱥid
	
	if(pulledNickNameVec.empty())
	{
		cout<<"pullPersonByNickName pulledNickNameVec is emmpty:"<<endl;
		return;
	}
	
	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);
	
	if(!chat)
	{
		snprintf(whisperInfo,2047,"35,0,7");  //��Ⱥ������
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;
	}	
	
	if(!chat->isInGroup(my_hero_id))
	{
		snprintf(whisperInfo,2047,"35,0,6");  //�����˵����û���ڴ�Ⱥ��
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;					
	}
	asistPull(pg_hero,chat,0,pulledNickNameVec);
}

//��Ӧ�����Ⱥ
void responsePullPerson(char *buffers)
{
	char *my_hero_id,*chatId;
	int type;
	
	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);
	MSG_INT(type);
	MSG_CHAR_END(chatId);//����Ⱥid
	

	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);
	if(!chat)
	{
		snprintf(whisperInfo,2047,"35,0,7");//��Ⱥ������
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}
	
	//��������
	if(type < 0 || type > 1)
	{
		cout<<"	responsePullPerson the type argument is error:"<<endl;
		return;	
	}
	
	snprintf(whisperInfo,2047,"35,1,3,%d,%s,%s",type,my_hero_id,pg_hero->getNickName());//Ⱥ��Ϣ
	
	//ͬ���Ⱥ
	if(type == 1)
	{
		pg_hero->insertGroupId(chatId);		
	}
	
	chat->sendMsg(whisperInfo);	
}

//�˳�Ⱥ,����Ҫ�κ���ͬ��
void outGroup(char *buffers)
{
	char *my_hero_id,*chatId;
	
	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);
	MSG_CHAR_END(chatId);//����Ⱥid
	

	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);
	if(!chat)
	{
		snprintf(whisperInfo,2047,"35,0,7");//��Ⱥ������
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}
	
	if(!chat->isInGroup(my_hero_id))
	{
		snprintf(whisperInfo,2047,"35,0,3");//���û���ڴ�Ⱥ��
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}
	
	pg_hero->eraseGroupId(chatId);
	
	snprintf(whisperInfo,2047,"35,1,4,%s,%s",my_hero_id,pg_hero->getNickName());
	
	chat->sendMsg(whisperInfo);	
	
	chat->erase(my_hero_id);
	
	//����Ⱥ
	if(chat->empty())
	{
		chatManager->recoverGroupHandle(chatId);
	}
	
}

//�����Ⱥ��������
void asistPull(const Hero* inviter,const ChatGroup* chat,const int type,const vector<string> &pulledIdVec)
{
	if(!inviter || !chat || pulledIdVec.empty() || type > 1 || type < 0 )
	{
		cout<<"asistPull the argument is error:"<<endl;
		return;
	}	
		
	for(vector<string>::const_iterator invited = pulledIdVec.begin();invited != pulledIdVec.begin();++invited)
	{
		char tempId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'},chatMsg[300] = {'\0'};
		
		//type 0 ��ʾvectorװ�Ķ����ǳƣ�����Ϊid
		if(type == 0)
		{
			int nickname_inspection_size = 0;			
			char* result = mem_operate_nickname_inspection->get_mem_data((*invited).c_str(), &nickname_inspection_size); 
			if(result == NULL)
			{
				snprintf(chatMsg,2047,"35,0,5"); //������Ҳ�����
				send_msg(inviter->getFd(),chatMsg);	
				continue;			
			}
			strncpy(tempId,result,strlen(result));
			free(result);
		}
		else
		{
			strncpy(tempId,(*invited).c_str(),strlen((*invited).c_str()));
		}
	
		Hero *invitedHero = heroid_to_hero(tempId);
		
		if(strncmp(inviter->getIdentity(),tempId,strlen(tempId)) == 0)
		{
			snprintf(chatMsg,2047,"35,0,4");//�Լ��������Լ���Ⱥ��
			send_msg(inviter->getFd(),chatMsg);			
			continue;	
		}
		
		if(!invitedHero)
		{
			if(chat->isInGroup(tempId))
			{
				snprintf(chatMsg,2047,"35,0,8");//����ڴ�Ⱥ��
				send_msg(inviter->getFd(),chatMsg);		
				continue;
			}
			else
			{
		
				snprintf(chatMsg,sizeof(chatMsg),"35,1,1,%s,%s,%s",inviter->getIdentity(),inviter->getNickName(),tempId,chat->getGroupId());
				//ĳ������ĳ�˽�ĳ��Ⱥ		
				send_msg(invitedHero->getFd(),chatMsg);
			}
		}
		else
		{
			snprintf(chatMsg,2047,"35,0,5");//������Ҳ�����
			send_msg(inviter->getFd(),chatMsg);	
		}
	}
}

//��ȡ��������
void gainMsgById(char *buffers)
{
	char *msgHeroId;
	MSG_BEGIN(buffers,g_msg_len);
	MSG_CHAR_END(msgHeroId);
	int onLine = 0;
	
	//���ݴ���
	if(!msgHeroId)
	{
		sprintf(whisperInfo,"4,1,1");
		send_msg(pg_hero->getFd(),whisperInfo);
		return;
	}
	
	Hero *msgHero = heroid_to_hero(msgHeroId);	
	MemHero *memHero;
	
	if(!msgHero)
	{
		int size = 0;
		int where = 0;
		char *pmem = mem_group->get_data(msgHeroId, &size, &where);
		if(pmem == NULL)
		{
			sprintf(whisperInfo,"4,1,2");     //���˲�����
			send_msg(pg_hero->getFd(),whisperInfo);
			return;
		}
	
		memHero = (MemHero *)malloc(sizeof(MemHero));
		memset(memHero, '\0', sizeof(MemHero));
    
		size = size < sizeof(MemHero) ? size : sizeof(MemHero);
		memcpy(memHero, pmem, size);
		free(pmem);
	}
	else
	{
		memHero = msgHero->memHero;
		onLine = 1;
	}
	sprintf(whisperInfo,"4,1,0,%s,%s,%d,%d,%d,%s,%d",msgHeroId,memHero->nickName,memHero->level,memHero->vipDailyData.stage,memHero->camp,\
	memHero->basicHeroData.party,onLine);
	send_msg(pg_hero->getFd(),whisperInfo);
}
	
	
