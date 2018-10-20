#ifndef FFO_H
#define FFO_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int deuxCouleurisation(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture);
int detection(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture);
int registry(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture);

#endif