#ifndef S_BUTTON_H
#define S_BUTTON_H

/*
	This is a inherited class of G_Sprit.
	About Button.
*/

#include "G_Sprit.h"

class S_Button : public G_Sprit
{
	private:
		POS spr_p;
		SIZE spr_size;
		
		G_Object * fun_rem;

	public:
		S_Button(POS=POS(0,0),SIZE=SIZE(100,50));
		~S_Button();

		virtual void Button_Draw();

		int  Message_Process(const MESSAGE *);
		
		void Click_Register(G_World *);
		bool Function_Register(G_Object *);
		bool Function_Register(G_Object &);
		void Function_Delete();
};

#endif
