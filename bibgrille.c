#include <time.h>
#include <stdlib.h>
#define HAUTEUR_GRILLE 5
#define LARGEUR_CASE 4
#define MAX 25
#define MIN 0

void dessiner_grille(char **lettres,int w, int h) {
    int x, y;
    printf("\n");
    for (y = 0; y <= h * LARGEUR_CASE; y++) {
        printf("\t\t");
        int trait_horizontal = !(y % LARGEUR_CASE);
        for(x = 0; x <= w * HAUTEUR_GRILLE; x++) {
            int trait_vertical = !(x % HAUTEUR_GRILLE);
            if (trait_horizontal && trait_vertical) {
                printf("+");
            } else if (trait_horizontal) {
                printf("-");
            } else if (trait_vertical) {
                printf("|");
            } else{

                 int xvaleur = x%HAUTEUR_GRILLE;
                 int yvaleur = y%LARGEUR_CASE;
                 if(xvaleur==2 && yvaleur==2){
                    printf("%c",lettres[y/h][x/w]);
                 }else{
                    printf(" ");
                 }
            }

         }
         printf("\n");
    }
}

char lettre_aleatoire(){
    // fonction de generation de nombre pseudo aleatoire
    /**
        pour generer des nombres qui semble etre aleatoire
        on vas utiliser l'heure actuel de systeme (avec millisecondes)
        comme graine pour la fonction pseudo aleatoire -

    **/
    int  nombreMystere = (rand() % (MAX  + 1)) ;
    return nombreMystere;

}


void genererGrille(char ** tab,int x,int y){

    time_t t=time(NULL);
    // allocation de memoire pour la matrice de lettre
    int i,j;
    srand(time(0));

    for(i=0;i<x;i++){
        tab[i]=malloc(sizeof(void)*j);
        for(j=0;j<y;j++){
            // Tirage d'un nombre aléatoire
            tab[i][j]=lettre_aleatoire()+'A';
        }


    }

}

