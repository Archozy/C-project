#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>




int EnregistrationPhoto(  int width, int height, SDL_Renderer* renderer,char* filename){

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

void UpdateTex(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture){
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture,NULL, NULL);
    SDL_RenderPresent(renderer);
}
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
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

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
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
int noirifier(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture){
    Uint32 p;
    Uint8 r,v,b= 100;


    Uint32 noir = SDL_MapRGB(image->format, 0,0,0);
    Uint32 white = SDL_MapRGB(image->format, 255,255,255);
    for(int y = 0 ; y<image->h ; y++){
            for(int i = 0 ; i<image->w ; i++){
                p = getpixel(image, i,y);
                SDL_GetRGB(p, image->format, &r, &v ,&b);
                if(r == 255 && v == 255 && b == 255 ){
                }
                else{
                    if( r ==0 && v == 0 && b == 0){
                    }
                    else{

                        if(b > r && b >= v){
                            setPixel(image, i, y, white);
                        }
                        else{
                            setPixel(image, i, y, noir);
                        }


                    }
                }
                r = 0;
                v = 0;
                b = 0;



            }
    }
    texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture,NULL, NULL);
                SDL_RenderPresent(renderer);
    return 0;
}

int detection(SDL_Surface *image, SDL_Renderer *renderer, SDL_Texture *texture){
    Uint32 p;
    Uint8 r,v,b = 100;



    printf("Ajustement des niveaux de noir \n");
    //deuxCouleurisation( image, renderer, texture);
    printf("Ajuste \n");




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
            else{

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

        //ESPACE
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



    printf("Finished");
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

    EnregistrationPhoto(image->w , image->h, renderer, "Neuronal_Network\\preuves");
    Uint32 p;
    Uint8 r,v,b = 100;

    image = SDL_LoadBMP("Neuronal_Network\\preuves.bmp");
    if(image == NULL)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    SDL_RenderClear(renderer);

    texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture,NULL, NULL);
            SDL_RenderPresent(renderer);


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
                char* nomphoto = (char*) malloc(50 * sizeof(char));
                if(nomphoto == NULL)
                {
                    printf("L'allocation n'a pu être réalisée\n");
                }
                sprintf(nomphoto, "Neuronal_Network\\%d", photo);
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
                printf("\n picture : %s ..... start at : %d:%d ; width : %d , height : %d",nomphoto, i, y , srect.w, srect.h);
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

int rectCollide(SDL_Rect Mouse, SDL_Rect Button){
    if(Mouse.x >= Button.x && Mouse.x <= (Button.x + Button.w) && Mouse.y >= Button.y && Mouse.y <= (Button.y + Button.h)){
        return 1;
    }
    return 0;
}

void Menu2(SDL_Rect Souris, SDL_Rect dest, SDL_Event e, SDL_Texture *tex, SDL_Renderer *renderer){


}
int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface * image = SDL_LoadBMP("image_OCR\\TD_1.bmp");
    SDL_Surface * ima = SDL_LoadBMP("Menu\\Launch.bmp");
    SDL_Surface * bg = SDL_LoadBMP("Menu\\Fond1.bmp");
    SDL_Window * window = SDL_CreateWindow("Alex ça marche",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  bg->w, bg->h, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    if(!window){
        printf("Erreur de chargement de la fenetre : %s",SDL_GetError());
        return -1;

    }


    if(image == NULL)
    {
        printf("Erreur de chargement de l'image1 : %s",SDL_GetError());
        return -1;
    }
    if(ima== NULL)
    {
        printf("Erreur de chargement de l'image2 : %s",SDL_GetError());
        return -1;
    }
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer, ima);
    SDL_Texture * background = SDL_CreateTextureFromSurface(renderer, bg);

    if(!tex){
        printf("%s", SDL_GetError());
    }
    SDL_Rect dest = {bg->w/2 - ima->w/2, 200, ima->w , ima->h};

    SDL_RenderCopy(renderer, tex, NULL, &dest);

    SDL_FreeSurface(ima);



    int x,y;
    int quit = 0;
    SDL_Rect Souris = {0,0,1,1};


    //deuxCouleurisation(image, renderer, texture);
    //UpdateTex(image, renderer, texture);
    //SDL_Delay(2000);
    //detection(image, renderer, texture);


    //registry(image, renderer, texture);
    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit )
    {
        SDL_GetMouseState(&x, &y);

        Souris.x = x;
        Souris.y = y;

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = 1;
            }
            if(e.type == SDL_MOUSEBUTTONDOWN && rectCollide(Souris, dest)){
                SDL_Surface * ima = SDL_LoadBMP("Menu\\Launch2.bmp");
                tex = SDL_CreateTextureFromSurface(renderer, ima);
                SDL_FreeSurface(ima);
            }else if(e.type == SDL_MOUSEBUTTONUP && rectCollide(Souris, dest)){
                /*SDL_Surface * ima = SDL_LoadBMP("Menu\\Launch1.bmp");
                tex = SDL_CreateTextureFromSurface(renderer, ima);
                SDL_FreeSurface(ima);*/
                deuxCouleurisation(image, renderer, texture);
                SDL_Delay(2000);
                detection(image, renderer, texture);
                SDL_Delay(2000);
                registry(image, renderer, texture);
            }else if(rectCollide(Souris, dest)){
                SDL_Surface * ima = SDL_LoadBMP("Menu\\Launch1.bmp");
                tex = SDL_CreateTextureFromSurface(renderer, ima);
                SDL_FreeSurface(ima);
            }else{
                SDL_Surface * ima = SDL_LoadBMP("Menu\\Launch.bmp");
                tex = SDL_CreateTextureFromSurface(renderer, ima);
                SDL_FreeSurface(ima);
            }




        }

        /*if(!outCase)
        {
            if(x >= dest.x && x< (dest.x + u) && y >= dest.y && y < (dest.y + v)){
                SDL_Surface * ima = SDL_LoadBMP("Menu\\Launch1.bmp");
                tex = SDL_CreateTextureFromSurface(renderer, ima);
                SDL_FreeSurface(ima);
                onCase = 1;
            }else{
                SDL_Surface * ima = SDL_LoadBMP("Menu\\Launch.bmp");
                tex = SDL_CreateTextureFromSurface(renderer, ima);
                SDL_FreeSurface(ima);
                onCase = 0;

            }
        }*/



        //Clear screen
        SDL_RenderClear( renderer );

        //Render texture to screen
        SDL_RenderCopy( renderer, background, NULL, NULL );
        SDL_RenderCopy( renderer, tex, NULL, &dest );


        //Update screen
        SDL_RenderPresent( renderer );
        SDL_Delay(33);
    }







    //detection(image, renderer, texture);

    //registry(image, renderer, texture);


    SDL_Delay(2000);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
