#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_BlitSurface.h>
#include <SDL/SDL_image.h> // Inclusion du header pour la SDL


#define LARGEUR_TILE 64  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 64
#define LARGEUR_FENETRE_TILE 60  // nombre a afficher en x et y
#define HAUTEUR_FENETRE_TILE 12
#define HAUTEUR_FENETRE_AFF 768
#define LARGEUR_FENETRE_AFF 1280
#define POSITION_ORIGINE_X_HELICO 300 //(position de démarage de l'hélico dans sa base en coordonnées X)
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

    startgame: ;

    int continuer = 1; // On initialise la variable 'continuer' a 1 (booleen pour continuer)
    SDL_Event choix; // On cree une variable de type SDL_Event

    /*------------------------------------------------------------------ INITIALISATION --------------------------------------------------------------------------------*/
                        SDL_Surface *back = NULL;//Initialisation des images et elements avec des pointeurs
                        SDL_Surface *sable = NULL;
                        SDL_Surface *soucoupe = NULL;
                        SDL_Surface *tire = NULL;
                        SDL_Surface *explosion = NULL;
                        SDL_Surface *immeuble_bas_gauche = NULL, *immeuble_bas_droite = NULL, *immeuble_milieu_bas_gauche = NULL, *immeuble_milieu_bas_droite = NULL, *immeuble_milieu_haut_gauche = NULL, *immeuble_milieu_haut_droite = NULL, *immeuble_haut_gauche = NULL, *immeuble_haut_droite = NULL, *helico = NULL;
                        SDL_Rect positionback;// Emplacemet de l'image du background grace a une variable

                        positionback.x = 0;// Et initialisation a zero en x et en y (coin superieur gauche pour l'image de fond)
                        positionback.y = 0;



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
                        soucoupe = IMG_Load("images/tileset/soucoupe.png");
                        tire = IMG_Load("images/tileset/tire.png");
                        explosion = IMG_Load("images/tileset/explosion/explo1.png");

                        int i,j;
                        int DECALAGE_SCROLL = 0; //Valeur de transition pour le scroll
                        int DEPLACMENT_HELICO_X = 0; //Valeur de transition pour le déplacmeent de l'hélico en axe Horizontal
                        int DEPLACMENT_HELICO_Y = 0; //Valeur de transition pour le déplacmeent de l'hélico en axe Vertical
                        int COORDONNEES_TIRE_T0_X;
                        int COORDONNEES_TIRE_T0_Y;
                        int VIE_HELICO = 3;
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
                        SDL_Rect Rect_soucoupe; // Affichage de la soucoupe
                        SDL_Rect Rect_tire;
                        SDL_Rect Rect_explosion;
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

    int COORDONNEES_SOUCOUPE_X = -2000;
    int COORDONNEES_SOUCOUPE_Y = 20;
    int COORDONNEES_EXPLOSION_X = -99999;
    int COORDONNEES_EXPLOSION_Y = -99999;
    int EXPLOSION_SOUCOUPE = 0;
    int EXPLOSION_HELICO = 0;
    int etat_helico_pour_rotation = 0;
    int etat_helico_tire = 0;
    int TIRE_EXISTANT = 0;
    int COORDONNEES_Y_TIRE = -99999;
    int COORDONNEES_X_TIRE = -99999;

