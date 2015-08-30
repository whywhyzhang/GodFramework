#include "L_Window.h"
#include "God.h"

#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

class Temp : public G_Sprit
{
	public:
		int Message_Process(const MESSAGE *);
};

int Temp::Message_Process(const MESSAGE *mes)
{
	cerr<<"OK\n";
	cerr<<mes->type<<' '<<mes->num[0]<<endl;
}

int main()
{
	God god;
	G_World * p_world=new G_World;
	G_Input * p_input;
	L_Window win(POS(10,10),SIZE(700,500));
	Temp * p_temp=new Temp;

	win.Window_Show();

	god.World_Register(p_world);

	p_input=win.Get_KeyMouse_Pointer();

	p_input->Event_Register(EVENT{M_KEY_PRE,38});

	p_world->Object_Register(p_input);
	p_world->Object_Register(p_temp);
	p_world->Message_Process_Register(M_KEY_PRE,p_temp->Obj_Num_Get());

	god.Run();

	return 0;
}
