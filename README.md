Mandelbrot Set Generator

Original Code in C++ by Solarian Programmer (https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/)

Translated Code in pure C by Antonio Ideguchi

You'll need FreeImage lib (dnf install freeimage freeimage-devel (Fedora 22))

Compiling:

$ gcc -std=c11 -O3 -o mandel save_image.c mandel.c -lfreeimage -lm
$ clang -std=c11 -03 -o mandel save_image.c mandel.c -lfreeimage -lm

Executing

$ ./mandel

GCC compiled execution time: ~556656
Clang compiled execution time: ~1845746 us
