/************************************************************
    �ļ�����showPartyLunch.cpp
    �ļ����ã����
    ���ߣ�chenzhen
    �������ڣ�2012.06.21
************************************************************/
#include"cpy_series_command_function.h"
#include"hero.h"
#include"takeGoods.h"

extern Hero* pg_hero;
extern int g_msg_len;

/*���*/
void olderDish(char *buffer)
{
	Map_Inform *map_now;
	char *dishId;
	
	MSG_BEGIN(buffer, g_msg_len);	
	/*����id*/
	MSG_CHAR(dishId);
	MSG_CHAR_END(char *identity);
	
	if (pg_hero->getGuild()==NULL)
	{
		return;
	}
	
	if (!pg_hero->getGuild()->isCanOpenFeast())
	{
		msg_error(g_out_buf,82);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	pg_hero->getGuild()->beginGuildFeast(pg_hero,dishId,identity);
}
	
void pickGuildFeast(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len);
	MSG_CHAR(char *id)
	MSG_INT(int number)
	
	if (pg_hero->getGuild()==NULL)
	{
		return;
	}	
	
	if (number<0||number>3)
	{
		return;
	}
	
	// pg_hero->getGuild()->eatGuildFeast(pg_hero,id,number);
}
	
	

