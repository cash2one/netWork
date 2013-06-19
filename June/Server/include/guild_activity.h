
#include<string>
#include<set>
using namespace std;

typedef struct ActivityTime_S
{
	int weekDay;				//����գ���ÿ�ܼ��㣨0-6����
	int beginHour;				//���ʼʱ��
	int beginMin;				//���ʼ������
	int endHour;				//�������ʱ��
	int endMin;					//�����������
	
	ActivityTime_S(int wd, int bh, int bm, int eh, int em)
	{
		weekDay = wd;
		beginHour = bh;
		beginMin = bm;
		endHour = eh;
		endMin = em;
	}
}ActivityTime_T;

//���ɻ�����а������������ӵ����ɵ�������
class GuildActivity
{
	private:
	char id[50 + 1];								//���ɻ��ID
	int guildLevelLimit;							//���ɻ�ĵȼ�Ҫ��
	set<ActivityTime_T*> timeSet;					//�ʱ������
	public:
	GuildActivity(char* _id, int limit, set<ActivityTime_T*> _timeSet);
	
	char* getId();
	int getLevelLimit();
	set<ActivityTime_T*> getTimeSet();
	bool isInGuildActTime();			//�Ƿ��ڸûʱ��
	
};