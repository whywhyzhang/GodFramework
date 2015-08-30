#ifndef G_SPRIT_H
#define G_SPRIT_H

/*
	This is the class about sprit.
*/

#include "G_Object.h"

class G_Sprit : public G_Object
{
	private:

	public:
		G_Sprit();
		~G_Sprit();
		
		virtual int Message_Process(const MESSAGE *)=0;
};

#endif
