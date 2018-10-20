#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "firstFunctionOCR.h"
#include "predefinefunction.h"
#include <string.h>
#include <err.h>


int deuxCouleurisation(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture){
    Uint32 p;
    Uint8 r,v,b= 100;
    Uint32 noir = SDL_MapRGB(image->format, 0,0,0);
    Uint32 white = SDL_MapRGB(image->format, 255,255,255);
    for(int y = 0 ; y<image->h ; y++){
        for(int i = 0 ; i<image->w ; i++){
            p = getpixel(image, i,y);
            SDL_GetRGB(p, image->format, &r, &v ,&b);
            int g = (r+v+b)/3;
            if(g  > 255/2){
                setPixel(image, i, y, white);
            }
            else{
                setPixel(image, i, y, noir);
            }
        }
        r = 0;
        v = 0;
        b = 0;

    }
}
int detection(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture){
    Uint32 p;
    Uint8 r,v,b = 100;

    printf("Ajustement des niveaux de noir \n");
    deuxCouleurisation( image, renderer, texture);
    printf("Ajuste Done\n");

    int loup = 0;
    int alter = 0;
    int numberRED = 0;
    for(int i = 0 ; i < image->w ; i++){
        setPixel(image, i, 0, SDL_MapRGB(image->format, 255, 0, 0));
    }


    for(int y = 0 ; y<image->h ; y++){
        for(int i = 0 ; i<image->w ; i++){
            p = getpixel(image, i,y);
            SDL_GetRGB(p, image->format, &r, &v ,&b);
            if(r == 0 && v == 0 && b ==0){
                loup =1;
            }
        }
        if(loup == 0){
            alter++;
            if(alter >= 3){
                for(int o = 0 ; o<image->w ; o++){
                    setPixel(image, o, y, SDL_MapRGB(image->format, 255, 0, 0));
                }
                numberRED++;
                alter = 0;
            }
        }
        loup = 0;
    }
    alter = 0;
    loup = 0;

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture,NULL, NULL);
    SDL_RenderPresent(renderer);
    int begins = 0;
    for(int y = 0 ; y<image->w ; y++){
        loup = 0;
        begins = 0;
        for(int i = 0 ; i<image->h ; i++){

            p = getpixel(image, y, i);
            SDL_GetRGB(p, image->format, &r, &v ,&b);
            if(r == 0 && v == 0 && b ==0){
                loup = 1;
            }
            if(r == 255 && v == 0 && b ==0){
                if(loup == 0){
                    for(int u = begins ; u < i ; u++){
                        setPixel(image, y, u, SDL_MapRGB(image->format, 255, 0, 0));
                    }
                    //loup = 0;
                }
                loup = 0;
                begins = i;
            }
        }
    }
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture,NULL, NULL);
    SDL_RenderPresent(renderer);
    //Space Management
    for(int y = 0 ; y<image->h ; y++){
        for(int i = 0 ; i<image->w ; i++){
            p = getpixel(image, i,y);
            SDL_GetRGB(p, image->format, &r, &v ,&b);
            if((r == 255 && v == 255 && b ==255 || r == 0 && v == 0 && b ==0) && alter > 13){
                for(int o = begins ; o<i-1 ; o++){
                    setPixel(image, o, y, SDL_MapRGB(image->format, 0, 0, 255));
                }
                loup = 0;
            }
            if((r == 255 && v == 255 && b ==255 || r == 0 && v == 0 && b ==0)){
                loup =1;
                begins = i +2;
                alter = 0;
            }
            if(loup == 1 && r == 255 && v == 0 && b ==0){
                alter++;
            }
        }
    }
    printf("Finished\n");
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture,NULL, NULL);
    SDL_RenderPresent(renderer);
    return 1;
}
int registry(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture){


    SDL_Rect srect;

    srect.x = 0;
    srect.y = 0;
    srect.h = 1000;
    srect.w = 500;

    Uint32 p;
    Uint8 r,v,b = 100;


    int widthstart = 0;
    int heightstart = 0;
    int heightend = 0;
    int widthend = 0;

    int huj = 0;

    int photo = 0;
    int xd = 0;


    for(int y = 0 ; y<image->h ; y++){

        for(int i = 0 ; i<image->w ; i++){
            p = getpixel(image, i,y);
            SDL_GetRGB(p, image->format, &r, &v ,&b);

            if((r == 255 && v == 255 && b ==255) || (r == 0 && v == 0 && b ==255)){
                huj = 1;
                widthstart = i;
                heightstart = y;
                for(int u = widthstart ; u < image->w ; u++){
                    p = getpixel(image, u,y);
                    SDL_GetRGB(p, image->format, &r, &v ,&b);
                    if(r == 255 && v == 0 && b ==0){
                        widthend = u;
                        break;
                    }
                }

                for(int u = heightstart ; u < image->h ; u++){
                    p = getpixel(image, i,u);
                    SDL_GetRGB(p, image->format, &r, &v ,&b);

                    if(r == 255 && v == 0 && b ==0){
                        heightend = u;
                        break;
                    }

                }
                /*char* nomphoto = (char*) malloc(25* sizeof(char));
                if(nomphoto == NULL)
                {
                    printf("L'allocation n'a pu être réalisée\n");
                }
                sprintf(nomphoto, "Neuronal_Network/%d.bmp", photo);
                photo++;
                srect.x = i;
                srect.y = y;
                srect.w = widthend - widthstart;
                srect.h = heightend - heightstart;

                if(srect.w < 0 || srect.h < 0){
                    i = image->w + 1;
                    y = image->h + 1;
                    printf("----------------------------------------------------------------------------------------------------\n");
                    xd = 1;
                    break;
                }

                SDL_RenderPresent(renderer);
                printf("picture : %s ..... start at : %d:%d ; width : %d , height : %d \n",nomphoto, i, y , srect.w, srect.h);
                extraction(image, srect, nomphoto);

                free(nomphoto);
                i = widthend;*/
                char* nomphoto = (char*) malloc(50 * sizeof(char));
                if(nomphoto == NULL)
                {
                    printf("L'allocation n'a pu être réalisée\n");
                }
                sprintf(nomphoto, "Neuronal_Network/%d", photo);
                photo++;
                srect.x = i;
                srect.y = y;
                srect.w = widthend - widthstart;
                srect.h = heightend - heightstart;

                if(srect.w < 0 || srect.h < 0){
                    i = image->w + 1;
                    y = image->h + 1;
                    printf("WESH LE GANG \n");
                    xd = 1;
                    break;
                }
                SDL_RenderClear(renderer);
                int s = SDL_RenderCopy(renderer, texture,&srect, NULL);
                if(s != 0){
                    printf("pour : %d", s);
                }
                SDL_RenderPresent(renderer);
                printf("picture : %s ..... start at : %d:%d ; width : %d , height : %d\n",nomphoto, i, y , srect.w, srect.h);
                int g = EnregistrationPhoto(image->w, image->h, renderer, nomphoto);
                if(g != 0){
                    printf("pour : %d", g);
                }
                free(nomphoto);
                i = widthend;

            }

        }
        if(xd == 1){
            break;
        }
        if(huj == 1){
            y = heightend;
            huj = 0;
        }



    }
    SDL_Delay(4000);


}


