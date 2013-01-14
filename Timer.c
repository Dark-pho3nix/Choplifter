#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main ()
{
    int heure, min, sec;
    printf("Entrez le temps du compte à rebours au format hh:mm:ss ");
    scanf("%d:%d:%d", &heure, &min, &sec);
    while(heure>=0)
    {
        while(min>=0)
        {
            while(sec>=0)
            {
                printf("%d:%d:%d\n", heure, min, sec);
                _sleep(1000);//car en milliseconde donc un intervalle de 1s pour la boucle
                sec--;
            }
            sec=60;
            min--;
        }
        min=60;
        heure--;
    }
    return 0;
}
