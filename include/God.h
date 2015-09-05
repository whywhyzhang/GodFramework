#ifndef GOD_H
#define GOD_H

/*
	This is the base of this Framework.
	This class will created worlds.
*/

#include "G_Config.h"
#include "G_Object.h"
#include "G_World.h"
#include "G_Input.h"
#include "G_Output.h"
#include "G_Sprit.h"
#include "G_Eye.h"

class God
{
	private:
		map < WORLD_NUM,G_World * > world_rem;

		typedef map < WORLD_NUM,G_World * > ::iterator WORLD_ITER;

	public:
		God();
		~God();

		bool World_Register(G_World *);
		bool World_Delete(WORLD_NUM);

		int Run();
};

#endif
