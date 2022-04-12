mandelbrot: mandelbrot.c
	gcc -o $@ $^ `sdl2-config --cflags --libs` -lm

julia: julia.c
	gcc -o $@ $^ `sdl2-config --cflags --libs` -lm

all: mandelbrot julia
