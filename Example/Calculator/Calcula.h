#ifndef CALCULA_H
#define CALCULA_H

#include <string.h>
#include <string>

#include "../../God.h"
#include "../../L_Window.h"
#include "../../S_Button.h"
#include "../../S_Label.h"
#include "../../E_2Dto2D.h"

class Cal_Lab : public S_Label
{
	private:
		int state;

	public:
		Cal_Lab(POS=POS(0,0),SIZE=SIZE(150,50),char * =0,int=0,int=25,int=0);

		int State_Get() const;
		void State_Set(int);
};

class Cal_But : public S_Button
{
	private:
		Cal_Lab * lab;
		char ch;
		
	private:
		double Cal_Ans(const char *,int,int,int &);
		bool isNum(char);
		bool isOpe(char);

	public:
		Cal_But(char=0,Cal_Lab * =0,POS=POS(0,0),SIZE=SIZE(100,50),char * =0,int=0);

		int  Click_Process(int);
};

void Window_Init(L_Window &);
void Button_Init(Cal_But * [],Cal_Lab *);

#endif
