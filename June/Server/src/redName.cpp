#include"redName.h"
//���ֵ���������ж�
bool term(Hero *me,Hero *hit)
{
	return me->getCamp()==hit->getCamp()?(hit->getisRedName()?false:true):false;
}