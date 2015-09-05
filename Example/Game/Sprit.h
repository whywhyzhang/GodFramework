#ifndef SPRIT_H
#define SPRIT_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

#include "../../include/God.h"
#include "../../include/L_Window.h"
#include "../../include/L_Input.h"
#include "../../include/S_Button.h"
#include "../../include/S_Label.h"
#include "../../include/S_Image.h"
#include "../../include/E_2Dto2D.h"
#include "../../include/T_Picture.h"

const MES_TYPE M_ADD=1000;
const MES_TYPE M_FAIL=1001;
const MES_TYPE M_UNLAND=1002;

using std::swap;

/*
	Tow Bugs:
		1. Message_Process_Delete make segment fault.
		2. When win or fail a game, is so slowly for the mouse.
*/

class Wel_Func : public G_Sprit
{
	private:
		int rem1,rem2,rem3;

	public:
		Wel_Func();
		
		int Message_Process(const MESSAGE *);
		int operator () (int);

		void Register(int,int);
};

class Game_Func : public G_Sprit
{
	private:
		int cou;
		int all_num;
		
	public:
		Game_Func(int);
		
		int  Message_Process(const MESSAGE *);
		bool Process_Register();
};

class Game_Lab : public S_Label
{
	private:
		int num;
		int all_num;
		
	public:
		Game_Lab(int,POS=POS(0,0),SIZE=SIZE(100,30),int=0);
		
		void Add(int);
		
		int Message_Process(const MESSAGE *);
		bool Process_Register();
};

class Game_But : public S_Button
{
	private:
		int state;
		int num;
		S_Image * image;
		
		Game_But * neigh[8];
		
	private:
		int DFS();
		
	public:
		Game_But(int,POS,SIZE,S_Image *,int=0);
		
		int Click_Process(int);
		void Button_Draw();
		
		int Num_Get() const;
		int State_Get() const;
		
		void State_Set(int);
		
		void Neigh_Set(Game_But *,int);
};

class Time_Meter : public S_Label
{
	private:
		int time_per;			// usec.
		
		struct Time
		{
			int hour,minute,second;
		};
		
		Time time_rem;
		
	private:
		void Time_Add();
		
	public:
		Time_Meter(int, POS=POS(0,0),SIZE=SIZE(100,30),int=0);
		~Time_Meter();
		
		int Message_Process(const MESSAGE *);
		bool Process_Register();
};

#endif
