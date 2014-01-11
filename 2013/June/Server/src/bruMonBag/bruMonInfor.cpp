/************************************************************
	�ļ�����bruMonInfor.cpp
	�ļ����ã�ʵ����BruMonInfor��ķ���
	���ߣ�chenzhen
	�������ڣ�2012.03.11
************************************************************/
#include"bruMonInfor.h"
BruMonInfor::BruMonInfor(char *_typeId,int _brushed_count = 0,int _sum = 0,int _alive_count = 0)
{
	typeId = _typeId;
	brushed_count = _brushed_count;
	sum = _sum;
	alive_count = _alive_count;
}

/*��ô������ִ��Ĺֵ�id����*/
set<string>& BruMonInfor::getLivMonId(void)
{
	return liveMonId;
}

/*��ô����ͼ����̳��ֵ�id����*/
set<string>& BruMonInfor::getBushMonId(void)
{
	return bushMonId;
}

/*��ô����͹���id*/
char* BruMonInfor::getTyId(void)
{
	return const_cast<char *>(typeId.c_str());
}

/*��ô����͹�����̳���Ŀ*/
int BruMonInfor::getBrshCnt(void)
{
	return brushed_count;
}

/*��ô����͹�������Ŀ*/
int BruMonInfor::getSumCnt(void)
{
	return sum;
}

/*�õ����ŵĹֵ���Ŀ*/	
int BruMonInfor::getLivCnt(void)
{
	return alive_count;
}

/*���ý�Ҫˢ�ֵ���Ŀ*/
void BruMonInfor::setBrshCnt(int _num)
{
	brushed_count = _num;
}

/*�����ֵܹ���Ŀ*/	
void BruMonInfor::setSumCnt(int _num)
{
	sum = _num;
}

/*���û��ŵĹֵ���Ŀ*/	
void BruMonInfor::setLivCnt(int _num)
{
	alive_count = _num;
}

/*��������Ĺֵ�id��������*/
set<string>& BruMonInfor::getDieMonId(void)
{
	return dieMonId;
}


//�������Ĺֵ�id��������������
// void BruMonInfor::InputDieId(char *monId)
// {
	// dieMonId.insert(monId);	
	// alive_count -= 1;
// }


/*�������Ĺֵ�id��������������(�ڹ�����������������ã�*/
void BruMonInfor::InputDieId(char *monId)
{
	set<string>::iterator liv_it;
	liv_it = liveMonId.find(monId);
	if(liv_it == liveMonId.end())
	{
		return;
	}
	liveMonId.erase(liv_it);
	dieMonId.insert(monId);	
	alive_count -= 1;
}

/*�ѻ��ŵĹֵ�id������������*/
void BruMonInfor::InputLiveId(char* monLivId)
{
	set<string>::iterator bru_it;
	bru_it = bushMonId.find(monLivId);
	if(bru_it == bushMonId.end())
	{
		return;
	}
	bushMonId.erase(bru_it);	
	liveMonId.insert(monLivId);
	alive_count += 1;
}

//�ѻ��ŵĹֵ�id������������
// void BruMonInfor::InputLiveId(char* monLivId)
// {
	// liveMonId.insert(monLivId);
	// alive_count += 1;
// }

/*��Ҫˢ�ֵ�id����ˢ��������*/
void BruMonInfor::InputBruId(char* monBruId)
{
	set<string>::iterator die_it;
	die_it = dieMonId.find(monBruId);
	if(die_it == dieMonId.end())
	{
		return;
	}
	dieMonId.erase(die_it);
	bushMonId.insert(monBruId);
	sum += 1;
}

/*��Ҫˢ�ֵ�id����ˢ��������(��Ҫ�ڵ�ͼ�����ļ�������ã�*/
void BruMonInfor::inputBruId(char* monBruId)
{
	bushMonId.insert(monBruId);
	sum += 1;
}

/*��Ҫ����������id����ˢ��������*/
void BruMonInfor::exchage(void)       
{
	set<string>::iterator die_it;
	for(die_it = dieMonId.begin();die_it != dieMonId.end();die_it++)
	{
		string dieId = *die_it;
		bushMonId.insert(*die_it);
	}
	dieMonId.clear();
}

