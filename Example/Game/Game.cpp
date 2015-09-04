#include "Game.h"

Wel_Func::Wel_Func()
{
	rem1=rem2=0;
}

int Wel_Func::Message_Process(const MESSAGE *)
{
	return 0;
}

int Wel_Func::operator () (int num)
{
	if(num==rem1)
		return 1;
	else if(num==rem2)
		return 2;

	return 0;
}

void Wel_Func::Register(int t,int num)
{
	if(t==1)
		rem1=num;
	else if(t==2)
		rem2=num;
}

bool Welcome()
{
	God god;

	G_World * p_world = new G_World;
	god.World_Register(p_world);

	L_Window win(POS(100,100),SIZE(700,650));
	win.Window_Show();
	win.Event_Register(MESSAGE{M_MOU_MOV});
	win.Event_Register(MESSAGE{M_MOU_PRE,1});
	win.Event_Register(MESSAGE{M_EXPOSE});
	win.Register_To_World(p_world);

	E_2Dto2D * eye = new E_2Dto2D(SIZE(700,650));
	p_world->Object_Register(eye);
	p_world->Message_Process_Register(M_EXPOSE,eye->Obj_Num_Get());

	T_JPEG * picbuf = new T_JPEG;
	picbuf->Jpg_Open("Welcome.jpg");
	S_Image * image = new S_Image;
	image->Image_Set(picbuf->Pic_Buf_Get(),picbuf->Size_Get());
	p_world->Object_Register(image);

	S_Button * but1 = new S_Button(POS(300,190),SIZE(100,50),"Start");
	S_Button * but2 = new S_Button(POS(300,390),SIZE(100,50),"Exit");

	Wel_Func func;
	func.Register(2,but1->Obj_Num_Get());
	func.Register(1,but2->Obj_Num_Get());
	
	but1->Function_Register(func,1);
	but2->Function_Register(func,1);
	p_world->Object_Register(but1);
	p_world->Object_Register(but2);

	return god.Run()-1;
}

bool Game_Run()
{
	God god;

	L_Window win(POS(100,100),SIZE(700,650));
	win.Window_Show();

	G_World * out_world = Out_World_Init(god,win);
	G_World * phy_world = Phy_World_Init(god);

	out_world->Other_World_Register(phy_world);
	phy_world->Other_World_Register(out_world);

	god.Run();

	return 0;
}

G_World * Out_World_Init(God &god,L_Window &win)
{
	G_World * p_world = new G_World;

	return p_world;
}

G_World * Phy_World_Init(God &god)
{
	G_World * p_world = new G_World;

	return p_world;
}
