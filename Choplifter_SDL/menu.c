
//On a cree un autre.c afin de creer le menu
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "SDL_image.h"
#include "menu.h"

void menu(void)
{
    //SDL_Init(SDL_INIT_EVERYTHING);// Appel de tous les modules de la SDL pour gerer sons, videos, controles du clavier

    //Gestion du menu
    SDL_Event touche; //Cette variable est celle qui contient l'evennement 'appui d'une touche sur le clavier'
    int position_du_curseur;
    position_du_curseur = 0;
    while(position_du_curseur<4)
    SDL_WaitEvent (&touche); //Cette fonction attend qu'un evenement se produise.
    if (touche.type == SDL_KEYDOWN) //Cette fonction teste l'evenement.
    {
            if (touche.key.keysym.sym == SDLK_DOWN)  //Cette fonction va verifier la valeur de la touche qui a ete enfoncee contenue dans la variable 'touche'. Ici, appui sur la touche 'bas'.
               {
                   if (position_du_curseur == 0||position_du_curseur == 1)
                    position_du_curseur = position_du_curseur+1 ;
                   else
                    position_du_curseur = 0;

               }
            if (touche.key.keysym.sym == SDLK_UP) //Appui sur la touche 'haut'
            {
                if (position_du_curseur == 1||position_du_curseur ==2)
                    position_du_curseur = position_du_curseur-1;
                else
                position_du_curseur = 2;

            }
            if (touche.key.keysym.sym == SDLK_RETURN) //Appui sur la touche 'Entree'
                position_du_curseur = 5;
    }

    //Affichage du menu
    TTF_Init();         //On lance la SDL_TTF qui va nous permmettre d'ecrire du texte dans notre fenetre SDL.
    if(TTF_Init()== -1) //On verifie que cette derniere c'est lancee correctement, si ce n'est pas le cas, on cree un fichier .txt contenant un message explicatif de l'erreur.
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Surface *fenetre = NULL, *back = NULL;
    SDL_Surface *titre = NULL, *nouvellepartie = NULL, *nouvellepartiesurbrillance = NULL, *tableaudesscores = NULL, *tableaudesscoressurbrillance = NULL, *quitter = NULL, *quittersurbrillance = NULL;
    SDL_Rect positionback;
    SDL_Rect positionTitre;
    SDL_Rect positionNouvellePartie;
    SDL_Rect positionNouvellePartieSurbrillance;
    SDL_Rect positionTableaudesScores;
    SDL_Rect positionTableaudesScoresSurbrillance;
    SDL_Rect positionQuitter;
    SDL_Rect positionQuitterSurbrillance;
    TTF_Font *policetitre = NULL; //Ce pointeur pointe vers la variable qui contiendra notre police pour le titre.
    TTF_Font *policeoptions = NULL;
    TTF_Font *policeoptionssurbrillance = NULL;
    SDL_Color couleurTitre = {104, 112, 16};
    SDL_Color couleurOption = {255, 255, 255};
    policetitre = TTF_OpenFont("stencil.ttf", 36); //La variable 'police' prend la valeur de la police que nous allons utiliser.
    policeoptions = TTF_OpenFont("stencil.ttf", 20);
    policeoptionssurbrillance = TTF_OpenFont("stencil.ttf", 20);
    TTF_SetFontStyle(policeoptionssurbrillance, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE); //Cette fonction rendra la police pour les options en surbrillance en gras et en souligne.
    FILE *erreur = NULL;


    positionback.x = 0;// Et initialisation a zero en x et en y (coin superieur gauche)
    positionback.y = 0;

    positionTitre.x = 349;
    positionTitre.y = 103;

    positionNouvellePartie.x = 434;
    positionNouvellePartie.y = 386;

    positionNouvellePartieSurbrillance.x = 434;
    positionNouvellePartieSurbrillance.y = 386;

    positionTableaudesScores.x = 434;
    positionTableaudesScores.y = 486;

    positionTableaudesScoresSurbrillance.x = 434;
    positionTableaudesScoresSurbrillance.y = 486;

    positionQuitter.x = 434;
    positionQuitter.y = 586;

    positionQuitterSurbrillance.x = 434;
    positionQuitterSurbrillance.y = 586;

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

    titre = TTF_RenderText_Blended(policetitre, "CHOPLIFTER", couleurTitre); //Charge la SDL_Surface contenant le texte
    SDL_BlitSurface(titre, NULL, fenetre, &positionTitre);
    SDL_Flip(titre);
    if ((position_du_curseur = 0))
    {
        nouvellepartiesurbrillance = TTF_RenderText_Blended(policeoptionssurbrillance, "NOUVELLE PARTIE", couleurOption);
        SDL_BlitSurface(nouvellepartie, NULL, fenetre, &positionNouvellePartieSurbrillance);
        SDL_Flip(nouvellepartiesurbrillance);
        tableaudesscores = TTF_RenderText_Blended(policeoptions, "TABLEAU DES SCORES", couleurOption);
        SDL_BlitSurface(tableaudesscores, NULL, fenetre, &positionTableaudesScores);
        SDL_Flip(tableaudesscores);
        quitter = TTF_RenderText_Blended(policeoptions, "QUITTER", couleurOption);
        SDL_BlitSurface(nouvellepartie, NULL, fenetre, &positionQuitter);
        SDL_Flip(quitter);

    }

    else
    {
        if ((position_du_curseur =1))
        {
            nouvellepartie = TTF_RenderText_Blended(policeoptions, "NOUVELLE PARTIE", couleurOption);
            SDL_BlitSurface(nouvellepartie, NULL, fenetre, &positionNouvellePartie);
            SDL_Flip(nouvellepartie);
            tableaudesscoressurbrillance = TTF_RenderText_Blended(policeoptionssurbrillance, "TABLEAU DES SCORES", couleurOption);
            SDL_BlitSurface(tableaudesscores, NULL, fenetre, &positionTableaudesScoresSurbrillance);
            SDL_Flip(tableaudesscoressurbrillance);
            quitter = TTF_RenderText_Blended(policeoptions, "QUITTER", couleurOption);
            SDL_BlitSurface(nouvellepartie, NULL, fenetre, &positionQuitter);
            SDL_Flip(quitter);

        }

        else
        {
            nouvellepartie = TTF_RenderText_Blended(policeoptions, "NOUVELLE PARTIE", couleurOption);
            SDL_BlitSurface(nouvellepartie, NULL, fenetre, &positionNouvellePartie);
            SDL_Flip(nouvellepartie);
            tableaudesscores = TTF_RenderText_Blended(policeoptions, "TABLEAU DES SCORES", couleurOption);
            SDL_BlitSurface(tableaudesscores, NULL, fenetre, &positionTableaudesScores);
            SDL_Flip(tableaudesscores);
            quittersurbrillance = TTF_RenderText_Blended(policeoptionssurbrillance, "QUITTER", couleurOption);
            SDL_BlitSurface(nouvellepartie, NULL, fenetre, &positionQuitterSurbrillance);
            SDL_Flip(quittersurbrillance);
        }
    }

    TTF_CloseFont(policetitre);
    TTF_CloseFont(policeoptions);
    TTF_CloseFont(policeoptionssurbrillance);
    TTF_Quit();
    SDL_FreeSurface(back);
    SDL_FreeSurface(titre);
    SDL_FreeSurface(nouvellepartie);
    SDL_FreeSurface(nouvellepartiesurbrillance);
    SDL_FreeSurface(tableaudesscores);
    SDL_FreeSurface(tableaudesscoressurbrillance);
    SDL_FreeSurface(quitter);
    SDL_FreeSurface(quittersurbrillance);
    SDL_Quit();

}
