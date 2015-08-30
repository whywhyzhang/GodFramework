/*
	The implement of S_Button.
*/

#include "S_Button.h"
#include "G_World.h"

S_Button::S_Button(POS p,SIZE s)
{
	spr_p=p;
	spr_size=s;

	fun_rem=0;
}

S_Button::~S_Button()
{}

void S_Button::Button_Draw()
{
	if(p_world)
	{
		p_world->Message_Send(MESSAGE{M_REC_DRW,spr_p.x,spr_p.y,spr_size.w,spr_size.h,0});
		p_world->Message_Send(MESSAGE{M_BUF_SHW,-1});
	}
}

int S_Button::Message_Process(const MESSAGE *mes)
{
	if(mes->num[1]>=spr_p.x && mes->num[1]<=spr_p.x+spr_size.w \
	&& mes->num[2]>=spr_p.y && mes->num[2]<=spr_p.y+spr_size.h \
	&& fun_rem)
		(*fun_rem)();
}

void S_Button::Click_Register(G_World * p_obj)
{
	p_obj->Message_Process_Register(M_MOU_PRE,obj_num);
}

bool S_Button::Function_Register(G_Object * p_obj)
{
	if(fun_rem) return 0;
	fun_rem=p_obj;
	return 1;
}

bool S_Button::Function_Register(G_Object & p_obj)
{
	Function_Register(&p_obj);
}

void S_Button::Function_Delete()
{
	fun_rem=0;
}
