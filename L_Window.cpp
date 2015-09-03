/*
	This is a class about X window.
*/

#include "L_Window.h"

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
