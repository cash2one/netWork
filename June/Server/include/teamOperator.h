#ifndef TEAM_OPERATOR_H
#define TEAM_OPERATOR_H


//�����Լ��Ƿ��Ѵ�������
void acceptTeamState(char *buffer);

//��������Ƿ��Ѵ�������
void acceptOtherHeroTeamState(char *buffer);

//������ˡ���ӡ�
void inviteHeroJoinTeam(char *buffer);

//����"���"��Ӧ
void responseInviteHeroJoinTeam(char *buffer);

//�˳�
void offTeam(char *buffer);

//��ɢ
void disMissTeam(char *buffer);

//ת��
void transferTeamLeader(char *buffer);

//ת�û�Ӧ
void transferTeamLeaderResponse(char *buffer);

//����
void kickOutTeam(char *buffer);

//�������
void applyForInTeam(char *buffer);

//ͬ���������
void agreeApplyForInTeam(char *buffer);

#endif