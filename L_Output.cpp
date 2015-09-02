/*
	This is the class of linux output.
*/

#include "L_Output.h"
#include "G_World.h"

/////////////////////////////////////////////////////
// The function of L_Monitor.

L_Monitor::L_Monitor(Display *dis, Window *win, COLOR col)
{
	p_xlib_dis=dis;
	p_xlib_win=win;
	
	if(col==-1) col=COL_WHITE;
	back_color=col;

	unsigned int depth,temp;
	Window win_temp;

	XGetGeometry(p_xlib_dis,*p_xlib_win,&win_temp,&pixmap_pos.x,&pixmap_pos.y,&pixmap_size.w,&pixmap_size.h,&temp,&depth);
	xlib_pixmap=XCreatePixmap(p_xlib_dis,*p_xlib_win,pixmap_size.w,pixmap_size.h,depth);

	xlib_gc=XCreateGC(p_xlib_dis,xlib_pixmap,0,0);

	XSetBackground(p_xlib_dis,xlib_gc,back_color);
	XSetForeground(p_xlib_dis,xlib_gc,back_color);
	XFillRectangle(p_xlib_dis,xlib_pixmap,xlib_gc,0,0,pixmap_size.w,pixmap_size.h);

	Font_Set(DEFAULT_FONT);
}

L_Monitor::~L_Monitor()
{
	XFreeGC(p_xlib_dis,xlib_gc);
	XFreePixmap(p_xlib_dis,xlib_pixmap);
}

int L_Monitor::Message_Process(const MESSAGE *mes)
{
	const int *num=mes->num;
	
	switch(mes->type)
	{
		case M_EXPOSE:
		case M_BUF_SHW:
			if(mes->num[0]==-1) PicBuffer_Show();
			else PicBuffer_Show(POS(num[0],num[1]),SIZE(num[2],num[3]),POS(num[4],num[5]));
			break;
		case M_LIN_SET:
			Line_Set(num[0],num[1],num[2],num[3]);
			break;
		case M_FIL_SET:
			Fill_Set(num[0]);
			break;
		case M_FON_SET:
			Font_Set((char *)mes->p);
			break;
		case M_FOR_COL:
			ForeColor_Set(num[0]);
			break;
		case M_BAC_COL:
			BackColor_Set(num[0]);
			break;
		case M_STR_DRW:
			String_Draw(POS(num[0],num[1]),num[2],(char *)mes->p,num[3],num[4]);
			break;
		case M_POI_DRW:
			Point_Draw(POS(num[0],num[1]),num[2]);
			break;
		case M_LIN_DRW:
			Line_Draw(POS(num[0],num[1]),POS(num[2],num[3]),num[4]);
			break;
		case M_REC_DRW:
			Rect_Draw(POS(num[0],num[1]),SIZE(num[2],num[3]),num[4]);
			break;
		case M_CIR_DRW:
			Circle_Draw(POS(num[0],num[1]),num[2],num[3],mes->dnum[0],mes->dnum[1],num[4]);
			break;
		case M_REC_FIL:
			Rect_Fill_Draw(POS(num[0],num[1]),SIZE(num[2],num[3]),num[4]);
			break;
		default:
			break;
	}
}

void L_Monitor::PicBuffer_Show()
{
	XCopyArea(p_xlib_dis,xlib_pixmap,*p_xlib_win,xlib_gc,\
			0,0,pixmap_size.w,pixmap_size.h,0,0);
	XFlush(p_xlib_dis);
}

void L_Monitor::PicBuffer_Show(POS buff,SIZE size,POS mon)
{
	XCopyArea(p_xlib_dis,xlib_pixmap,*p_xlib_win,xlib_gc,\
			buff.x,buff.y,size.w,size.h,mon.x,mon.y);
	XFlush(p_xlib_dis);
}

void L_Monitor::Line_Set(int width, int line_style, int cap_style, int join_style)
{
	XGCValues temp;
	XGetGCValues(p_xlib_dis,xlib_gc,GCLineWidth | GCLineStyle | GCCapStyle | GCJoinStyle,&temp);
	if(width==-1) width=temp.line_width;
	if(line_style==-1) line_style=temp.line_style;
	if(cap_style==-1) cap_style=temp.cap_style;
	if(join_style==-1) join_style=temp.join_style;
	
	XSetLineAttributes(p_xlib_dis,xlib_gc,width,line_style,cap_style,join_style);
}

void L_Monitor::Fill_Set(int style)
{
	XSetFillStyle(p_xlib_dis,xlib_gc,style);
}

void L_Monitor::BackColor_Set(COLOR col)
{
	XSetBackground(p_xlib_dis,xlib_gc,col);
}

