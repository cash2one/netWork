#include"hero_help.h"
HeroHelp::HeroHelp(bool _isyd,bool _ds,bool _dx,bool _xy,bool _jt,bool _jdrx,bool _jdmz,bool _jdgf,bool _ftsh,bool _xhxl,bool _tx,bool _xb,bool _wd)
{
	isyd =  _isyd;
	ds = _ds;
	dx = _dx;
	xy = _xy;
	jt = _jt;
	jdrx = _jdrx;
	jdmz = _jdmz;
	jdgf = _jdgf;
	ftsh = _ftsh;
	xhxl = _xhxl;
	tx = _tx;
	xb = _xb;
	wd = _wd;
	life_change = 0;
	isflight = false;
}
bool   HeroHelp::getisflight(void)					//�����һ��ս���Ƿ��Ѿ�������� evan add 2012.9.25
{
	return isflight;
}
void   HeroHelp::setisflight(bool _isflight)
{
	isflight = _isflight;
}
	
bool   HeroHelp::getisyd(void)				//��������������ʱ����Ҳ����ƶ�
{
	return isyd;
}
void   HeroHelp::setisyd(bool _isyd)
{
	isyd = _isyd;
}
int	   HeroHelp::getisyd_contime(void)		//��������ʱ��
{
	return isyd_contime;
}
void   HeroHelp::setisyd_contime(int _isyd_contime)
{
	isyd_contime = _isyd_contime;
}

int    HeroHelp::getisyd_now_time(void)		//�������ſ�ʼʱ��
{
	return isyd_now_time;
}
void   HeroHelp::setisyd_now_time(int _isyd_now_time)
{
	isyd_now_time = _isyd_now_time;
}

int	   HeroHelp::getlife_change(void)					//�����ߵ�Ѫֵ�仯
{
	return life_change;
}
void   HeroHelp::setlife_change(int _life_change)
{
	life_change = _life_change;
}

int    HeroHelp::getfight_status(void)				//�˴ι����Ƿ��Ʒ���������߱��Է����ܵ�Ч������1���ޱ��������ܣ�2��������3�����ܣ���
{
	return fight_status;
}
void   HeroHelp::setfight_status(int _fight_status)
{
	fight_status = _fight_status;
}
	/*debuffЧ��*/
		/*1:����*/
bool   HeroHelp::getds(void)      				//�Ƿ񴥷�������Ч��
{
	return ds;
}
void   HeroHelp::setds(bool _ds)	
{
	ds = _ds;
}

string HeroHelp::getds_id(void)  				//������ܹ����Ķ�����ID
{
	return ds_id;
}
void   HeroHelp::setds_id(string _ds_id)
{
	ds_id = _ds_id;
}
	
int	   HeroHelp::getds_contime(void)			//�����ܳ���ʱ��
{
	return ds_contime;
}
void   HeroHelp::setds_contime(int _ds_contime)
{
	ds_contime = _ds_contime;
}
	
int    HeroHelp::getds_now_time(void)			//�������ͷ�ʱ��
{
	return ds_now_time;
}
void   HeroHelp::setds_now_time(int _ds_now_time)
{
	ds_now_time = _ds_now_time;
}
	
		/*2:��Ѩ*/
bool   HeroHelp::getdx(void)					//�Ƿ񴥷���ѨЧ��
{
	return dx;
}
void   HeroHelp::setdx(bool _dx)
{
	dx = _dx;
}
	
string HeroHelp::getdx_id(void)  				//������ܹ����ĵ�Ѩ����ID
{
	return dx_id;
}	
void   HeroHelp::setdx_id(string _dx_id)
{
	dx_id = _dx_id;
}
	
int	   HeroHelp::getdx_contime(void)			//��Ѩ���ܳ���ʱ��
{
	return dx_contime;
}
void   HeroHelp::setdx_contime(int _dx_contime)
{
	dx_contime = _dx_contime;
}
	
int    HeroHelp::getdx_now_time(void)			//��Ѩ�����ͷ�ʱ��
{
	return dx_now_time;
}
void   HeroHelp::setdx_now_time(int _dx_now_time)
{
	dx_now_time = _dx_now_time;
}
		/*3:ѣ��*/
bool   HeroHelp::getxy(void)					//�Ƿ񴥷�ѣ��Ч��
{
	return xy;
}
void   HeroHelp::setxy(bool _xy)
{
	xy = _xy;
}	
string HeroHelp::getxy_id(void)					//������ܹ�����ѣ�μ���Id
{
	return xy_id;
}
void   HeroHelp::setxy_id(string _xy_id)
{
	xy_id = _xy_id;
}
	