/*------------------------------------------------------------------ FIN INITIALISATION --------------------------------------------------------------------------------*/

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
                    {
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
                                                touches[5] = 0;
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
                                                                         goto startgame;

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
                                            if(quitter.key.keysym.sym == SDLK_TAB)
                                            {
                                                touches[5] = 1;
                                                SDL_Delay(20);
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
                                                if(quitter.key.keysym.sym == SDLK_TAB)
                                                {
                                                    touches[5] = 0;
                                                }

                                        }
                                    }
                                }

                            int COORDONNEES_ACTUELS_HELICO_X_ECRAN = 0; //(Coordonnées X où se situe l'hélico sur l'écran donc grile de 1280 X 768)
                            int COORDONNEES_ACTUELS_HELICO_Y_ECRAN = 0; //(Coordonnées Y où se situe l'hélico sur l'écran donc grile de 1280 X 768)
                            COORDONNEES_ACTUELS_HELICO_X_ECRAN = POSITION_ORIGINE_X_HELICO+DEPLACMENT_HELICO_X;
                            COORDONNEES_ACTUELS_HELICO_Y_ECRAN = POSITION_ORIGINE_Y_HELICO+DEPLACMENT_HELICO_Y;

                            int COORDONNEES_ACTUELS_HELICO_X = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en X)
                            int COORDONNEES_ACTUELS_HELICO_Y = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en Y)
                            COORDONNEES_ACTUELS_HELICO_X = POSITION_ORIGINE_X_HELICO+DEPLACMENT_HELICO_X+DECALAGE_SCROLL;
                            COORDONNEES_ACTUELS_HELICO_Y = POSITION_ORIGINE_Y_HELICO+DEPLACMENT_HELICO_Y;

                            int COORDONNEES_COLLISION_HELICO_X_GAUCHE = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en X pour tester les collisions dans le tableau)
                            int COORDONNEES_COLLISION_HELICO_Y_GAUCHE = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en Y pour tester les collisions dans le tableau)
                            int COORDONNEES_COLLISION_HELICO_X_BORD_GAUCHE = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en X pour tester les collisions dans le tableau Bord Droit)
                            int COORDONNEES_COLLISION_HELICO_Y_BORD_GAUCHE = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en Y pour tester les collisions dans le tableau Bord Bas)
                            COORDONNEES_COLLISION_HELICO_X_GAUCHE = (COORDONNEES_ACTUELS_HELICO_X-11)/(64);
                            COORDONNEES_COLLISION_HELICO_Y_GAUCHE = (COORDONNEES_ACTUELS_HELICO_Y)/(64);
                            COORDONNEES_COLLISION_HELICO_X_BORD_GAUCHE = (COORDONNEES_ACTUELS_HELICO_X-11)/(64);
                            COORDONNEES_COLLISION_HELICO_Y_BORD_GAUCHE = (COORDONNEES_ACTUELS_HELICO_Y+58)/(64);

                            int COORDONNEES_COLLISION_HELICO_X_DROITE = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en X pour tester les collisions dans le tableau)
                            int COORDONNEES_COLLISION_HELICO_Y_DROITE = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en Y pour tester les collisions dans le tableau)
                            int COORDONNEES_COLLISION_HELICO_X_BORD_DROITE = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en X pour tester les collisions dans le tableau Bord Droit)
                            int COORDONNEES_COLLISION_HELICO_Y_BORD_DROITE = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en Y pour tester les collisions dans le tableau Bord Bas)
                            COORDONNEES_COLLISION_HELICO_X_DROITE = (COORDONNEES_ACTUELS_HELICO_X+113)/(64);
                            COORDONNEES_COLLISION_HELICO_Y_DROITE = (COORDONNEES_ACTUELS_HELICO_Y)/(64);
                            COORDONNEES_COLLISION_HELICO_X_BORD_DROITE = (COORDONNEES_ACTUELS_HELICO_X+113)/(64);
                            COORDONNEES_COLLISION_HELICO_Y_BORD_DROITE = (COORDONNEES_ACTUELS_HELICO_Y+58)/(64);

                            int COORDONNEES_COLLISION_HELICO_X_BAS = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en X pour tester les collisions dans le tableau)
                            int COORDONNEES_COLLISION_HELICO_Y_BAS = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en Y pour tester les collisions dans le tableau)
                            int COORDONNEES_COLLISION_HELICO_X_BORD_BAS = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en X pour tester les collisions dans le tableau Bord Droit)
                            int COORDONNEES_COLLISION_HELICO_Y_BORD_BAS = 0; //(Coordonnées où se situe l'hélico suite au mouvement des touches en Y pour tester les collisions dans le tableau Bord Bas)
                            COORDONNEES_COLLISION_HELICO_X_BAS = (COORDONNEES_ACTUELS_HELICO_X+10)/(64);
                            COORDONNEES_COLLISION_HELICO_Y_BAS = (COORDONNEES_ACTUELS_HELICO_Y+70)/(64);
                            COORDONNEES_COLLISION_HELICO_X_BORD_BAS = (COORDONNEES_ACTUELS_HELICO_X+111)/(64);
                            COORDONNEES_COLLISION_HELICO_Y_BORD_BAS = (COORDONNEES_ACTUELS_HELICO_Y+70)/(64);

                            if (EXPLOSION_HELICO != 0)
                                {
                                    touches[0] = 0;
                                    touches[1] = 0;
                                    touches[2] = 0;
                                    touches[3] = 0;
                                    touches[4] = 0;
                                    touches[5] = 0;
                                }

                            if(touches[0] == 1) //Decalle l'helico sur le bas de 8 pixels
                            {
                                if (COORDONNEES_ACTUELS_HELICO_Y == 0 )
                                        {
                                            touches[0]=0;
                                            EXPLOSION_HELICO = 1;
                                        }
                                else
                                DEPLACMENT_HELICO_Y=DEPLACMENT_HELICO_Y-12;
                            }
                            if(touches[1] == 1) //Decalle l'helico sur le haut de 8 pixels
                            {
                                if (carte [COORDONNEES_COLLISION_HELICO_Y_BAS][COORDONNEES_COLLISION_HELICO_X_BAS] >0 || carte [COORDONNEES_COLLISION_HELICO_Y_BORD_BAS][COORDONNEES_COLLISION_HELICO_X_BORD_BAS] > 0)
                                        {
                                            touches[1]=0;
                                            EXPLOSION_HELICO = 1;
                                        }
                                        else
                                DEPLACMENT_HELICO_Y=DEPLACMENT_HELICO_Y+12;
                            }
                            if(touches[2] == 1) //Decalle le scroll sur la gauche de 12 pixels
                            {
                                if (COORDONNEES_ACTUELS_HELICO_X < 20 || carte [COORDONNEES_COLLISION_HELICO_Y_GAUCHE][COORDONNEES_COLLISION_HELICO_X_GAUCHE] >0 || carte [COORDONNEES_COLLISION_HELICO_Y_BORD_GAUCHE][COORDONNEES_COLLISION_HELICO_X_BORD_GAUCHE] > 0)
                                        {
                                            touches[2]=0;
                                            EXPLOSION_HELICO = 1;
                                        }
                                        else
                               DECALAGE_SCROLL=DECALAGE_SCROLL-12;
                            }
                            if(touches[3] == 1) //Decalle le scroll sur la droite de 12 pixels
                            {
                                if (COORDONNEES_ACTUELS_HELICO_X > 3710|| carte [COORDONNEES_COLLISION_HELICO_Y_DROITE][COORDONNEES_COLLISION_HELICO_X_DROITE] >0 || carte [COORDONNEES_COLLISION_HELICO_Y_BORD_DROITE][COORDONNEES_COLLISION_HELICO_X_BORD_DROITE] > 0)
                                        {
                                            touches[3]=0;
                                            EXPLOSION_HELICO = 1;
                                        }
                                        else
                               DECALAGE_SCROLL=DECALAGE_SCROLL+12;
                            }
                            if(touches[4] == 1) //Prévision de la touche de tire
                            {
                                if (TIRE_EXISTANT == 1)
                                {
                                    touches[4] = 0;
                                }
                                else
                                    {
                                        COORDONNEES_TIRE_T0_X = COORDONNEES_ACTUELS_HELICO_X_ECRAN;
                                        COORDONNEES_TIRE_T0_Y = COORDONNEES_ACTUELS_HELICO_Y_ECRAN;
                                         if (etat_helico_pour_rotation == 1 || etat_helico_pour_rotation == 3 )
                                        {
                                            etat_helico_tire = 1;
                                            TIRE_EXISTANT =  1;
                                            COORDONNEES_X_TIRE = COORDONNEES_TIRE_T0_X + 56;
                                            COORDONNEES_Y_TIRE = COORDONNEES_TIRE_T0_Y + 62;
                                        }

                                        if (etat_helico_pour_rotation == 0)
                                        {
                                            etat_helico_tire = 2;
                                            TIRE_EXISTANT =  1;
                                            COORDONNEES_X_TIRE = COORDONNEES_TIRE_T0_X + 113;
                                            COORDONNEES_Y_TIRE = COORDONNEES_TIRE_T0_Y + 62;
                                        }

                                        if (etat_helico_pour_rotation == 2)
                                        {
                                            etat_helico_tire = 3;
                                            TIRE_EXISTANT =  1;
                                            COORDONNEES_X_TIRE = COORDONNEES_TIRE_T0_X;
                                            COORDONNEES_Y_TIRE = COORDONNEES_TIRE_T0_Y + 62;
                                        }
                                    }

                            }

                            if(touches[5] == 1) //Prévision de la touche de tire
                            {
                               switch(etat_helico_pour_rotation)
                                {
                                    case 0 :
                                    helico = IMG_Load("images/tileset/helico_face.png");
                                    SDL_BlitSurface(helico, NULL, fenetre, &Rect_helico);
                                    SDL_Flip(fenetre);
                                    etat_helico_pour_rotation = 1;
                                    break;

                                    case 1 :
                                    helico = IMG_Load("images/tileset/helico_vol_gauche.png");
                                    SDL_BlitSurface(helico, NULL, fenetre, &Rect_helico);
                                    SDL_Flip(fenetre);
                                    etat_helico_pour_rotation = 2;
                                    break;

                                    case 2 :
                                    helico = IMG_Load("images/tileset/helico_face.png");
                                    SDL_BlitSurface(helico, NULL, fenetre, &Rect_helico);
                                    SDL_Flip(fenetre);
                                    etat_helico_pour_rotation = 3;
                                    break;

                                    case 3 :
                                    helico = IMG_Load("images/tileset/helico_vol_droite.png");
                                    SDL_BlitSurface(helico, NULL, fenetre, &Rect_helico);
                                    SDL_Flip(fenetre);
                                    etat_helico_pour_rotation = 0;
                                    break;

                                }
                            }



