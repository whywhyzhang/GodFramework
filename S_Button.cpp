/*
	The implement of S_Button.
*/

#include "S_Button.h"
#include "G_World.h"

S_Button::S_Button(POS p,SIZE s)
{
	spr_p=p;
	spr_size=s;

	for(int i=0;i<MOU_BUTTON_NUM;++i)
		fun_rem[i]=0;
}

S_Button::~S_Button()
{}

void S_Button::Button_Draw()
{
	if(p_world)
	{
		if(mou_on)
			p_world->Message_Send(MESSAGE{M_REC_FIL,spr_p.x,spr_p.y,spr_size.w,spr_size.h,0x6f6f6f});
		else
			p_world->Message_Send(MESSAGE{M_REC_DRW,spr_p.x,spr_p.y,spr_size.w,spr_size.h,0});
	}
}

int S_Button::Message_Process(const MESSAGE *mes)
{
	switch(mes->type)
	{
		case M_MOU_MOV:
			if(mes->num[1]>=spr_p.x && mes->num[1]<=spr_p.x+spr_size.w \
			&& mes->num[2]>=spr_p.y && mes->num[2]<=spr_p.y+spr_size.h)
				mou_on=1;
			else
				mou_on=0;
			break;
		case M_MOU_PRE:
			if(fun_rem[mes->num[0]])
				(*fun_rem[mes->num[0]])();
			break;
		default:
			break;
	}
}

bool S_Button::Process_Register()
{
	if(p_world) return 0;
	
	p_world->Message_Process_Register(M_MOU_PRE,obj_num);
	p_world->Message_Process_Register(M_MOU_MOV,obj_num);

	return 1;
}

void S_Button::Redraw()
{
	Button_Draw();
}

bool S_Button::Function_Register(G_Object * p_obj,int t)
{
	if(t>=MOU_BUTTON_NUM || t<0) return 0;
	if(fun_rem[t]) return 0;
	fun_rem[t]=p_obj;

	return 1;
}

bool S_Button::Function_Register(G_Object & p_obj,int t)
{
	Function_Register(&p_obj,t);
}

void S_Button::Function_Delete(int t)
{
	if(t>=MOU_BUTTON_NUM || t<0) return;
	fun_rem[t]=0;
}
