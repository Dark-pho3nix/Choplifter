#include "niveau1.h"
#include "SDL_image.h"

int coordonnees[60][12]; // [Colonnes][Lignes]==[i][j]
int i,j;
FILE *fichier = NULL;

void initialiser_coordonnees() // Fonction pour initialiser les coordonnees a 0 pour ne pas avoir de suprise
{
    for (i=0; i<60; i++)
    {
        for (j=0; j<12; j++)
        {
            coordonnees[i][j]=0;
        }
    }
    fichier = fopen("verif.txt", "a+");
    if (fichier !=NULL)
    {
        fprintf(fichier, "Coordonnees initialisee !\n");
    }
    fclose(fichier);
}

void ajout_valeurs_sprites() // Fonction a completer pour mettre des valeurs aux emplacements dans la matrice pour ensuite y afficher les images correspondantes
{
    for (i=0; i<60; i++)
    {
        coordonnees[i][12]=1;
    }
    fichier = fopen("verif.txt", "a+");
    if (fichier !=NULL)
    {
        fprintf(fichier, "Coordonnees a 1 !\n");
    }
    fclose(fichier);
}

void ajouter_sol() // Fonction pour afficher l'image en fonction de la valeurs definie dans la fonction ajout_valeurs_sprites
{
    SDL_Surface *sable = NULL;
    SDL_Surface *fenetre = NULL;
    for (i=0; i<60; i++)
    {
        sable = IMG_Load("images/tileset/1.png"); // Y ajouter alors l'image 1.png : le sable pour le sol
        SDL_BlitSurface(sable, NULL, fenetre, &coordonnees[i][12]); // Indique ou sera affichée l'image
        SDL_Flip(sable);
    }

    fichier = fopen("verif.txt", "a+");
    if (fichier !=NULL)
    {
        fprintf(fichier, "Passe dans la boucle pour le sable !\n");
    }
    fclose(fichier);
}
