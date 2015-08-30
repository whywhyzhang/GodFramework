#include "L_Window.h"
#include "S_Button.h"
#include "God.h"

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Temp : public G_Sprit
{
	public:
		int Message_Process(const MESSAGE *);
		void operator () ()
		{
			cerr<<"haha\n";
			MESSAGE mes;
			Message_Process(&mes);
			p_world->Message_Send(MESSAGE{M_LIN_DRW,10,10,30,30,0});
			p_world->Message_Send(MESSAGE{M_BUF_SHW,-1});
		}
};

int Temp::Message_Process(const MESSAGE *mes)
{
	switch(mes->type)
	{
		case M_MOU_PRE:
			cerr<<mes->num[0]<<' '<<mes->num[1]<<' '<<mes->num[2]<<endl;
	}
}

int main()
{
	God god;
	G_World * p_world=new G_World;
	L_Window win(POS(10,10),SIZE(700,500));
	Temp * p_temp=new Temp;
	S_Button *but=new S_Button(POS(50,10));

	win.Window_Show();

	god.World_Register(p_world);

	win.Event_Register(EVENT{M_KEY_PRE,38});
	win.Event_Register(EVENT{M_MOU_PRE,1});
	win.Event_Register(EVENT{M_EXPOSE});
	win.Register_To_World(p_world);

	but->Function_Register(p_temp);
	but->Click_Register(p_world);
	p_world->Object_Register(but);
	but->Button_Draw();
	
	p_world->Object_Register(p_temp);
	p_world->Message_Process_Register(M_KEY_PRE,p_temp->Obj_Num_Get());
	p_world->Message_Process_Register(M_MOU_PRE,p_temp->Obj_Num_Get());

	god.Run();

	return 0;
}
