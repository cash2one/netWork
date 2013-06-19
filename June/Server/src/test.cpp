/***************************************
*	�ļ����ͣ�ʵ���ļ�
*	�ļ����ƣ�test.cpp
*	�ļ����ã������ļ�
***************************************/
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
//ȫ�ֺ���ͷ�ļ�
#include"command_other_function_all_over.h"
//�����ļ���ȡ��ͷ�ļ�
#include"function_read_configuration_files.h"
//�¼�����ͷ�ļ���IO
#include"libev.h"
//�Զ�����������ͷ�ļ�
#include"other_define_data.h"
//�õ��ı�׼ͷ�ļ�
#include<stdio.h>
#include "set_camp.h"
#include<vector>
#include<map>
#include<set>
#include <fcntl.h>
#include"map_inform.h"
#include"timerContainer.h"
// #include "campWarManagement.h"
#include"my_time.h"
#include"takeGoods.h"
#include"wagon.h"
#include"bottle.h"
#include"trap.h"
#include"guild_war_asist.h"
#include "my_memcached.h"
#include "rankInfoAsist.h"
#include "bootAssignment.h"
#include "campWarManagement.h"
#include "dictionary_asist.h"
#include "set_camp.h"
#include "command_user_role_manage.h"
#include "read_rsa_key.h"
#include "wholeDefine.h"
#include "instancing_manage.h"
#include"cpyManager.h"
#include "system_activity_reward_assist.h"
#include "activeAsist.h"
#include "mail_systerm_interface.h"
#include "my_mem_group.h"
#include"statuaryAsist.h"
#include "rob_flag_war_logic.h"
#include"chatGroupManager.h"
#include "camp_leader_and_chief.h"
#include"cpyAsist.h"

extern ChatGroupManager *chatManager;

extern struct event_base *loops;

extern map<string,string>mapId_connect_monsterId; 

extern char cross_domain_str[256];

extern GuildWarAsist *guildWarManage;           //����ս����
RobFlagWarLogic *robFlagWarManage;
extern int serverOpenTime;
//��Ӫս�����ࣻ
extern campWarManagement campWarController; 

//�����û��б�,��ʼ����Ϸ����(�븱�����ݵĳ�ʼ������)		
extern list<Role*> idle_role_list;

extern map<string, Hero*> heroId_to_pHero;

extern MapType_T mapTypeInfo;		//ĳЩ�����ͼ��ID��

extern CpyManger *cpyManger;

int TakeGoods::count = 0;
// int Wagon::count = 0;  
int Bottle::count = 0;  
int Trap::count = 0;  
int Map_Inform::count = 0;  
extern DurCampTme durCampTime; 

//��ǰ���̱���֮ǰ���洢���ݺ���
void dump(int);

