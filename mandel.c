#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include "auxtypes.h"
#include "save_image.h"

//gcc -std=c11 -O3 save_image.c mandel.c -lfreeimage -lm

Complex func(Complex z, Complex c)
{
	Complex res;

	res.r = z.r*z.r - z.i*z.i + c.r;
	res.i = z.r*z.i + z.i*z.r + c.i;
	
	return res;
}

Complex scale(window scr, fract fr, Complex c)
{
	Complex aux;

	aux.r = c.r / (double)scr.width * fr.width + fr.x_min;
	aux.i = c.i / (double)scr.height * fr.height + fr.y_min;

	return aux;
}

int escape(Complex c, int iter_max)
{
	Complex z;
	int iter = 0;
	z.r = 0;
	z.i = 0;

	while(sqrt(z.r*z.r + z.i*z.i) < 2.0 && iter < iter_max)
	{
		z = func(z, c);
		iter++;
	}
	return iter;
}

void get_number_iterations(window scr, fract fr, int iter_max, int *colors)
{
	int k = 0;
	for(int i = scr.y_min; i < scr.y_max; ++i) {
		for(int j = scr.x_min; j < scr.x_max; ++j) {
			Complex c;
			c.r = j;
			c.i = i;	
			c = scale(scr, fr, c);
			colors[k] = escape(c, iter_max);
			k++;			
		}
	}
} 

fract zoom(double window_ratio, double x0, double x1, double y0, double y1, fract fr)
{
	fract frt;
	double y = (x1 - x0) * window_ratio;
	frt.x_min = x0;
	frt.x_max = x1;
	frt.y_min = y0;
	frt.y_max = y + y0;
	frt.width = fr.x_max - fr.x_min;
	frt.height = fr.y_max - fr.y_min;
	frt.size = fr.width * fr.height;

	return frt;
}

void fractal (window scr, fract fr, int iter_max, const char* fname, int smooth_color)
{
	int colors[scr.size];
  	int64_t count, i, delta;
	struct timeval start, stop;

	gettimeofday(&start, NULL);
	get_number_iterations(scr, fr, iter_max, colors);
	gettimeofday(&stop, NULL);

	
	delta = ((stop.tv_sec - start.tv_sec) * (int64_t) 1000000 +
		     stop.tv_usec - start.tv_usec);
	    
	printf("Time for Generation Elapsed: %li us\n", delta);

	plot(scr, colors, iter_max, fname, smooth_color);
}

void mandelbrot() {

	window scr;
	fract fr;

	scr.x_min = 0;
	scr.y_min = 0;
	scr.x_max = 1200;
	scr.y_max = 1200;
	scr.width = scr.x_max - scr.x_min;
	scr.height = scr.y_max - scr.y_min;
	scr.size = scr.width * scr.height;
	
	fr.x_min = -2.2;
	fr.x_max = 1.2;
	fr.y_min = -1.7;
	fr.y_max = 1.7;
	fr.width = fr.x_max - fr.x_min;
	fr.height = fr.y_max - fr.y_min;
	fr.size = fr.width * fr.height;

	int iter_max = 500;
	const char *fname = "mandelbrot2.png";
	int smooth_color = 0;

	//fr = zoom(1.0, -1.225, -1.22, 0.15, 0.16, fr);
	fractal(scr, fr, iter_max, fname, smooth_color);
}

int main(int argc, char** argv)
{
	mandelbrot();
}
