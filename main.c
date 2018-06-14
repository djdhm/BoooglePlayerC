#include "bibdict.h"
#include "bibgrille.h"
int main(int argc,char * argv){

 dict * didi=charger_fichier("dict.txt");
    //dict * didi=nouveau_dict("test.txt");
   // ajouter_mot(didi,"allo");
    //ajouter_mot(didi,"alli");
    //ajouter_mot(didi,"all");
    printf("Nombre de mots total = %d\n",nb_mots(didi));
    printf("Nombre de noeuds total = %d\n",nb_noeuds(didi));

  //  char * mot=malloc(50);
   // scanf("%s",mot);
   // rechercher_mot(didi,"porriff");

  //  printf("\n");

    grille * test;
    test=genererGrille(5,5);
    printf("Affichage de la grille de lettres : ");
    dessiner_grille(test);

    return 0;
}