int    HeroHelp::getxy_contime(void)			//ѣ�μ��ܳ���ʱ��
{
	return xy_contime;
}
void   HeroHelp::setxy_contime(int _xy_contime)
{
	xy_contime = _xy_contime;
}
	
int    HeroHelp::getxy_now_time(void)			//ѣ�μ����ͷ�ʱ��
{
	return xy_now_time;
}
void   HeroHelp::setxy_now_time(int _xy_now_time)
{
	xy_now_time = _xy_now_time;
}
		/*4:����*/
bool   HeroHelp::getjt(void)							//�Ƿ񴥷�����Ч��
{
	return jt;
}
void   HeroHelp::setjt(bool _jt)	
{
	jt = _jt;
}
		/*5:���͵з�����*/
bool   HeroHelp::getjdrx(void)						//�Ƿ񴥷���������Ч��
{
	return jdrx;
}
void   HeroHelp::setjdrx(bool _jdrx)
{
	jdrx = _jdrx;
}
	
string HeroHelp::getjdrx_id(void)					//������ܹ����Ľ������Լ���ID
{
	return jdrx_id;
}
void   HeroHelp::setjdrx_id(string _jdrx_id)
{
	jdrx_id = _jdrx_id;
}
	
int	   HeroHelp::getjdrx_contime(void)				//�������Լ��ܳ���ʱ��
{
	return jdrx_contime;
}
void   HeroHelp::setjdrx_contime(int _jdrx_contime)
{
	jdrx_contime = _jdrx_contime;
}	
int    HeroHelp::getjdrx_now_time(void)				//�������Լ����ͷ�ʱ��
{
	return jdrx_now_time;
}
void   HeroHelp::setjdrx_now_time(int _jdrx_now_time)
{
	jdrx_now_time = _jdrx_now_time;
}
	
int    HeroHelp::getjdrx_value(void)					//��������ֵ
{
	return jdrx_value;
}
void   HeroHelp::setjdrx_value(int _jdrx_value)
{
	jdrx_value = _jdrx_value;
}
	/*6:���͵з�����*/
bool   HeroHelp::getjdmz(void)							//�Ƿ񴥷���������Ч��
{
	return jdmz;
}
void   HeroHelp::setjdmz(int _jdmz)
{
	jdmz = _jdmz;
}

string HeroHelp::getjdmz_id(void)						//������ܹ����Ľ������м���Id
{
	return jdmz_id;
}
void   HeroHelp::setjdmz_id(string _jdmz_id)
{
	jdmz_id = _jdmz_id;
}

int    HeroHelp::getjdmz_contime(void)					//�������м��ܳ���ʱ��
{
	return jdmz_contime;
}
void   HeroHelp::setjdmz_contime(int _jdmz_contime)
{
	jdmz_contime = _jdmz_contime;
}

int    HeroHelp::getjdmz_now_time(void)					//�������м����ͷ�ʱ��
{
	return jdmz_now_time;
}
void   HeroHelp::setjdmz_now_time(int _jdmz_now_time)
{
	jdmz_now_time = _jdmz_now_time;
}

int    HeroHelp::getjdmz_value(void)					//���͵�����ֵ
{
	return jdmz_value;
}
void   HeroHelp::setjdmz_value(int _jdmz_value)
{
	jdmz_value = _jdmz_value;
}
/*7:���͵з�������ֵ*/
bool   HeroHelp::getjdgf(void)						//�Ƿ񴥷����͹���Ч��
{
	return jdgf;
}
void   HeroHelp::setjdgf(int _jdgf)
{
	jdgf = _jdgf;
}
	
string HeroHelp::getjdgf_id(void)					//������ܹ����Ľ��͹�������Id
{
	return jdgf_id;
}
void   HeroHelp::setjdgf_id(string _jdgf_id)
{
	jdgf_id = _jdgf_id;
}
	
int    HeroHelp::getjdgf_contime(void)				//���͹������ܳ���ʱ��
{
	return jdgf_contime;
}
void   HeroHelp::setjdgf_contime(int _jdgf_contime)
{
	jdgf_contime = _jdgf_contime;
}

int    HeroHelp::getjdgf_now_time(void)				//���͹��������ͷ�ʱ��
{
	return jdgf_now_time;
}
void   HeroHelp::setjdgf_now_time(int _jdgf_now_time)
{
	jdgf_now_time = _jdgf_now_time;
}

