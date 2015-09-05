#include "Sprit.h"

Wel_Func::Wel_Func()
{
	rem1=rem2=0;
}

int Wel_Func::Message_Process(const MESSAGE *)
{
	return 0;
}

int Wel_Func::operator () (int num)
{
	if(num==rem1)
		return 1;
	else if(num==rem2)
		return 2;
	else if(num==rem3)
		return 1;

	return 0;
}

void Wel_Func::Register(int t,int num)
{
	if(t==1)
		rem1=num;
	else if(t==2)
		rem2=num;
	else if(t==3)
		rem3=num;
}

//////////////////////////////////////////////

Game_Func::Game_Func(int n)
{
	all_num=n;
	cou=0;
}

int Game_Func::Message_Process(const MESSAGE * mes)
{
	if(mes->type==M_FAIL)
		return 2;
	else if(mes->type==M_UNLAND)
	{
		cou+=mes->num[0];

		if(cou>=all_num)
			return 1;
	}
	
	return 0;
}

bool Game_Func::Process_Register()
{
	if(p_world==0) return 0;

	p_world->Message_Process_Register(M_FAIL,obj_num);
	p_world->Message_Process_Register(M_UNLAND,obj_num);

	return 1;
}

//////////////////////////////////////////////

Game_Lab::Game_Lab(int n,POS pos,SIZE size,int pri)
{
	all_num=n;
	num=0;
	spr_p=pos;
	spr_size=size;
	pri_num=pri;

	out_type=MID_MID;
	len_limit=25;
	have_frame=1;

	char ts[30]="0/";
	sprintf(ts+2,"%d",all_num);
	text=ts;
}

void Game_Lab::Add(int t)
{
	num+=t;
	char ts[30];
	sprintf(ts,"%d/%d",num,all_num);
	Text_Set(ts);
}

int Game_Lab::Message_Process(const MESSAGE * mes)
{
	if(mes->type==M_ADD)
		Add(mes->num[0]);
}

bool Game_Lab::Process_Register()
{
	if(p_world==0) return 0;

	p_world->Message_Process_Register(M_ADD,obj_num);

	return 1;
}

//////////////////////////////////////////////////////////////////

Game_But::Game_But(int n, POS pos, SIZE size, int pri)
{
	num=n;
	state=0;

	spr_p=pos;
	spr_size=size;
	pri_num=pri;

	text.clear();

	for(int i=0;i<8;++i)
		neigh[i]=0;
}

int Game_But::DFS()
{
	if(num==-1)
		return 0;

	int ret=1;

	State_Set(1);

	if(num)
		return 1;

	for(int i=0;i<8;++i)
		if(neigh[i])
			if(neigh[i]->State_Get()!=1)
				ret+=neigh[i]->DFS();

	return ret;
}

int Game_But::Click_Process(int n)
{

	if(state==1)
		return 0;

	if(n==1)
	{
		if(num==-1)
		{
			State_Set(1);
			p_world->Message_Send(MESSAGE{M_FAIL});
		}
		else
		{
			int t=DFS();
			p_world->Message_Send(MESSAGE{M_UNLAND,t});
		}
	}
	else if(n==3)
	{
		if(state==2)
			State_Set(0);
		else if(state==0)
			State_Set(2);
	}

	return 0;
}

int Game_But::Num_Get() const
{
	return num;
}

int Game_But::State_Get() const
{
	return state;
}

void Game_But::State_Set(int t)
{
	if(state==t)
		return;

	if(state==2)
		p_world->Message_Send(MESSAGE{M_ADD,-1});

	state=t;

	if(t==2)
	{
		Text_Set("?");
		p_world->Message_Send(MESSAGE{M_ADD,1});
	}
	else if(t==1)
	{
		//mou_on=0;
		//p_world->Message_Process_Delete(M_MOU_MOV,obj_num);
		//p_world->Message_Process_Delete(M_MOU_PRE,obj_num);
		
		if(num==-1)
			Text_Set("*");
		else if(num==0)
			Text_Set("");
		else
		{
			char ts[3];
			ts[0]='0'+num;
			ts[1]=0;
			Text_Set(ts);
		}
	}
	else if(t==0)
		Text_Set("");
}

void Game_But::Neigh_Set(Game_But * p,int t)
{
	neigh[t]=p;
}

void Game_But::Button_Draw()
{
	if(p_world)
	{
		COLOR col;
		MESSAGE mes={M_STR_DRW,spr_p.x+spr_size.w/2,spr_p.y+spr_size.h/2,0,text.length(),MID_MID};
		mes.p=(char *)text.data();

		if(mou_on && state!=1)
		{
			p_world->Message_Send(MESSAGE{M_REC_FIL,spr_p.x,spr_p.y,spr_size.w,spr_size.h,0x6f6f6f});
			col=COL_WHITE;
		}
		else if(mou_on==0 && state!=1)
		{
			p_world->Message_Send(MESSAGE{M_REC_FIL,spr_p.x,spr_p.y,spr_size.w,spr_size.h,0xBBBBBB});
			p_world->Message_Send(MESSAGE{M_REC_DRW,spr_p.x,spr_p.y,spr_size.w,spr_size.h,0});
			col=0;
		}
		else
		{
			p_world->Message_Send(MESSAGE{M_REC_FIL,spr_p.x,spr_p.y,spr_size.w,spr_size.h,COL_WHITE});
			p_world->Message_Send(MESSAGE{M_REC_DRW,spr_p.x,spr_p.y,spr_size.w,spr_size.h,0});
			col=0;
		}
		
		mes.num[2]=col;
		p_world->Message_Send(mes);
	}
}

//////////////////////////////////////////////////////////////////

Time_Meter::Time_Meter(int t_time,POS pos,SIZE size,int pri)
{
	time_per=t_time;
	spr_p=pos;
	spr_size=size;

	text="00:00:00";
	time_rem.hour=time_rem.minute=time_rem.second=0;

	out_type=MID_MID;
	pri_num=pri;
	len_limit=25;
	have_frame=1;
}

Time_Meter::~Time_Meter()
{}

void Time_Meter::Time_Add()
{
	++time_rem.second;
	if(time_rem.second>=60)
	{
		time_rem.second-=60;
		++time_rem.minute;
	}

	if(time_rem.minute>=60)
	{
		time_rem.minute-=60;
		++time_rem.hour;
	}

	char ts[30];

	ts[0]=time_rem.hour/10+'0';
	ts[1]=time_rem.hour%10+'0';
	ts[2]=':';
	ts[3]=time_rem.minute/10+'0';
	ts[4]=time_rem.minute%10+'0';
	ts[5]=':';
	ts[6]=time_rem.second/10+'0';
	ts[7]=time_rem.second%10+'0';
	ts[8]=0;

	Text_Set(ts);
}

int Time_Meter::Message_Process(const MESSAGE * mes)
{
	if(mes->type==M_TIM_PER)
	{
		if(mes->num[0]==obj_num)
			Time_Add();
	}

	return 0;
}

bool Time_Meter::Process_Register()
{
	if(p_world==0) return 0;

	int t1=time_per/1000000;
	int t2=time_per%1000000;

	L_Clock * p_clo = new L_Clock();
	p_clo->Event_Register(EVENT{M_TIM_PER,obj_num,t1,t2});
	
	p_world->Object_Register(p_clo);
	p_world->Message_Process_Register(M_TIM_PER,obj_num);

	return 1;
}
