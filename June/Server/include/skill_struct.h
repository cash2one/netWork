#ifndef SKILL_STRUCT
#define SKILL_STRUCT
typedef struct
{
/*��������*/
	char identity[50],id[50],name[50];	
	int    type;				//��������  ��1��������2��������3��debuff��4��buff��5��ҽ�ƣ���
	int    effect;              //���ܸ���Ч��
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
	int    value1;				//������1
	int    value2;				//������2
	int    value3;			    //������3
	/*����������������   */ 
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
	int  attack_range;			//��������
	int  genuine_growup;		//�������ĳɳ�����
	int	 effect_growup;			//����Ч���ɳ�����
	/*������������  14*/
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
	/*ҽ�Ƽ�������   1*/
	int    cure_type;           //ҽ����ʽ��1������ҽ�ƣ�2��Ⱥ��ҽ	
	/*buff��������   8*/
	int   zjngshbfb_buff;        //buff�����ڹ��˺�
	int   zjwgshbfb_buff;        //buff�����⹦�˺�
	int   zjsmsx_buff;        	 //buff��������
	int   ftsh_buff;             //�����˺�
	int   smxh_buff;       		 //��������
	int   xxl_buff;              //��Ѫ��
	int   cxsjcz_buff;           //����ʱ���ֵ
	int	  consumer_growth;		 //�������ĳɳ�����
	int   cxsjcz_growup_buff;	 //���ܳ���ʱ��ɳ�����
	int   cd_growup_buff;		 //����CD�ɳ�����      
	int   xg_growup_buff;		 //����Ч���ɳ�
}MemSkill;
#endif