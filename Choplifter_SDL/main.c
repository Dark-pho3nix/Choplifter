#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "SDL_image.h" // Inclusion du header pour la SDL
#include "global.h" // Inclusion du fichier contenant les fonction globales, generales



#define LARGEUR_TILE 64  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 64
#define LARGEUR_FENETRE 60  // nombre a afficher en x et y
#define HAUTEUR_FENETRE 12



int main(int argc, char *argv[])
{
    SDL_Surface *fenetre = NULL, *back = NULL;//Initialisation des images et elements avec des pointeurs
    SDL_Surface *sable = NULL;
    SDL_Rect positionback;// Emplacemet de l'image du background grace a une variable

    FILE *erreur = NULL;

    positionback.x = 0;// Et initialisation a zero en x et en y (coin superieur gauche)
    positionback.y = 0;

    SDL_Init(SDL_INIT_EVERYTHING);// Appel de tous les modules de la SDL pour gerer sons, videos, controles du clavier
    fenetre = SDL_SetVideoMode(1280, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); /* Creation de la fenetre repr�sent�e par le pointeur back en utilisant la largeur et la hauteur.
    On utilise aussi la m�moire vid�o (SDL_HWSURFACE) et le double buffer pour �viter que �a scintille (SDL_HWSURFACE) et le double buffer pour �viter que �a scintille (SDL_DOUBLEBUF)*/
    if ((SDL_Init(SDL_INIT_EVERYTHING) < 0) || (fenetre == NULL)) // On teste l'erreur a l'initialisation des modules de la SDL ou a la creation de la fenetre
    {
        erreur = fopen("erreur.txt","a+");
        if (erreur != NULL)
        {
            fprintf(erreur, "Erreur dans l'initialisation de la SDL\n");
        }
        fclose(erreur);
        exit(1);
    }

    SDL_WM_SetCaption("CHOPLIFTER", NULL);//Le nom de la fen�tre
    back = IMG_Load("images/back.png");//Charge l'image a partir de SDL_Image
    SDL_BlitSurface(back, NULL, fenetre, &positionback);//Indique ou sera affich�e l'image
    SDL_Flip(fenetre);


    char *carte[]={ // Pour afficher tel ou tel tile en fonction du numero
    "000000000000000000000000000000000000000000000000000000000000", // 0 affiche le sable pour le sol
    "000000000000000000000000000000000000000000000000000000000000",
    "000000000000000000000000000000000000000000000000000000000000",
    "000000000000000000000000000000000000000000000000000000000000",
    "000000000000000000000000000000000000000000000000000000000000",
    "000000000000000000000000000000000000000000000000000000000000",
    "000000000000000000000000000000000000000000000000000000000000",
    "000000000000000000000000000000000000000000000000000000000000",
    "000000000000000000000000000000000000000000000000000000000000",
    "000000000000000000000000000000000000000000000000000000000000",
    "000000000000000000000000000000000000000000000000000000000000",
    "111111111111111111111111111111111111111111111111111111111111"
    };

    sable = IMG_Load("images/tileset/1.png");
    sable = IMG_Load("images/tileset/1.png");
    int i,j;
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    Rect_source.w = LARGEUR_TILE;
    Rect_source.h = HAUTEUR_TILE;
    for(i=0;i<LARGEUR_FENETRE;i++)
    {
        for(j=0;j<HAUTEUR_FENETRE;j++)
        {
            Rect_dest.x = i*LARGEUR_TILE;
            Rect_dest.y = j*HAUTEUR_TILE;
            Rect_source.x = (carte[j][i]-'1')*LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_BlitSurface(sable,&Rect_source,fenetre,&Rect_dest);
        }
    }
    SDL_Flip(fenetre);



    pause();

    SDL_FreeSurface(back);
    SDL_Quit();
    return EXIT_SUCCESS;
}
