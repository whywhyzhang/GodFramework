#ifndef G_OUTPUT_H
#define G_OUTPUT_H

/*
	This is a abstract class of output.
*/

#include "G_Object.h"

// The class about Output.
class G_Output:public G_Object
{
	private:

	public:
		G_Output();
		virtual ~G_Output()=0;

		virtual int Message_Process(const MESSAGE *)=0;						// The function that belong to G_Object class.
//		virtual int Message_Process(const MESSAGE &)=0;
};

#endif
