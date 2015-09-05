/*
	The implement of class God.
*/

#include "../include/God.h"

God::God()
{
	world_rem.clear();
}

God::~God()
{
	WORLD_ITER iter;
	
	for(iter=world_rem.begin();iter!=world_rem.end();++iter)
	{
		(iter->second)->God_Set(0);					// !!!
		delete iter->second;
		iter->second=0;
	}
}

bool God::World_Register(G_World * p_world)
{
	if(p_world->God_Get()) return 0;
	p_world->God_Set(this);

	WORLD_NUM num=p_world->World_Num_Get();
	world_rem.insert(pair < WORLD_NUM,G_World * > (num,p_world));

	return 1;
}

bool God::World_Delete(WORLD_NUM num)
{
	WORLD_ITER iter=world_rem.find(num);

	if(iter==world_rem.end()) return 0;

	world_rem.erase(iter);
	return 1;
}

int God::Run()
{
	WORLD_ITER iter;
	int temp;
	
	while(1)
	{
		for(iter=world_rem.begin();iter!=world_rem.end();++iter)			// Maybe multi thread there.
			if(temp=(iter->second)->Run())
				return temp;
	}

	return 0;
}