/*---------------------------------------------------------------------------------------------------------------------------------------------------------------
 ----------------------------------------- Fonction Explosion helico ---------------------------------------------------------------------------------------------
 ----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
 if (EXPLOSION_HELICO == 1 )
 {
    COORDONNEES_EXPLOSION_X = COORDONNEES_ACTUELS_HELICO_X_ECRAN + 20;
    COORDONNEES_EXPLOSION_Y = COORDONNEES_ACTUELS_HELICO_Y_ECRAN + 10;
 }
if (EXPLOSION_HELICO > 0)
{
    COORDONNEES_ACTUELS_HELICO_X_ECRAN = 99999;
    COORDONNEES_ACTUELS_HELICO_Y_ECRAN = 99999;
        switch(EXPLOSION_HELICO)
                                {
                                    case 1 :
                                    explosion = IMG_Load("images/tileset/explosion/explo1.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 2;
                                    SDL_Delay(2);
                                    break;

                                    case 2 :
                                    explosion = IMG_Load("images/tileset/explosion/explo2.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 3;
                                    SDL_Delay(2);
                                    break;

                                    case 3 :
                                    explosion = IMG_Load("images/tileset/explosion/explo3.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 4;
                                    SDL_Delay(2);
                                    break;

                                    case 4 :
                                    explosion = IMG_Load("images/tileset/explosion/explo4.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 5;
                                    SDL_Delay(2);
                                    break;

                                    case 5 :
                                    explosion = IMG_Load("images/tileset/explosion/explo5.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 6;
                                    SDL_Delay(2);
                                    break;

                                    case 6 :
                                    explosion = IMG_Load("images/tileset/explosion/explo6.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 7;
                                    SDL_Delay(2);
                                    break;

                                    case 7 :
                                    explosion = IMG_Load("images/tileset/explosion/explo7.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 8;
                                    SDL_Delay(2);
                                    break;

                                    case 8 :
                                    explosion = IMG_Load("images/tileset/explosion/explo8.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 9;
                                    SDL_Delay(2);
                                    break;

                                    case 9 :
                                    explosion = IMG_Load("images/tileset/explosion/explo9.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 10;
                                    SDL_Delay(2);
                                    break;

                                    case 10 :
                                    explosion = IMG_Load("images/tileset/explosion/explo10.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 11;
                                    SDL_Delay(2);
                                    break;

                                    case 11 :
                                    explosion = IMG_Load("images/tileset/explosion/explo11.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 12;
                                    SDL_Delay(2);
                                    break;

                                    case 12 :
                                    explosion = IMG_Load("images/tileset/explosion/explo12.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 13;
                                    SDL_Delay(2);
                                    break;

                                    case 13 :
                                    explosion = IMG_Load("images/tileset/explosion/explo13.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 14;
                                    SDL_Delay(2);
                                    break;

                                    case 14 :
                                    explosion = IMG_Load("images/tileset/explosion/explo14.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 15;
                                    SDL_Delay(2);
                                    break;

                                    case 15 :
                                    explosion = IMG_Load("images/tileset/explosion/explo15.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 16;
                                    SDL_Delay(2);
                                    break;

                                    case 16 :
                                    explosion = IMG_Load("images/tileset/explosion/explo16.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_HELICO = 0;
                                    SDL_Delay(2);
                                    DECALAGE_SCROLL = 0;
                                    DEPLACMENT_HELICO_X = 0;
                                    DEPLACMENT_HELICO_Y = 0;
                                    VIE_HELICO -= ;
                                    break;


                                }
}

if ( VIE_HELICO == 0)
{

}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------
 ----------------------------------------- FIN Fonction Explosion helico ---------------------------------------------------------------------------------------------
 ----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

 /*====================================================Fonction TIRE=================================================================================================*/

 if (TIRE_EXISTANT ==  1 && ( COORDONNEES_X_TIRE - COORDONNEES_TIRE_T0_X < (-200) || COORDONNEES_X_TIRE - (COORDONNEES_TIRE_T0_X + 112 ) > 200 ||  COORDONNEES_Y_TIRE - (COORDONNEES_TIRE_T0_Y + 62 ) > 200 ) )
{
    TIRE_EXISTANT =  0;
    COORDONNEES_Y_TIRE = -99999;
    COORDONNEES_X_TIRE = -99999;
}

