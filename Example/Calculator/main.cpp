#include "Calcula.h"

using std::string;

int main()
{
	God god;
	
	G_World *p_world = new G_World;
	god.World_Register(p_world);

	L_Window win(POS(100,100),SIZE(700,500));
	win.Window_Show();
	Window_Init(win);
	win.Register_To_World(p_world);

	E_2Dto2D * eye = new E_2Dto2D(SIZE(700,500));
	p_world->Object_Register(eye);
	p_world->Message_Process_Register(M_EXPOSE,eye->Obj_Num_Get());

	Cal_Lab * lab = new Cal_Lab(POS(150,50),SIZE(400,50),0,1,48);
	p_world->Object_Register(lab);

	Cal_But * but[20];
	Button_Init(but,lab);
	for(int i=0;i<20;++i)
		p_world->Object_Register(but[i]);

	god.Run();

	return 0;
}
