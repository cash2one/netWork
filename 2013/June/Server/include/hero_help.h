/*

*/
#ifndef HERO_HELP_H
#define HERO_HELP_H
#include<string>
#include<iostream>
#include<map>
#include"skill.h"
using namespace std;
class Skill;
class HeroHelp 
{
	private:
		bool   isflight;					//�����һ��ս���Ƿ��Ѿ�������� evan add 2012.9.25
		
		bool   isyd;						//��������������ʱ����Ҳ����ƶ�
		int	   isyd_contime;				//��������ʱ��
		int    isyd_now_time;				//�������ſ�ʼʱ��
		int	   life_change;					//�����ߵ�Ѫֵ�仯
		int	   type;						//����Ч������
		
		int 	fight_status;				//�˴ι����Ƿ��Ʒ���������߱��Է����ܵ�Ч������1���ޱ��������ܣ�2��������3�����ܣ���
		/*debuffЧ��*/
		/*1:����*/
		bool   ds;      					//�Ƿ񴥷�����Ч��
		string ds_id;  					    //������ܹ����Ķ�����ID
		int	   ds_contime;					//�����ܳ���ʱ��
		int    ds_now_time;					//�������ͷ�ʱ��
		/*2:��Ѩ*/
		bool   dx;							//�Ƿ񴥷���ѨЧ��
		string dx_id;  					    //������ܹ����ĵ�Ѩ����ID
		int	   dx_contime;					//��Ѩ���ܳ���ʱ��
		int    dx_now_time;					//��Ѩ�����ͷ�ʱ��	
		/*3:ѣ��*/
		bool   xy;							//�Ƿ񴥷�ѣ��Ч��
		string xy_id;						//������ܹ�����ѣ�μ���Id
		int    xy_contime;					//ѣ�μ��ܳ���ʱ��
		int    xy_now_time;					//ѣ�μ����ͷ�ʱ��
		/*4:����*/
		bool	jt;							//�Ƿ񴥷�����Ч��
		
		/*5:���͵з�����*/
		bool   jdrx;						//�Ƿ񴥷���������Ч��
		string jdrx_id;						//������ܹ����Ľ������Լ���ID
		int	   jdrx_contime;				//�������Լ��ܳ���ʱ��
		int    jdrx_now_time;				//�������Լ����ͷ�ʱ��
		int    jdrx_value;					//���͵�����ֵ
		/*6:���͵з�����*/
		bool   jdmz;						//�Ƿ񴥷���������Ч��
		string jdmz_id;						//������ܹ����Ľ������м���Id
		int    jdmz_contime;				//�������м��ܳ���ʱ��
		int    jdmz_now_time;				//�������м����ͷ�ʱ��
		int    jdmz_value;					//���͵�����ֵ
		
