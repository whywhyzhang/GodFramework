/*
	This is the class about sprit.
*/

#include "../include/G_Sprit.h"

G_Sprit::G_Sprit():G_Object(OBJ_SPR,1)
{}

G_Sprit::~G_Sprit()
{}

int G_Sprit::operator () (int obj_num)
{
	return 0;
}

POS G_Sprit::Pos_Get() const
{
	return spr_p;
}

SIZE G_Sprit::Size_Get() const
{
	return spr_size;
}

int G_Sprit::Pri_Get() const
{
	return pri_num;
}

void G_Sprit::Pos_Set(POS p)
{
	spr_p=p;
}

void G_Sprit::Size_Set(SIZE s)
{
	spr_size=s;
}

void G_Sprit::Pri_Set(int x)
{
	pri_num=x;
}

void G_Sprit::Move(POS s)
{
	spr_p.x+=s.x;
	spr_p.y+=s.y;
}
