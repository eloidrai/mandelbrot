#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <complex.h>

#include <SDL.h>

# define SCALE 250
# define PREC 40


int main (int argc, char ** argv) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window * window;
  SDL_Renderer * renderer;
  SDL_Texture * texture;
  uint32_t * pixels;
  int pitch;

  double a, b;
  sscanf(argv[1], "%lf", &a);
  sscanf(argv[2], "%lf", &b);

  double complex c = a + b*I;

  SDL_CreateWindowAndRenderer(1000, 1000, 0, &window, &renderer);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 1000, 1000);

  SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch);
    for (int x=0; x<4*SCALE; x++) {
      for (int y=0; y<4*SCALE; y++) {
        double complex z = (double)x/SCALE + (double)y/SCALE * I - 2 - 2*I;
        int i = 0;
        while (cabs(z)<2 && i<PREC) {
          z = z*z + c;
          i++;
        }
        if (i < PREC) {
          int shade = 0xFF * i / PREC;
          pixels[y*1000 + x] = (shade << 24) | (0x60 << 8) | 0xFF;
        } else {
          pixels[y*1000 + x] = 0x000000FF;
        }
      }
    }
  SDL_UnlockTexture(texture);

  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  SDL_Event event;
  while (true) {
    SDL_WaitEvent(&event);
    if (event.type==SDL_QUIT) {
      goto end;
    }
  }

  end:
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  SDL_Quit();
  return 0;
}
