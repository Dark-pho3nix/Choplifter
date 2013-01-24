#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "SDL_image.h" // Inclusion du header pour la SDL
#include "niveau1.h" // Inclusion du header pour le niveau 1
#include "global.h" // Inclusion du fichier contenant les fonction globales, generales

int main(int argc, char *argv[])
{
    SDL_Surface *fenetre = NULL, *back = NULL;//Initialisation des images et elements avec des pointeurs
    SDL_Rect positionback;// Emplacemet de l'image du background grace a une variable

    FILE *fichier = NULL;

    positionback.x = 0;// Et initialisation a zero en x et en y (coin superieur gauche)
    positionback.y = 0;

    SDL_Init(SDL_INIT_EVERYTHING);// Appel de tous les modules de la SDL pour gerer sons, videos, controles du clavier
    fenetre = SDL_SetVideoMode(1280, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); /* Creation de la fenetre représentée par le pointeur back en utilisant la largeur et la hauteur.
    On utilise aussi la mémoire vidéo (SDL_HWSURFACE) et le double buffer pour éviter que ça scintille (SDL_HWSURFACE) et le double buffer pour éviter que ça scintille (SDL_DOUBLEBUF)*/
    if ((SDL_Init(SDL_INIT_EVERYTHING) < 0) || (fenetre == NULL)) // On teste l'erreur a l'initialisation des modules de la SDL ou a la creation de la fenetre
    {
        printf("Erreur dans l'initialisation de la SDL\n");
        exit(1);
    }

    SDL_WM_SetCaption("CHOPLIFTER", NULL);//Le nom de la fenêtre
    back = IMG_Load("images/Back.png");//Charge l'image a partir de SDL_Image
    SDL_BlitSurface(back, NULL, fenetre, &positionback);//Indique ou sera affichée l'image

    SDL_Flip(fenetre);
    pause();

    fichier = fopen("verif.txt", "a+");
    if (fichier !=NULL)
    {
        fprintf(fichier, "Main passe !\n");
    }
    fclose(fichier);

    initialiser_coordonnees();
    ajout_valeurs_sprites();
    ajouter_sol();


    SDL_FreeSurface(back);
    SDL_Quit();
    return EXIT_SUCCESS;
}


