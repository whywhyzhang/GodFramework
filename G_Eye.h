#ifndef G_EYE_H
#define G_EYE_H

/*
   	This is the class G_Eye.
*/

#include "G_Object.h"

class G_Eye:public G_Object
{
	protected:
		POS eye_p;
		double eye_ang;
		int eye_height;
		POS in_p;
		SIZE in_size;
		POS out_p;
		SIZE out_size;

	public:
		G_Eye();
		virtual ~G_Eye()=0;

		virtual int Message_Process(const MESSAGE *)=0;
};

#endif
