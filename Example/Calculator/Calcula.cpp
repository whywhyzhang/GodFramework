#include <stdlib.h>

#include "Calcula.h"

Cal_Lab::Cal_Lab(POS pos,SIZE size,char *str,int t,int lim,int pri) \
		:S_Label(pos,size,str,t,lim,pri)
{
	state=0;
	out_type=MID_RIG;
}

int Cal_Lab::State_Get() const
{
	return state;
}

void Cal_Lab::State_Set(int t)
{
	state=t;
}

Cal_But::Cal_But(char c,Cal_Lab * plab,POS p,SIZE s,char *str,int pri) \
		:S_Button(p,s,str,pri)
{
	ch=c;
	lab=plab;
}

void Cal_But::Click_Process(int num)
{
	if(num!=1) return;
	if(lab==0) return;

	if(isNum(ch) || ch=='.' || ch=='(' || ch==')')
	{
		int state=lab->State_Get();
		char ts[10];
		ts[0]=ch;
		ts[1]=0;

		if(state==0)
			(*lab)+=ts;
		else
		{
			lab->State_Set(0);
			lab->Text_Set(ts);
		}
	}
	else if(isOpe(ch))
	{
		int state=lab->State_Get();
		char ts[10];
		ts[0]=ch;
		ts[1]=0;
		lab->State_Set(0);

		if(state==0 || state==1)
			(*lab)+=ts;
		else
			lab->Text_Set(ts);
	}
	else if(ch=='=')
	{
		double ans;
		int error=0;			// !

		ans=Cal_Ans(lab->Text_Get(),0,lab->Text_Length_Get(),error);

		if(error)
		{
			lab->State_Set(2);
			lab->Text_Set("Error.");
		}
		else
		{
			lab->State_Set(1);
			char ts[100];
			gcvt(ans,48,ts);
			lab->Text_Set(ts);
		}
	}
	else if(ch=='C')
	{
		lab->State_Set(0);
		lab->Text_Set(0);
	}
	else if(ch=='D')
	{
		int state=lab->State_Get();

		if(state==0)
			(*lab)-=1;
		else
		{
			lab->Text_Set(0);
			lab->State_Set(0);
		}
	}
}

double Cal_But::Cal_Ans(const char *str,int x,int y,int &error)
{
	if(error)
		return 0.0;

	if(x>=y)
		return 0.0;

	int rem1=-1,rem2=-1;
	int cou=0;

	for(int i=x;i<y;++i)
	{
		if(str[i]=='(')
			++cou;
		else if(str[i]==')')
		{
			--cou;
			if(cou<0)
			{
				error=1;				///////
				return 0.0;
			}
		}
		else if(cou==0 && (str[i]=='+' || str[i]=='-'))
			rem1=i;
		else if(cou==0 && (str[i]=='*' || str[i]=='/'))
			rem2=i;
	}

	if(cou)
	{
		error=1;						///////
		return 0.0;
	}

	if(rem1==-1) rem1=rem2;
	if(rem1==-1)
	{
		if(str[x]=='(')
		{
			if(str[y-1]!=')')
			{
				error=1;				///////
				return 0.0;
			}
			return Cal_Ans(str,x+1,y-1,error);
		}
		else
		{
			int tc=0;
			for(int i=x;i<y;++i)
				if(str[i]=='.')
					++tc;
				else if(!isNum(str[i]))
					error=4;			///////
			if(tc>1)
				error=4;				///////

			return atof(str+x);			// Maybe bug.
		}
	}

	if(rem1==y-1 || (rem1==x && rem2==x))
	{
		error=3;						///////
		return 0.0;
	}

	double t1=Cal_Ans(str,x,rem1,error);
	double t2=Cal_Ans(str,rem1+1,y,error);

	if(error)
		return 0.0;

	if(str[rem1]=='+') return t1+t2;
	else if(str[rem1]=='-') return t1-t2;
	else if(str[rem1]=='*') return t1*t2;
	else if(str[rem1]=='/') return t1/t2;
	else error=5;						///////
	
	return 0.0;
}

bool Cal_But::isNum(char ch)
{
	return ch>='0' && ch<='9';
}

bool Cal_But::isOpe(char ch)
{
	return ch=='+' || ch=='-' || ch=='*' || ch=='/';
}

void Window_Init(L_Window & win)\
{
	win.Event_Register(EVENT{M_KEY_PRE,-1});
	win.Event_Register(EVENT{M_MOU_MOV});
	for(int i=0;i<10;++i)
		win.Event_Register(EVENT{M_MOU_PRE,i});
	win.Event_Register(EVENT{M_EXPOSE});
}

void Button_Init(Cal_But * but[],Cal_Lab *lab)
{
	SIZE t_s=SIZE(50,50);
	const char * str="0123456789.+-*/()=CD";
	char ts[10];
	POS pos[20]={{150,360},\
		{150,290},{220,290},{290,290},\
		{150,220},{220,220},{290,220},\
		{150,150},{220,150},{290,150},\
		{290,360},\
		{360,150},{360,220},{360,290},{360,360},\
		{430,290},{500,290},\
		{430,360},\
		{430,150},{430,220}};

	for(int i=0;str[i];++i)
	{
		ts[0]=str[i];
		ts[1]=0;
		but[i]=new Cal_But(str[i],lab,pos[i],t_s,ts);
	}

	but[0 ]->Size_Set(SIZE(120,50));
	but[17]->Size_Set(SIZE(120,50));
	but[18]->Size_Set(SIZE(120,50));
	but[19]->Size_Set(SIZE(120,50));
}
