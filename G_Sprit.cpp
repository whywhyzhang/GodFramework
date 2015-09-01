/*
	This is the class about sprit.
*/

#include "G_Sprit.h"

G_Sprit::G_Sprit():G_Object(OBJ_SPR,1)
{}

G_Sprit::~G_Sprit()
{}

POS G_Sprit::Pos_Get()
{
	return spr_p;
}

SIZE G_Sprit::Size_Get()
{
	return spr_size;
}

void G_Sprit::Pos_Set(POS p)
{
	spr_p=p;
}

void G_Sprit::Move(POS s)
{
	spr_p.x+=s.x;
	spr_p.y+=s.y;
}
