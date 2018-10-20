#include "predefinefunction.h"
#include "firstFunctionOCR.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    init_sdl();
    //SDL_Surface * bg = SDL_LoadBMP("Menu/Fond1.bmp");
    SDL_Window * window = SDL_CreateWindow("Alex ça marche",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 800, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * image = SDL_LoadBMP("image_OCR/TD_1.bmp");
    if(!window){
        printf("Erreur de chargement de la fenetre : %s\n",SDL_GetError());
        return -1;

    }
    if(image == NULL)
    {
        printf("Erreur de chargement de l'image1 : %s\n",SDL_GetError());
        return -1;
    }
    //SDL_Texture * background = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect r;
    UpdateTex(image, renderer, texture);
    SDL_Delay(1000);
    r.x = 1456;
    r.y = 680;
    r.w = 28;
    r.h = 76;

    //deuxCouleurisation(bg, renderer, background);
    detection(image, renderer, texture);
    registry(image, renderer, texture);
    //extraction(image, r, "wwiw.bmp");


    UpdateTex(image, renderer, texture);
    SDL_Delay(2000);
    SDL_FreeSurface(image);
    //SDL_FreeSurface(bg);
    SDL_DestroyTexture(texture);
    //SDL_DestroyTexture(background);

    SDL_Quit();
    return 0;
}