		/*7:���͵з�������ֵ*/
		bool   jdgf;						//�Ƿ񴥷����͹���Ч��
		string jdgf_id;						//������ܹ����Ľ��͹�������Id
		int    jdgf_contime;				//���͹������ܳ���ʱ��
		int    jdgf_now_time;				//���͹��������ͷ�ʱ��
		int    jdgf_ngvalue;				//���͵��ڹ�����ֵ
		int    jdgf_wgvalue;				//���͵��⹦����ֵ
		int    jdgf_nfvalue;				//���͵��ڹ�����ֵ
		int    jdgf_wfvalue;				//���͵��⹦����ֵ
		/*8:������Ѫ*/
		bool   cxdx;						//�Ƿ񴥷�������Ѫ����
		string cxdx_id;						//������ܹ����Ľ�������Ѫ����Id
		int    cxdx_contime;				//������Ѫ���ܳ���ʱ��
		int    cxdx_now_time;				//������Ѫ�����ͷ�ʱ��
		int    cxdx_value;					//���͵ĵ�Ѫ��Ѫֵ
		string cxdx_hiterid;				//�ܓ���Id
		/*buffЧ��*/	
		/*10:�ɷ������������˺����ͷ���*/
		bool   ftsh;						//�Ƿ񴥷������˺�
		string ftsh_id;						//�����˺�����ID
		int    ftsh_contime;				//�����˺����ܳ���ʱ��
		int    ftsh_now_time;				//�����˺����ܴ���ʱ��
		int    ftsh_value;					//�����˺��ʣ�����1000��
		int    ftsh_hitvalue;				//�����˺�ֵ
		/*11:��������Ѫ������������*/
		bool   xhxl;						//�Ƿ񴥷��˼���
		string xhxl_id;						//����Id
		int    xhxl_contime;				//���ܳ���ʱ��
		int    xhxl_now_time;				//���ܴ���ʱ��
		int    xhxl_inhurt;					//���������ڹ��˺�ֵ
		int    xhxl_outhurt;				//���������⹦�˺�ֵ
		/*12:����͵ѪЧ��*/
		bool   tx;							//�Ƿ񴥷�͵Ѫ����
		string tx_id;						//͵Ѫ����Id
		int    tx_contime;					//͵Ѫ���ܳ���ʱ��
		int    tx_now_time;					//͵Ѫ���ܴ���ʱ��
		int    tx_value;					//͵Ѫ��
		/*13:�����ڸ���һ��Ѫ��*/
		bool   xb;							//�Ƿ񴥷��˼���
		string xb_id;						//Ѫ������Id
		int    xb_contime;					//�˼��ܳ���ʱ��
		int    xb_now_time;					//�˼��ܴ���ʱ��
		int    xb_value;					//Ѫ��ֵ
		/*14:�������޵�״̬*/
		bool   wd;							//�Ƿ񴥷��˼���
		string wd_id;						//�޵м���Id
		int    wd_contime;					//�˼��ܳ���ʱ��
		int    wd_now_time;					//�˼��ܴ���ʱ��
	public:
	HeroHelp(bool _isyd,bool _ds,bool _dx,bool _xy,bool _jt,bool _jdrx,bool _jdmz,bool _jdgf,bool _ftsh,bool _xhxl,bool _tx,bool _xb,bool _wd);
	
	bool   getisflight(void);					//�����һ��ս���Ƿ��Ѿ�������� evan add 2012.9.25
	void   setisflight(bool _isflight);
	
	bool   getisyd(void);				//��������������ʱ����Ҳ����ƶ�
	void   setisyd(bool _isyd);
	
	int	   getisyd_contime(void);		//��������ʱ��
	void   setisyd_contime(int _isyd_contime);
	
	int    getisyd_now_time(void);		//�������ſ�ʼʱ��
	void   setisyd_now_time(int _isyd_now_time);
	
	int	   getlife_change(void);					//�����ߵ�Ѫֵ�仯
	void   setlife_change(int _life_change);
	
	int 	getfight_status(void);				//�˴ι����Ƿ��Ʒ���������߱��Է����ܵ�Ч������1���ޱ��������ܣ�2��������3�����ܣ���
	void    setfight_status(int _fight_status);
	/*debuffЧ��*/
		/*1:����*/
	bool   getds(void);      			//�Ƿ񴥷�������Ч��
	void   setds(bool _ds);	
	
	string getds_id(void);  			//������ܹ����Ķ�����ID
	void   setds_id(string _ds_id);
	
	int	   getds_contime(void);			//�����ܳ���ʱ��
	void   setds_contime(int _ds_contime);
	
	int    getds_now_time(void);		//�������ͷ�ʱ��
	void   setds_now_time(int _ds_now_time);
	
		/*2:��Ѩ*/
	bool   getdx(void);					//�Ƿ񴥷���ѨЧ��
	void   setdx(bool _dx);
	
	string getdx_id(void);  			//������ܹ����ĵ�Ѩ����ID
	void   setdx_id(string _dx_id);
	
	int	   getdx_contime(void);			//��Ѩ���ܳ���ʱ��
	void   setdx_contime(int _dx_contime);
	
