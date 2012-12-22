#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

void pause();

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO); // Appel de la SDL

    SDL_SetVideoMode(1000, 700, 32, SDL_HWSURFACE); // Ouverture de la fenêtre en 640 par 480
    SDL_WM_SetCaption("Choplifter", NULL);

    pause(); // Appel de la fonction pause issue du tuto du SdZ

    SDL_Quit();

    return EXIT_SUCCESS;
}

void pause()// Fonction du SdZ pour la pause
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
