#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <D:\Logiciels\Logiciels école\CodeBlocks\SDL\include\SDL\SDL_BlitSurface.h>
#include "D:\Logiciels\Logiciels école\CodeBlocks\SDL\include\SDL_image.h" // Inclusion du header pour la SDL
#include "D:\Logiciels\Logiciels école\CodeBlocks\SDL\include\SDL\SDL_ttf.h"




#define LARGEUR_TILE 64  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 64
#define LARGEUR_FENETRE_TILE 60  // nombre a afficher en x et y
#define HAUTEUR_FENETRE_TILE 12
#define HAUTEUR_FENETRE_AFF 768
#define LARGEUR_FENETRE_AFF 1280
#define POSITION_ORIGINE_X_HELICO 576 //(position de démarage de l'hélico dans sa base en coordonnées X)
#define POSITION_ORIGINE_Y_HELICO 640 //(position de démarage de l'hélico dans sa base en coordonnées Y)
// DEPLACMENT_HELICO_X (coordonnées ajoutées en X par les touches)
int main(int argc, char *argv[])
{
    SDL_Surface *fenetre = NULL, *menu = NULL;//Initialisation des images et elements avec des pointeurs
    SDL_Rect positionmenu;// Emplacemet de l'image du background grace a une variable
    FILE *erreur = NULL;

    positionmenu.x = 0;// Et initialisation a zero en x et en y (coin superieur gauche pour le menu)
    positionmenu.y = 0;

    SDL_Init(SDL_INIT_EVERYTHING);// Appel de tous les modules de la SDL pour gerer sons, videos, controles du clavier
    SDL_WM_SetIcon(IMG_Load("images/helico_vol_droite.png"), NULL);// On Blit L'image de l'hélicopteur par défaut donc coté droit
    fenetre = SDL_SetVideoMode(1280, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); /* Creation de la fenetre représentée par le pointeur menu en utilisant la largeur et la hauteur.
    On utilise aussi la mémoire vidéo (SDL_HWSURFACE) et le double buffer pour éviter que ça scintille (SDL_HWSURFACE) et le double buffer pour éviter que ça scintille (SDL_DOUBLEBUF)*/
    if ((SDL_Init(SDL_INIT_EVERYTHING) < 0) || (fenetre == NULL)) // On teste l'erreur a l'initialisation des modules de la SDL ou a la creation de la fenetre
    {
        erreur = fopen("erreur.txt","a+");
        if (erreur != NULL)
        {
            fprintf(erreur, "Erreur dans l'initialisation de la SDL pour le menu principal\n");
        }
        fclose(erreur);
        exit(1);
    }

    SDL_WM_SetCaption("CHOPLIFTER", NULL);//Le nom de la fenêtre
    menu = IMG_Load("images/menu.png");//Charge l'image a partir de SDL_Image
    SDL_BlitSurface(menu, NULL, fenetre, &positionmenu);//Indique ou sera affichée l'image



    int continuer = 1; // On initialise la variable 'continuer' a 1 (booleen pour continuer)
    SDL_Event choix; // On cree une variable de type SDL_Event
    while (continuer == 1)// On initialise notre boucle qui permet d'executer le code tant que l'éxecution n'a pas était demandé
    {
        SDL_WaitEvent(&choix);// on attend une réponse au choix dans le menu
        switch (choix.type)
        {
            default://Gère les touches non définient dans ce cas
                    break;

            case SDL_KEYDOWN: //Dans le cas ou une touche est pressée
                switch(choix.key.keysym.sym)  //On vérifie quelle touche est pressée
                {
                    default://Gère les touches non définient dans ce cas
                            break;

                    case SDLK_ESCAPE: //Si c'est la touche échape "ECHAP"
                        continuer = 0; //On stoppe la boucle et on quitte
                        break;

                    case SDLK_RETURN: //Si c'est la touche "ENTREE"
/*------------------------------------------------------------------ A inclure dans une fonction (Fonction jeu) --------------------------------------------------------------------------------*/
                        SDL_Surface *back = NULL;//Initialisation des images et elements avec des pointeurs
                        SDL_Surface *sable = NULL;
                        SDL_Surface *immeuble_bas_gauche = NULL, *immeuble_bas_droite = NULL, *immeuble_milieu_bas_gauche = NULL, *immeuble_milieu_bas_droite = NULL, *immeuble_milieu_haut_gauche = NULL, *immeuble_milieu_haut_droite = NULL, *immeuble_haut_gauche = NULL, *immeuble_haut_droite = NULL, *helico = NULL;
                        SDL_Rect positionback;// Emplacemet de l'image du background grace a une variable

                        positionback.x = 0;// Et initialisation a zero en x et en y (coin superieur gauche pour l'image de fond)
                        positionback.y = 0;



                        back = IMG_Load("images/back.png");//Charge l'image a partir de SDL_Image
                        SDL_BlitSurface(back, NULL, fenetre, &positionback);//Indique ou sera affichée l'image

                        sable = IMG_Load("images/tileset/1.png");
                        immeuble_bas_gauche = IMG_Load("images/tileset/10.png");
                        immeuble_bas_droite = IMG_Load("images/tileset/11.png");
                        immeuble_milieu_bas_gauche = IMG_Load("images/tileset/12.png");
                        immeuble_milieu_bas_droite = IMG_Load("images/tileset/13.png");
                        immeuble_milieu_haut_gauche = IMG_Load("images/tileset/14.png");
                        immeuble_milieu_haut_droite = IMG_Load("images/tileset/15.png");
                        immeuble_haut_gauche = IMG_Load("images/tileset/16.png");
                        immeuble_haut_droite = IMG_Load("images/tileset/17.png");
                        helico = IMG_Load("images/tileset/helico_vol_droite.png");

                        int i,j;
                        int DECALAGE_SCROLL = 0; //Valeur de transition pour le scroll
                        int DEPLACMENT_HELICO_X = 0; //Valeur de transition pour le déplacmeent de l'hélico en axe Horizontal
                        int DEPLACMENT_HELICO_Y = 0; //Valeur de transition pour le déplacmeent de l'hélico en axe Vertical
                        int carte[HAUTEUR_FENETRE_TILE][LARGEUR_FENETRE_TILE];
                        int touches [4]; // Tableau pour gerer les touches
                        FILE* maps1;//on ouvre le fichier map
                        maps1=fopen("maps/map1.txt","r");//on lit le fichier map pour le retranscrire la map dans un tableau
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
                                Rect_dest.x = i*LARGEUR_TILE-DECALAGE_SCROLL;
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

                        int continuer2 = 1; // On initialise la variable 'continuer2' a 1
                        SDL_Event quitter; // On cree une variable de type SDL_Event
                        SDL_EnableKeyRepeat(10, 10);
                        while (continuer2==1 || continuer2 == 2)
                        {

                            while (SDL_PollEvent(&quitter))// Tant que l'événement existe
                            {

                                switch (quitter.type)
                                {
                                    default://Gère les touches non définient dans ce cas
                                            break;



                                    case SDL_KEYDOWN: // Si une touche est enfoncée
                                                     //vérifit les événements en créeant un un tableau pour créer la gestion de plusieurs touches
                                    {

                                            if (quitter.key.keysym.sym == SDLK_p) //Si c'est la touche "p" alors on enclenche la pause et les touches sont gelées
                                            {
                                                touches[0] = 0;
                                                touches[1] = 0;
                                                touches[2] = 0;
                                                touches[3] = 0;
                                                touches[4] = 0;
                                                continuer2 = 2;
/*---------------------------------------------- A inclure dans une autre fonction (Fonction pause)---------------------------------------------------------------------------------------*/                                               continuer = 2;
                                                while (continuer2 == 2)
                                                {
                                                    SDL_Surface *menu_pause = NULL;//Initialisation des images et elements avec des pointeurs
                                                    SDL_Rect positionmenupause;// Emplacemet de l'image du background grace a une variable

                                                    positionmenupause.x = 0;// Et initialisation a zero en x et en y (coin superieur gauche)
                                                    positionmenupause.y = 0;

                                                    menu_pause = IMG_Load("images/pause.png");//Charge l'image a partir de SDL_Image
                                                    SDL_BlitSurface(menu_pause, NULL, fenetre, &positionmenupause);//Indique ou sera affichée l'image
                                                    SDL_Flip(fenetre);

                                                         SDL_WaitEvent(&choix);
                                                         switch (choix.type)
                                                         {
                                                             default://Gère les touches non définient dans ce cas
                                                                        break;

                                                             case SDL_KEYDOWN: //Dans le cas ou une touche est pressée
                                                                 switch(choix.key.keysym.sym)  //On vérifie quelle touche est pressée
                                                                 {
                                                                    default://Gère les touches non définient dans ce cas
                                                                        break;

                                                                     case SDLK_a: //La SDL reconnaissant les clavier qwerty, il faudra enfaite appuyer sur q pour revenir au menu principal
                                                                         continuer2 = 0; //On stoppe la boucle et on quitte
                                                                         continuer = 1;

                                                                         break;

                                                                     case SDLK_RETURN: //Si c'est la touche "ENTREE"
                                                                        continuer2 = 1; //On stoppe la boucle et on retourne au jeu
                                                                        SDL_FreeSurface(menu_pause);
                                                                        break;

                                                                     case SDLK_ESCAPE: //Si c'est la touche "ECHAP"
                                                                        continuer2 = 0; //On stoppe la boucle et on quitte tout
                                                                        continuer = 0;
                                                                        SDL_FreeSurface(menu_pause);
                                                                        break;
                                                                }
                                                                break;
                                                         }



                                                }
                                            }
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
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
                                            if(quitter.key.keysym.sym == SDLK_ESCAPE) // Si échap alors on quitte tout
                                            {
                                                continuer2 = 0;
                                                continuer = 0;

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
                                    }
                                }

                            int COORDONNEES_ACTUELS_HELICO_X = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en X)
                            int COORDONNEES_ACTUELS_HELICO_Y = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en Y)
                            COORDONNEES_ACTUELS_HELICO_X = POSITION_ORIGINE_X_HELICO+DEPLACMENT_HELICO_X;
                            COORDONNEES_ACTUELS_HELICO_Y = POSITION_ORIGINE_Y_HELICO-DEPLACMENT_HELICO_Y;

                            if(touches[0] == 1) //Decalle l'helico sur le bas de 8 pixels
                            {
                                DEPLACMENT_HELICO_Y=DEPLACMENT_HELICO_Y+8;
                            }
                            if(touches[1] == 1) //Decalle l'helico sur le haut de 8 pixels
                            {
                                DEPLACMENT_HELICO_Y=DEPLACMENT_HELICO_Y-8;
                            }
                            if(touches[2] == 1) //Decalle le scroll sur la gauche de 12 pixels
                            {
                                if (COORDONNEES_ACTUELS_HELICO_X < 20)
                                        {
                                            touches[2]=0;
                                        }
                                        else
                               DECALAGE_SCROLL=DECALAGE_SCROLL-12;
                               DEPLACMENT_HELICO_X=DEPLACMENT_HELICO_X-0;
                            }
                            if(touches[3] == 1) //Decalle le scroll sur la droite de 12 pixels
                            {
                                if (COORDONNEES_ACTUELS_HELICO_X > 1150)
                                        {
                                            touches[3]=0;
                                        }
                                        else
                               DECALAGE_SCROLL=DECALAGE_SCROLL+12;
                               DEPLACMENT_HELICO_X=DEPLACMENT_HELICO_X+0;
                            }
                            if(touches[4] == 1) //Prévision de la touche de tire
                            {

                            }
/*=======================================================VERIFICATION COLLISIONS=============================================================*/
                            if (DECALAGE_SCROLL<0 || DEPLACMENT_HELICO_X<0) //limite le scroll et recadre la camera sur l'helico sur le bord gauche
                                {
                                if(touches[2] == 1)
                                    {
                                        DECALAGE_SCROLL=11;
                                        DEPLACMENT_HELICO_X=DEPLACMENT_HELICO_X-12;
                                    }
                                if(touches[3] == 1)
                                    {
                                        DECALAGE_SCROLL=11;
                                        DEPLACMENT_HELICO_X=DEPLACMENT_HELICO_X+12;
                                    }

                                }
                            if (DECALAGE_SCROLL>(LARGEUR_FENETRE_TILE-20)*64 || DEPLACMENT_HELICO_X > 0)   //limite le scroll et recadre la camera sur l'helico sur le bord droit
                                {

                                if(touches[2] == 1)
                                    {
                                        DECALAGE_SCROLL=(LARGEUR_FENETRE_TILE-20)*64;
                                        DEPLACMENT_HELICO_X=DEPLACMENT_HELICO_X-12;
                                    }
                                if(touches[3] == 1)
                                    {
                                        DECALAGE_SCROLL=(LARGEUR_FENETRE_TILE-20)*64;
                                        DEPLACMENT_HELICO_X=DEPLACMENT_HELICO_X+12;
                                    }
                                }

                            //limite l'hélico sur le bord gauche car l'hélico se déplace seulement de 640 pixels sur le bord droit
                            if (DEPLACMENT_HELICO_Y < 0) //limite l'hélico sur le bord bas
                                {
                                    DEPLACMENT_HELICO_Y = 0;
                                }
                            if (DEPLACMENT_HELICO_Y > 640)//limite l'hélico sur le bord haut
                                {
                                    DEPLACMENT_HELICO_Y = 640;
                                }
/*=======================================================FIN VERIFICATION COLLISIONS=============================================================*/
                            SDL_BlitSurface(back, NULL, fenetre, &positionback);//Indique ou sera affichée l'image
                            SDL_BlitSurface(helico, NULL, fenetre, &Rect_helico);//Charge l'image de l'helico
                            Rect_helico.x = COORDONNEES_ACTUELS_HELICO_X; //Distance en X de l'helico (pour le mettre au mileux de l'écran)
                            Rect_helico.y = COORDONNEES_ACTUELS_HELICO_Y; //Distance en y de l'helico

                            for(i=0;i<LARGEUR_FENETRE_TILE;i++)
                            {
                                for(j=0;j<HAUTEUR_FENETRE_TILE;j++)
                                {
                                    Rect_dest.x = i*LARGEUR_TILE-DECALAGE_SCROLL;//Ici a faire avec un -M qui sera un pointeur qui décroit par les touches
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

                        break;
                }
                break;
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
            }

        SDL_BlitSurface(menu, NULL, fenetre, &positionmenu);//Indique ou sera affichée l'image

        SDL_Flip(fenetre);
        SDL_Delay(1);
        }



    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}

