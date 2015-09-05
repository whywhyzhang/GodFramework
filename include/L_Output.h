#ifndef L_OUTPUT_H
#define L_OUTPUT_H

/*
	This is the class about linux output.
*/

#include <X11/Xlib.h>

#include "G_Output.h"

// The class about linux Monitor.
class L_Monitor:public G_Output
{
	private:
		Display *p_xlib_dis;
		Window *p_xlib_win;
		GC xlib_gc;
		Pixmap xlib_pixmap;
		
		POS pixmap_pos;
		SIZE pixmap_size;
		COLOR back_color;
		XFontStruct * p_font;
		int font_height;

	public:
		L_Monitor(Display * =NULL,Window * =NULL,COLOR =-1);
		~L_Monitor();

		virtual int Message_Process(const MESSAGE *);
		
		virtual void PicBuffer_Show();
		virtual void PicBuffer_Show(POS,SIZE,POS);						// Show the buffer(from pos) to monitor(to pos) with a size.

		virtual void Line_Set(int =-1, int =-1, int =-1, int =-1);		// Set the width,line style,cap style and join style of line.
		virtual void Fill_Set(int);										// Set the fill style for a fill.
		virtual void BackColor_Set(COLOR);								// Set the Background color.
		virtual void ForeColor_Set(COLOR);								// Set the Foreground color.
		virtual bool Font_Set(const char *);							// Set the font.

		virtual void String_Draw(POS,COLOR,char *,int,int);				// Output a string to pos, with a length and whether pos is bottom-left or others.
		virtual void Point_Draw(POS,COLOR);								// Draw a Point on POS with a COLOR.
		virtual void Line_Draw(POS,POS,COLOR);							// Draw a line from POS to POS with a COLOR.
		virtual void Rect_Draw(POS,SIZE,COLOR);
		virtual void Circle_Draw(POS,int,int,double,double,COLOR);		// Draw a circle(or oval) on POS with Rx and Ry and a COLOR, start from double1, has a angle of double2(Counterclockwise,0-360).
		virtual void Rect_Fill_Draw(POS,SIZE,COLOR);					// Draw a Rectangle and fill it, form POS with a SIZE, with COLOR.
		virtual void Picture_Draw(POS,POS,SIZE,bool,unsigned char *);	// Draw a picture(char buffer) in POS with a SIZE from the POS2 of picture.
		
		void Register_To_World(G_World *);
};

// The class about linux audio.
class L_Audio:public G_Output
{
	private:

	public:
		L_Audio();
		~L_Audio();

		virtual int Message_Process(const MESSAGE *);
};

#endif
