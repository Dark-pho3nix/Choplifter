#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "SDL_image.h" /* Inclusion du header de SDL_image (adapter le dossier au besoin) */

void pause();

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *back = NULL;//Initialisation des images et �l�ments
    SDL_Rect positionback;//Emplacemet de l'image background

    positionback.x = 0;
    positionback.y = 0;

    SDL_Init(SDL_INIT_VIDEO);//initialisation du module video de SDL
    if (SDL_Init(SDL_INIT_VIDEO ) < 0)
    {
        printf("Erreure d'initialisation de SDL: %s\n", SDL_GetError());
        exit(1);
    }


    ecran = SDL_SetVideoMode(1280, 800, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    /* On cr�e la fen�tre, repr�sent�e par le pointeur back en utilisant la largeur et la
     hauteur. On utilise aussi la m�moire vid�o
     (SDL_HWSURFACE) et le double buffer pour �viter que �a scintille
     (SDL_DOUBLEBUF) */
        if (ecran == NULL)//V�rifie si la fen�tre s'initialise
        {
            printf("Couldn't set screen mode to %d x %d: %s\n", 1280,
                     800, SDL_GetError());
            exit(1);
        }
    SDL_WM_SetCaption("Chopfilter Test", NULL);//Le nom de la fen�tre

    back = IMG_Load("images/back.png");//Charge l'image a partir de SDL_Image
    SDL_BlitSurface(back, NULL, ecran, &positionback);//Indique ou sera affich�e l'image

    /*
    Celui-ci est automatiquement rendu transparent car les informations de
    transparence sont cod�es � l'int�rieur du fichier PNG */
    //COUCOU

    SDL_Flip(ecran);
    pause();

    SDL_FreeSurface(back);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void pause() //Boucle qui permet au jeux de ne pas se fermer sauf si le processus est coup�
{
    int continuer = 1;
    SDL_Event event;

    while (continuer==1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
