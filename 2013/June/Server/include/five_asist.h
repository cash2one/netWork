#include"five_elements.h"
#include"hero.h"

//��ҿ�������
bool openFiveElem(Hero *hero, FIVE_ELEMENT_T elem, int index);
//������������
bool changeFiveElem(Hero *hero, FIVE_ELEMENT_T elem, int index, int order);
//������������
int changeFiveElemNew(Hero *hero, FIVE_ELEMENT_T elem, int index);
//ʹ�����е���
bool useFiveElemGoods(Hero *hero, char* goodsId, int order, int index);
//��ȡ�����˺�
int getFiveElemHurt(FiveElem *fiveHit, FiveElem *fiveHited);
