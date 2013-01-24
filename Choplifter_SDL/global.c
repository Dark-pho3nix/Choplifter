#include "global.h"
#include "SDL_image.h"

void pause()
{
    int continuer = 1; // On initialise la variable 'continuer' a 1 (booleen pour continuer)
    SDL_Event quitter; // On cree une variable de type SDL_Event

    while (continuer==1)
    {
        SDL_WaitEvent(&quitter);
        if (quitter.type==SDL_KEYDOWN)                  //
        {                                               //
            if (quitter.key.keysym.sym==SDLK_ESCAPE)    //
            {                                           // On test si il y a un appui sur la touche 'echap', si c'est vrai on met la variable a 0 et
                continuer=0;                            // le jeu quitte.
            }                                           //
        }
    }
}
