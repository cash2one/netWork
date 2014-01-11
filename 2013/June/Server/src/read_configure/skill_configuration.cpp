#include"skill_configuration.h"
/*����������������*/	
Skill_Configuration::Skill_Configuration(string _id,string _name,int _type,int _effect,int _con_time,int _cd_time,int _factor,
										int	_genuine,int _time_sec,int _time_usec,int  _nggjjdz_debuff,int _wggjjdz_debuff,
										int _ngfyjdz_debuff,int _wgfyjdz_debuff,int _mzjd_debuff,int _jdrx_debuff,int _jdsb_debuff,
										int _jdbj_debuff,int _cxdx_debuff,int _attack_type,int _attack_range,int _effect_growup,
										int _genuine_growup,int _factor_growup,int _control_grade,int _value1,int _value2,int _value3)
{
			id = _id;
			name = _name;
			type = _type;
			effect = _effect;
			con_time = _con_time;
			cd_time = _cd_time;
			factor = _factor;
			genuine = _genuine;
			time_sec = _time_sec;
			time_usec = _time_usec;
			nggjjdz_debuff = _nggjjdz_debuff;	 
			wggjjdz_debuff = _wggjjdz_debuff;		
			ngfyjdz_debuff = _ngfyjdz_debuff;			
			wgfyjdz_debuff = _wgfyjdz_debuff;		
			mzjd_debuff = _mzjd_debuff;			
			jdrx_debuff = _jdrx_debuff;			
			jdsb_debuff = _jdsb_debuff;		
			jdbj_debuff = _jdbj_debuff;		
			cxdx_debuff = _cxdx_debuff;		
			attack_type = _attack_type;		
			attack_range = _attack_range;			
			genuine_growup = _genuine_growup;		
			effect_growup = _effect_growup;	
			factor_growup = _factor_growup;
			control_grade = _control_grade;
			value1 = _value1;
			value2 = _value2;
			value3 = _value3;
			       
			last_time_sec = 0;    
			last_time_usec = 0;   	
			skill_grade = 1;    
			useup_money = 0;		
			useup_exp = 0;			
			value2 = 0;			
			value3 = 0;			   
			smsxjdz_bd = 0; 
			wgshbfb_bd = 0;
			wggjbfb_bd = 0;      
			nggjbfb_bd = 0;   
			wgfybfb_bd = 0;        
			ngfybfb_bd = 0;     
			mzjdz_bd = 0;         
			bjjdz_bd = 0;      
			sbjdz_bd = 0;          
			rxjdz_bd = 0;          
			fjxgcs_growup_bd = 0;
			cure_type = 0;
			zjngshbfb_buff = 0;   
			zjwgshbfb_buff = 0;   
			zjsmsx_buff = 0;   
			ftsh_buff = 0;    
			smxh_buff = 0;     
			xxl_buff = 0;         
			cxsjcz_buff = 0;     
			consumer_growth = 0;		
			cxsjcz_growup_buff = 0;	
			cd_growup_buff = 0;	
			xg_growup_buff = 0;			
}							
		/*������������  */
Skill_Configuration::Skill_Configuration(string _id,string _name,int _type,int _effect,int _smsxjdz_bd,int _wgshbfb_bd,int _wggjbfb_bd,
										int _nggjbfb_bd,int _wgfybfb_bd,int _ngfybfb_bd,int _mzjdz_bd,int _bjjdz_bd,int _sbjdz_bd,
										int _rxjdz_bd,int _fjxgcs_growup_bd,int _control_grade)
{
			id = _id;
			name = _name;
			type = _type;
			effect = _effect;
			smsxjdz_bd = _smsxjdz_bd;         
			wgshbfb_bd = _wgshbfb_bd;          
			wggjbfb_bd = _wggjbfb_bd;          
			nggjbfb_bd = _nggjbfb_bd;          
			wgfybfb_bd = _wgfybfb_bd;          
			ngfybfb_bd = _ngfybfb_bd;          
			mzjdz_bd = _mzjdz_bd;           
			bjjdz_bd = _bjjdz_bd;           
			sbjdz_bd = _sbjdz_bd;           
			rxjdz_bd = _rxjdz_bd;           
			fjxgcs_growup_bd = _fjxgcs_growup_bd;	
			control_grade = _control_grade;       
			con_time = 0;           
			cd_time = 0;            
			factor = 0;           
			genuine = 0;         
			time_sec = 1;         
			time_usec = 0;         
			last_time_sec = 0;    
			last_time_usec = 0;   	
			skill_grade = 1;    
			factor_growup = 0;	
			useup_money = 0;		
			useup_exp = 0;		
			value1 = 0;			
			value2 = 0;			
			value3 = 0;			   
			nggjjdz_debuff = 0;	 
			wggjjdz_debuff = 0;
			ngfyjdz_debuff = 0;
			wgfyjdz_debuff = 0;
			mzjd_debuff = 0;	
			jdrx_debuff = 0;	
			jdsb_debuff = 0;	
			jdbj_debuff = 0;	
			cxdx_debuff = 0;	
			attack_type = 0;		
			attack_range = 0;
			genuine_growup = 0;	
			effect_growup = 0;
			cure_type = 0;
			zjngshbfb_buff = 0;   
			zjwgshbfb_buff = 0;   
			zjsmsx_buff = 0;   
			ftsh_buff = 0;    
			smxh_buff = 0;     
			xxl_buff = 0;         
			cxsjcz_buff = 0;     
			consumer_growth = 0;		
			cxsjcz_growup_buff = 0;	
			cd_growup_buff = 0;	
			xg_growup_buff = 0;		
}
			/*ҽ�Ƽ������� */
