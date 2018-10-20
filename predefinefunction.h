#ifndef PRE_H
#define PRE_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
int EnregistrationPhoto( int width, int height, SDL_Renderer* renderer,char* filename);
void UpdateTex(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture);
int extraction(SDL_Surface *image, SDL_Rect rect, char* filename);
void init_sdl();
int cfileexists(const char * filename);


#endif