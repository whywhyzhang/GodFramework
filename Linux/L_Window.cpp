/*
	This is a class about X window.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <jpeglib.h>
#include <jerror.h>

#include "../include/L_Window.h"

Display * L_Window::xlib_dis=0;
int L_Window::win_cou=0;

L_Window::L_Window()
{
	++win_cou;
	win_size.w=900;  win_size.h=800;
	win_pos.x=0;  win_pos.y=0;
	back_color=COL_WHITE;
	
	if(!xlib_dis) xlib_dis=XOpenDisplay(0);
	xlib_win=XCreateSimpleWindow(xlib_dis,DefaultRootWindow(xlib_dis),win_pos.x,win_pos.y,win_size.w,win_size.h,0,0,back_color);

	XSelectInput(xlib_dis,xlib_win,ExposureMask|KeyPressMask|ButtonReleaseMask|ButtonPressMask|PointerMotionMask);

	p_win_keymouse=new L_Key_Mou_Win(xlib_dis,&xlib_win);
	p_win_monitor=new L_Monitor(xlib_dis,&xlib_win);
}

L_Window::L_Window(POS start,SIZE size)
{
	++win_cou;
	win_size=size;
	win_pos=start;
	back_color=COL_WHITE;
	
	if(!xlib_dis) xlib_dis=XOpenDisplay(0);
	xlib_win=XCreateSimpleWindow(xlib_dis,DefaultRootWindow(xlib_dis),win_pos.x,win_pos.y,win_size.w,win_size.h,0,0,back_color);

	XSelectInput(xlib_dis,xlib_win,ExposureMask|KeyPressMask|ButtonReleaseMask|ButtonPressMask|PointerMotionMask);

	p_win_keymouse=new L_Key_Mou_Win(xlib_dis,&xlib_win);
	p_win_monitor=new L_Monitor(xlib_dis,&xlib_win,back_color);
}

L_Window::L_Window(char *xsever,POS start,SIZE size,COLOR background)
{
	++win_cou;
	win_pos=start;
	win_size=size;
	
	if(!xlib_dis) xlib_dis=XOpenDisplay(xsever);
	
	if(background<0) background=WhitePixel(xlib_dis,DefaultScreen(xlib_dis));
	back_color=background;
	xlib_win=XCreateSimpleWindow(xlib_dis,DefaultRootWindow(xlib_dis),win_pos.x,win_pos.y,win_size.w,win_size.h,0,0,back_color);

	XSelectInput(xlib_dis,xlib_win,ExposureMask|KeyPressMask|ButtonReleaseMask|ButtonPressMask|PointerMotionMask);

	p_win_keymouse=new L_Key_Mou_Win(xlib_dis,&xlib_win);
	p_win_monitor=new L_Monitor(xlib_dis,&xlib_win,back_color);
}

L_Window::~L_Window()
{
	--win_cou;
	XDestroyWindow(xlib_dis,xlib_win);
	if(win_cou==0)
	{
		XCloseDisplay(xlib_dis);
		xlib_dis=0;
	}
}

void L_Window::Window_Close()
{
	XUnmapWindow(xlib_dis,xlib_win);
}

bool L_Window::Window_Show() const
{
	XMapWindow(xlib_dis,xlib_win);
	XFlush(xlib_dis);
}

L_Key_Mou_Win * L_Window::Get_KeyMouse_Pointer() const
{
	return p_win_keymouse;
}

L_Monitor * L_Window::Get_Monitor_Pointer() const
{
	return p_win_monitor;
}

bool L_Window::Event_Register(const EVENT & eve)
{
	p_win_keymouse->Event_Register(eve);
}

void L_Window::Register_To_World(G_World * p)
{
	p_win_keymouse->Register_To_World(p);
	p_win_monitor->Register_To_World(p);
}

int L_Window::get_byte_order ()
{
	union
	{
		char c[sizeof(short)];
		short s;
	} order;

	order.s = 1;
	if ((1 == order.c[0]))
		return LSBFirst;
	else
		return MSBFirst;
}	

bool L_Window::T_PicBuf_To_Image(const unsigned char * buf, SIZE size, void * &ret)
{
	if(xlib_dis==0 || buf==0)
		return 0;
		
	int depth;
	XImage *img = 0;
	Visual *vis;
	double rRatio;
	double gRatio;
	double bRatio;
	int outIndex = 0;	
	int i;
	int numBufBytes = (3 * (size.w * size.h));
	int screen=DefaultScreen(xlib_dis);
		
	depth = DefaultDepth (xlib_dis, screen);
	vis = DefaultVisual (xlib_dis, screen);

	rRatio = vis->red_mask / 255.0;
	gRatio = vis->green_mask / 255.0;
	bRatio = vis->blue_mask / 255.0;
		
	if (depth >= 24)
	{
		size_t numNewBufBytes = (4 * (size.w * size.h));
		unsigned int * newBuf = new unsigned int [numNewBufBytes];
	
		for (i = 0; i < numBufBytes; ++i)
		{
			unsigned int r, g, b;
			r = (buf[i] * rRatio);
			++i;
			g = (buf[i] * gRatio);
			++i;
			b = (buf[i] * bRatio);
					
			r &= vis->red_mask;
			g &= vis->green_mask;
			b &= vis->blue_mask;
			
			newBuf[outIndex] = r | g | b;
			++outIndex;
		}
		
		img = XCreateImage (xlib_dis, CopyFromParent, depth, ZPixmap, 0, (char *) newBuf, size.w, size.h, 32, 0);
	}
	else if (depth >= 15)
	{
		size_t numNewBufBytes = (2 * (size.w * size.h));
		unsigned short * newBuf = new unsigned short [numNewBufBytes];
		
		for (i = 0; i < numBufBytes; ++i)
		{
			unsigned int r, g, b;

			r = (buf[i] * rRatio);
			++i;
			g = (buf[i] * gRatio);
			++i;
			b = (buf[i] * bRatio);
					
			r &= vis->red_mask;
			g &= vis->green_mask;
			b &= vis->blue_mask;
			
			newBuf[outIndex] = r | g | b;
			++outIndex;
		}
		
		img = XCreateImage (xlib_dis, CopyFromParent, depth, ZPixmap, 0, (char *) newBuf, size.w, size.h, 16, 0);
	}
	else
		return 0;

	XInitImage (img);
	
	if ((LSBFirst == get_byte_order ()))
		img->byte_order = LSBFirst;
	else
		img->byte_order = MSBFirst;
	img->bitmap_bit_order = MSBFirst;
	
	ret=(void *)img;

	return 1;
}

bool L_Window::T_Xpm_To_Image(const char * buf, void * ret)
{
}

bool L_Window::T_Image_Destroy(void * p)
{
	if(p==0)
		return 0;
	
	XDestroyImage((XImage *)p);
	
	return 1;
}
