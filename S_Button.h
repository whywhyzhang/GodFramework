#ifndef S_BUTTON_H
#define S_BUTTON_H

/*
	This is a inherited class of G_Sprit.
	About Button.
*/

#include <string>

#include "G_Sprit.h"

using std::string;

class S_Button : public G_Sprit
{
	private:
		bool mou_on;								// Whether the mouse if on the Button.
		string text;
		
		G_Object * fun_rem[MOU_BUTTON_NUM];			// The function that'll be called when the ith button is clicked.

	public:
		S_Button(POS=POS(0,0),SIZE=SIZE(100,50),char * =0,int=0);
		~S_Button();

		virtual void Button_Draw();

		int  Message_Process(const MESSAGE *);
		bool Process_Register();
		void Redraw();
		
		void Text_Set(char *);

		bool Function_Register(G_Object *,int);
		bool Function_Register(G_Object &,int);
		void Function_Delete(int);
};

#endif
