#ifndef G_OBJECT_H
#define G_OBJECT_H

/*
	This is the base class of all the object.
*/

#include "G_Config.h"

class G_World;

class G_Object
{
	private:
		static OBJECT_NUM obj_cou;							// Remember how many object in all.
		const OBJECT_TYPE obj_type;
		
	protected:
		G_World *p_world;									// This object is belong to which world.
		OBJECT_NUM obj_num;									// The num for this object.

	public:
		G_Object(OBJECT_TYPE);
		virtual ~G_Object()=0;

		virtual int Message_Process(const MESSAGE *)=0;		// Process a message.
		virtual void operator () ();
		int Message_Process(const MESSAGE &);
		
		bool World_Register(G_World *);							// Regeister a god to this object.
		void Register_To_World(G_World *);
		G_World * World_Get() const;
		OBJECT_NUM Obj_Num_Get() const;
		OBJECT_TYPE Obj_Type_Get() const;
};

#endif