Skill_Configuration::Skill_Configuration(string _id,string _name,int _type,int _effect,int _con_time,int _cd_time,int _factor,int _genuine,
										int _time_sec,int _time_usec,int _cure_type,int _factor_growup,int _control_grade,int _value1)
{
			id = _id;
			name = _name;
			type = _type;
			effect = _effect;
			con_time = _con_time;
			cd_time = _cd_time;
			factor = _factor;
			genuine = _genuine;
			time_sec = _time_sec;
			time_usec = _time_usec;
			cure_type = _cure_type;	
			factor_growup = _factor_growup;	
			control_grade = _control_grade;
			value1 = _value1;
        
			last_time_sec = 0;    
			last_time_usec = 0;   	
			skill_grade = 1;    
			useup_money = 0;		
			useup_exp = 0;				
			value2 = 0;			
			value3 = 0;			   
			nggjjdz_debuff = 0;	 
			wggjjdz_debuff = 0;
			ngfyjdz_debuff = 0;
			wgfyjdz_debuff = 0;
			mzjd_debuff = 0;	
			jdrx_debuff = 0;	
			jdsb_debuff = 0;	
			jdbj_debuff = 0;	
			cxdx_debuff = 0;	
			attack_type = 0;		
			attack_range = 0;
			genuine_growup = 0;	
			effect_growup = 0;
			smsxjdz_bd = 0; 
			wgshbfb_bd = 0;
			wggjbfb_bd = 0;      
			nggjbfb_bd = 0;   
			wgfybfb_bd = 0;        
			ngfybfb_bd = 0;     
			mzjdz_bd = 0;         
			bjjdz_bd = 0;      
			sbjdz_bd = 0;          
			rxjdz_bd = 0;          
			fjxgcs_growup_bd = 0;
			zjngshbfb_buff = 0;   
			zjwgshbfb_buff = 0;   
			zjsmsx_buff = 0;   
			ftsh_buff = 0;    
			smxh_buff = 0;     
			xxl_buff = 0;         
			cxsjcz_buff = 0;     
			consumer_growth = 0;		
			cxsjcz_growup_buff = 0;	
			cd_growup_buff = 0;	
			xg_growup_buff = 0;	
			
			
}

			/*buff��������   */
