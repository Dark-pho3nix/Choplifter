#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <windows.h>
#include "SDL_image.h" /* Inclusion du header de SDL_image (adapter le dossier au besoin) */

void pause();

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *back = NULL;
    SDL_Rect positionback;

    positionback.x = 0;
    positionback.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("sdl_icone.bmp"), NULL);

    ecran = SDL_SetVideoMode(1280, 800, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);

    back = IMG_Load("images/back.png");
    SDL_BlitSurface(back, NULL, ecran, &positionback);

    /* Chargement d'un PNG avec IMG_Load
    Celui-ci est automatiquement rendu transparent car les informations de
    transparence sont codées à l'intérieur du fichier PNG */

    SDL_Flip(ecran);
    pause();

    SDL_FreeSurface(back);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
