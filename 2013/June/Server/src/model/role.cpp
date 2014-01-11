/*
        �ļ����ͣ�ʵ���ļ�
        �ļ����ƣ�role.cpp
        �ļ����ã�ʵ����Role����ĳ�Ա����
*/
#include"role.h"
#include"other_define_data.h"
//�û���ɫ����������ͷ�ļ�
#include"user_role_manage_assist.h"			
//���й��ߺ�����ͷ�ļ�
#include"command_other_function_all_over.h"	
#include"hero_configuration.h"
#include<iostream>
#include<map>
#include"command_user_role_manage.h"
#include"skill.h"
#include"skill_configuration.h"
#include"hero_help.h"
#include"user_role_manage_growup.h"
#include"bottle.h"
#include"trap.h"
#include"monsterBase.h"
#include"heroCpyRecord.h"
#include"boxAsist.h"

//���������
#include "my_memcached.h"
//���������������
#include "my_mem_group.h"

extern MyMemGroup* mem_group;
//���������ʵ��ָ�룬ȫ�ֱ���
// extern MyMemcache* mem_operate;

//����������Hero ID����Hero����ָ���map���������������ѳ�ʼ����Hero����
extern map<string, Hero*> heroId_to_pHero;

extern map<string,Skill_Configuration*>id_to_skill;

extern map<string,Pick*> goods_to_hero;

//�����ǳƼ�黺��Ĳ�����ָ��ʵ����������
extern MyMemcache* mem_operate_nickname_inspection;

extern NickName2heroIdHash heroNameCheckHash;

extern char server_name[10];

Role::Role()
{
	strncpy(user.userName, "unknow", MAX_NAME_LEN+1);
	strncpy(user.passWord, "unknow", MAX_WORD_LEN+1);
	
    connect_fd = -1;  				//fd
    isLogin = false;               	//�Ƿ��½��־��true��ʾ�ѵ�½				
    active_hero = NULL;             //��ǰ���ɫָ��
	
    memRole = (MemRole*)malloc(sizeof(MemRole));
    if(memRole == NULL)
    {
        printf("exit from Role(),cause out of memory" );
        exit(1);
    }
	
    memRole->user = user;
    memRole->idSize = 0;
	
	memset(memRole->cardId,'\0',sizeof(memRole->cardId));
}

//����δ���ڵ��û���½��Ϸʱ����ʼ���µ��û�����
void Role::initNewRole(UserInform &_user, int _connect_fd, int _where)
{
    user = _user;
	where = _where;
    this->connect_fd = _connect_fd;  //fd
    isLogin = true;                 //�Ƿ��½��־��true��ʾ�ѵ�½				
    active_hero = NULL;             //��ǰ���ɫָ��
	
    memRole->user = user;
    memRole->idSize = 0;
	hero_infor_list.clear();	//tory modify 2013.1.30
}

/**************************************
* Author:	Tory
* Date	:	2012.10.13
* Amend :	
* Description�������Ѵ��ڵ��û���½ʱ����memcached server����ȡ�û�������game server��
***************************************/
void Role::loadRoleData(MemRole *_memRole, int _connect_fd, int _where)
{
	memmove(memRole, _memRole, sizeof(MemRole));
	user = memRole->user;           //�û�����
    
	where = _where;
    this->connect_fd = _connect_fd;  //fd
    isLogin = true;                 //�Ƿ��½��־��true��ʾ�ѵ�½				
    active_hero = NULL;             //��ǰ���ɫָ��	

    //����������н�ɫ��Ϣ����game server�е�hero_infor_list������
	if(memRole->idSize > 4 || memRole->idSize < 0)	//tory add 2012.12.18
	{
		memRole->idSize = 0;		
	}
	
	hero_infor_list.clear();	//tory modify 2013.1.30
	int i = 0;
    for(i; i < memRole->idSize&&i < 4; i++)	//tory modify 2012.12.25
    {        
		hero_infor_list.push_back(memRole->my_hero_infor_list[i]);  
    }

}