	int    getdx_now_time(void);		//��Ѩ�����ͷ�ʱ��
	void   setdx_now_time(int _dx_now_time);
		/*3:ѣ��*/
	bool   getxy(void);					//�Ƿ񴥷�ѣ��Ч��
	void   setxy(bool _xy);
	
	string getxy_id(void);				//������ܹ�����ѣ�μ���Id
	void   setxy_id(string _xy_id);
	
	int    getxy_contime(void);			//ѣ�μ��ܳ���ʱ��
	void   setxy_contime(int _xy_contime);
	
	int    getxy_now_time(void);		//ѣ�μ����ͷ�ʱ��
	void   setxy_now_time(int _xy_now_time);
		/*4:����*/
	bool   getjt(void);							//�Ƿ񴥷�����Ч��
	void   setjt(bool _jt);	
		/*5:���͵з�����*/
	bool   getjdrx(void);						//�Ƿ񴥷���������Ч��
	void   setjdrx(bool _jdrx);
	
	string getjdrx_id(void);					//������ܹ����Ľ������Լ���ID
	void   setjdrx_id(string _jdrx_id);
	
	int	   getjdrx_contime(void);				//�������Լ��ܳ���ʱ��
	void   setjdrx_contime(int _jdrx_contime);
	
	int    getjdrx_now_time(void);				//�������Լ����ͷ�ʱ��
	void   setjdrx_now_time(int _jdrx_now_time);
	
	int    getjdrx_value(void);					//��������ֵ
	void   setjdrx_value(int _jdrx_value);
	
	/*6:���͵з�����*/
	bool   getjdmz(void);						//�Ƿ񴥷���������Ч��
	void   setjdmz(int _jdmz);
	
	string getjdmz_id(void);					//������ܹ����Ľ������м���Id
	void   setjdmz_id(string _jdmz_id);
	
	int    getjdmz_contime(void);				//�������м��ܳ���ʱ��
	void   setjdmz_contime(int _jdmz_contime);
	
	int    getjdmz_now_time(void);				//�������м����ͷ�ʱ��
	void   setjdmz_now_time(int _jdmz_now_time);
	
	int    getjdmz_value(void);					//���͵�����ֵ
	void   setjdmz_value(int _jdmz_value);
	
	/*7:���͵з�������ֵ*/
	bool   getjdgf(void);						//�Ƿ񴥷����͹���Ч��
	void   setjdgf(int _jdgf);
	
	string getjdgf_id(void);					//������ܹ����Ľ��͹�������Id
	void   setjdgf_id(string _jdgf_id);
	
	int    getjdgf_contime(void);				//���͹������ܳ���ʱ��
	void   setjdgf_contime(int _jdgf_contime);
	
	int    getjdgf_now_time(void);				//���͹��������ͷ�ʱ��
	void   setjdgf_now_time(int _jdgf_now_time);
	
	int    getjdgf_ngvalue(void);				//���͵��ڹ�����ֵ
	void   setjdgf_ngvalue(int _jdgf_ngvalue);
	
	int    getjdgf_wgvalue(void);				//���͵��⹦����ֵ
	void   setjdgf_wgvalue(int _jdgf_wgvalue);
	
	int    getjdgf_nfvalue(void);				//���͵��ڹ�����ֵ
	void   setjdgf_nfvalue(int _jdgf_nfvalue);
	
	int    getjdgf_wfvalue(void);				//���͵��⹦����ֵ
	void   setjdgf_wfvalue(int _jdgf_wfvalue);
	/*8:������Ѫ*/
	bool   getcxdx(void);						//�Ƿ񴥷�������Ѫ����
	void   setcxdx(bool _cxdx);
	
	string getcxdx_id(void);					//������ܹ����Ľ�������Ѫ����Id
	void   setcxdx_id(string _cxdx_id);
	
	int    getcxdx_contime(void);				//������Ѫ���ܳ���ʱ��
	void   setcxdx_contime(int _cxdx_contime);
	
