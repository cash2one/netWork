#ifndef SKILL_CONFIGURATION_H
#define SKILL_CONFIGURATION_H
#include<iostream>
#include<string>
#include<map>
using namespace std;
class Skill_Configuration
{
private: 
			/*��������*/
			string id;           		//����Id
			string name;         		//��������
			int    type;				//��������  ��1��������2��������3��debuff��4��buff��5��ҽ�ƣ���
			int    effect;              //���ܸ���Ч��
										/*
											������1���ޣ�2������3����Ѩ��4�����ˣ�5��ѣ�Σ�6�����͵з����ԣ�
												  7�����ӽ��͵з����У�8�����幥�����ܣ����ӵ��˳�����ѪЧ����
												  9�����幥�����ܣ������ж����˹�����ֵ�½�Ч��
											
											������1����������Ѫ�����ޣ�2�������������ԣ�3�������������ܣ�4���������ﱩ����
												  5�������������У�6�����������⹦�˺���7�����������⹦������8�����������ڹ�������
												  9�����������⹦����10�����������ڹ�����
										*/
			int    con_time;            //Ч������ʱ��
			int    cd_time;             //����cd����ȴʱ�䣩
			int	   factor;              //����ϵ������ֵ
			int    genuine;             //��������
			int	   time_sec;            //���ܶ�������ʱ�䣨�룩
			int    time_usec;           //���ܶ�������ʱ�䣨΢�룩
			int    last_time_sec;        //�ϴ�ʹ�ü���ʱ�䣨�룩
			int    last_time_usec;       //�ϴ�ʹ�ü���ʱ�䣨΢�			
			int    skill_grade;         //���ܵȼ�			
			int	   factor_growup;		//����ϵ���ɳ����� 
			int    control_grade;		//�ȼ�����	
			int    useup_money;			//����������ĵĽ�Ǯ
			int    useup_exp;			//����������ĵľ���ֵ	
			
			//int	   skill_book;			//����Ƿ��ȡ�������飬1����ȡ���ˣ�0��δ��ȡ�� 	
			int    value1;				//������1
			int    value2;				//������2
			int    value3;			    //������3
			/*���������������� */			
			int  nggjjdz_debuff;	    //debuff�����ڹ�����
			int  wggjjdz_debuff;		//debuff�����⹦����		
			int  ngfyjdz_debuff;		//debuff�����ڹ�����		
			int  wgfyjdz_debuff;		//debuff�����⹦����
			int  mzjd_debuff;			//debuff��������
			int  jdrx_debuff;			//debuff��������
			int	 jdsb_debuff;			//debuff��������
			int  jdbj_debuff;			//debuff���ͱ���
			int  cxdx_debuff;			//������Ѫֵ
			int  attack_type;			//������ʽ
										/*������ʽ1�����幥����2����ǰ��浥�幥����3������˵��幥����
												  4��ǰ��ֱ��Ⱥ�幥����5�������Ϊ���Ŀ��ƶ�Բ��Ⱥ�幥����
												  6�������ΪԲ��Բ��Ⱥ�幥����7���������������ΪԲ��Բ��Ⱥ�幥��
										*/
			int  attack_range;			//��������
			int  genuine_growup;		//�������ĳɳ�����
			int	 effect_growup;			//����Ч���ɳ�����
			/*������������ */
			int    smsxjdz_bd;          //������������
			int    wgshbfb_bd;          //�����⹦�˺�
			int    wggjbfb_bd;          //�����⹦����
			int    nggjbfb_bd;          //�����ڹ�����
			int    wgfybfb_bd;          //�����⹦����
			int    ngfybfb_bd;          //�����ڹ�����
			int    mzjdz_bd;            //��������
			int    bjjdz_bd;            //���ӱ���
			int    sbjdz_bd;            //��������
			int    rxjdz_bd;            //��������
			int    fjxgcs_growup_bd;	//����Ч������ֵ�ɳ�����
			/*ҽ�Ƽ�������   */
			int    cure_type;           //ҽ����ʽ��1������ҽ�ƣ�2��Ⱥ��ҽ��
			