if ( etat_helico_tire == 1 && TIRE_EXISTANT ==  1)
                                        {
                                            COORDONNEES_Y_TIRE += 20;
                                        }

if ( etat_helico_tire == 2 && TIRE_EXISTANT ==  1)
                                        {
                                            COORDONNEES_X_TIRE += 20;
                                        }

if ( etat_helico_tire == 3 && TIRE_EXISTANT ==  1)
                                        {
                                            COORDONNEES_X_TIRE -= 20;
                                        }



/*if ( ( carte [COORDONNEES_Y_TIRE + COORDONNEES_TIRE_T0_Y] [COORDONNEES_X_TIRE + COORDONNEES_TIRE_T0_X] > 1 ) && TIRE_EXISTANT ==  1 )
    {
        if (carte  [COORDONNEES_Y_TIRE + COORDONNEES_TIRE_T0_Y] [COORDONNEES_X_TIRE + COORDONNEES_TIRE_T0_X] == 2)
            {
                TIRE_EXISTANT =  0;
                COORDONNEES_Y_TIRE = -99999;
                COORDONNEES_X_TIRE = -99999;
            }
    }*/
 /*====================================================FIN Fonction TIRE=================================================================================================*/
/*=======================================================VERIFICATION COLLISIONS=============================================================*/
                            if ( COORDONNEES_ACTUELS_HELICO_X  < 576) //limite le scroll et recadre la camera sur l'helico sur le bord gauche
                                {
                                if(touches[2] == 1)
                                    {
                                        DECALAGE_SCROLL=0;
                                        DEPLACMENT_HELICO_X=DEPLACMENT_HELICO_X-12;
                                    }
                                if(touches[3] == 1)
                                    {
                                        DECALAGE_SCROLL=0;
                                        DEPLACMENT_HELICO_X=DEPLACMENT_HELICO_X+12;
                                    }

                                }
                            if (DECALAGE_SCROLL>(LARGEUR_FENETRE_TILE-20)*64 || COORDONNEES_ACTUELS_HELICO_X > (LARGEUR_FENETRE_TILE*64)-640)   //limite le scroll et recadre la camera sur l'helico sur le bord droit
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
/*=======================================================FIN VERIFICATION COLLISIONS=============================================================*/

