#ifndef S_IMAGINE_H
#define S_IMAGINE_H

/*
	This is the Sprit Image.
*/

#include "G_Sprit.h"

class S_Image : public G_Sprit
{
	private:
		void * image;
		POS pic_draw_pos;

	public:
		S_Image(POS=POS(0,0));
		~S_Image();

		bool Image_Set(const unsigned char * ,SIZE);

		void Image_Draw();
		void Redraw();
		
		void PicDraw_Pos_Set(POS);

		int  Message_Process(const MESSAGE *mes);
};

#endif