int main(int argc ,char** argv)
{
    cout << "g_out_buf size:" << sizeof(g_out_buf) << endl;
    if(argc < 2)
    {
        perror("argument error\n");
        return(-1);
    }
	
#if 0
	//Ⱥ��Ŀǰ��Ҫ
	ChatGroupManager::createManagerInst(1000);
	chatManager = ChatGroupManager::getManagerInst();
#endif
	
	cpyManger = new CpyManger(1000);
	cpyManger->print();
    loops = event_base_new();
	srand ( time(NULL) );
	
    //���ع��＼�����������ļ�add chenzhen 7.16
    string monSkill = "config/monSkill/monSkill.xml";
    read_monster_skill(const_cast<char *>(monSkill.c_str()));
	
	//����game server�����ļ�
    char main_config_path[] = "config/main_config.xml";
    int rc = read_main_config(main_config_path); 
	if(rc < 0)
	{
		perror("read read_main_config.xml error");
        return -1;
	}

    //��ȡ�������������ļ�add chenzhen 6.13
    string cpyLimit = "config/cpyLimit.xml";
    read_files_cpyLimit(const_cast<char *>(cpyLimit.c_str()));
    vector<string> cpyFile;
    cpyFile.push_back("config/cpy.xml");
    int cpyFileLen = cpyFile.size();
    int i;
    for(i = 0; i < cpyFileLen; i++)
    {
        read_files_cpy(const_cast<char *>(cpyFile[i].c_str()));
    }   

    /** ���ذ�ȫ�����ļ� Tory **/
    int file_desc = open("config/crossdomain.xml", O_RDONLY, 0);
    memset(cross_domain_str, 0, 256);
    rc = read(file_desc, cross_domain_str, 256);
    if(rc < 0)
    {
        perror("read crossdomain.xml error");
        return -1;
    }
	close(file_desc);

	
    /** ��ʼ����������б� list<Role*> idle_role_list **/
    i = 0;
    while(i < 2000)
    {
        Role* idle_role = new Role();
        idle_role_list.push_back(idle_role);
        i++;
    }

	if(initMyMemcached() == false)	//��ʼ�����ӻ���Ĳ�����ʵ�� Tory
	{
		cout<<"initMyMemcached failure"<<endl;
		return -1;
	}	
	
	if (initCdKeyCached()== false)
	{
		cout<<"initCdKeyCached failuer"<<endl;
		return -1;
	}

	if(initMyMemGroup() == false)	//��ʼ�����������������ʵ�� Tory
	{
		cout<<"initMyMemGroup failure"<<endl;
		return -1;
	}
	
	if(MailSystermInterface::createMailDir() < 0)		//����ʼ������ļ����Ƿ���ڣ��������򴴽� tory
	{
		cout<<"create createMailDir error"<<endl;
		return -1;
	}
	
	initCampeDurTme();
	//TODO ��ʽ�����󣬳�ʼ�������溯����
    campWarController.initCampWarInfo(durCampTime.camphappyFight,durCampTime.campcompeteFight,\
							durCampTime.takePartDurTme,durCampTime.kungFuMaster,durCampTime.campPeaceTme,durCampTime.kungPeaceTme);       //��ʼ����Ӫսս����Ĭ��ȫ���Ŀ�ʼ����ʱ����20���ӣ��� 	
	
	
    guildWarManage = new GuildWarAsist();
	robFlagWarManage = new RobFlagWarLogic();
    initAllExistGuild();                                //��ʼ�����Ѵ����
	init_command_map();                                 //��ʼ���������
    initMyTime();                                       //��ʼ�������ڲ�ά�ֵ�ʱ��
    initMyTimer();                                      
    initDictionary();                                   //��ʼ���ֵ�
	initPlayerNumber();
	initInstManage();									//��ʼ�������������
    rankInfoBootInit();//����������Ϣ���£�
    // nickNameCheckValueBootInit();//ͬ����鿪ʼ��ȡ���棻
	// initTowerDefRoom(500);//����500�����鷿�䣻
	init_rechargeInfo_reward();//��ʼ����ֵ������
	init_consumeInfo_reward();//��ʼ�����ѽ�����	
	init_goods_opr_reward();//�ͻ�������ʼ����
	initCampNumber();		//��ʼ����Ӫ����
	serverOpenTime=myTime.tv_sec;
	
	openServerStatuaryMsg();//��ʼ������
	
	init_leader_and_chief_from_mem();
	/*������*/
//	destroyAllStatuary();
	
   	//TODO �����ã��벻Ҫɾ������ʼ����Ӫսս����Ĭ��ȫ���Ŀ�ʼ����ʱ����20���ӣ���							
    // campWarController.initCampWarInfo(1*60+30,40*60,2*60-30,40*60,5*60,20); 

#if 1
	//TODO ��ʽ�����󣬳�ʼ�������溯����
    campWarController.initCampWarInfo(durCampTime.camphappyFight,durCampTime.campcompeteFight,\
							durCampTime.takePartDurTme,durCampTime.kungFuMaster,durCampTime.campPeaceTme,durCampTime.kungPeaceTme);       //��ʼ����Ӫսս����Ĭ��ȫ���Ŀ�ʼ����ʱ����20���ӣ��� 	
#endif	
	//test the special mapId��TODO ��Ҫɾ��;
	cout<<"[XHM TEST]guid mapId:"<<mapTypeInfo.guidWarMapId<<endl;
	cout<<"[XHM TEST]campWar mapId:"<<mapTypeInfo.campWarMapId<<endl;
	cout<<"[XHM TEST]campSence mapId:"<<mapTypeInfo.campSenceMapId<<endl;
	cout<<"[XHM TEST]mainCity1 mapId:"<<mapTypeInfo.mainCityMapId<<endl;
	cout<<"[XHM TEST]mainCity2 mapId:"<<mapTypeInfo.mainCityMapId2<<endl;
	cout<<"[XHM TEST]towerDefMapId mapId:"<<mapTypeInfo.towerDefMapId<<endl;
	cout<<"[XHM TEST]campResWarMapId mapId:"<<mapTypeInfo.campResWarMapId<<endl;
	
	//��ȡwebServer��Կ
	get_pubilc_key();
	
    //signal(SIGSEGV, &dump);
    signal(SIGTERM, &dump); //kill �ź�
	signal(SIGKILL, &dump);	//���Ѻ�kill����
	signal(SIGINT, &dump);	//ctrl + c�Ĵ���
	signal(SIGPIPE, SIG_IGN);
	
	if (argc > 2 && (!strcmp(argv[2], "-d") || !strcmp(argv[2], "-D")))
	{
		cout<<"You have given the argv with -d "<<endl;
		daemon(1, 0);
    }
	
	int port;
    port = atoi(argv[1]);                //��ʼ���׽���
	
    run_loop(port); 
	
	initCpyLimitMemRecord();
	
	cpyManger->print();
	
	
    return 0;
}

