#ifndef AUXTYPES_H
#define AUXTYPES_H

typedef struct {
	int r;
	int g;
	int b;
} rgb;

typedef struct {
	double r;
	double i;
} Complex;

typedef struct {
	int x_min;
	int x_max;
	int y_min;
	int y_max;
	int width;
	int height;
	int size;
} window;

typedef struct {
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	double width;
	double height;
	double size;
} fract;

#endif
