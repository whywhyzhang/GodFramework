#include <string.h>
#include <string>

#include "../../God.h"
#include "../../L_Window.h"
#include "../../S_Button.h"
#include "../../S_Label.h"
#include "../../E_2Dto2D.h"

#include "Calcula.h"

using std::string;

int main()
{
	God god;
	
	G_World *p_world = new G_World;
	L_Window win(POS(0,0),SIZE(700,500));

	S_Button *but[20];
	S_Label  *lab = new S_Label(POS());

	return 0;
}
