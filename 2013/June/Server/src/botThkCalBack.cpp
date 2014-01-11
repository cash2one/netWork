#include"bottle.h"
#include"trap.h"
#include"takeGoods.h"
#include"otherThingCalBack.h"
extern struct ev_loop *loops;

/*ƿ�޴��飬�Լ���ˢ����*/
void botThkCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{		
	Bottle *bot;
	
	ev_timer_stop(loop,think);	
	
	bot = (Bottle *)think->target;
	
	if(bot == NULL)
	{
		return;
	}	
	
	if(bot->dieOutFlg())
	{
		bot->disperMsg();
		
		/*��һЩ�Ǵ�����ˢ����*/
		if(bot->getBrushStyle() == 0)
		{
			ext_ev_timer_init(think,botThkCalBack,2,0, bot);
			ev_timer_start(loop,think);
		}
		
		/*�������������Ǵ��鲻��ˢ��*/
		else
		{
			return;
		}
	}
	
	else if(bot->aliveFlg())
	{
		bot->brushMsg(); 	
	}
}



/*����ص�*/
void trapThkCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{		
	Trap *trap;
	
	ev_timer_stop(loop,think);	
	
	trap = (Trap *)think->target;
	
	if(trap == NULL)
	{
		return;
	}	
	
	/*�����Ԥ��*/
	if(trap->warning())
	{
		return;
	}
	
	
	/*���������ʧ*/
	if(trap->calBack())
	{		
		ext_ev_timer_init(think,trapDispearCalBack,2,0,trap);

		ev_timer_start(loops,think);
		
		return;
	}	
	
	ext_ev_timer_init(think,trapThkCalBack,trap->getCdTme(),0,trap);

	ev_timer_start(loops,think);
	
}


/*������ʧ�ص�����*/
void trapDispearCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{		
	Trap *trap;
	
	ev_timer_stop(loop,think);	
	
	trap = (Trap *)think->target;
	
	if(trap == NULL)
	{
		return;
	}	
	
	/*��ʧ*/
	if(trap->getIsDispear())
	{
		trap->disperMsg();		
		return;
	}
}



/*��ժȡ��Ʒ����ʧ�Լ���ˢ����*/
void takeGoodsThkCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{		
	TakeGoods *takeGoods;
	
	ev_timer_stop(loop,think);	
	
	takeGoods = (TakeGoods *)think->target;
	
	/*��Դս�������Դ������Ҫ�ٴ�ˢ��*/
	if(takeGoods == NULL || takeGoods->getIsCampSource())
	{
		return;
	}
		
	/*��ʧ�ˣ���ˢ����*/
	if(!takeGoods->getBruOut())
	{
		takeGoods->brushMsg();	
	}
	
	else
	{
		/*�ᶯ��*/
		if(takeGoods->getIsMove())
		{
			takeGoods->calBack();
		
			ext_ev_timer_init(think,takeGoodsThkCalBack,4,0, takeGoods);

			ev_timer_start(loop,think);
		}		
	}	
	
}

/*����ʾ���ص�����*/
void trapWarnCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{		
	Trap *trap;
	
	ev_timer_stop(loop,think);	
	
	trap = (Trap *)think->target;
	
	
	if(trap == NULL)
	{
		return;
	}	
	
	/*���������ʧ*/
	if(trap->calBack())
	{		
		trap->initTimerDispear();
		
		return;
	}		
	
	trap->initTimer();
}