/*
* Author:	Cookie
* Date	:	2012.9.12
* Amend :	Tory ���ߺ���
* Description����Ҫ��memcached server�д洢memRole����ʱ����
*/
void Role::memSet(void)
{
    // bool isSuccess = mem_operate->set_mem_data(user.userName, (char*)memRole, (int)sizeof(MemRole));
    // if(isSuccess == true)
    // {
        // cout<<"set memRole into memcached server success"<<endl;
    // } else
    // {
        // cout<<"set memRole into memcached server failure"<<endl;
    // }
	
	bool isSuccess = mem_group->set_data(user.userName, (char*)memRole, (int)sizeof(MemRole), Role::where);
    if(isSuccess == true)
    {
        cout<<"set memRole into memcached server success"<<endl;
    } else
    {
        cout<<"set memRole into memcached server failure"<<endl;
    }

}

/*
* Author:	Tory
* Date	:	2012.9.12
* Amend :	
* Description����Ҵ����½�ɫʱ�����´����Ľ�ɫIDͬʱ����game_server ��heroId_set��memRole��
*/
void Role::addHeroInfor(My_hero_infor &hero_infor)
{
    if(Role::memRole->idSize >= ROLETOP)
    {
        return;
    } else
    {
		//���´����Ľ�ɫ
        switch(Role::memRole->idSize)	
        {
        case 0:
            memRole->my_hero_infor_list[0] = hero_infor;
            cout<<"100000000000 "<<endl;
            break;
        case 1:
            memRole->my_hero_infor_list[1] = hero_infor;
			cout<<"200000000000 "<<endl;
            break;
        case 2:	
            memRole->my_hero_infor_list[2] = hero_infor;
            cout<<"300000000000 "<<endl;
            break;
        case 3:	
			memRole->my_hero_infor_list[3] = hero_infor;
            cout<<"400000000000 "<<endl;
            break;
        default :
            cout<<"wrong in role.cpp:153"<<endl;
            break;
        }
    
		Role::memRole->idSize++ ;  

    }
}


/*
* Author:	Tory
* Date	:	2012.9.12
* Description����heroId��Ӧ��memHero���ݴ�memcached serverɾ���󣬸���memRole�еĽ�ɫ�б�
*/
void Role::deleteHero(char *heroId)
{
	if(heroId==NULL || strlen(heroId)==0)
	{
		return;
	}
	
	int index = 0;
	for(index; index < memRole->idSize; index++)
	{
		My_hero_infor my_hero_infor = memRole->my_hero_infor_list[index];
		//�ҵ�Ҫɾ����ɫ��id��memRole.my_hero_infor_list�±꣬����ѭ��	
		if(strcmp(heroId, my_hero_infor.heroId) == 0)
		{
			break;			
		}
	}	
	// ��Ҫɾ���Ľ�ɫ�±�������ʼ�������Ժ�Ľ�ɫ��Ϣ������ǰ�ƶ�������߼�ò���ڿ�������������tory
	if(index < 4)
	{
		memRole->idSize--;//���ɾ�����ĸ���ɫ�������ǰ�idsize��ȥ1���һ���Ϊ����memRole->my_hero_infor_list[index+1]��Խ�硣
		for(index; index < memRole->idSize; index++)
		{
			memRole->my_hero_infor_list[index] = memRole->my_hero_infor_list[index+1];		
		}
	}

	if(hero_infor_list.size()<=0)	//xhm add 2012.12.25
	{
		return;
	}
	
	list<My_hero_infor>::iterator iter = hero_infor_list.begin();//tory modify 2012.12.25
	for(iter; iter != hero_infor_list.end(); iter++)
	{
		My_hero_infor my_hero_infor = *iter;
		if(strcmp(heroId, my_hero_infor.heroId) == 0)	
		{
			hero_infor_list.erase(iter);
			
			// NickName2heroIdHash::iterator sameNameiter = heroNameCheckHash.find(my_hero_infor.nickName);
			// if(sameNameiter != heroNameCheckHash.end())
			// {
				// heroNameCheckHash.erase(sameNameiter);
			// }	
			
			/**
				*ɾ���û�����Ӧ��heroId��������RTX xhm����Ҫɾ����
			*/
			// bool erase_name_inspeciton = mem_operate_nickname_inspection->delete_mem_data(my_hero_infor.nickName);
			// if(!erase_name_inspeciton)
			// {
				// puts("[XHM WARNING] mem_operate_nickname_inspection delete_mem_data nickname ERROR.");
			// }
			break;
		}
	}
	
	
	/********************* add start xhm *****************	
	//hashmapͬ������޸ģ��벻Ҫɾ����
	if(strcmp(heroId,memRole->role4)==0)
    {
		NickName2heroIdHash::iterator nameiter = heroNameCheckHash.find(memRole->nickName4);
		if(nameiter != heroNameCheckHash.end())
		{
			heroNameCheckHash.erase(nameiter);	
		}
    }
	
	/********************* add end xhm *****************/

	//memRole�����Ѹ��£������º������������memcached server
	memSet();	
}

