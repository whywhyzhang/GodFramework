#ifndef T_PICTURE_H
#define T_PICTURE_H

/*
	This is the tool of picture.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <jpeglib.h>
#include <jerror.h>

#include "G_Config.h"

void jpeg_error_exit (j_common_ptr);
unsigned char * Jpg_To_Pic(char * const,SIZE &);

#endif