			/*buff��������   */
			int   zjngshbfb_buff;        //buff�����ڹ��˺�
			int   zjwgshbfb_buff;        //buff�����⹦�˺�
			int   zjsmsx_buff;        	 //buff������������
			int   ftsh_buff;             //�����˺�
			int   smxh_buff;       		 //��������
			int   xxl_buff;              //��Ѫ��
			int   cxsjcz_buff;           //����ʱ���ֵ
			int	  consumer_growth;		 //�������ĳɳ�����
			int   cxsjcz_growup_buff;	 //���ܳ���ʱ��ɳ�����
			int   cd_growup_buff;		 //����CD�ɳ�����      
			int   xg_growup_buff;		 //����Ч���ɳ�
public:
		/*����������������*/	
		Skill_Configuration(string _id,string _name,int _type,int _effect,int _con_time,int _cd_time,int _factor,
							int	_genuine,int _time_sec,int _time_usec,int  _nggjjdz_debuff,int _wggjjdz_debuff,
							int _ngfyjdz_debuff,int _wgfyjdz_debuff,int _mzjd_debuff,int _jdrx_debuff,int _jdsb_debuff,
							int _jdbj_debuff,int _cxdx_debuff,int _attack_type,int _attack_range,int _effect_growup,
							int _genuine_growup,int _factor_growup,int _control_grade,int _value1,int _value2,int _value3);						
		/*������������  */
		Skill_Configuration(string _id,string _name,int _type,int _effect,int _smsxjdz_bd,int _wgshbfb_bd,int _wggjbfb_bd,
							int _nggjbfb_bd,int _wgfybfb_bd,int _ngfybfb_bd,int _mzjdz_bd,int _bjjdz_bd,int _sbjdz_bd,
							int _rxjdz_bd,int _fjxgcs_growup_bd,int _control_grade);
			/*ҽ�Ƽ������� */
		Skill_Configuration(string _id,string _name,int _type,int _effect,int _con_time,int _cd_time,int _factor,int _genuine,
							int _time_sec,int _time_usec,int _cure_type,int _factor_growup,int _control_grade,int _values1);


			/*buff��������   */
		Skill_Configuration(string _id,string _name,int _type,int _effect,int _cd_time,int _genuine,int _zjngshbfb_buff,
							int _zjwgshbfb_buff,int _zjsmsx_buff,int _ftsh_buff,int _smxh_buff,int _xxl_buff,int _cxsjcz_buff,
							int _consumer_growth,int _cxsjcz_growup_buff,int _cd_growup_buff,int _xg_growup_buff,int _control_grade);
			
			/*��������*/
			string getid(void);           		//����Id
			string getname(void);         		//��������
			int    gettype(void);				//��������  ��1��������2��������3��debuff��4��buff��5��ҽ�ƣ���
			int    geteffect(void);              //���ܸ���Ч��
										/*
											������1���ޣ�2������3����Ѩ��4�����ˣ�5��ѣ�Σ�6�����͵з����ԣ�
												  7�����ӽ��͵з����У�8�����幥�����ܣ����ӵ��˳�����ѪЧ����
												  9�����幥�����ܣ������ж����˹�����ֵ�½�Ч��
											
											������1����������Ѫ�����ޣ�2�������������ԣ�3�������������ܣ�4���������ﱩ����
												  5�������������У�6�����������⹦�˺���7�����������⹦������8�����������ڹ�������
												  9�����������⹦����10�����������ڹ�����
										*/
			int    getcon_time(void);            //Ч������ʱ��

			
			int    getcd_time(void);             //����cd����ȴʱ�䣩

			
			int	   getfactor(void);              //����ϵ������ֵ

			
			int    getgenuine(void);             //��������

			
			int	   gettime_sec(void);            //���ܶ�������ʱ�䣨�룩

			
			int    gettime_usec(void);           //���ܶ�������ʱ�䣨΢�룩

			
			int    getlast_time_sec(void);//�����ϴ�ʹ��ʱ�䣺��

		    
			int    getlast_time_usec(void); //�����ϴ�ʹ��ʱ�䣺΢��

