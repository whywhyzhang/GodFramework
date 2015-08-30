/*
	The tool of picture.
*/

#include "T_Picture.h"

void jpeg_error_exit (j_common_ptr cinfo)
{
	cinfo->err->output_message (cinfo);
	exit (EXIT_FAILURE);
}

unsigned char * Jpg_To_Pic(char * const name,SIZE &size)
{
	register JSAMPARRAY lineBuf;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr err_mgr;
	int bytesPerPix;
	FILE *inFile;
	u_char *retBuf;
	
	inFile = fopen (name, "rb");
	if (NULL == inFile) { 
		perror (NULL);
		return NULL;
	}

	cinfo.err = jpeg_std_error (&err_mgr);
	err_mgr.error_exit = jpeg_error_exit;	

	jpeg_create_decompress (&cinfo);
	jpeg_stdio_src (&cinfo, inFile);
	jpeg_read_header (&cinfo, (boolean)1);
	cinfo.do_fancy_upsampling = (boolean)0;
	cinfo.do_block_smoothing = (boolean)0;
	jpeg_start_decompress (&cinfo);

	size.w = cinfo.output_width;
	size.h = cinfo.output_height;
	bytesPerPix = cinfo.output_components;

	lineBuf = cinfo.mem->alloc_sarray ((j_common_ptr) &cinfo, JPOOL_IMAGE, (size.w * bytesPerPix), 1);
	retBuf = new unsigned char [(3 * (size.w * size.h))];
		
	if (NULL == retBuf) {
		perror (NULL);
		return NULL;
	}
		

	if (3 == bytesPerPix) {
		int lineOffset = (size.w * 3);
		int x;
		int y;
		
		for (y = 0; y < cinfo.output_height; ++y) {
			jpeg_read_scanlines (&cinfo, lineBuf, 1);
				
			for (x = 0; x < lineOffset; ++x) {
				retBuf[(lineOffset * y) + x] = lineBuf[0][x];
				++x;
				retBuf[(lineOffset * y) + x] = lineBuf[0][x];
				++x;
				retBuf[(lineOffset * y) + x] = lineBuf[0][x];
			}
		}
	} else if (1 == bytesPerPix) { 
		unsigned int col;
		int lineOffset = (size.w * 3);
		int lineBufIndex;
		int x ;
		int y;
						
		for (y = 0; y < cinfo.output_height; ++y) {
			jpeg_read_scanlines (&cinfo, lineBuf, 1);
				
			lineBufIndex = 0;
			for (x = 0; x < lineOffset; ++x) {
				col = lineBuf[0][lineBufIndex];
			
				retBuf[(lineOffset * y) + x] = col;
				++x;
				retBuf[(lineOffset * y) + x] = col;
				++x;
				retBuf[(lineOffset * y) + x] = col;
				
				++lineBufIndex;
			}			
		}
	} else {
		fprintf (stderr, "Error: the number of color channels is %d.  This program only handles 1 or 3\n", bytesPerPix);
		return NULL;
	}
	jpeg_finish_decompress (&cinfo);
	jpeg_destroy_decompress (&cinfo);
	fclose (inFile);
			
	return retBuf;
}
