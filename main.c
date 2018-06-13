#include "bibdict.h"
int main(int argc,char * argv){

 dict * didi=charger_fichier("dict.txt");
    //dict * didi=nouveau_dict("test.txt");
   // ajouter_mot(didi,"allo");
    //ajouter_mot(didi,"alli");
    //ajouter_mot(didi,"all");
    printf("Nombre de mots total = %d\n",nb_mots(didi));
    printf("Nombre de noeuds total = %d\n",nb_noeuds(didi));

    printf("rechercher un mot : ");
    char * mot=malloc(50);
   // scanf("%s",mot);
    rechercher_mot(didi,"porrid");

    printf("\n");

    //draw_box(4,5);
    return 0;
}
