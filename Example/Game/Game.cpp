#include "Game.h"

bool Welcome(God & god, G_World * p_world, G_Eye * eye)
{
	S_Button * but1 = new S_Button(POS(300,190),SIZE(100,50),"Start");
	S_Button * but2 = new S_Button(POS(300,390),SIZE(100,50),"Exit");

	Wel_Func func;
	func.Register(2,but1->Obj_Num_Get());
	func.Register(1,but2->Obj_Num_Get());
	
	but1->Function_Register(func,1);
	but2->Function_Register(func,1);
	p_world->Object_Register(but1);
	p_world->Object_Register(but2);

	int ret = god.Run();
	
	delete but1;
	delete but2;
	
	p_world->Message_Send(MESSAGE{M_PAINT});
	
	return ret-1;
}

bool Game_Run(God & god, G_World * p_world, S_Image * image)
{
	int land_num=40;
	SIZE num_size(16,16);

	Time_Meter * p_time = new Time_Meter(1000000,POS(130,12));
	p_world->Object_Register(p_time);

	Game_Lab * p_lab = new Game_Lab(land_num,POS(470,12));
	p_world->Object_Register(p_lab);

	int len=num_size.w*num_size.h;
	Game_But * but_rem [len];
	Button_Init(but_rem, p_world,num_size,land_num,SIZE(35,35),SIZE(1,1),POS(62,58),image);

	Game_Func * p_func = new Game_Func(num_size.w*num_size.h-land_num);
	p_world->Object_Register(p_func);

	int ret=god.Run();

	for(int i=0;i<len;++i)
		but_rem[i]->State_Set(1);

	Game_Result(god,p_world,ret);

	for(int i=0;i<len;++i)
		delete but_rem[i];
	delete p_lab;
	delete p_func;
	delete p_time;
	p_world->Message_Send(MESSAGE{M_PAINT});

	return 0;
}

void Button_Init(Game_But * but_rem [], G_World * p_world, SIZE num_size, int land_num, SIZE but_size, SIZE space_size, POS start_pos,S_Image * image)
{
	int len=num_size.h * num_size.w;
	int * num = new int [len];
	int * rem = new int [len];
	Game_But * p_but;
	POS tpos;

	for(int i=0;i<len;++i)
		rem[i]=0;

	GetRand(num,len);

	for(int i=0;i<land_num;++i)
		rem[num[i]]=-1;

	for(int i=0;i<len;++i)
		if(rem[i]!=-1)
			rem[i]=GetNum(i,num_size,rem);

	int tw=but_size.w+space_size.w;
	int th=but_size.h+space_size.h;

	for(int i=0;i<len;++i)
	{
		tpos.x=start_pos.x+(i % num_size.w)*tw;
		tpos.y=start_pos.y+(i / num_size.w)*th;
		p_but = new Game_But(rem[i],tpos,but_size,image);
		p_world->Object_Register(p_but);
		
		but_rem[i]=p_but;
	}

	const int step[8][2]={{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1}};
	int ti,tj;

	for(int i=0;i<num_size.h;++i)
		for(int j=0;j<num_size.w;++j)
			for(int k=0;k<8;++k)
			{
				ti=i+step[k][0];
				tj=j+step[k][1];

				if(ti>=0 && ti<num_size.h && tj>=0 && tj<num_size.w)
					but_rem[i*num_size.w+j]->Neigh_Set(but_rem[ti*num_size.w+tj],k);
			}
}

void GetRand(int * num, int len)
{
	for(int i=0;i<len;++i)
		num[i]=i;

	srand(time(0));

	int t,temp;

	for(int i=len;i>0;--i)
	{
		t=rand()%i;
		swap(num[t],num[i-1]);
	}
}

int GetNum(int pos, SIZE size, int * num)
{
	const int step[8][2]={{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1}};

	int ret=0;
	int r=pos/size.w, c=pos%size.w;
	int tr,tc;

	for(int i=0;i<8;++i)
	{
		tr=r+step[i][0];
		tc=c+step[i][1];

		if(tr<size.h && tr>=0 && tc<size.w && tc>=0)
			if(num[tr*size.w+tc]==-1)
				++ret;
	}

	return ret;
}

void Game_Result(God &god, G_World * p_world, int res)
{
	S_Button * but = new S_Button(POS(300,490),SIZE(100,50),"Return");

	Wel_Func func;
	func.Register(3,but->Obj_Num_Get());
	
	but->Function_Register(func,1);
	p_world->Object_Register(but);

	T_JPEG * picbuf = new T_JPEG;
	if(res==1)
		picbuf->Jpg_Open("Win.jpg");
	else if(res==2)
		picbuf->Jpg_Open("Fail.jpg");

	S_Image * image = new S_Image();
	SIZE size=picbuf->Size_Get();
	int x=(700-size.w)/2;
	image->Pos_Set(POS(x,100));
	image->Image_Set(picbuf->Pic_Buf_Get(),size);
	p_world->Object_Register(image);

	god.Run();

	delete image;
	delete but;
	p_world->Message_Send(MESSAGE{M_PAINT});
}
