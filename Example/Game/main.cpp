#include "Game.h"

#include <iostream>
using namespace std;

int main()
{
	God god;
	
	G_World * p_world = new G_World;
	god.World_Register(p_world);

	L_Window win(POS(100,100),SIZE(700,650));
	win.Window_Show();
	win.Event_Register(MESSAGE{M_MOU_MOV});
	win.Event_Register(MESSAGE{M_MOU_PRE,1});
	win.Event_Register(MESSAGE{M_MOU_PRE,3});
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

	while(Welcome(god,p_world,eye))
		Game_Run(god,p_world);

	return 0;
}