			int    getskill_grade(void);          //���ܵȼ�

			
			int	   getfactor_growup(void);		//����ϵ���ɳ�����   2012.6.19 evan
			
			int    getcontrol_grade(void);		//�ȼ�����  2012.6.25 evan
	

			int    getuseup_money(void);			//����������ĵĽ�Ǯ 2012.6.25 evan

			
			int    getuseup_exp(void);			//����������ĵľ���ֵ	2012.6.25	evan
		
			
			//int	   getskill_book(void);			//����Ƿ��ȡ�������飬1����ȡ���ˣ�0��δ��ȡ�� 	2012.6.25	evan
			//void   setskill_book(int _skill_book);
			
			int    getvalue1(void);				//������1
			int    getvalue2(void);				//������2
			int    getvalue3(void);			    //������3
			/*����������������    */
			int    getnggjjdz_debuff(void);	    //debuff�����ڹ�����
			int    getwggjjdz_debuff(void);		//debuff�����⹦����		
			int    getngfyjdz_debuff(void);		//debuff�����ڹ�����		
			int    getwgfyjdz_debuff(void);		//debuff�����⹦����
			int    getmzjd_debuff(void);			//debuff��������
			int    getjdrx_debuff(void);			//debuff��������
			int	   getjdsb_debuff(void);			//debuff��������
			int    getjdbj_debuff(void);			//debuff���ͱ���
			int    getcxdx_debuff(void);			//������Ѫֵ
			int    getattack_type(void);			//������ʽ
										/*������ʽ1�����幥����2����ǰ��浥�幥����3������˵��幥����
												  4��ǰ��ֱ��Ⱥ�幥����5�������Ϊ���Ŀ��ƶ�Բ��Ⱥ�幥����
												  6�������ΪԲ��Բ��Ⱥ�幥����7���������������ΪԲ��Բ��Ⱥ�幥��
										*/
			int    getattack_range(void);			//��������
			int    getgenuine_growup(void);		//�������ĳɳ�����
			int	   geteffect_growup(void);			//����Ч���ɳ�����
			/*������������ */
			int    getsmsxjdz_bd(void);          //������������
			int    getwgshbfb_bd(void);          //�����⹦�˺�
			int    getwggjbfb_bd(void);          //�����⹦����
			int    getnggjbfb_bd(void);          //�����ڹ�����
			int    getwgfybfb_bd(void);          //�����⹦����
			int    getngfybfb_bd(void);          //�����ڹ�����
			int    getmzjdz_bd(void);            //��������
			int    getbjjdz_bd(void);            //���ӱ���
			int    getsbjdz_bd(void);            //��������
			int    getrxjdz_bd(void);            //��������
			int    getfjxgcs_growup_bd(void);	//����Ч������ֵ�ɳ�����
			/*ҽ�Ƽ�������   */
			int    getcure_type(void);           //ҽ����ʽ��1������ҽ�ƣ�2��Ⱥ��ҽ��
			
			/*buff��������   */
			int    getzjngshbfb_buff(void);        //buff�����ڹ��˺�
			int    getzjwgshbfb_buff(void);        //buff�����⹦�˺�
			int    getzjsmsx_buff(void);        	 //buff������������
			int    getftsh_buff(void);             //�����˺�
			int    getsmxh_buff(void);       		 //��������
			int    getxxl_buff(void);              //��Ѫ��
			int    getcxsjcz_buff(void);           //����ʱ���ֵ
			int	   getconsumer_growth(void);		 //�������ĳɳ�����
			int    getcxsjcz_growup_buff(void);	 //���ܳ���ʱ��ɳ�����
			int    getcd_growup_buff(void);		 //����CD�ɳ�����      
			int    getxg_growup_buff(void);		 //����Ч���ɳ�
			~Skill_Configuration(void);
};
#endif
