/*
	The implement of S_Button.
*/

#include "S_Button.h"
#include "G_World.h"

S_Button::S_Button()
{
	spr_p=POS(0,0);
	spr_size=SIZE(40,20);

	fun_rem=0;
}

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
	p_world->Message_Send(MESSAGE{});

}

int S_Button::Message_Process(const MESSAGE *mes)
{
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
