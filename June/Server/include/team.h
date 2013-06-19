#ifndef TEAM_H
#define TEAM_H
#include<string>
#include<set>
#include"wholeDefine.h"
#include<iostream>
#include<vector>
#include"libev.h"

using namespace std;

const int TEAM_MEM_MSG_LEN = 1024;
const int TEAM_COPYID_LEN = 50;
const int TEAM_BIND_COPYROOM_TIME = 60;

const int BRAUSH_TEAM_HEAD_F = 37;
const int BRAUSH_TEAM_HEAD_S = 0;

struct TeamMemInfo;

class Team
{
	size_t index;
	char header[HEROID_LENGTH + 1];
	char teamId[HEROID_LENGTH + 1];
	set<TeamMemInfo> memberIdSet;
	
	char teamMemMsg[TEAM_MEM_MSG_LEN + 1];
	
	//��Ա�Ƿ���������˽��ӵ��ʸ���ֵ�����ʾ��������
	bool memInvite;
	
	char captureCopyId[TEAM_COPYID_LEN + 1];
	
	ev_timer bindCopyRoomTmer;  
	
	size_t agreeNum;	
	
	public:
	
	static const size_t TEAM_NUM_SIZE = 4;
	
	Team(size_t _index);
	
	const char* captureTeam(const char *leaderHero);
	
	const char* join(const char *teamMemId);
	
	
	const char* getTeamId() const;
	
	const char* getHeader() const;
	
	bool isInTeam(const char* memberId) const;
	
	size_t size() const;
	
	
	//�Ƿ��Ƕӳ�
	bool isHeader(const char* memberId) const;
	
	bool getMemInvite(void) const;
	
	//ֻ�жӳ�����Ȩ�����ó�Ա�Ƿ���������˽��ӵ��ʸ�
	void setMemInvite(bool _memInvite);
	
	void sendMsg(const char* teamMsg) const;
	
	const char* getTeamMemMsg() const;
	
	void setCaptureCopy(const char* copyId);
	
	const char* getCaptureCopy(void) const;
	
	//��������
	bool memOffLine(const Hero* memberHero);
	
	//������������
	size_t memOnLineSize() const;
	
	void init();
	
	void initTimer(void);
	
	void stopTimer(void);
	
	void disMissTeam(const char* disMissMsg) const;
	
	bool passHeader(const char *newLeaderId);
	
	bool eraseMemSet(const char *nemberId);
	
	void initCaptureCopyId(bool _isRecover = false);
	
	const char* getCaptureCopyId(void) const;
	
	void holdCaptureCopyId(const char *_captureCopyId);
	
	const set<TeamMemInfo>& getMemberInfo() const ;
	
	void getTeamMemberId(vector<string>& teamMemberIdVec) ;
	
	size_t getAgreeNum() const;
	
	void addAgreeNum();
	
	void initAgreeNum();
	
	~Team();
	
	bool assignGoods(const char* goodsId, int num);
	
	void formTeamMemMsg(const char* expectMemHeroId);
	
	void formTeamMemMsg(void);
		
	private:
	
	void createTeamId();
	
	Team(const Team &team);
	
	Team& operator=(const Team &team);
	
	bool insertMemSet(const char* memId);
	
	
	

	
	void passHeader();
	
	void recoverCpyRoom();
	
	//���Ͷ�����Ϣ,����ĳ����
	void sendMsg(const char* teamMsg,const char* exceptMemId) const;
	
	
};

#endif