	int    getcxdx_now_time(void);				//������Ѫ�����ͷ�ʱ��
	void   setcxdx_now_time(int _cxdx_now_time);
	
	int    getcxdx_value(void);					//���͵ĵ�Ѫ��Ѫֵ
	void   setcxdx_value(int _cxdx_value);
	
	string getcxdx_hiterid(void);				//�ܓ���Id
	void   setcxdx_hiterid(string _cxdx_hiterid);
		/*buffЧ��*/	
		/*10:�ɷ������������˺����ͷ���*/
	bool   getftsh(void);						//�Ƿ񴥷������˺�
	void   setftsh(bool _ftsh);
	string getftsh_id(void);					//�����˺�����ID
	void   setftsh_id(string _ftsh_id);
	
	int    getftsh_contime(void);				//�����˺����ܳ���ʱ��
	void   setftsh_contime(int _ftsh_contime);
	
	int    getftsh_now_time(void);				//�����˺����ܴ���ʱ��
	void   setftsh_now_time(int _ftsh_now_time);
	
	int    getftsh_value(void);					//�����˺��ʣ�����1000��
	void   setftsh_value(int _ftsh_value);
	
	int    getftsh_hitvalue(void);				//�����˺�ֵ
	void   setftsh_hitvalue(int _ftsh_hitvalue);
	/*11:��������Ѫ������������*/
	bool   getxhxl(void);						//�Ƿ񴥷��˼���
	void   setxhxl(bool _xhxl);
	
	string getxhxl_id(void);					//����Id
	void   setxhxl_id(string _xhxl_id);
	
	int    getxhxl_contime(void);				//���ܳ���ʱ��
	void   setxhxl_contime(int _xhxl_contime);
	
	int    getxhxl_now_time(void);				//���ܴ���ʱ��
	void   setxhxl_now_time(int _xhxl_now_time);
	
	int    getxhxl_inhurt(void);				//���������ڹ��˺�ֵ
	void   setxhxl_inhurt(int _xhxl_inhurt);
	
	int    getxhxl_outhurt(void);				//���������⹦�˺�ֵ
	void   setxhxl_outhurt(int _xhxl_outhurt);
	/*12:����͵ѪЧ��*/
	bool   gettx(void);							//�Ƿ񴥷�͵Ѫ����
	void   settx(bool _tx);
	
	string gettx_id(void);						//͵Ѫ����Id
	void   settx_id(string _tx_id);
	
	int    gettx_contime(void);					//͵Ѫ���ܳ���ʱ��
	void   settx_contime(int _tx_contime);
	
	int    gettx_now_time(void);				//͵Ѫ���ܴ���ʱ��
	void   settx_now_time(int _tx_now_time);
	
	int    gettx_value(void);					//͵Ѫ��
	void   settx_value(int _tx_value);
	/*13:�����ڸ���һ��Ѫ��*/
	bool   getxb(void);							//�Ƿ񴥷��˼���
	void   setxb(bool _xb);
	
	string getxb_id(void);						//Ѫ������Id
	void   setxb_id(string _xb_id);
	
	int    getxb_contime(void);					//�˼��ܳ���ʱ��
	void   setxb_contime(int _xb_contime);
	
	int    getxb_now_time(void);				//�˼��ܴ���ʱ��
	void   setxb_now_time(int _xb_now_time);
	
	int    getxb_value(void);					//Ѫ��ֵ
	void   setxb_value(int _xb_value);
	/*14:�������޵�״̬*/
	bool   getwd(void);							//�Ƿ񴥷��˼���
	void   setwd(bool _wd);
	
	string getwd_id(void);						//�޵м���Id
	void   setwd_id(string _wd_id);
	
	int    getwd_contime(void);					//�˼��ܳ���ʱ��
	void   setwd_contime(int _wd_contime);
	
	int    getwd_now_time(void);				//�˼��ܴ���ʱ��
	void   setwd_now_time(int _wd_now_time);
};
#endif