/*=======================================================DEPLACMENT AVION=============================================================*/

/*=======================================================FIN AVION=============================================================*/

/*=======================================================DEBUT SOUCOUPE=============================================================*/
if ( COORDONNEES_SOUCOUPE_X < COORDONNEES_ACTUELS_HELICO_X_ECRAN )
        {
            COORDONNEES_SOUCOUPE_X += 6;
        }

if ( COORDONNEES_SOUCOUPE_X > COORDONNEES_ACTUELS_HELICO_X_ECRAN )
        {
            COORDONNEES_SOUCOUPE_X -= 6;
        }

if ( COORDONNEES_SOUCOUPE_Y < COORDONNEES_ACTUELS_HELICO_Y_ECRAN + 20 )
        {
            COORDONNEES_SOUCOUPE_Y += 6;
        }

if ( COORDONNEES_SOUCOUPE_Y > COORDONNEES_ACTUELS_HELICO_Y_ECRAN + 20 )
        {
            COORDONNEES_SOUCOUPE_Y -= 6;
        }
if ( ( COORDONNEES_SOUCOUPE_X<= COORDONNEES_X_TIRE && (COORDONNEES_SOUCOUPE_X + 113 ) >= COORDONNEES_X_TIRE ) && ( COORDONNEES_SOUCOUPE_Y<= COORDONNEES_Y_TIRE && (COORDONNEES_SOUCOUPE_Y + 62 ) >= COORDONNEES_Y_TIRE ) )
        {
            COORDONNEES_EXPLOSION_X = COORDONNEES_SOUCOUPE_X + 20;
            COORDONNEES_EXPLOSION_Y = COORDONNEES_SOUCOUPE_Y + 10;
            COORDONNEES_SOUCOUPE_X = -2000;
            EXPLOSION_SOUCOUPE = 1;
        }