void dump(int signo)
{
    if(signo == SIGSEGV || signo == SIGKILL || signo == SIGTERM)
    {
        void *array[20];
        size_t size;
        char **strings;
        size_t i;

        size = backtrace(array, 20);
        strings = backtrace_symbols (array, size);

        printf ("Obtained %zd stack frames.\n", size);

        FILE *out;

		string out_file = "my_core.";
		char time_temp[20] = {0}; 
		int current_time = MY_TV_SEC;
		sprintf(time_temp, "%d",current_time);	
		out_file += time_temp;
		 
        if((out = fopen(out_file.c_str(), "w+")) == NULL)
        {
            fprintf(stderr, "fopen file error!\n");
            _exit(EXIT_FAILURE);
        }

		if(signo == SIGSEGV)	fprintf(out,"%s\n", "signo==SIGSEGV");
		if(signo == SIGKILL)	fprintf(out,"%s\n", "signo==SIGKILL");
		if(signo == SIGTERM)	fprintf(out,"%s\n", "signo==SIGTERM");
        for(i = 0; i < size; i++)
            fprintf(out, "%s\n", strings[i]);
        free (strings);
		if(fclose(out) != 0)
		{
			fprintf(stderr, "fclose file error!\n");
			_exit(EXIT_FAILURE);
		} 
    }
	
	//������������а���ϵͳ��Ϣ
	// saveGuildSystemToMemc();
    map<string, Hero*>::iterator iter =  heroId_to_pHero.begin();
    for(iter; iter != heroId_to_pHero.end(); iter++)
    {
        Hero* myHero = iter->second;
        cout<<"heroId:"<<iter->first<<endl;
        if(myHero != NULL)
        {
			closeServerDeal(myHero);
            //bool isSuccess = myHero->memSet();
        }
    }
	
	saveCampNumber();
	save_leader_and_chief_to_mem();
	
	/*�رշ�����ʱ������������������Ϣ*/
	closeServerStatuaryMsg();
	
	//�渱����¼
	storeCpyLimitMemRecord();
	
	//event_base_free(loops);
    _exit(0);    
}
