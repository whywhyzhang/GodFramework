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
	protected:
		string text;
		int out_type;
		int have_frame;
		int len_limit;

	public:
		S_Label(POS=POS(0,0),SIZE=SIZE(150,50),char * =0,int=0,int=25,int=0);
		~S_Label();

		virtual void Label_Draw();

		int Message_Process(const MESSAGE *);
		bool Process_Register();
		void Redraw();

		void Text_Set(char *);
		void Out_Type_Set(int);
		void Len_Limit_Set(int);
		const char * operator += (const string &);				// Add a string to text;
		const char * operator -= (int);
		
		const char * Text_Get() const;
		int Text_Length_Get() const;
};

#endif
