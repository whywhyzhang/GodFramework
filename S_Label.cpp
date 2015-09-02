/*
   	The implement of class S_Label.
*/

#include "S_Label.h"
#include "G_World.h"

S_Label::S_Label(POS pos,SIZE size,char *str,int pri)
{
	spr_p=pos;
	spr_size=size;
	if(str) text=str;
	else text.clear();
	out_type=TOP_LEF;
	pri_num=pri;
}

S_Label::~S_Label()
{}

void S_Label::Label_Draw()
{
	if(p_world)
	{
		p_world->Message_Send(MESSAGE{M_REC_FIL,spr_p.x,spr_p.y,spr_size.w,spr_size.h,COL_WHITE});
		p_world->Message_Send(MESSAGE{M_REC_DRW,spr_p.x,spr_p.y,spr_size.w,spr_size.h,0});
		
		int x,y;
		x=spr_p.x,y=spr_p.y;
		
		switch(out_type)
		{
			case TOP_LEF:
				break;
			case TOP_MID:
				x+=spr_size.w/2;
				break;
			case TOP_RIG:
				x+=spr_size.w;
				break;
			case MID_LEF:
				y+=spr_size.h/2;
				break;
			case MID_MID:
				x+=spr_size.w/2;
				y+=spr_size.h/2;
				break;
			case MID_RIG:
				x+=spr_size.w;
				y+=spr_size.h/2;
				break;
			case LOW_LEF:
				y+=spr_size.h;
				break;
			case LOW_MID:
				x+=spr_size.w/2;
				y+=spr_size.h;
				break;
			case LOW_RIG:
				x+=spr_size.w;
				y+=spr_size.h;
				break;
			default:
				break;
		}

		MESSAGE mes={M_STR_DRW,x,y,0,text.length(),out_type};
		mes.p=(char *)text.data();
		p_world->Message_Send(mes);
	}
}

int S_Label::Message_Process(const MESSAGE *)
{}

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

const char * S_Label::operator += (const string & str)
{
	text+=str;
		
	if(p_world)
		p_world->Message_Send(MESSAGE{M_PAINT});
		
	return text.data();
}

const char * S_Label::Text_Get() const
{
	return text.data();
}
