/*
	This is the implementation of class L_Input.
	Keyboard and mouse use the event about Xlib.
	The clokc use function gettimeofday.
*/

#include <X11/Xlib.h>
#include <cstring>

#include "L_Input.h"

////////////////////////////////////////////////////
// The function of L_Key_Mouse.

L_Key_Mou_Win::L_Key_Mou_Win(Display *dis, Window *win)
{
	p_xlib_dis=dis;
	p_xlib_win=win;

	memset(event_rem,0,sizeof(event_rem));
	memset(key_state,0,sizeof(key_state));
}

L_Key_Mou_Win::~L_Key_Mou_Win()
{}

bool L_Key_Mou_Win::Event_Register(const EVENT &event)
{
	switch(event.type)
	{
		case M_KEY_PRE:
			event_rem[event.num[0]] |= LM_KEY_PRE;
			break;
		case M_KEY_REL:
			event_rem[event.num[0]] |= LM_KEY_REL;
			break;
		case M_MOU_PRE:
			event_rem[event.num[0]] |= LM_MOU_PRE;
			break;
		case M_MOU_REL:
			event_rem[event.num[0]] |= LM_MOU_REL;
			break;
		case M_MOU_MOV:
			event_rem[0] |= LM_MOU_MOV;
			break;
		case M_EXPOSE:
			event_rem[0] |= LM_EXPOSE;
			break;
		default:
			return 0;
			break;
	}

	return 1;
}

bool L_Key_Mou_Win::Event_Delete(const EVENT &event)
{
	switch(event.type)
	{
		case M_KEY_PRE:
			event_rem[event.num[0]] &= ~LM_KEY_PRE;
			break;
		case M_KEY_REL:
			event_rem[event.num[0]] &= ~LM_KEY_REL;
			break;
		case M_MOU_PRE:
			event_rem[event.num[0]] &= ~LM_MOU_PRE;
			break;
		case M_MOU_REL:
			event_rem[event.num[0]] &= ~LM_MOU_REL;
			break;
		case M_MOU_MOV:
			event_rem[0] &= ~LM_MOU_MOV;
			break;
		case M_EXPOSE:
			event_rem[0] &= ~LM_EXPOSE;
			break;
		default:
			return 0;
			break;
	}

	return 1;
}

void L_Key_Mou_Win::Event_Happend()
{
	if(XEventsQueued(p_xlib_dis,QueuedAfterReading))
		XNextEvent(p_xlib_dis,&xlib_event);
	else
		return;

	switch(xlib_event.type)
	{
		case KeyPress:
			if(event_rem[xlib_event.xkey.keycode] & LM_KEY_PRE)
				p_world->Message_Send(MESSAGE{M_KEY_PRE,xlib_event.xkey.keycode});
			break;
		case KeyRelease:
			if((event_rem[xlib_event.xkey.keycode] & LM_KEY_REL) && ! Key_State_Judge(xlib_event.xkey.keycode))
				p_world->Message_Send(MESSAGE{M_KEY_REL,xlib_event.xkey.keycode});
			break;
		case Expose:
			if(event_rem[0] & LM_EXPOSE)
				p_world->Message_Send(MESSAGE{M_EXPOSE});
			break;
		case ButtonPress:
			if(event_rem[xlib_event.xbutton.button] & LM_MOU_PRE)
				p_world->Message_Send(MESSAGE{M_MOU_PRE,xlib_event.xbutton.button,xlib_event.xbutton.x,xlib_event.xbutton.y});
			break;
		case ButtonRelease:
			if(event_rem[xlib_event.xbutton.button] & LM_MOU_REL)
				p_world->Message_Send(MESSAGE{M_MOU_REL,xlib_event.xbutton.button,xlib_event.xbutton.x,xlib_event.xbutton.y});
			break;
		case MotionNotify:
			if(event_rem[0] & LM_MOU_MOV)
				p_world->Message_Send(MESSAGE{M_MOU_MOV,xlib_event.xmotion.x,xlib_event.xmotion.y});
			break;
		default:
			break;
	}
}

int L_Key_Mou_Win::Message_Process(const MESSAGE *mes)
{}

bool L_Key_Mou_Win::Key_State_Judge(int key)
{
	XQueryKeymap(p_xlib_dis,key_state);
	return key_state[key/8] & (1<<(key-8*(key/8)));
}

/////////////////////////////////////////////////////////////
// The function of L_Clock.

L_Clock::L_Clock()
{}

L_Clock::~L_Clock()
{}

bool L_Clock::Event_Register(const EVENT &event)
{}

bool L_Clock::Event_Delete(const EVENT &event)
{}

void L_Clock::Event_Happend()
{}

int L_Clock::Message_Process(const MESSAGE *mes)
{}
