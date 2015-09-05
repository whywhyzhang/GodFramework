CC=g++
CINCLUDE=-I/usr/X11R6/include -I/usr/local/include -I../../include
CFLAGS=-Wall -g
LFLAGS=-L/usr/X11R6/lib -L/usr/local/lib -lX11 -ljpeg -lm

OBJECT = ../../God/God.o ../../God/G_World.o ../../God/G_Object.o ../../God/G_Input.o ../../God/G_Output.o ../../God/G_Sprit.o ../../God/G_Eye.o \
		 ../../Linux/L_Input.o ../../Linux/L_Output.o ../../Linux/L_Window.o \
		 ../../Tool/T_Picture.o \
		 ../../Sprit/S_Button.o ../../Sprit/S_Label.o ../../Sprit/S_Image.o \
		 ../../Eye/E_2Dto2D.o \
		 Game.o Sprit.o main.o

test : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) $(CINCLUDE) $(LFLAGS) -o game

$(OBJECT) : ../../include/God.h ../../include/G_Config.h ../../include/G_Object.h ../../include/G_World.h
L_Input.o : ../../include/L_Input.h ../../include/G_Input.h
L_Output.o : ../../include/L_Output.h ../../include/G_Output.h
L_Window.o : ../../include/L_Window.h ../../include/L_Input.h ../../include/L_Output.h ../../include/G_Input.h ../../include/G_Output.h
T_Picture.o : ../../include/T_Picture.h
S_Button.o : ../../include/S_Button.h ../../include/G_Sprit.h
S_Label.o : ../../include/S_Label.h ../../include/G_Sprit.h
S_Image.o : ../../include/S_Image.h ../../include/G_Sprit.h
E_2Dto2D.o : ../../include/E_2Dto2D.h ../../include/G_Eye.h
Game.o : Game.h
Sprit.o : Sprit.h

.PHONY : clean
clean :
	-rm game $(OBJECT)
