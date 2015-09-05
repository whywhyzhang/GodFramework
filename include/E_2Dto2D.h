#ifndef E_2DTO2D_H
#define E_2DTO2D_H

/*
	This is the Eye class 2D To 2D.
	That will change the 2D world to 2D.
*/

#include "G_Eye.h"

class E_2Dto2D : public G_Eye
{
	private:
		class Sprit_Cmp
		{
			public:
				bool operator () (const G_Sprit *, const G_Sprit *);
		};
		
	private:
		POS in_pos;
		// The size of in is the same as the size of out.
		
		set <G_Sprit *,Sprit_Cmp> obj_rem;
		
	private:
		bool InRange(G_Sprit *);

	public:
		E_2Dto2D();
		E_2Dto2D(POS,POS,SIZE);
		E_2Dto2D(SIZE);
		~E_2Dto2D();

		void Size_Set(SIZE);
		void In_Pos_Set(POS);
		void Out_Pos_Set(POS);

		void Object_Register(G_Sprit *);
		void Object_Delete(G_Sprit *);
		
		bool Process_Register();
		int  Message_Process(const MESSAGE *);
		void Redraw();
};

#endif
