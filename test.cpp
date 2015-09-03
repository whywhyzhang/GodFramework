#include "L_Window.h"
#include "S_Button.h"
#include "S_Label.h"
#include "E_2Dto2D.h"
#include "God.h"

#include <iostream>
#include <cstring>
#include <string>

using namespace std;


class Temp : public G_Sprit
{
	public:
		int num;
		S_Label *lab;
		L_Clock *clo;
		Temp()
		{
			lab=0;
			spr_p=POS(0,0);
			spr_size=SIZE(10,10);
		}
		int Message_Process(const MESSAGE *);
		int operator () (int num)
		{
			//return 1230;
			cerr<<"haha\n";
			if(lab)
				(*lab)-=3;
				
			return 0;
	//		cerr<<"haha\n";
	//		MESSAGE mes;
	//		Message_Process(&mes);
	//		p_world->Message_Send(MESSAGE{M_LIN_DRW,10,10,30,30,0});
	//		p_world->Message_Send(MESSAGE{M_BUF_SHW,-1});
		}
};

int Temp::Message_Process(const MESSAGE *mes)
{
	static int cou[10]={};
	
	switch(mes->type)
	{
		case M_MOU_PRE:
	//		cerr<<mes->num[0]<<' '<<mes->num[1]<<' '<<mes->num[2]<<endl; 
			break;
		case M_KEY_PRE:
		{
			//p_world->Message_Send(MESSAGE{M_LIN_DRW,10,10,200,200,0});
			//p_world->Message_Send(MESSAGE{M_BUF_SHW,-1});
			const char *s="heihei";
			MESSAGE mm={M_STR_DRW,100,100,255,6,0};
			mm.p=(void *)s;
			p_world->Message_Send(mm);
			p_world->Message_Send(MESSAGE{M_BUF_SHW,-1});
			break;
		}
		case M_EXPOSE:
			p_world->Message_Send(MESSAGE{M_PAINT});
			break;
		case M_TIM_PER:
			cerr<<mes->num[0]<<' '<<++cou[mes->num[0]]<<endl;
			
			if(cou[mes->num[0]]>=10)
				clo->Event_Delete(EVENT{M_TIM_PER,mes->num[0]});
			break;
		default:
			break;
	}
	
	return 0;
}

int main()
{
	God god;
	G_World * p_world=new G_World;
	L_Window win(POS(10,10),SIZE(700,500));
	Temp * p_temp=new Temp;
	S_Button *but=new S_Button(POS(50,10));
	S_Label * lab=new S_Label(POS(200,200));
	E_2Dto2D *eye=new E_2Dto2D;
	
	but->Text_Set("Button");
	lab->Text_Set("asdfgqwert");

	p_temp->lab=lab;

	lab->Out_Type_Set(4);

	win.Window_Show();

	god.World_Register(p_world);

	p_world->Object_Register(eye);

	win.Event_Register(EVENT{M_KEY_PRE,38});
	win.Event_Register(EVENT{M_MOU_PRE,1});
	win.Event_Register(EVENT{M_MOU_MOV});
	win.Event_Register(EVENT{M_EXPOSE});
	win.Register_To_World(p_world);

	but->Function_Register(p_temp,1);
	p_world->Object_Register(but);
	p_world->Object_Register(lab);
	
	p_world->Object_Register(p_temp);
	p_world->Message_Process_Register(M_KEY_PRE,p_temp->Obj_Num_Get());
	p_world->Message_Process_Register(M_MOU_PRE,p_temp->Obj_Num_Get());

	p_world->Message_Process_Register(M_EXPOSE,p_temp->Obj_Num_Get());
	
/*	L_Clock *clo=new L_Clock();
	clo->Event_Register(EVENT{M_TIM_PER,1,0,500000});
	//clo->Event_Register(EVENT{M_TIM_PER,2,0,1000000});
	//clo->Event_Register(EVENT{M_TIM_PER,3,0,100000});
	clo->Event_Register(EVENT{M_TIM_PER,1,0,100000});
	p_world->Object_Register(clo);
	p_temp->clo=clo;
	
	p_world->Message_Process_Register(M_TIM_PER,p_temp->Obj_Num_Get());*/

	cerr<<god.Run()<<endl;

	return 0;
}

/*
int main()
{
	God god;
	G_World * p_world = new G_World;
	Temp *p1=new Temp, *p2=new Temp, *p3=new Temp, *p4=new Temp;
	
	p1->Pri_Set(15);
	p2->Pri_Set(1);
	p3->Pri_Set(12);
	p4->Pri_Set(1);
	
	p1->num=1;
	p2->num=2;
	p3->num=3;
	p4->num=4;
	
	p4->Pos_Set(POS(-51,10));
	
	E_2Dto2D * eye = new E_2Dto2D(POS(0,0),POS(0,0),SIZE(50,50));
	
	god.World_Register(p_world);
	p_world->Object_Register(eye);
	p_world->Object_Register(p1);
	p_world->Object_Register(p2);
	p_world->Object_Register(p3);
	p_world->Object_Register(p4);
	
	cout<<eye->getnum()<<endl;
	
	p_world->Message_Send(MESSAGE{M_PAINT});
	
	god.Run();
}
*/
