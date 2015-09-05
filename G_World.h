#ifndef G_WORLD_H
#define G_WORLD_H

/*
	This is the class G_World.
*/

#include "G_Config.h"

class God;

class G_World
{
	private:
		static WORLD_NUM world_cou;
		WORLD_NUM world_num;

		God *p_god;
		
	private:
		queue <const MESSAGE *> mes_que;									// Message queue.
		map <OBJECT_NUM,G_Object *> obj_type_rem[OBJ_KIND];
		map <OBJECT_NUM,G_Object *> obj_rem;
		multimap <MES_TYPE,OBJECT_NUM> mes_obj_rem;							// A map that remember all the message that have been register.

		typedef map <OBJECT_NUM,G_Object *> ::iterator OBJ_ITER;
		typedef multimap <MES_TYPE,OBJECT_NUM> ::iterator MES_ITER;

	private:
		queue <const MESSAGE *> world_mes_que;								// Message coming from other world. Maybe Multi thread there.
		map <WORLD_NUM, G_World *> other_world_rem;							// Remember other world that this world can send message to.
		
		typedef map <WORLD_NUM, G_World *> ::iterator WORLD_ITER;

	private:
		void Event_Happend();
		int  Message_Process(const MESSAGE *);								// Process a message.

	public:
		G_World();
		~G_World();

		God * God_Get() const;
		void God_Set(God *);
		WORLD_NUM World_Num_Get() const;
		int Run();
		
	public:
		void Message_Process_Register(MES_TYPE,OBJECT_NUM);					// Register a process object about a message.
		bool Message_Process_Delete(MES_TYPE,OBJECT_NUM);					// Delete a relationship about Message and Object.
		void Message_Delete(MES_TYPE);
		void Message_Send(const MESSAGE &);									// Send a message to message queue.

		bool Object_Register(G_Object *);									// Register a object.
		bool Object_Delete(const OBJECT_NUM);								// Delete a object according to his num.
		
		void Visual_Change(OBJECT_NUM,bool);								// Change the visual of Object.
		
	public:
		void World_Message_Send(const MESSAGE &);							// Send a message from other world.
		bool Send_Message_To_World(WORLD_NUM, const MESSAGE &);				// Send a message to other world.
		
		void Other_World_Register(G_World *);
		bool Other_World_Delete(WORLD_NUM);
};

#endif
