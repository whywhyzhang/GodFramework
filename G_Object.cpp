/*
	This is the abstract of all object.
*/

#include "G_Object.h"
#include "G_World.h"

int G_Object::obj_cou=0;

G_Object::G_Object(OBJECT_TYPE type,bool t):obj_type(type)
{
	is_vis=t;
	
	obj_num=++obj_cou;
	p_world=0;
}

G_Object::~G_Object()
{
	if(p_world)
	{
		if(is_vis) p_world->Visual_Change(obj_num,0);
		p_world->Object_Delete(obj_num);
	}
}

bool G_Object::World_Register(G_World *poi)
{
	if(p_world) return 0;

	p_world=poi;
	if(is_vis)
		p_world->Visual_Change(obj_num,is_vis);
	return 1;
}

bool G_Object::Process_Register()
{}

void G_Object::Register_To_World(G_World *poi)
{
	poi->Object_Register(this);
}

void G_Object::operator () ()
{}

int G_Object::Message_Process(const MESSAGE & temp)
{
	Message_Process(&temp);
}

G_World * G_Object::World_Get() const
{
	return p_world;
}

OBJECT_NUM G_Object::Obj_Num_Get() const
{
	return obj_num;
}

OBJECT_TYPE G_Object::Obj_Type_Get() const
{
	return obj_type;
}

void G_Object::Visual_Set(bool t)
{
	if(t==is_vis) return;
	is_vis=t;
	if(p_world)
		p_world->Visual_Change(obj_num,t);
}

bool G_Object::Visual_Get()
{
	return is_vis;
}

void G_Object::Redraw()
{}
