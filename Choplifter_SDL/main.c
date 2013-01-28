#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "SDL_image.h" // Inclusion du header pour la SDL
#include "global.h" // Inclusion du fichier contenant les fonction globales, generales



#define LARGEUR_TILE 64  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 64
#define LARGEUR_FENETRE 20  // nombre a afficher en x et y
#define HAUTEUR_FENETRE 12



int main(int argc, char *argv[])
{
    SDL_Surface *fenetre = NULL, *back = NULL;//Initialisation des images et elements avec des pointeurs
    SDL_Surface *sable = NULL;
    SDL_Surface *immeuble_bas_gauche = NULL, *immeuble_bas_droite = NULL, *immeuble_milieu_bas_gauche = NULL, *immeuble_milieu_bas_droite = NULL, *immeuble_milieu_haut_gauche = NULL, *immeuble_milieu_haut_droite = NULL, *immeuble_haut_gauche = NULL, *immeuble_haut_droite = NULL;
    SDL_Rect positionback;// Emplacemet de l'image du background grace a une variable
    FILE *erreur = NULL;

    positionback.x = 0;// Et initialisation a zero en x et en y (coin superieur gauche)
    positionback.y = 0;

    SDL_Init(SDL_INIT_EVERYTHING);// Appel de tous les modules de la SDL pour gerer sons, videos, controles du clavier
    fenetre = SDL_SetVideoMode(1280, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); /* Creation de la fenetre représentée par le pointeur back en utilisant la largeur et la hauteur.
    On utilise aussi la mémoire vidéo (SDL_HWSURFACE) et le double buffer pour éviter que ça scintille (SDL_HWSURFACE) et le double buffer pour éviter que ça scintille (SDL_DOUBLEBUF)*/
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

    SDL_WM_SetCaption("CHOPLIFTER", NULL);//Le nom de la fenêtre
    back = IMG_Load("images/back.png");//Charge l'image a partir de SDL_Image
    SDL_BlitSurface(back, NULL, fenetre, &positionback);//Indique ou sera affichée l'image
    SDL_Flip(fenetre);

    sable = IMG_Load("images/tileset/1.png");
    immeuble_bas_gauche = IMG_Load("images/tileset/2.png");
    immeuble_bas_droite = IMG_Load("images/tileset/3.png");
    immeuble_milieu_bas_gauche = IMG_Load("images/tileset/4.png");
    immeuble_milieu_bas_droite = IMG_Load("images/tileset/5.png");
    immeuble_milieu_haut_gauche = IMG_Load("images/tileset/6.png");
    immeuble_milieu_haut_droite = IMG_Load("images/tileset/7.png");
    immeuble_haut_gauche = IMG_Load("images/tileset/8.png");
    immeuble_haut_droite = IMG_Load("images/tileset/9.png");

    int i,j;
    int carte[HAUTEUR_FENETRE][LARGEUR_FENETRE];
    FILE* maps1;
    maps1=fopen("maps/map1.txt","r");
    for(j=0;j<HAUTEUR_FENETRE;j++)
           {
               for(i=0;i<LARGEUR_FENETRE;i++)
                    {
                        fscanf(maps1,"%d ",&carte[j][i]);
                    }
           }
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
            Rect_source.x = (carte[j][i]!=1)*LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_BlitSurface(sable,&Rect_source,fenetre,&Rect_dest);
            Rect_source.x = (carte[j][i]!=2)*LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_BlitSurface(immeuble_bas_gauche,&Rect_source,fenetre,&Rect_dest);
            Rect_source.x = (carte[j][i]!=3)*LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_BlitSurface(immeuble_bas_droite,&Rect_source,fenetre,&Rect_dest);
            Rect_source.x = (carte[j][i]!=4)*LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_BlitSurface(immeuble_milieu_bas_gauche,&Rect_source,fenetre,&Rect_dest);
            Rect_source.x = (carte[j][i]!=5)*LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_BlitSurface(immeuble_milieu_bas_droite,&Rect_source,fenetre,&Rect_dest);
            Rect_source.x = (carte[j][i]!=6)*LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_BlitSurface(immeuble_milieu_haut_gauche,&Rect_source,fenetre,&Rect_dest);
            Rect_source.x = (carte[j][i]!=7)*LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_BlitSurface(immeuble_milieu_haut_droite,&Rect_source,fenetre,&Rect_dest);
            Rect_source.x = (carte[j][i]!=8)*LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_BlitSurface(immeuble_haut_gauche,&Rect_source,fenetre,&Rect_dest);
            Rect_source.x = (carte[j][i]!=9)*LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_BlitSurface(immeuble_haut_droite,&Rect_source,fenetre,&Rect_dest);
        }
    }
    SDL_Flip(fenetre);


    pause();

    SDL_FreeSurface(back);
    SDL_Quit();
    return EXIT_SUCCESS;
}
