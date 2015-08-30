/*
	This is the abstract of all object.
*/

#include "G_Object.h"
#include "G_World.h"

int G_Object::obj_cou=0;

G_Object::G_Object(OBJECT_TYPE type):obj_type(type)
{
	obj_num=++obj_cou;
	p_world=0;
}

G_Object::~G_Object()
{
	if(p_world)
		p_world->Object_Delete(obj_num);
}

bool G_Object::World_Register(G_World *poi)
{
	if(p_world) return 0;

	p_world=poi;
	return 1;
}

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
