#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "SDL_image.h"

#include "menu.h"

void pause();

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING); // Appel de la SDL (via SDL/SDL.h)
    if (SDL_Init(SDL_INIT_EVERYTHING)==-1)//SDL_INIT_EVERYTHING renvoi 0 si tout s'est bien passe et -1 sinon. On teste dans ce if si il y a une erreur a l'initialisation.
    {
        printf("Erreur a l'initialisation de la SDL !");
        exit; // Si erreur : on quitte;
    }
    SDL_SetVideoMode(1280, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Ouverture de la fenêtre de 800 par 400 avec gestion des images par la memoire video (HWSURFACE). DOUBLEBUF permet de faire un design fluide et non-scintillant
    SDL_WM_SetCaption("CHOPLIFTER", "Choplifter"); // Titre de la fenetre puis titre de l'icone.

    SDL_Surface *backg = NULL;
    backg=IMG_Load("backg.png");

    pause(); // Mise en pause du programme

    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS; // Fermeture du programme


}

void pause() // Fonction du SdZ, a changer plus tard.
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
