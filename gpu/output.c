/*
	File: output.c
	Role: implementation of file output functions

	Questions/comments to trevor.keller@nist.gov
	Bugs/requests to https://github.com/usnistgov/phasefield-accelerator-benchmarks
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

#include "diffusion.h"

void write_csv(double** A, int nx, int ny, double dx, double dy, int step)
{
	int i, j;
	double x, y;
	FILE* output;
	char name[256];
	char num[20];

	/* generate the filename */
	sprintf(num, "%07i", step);
	strcpy(name, "data.");
	strcat(name, num);
	strcat(name, ".csv");

	/* open the file */
	output = fopen(name, "w");
	if (output == NULL) {
		printf("Error: unable to open %s for output. Check permissions.\n", name);
		exit(-1);
	}

	/* write csv data */
	fprintf(output, "x,y,c\n");
	for (j = 1; j < ny-1; j++) {
		y = dy * (j - 1);
		for (i = 1; i < nx-1; i++)	{
			x = dx * (i - 1);
			fprintf(output, "%f,%f,%f\n", x, y, A[j][i]);
		}
	}

	fclose(output);
}

void write_png(double** A, int nx, int ny, int step)
{
	/* After "A simple libpng example program," http://zarb.org/~gc/html/libpng.html
	   and the libong manual, http://www.libpng.org/pub/png */

	double min, max, *c;
	int i, j, w, h, n;
	FILE* output;
	char name[256];
	char num[20];
	unsigned char* buffer;

	png_infop info_ptr;
	png_bytepp row_pointers;
	png_structp png_ptr;
	png_byte color_type = PNG_COLOR_TYPE_GRAY;
	png_byte bit_depth = 8;

	w = nx - 2;
	h = ny - 2;

	/* generate the filename */
	sprintf(num, "%07i", step);
	strcpy(name, "data.");
	strcat(name, num);
	strcat(name, ".png");

	/* open the file */
	output = fopen(name, "wb");
	if (output == NULL) {
		printf("Error: unable to open %s for output. Check permissions.\n", name);
		exit(-1);
	}

	/* allocate and populate image array */
	buffer = (unsigned char*)malloc(w * h * sizeof(unsigned char));
	row_pointers = (png_bytepp)malloc(h * sizeof(png_bytep));
	for (j = 0; j < h; j++)
		row_pointers[j] = &buffer[w * j];

	/* determine data range */
	min = 0.0;
	max = 1.0;
	for (j = ny-2; j > 0; j--) {
		for (i = 1; i < nx-1; i++) {
			c = &A[j][i];
			if (*c < min)
				min = *c;
			if (*c > max)
				max = *c;
		}
	}

	/* rescale data into buffer */
	n = 0;
	for (j = ny-2; j > 0; j--) {
		for (i = 1; i < nx-1; i++) {
			buffer[n] = (unsigned char) 255 * (min + (A[j][i] - min) / (max - min));
			n++;
		}
	}
	if (n != w * h) {
		printf("Error making image: expected %i values in buffer, got %i.\n", w*h, n);
		exit(-1);
	}

	/* let libpng do the heavy lifting */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		printf("Error making image: png_create_write_struct failed.\n");
		exit(-1);
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("Error making image: unable to init_io.\n");
		exit(-1);
	}
	png_init_io(png_ptr, output);

	/* write PNG header */
	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("Error making image: unable to write header.\n");
		exit(-1);
	}
	png_set_IHDR(png_ptr, info_ptr, w, h,
	                 bit_depth, color_type, PNG_INTERLACE_NONE,
	                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	/* write image */
	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("Error making image: unable to write data.\n");
		exit(-1);
	}
	png_write_image(png_ptr, row_pointers);

	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("Error making image: unable to finish writing.\n");
		exit(-1);
	}
	png_write_end(png_ptr, NULL);

	/* clean up */
	fclose(output);
	free(row_pointers);
	free(buffer);
}