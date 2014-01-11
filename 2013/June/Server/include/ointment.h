#ifndef OINTMENT_
#define OINTMENT_
#include <string>
#include <string.h>

#include "my_timer.h"
//���鳤�Ⱥ궨��ͷ�ļ�
#include "wholeDefine.h"

using namespace::std; 

/* ointmentType ҩƷ�������� ����Ӱ���ɫ���Բ�ͬ����
0 Ѫҩ			1 ��ҩ			2 ��������ֵ
3 ħ������ֵ	4 ����			5 ����
6 ����			7 ����			8 �⹦����
9 �ڹ�����		10 �⹦����		11 �ڹ�����     
12 Ѫ��			13 ���� 
***********************************************/
class Ointment
{
	public:		
		Ointment(string _id,string _name,int _cd,int _sellPriceBoundGold,int _ointmentType,			
		int _sellPriceNoBoundGold,int _sellPriceBoundMoney,int _sellPriceNoBoundMoney,
		int _levelLimits,int _pileUp,int _type,int _value,int level,int _factor);
		string getId(void);						//ҩƷ����ID											
		string getIdentity(void);
		string getName(void);			             
		int getCd(void);  						//����cd														              			
		int getSellPriceBoundGold(void)	;		//npc���۳��۸�	��Ԫ��				
		int getSellPriceNoBoundGold(void);	 	//npc���۳��۸�	�ǰ�Ԫ��
		int getSellPriceBoundMoney(void);		//npc���۳��۸�	����Ϸ��
		int getSellPriceNoBoundMoney(void);		//npc���۳��۸�	�ǰ���Ϸ��
		int getLevelLimits(void)	;			//�ȼ�����							
		int getPileUp(void);					//�ѵ�����	
		int getType(void);
		int getOintmentType(void);
		int getValue(void);
		int getLevel(void);						//��ȡҩƷ�ȼ�
		int getFactor(void);
	private:
		string id;						//����ID													
		string name;	
		int cd;
		int sellPriceBoundGold	;		//npc���۳��۸�	��Ԫ��				
		int sellPriceNoBoundGold;	 	//npc���۳��۸�	�ǰ�Ԫ��
		int sellPriceBoundMoney;		//npc���۳��۸�	����Ϸ��
		int sellPriceNoBoundMoney;		//npc���۳��۸�	�ǰ���Ϸ��
		int levelLimits	;				//�ȼ�����							
		int pileUp;						//�ѵ�����	
		int type;						//0 ҩƿ ��1 ҩ����2 buffҩ
		int ointmentType;				//ҩƷ���� ����Ӱ���ɫ���Բ�ͬ����
		int value;						//ҩƷӰ���ɫ������ֵ
		int level;
		int factor;
};

//����buffҩƷ���ݣ����ڴ洢
typedef struct BuffDrugData_T
{
	char		type_id[IDL];		//ҩƷ����ID
	int			effect_type;		//buffҩ��������
	int			level;				//ҩƷ�ȼ�
	int			effect_value;		//buffҩ������
	int 		remain_time;		//ʣ��ʱ��	
}BuffDrugData;
#endif
