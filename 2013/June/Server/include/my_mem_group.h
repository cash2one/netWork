#ifndef MY_MEM_GROUP_
#define MY_MEM_GROUP_

#include <map>
#include <string>
using namespace std;

class MyMemcache;		//Ԥ���������������
bool initMyMemGroup();	//����������ʱ�����ڳ�ʼ������������б����

/* ��������������� tory 2013.3.13 */
class MyMemGroup
{
	public:
		MyMemGroup();
		~MyMemGroup();

		//����keyֵ��zone_index,��ָ�������������ȡ����,sz��where�ֱ��ʾ���ݵĴ�С����Դ;��zone_indexȱʡ��Ĭ��Ϊ-1����ʾ������һ̨�����������ȡ����
		char* get_data(string mem_key, int*sz, int*where, int zone_index=-1);
		char* get_data(char* mem_key, int*sz, int*where, int zone_index=-1);
		
		// ����keyֵ�������ݴ洢��ָ�����������
		bool set_data(string key, char* data2set, int size, int zone_index);
		bool set_data(char* key, char* data2set, int size, int zone_index);
		
		// ����keyֵ����ָ�����������ɾ������
		bool delete_data(string key, int zone_index);
		bool delete_data(char* key, int zone_index);

	public:
		int		number;							//���ӵĻ������������Ŀ

	private:
		map<int,MyMemcache*>	mem_server_map;	//��������������������������ڶԲ�ͬ����DB���ݽ��з��ʺ��޸�
};

#endif