if (COORDONNEES_SOUCOUPE_Y == (COORDONNEES_ACTUELS_HELICO_Y_ECRAN + 20) && (COORDONNEES_SOUCOUPE_X == COORDONNEES_ACTUELS_HELICO_X_ECRAN ) )
        {
          DECALAGE_SCROLL = 0;
          DEPLACMENT_HELICO_X = 0;
          DEPLACMENT_HELICO_Y = 0;
          EXPLOSION_SOUCOUPE = 1;
        }
if (EXPLOSION_SOUCOUPE > 0)
{
        switch(EXPLOSION_SOUCOUPE)
                                {
                                    case 1 :
                                    explosion = IMG_Load("images/tileset/explosion/explo1.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 2;
                                    SDL_Delay(2);
                                    break;

                                    case 2 :
                                    explosion = IMG_Load("images/tileset/explosion/explo2.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 3;
                                    SDL_Delay(2);
                                    break;

                                    case 3 :
                                    explosion = IMG_Load("images/tileset/explosion/explo3.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 4;
                                    SDL_Delay(2);
                                    break;

                                    case 4 :
                                    explosion = IMG_Load("images/tileset/explosion/explo4.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 5;
                                    SDL_Delay(2);
                                    break;

                                    case 5 :
                                    explosion = IMG_Load("images/tileset/explosion/explo5.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 6;
                                    SDL_Delay(2);
                                    break;

                                    case 6 :
                                    explosion = IMG_Load("images/tileset/explosion/explo6.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 7;
                                    SDL_Delay(2);
                                    break;

                                    case 7 :
                                    explosion = IMG_Load("images/tileset/explosion/explo7.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 8;
                                    SDL_Delay(2);
                                    break;

                                    case 8 :
                                    explosion = IMG_Load("images/tileset/explosion/explo8.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 9;
                                    SDL_Delay(2);
                                    break;

                                    case 9 :
                                    explosion = IMG_Load("images/tileset/explosion/explo9.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 10;
                                    SDL_Delay(2);
                                    break;

                                    case 10 :
                                    explosion = IMG_Load("images/tileset/explosion/explo10.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 11;
                                    SDL_Delay(2);
                                    break;

                                    case 11 :
                                    explosion = IMG_Load("images/tileset/explosion/explo11.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 12;
                                    SDL_Delay(2);
                                    break;

                                    case 12 :
                                    explosion = IMG_Load("images/tileset/explosion/explo12.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 13;
                                    SDL_Delay(2);
                                    break;

                                    case 13 :
                                    explosion = IMG_Load("images/tileset/explosion/explo13.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 14;
                                    SDL_Delay(2);
                                    break;

                                    case 14 :
                                    explosion = IMG_Load("images/tileset/explosion/explo14.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 15;
                                    SDL_Delay(2);
                                    break;

                                    case 15 :
                                    explosion = IMG_Load("images/tileset/explosion/explo15.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 16;
                                    SDL_Delay(2);
                                    break;

                                    case 16 :
                                    explosion = IMG_Load("images/tileset/explosion/explo16.png");
                                    SDL_BlitSurface(explosion, NULL, fenetre, &Rect_explosion);
                                    SDL_Flip(fenetre);
                                    EXPLOSION_SOUCOUPE = 0;
                                    SDL_Delay(2);
                                    break;
                                }

}

/*=======================================================FIN SOUCOUPE=============================================================*/

                            SDL_BlitSurface(back, NULL, fenetre, &positionback);//Indique ou sera affichée l'image

                            SDL_BlitSurface(helico, NULL, fenetre, &Rect_helico);//Charge l'image de l'helico
                            Rect_helico.x = COORDONNEES_ACTUELS_HELICO_X_ECRAN; //Distance en X de l'helico (pour le mettre au mileux de l'écran)
                            Rect_helico.y = COORDONNEES_ACTUELS_HELICO_Y_ECRAN; //Distance en y de l'helico

                            SDL_BlitSurface(soucoupe, NULL, fenetre, &Rect_soucoupe);
                            Rect_soucoupe.x = COORDONNEES_SOUCOUPE_X; //Distance en X de l'helico (pour le mettre au mileux de l'écran)
                            Rect_soucoupe.y = COORDONNEES_SOUCOUPE_Y;

                            SDL_BlitSurface(tire, NULL, fenetre, &Rect_tire);
                            Rect_tire.x = COORDONNEES_X_TIRE; //Distance en X de l'helico (pour le mettre au mileux de l'écran)
                            Rect_tire.y = COORDONNEES_Y_TIRE;


                            Rect_explosion.x = COORDONNEES_EXPLOSION_X;
                            Rect_explosion.y = COORDONNEES_EXPLOSION_Y;

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
                        SDL_FreeSurface(immeuble_bas_droite);
                        SDL_FreeSurface(immeuble_milieu_bas_gauche);
                        SDL_FreeSurface(immeuble_milieu_bas_droite);
                        SDL_FreeSurface(immeuble_milieu_haut_gauche);
                        SDL_FreeSurface(immeuble_milieu_haut_droite);
                        SDL_FreeSurface(immeuble_haut_gauche);
                        SDL_FreeSurface(immeuble_haut_droite);

                        break;
                        }
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

