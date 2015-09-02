/*
	The tool of picture.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <jpeglib.h>
#include <jerror.h>

#include "T_Picture.h"


T_JPEG::T_JPEG()
{
	is_vis=0;
	pic_buf=0;
}

T_JPEG::~T_JPEG()
{
	if(pic_buf)
	{
		delete pic_buf;
		pic_buf=0;
	}
}

void T_JPEG::jpeg_error_exit (j_common_ptr cinfo)
{
	cinfo->err->output_message (cinfo);
	exit (EXIT_FAILURE);
}

bool T_JPEG::Jpg_Open(char * name)
{
	if(pic_buf)
	{
		delete pic_buf;
		pic_buf=0;
	}
	
	register JSAMPARRAY lineBuf;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr err_mgr;
	int bytesPerPix;
	FILE *inFile;
	
	inFile = fopen (name, "rb");
	if (NULL == inFile) return 0;

	cinfo.err = jpeg_std_error (&err_mgr);
	err_mgr.error_exit = jpeg_error_exit;	

	jpeg_create_decompress (&cinfo);
	jpeg_stdio_src (&cinfo, inFile);
	jpeg_read_header (&cinfo, (boolean)1);
	cinfo.do_fancy_upsampling = (boolean)0;
	cinfo.do_block_smoothing = (boolean)0;
	jpeg_start_decompress (&cinfo);

	pic_size.w = cinfo.output_width;
	pic_size.h = cinfo.output_height;
	bytesPerPix = cinfo.output_components;

	lineBuf = cinfo.mem->alloc_sarray ((j_common_ptr) &cinfo, JPOOL_IMAGE, (pic_size.w * bytesPerPix), 1);
	pic_buf = new unsigned char [(3 * (pic_size.w * pic_size.h))];
		
	if (NULL == pic_buf) return 0;

	if (3 == bytesPerPix)
	{
		int lineOffset = (pic_size.w * 3);
		int x;
		int y;
		
		for (y = 0; y < cinfo.output_height; ++y)
		{
			jpeg_read_scanlines (&cinfo, lineBuf, 1);
				
			for (x = 0; x < lineOffset; ++x)
			{
				pic_buf[(lineOffset * y) + x] = lineBuf[0][x];
				++x;
				pic_buf[(lineOffset * y) + x] = lineBuf[0][x];
				++x;
				pic_buf[(lineOffset * y) + x] = lineBuf[0][x];
			}
		}
	}
	else if (1 == bytesPerPix)
	{
		unsigned int col;
		int lineOffset = (pic_size.w * 3);
		int lineBufIndex;
		int x ;
		int y;

		for (y = 0; y < cinfo.output_height; ++y)
		{
			jpeg_read_scanlines (&cinfo, lineBuf, 1);
				
			lineBufIndex = 0;
			for (x = 0; x < lineOffset; ++x)
			{
				col = lineBuf[0][lineBufIndex];
			
				pic_buf[(lineOffset * y) + x] = col;
				++x;
				pic_buf[(lineOffset * y) + x] = col;
				++x;
				pic_buf[(lineOffset * y) + x] = col;
				
				++lineBufIndex;
			}			
		}
	}
	else
		return 0;

	jpeg_finish_decompress (&cinfo);
	jpeg_destroy_decompress (&cinfo);
	fclose (inFile);

	return 1;
}

SIZE T_JPEG::Size_Get() const
{
	return pic_size;
}

const unsigned char * T_JPEG::Pic_Buf_Get() const
{
	return pic_buf;
}

int T_JPEG::Message_Process(const MESSAGE *mes)
{}
