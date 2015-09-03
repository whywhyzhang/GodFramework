#ifndef L_WINDOW_H
#define L_WINDOW_H

/*
	This is the class for a X window.
	This class contions Keyboard,Mouse and Window.
*/

#include "L_Input.h"
#include "L_Output.h"

class L_Window
{
	private:
		static Display *xlib_dis;
		static int win_cou;
		Window xlib_win;
		
		SIZE win_size;
		POS win_pos;
		COLOR back_color;

		L_Key_Mou_Win *p_win_keymouse;
		L_Monitor *p_win_monitor;

	public:
		L_Window();
		L_Window(POS,SIZE);
		L_Window(char *, POS, SIZE, COLOR=-1);				// Create a window of x sever char*, start from POS, has a SIZE, a COLOR of background.
		~L_Window();

		bool Window_Show() const;
		void Window_Close();

		L_Key_Mou_Win * Get_KeyMouse_Pointer() const;
		L_Monitor * Get_Monitor_Pointer() const;
		
		bool Event_Register(const EVENT &);
		void Register_To_World(G_World *);
};

#endif
