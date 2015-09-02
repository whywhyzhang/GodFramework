#include <stdio.h>
#include <iostream>

#include "../../God.h"
#include "../../L_Window.h"
#include "../../E_2Dto2D.h"
#include "../../T_Picture.h"

using std::cin;

class PicDraw : public G_Sprit
{
	private:
		SIZE pic_size;
		POS pic_pos;
		const unsigned char *pic_buf;

	public:
		PicDraw(POS pos=POS(0,0)):pic_pos(pos)
		{
			pic_buf=0;
		}

		void Picture_Set(const unsigned char * p,SIZE s)
		{
			pic_buf=p;
			pic_size=s;
		}

		void Redraw()
		{
			MESSAGE mes={M_PIC_DRW,0,0,pic_size.w,pic_size.h};
			mes.p=(void *)pic_buf;
			p_world->Message_Send(mes);
		}

		int Message_Process(const MESSAGE *mes)
		{}
};

int main(int argc,char **argv)
{
	if(argc<2)
	{
		std::cerr<<"Please input the name of picture!\n";
		return 1;
	}

	God god;

	G_World * p_world = new G_World;
	god.World_Register(p_world);

	L_Window win(POS(10,10),SIZE(700,500));
	win.Window_Show();
	win.Event_Register(EVENT{M_EXPOSE});
	win.Register_To_World(p_world);

	E_2Dto2D * eye = new E_2Dto2D(SIZE(700,500));
	p_world->Object_Register(eye);
	p_world->Message_Process_Register(M_EXPOSE,eye->Obj_Num_Get());

	T_JPEG * picbuf = new T_JPEG;
	picbuf->Jpg_Open(argv[1]);

	PicDraw * pic = new PicDraw;
	pic->Picture_Set(picbuf->Pic_Buf_Get(),picbuf->Size_Get());
	p_world->Object_Register(pic);

	god.Run();

	return 0;
}
