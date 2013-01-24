#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int i,j, valeurs_sprite, valeurs_temp;
    FILE *fichier = NULL;
    fichier = fopen("fichier.txt","r");
    void rewind(fichier);
    do {
        valeurs_temp=fgetc(fichier);
        if (valeurs_temp != ' ')
        {
           valeurs_sprite=valeurs_temp;
           printf("%c", valeurs_sprite);
        }

    } while (valeurs_sprite != EOF);

    fclose(fichier);
    return 0;
}
