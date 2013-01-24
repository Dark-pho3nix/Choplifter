//On a cree un autre.c afin de creer le menu
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "menu.h"
#include "structures.h"

void gestion_du_menu(void) //Cette fonction va nous permettre de gerer notre menu.
{
    SDL_Event event; //Cette variable est celle qui contient l'evennement 'appui d'une touche sur le clavier'

    position_du_curseur = 0;
    while(position_du_curseur<=4)
    SDL_WaitEvent (&event); //Cette fonction atted qu'un evenement se produise
    switch (event.type) //Cette fonction teste l'evenement
    {
        case 1:SDL_KEYDOWN;
        switch (event.key.keysym.sym) //Cette fonction va verifier la valeur de la touche qui a ete enfoncee contenue dans la variable event)
        {
            case 2:SDLK_DOWN; //Appui sur la touche 'bas'
                if (position_du_curseur == 0||position_du_curseur == 1)
                    position_du_curseur++;
                else
                    position_du_curseur == 0;
                break;
            case 3:SDLK_UP; //Appui sur la touche 'haut'
               if (position_du_curseur == 1||position_du_curseur ==2)
                    position_du_curseur--;
                else
                position_du_curseur = 0;
                break;
          /*case SDLK_RETURN
                switch (position_du_curseur)
                {
                    case position_du_curseur == 0

                    break;
                    case position_du_curseur == 1

                    break;
                    case position_du_curseur == 2

                    break;
                }
         */
    }
}
}

void affichage_du_menu (void)
{
    char texte[200]; //Cette chaîne contiendra notre texte

    sprintf(texte, "Choplifter\n");
    if (position_du_curseur != 0 && position_du_curseur !=1)
    {
        sprintf(texte, "Démarrer la partie\n");
        sprintf(texte, "Tableau des scores\n");
        sprintf(texte, "=> Quitter la partie <=");
    }
     if (position_du_curseur != 0 && position_du_curseur !=2)
    {
        sprintf(texte, "Démarrer la partie\n");
        sprintf(texte, "=> Tableau des scores <=\n");
        sprintf(texte, "Quitter la partie");
    }
     if (position_du_curseur != 1 && position_du_curseur !=2)
    {
        sprintf(texte, "=> Démarrer la partie <=\n");
        sprintf(texte, "Tableau des scores\n");
        sprintf(texte, "Quitter la partie");
    }
}