int    HeroHelp::getjdgf_ngvalue(void)				//���͵��ڹ�����ֵ
{
	return jdgf_ngvalue;
}
void   HeroHelp::setjdgf_ngvalue(int _jdgf_ngvalue)
{
	jdgf_ngvalue = _jdgf_ngvalue;
}
	
int    HeroHelp::getjdgf_wgvalue(void)				//���͵��⹦����ֵ
{
	return jdgf_wgvalue;
}
void   HeroHelp::setjdgf_wgvalue(int _jdgf_wgvalue)
{
	jdgf_wgvalue = _jdgf_wgvalue;
}
	
int    HeroHelp::getjdgf_nfvalue(void)				//���͵��ڹ�����ֵ
{
	return jdgf_nfvalue;
}
void   HeroHelp::setjdgf_nfvalue(int _jdgf_nfvalue)
{
	jdgf_nfvalue = _jdgf_nfvalue;
}
	
int    HeroHelp::getjdgf_wfvalue(void)				//���͵��⹦����ֵ
{
	return jdgf_wfvalue;
}
void   HeroHelp::setjdgf_wfvalue(int _jdgf_wfvalue)
{
	jdgf_wfvalue = _jdgf_wfvalue;
}
/*8:������Ѫ*/
bool   HeroHelp::getcxdx(void)						//�Ƿ񴥷�������Ѫ����
{
	return cxdx;
}
void   HeroHelp::setcxdx(bool _cxdx)
{
	cxdx = _cxdx;
}

string HeroHelp::getcxdx_id(void)					//������ܹ����Ľ�������Ѫ����Id
{
	return cxdx_id;
}
void   HeroHelp::setcxdx_id(string _cxdx_id)
{
	cxdx_id = _cxdx_id;
}
	
int    HeroHelp::getcxdx_contime(void)				//������Ѫ���ܳ���ʱ��
{
	return cxdx_contime;
}
void   HeroHelp::setcxdx_contime(int _cxdx_contime)
{
	cxdx_contime = _cxdx_contime;
}
	
int    HeroHelp::getcxdx_now_time(void)				//������Ѫ�����ͷ�ʱ��
{
	return cxdx_now_time;
}
void   HeroHelp::setcxdx_now_time(int _cxdx_now_time)
{
	cxdx_now_time = _cxdx_now_time;
}
	
int    HeroHelp::getcxdx_value(void)					//���͵ĵ�Ѫ��Ѫֵ
{
	return cxdx_value;
}
void   HeroHelp::setcxdx_value(int _cxdx_value)
{
	cxdx_value = _cxdx_value;
}
	
string HeroHelp::getcxdx_hiterid(void)				//�ܓ���Id
{
	return cxdx_hiterid;
}
void   HeroHelp::setcxdx_hiterid(string _cxdx_hiterid)
{
	cxdx_hiterid = _cxdx_hiterid;
}
	/*buffЧ��*/	
	/*10:�ɷ������������˺����ͷ���*/
bool   HeroHelp::getftsh(void)						//�Ƿ񴥷������˺�
{
	return ftsh;
}
void   HeroHelp::setftsh(bool _ftsh)
{
	ftsh = _ftsh;
}
string HeroHelp::getftsh_id(void)					//�����˺�����ID
{
	return ftsh_id;
}
void   HeroHelp::setftsh_id(string _ftsh_id)
{
	ftsh_id = _ftsh_id;
}
	
int    HeroHelp::getftsh_contime(void)				//�����˺����ܳ���ʱ��
{
	return ftsh_contime;
}
void   HeroHelp::setftsh_contime(int _ftsh_contime)
{
	ftsh_contime = _ftsh_contime;
}	
int    HeroHelp::getftsh_now_time(void)				//�����˺����ܴ���ʱ��
{
	return ftsh_now_time;
}
void   HeroHelp::setftsh_now_time(int _ftsh_now_time)
{
	ftsh_now_time = _ftsh_now_time;
}
	
int    HeroHelp::getftsh_value(void)					//�����˺��ʣ�����1000��
{
	return ftsh_value;
}
void   HeroHelp::setftsh_value(int _ftsh_value)
{
	ftsh_value = _ftsh_value;
}

int    HeroHelp::getftsh_hitvalue(void)				//�����˺�ֵ
{
	return ftsh_hitvalue;
}
void   HeroHelp::setftsh_hitvalue(int _ftsh_hitvalue)
{
	ftsh_hitvalue = _ftsh_hitvalue;
}
	/*11:��������Ѫ������������*/
bool   HeroHelp::getxhxl(void)						//�Ƿ񴥷��˼���
{
	return xhxl;
}
void   HeroHelp::setxhxl(bool _xhxl)
{
	xhxl = _xhxl;
}

