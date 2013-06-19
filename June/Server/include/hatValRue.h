#ifndef HAT_VAL_RILE_H
#define HAT_VAL_RILE_H
class HatValRue
{
private:
	double hatInRag;       //�����޷�Χʱ��ֵ
	double genHitPer;      //��ͨ�������ֵ��������
	double sklHitPer;		//�˺����ܳ��ֵ��������
	double proLosPer;		//���漼�ܳ��ֵ��������
	double friHitGan;       //��һ�ι������ֵ
	double chageAirPer;        //ת��Ŀ���ޱ���
	double hatUpVal;         //��ֵ����ֵ
	double redueValPer;      //�ﵽ�������ʱ�������������
	int hatRage;              //��޷�Χ
public:
	HatValRue(double _hatInRag,double _genHitPer,double _sklHitPer,double _proLosPer,double _friHitGan,double _chageAir,double hatUpVal,double _redueValPer,int _hatRage);
	int getHatRage(void);
	double getHatInRag(void);
	double getGenHitPer(void);
	double getSklHitPer(void);
	double getProLosPer(void);
	double getFriHitGan(void);
	double getChageAirPer(void);
	double getHatUpVal(void);
	double getRedueValPer(void);
};
#endif
