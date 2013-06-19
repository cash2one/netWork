/*
		�ļ����ͣ�ͷ�ļ�
		�ļ����ƣ�role.h
		�ļ����ã�����Role�࣬���༴Ϊ�����
*/

#ifndef ROLE_H
#define ROLE_H
#include"hero.h"
#include"library_head.h"
#include"map_inform.h"
#include"pick.h"
#include"wholeDefine.h"

#include "my_memcached.h"


#if (__GNUC__ >= 3)
#define _BACKWARD_BACKWARD_WARNING_H    // needed for gcc 4.3
#include <ext/hash_map>
#include <ext/hash_set>
#undef _BACKWARD_BACKWARD_WARNING_H
#else
#include <hash_map>
#include <hash_set>
#include <map>
#endif

#if defined(__GNUC__)
using namespace __gnu_cxx;
#endif
struct eqstr
{
    inline bool operator() (const char*s1, const char*s2) const
    {
        return 0 == strcmp(s1, s2);
    }
};
// typedef hash_map<const char*,const char*,hash<const char*>, eqstr> NickName2heroIdHash;
typedef hash_map<const char*,const char*,hash<const char*>, eqstr> NickName2heroIdHash;

class Hero;

class Map_Inform;

using namespace std;

#define ROLETOP 4
typedef struct           //�ṹ�壬�����û���������
{
	char userName[MAX_NAME_LEN+1];
	char passWord[MAX_WORD_LEN+1];
}UserInform;  

//�û������Ľ�ɫ��Ϣ�����ڽ�ɫѡ��ʱ�ͻ��˵������ʾ
typedef struct my_hero_infor
{
	char heroId[IDL+1];
	char nickName[MAX_NAME_LEN+1];
	char party[IDL+1];
	char photoId[IDL+1];
	int gradeNow;	//
	
	my_hero_infor(){}
	
	my_hero_infor(char* _heroId, char* _nickName, char* _party, char* _photoId,int _gradeNow=0)
	{
		strncpy(heroId, _heroId, IDL+1);
		strncpy(nickName, _nickName, MAX_NAME_LEN+1);
		strncpy(party, _party, IDL+1);
		strncpy(photoId, _photoId, IDL+1);
		gradeNow=_gradeNow;
	}
}My_hero_infor;

typedef struct
{
	UserInform 	user;
	int idSize;
	My_hero_infor my_hero_infor_list[4];
	char cardId[MAX_WORD_LEN+1];			//���ֿ�id
}MemRole;

class Role
{
private:
	MemRole*		memRole;			//���ڴ洢ֵmemcached server�е�����
	UserInform 		user;           	//�û�����
	list<My_hero_infor> hero_infor_list;	//�Ѵ����Ľ�ɫ��Ϣ�б�
	
	int 			connect_fd;	        //fd
	bool			isLogin;			//�Ƿ��½��־��true��ʾ�ѵ�½
	string			active_heroId;		//��ǰ���ɫ
	Hero			*active_hero;		//��ǰ���ɫָ��
	int				where;				//�û��������ڵڼ��������û���½ʱ��ʼ��
private:	
	void 			inHeroId(void);
public: 
	Role();
	~Role(void){}
	
	void memSet(void);	
	//�����Ѵ��ڵ��û���½��Ϸʱ����memcached server����ȡ�û�������game server��
	void loadRoleData(MemRole *_memRole, int connect_fd, int where);
	//����δ���ڵ��û���½��Ϸʱ����ʼ���µ��û�����
	void initNewRole(UserInform &_user, int connect_fd,  int where);
	
	int 	getArea();						//��ȡ��ǰ�û����ڷ������������	
	char* 	getUserName(void);  			//����û���
	void 	setLoginState(bool _isLogin);	//���õ�½״̬
	bool 	getLoginState();				//��õ�½״̬
	
	string	getActive_heroId();					//��ȡ��ǰ���ɫID	
	void	setActive_heroId(string heroId);	//���õ�ǰ���ɫID
	Hero*	getActive_hero();					//��û��ɫָ��
	void	setActive_hero(Hero *_active_hero);	//���û��ɫָ��
	
	void 	addHeroInfor(My_hero_infor &hero_infor);	//��Ҵ����½�ɫ�ɹ���ͨ���˺����޸�memRole������
	
	list<My_hero_infor>& getHero_infor_list();			//�������Ѵ����Ľ�ɫ��Ϣ�б�
		
	/*	2012.3.22 Tory Add */
	Hero* 	create_hero(char *party, char *nickname, char *heroTypeId);		//����Hero����
	void 	deleteHero(char *heroId);

	void	setNickName(char *_nickName,char *heroId);
	
	My_hero_infor getHeroInfor(char *heroId);	
	
	/*�������*/
	bool useCardId(char *cardId);
	
	/*�Ƿ����ù�������*/
	bool isUseCard(void);
	
	//�����û���
	bool changeUserName(char* newName);
};

void show_memRole_data(MemRole *mem_data_role);	//���ڲ��Դ�memcached server�л�ȡ���������Ƿ���ȷ added by Tory

#endif