Skill_Configuration::Skill_Configuration(string _id,string _name,int _type,int _effect,int _cd_time,int _genuine,int _zjngshbfb_buff,
										int _zjwgshbfb_buff,int _zjsmsx_buff,int _ftsh_buff,int _smxh_buff,int _xxl_buff,int _cxsjcz_buff,
										int _consumer_growth,int _cxsjcz_growup_buff,int _cd_growup_buff,int _xg_growup_buff,int _control_grade)
{
			id = _id;
			name = _name;
			type = _type;
			effect = _effect;
			cd_time = _cd_time;
			genuine = _genuine;
			zjngshbfb_buff = _zjngshbfb_buff;       
			zjwgshbfb_buff = _zjwgshbfb_buff;       
			zjsmsx_buff = _zjsmsx_buff;        	
			ftsh_buff = _ftsh_buff;            
			smxh_buff = _smxh_buff;       		
			xxl_buff = _xxl_buff;             
			cxsjcz_buff = _cxsjcz_buff;          
			consumer_growth = _consumer_growth;		 
			cxsjcz_growup_buff = _cxsjcz_growup_buff;	
			cd_growup_buff = _cd_growup_buff;		   
			xg_growup_buff = _xg_growup_buff;	
			control_grade = _control_grade;		 
			con_time = 0;                  
			factor = 0;           
			time_sec = 1;         
			time_usec = 0;         
			last_time_sec = 0;    
			last_time_usec = 0;   	
			skill_grade = 1;    
			factor_growup = 0;	
			useup_money = 0;		
			useup_exp = 0;		
			value1 = 0;			
			value2 = 0;			
			value3 = 0;			   
			nggjjdz_debuff = 0;	 
			wggjjdz_debuff = 0;
			ngfyjdz_debuff = 0;
			wgfyjdz_debuff = 0;
			mzjd_debuff = 0;	
			jdrx_debuff = 0;	
			jdsb_debuff = 0;	
			jdbj_debuff = 0;	
			cxdx_debuff = 0;	
			attack_type = 0;		
			attack_range = 0;
			genuine_growup = 0;	
			effect_growup = 0;
			smsxjdz_bd = 0; 
			wgshbfb_bd = 0;
			wggjbfb_bd = 0;      
			nggjbfb_bd = 0;   
			wgfybfb_bd = 0;        
			ngfybfb_bd = 0;     
			mzjdz_bd = 0;         
			bjjdz_bd = 0;      
			sbjdz_bd = 0;          
			rxjdz_bd = 0;          
			fjxgcs_growup_bd = 0;
			cure_type = 0;		
}	
/*��������*/
		string Skill_Configuration::getid(void)           		//����Id
		{
			return id;
		}
		string Skill_Configuration::getname(void)         		//��������
		{
			return name;
		}
		int    Skill_Configuration::gettype(void)				//��������  ��1��������2��������3��debuff��4��buff��5��ҽ�ƣ���
		{
			return type;
		}
		int    Skill_Configuration::geteffect(void)              //���ܸ���Ч��
		{
			return effect;
		}
			
		int    Skill_Configuration::getcon_time(void)            //Ч������ʱ��
		{
			return con_time;
		}
		
		int    Skill_Configuration::getcd_time(void)             //����cd����ȴʱ�䣩
		{
			return cd_time;
		}
		
		int	   Skill_Configuration::getfactor(void)              //����ϵ������ֵ
		{
			return factor;
		}
		int    Skill_Configuration::getgenuine(void)             //��������
		{
			return genuine;
		}
		int	   Skill_Configuration::gettime_sec(void)            //���ܶ�������ʱ�䣨�룩
		{
			return time_sec;
		}
		
		int    Skill_Configuration::gettime_usec(void)           //���ܶ�������ʱ�䣨΢�룩
		{
			return time_usec;
		}
		
		int    Skill_Configuration::getlast_time_sec(void)//�����ϴ�ʹ��ʱ�䣺��
		{
			return last_time_sec;
		}
		
		    
		int    Skill_Configuration::getlast_time_usec(void) //�����ϴ�ʹ��ʱ�䣺΢��
		{	
			return last_time_usec;
		}
		
		int   Skill_Configuration::getskill_grade(void)          //���ܵȼ�
		{
			return skill_grade;
		}
		
		int	  Skill_Configuration::getfactor_growup(void)		//����ϵ���ɳ�����   2012.6.19 evan
		{
			return factor_growup;
		}
		
		int    Skill_Configuration::getcontrol_grade(void)		//�ȼ�����  2012.6.25 evan
		{
			return control_grade;
		}
		
		int    Skill_Configuration::getuseup_money(void)			//����������ĵĽ�Ǯ 2012.6.25 evan
		{
			return useup_money;
		}
		
		int    Skill_Configuration::getuseup_exp(void)			//����������ĵľ���ֵ	2012.6.25	evan
		{
			return useup_exp;
		}
		
		int    Skill_Configuration::getvalue1(void)			//������1
		{
			return value1;
		}
		int    Skill_Configuration::getvalue2(void)				//������2
		{
			return value2;
		}
		int    Skill_Configuration::getvalue3(void)			    //������3
		{
			return value3;
		}
