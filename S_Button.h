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
		S_Button();
		S_Button(POS,SIZE);
		~S_Button();

		virtual void Button_Draw();

		int Message_Process(const MESSAGE *);
		bool Function_Register(G_Object *);
		bool Function_Register(G_Object &);
};

#endif
