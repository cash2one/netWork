#include<iostream>
#include<string>
#include <libmemcached/memcached.h>
using namespace std;

int main(void)
{
	memcached_st* 				memc_s;//be used by other libmemcached(3) functions to communicate with the server.��������memcached��C�����ӿ���memcached server����
	memcached_server_list_st 	server_list;//memcached_server_st* was aliased to memcached_server_list_st.0.39�汾��memcached_server_list_st����memcached_server_st�ı���
	memcached_return_t 			rc;//to hold any error
	
	size_t 		key_length;//����memcached_setʱ����Ϊ����ֵ����
	size_t 		value_length;//����memcached_getʱ������ʶ��ȡ����ֵ�Ĵ�С
	time_t 		expiration;//����ʱ��
	uint32_t 	flags;		
		
	memc_s = memcached_create(NULL);
	server_list = NULL;
	expiration = 0;
	flags = 0;

	//	ip�Ͷ˿ڽ�ͨ��Mem_configure�ṩ
	//	first append server to memcached_server_list ,the first argument is  NULL
	server_list = memcached_server_list_append(server_list,server_ip,server_port,&rc);    
	if(rc == MEMCACHED_FAILURE)
	{
		cout<<"adds a server to the memcached_server_list failure"<<endl;
		exit(1);
	}

    //pushes an array of memcached_server_st into the memcached_st struct
	rc = memcached_server_push(memc_s, server_list);
	if(rc == MEMCACHED_FAILURE)
	{
		cout<<"memcached_server_push failure"<<endl;
		exit(1);
	}

	memcached_server_list_free(server_list);
	
	memcached_free(memc_s);
	
	return 1;
}