/*����������������    */
int    Skill_Configuration::getnggjjdz_debuff(void)	    //debuff�����ڹ�����
{
		return nggjjdz_debuff;
}
int    Skill_Configuration::getwggjjdz_debuff(void)		//debuff�����⹦����
{
		return wggjjdz_debuff;
}		
int    Skill_Configuration::getngfyjdz_debuff(void)		//debuff�����ڹ�����
{
		return ngfyjdz_debuff;
}		
int    Skill_Configuration::getwgfyjdz_debuff(void)		//debuff�����⹦����
{
		return wgfyjdz_debuff;
}
int    Skill_Configuration::getmzjd_debuff(void)			//debuff��������
{
		return mzjd_debuff;
}
int    Skill_Configuration::getjdrx_debuff(void)			//debuff��������
{
		return jdrx_debuff;
}
int	   Skill_Configuration::getjdsb_debuff(void)			//debuff��������
{
		return jdsb_debuff;
}
int    Skill_Configuration::getjdbj_debuff(void)			//debuff���ͱ���
{
		return jdbj_debuff;
}
int    Skill_Configuration::getcxdx_debuff(void)			//������Ѫֵ
{
		return cxdx_debuff;
}
int    Skill_Configuration::getattack_type(void)			//������ʽ
{
		return attack_type;
}
							
int    Skill_Configuration::getattack_range(void)			//��������
{
		return attack_range;
}
int    Skill_Configuration::getgenuine_growup(void)		//�������ĳɳ�����
{
		return genuine_growup;
}
int	   Skill_Configuration::geteffect_growup(void)			//����Ч���ɳ�����
{
		return effect_growup;
}
			/*������������ */
int    Skill_Configuration::getsmsxjdz_bd(void)          //������������
{
		return smsxjdz_bd;
}
int    Skill_Configuration::getwgshbfb_bd(void)          //�����⹦�˺�
{
		return wgshbfb_bd;
}
int    Skill_Configuration::getwggjbfb_bd(void)          //�����⹦����
{
		return wggjbfb_bd;
}
int    Skill_Configuration::getnggjbfb_bd(void)          //�����ڹ�����
{
		return nggjbfb_bd;
}
int    Skill_Configuration::getwgfybfb_bd(void)          //�����⹦����
{
		return wgfybfb_bd;
}
int    Skill_Configuration::getngfybfb_bd(void)          //�����ڹ�����
{
		return ngfybfb_bd;
}
int    Skill_Configuration::getmzjdz_bd(void)            //��������
{
		return mzjdz_bd;
}
int    Skill_Configuration::getbjjdz_bd(void)            //���ӱ���
{
		return bjjdz_bd;
}
int    Skill_Configuration::getsbjdz_bd(void)            //��������
{
		return sbjdz_bd;
}
int    Skill_Configuration::getrxjdz_bd(void)            //��������
{
		return rxjdz_bd;
}
int    Skill_Configuration::getfjxgcs_growup_bd(void)	//����Ч������ֵ�ɳ�����
{
		return fjxgcs_growup_bd;
}
			/*ҽ�Ƽ�������   */
int    Skill_Configuration::getcure_type(void)           //ҽ����ʽ��1������ҽ�ƣ�2��Ⱥ��ҽ��
{
		return cure_type;
}
			
			/*buff��������   */
int    Skill_Configuration::getzjngshbfb_buff(void)        //buff�����ڹ��˺�
{
		return zjngshbfb_buff;
}
int    Skill_Configuration::getzjwgshbfb_buff(void)        //buff�����⹦�˺�
{
		return zjwgshbfb_buff;
}
int    Skill_Configuration::getzjsmsx_buff(void)        	 //buff������������
{
		return zjsmsx_buff;
}
int    Skill_Configuration::getftsh_buff(void)             //�����˺�
{
		return ftsh_buff;
}
int    Skill_Configuration::getsmxh_buff(void)       		 //��������
{
		return smxh_buff;
}
int    Skill_Configuration::getxxl_buff(void)              //��Ѫ��
{
		return xxl_buff;
}
int    Skill_Configuration::getcxsjcz_buff(void)           //����ʱ���ֵ
{
		return cxsjcz_buff;
}
int	   Skill_Configuration::getconsumer_growth(void)		 //�������ĳɳ�����
{
		return consumer_growth;
}
int    Skill_Configuration::getcxsjcz_growup_buff(void)	 //���ܳ���ʱ��ɳ�����
{
		return cxsjcz_growup_buff;
}
int    Skill_Configuration::getcd_growup_buff(void)		 //����CD�ɳ����� 
{
		return cd_growup_buff;
}     
int    Skill_Configuration::getxg_growup_buff(void)		 //����Ч���ɳ�
{
		return xg_growup_buff;
}
		

									