string HeroHelp::getxhxl_id(void)					//����Id
{
	return xhxl_id;
}
void   HeroHelp::setxhxl_id(string _xhxl_id)
{
	xhxl_id = _xhxl_id;
}
	
int    HeroHelp::getxhxl_contime(void)				//���ܳ���ʱ��
{
	return xhxl_contime;
}
void   HeroHelp::setxhxl_contime(int _xhxl_contime)
{
	xhxl_contime = _xhxl_contime;
}
	
int    HeroHelp::getxhxl_now_time(void)				//���ܴ���ʱ��
{
	return xhxl_now_time;	
}
void   HeroHelp::setxhxl_now_time(int _xhxl_now_time)
{
	xhxl_now_time = _xhxl_now_time;
}
	
int    HeroHelp::getxhxl_inhurt(void)				//���������ڹ��˺�ֵ
{
	return xhxl_inhurt;
}
void   HeroHelp::setxhxl_inhurt(int _xhxl_inhurt)
{
	xhxl_inhurt =_xhxl_inhurt;
}
	
int    HeroHelp::getxhxl_outhurt(void)				//���������⹦�˺�ֵ
{
	return xhxl_outhurt;
}
void   HeroHelp::setxhxl_outhurt(int _xhxl_outhurt)
{
	xhxl_outhurt = _xhxl_outhurt;
}

/*12:����͵ѪЧ��*/
bool   HeroHelp::gettx(void)							//�Ƿ񴥷�͵Ѫ����
{
	return tx;
}
void   HeroHelp::settx(bool _tx)
{
	tx = _tx;
}

string HeroHelp::gettx_id(void)						//͵Ѫ����Id
{
	return tx_id;
}
void   HeroHelp::settx_id(string _tx_id)
{
	tx_id = _tx_id;
}

int    HeroHelp::gettx_contime(void)					//͵Ѫ���ܳ���ʱ��
{
	return tx_contime;
}
void   HeroHelp::settx_contime(int _tx_contime)
{
	tx_contime = _tx_contime;
}

int    HeroHelp::gettx_now_time(void)				//͵Ѫ���ܴ���ʱ��
{
	return tx_now_time;
}
void   HeroHelp::settx_now_time(int _tx_now_time)
{
	tx_now_time = _tx_now_time;
}
	
int    HeroHelp::gettx_value(void)					//͵Ѫ��
{
	return tx_value;
}
void   HeroHelp::settx_value(int _tx_value)
{
	tx_value = _tx_value;
}

/*13:�����ڸ���һ��Ѫ��*/
bool   HeroHelp::getxb(void)							//�Ƿ񴥷��˼���
{
	return xb;
}
void   HeroHelp::setxb(bool _xb)
{
	xb = _xb;
}

string HeroHelp::getxb_id(void)						    //Ѫ������Id
{
	return xb_id;
}
void   HeroHelp::setxb_id(string _xb_id)
{
	xb_id = _xb_id;
}

int    HeroHelp::getxb_contime(void)					//�˼��ܳ���ʱ��
{
	return xb_contime;
}
void   HeroHelp::setxb_contime(int _xb_contime)
{
	xb_contime = _xb_contime;
}
	
int    HeroHelp::getxb_now_time(void)					//�˼��ܴ���ʱ��
{
	return xb_now_time;
}
void   HeroHelp::setxb_now_time(int _xb_now_time)
{
	xb_now_time = _xb_now_time;
}
	
int    HeroHelp::getxb_value(void)						//Ѫ��ֵ
{
	return xb_value;
}
void   HeroHelp::setxb_value(int _xb_value)
{
	xb_value = _xb_value;
}
/*14:�������޵�״̬*/
bool   HeroHelp::getwd(void)							//�Ƿ񴥷��˼���
{
	return wd;
}
void   HeroHelp::setwd(bool _wd)
{
	wd = _wd;
}
string HeroHelp::getwd_id(void)						//�޵м���Id
{
	return wd_id;
}
void   HeroHelp::setwd_id(string _wd_id)
{
	wd_id = _wd_id;
}
int    HeroHelp::getwd_contime(void)					//�˼��ܳ���ʱ��
{
	return wd_contime;
}
void   HeroHelp::setwd_contime(int _wd_contime)
{
	wd_contime = _wd_contime;
}
	
int    HeroHelp::getwd_now_time(void)				//�˼��ܴ���ʱ��
{
	return wd_now_time;
}
void   HeroHelp::setwd_now_time(int _wd_now_time)
{
	wd_now_time = _wd_now_time;
}