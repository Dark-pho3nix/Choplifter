#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_BlitSurface.h>
#include "SDL_image.h" // Inclusion du header pour la SDL
#include "global.h" // Inclusion du fichier contenant les fonction globales, generales



#define LARGEUR_TILE 64  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 64
#define LARGEUR_FENETRE_TILE 60  // nombre a afficher en x et y
#define HAUTEUR_FENETRE_TILE 12
#define HAUTEUR_FENETRE_AFF 768
#define LARGEUR_FENETRE_AFF 1280
#define MOVESPEED 1 // Vitesse du scrolling donc perso



int main(int argc, char *argv[])
{
    SDL_Surface *fenetre = NULL, *back = NULL;//Initialisation des images et elements avec des pointeurs
    SDL_Surface *sable = NULL;
    SDL_Surface *immeuble_bas_gauche = NULL, *immeuble_bas_droite = NULL, *immeuble_milieu_bas_gauche = NULL, *immeuble_milieu_bas_droite = NULL, *immeuble_milieu_haut_gauche = NULL, *immeuble_milieu_haut_droite = NULL, *immeuble_haut_gauche = NULL, *immeuble_haut_droite = NULL, *helico = NULL;
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

    sable = IMG_Load("images/tileset/1.png");
    immeuble_bas_gauche = IMG_Load("images/tileset/2.png");
    immeuble_bas_droite = IMG_Load("images/tileset/3.png");
    immeuble_milieu_bas_gauche = IMG_Load("images/tileset/4.png");
    immeuble_milieu_bas_droite = IMG_Load("images/tileset/5.png");
    immeuble_milieu_haut_gauche = IMG_Load("images/tileset/6.png");
    immeuble_milieu_haut_droite = IMG_Load("images/tileset/7.png");
    immeuble_haut_gauche = IMG_Load("images/tileset/8.png");
    immeuble_haut_droite = IMG_Load("images/tileset/9.png");
    helico = IMG_Load("images/tileset/helico_vol_droite.png");

    int i,j;
    int m = 0; //Valeur de transition pour le scroll
    int hx = 0; //Valeur de transition pour le déplacmeent de l'hélico en axe Horizontal
    int hy = 0; //Valeur de transition pour le déplacmeent de l'hélico en axe Vertical
    int carte[HAUTEUR_FENETRE_TILE][LARGEUR_FENETRE_TILE];
    int touches [4]; // Tableau pour gerer les touches
    FILE* maps1;
    maps1=fopen("maps/map1.txt","r");
    for(j=0;j<HAUTEUR_FENETRE_TILE;j++)
           {
               for(i=0;i<LARGEUR_FENETRE_TILE;i++)
                    {
                        fscanf(maps1,"%d ",&carte[j][i]);
                    }
           }
    SDL_Rect Rect_dest;   // Affiche les tileset
    SDL_Rect Rect_source; // Séléctionne les images
    SDL_Rect Rect_helico; // Affichage de l'hélico
    Rect_source.w = LARGEUR_TILE;
    Rect_source.h = HAUTEUR_TILE;
    for(i=0;i<LARGEUR_FENETRE_TILE;i++)
    {
        for(j=0;j<HAUTEUR_FENETRE_TILE;j++)
        {
            Rect_dest.x = i*LARGEUR_TILE-m;
            //Ici a faire avec un -M qui sera un pointeur qui décroit par les touches
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



    int continuer = 1; // On initialise la variable 'continuer' a 1 (booleen pour continuer)
    SDL_Event quitter; // On cree une variable de type SDL_Event
    SDL_EnableKeyRepeat(10, 10);
    while (continuer==1)
    {
            while (SDL_PollEvent(&quitter))// Tant que l'événement existe
        {

            switch (quitter.type)
            {


                // Si une touche est enfoncée
                case SDL_KEYDOWN: //vérifit les événements en créeant un un tableau pour créer la gestion de plusieurs touches
                {

                    // Si échap alors on quitte
                    if (quitter.key.keysym.sym == SDLK_ESCAPE)
                    {
                        continuer = 0;
                    }
                    if (quitter.key.keysym.sym == SDLK_UP)
                    {
                        touches[0] = 1;//dstrect.y --;
                    }
                    if (quitter.key.keysym.sym == SDLK_DOWN)
                    {
                        touches[1] = 1;//dstrect.y ++;
                    }
                    if (quitter.key.keysym.sym == SDLK_LEFT)
                    {
                        touches[2] = 1;//dstrect.x --;
                    }
                    if (quitter.key.keysym.sym == SDLK_RIGHT)
                    {
                        touches[3] = 1;//dstrect.x ++;
                    }
                    if(quitter.key.keysym.sym == SDLK_SPACE)
                    {
                        touches[4] = 1;
                    }
                    break;
                }
            case SDL_KEYUP: //vérifit les événements en créeant un un tableau pour créer la gestion de plusieurs touches
            {
                    if (quitter.key.keysym.sym == SDLK_UP)
                    {
                        touches[0] = 0;//dstrect.y --;
                    }
                    if (quitter.key.keysym.sym == SDLK_DOWN)
                    {
                        touches[1] = 0;//dstrect.y ++;
                    }
                    if (quitter.key.keysym.sym == SDLK_LEFT)
                    {
                        touches[2] = 0;//dstrect.x --;
                    }
                    if (quitter.key.keysym.sym == SDLK_RIGHT)
                    {
                        touches[3] = 0;//dstrect.x ++;
                    }
                    if(quitter.key.keysym.sym == SDLK_SPACE)
                    {
                        touches[4] = 0;
                    }

                }
            }// end switch
        } // end of message processing
        if (m<0 || hx<0) //limite le scroll et recadre la camera sur l'helico sur le bord gauche
            {
            if(touches[2] == 1)
                {
                    m=0;
                hx=hx-4;
                }
            if(touches[3] == 1)
                {
                    m=0;
                hx=hx+4;
                }

            }
        if (m>(LARGEUR_FENETRE_TILE-20)*64 || hx > 0)   ////limite le scroll et recadre la camera sur l'helico sur le bord droit
            {

            if(touches[2] == 1)
                {
                    m=(LARGEUR_FENETRE_TILE-20)*64;
                    hx=hx-4;
                }
            if(touches[3] == 1)
                {
                    m=(LARGEUR_FENETRE_TILE-20)*64;
                    hx=hx+4;
                }
            }
        if (hx < -584) //limite l'hélico sur le bord gauche car l'hélico se déplace seulement de 640 pixels sur le bord gauche
            {          // Seulement l'hélico fait 113 pix de long donc on limite a - 584 car le pixel pilote est au milieux
                hx = -584;
            }
        if (hx > 584)//limite l'hélico sur le bord gauche car l'hélico se déplace seulement de 640 pixels sur le bord droit
            {
                hx = 584;
            }
        if (hy < 0) //limite l'hélico sur le bord bas
            {
                hy = 0;
            }
        if (hy > 640)//limite l'hélico sur le bord haut
            {
                hy = 640;
            }

        if(touches[0] == 1) //Decalle l'helico sur le bas de 4 pixels
        {
            hy=hy+4;
        }
        if(touches[1] == 1) //Decalle l'helico sur le haut de 4 pixels
        {
            hy=hy-4;
        }
        if(touches[2] == 1) //Decalle le scroll sur la gauche de 4 pixels
        {
           m=m-4;
           hx=hx-0;
        }
        if(touches[3] == 1) //Decalle le scroll sur la droite de 4 pixels
        {
           m=m+4;
           hx=hx+0;
        }
        if(touches[4] == 1) //Prévision de la touche de tire
        {

        }
        SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
        SDL_BlitSurface(back, NULL, fenetre, &positionback);//Indique ou sera affichée l'image
        SDL_BlitSurface(helico, NULL, fenetre, &Rect_helico);//Charge l'image de l'helico
        Rect_helico.x = 576+hx ; //Distance en X de l'helico (pour le mettre au mileux de l'écran
        Rect_helico.y = 640-hy; //Distance en y de l'helico

        for(i=0;i<LARGEUR_FENETRE_TILE;i++)
    {
        for(j=0;j<HAUTEUR_FENETRE_TILE;j++)
        {
            Rect_dest.x = i*LARGEUR_TILE-m;//Ici a faire avec un -M qui sera un pointeur qui décroit par les touches
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
        SDL_Delay(1);
    }

    SDL_FreeSurface(back);
    SDL_FreeSurface(sable);
    SDL_FreeSurface(immeuble_bas_gauche);
    SDL_FreeSurface( immeuble_bas_droite);
    SDL_FreeSurface(immeuble_milieu_bas_gauche);
    SDL_FreeSurface(immeuble_milieu_bas_droite);
    SDL_FreeSurface(immeuble_milieu_haut_gauche);
    SDL_FreeSurface(immeuble_milieu_haut_droite);
    SDL_FreeSurface(immeuble_haut_gauche);
    SDL_FreeSurface(immeuble_haut_droite);
    SDL_Quit();
    return 0;
}
