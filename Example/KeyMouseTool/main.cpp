#include <string.h>
#include <string>
#include <stdio.h>

#include "../../include/God.h"
#include "../../include/L_Window.h"
#include "../../include/S_Button.h"
#include "../../include/S_Label.h"
#include "../../include/E_2Dto2D.h"

using std::string;

class Func : public G_Sprit
{
	private:
		S_Label *moubut, *keybut, *moux, *mouy;

	public:
		Func()
		{
			is_vis=0;
		}

		void Register(S_Label *p1,S_Label *p2,S_Label *p3,S_Label *p4)
		{
			moubut=p1;
			keybut=p2;
			moux=p3;
			mouy=p4;
		}

		int Message_Process(const MESSAGE * mes)
		{
			char ts[50];

			switch(mes->type)
			{
				case M_KEY_PRE:
					if(keybut)
					{
						sprintf(ts,"%d",mes->num[0]);
						keybut->Text_Set(ts);
					}
					break;
				case M_MOU_PRE:
					if(moubut)
					{
						sprintf(ts,"%d",mes->num[0]);
						moubut->Text_Set(ts);
					}
					break;
				case M_MOU_MOV:
					if(moux && mouy)
					{
						sprintf(ts,"%d",mes->num[0]);
						moux->Text_Set(ts);
						sprintf(ts,"%d",mes->num[1]);
						mouy->Text_Set(ts);
					}
					break;
				default:
					break;
			}
			
			return 0;
		}

		bool Process_Register()
		{
			p_world->Message_Process_Register(M_KEY_PRE,obj_num);
			p_world->Message_Process_Register(M_MOU_PRE,obj_num);
			p_world->Message_Process_Register(M_MOU_MOV,obj_num);
		}
};

int main()
{
	God god;

	G_World * p_world = new G_World;
	god.World_Register(p_world);

	L_Window win(POS(10,10),SIZE(700,500));
	win.Window_Show();
	win.Event_Register(EVENT{M_KEY_PRE,-1});
	win.Event_Register(EVENT{M_MOU_MOV});
	win.Event_Register(EVENT{M_EXPOSE});
	for(int i=0;i<10;++i)
		win.Event_Register(EVENT{M_MOU_PRE,i});
	win.Register_To_World(p_world);

	E_2Dto2D * eye = new E_2Dto2D(SIZE(700,500));
	p_world->Object_Register(eye);
	p_world->Message_Process_Register(M_EXPOSE,eye->Obj_Num_Get());

	S_Label * lab1 = new S_Label(POS(155,50),SIZE(150,50),"Mouse Button:");
	S_Label * lab2 = new S_Label(POS(155,210),SIZE(150,50),"Keyboard Button:");
	S_Label * lab3 = new S_Label(POS(155,370),SIZE(150,50),"Mouse Pos:");
	p_world->Object_Register(lab1);
	p_world->Object_Register(lab2);
	p_world->Object_Register(lab3);

	S_Label * moubut = new S_Label(POS(350,50),SIZE(50,50),0,1);
	S_Label * keybut = new S_Label(POS(350,210),SIZE(50,50),0,1);
	S_Label * moux = new S_Label(POS(350,370),SIZE(50,50),0,1);
	S_Label * mouy = new S_Label(POS(420,370),SIZE(50,50),0,1);
	p_world->Object_Register(moubut);
	p_world->Object_Register(keybut);
	p_world->Object_Register(moux);
	p_world->Object_Register(mouy);

	Func * p_fun = new Func;
	p_fun->Register(moubut,keybut,moux,mouy);
	p_world->Object_Register(p_fun);

	god.Run();

	return 0;
}
