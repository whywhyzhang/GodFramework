#ifndef T_PICTURE_H
#define T_PICTURE_H

/*
	This is the tool class of picture.
*/

#include <jpeglib.h>

#include "G_Sprit.h"

class T_JPEG : public G_Sprit
{
	private:
		unsigned char * pic_buf;
		SIZE pic_size;

	private:
		static void jpeg_error_exit (j_common_ptr);

	public:
		T_JPEG();
		~T_JPEG();

		bool Jpg_Open(char *);

		SIZE Size_Get() const;
		const unsigned char * Pic_Buf_Get() const;
		
		int Message_Process(const MESSAGE *);
};

#endif
