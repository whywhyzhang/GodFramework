#ifndef S_LABEL_H
#define S_LABEL_H

/*
	The class of sprit label.
*/

#include <string>

#include "G_Sprit.h"

using std::string;

class S_Label : public G_Sprit
{
	private:
		string text;
		int out_type;

	public:
		S_Label(POS=POS(0,0),SIZE=SIZE(150,50),char * =0,int=0);
		~S_Label();

		virtual void Label_Draw();

		int Message_Process(const MESSAGE *);
		bool Process_Register();
		void Redraw();

		void Text_Set(char *);
		void Out_Type_Set(int);
		const char * operator += (const string &);				// Add a string to text;
		
		const char * Text_Get() const;
};

#endif
