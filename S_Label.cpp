/*
   	The implement of class S_Label.
*/

#include <algorithm>

#include "S_Label.h"
#include "G_World.h"

using std::min;

S_Label::S_Label(POS pos,SIZE size,char *str,int t,int lim,int pri)
{
	spr_p=pos;
	spr_size=size;
	if(str) text=str;
	else text.clear();
	out_type=MID_LEF;
	pri_num=pri;
	len_limit=lim;
	have_frame=t;
}

S_Label::~S_Label()
{}

void S_Label::Label_Draw()
{
	if(p_world)
	{
		p_world->Message_Send(MESSAGE{M_REC_FIL,spr_p.x,spr_p.y,spr_size.w,spr_size.h,COL_WHITE});
		
		if(have_frame)
			p_world->Message_Send(MESSAGE{M_REC_DRW,spr_p.x,spr_p.y,spr_size.w,spr_size.h,0});
		
		int x,y;
		int OFFSET=6;
		x=spr_p.x,y=spr_p.y;
		
		switch(out_type)
		{
			case TOP_LEF:
				x+=OFFSET;
				y+=OFFSET;
				break;
			case TOP_MID:
				x+=spr_size.w/2;
				y+=OFFSET;
				break;
			case TOP_RIG:
				x+=spr_size.w;
				x-=OFFSET;
				y+=OFFSET;
				break;
			case MID_LEF:
				x+=OFFSET;
				y+=spr_size.h/2;
				break;
			case MID_MID:
				x+=spr_size.w/2;
				y+=spr_size.h/2;
				break;
			case MID_RIG:
				x+=spr_size.w;
				x-=OFFSET;
				y+=spr_size.h/2;
				break;
			case LOW_LEF:
				x+=OFFSET;
				y+=spr_size.h;
				y-=OFFSET;
				break;
			case LOW_MID:
				x+=spr_size.w/2;
				y+=spr_size.h;
				y-=OFFSET;
				break;
			case LOW_RIG:
				x+=spr_size.w;
				x-=OFFSET;
				y+=spr_size.h;
				y-=OFFSET;
				break;
			default:
				break;
		}
		
		MESSAGE mes={M_STR_DRW,x,y,0,min(len_limit,(int)text.length()),out_type};
		mes.p=(char *)text.data();
		p_world->Message_Send(mes);
	}
}

int S_Label::Message_Process(const MESSAGE *)
{
	return 0;
}

bool S_Label::Process_Register()
{}

void S_Label::Redraw()
{
	Label_Draw();
}

void S_Label::Text_Set(char * str)
{
	if(str) text=str;
	else text.clear();
	
	if(p_world)
		p_world->Message_Send(MESSAGE{M_PAINT});
}

void S_Label::Out_Type_Set(int t)
{
	out_type=t;
	
	if(p_world)
		p_world->Message_Send(MESSAGE{M_PAINT});
}

void S_Label::Len_Limit_Set(int len)
{
	len_limit=len;
}

const char * S_Label::operator += (const string & str)
{
	text+=str;
		
	if(p_world)
		p_world->Message_Send(MESSAGE{M_PAINT});
		
	return text.data();
}

const char * S_Label::operator -= (int num)
{
	int len=text.length();
	if(len-num>=0)
		text.erase(len-num);
	else
		text.clear();
	
	if(p_world)
		p_world->Message_Send(MESSAGE{M_PAINT});
	
	return text.data();
}

const char * S_Label::Text_Get() const
{
	return text.data();
}

int S_Label::Text_Length_Get() const
{
	return text.length();
}
