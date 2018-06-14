#include <time.h>
#include <stdlib.h>
#define HAUTEUR_GRILLE 5
#define LARGEUR_CASE 4
#define MAX 25
#define MIN 0
#include "bibgrille.h"


int largeur(grille *g){
    return g->largeur;
}
int longueur(grille *g){
    return g->longueur;
}
char lettre_dans_case(grille *g,int x,int y){
    return g->tableau[x][y];
}
// cette fonction permet de desiiner une grille sur la console
void dessiner_grille(grille * g) {
    int x, y;
    int h=longueur(g);
    int w=largeur(g);
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
                    printf("%c",lettre_dans_case(g,y/h,x/w));
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
    return (rand() % (MAX  + 1)) ;

}


grille * genererGrille(int x,int y){

    // allocatioon de memoire pour la grille
    grille * temp = malloc(sizeof(grille));
    // allocation de memoire pour la matrice de lettre
    char ** tab=malloc(sizeof(void)*x);

    int i,j;
    /**
        la fonction Srand() permet de fixer le seed pour la fonction rand de géneration pseudo-aléatoire
        et vue que cette générer une meme sequence de lettre si elle a le meme seed
        on vas utiliser le temps actuel de la machine ce qui permettera d'avoir des séries de nombre différente
        a chaque fois
    */
    srand(time(0));

    for(i=0;i<x;i++){
        tab[i]=malloc(sizeof(void)*j);
        for(j=0;j<y;j++){
            // Tirage d'un nombre aléatoire en 0 et 25 A-Z
            tab[i][j]=lettre_aleatoire()+'A';
        }


    }
    temp->tableau=tab;
    temp->largeur=x;
    temp->longueur=y;
    return temp;
}

