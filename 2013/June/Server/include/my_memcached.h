/**********************************************
* author:	Tory
* data	:	2012.9.9
* Description:���ڴ�����memcached server������memcached_st* memc��
* @@@@@@@@@@@ ���ṩ����memcached server���Ӻ�memcached server�����ݽ�������
************************************************/ 
#ifndef MYMEMCACHED_H_
#define MYMEMCACHED_H_

#include <iostream>
#include <string.h>
#include <libmemcached/memcached.h>

using namespace std;

//memcached server ��������
typedef struct mem_configure
{
	char server_ip[20]; 		//memcached server ip
	int  server_port;			//memcached server port
	mem_configure(char* ip, int port)
	{
		memset(server_ip, 0, 20);
		if(ip != NULL) 
		{
			strncpy(server_ip, ip, 20);
		}
		server_port = port;
	}
}Mem_configure;

bool initMyMemcached();

bool initCdKeyCached();

class MyMemcache
{
	public:
	//	MyMemcache(vector<Mem_configure> server_config_array)
		MyMemcache(char* server_ip, int server_port);
		
		void show_mem_server_infor()
		{
			cout<<"server_list_count:"<<(int)memcached_server_list_count(server_list)<<endl;
			cout<<"server_count:"<<(int)memcached_server_count(memc_s)<<endl;
		}
		/************************************************
		* ������������ڴ洢����data2set�����ݴ�Сsize
		* ����ֵ:	����string����ID����ID��Ϊ�գ���ʾ���ݴ洢�ɹ�������ʧ��
		************************************************/ 		
		char* add_mem_data(char* data2add, int size);
		
		/************************************************
		* �����������ֵkey,�����޸ĵ�����data2set�����ݴ�Сsize
		* ����ֵ:	boolֵ���޸ĳɹ�������true,���򷵻�false
		************************************************/ 
		bool set_mem_data(string key, char* data2set, int size);
		bool set_mem_data(char* key, char* data2set,int size);

		/************************************************
		* �����������ֵkey,���ڴ洢/�޸ĵ�����data2set�����ݴ�Сsize
		* ����ֵ:	boolֵ���洢/�޸ĳɹ�������true,���򷵻�false
		************************************************/ 
		bool delete_mem_data(string key);
		bool delete_mem_data(char* key);
		/**********************************************
		* �����������ֵkey,���ڻ�ȡ�õ������ݵ��ֽڴ�С
		* ����ֵ:	�����ݻ�ȡ�ɹ������ݼ�ֵ��õ�char*������ָ�룬
		* @@@@@@@	ͬʱΪ�����int* sz������Ӧ��С��ֵ�����򷵻�NULL
		************************************************/
		char* get_mem_data(string key, int* sz);
		char* get_mem_data(char* key, int* sz);
	private:
		memcached_st* 				memc_s;		//be used by other libmemcached(3) functions to communicate with the server.��������memcached��C�����ӿ���memcached server����
		memcached_server_list_st 	server_list;//memcached_server_st* was aliased to memcached_server_list_st.0.39�汾��memcached_server_list_st����memcached_server_st�ı���
		memcached_return_t 			rc;			//to hold any error
		
		size_t 		key_length;					//����memcached_setʱ����Ϊ����ֵ����
		size_t 		value_length;				//����memcached_getʱ������ʶ��ȡ����ֵ�Ĵ�С
		time_t 		expiration;					//����ʱ��
		uint32_t 	flags;		
};
//���Ի���������Ƿ���������
bool test_memcached_server(MyMemcache* my_mem);
#endif
