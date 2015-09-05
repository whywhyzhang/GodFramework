CC=g++
CINCLUDE=-I/usr/X11R6/include -I/usr/local/include
CFLAGS=-Wall -g
LFLAGS=-L/usr/X11R6/lib -L/usr/local/lib -lX11 -ljpeg -lm

OBJECT = ../../God.o ../../G_World.o ../../G_Object.o ../../G_Input.o ../../G_Output.o ../../G_Sprit.o ../../G_Eye.o \
		 ../../L_Input.o ../../L_Output.o ../../L_Window.o \
		 ../../T_Picture.o \
		 ../../S_Button.o ../../S_Label.o ../../S_Image.o \
		 ../../E_2Dto2D.o \
		 Game.o Sprit.o main.o

test : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) $(CINCLUDE) $(LFLAGS) -o game

$(OBJECT) : ../../God.h ../../G_Config.h ../../G_Object.h ../../G_World.h
L_Input.o : ../../L_Input.h ../../G_Input.h
L_Output.o : ../../L_Output.h ../../G_Output.h
L_Window.o : ../../L_Window.h ../../L_Input.h ../../L_Output.h ../../G_Input.h ../../G_Output.h
T_Picture.o : ../../T_Picture.h
S_Button.o : ../../S_Button.h ../../G_Sprit.h
S_Label.o : ../../S_Label.h ../../G_Sprit.h
S_Image.o : ../../S_Image.h ../../G_Sprit.h
E_2Dto2D.o : ../../E_2Dto2D.h ../../G_Eye.h
Game.o : Game.h
Sprit.o : Sprit.h

.PHONY : clean
clean :
	-rm game $(OBJECT)