char* Role::getUserName(void)
{
    return user.userName; 
}


//�������Ѵ����Ľ�ɫ��Ϣ�б�
list<My_hero_infor>& Role::getHero_infor_list()
{
	return hero_infor_list;
} 

void Role::setLoginState(bool _isLogin)     //���õ�½״̬
{
    isLogin = _isLogin;
}
bool Role::getLoginState()                  //��õ�½״̬
{
    return isLogin;
}

string  Role::getActive_heroId()            //��ȡ��ǰ���ɫID
{
    return active_heroId;
}
void    Role::setActive_heroId(string heroId)//���õ�ǰ���ɫID
{
    active_heroId = heroId;
}

//���û��ɫָ��
void Role::setActive_hero(Hero *_active_hero)                
{
    active_hero = _active_hero;
}

//��û��ɫָ��
Hero*   Role::getActive_hero()              
{
    return active_hero;
}

/*
* Author: tory
* Date	: 2012.
  @ party:�ͻ��˷��͹��������ɣ�Ϊ����+A(�ӵ���A)
  @ nickName:�ǳ�
  @ heroTypeId����ʱ��ʵ�����壬�����պ���չ
*/
Hero* Role::create_hero(char *party, char *nickname, char *heroTypeId)        
{
    if(hero_infor_list.size() > 4)//xhm add warning msg;
	{
		cout<<"[XHM WARNING] The hero_infor_list.size():"<<hero_infor_list.size()<<endl;	
		return NULL;  //�ж���Ҵ����Ľ�ɫ��Ŀ�Ƿ��ѵ�����	
	}

	party[1] = '\0';	//�ͻ��˷����������ɸ�ʽ������+A,�绪ɽ��Ϊ��HA,�ӵ����轫Aȥ��������
	cout<<"@@Tory 1000000 party:"<<party<<endl;
	Hero *myHero = new Hero(nickname, party, Role::where);
	
    //�´������ɫ���������memRole������Ҫ�޸ģ������memcached server�е�memRole�� Tory add
	char photoId[IDL] = {"HM00101"};	//H-->Hero��M-->Party��00101-->��������
	photoId[1] = *party;

	My_hero_infor heroInfor(myHero->getIdentity(), nickname, party, photoId);
	hero_infor_list.push_back(heroInfor);
	Role::addHeroInfor(heroInfor);
    return myHero;	
}

My_hero_infor Role::getHeroInfor(char *heroId)
{
	int index = 0;
	for(index; index < memRole->idSize; index++)
	{
		My_hero_infor my_hero_infor = memRole->my_hero_infor_list[index];
		if(strcmp(heroId, my_hero_infor.heroId) == 0)
		{			//�ҵ�Ҫɾ����ɫ��id��memRole.my_hero_infor_list�±꣬����ѭ��	
			return my_hero_infor;
		}
	}
}