void L_Monitor::ForeColor_Set(COLOR col)
{
	XSetForeground(p_xlib_dis,xlib_gc,col);
}

bool L_Monitor::Font_Set(const char * font_name)
{
	XFontStruct *temp;
	temp=XLoadQueryFont(p_xlib_dis,font_name);
	if(!temp) return 0;
	p_font=temp;
	font_height=p_font->ascent+p_font->descent;

	XSetFont(p_xlib_dis,xlib_gc,p_font->fid);
	
	return 1;
}

void L_Monitor::String_Draw(POS pos,COLOR col,char *str,int len,int type)
{
	ForeColor_Set(col);
	int width=XTextWidth(p_font,str,len);
	
	switch(type)
	{
		case TOP_LEF:
			pos.y+=font_height;
			break;
		case TOP_MID:
			pos.x-=width/2;
			pos.y+=font_height;
			break;
		case TOP_RIG:
			pos.x-=width;
			pos.y+=font_height;
			break;
		case MID_LEF:
			pos.y+=font_height/2;
			break;
		case MID_MID:
			pos.x-=width/2;
			pos.y+=font_height/2;
			break;
		case MID_RIG:
			pos.x-=width;
			pos.y+=font_height/2;
			break;
		case LOW_LEF:
			break;
		case LOW_MID:
			pos.x-=width/2;
			break;
		case LOW_RIG:
			pos.x-=width;
			break;
		default:
			break;
	}

	XDrawString(p_xlib_dis,xlib_pixmap,xlib_gc,pos.x,pos.y,str,len);
}

void L_Monitor::Point_Draw(POS pos, COLOR col)
{
	ForeColor_Set(col);
	XDrawPoint(p_xlib_dis,xlib_pixmap,xlib_gc,pos.x,pos.y);
}

void L_Monitor::Line_Draw(POS pos1, POS pos2, COLOR col)
{
	ForeColor_Set(col);
	XDrawLine(p_xlib_dis,xlib_pixmap,xlib_gc,pos1.x,pos1.y,pos2.x,pos2.y);
}

void L_Monitor::Rect_Draw(POS pos,SIZE size,COLOR col)
{
	ForeColor_Set(col);
	XDrawRectangle(p_xlib_dis,xlib_pixmap,xlib_gc,pos.x,pos.y,size.w,size.h);
}

void L_Monitor::Circle_Draw(POS pos, int rX,int rY, double start, double angle, COLOR col)
{
	ForeColor_Set(col);
	XDrawArc(p_xlib_dis,xlib_pixmap,xlib_gc,pos.x-rX,pos.y-rY,rX*2,rY*2,(int)(start*64),(int)(angle*64));
}

void L_Monitor::Rect_Fill_Draw(POS pos,SIZE size,COLOR col)
{
	ForeColor_Set(col);
	XFillRectangle(p_xlib_dis,xlib_pixmap,xlib_gc,pos.x,pos.y,size.w,size.h);
}

void L_Monitor::Picture_Draw(POS p,SIZE s,unsigned char *buf)
{
	COLOR temp;
	int cou=0;
	POS dp=p;

	for(int i=0;i<s.h;++dp.y,++i,dp.x=p.x)
		for(int j=0;j<s.w;++dp.x,++j)
		{
			temp=buf[cou++]<<16;
			temp|=buf[cou++]<<8;
			temp|=buf[cou++];

			if(temp!=TRANS_COLOR)
				Point_Draw(dp,temp);
		}
}

void L_Monitor::Register_To_World(G_World *p_world)
{
	p_world->Object_Register(this);
	p_world->Message_Process_Register(M_EXPOSE ,obj_num);
	p_world->Message_Process_Register(M_BUF_SHW,obj_num);
	p_world->Message_Process_Register(M_LIN_SET,obj_num);
	p_world->Message_Process_Register(M_FIL_SET,obj_num);
	p_world->Message_Process_Register(M_FOR_COL,obj_num);
	p_world->Message_Process_Register(M_BAC_COL,obj_num);
	p_world->Message_Process_Register(M_STR_DRW,obj_num);
	p_world->Message_Process_Register(M_POI_DRW,obj_num);
	p_world->Message_Process_Register(M_LIN_DRW,obj_num);
	p_world->Message_Process_Register(M_REC_DRW,obj_num);
	p_world->Message_Process_Register(M_CIR_DRW,obj_num);
	p_world->Message_Process_Register(M_REC_FIL,obj_num);

}

//////////////////////////////////////////////////////
// The function of L_Audio.

L_Audio::L_Audio()
{}

L_Audio::~L_Audio()
{}

int L_Audio::Message_Process(const MESSAGE *mes)
{}

int L_Audio::Message_Process(const MESSAGE &mes)
{}
