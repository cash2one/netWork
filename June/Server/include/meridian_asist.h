#include<string>
#include<hero.h>
using namespace std;

//��ʼ��������
int startMeridStudy(Hero *hero, int index, char* result);
//ʹ�õ��߼ӿ�����
int useMeridGoods(Hero *hero, char* goodsId, int index, int num, char* result);
//ȡ������
bool cancelMeridStudy(Hero *hero);
//����ǿ��
int strenMerid(Hero *hero, char* result);
//��memcache�������ݺ���������
void restartMeridStudy(Hero *hero);
//�������ʱֹͣ������ʱ��
void stopMeridianTimer(char* heroId);

//��ȡ�˸��������ܵȼ��������������Ҫ������ӿ�
int getTotalLevel(Hero *hero);

//��Ԫ�����پ�������ʱ��
int decMeridTimeWithGold(Hero *hero, int flag, char *result);
