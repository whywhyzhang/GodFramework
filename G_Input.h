#ifndef G_INPUT_H
#define G_INPUT_H

/*
	Abstract Input class.
	The class is used for Input hardware, and you should to rewrite some functions for a personal use.
	
	And I think Event is Message.
	Input device only can send a message about a event.
*/

#include "G_Object.h"
#include "G_Config.h"

// The class about Input.
class G_Input:public G_Object
{
	private:

	public:
		G_Input();
		virtual ~G_Input()=0;

		virtual bool Event_Register(const EVENT &)=0;							// Register a event that will be sended.
		virtual bool Event_Delete(const EVENT &)=0;								// Delete a event that will be sended.
		virtual void Event_Happend()=0;											// Judge whether a Event happend for a input device.
		
		virtual int Message_Process(const MESSAGE *)=0;							// The function that belong to G_Object class.
//		virtual int Message_Process(const MESSAGE &)=0;
};

#endif
