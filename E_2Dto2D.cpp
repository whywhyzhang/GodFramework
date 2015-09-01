/*
	The implement of E_2Dto2D class.
*/

#include "E_2Dto2D.h"
#include "G_World.h"
#include "G_Sprit.h"

bool E_2Dto2D::Sprit_Cmp::operator () (const G_Sprit *p1,const G_Sprit *p2)
{
	int t1,t2;
	
	t1=p1->Pri_Get();
	t2=p2->Pri_Get();
	
	if(t1!=t2) return t1<t2;
	
	return p1->Obj_Num_Get() < p2->Obj_Num_Get();
}

E_2Dto2D::E_2Dto2D()
{
	out_pos=in_pos=POS(0,0);
	out_size=SIZE(700,700);			/////

	obj_rem.clear();
}

E_2Dto2D::E_2Dto2D(POS p1,POS p2,SIZE s)
{
	in_pos=p1;
	out_pos=p2;
	out_size=s;

	obj_rem.clear();
}

E_2Dto2D::~E_2Dto2D()
{}

void E_2Dto2D::Size_Set(SIZE s)
{
	out_size=s;
}

void E_2Dto2D::In_Pos_Set(POS p)
{
	in_pos=p;
}

void E_2Dto2D::Out_Pos_Set(POS p)
{
	out_pos=p;
}

bool E_2Dto2D::Process_Register()
{
	if(p_world==0) return 0;

	p_world->Message_Process_Register(M_PAINT,obj_num);

	return 1;
}

int E_2Dto2D::Message_Process(const MESSAGE *mes)
{
	switch(mes->type)
	{
		case M_PAINT:
			Redraw();
			break;
		default:
			break;
	}
}

bool E_2Dto2D::InRange(G_Sprit *p_spr)
{
	POS p[4];
	SIZE s=p_spr->Size_Get();
	POS tp=POS(in_pos.x+out_size.w,in_pos.y+out_size.h);
	
	p[0]=p[1]=p[2]=p[3]=p_spr->Pos_Get();
	p[1].x+=s.w;
	p[2].y+=s.h;
	p[3].x+=s.w;
	p[3].y+=s.h;
	
	for(int i=0;i<4;++i)
		if(p[i].x>=in_pos.x && p[i].x<=tp.x && p[i].y>=in_pos.y && p[i].y<=tp.y)
			return 1;
		
	return 0;
}

void E_2Dto2D::Redraw()
{
	set <G_Sprit *> ::iterator iter;

	for(iter=obj_rem.begin();iter!=obj_rem.end();++iter)
		if(InRange(*iter))
			(*iter)->Redraw();
		
	p_world->Message_Send(MESSAGE{M_BUF_SHW,out_pos.x,out_pos.y,out_size.w,out_size.h,out_pos.x,out_pos.y});
}

void E_2Dto2D::Object_Register(G_Sprit * p)
{
	if(p_world)
		obj_rem.insert(p);
}

void E_2Dto2D::Object_Delete(G_Sprit * p)
{
	obj_rem.erase(p);
}
