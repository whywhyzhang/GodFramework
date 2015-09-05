/*
	The implement of class S_Image.
*/

#include "../include/S_Image.h"
#include "../include/G_World.h"

#include "../include/L_Window.h"				// !!!

S_Image::S_Image(POS pos)
{
	spr_p=pos;
	spr_size=SIZE(0,0);
	image=0;
	
	pic_draw_pos=POS(0,0);
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

void S_Image::PicDraw_Pos_Set(POS pos)
{
	pic_draw_pos=pos;
}

void S_Image::Image_Draw()
{
	if(image==0 || p_world==0) return;
	
	MESSAGE mes={M_PIC_DRW,spr_p.x,spr_p.y,pic_draw_pos.x,pic_draw_pos.y,spr_size.w,spr_size.h,0};
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