/*��Ҫ����Ҫˢ�Ĺֵ�id�������vector��*/
void BruMonInfor::outBruMonId(vector<string>& bruId,int _num)
{
	int i = 0;
	if(_num == 0)
	{
		_num = bushMonId.size();
	}		
	set<string>::iterator bru_it;
	for(bru_it = bushMonId.begin();bru_it != bushMonId.end() && i < _num;bru_it++,i++)
	{
		string id = *bru_it;
		bruId.push_back(id);		
	}
	bushMonId.erase(bushMonId.begin(),bru_it);
}

/*�Ѹ�ˢ�õĵĹֵ�id��������vector��������������*/
void BruMonInfor::InputLiveId(vector<string>& bruId)
{
	int num_arr = bruId.size();
	int i ;
	for(i = 0;i < num_arr;i++)
	{
		liveMonId.insert(bruId[i]);
	}
	alive_count += i;
}

/*��������*/		
BruMonInfor::~BruMonInfor(void)
{
	liveMonId.clear();
	bushMonId.clear();
	dieMonId.clear();
}

/*ȡ�����м����̳��Ĺ���id*/
void BruMonInfor::outBruMonIdAll(vector<string>& bruId)     
{
	set<string>::iterator bru_it;
	for(bru_it = bushMonId.begin();bru_it != bushMonId.end() ;bru_it++)
	{
		string id = *bru_it;
		bruId.push_back(id);		
	}
	bushMonId.clear();
}

/*���Դ�ӡ������������*/
void BruMonInfor::testPrintDie(void)
{
	cout<<"begin test Die container:"<<endl;
	set<string>::iterator die_it;
	for(die_it = dieMonId.begin();die_it != dieMonId.end();die_it++)
	{
		cout<<"monster Id:"<<*die_it<<endl;
	}
	cout<<"end test Die container:"<<endl;
}

/*���Դ�ӡ�����������*/
void BruMonInfor::testPrintLive(void)
{
	cout<<"begin test live container:"<<endl;
	set<string>::iterator live_it;
	for(live_it = liveMonId.begin();live_it != liveMonId.end();live_it++)
	{
		cout<<"monster Id:"<<*live_it<<endl;
	}
	cout<<"end test live container:"<<endl;
}	

/*���Դ�ӡ��Ҫ�̳���������*/
void BruMonInfor::testPrintBush(void)
{
	cout<<"begin test brush container:"<<endl;
	set<string>::iterator brush_it;
	for(brush_it = bushMonId.begin();brush_it != bushMonId.end();brush_it++)
	{
		cout<<"monster Id:"<<*brush_it<<endl;
	}
	cout<<"end test brush container:"<<endl;
}	

/*���Դ�����Ž���ˢ������*/
void BruMonInfor::exchageLve(void)
{
	set<string>::iterator liv_it;
	for(liv_it = liveMonId.begin();liv_it != liveMonId.end();liv_it++)
	{
		string livId = *liv_it;
		bushMonId.insert(livId);
	}
	liveMonId.clear();
}
	
/*��ԭbrush*/
void BruMonInfor::initBrush(void)
{
	exchage();
	exchageLve();
	brushed_count = 0;	           
	alive_count = 0;
	sum = bushMonId.size();       
}

/*��������������*/
void BruMonInfor::inputOneLve(char* monLivId)
{
	set<string>::iterator bru_it;
	bru_it = liveMonId.find(monLivId);
	if(bru_it != liveMonId.end())
	{
		return;
	}	
	liveMonId.insert(monLivId);
	alive_count += 1;
}

/*���ô������*/
void BruMonInfor::setLiveMonId(set<string> &_liveMonId)
{
	liveMonId = _liveMonId;
}

/*���ô������*/
void BruMonInfor::setDieMonId(set<string> &_dieMonId)
{
	dieMonId = _dieMonId;
}

/*����ˢ������*/
void BruMonInfor::setBushMonId(set<string> &_bushMonId)
{
	bushMonId = _bushMonId;
}


/*����ˢ������*/
BruMonInfor* BruMonInfor::copyMonBru(void)
{
	BruMonInfor* newMonBru;
	newMonBru = NULL;

	newMonBru = new BruMonInfor(const_cast<char *>(typeId.c_str()),brushed_count,sum,alive_count);
	newMonBru->setLiveMonId(liveMonId);
	newMonBru->setDieMonId(dieMonId);
	newMonBru->setBushMonId(bushMonId);
	return newMonBru;	
}