#include <FreeImage.h>
#include "save_image.h"
#include "auxtypes.h"

rgb get_rgb_piecewise_linear(int n, int iter_max)
{
	int N = 256;
	int N3 = N * N * N;
	rgb point;
	
	double t = (double)n / (double)iter_max;

	n = (int) (t * (double) N3);
	
	point.b = n/(N*N);
	int nn = n - point.b * N * N;
	point.r = nn/N;
	point.g = nn - point.r * N;
	
	return point;
}

rgb get_rgb_smooth(int n, int iter_max)
{
	rgb point;
	double t = (double)n / (double)iter_max;

	point.r = (int)(9*(1-t)*t*t*t*255);
	point.g = (int)(15*(1-t)*(1-t)*t*t*255);
	point.b = (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);

	return point;
}

void plot(window scr, int* colors, int iter_max, const char *fname, int smooth_color)
{
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif

	unsigned int width = scr.width;
	unsigned int height = scr.height;

	FIBITMAP *bitmap = FreeImage_Allocate(width, height, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);

	int k = 0;
	rgb point;
	for(int i = scr.y_min; i < scr.y_max; ++i) {
		for(int j = scr.x_min; j < scr.x_max; ++j) {
			int n = colors[k];
			if(!smooth_color)
			{
				point = get_rgb_piecewise_linear(n, iter_max);
			}
			else
			{
				point = get_rgb_smooth(n, iter_max);
			}
			
			RGBQUAD col;
			col.rgbRed = point.r;
			col.rgbGreen = point.g;
			col.rgbBlue = point.b;
			col.rgbReserved = 255;
			FreeImage_SetPixelColor(bitmap, j, i, &col);
			k++;
		}
	}

	FreeImage_Save(FIF_PNG, bitmap, fname, PNG_DEFAULT);
	
	FreeImage_Unload(bitmap);

	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif
}
