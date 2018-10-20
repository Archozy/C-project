#include "predefinefunction.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}
Uint32 getpixel(SDL_Surface *surface, int x, int y){
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
    }
}
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
    switch(nbOctetsParPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}
int EnregistrationPhoto(int width, int height, SDL_Renderer* renderer,char* filename){

    SDL_Surface *sshot = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    int y = SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    /*for(int y = 0 ; y<yb ; y++){
        for(int i = 0 ; i<xb; i++){
        }
    }*/
    if(y != 0){
        printf("Error RendererPixelReading : %s", SDL_GetError());
        return -1;
    }
    char* ext = (char*) malloc(10 * sizeof(char));
    if(ext == NULL)
    {
        printf("L'allocation n'a pu être réalisée\n");
    }
    ext = ".bmp";
    char* neFile = (char*) malloc(30 * sizeof(char));
    if(neFile == NULL)
    {
        printf("L'allocation n'a pu être réalisée\n");
    }
    strcpy(neFile, filename);
    strcat(neFile, ext);

    int check = SDL_SaveBMP(sshot, neFile);
    if(check != 0){
        printf("Error Saving : %s", SDL_GetError());
    }
    free(neFile);
    free(ext);

    SDL_FreeSurface(sshot);
    return 0;
}
void UpdateTex(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture) {
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
int cfileexists(const char * filename){
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}
int extraction(SDL_Surface *image, SDL_Rect rect, char* filename){
    Uint32 rmask, gmask, bmask, amask;
    SDL_Surface *surface = NULL;
    surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0,0,0,0);
    if(surface == NULL){
        printf("%s", SDL_GetError());
    }
    int x = 0,y = 0;
    for(int j = rect.y ; j < rect.y + rect.h ; j++){
        for(int i = rect.x ; i < rect.x + rect.w ; i++){
            setPixel(surface, x, y, getpixel(image, i, j));
            //printf("pos[%d;%d] --- r = %d : v = %d : b = %d \n", i,j,r,g,b);
            x++;
        }
        y++;
    }

    if(cfileexists(filename)){
        remove(filename);
    }
    int a = SDL_SaveBMP(surface, filename);

    if(a != 0){
        printf("%s", SDL_GetError());
    }
    printf("%d\n", a);

}