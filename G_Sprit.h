#ifndef G_SPRIT_H
#define G_SPRIT_H

/*
	This is the class about sprit.
*/

#include "G_Object.h"

class G_Sprit : public G_Object
{
	protected:
		POS spr_p;
		SIZE spr_size;

	public:
		G_Sprit();
		~G_Sprit();
		
		virtual int Message_Process(const MESSAGE *)=0;
		
		POS Pos_Get();
		SIZE Size_Get();
		
		virtual void Pos_Set(POS);
		virtual void Move(POS);			// Move the spr_p by POS.
};

#endif
