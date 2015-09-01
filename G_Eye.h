#ifndef G_EYE_H
#define G_EYE_H

/*
   	This is the class G_Eye.
*/

#include "G_Object.h"

class G_Eye:public G_Object
{
	protected:
		POS out_pos;
		SIZE out_size;

	public:
		G_Eye();
		virtual ~G_Eye()=0;

		virtual int Message_Process(const MESSAGE *)=0;
		virtual void Object_Register(G_Sprit *)=0;
		virtual void Object_Delete(G_Sprit *)=0;
};

#endif
