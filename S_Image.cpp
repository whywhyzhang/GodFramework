/*
	The implement of class S_Image.
*/

#include "S_Image.h"
#include "G_World.h"

#include "L_Window.h"				// !!!

S_Image::S_Image(POS pos)
{
	spr_p=pos;
	spr_size=SIZE(0,0);
	image=0;
}

S_Image::~S_Image()
{
	if(image)
		L_Window::T_Image_Destroy(image);
}

bool S_Image::Image_Set(const unsigned char * p,SIZE s)
{
	if(p==0) return 0;
	
	spr_size=s;
	if(0==L_Window::T_PicBuf_To_Image(p,s,image))
	{
		image=0;
		return 0;
	}
	
	return 1;
}

void S_Image::Image_Draw()
{
	MESSAGE mes={M_PIC_DRW,0,0,spr_size.w,spr_size.h,0};
	mes.p=(void *)image;
	p_world->Message_Send(mes);
}

void S_Image::Redraw()
{
	if(image)
		Image_Draw();
}

int S_Image::Message_Process(const MESSAGE *mes)
{
	return 0;
}
