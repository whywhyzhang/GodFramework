#ifndef GAME_H
#define GAME_H

#include "../../God.h"
#include "../../L_Window.h"
#include "../../S_Button.h"
#include "../../S_Label.h"
#include "../../S_Image.h"
#include "../../E_2Dto2D.h"
#include "../../T_Picture.h"

class Wel_Func : public G_Sprit
{
	private:
		int rem1,rem2;

	public:
		Wel_Func();
		int Message_Process(const MESSAGE *);
		int operator () (int);

		void Register(int,int);
};

bool Welcome();
bool Game_Run();

G_World * Out_World_Init(God &,L_Window &);
G_World * Phy_World_Init(God &);

#endif
