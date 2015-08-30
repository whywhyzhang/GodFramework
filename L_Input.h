#ifndef L_INPUT_H
#define L_INPUT_H

/*
	The input device about linux.
	Keyboard,mouse,clock.
*/

/*
	According to Xlib Event.
	The keyboard event if 
*/

#include <X11/Xlib.h>

#include "L_Config.h"

#include "G_Input.h"
#include "God.h"

// The class about keyboard and mouse
class L_Key_Mou_Win:public G_Input
{
	private:
		Display *p_xlib_dis;
		Window *p_xlib_win;
		XEvent xlib_event;

		L_MES_STA event_rem[256];											// Remember the message the event[i] will send, 0 means no message.
		char key_state[32];

	public:
		L_Key_Mou_Win(Display * =NULL,Window * =NULL);						// XOpenDisplay open the string.
		~L_Key_Mou_Win();

		virtual bool Event_Register(const EVENT &);							// Register a event.
		virtual bool Event_Delete(const EVENT &);
		virtual void Event_Happend();										// Judge whether a Event happend for a input device.
		
		virtual int Message_Process(const MESSAGE *);						// The function that belong to G_Object class.

		bool Key_State_Judge(int);
};

// The class about clock.
class L_Clock:public G_Input
{
	private:
		struct timeval time_start;

	public:
		L_Clock();
		~L_Clock();

		virtual bool Event_Register(const EVENT &);							// Register a event.
		virtual bool Event_Delete(const EVENT &);
		virtual void Event_Happend();										// Judge whether a Event happend for a input device.
		
		virtual int Message_Process(const MESSAGE *);						// The function that belong to G_Object class.
};

#endif