void	Role::setNickName(char *_nickName,char *heroId)
{
	if (_nickName==NULL||heroId==NULL)
	{
		return;
	}
	int index = 0;
	for(index; index < memRole->idSize; index++)
	{
		My_hero_infor my_hero_infor = memRole->my_hero_infor_list[index];
		if(strcmp(heroId, my_hero_infor.heroId) == 0)
		{					
			// cout<<"heroInfor.nickName before is "<<heroInfor.nickName<<endl;
			strncpy(memRole->my_hero_infor_list[index].nickName, _nickName, MAX_NAME_LEN+1);
			// cout<<"heroInfor.nickName after  is "<<heroInfor.nickName<<endl;
		}
	}
	memSet();
}

/*��ɫ�������*/
bool Role::useCardId(char *cardId)
{
	if(cardId == NULL || strlen(cardId) == 0)
	{
		cout<<"the card of argument cardId is NULL or empty:"<<endl;
		return false;
	}
	if(strlen(memRole->cardId) == 0)
	{
		strncpy(memRole->cardId,cardId,strlen(cardId));
		return true;
	}
	if(strcmp(memRole->cardId,cardId) == 0)
	{
		return true;
	}
	return false;
}

/*�Ƿ����ù�������*/
bool Role::isUseCard(void)
{
	if(strlen(memRole->cardId) == 0)
	{
		return false;
	}
	return true;
}


//�����û���
bool Role::changeUserName(char* newName)
{
	char log_msg[1024] = {0};
	
	//������ʱ�û�����ʱ��дһ����־
	sprintf(log_msg,"20,0,%s,%ld,%s,%s", server_name, MY_TV_SEC, user.userName, newName);
	write_log(log_msg);	
	strncpy(user.userName, newName, MAX_NAME_LEN+1);
	memRole->user = user;
	// cout<<"memRole's user name is "<<memRole->user.userName<<endl;
	int size = hero_infor_list.size();
	list<My_hero_infor>::iterator it_info = hero_infor_list.begin();
	for (int i = 0; i < size; i++, it_info++)
	{
		memRole->my_hero_infor_list[i] = *it_info;
	}
	
	memSet();
	
	// int size1 = 0;
	
	// MemRole *testMemRole = (MemRole*)mem_operate->get_mem_data(newName, &size1);
	// if (testMemRole == NULL)
	// {
		// cout<<"333333333333333333333333333333333333333333333333"<<endl;
		// cout<<"333333333333333333333333333333333333333333333333"<<endl;
		// cout<<"333333333333333333333333333333333333333333333333"<<endl;
	// } else {
		// cout<<"4444444444444444444444444444444444444444444444444444"<<endl;
		// cout<<"4444444444444444444444444444444444444444444444444444"<<endl;
		// cout<<"4444444444444444444444444444444444444444444444444444"<<endl;
		// cout<<"userName is "<<testMemRole->user.userName<<endl;
	// }
	return true;
}

/* ��ȡ��ǰ�û����ڷ������������	 */
int Role::getArea()
{
	return where;
}

/*
* Author:	Tory
* Date	:	2012.9.12
* Amend :	
* Description�����ڲ��Դ�memcached server��ȡ����memRole�����Ƿ���ȷ
*/
void show_memRole_data(MemRole *mem_data_role)
{
    if(mem_data_role != NULL)
    {
        cout<<"username:"<<mem_data_role->user.userName<<endl;
        cout<<"heroId list Size:"<<mem_data_role->idSize<<endl;

        int i = 0;
        for(i; i < mem_data_role->idSize; i++)
        {
			cout<<"************hero_infor:"<<i+1<<"  *****"<<endl;			
			printf("test my_hero_infor heroId:%s\n", mem_data_role->my_hero_infor_list[i].heroId);
			printf("test my_hero_infor nickName:%s\n", mem_data_role->my_hero_infor_list[i].nickName);
			printf("test my_hero_infor party:%s\n", mem_data_role->my_hero_infor_list[i].party);
			printf("test my_hero_infor photoId:%s\n", mem_data_role->my_hero_infor_list[i].photoId);
        }
    } 
}