/*
   	The implement of G_World.
*/

#include "../include/G_World.h"
#include "../include/God.h"

WORLD_NUM G_World::world_cou=0;

G_World::G_World()
{
	world_num=++world_cou;
	p_god=0;

	while(!mes_que.empty()) mes_que.pop();
	while(!world_mes_que.empty()) world_mes_que.pop();
	for(int i=0;i<OBJ_KIND;++i)	obj_type_rem[i].clear();
	obj_rem.clear();
	mes_obj_rem.clear();
	
	other_world_rem.clear();
}

G_World::~G_World()
{
	if(p_god)
		p_god->World_Delete(world_num);

	OBJ_ITER iter;
	OBJECT_TYPE type_temp;
	for(iter=obj_rem.begin();iter!=obj_rem.end();++iter)
	{
		(iter->second)->World_Clear();					// !!!
		type_temp=(iter->second)->Obj_Type_Get();
		obj_type_rem[type_temp].erase((iter->second)->Obj_Num_Get());				// !!!
		delete (*iter).second;
		(*iter).second=0;
	}

	while(!mes_que.empty())
	{
		delete mes_que.front();				// For some compliers this will be error. Because they don't think that const pointer can be delete.
		mes_que.pop();
	}
	
	while(!world_mes_que.empty())
	{
		delete world_mes_que.front();
		world_mes_que.pop();
	}
}

God * G_World::God_Get() const
{
	return p_god;
}

void G_World::God_Set(God *p)
{
	p_god=p;
}

WORLD_NUM G_World::World_Num_Get() const
{
	return world_num;
}

int G_World::Run()
{
	const MESSAGE *p_temp;
	int temp;
	
	Event_Happend();

	// Process all the Message in the queue.
	// Maybe multi thread.
	while(!mes_que.empty())
	{
		p_temp=mes_que.front();
		mes_que.pop();

		if(temp=Message_Process(p_temp))
			return temp;
	}

	while(!world_mes_que.empty())
	{
		p_temp=world_mes_que.front();
		world_mes_que.pop();

		if(temp=Message_Process(p_temp))
			return temp;
	}

	return 0;
}

// Judge wether there are some events happend for a IO Object (External Object).
void G_World::Event_Happend()
{
	OBJ_ITER iter;
	for(iter=obj_type_rem[OBJ_IN].begin();iter!=obj_type_rem[OBJ_IN].end();++iter)
		((G_Input *)(*iter).second)->Event_Happend();
}

int G_World::Message_Process(const MESSAGE *mes)
{
	pair <MES_ITER,MES_ITER> temp=mes_obj_rem.equal_range(mes->type);
	MES_ITER iter,pre_iter;
	OBJ_ITER obj;
	int ret_temp;

	for(iter=temp.first;iter!=temp.second;++iter)
	{
		obj=obj_rem.find((*iter).second);
		if(obj!=obj_rem.end())
		{
			if(ret_temp=((*obj).second->Message_Process(mes)))
				return ret_temp;
		}
		else
		{
			pre_iter=iter;
			
			if(pre_iter!=mes_obj_rem.begin())			// Oh my God , What a God Bug.
			{
				--pre_iter;
				mes_obj_rem.erase(iter);				// !!!
				iter=pre_iter;
			}
			else
			{
				mes_obj_rem.erase(iter);
				iter=mes_obj_rem.begin();
			}
		}
	}
	
	return 0;
}

void G_World::Message_Process_Register(MES_TYPE mes,OBJECT_NUM num)
{
	mes_obj_rem.insert(pair <MES_TYPE,OBJECT_NUM> (mes,num));
}

bool G_World::Message_Process_Delete(MES_TYPE mes,OBJECT_NUM num)
{
	pair <MES_ITER,MES_ITER> temp=mes_obj_rem.equal_range(mes);
	MES_ITER iter,preiter;
	bool ok;

	while(mes_obj_rem.begin()->second==num) mes_obj_rem.erase(mes_obj_rem.begin());			///////////

	for(iter=temp.first;iter!=temp.second;++iter)
		if((*iter).second==num)
		{
			ok=1;
			preiter=iter;
			--preiter;
			mes_obj_rem.erase(iter);
			iter=preiter;
		}

	return ok;
}

void G_World::Message_Delete(MES_TYPE mes)
{
	mes_obj_rem.erase(mes);
}

void G_World::Message_Send(const MESSAGE &mes)
{
	MESSAGE *temp=new MESSAGE(mes);
	mes_que.push(temp);
}

void G_World::World_Message_Send(const MESSAGE &mes)
{
	MESSAGE *temp=new MESSAGE(mes);
	world_mes_que.push(temp);
}

bool G_World::Send_Message_To_World(WORLD_NUM num, const MESSAGE &mes)
{
	WORLD_ITER iter=other_world_rem.find(num);
	if(iter==other_world_rem.end()) return 0;
	
	(iter->second)->World_Message_Send(mes);
	
	return 1;
}

bool G_World::Object_Register(G_Object * p_obj)
{
	if(!p_obj) return 0;
	
	if(p_obj->World_Get())					/////
		return 0;

	typedef pair <OBJECT_NUM,G_Object *> pii;

	OBJECT_TYPE obj_type=p_obj->Obj_Type_Get();
	OBJECT_NUM obj_num=p_obj->Obj_Num_Get();

	obj_type_rem[obj_type].insert(pii (obj_num,p_obj));
	obj_rem.insert(pii (obj_num,p_obj));

	p_obj->World_Register(this);
	p_obj->Process_Register();

	return 1;
}

bool G_World::Object_Delete(const OBJECT_NUM num)
{
	OBJ_ITER iter=obj_rem.find(num);
	if(iter==obj_rem.end()) return 0;

	OBJECT_TYPE obj_type=iter->second->Obj_Type_Get();
	obj_type_rem[obj_type].erase(num);
	obj_rem.erase(num);

	return 1;
}

void G_World::Visual_Change(OBJECT_NUM num, bool type)
{
	OBJ_ITER iter=obj_rem.find(num);
	if(iter==obj_rem.end()) return;
	
	OBJ_ITER iter_eye;
	G_Eye *p;
	
	for(iter_eye=obj_type_rem[OBJ_EYE].begin();iter_eye!=obj_type_rem[OBJ_EYE].end();++iter_eye)
	{		
		p=(G_Eye *)(iter_eye->second);
		
		if(type)
			p->Object_Register((G_Sprit *)iter->second);
		else
			p->Object_Delete((G_Sprit *)iter->second);
	}
}

void G_World::Other_World_Register(G_World * p)
{
	if(!p) return;
	
	WORLD_NUM num =  p->World_Num_Get();
	other_world_rem.insert(pair <WORLD_NUM, G_World *> (num,p));
}

bool G_World::Other_World_Delete(WORLD_NUM num)
{
	return other_world_rem.erase(num);
}
