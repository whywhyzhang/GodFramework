#include "God.h"
#include "L_Window.h"
#include "T_Picture.h"

#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	L_Window win(0,POS(0,0),SIZE(800,700));
	L_Monitor *out;
	unsigned char *buf;
	SIZE size;
	
	win.Window_Show();
	
	out=win.Get_Monitor_Pointer();
	
	buf=Jpg_To_Pic("2.jpg",size);
	out->Picture_Draw(POS(10,10),size,buf);
	
	for(int i=0;i<30;++i) cerr<<(int)buf[i]<<' ';
	
	//out->Point_Draw(POS(20,20),0);
	//out->Rect_Draw(POS(10,10),SIZE(20,20),0);
	out->PicBuffer_Show();
	
	clock_t t=clock();
	
	while(1)
	{
		if(clock()-t<100000) continue;
		
		t=clock();
		out->PicBuffer_Show();
	}

	return 0;
}
