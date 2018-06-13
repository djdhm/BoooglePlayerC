#include <stdlib.h>
#include "bibdict.h"
#include <stdio.h>
#include <stdbool.h>


#define BLOCK_SIZE_X 5
#define BLOCK_SIZE_Y 4

void draw_box(int w, int h) {
    int x, y;
    for (y = 0; y <= h * BLOCK_SIZE_Y; y++) {
        int on_horizontal = !(y % BLOCK_SIZE_Y);
        for(x = 0; x <= w * BLOCK_SIZE_X; x++) {
            int on_vertical = !(x % BLOCK_SIZE_X);
            if (on_horizontal && on_vertical) {
                printf("+");
            } else if (on_horizontal) {
                printf("-");
            } else if (on_vertical) {
                printf("|");
            } else printf(" ");
         }
         printf("\n");
    }
}

/**
    Créer une nouvelle feuille associé a une lettre et une variable
    indiquant si la feuille est un terminal ou non

**/
feuille * nouvelle_feuille(char lettre,int terminal){

        feuille * temp=malloc(sizeof(feuille));
        temp->terminal=terminal;
        temp->lettre=lettre;
        temp->fils=NULL;
        temp->nb_fils=0;
        return temp;
}

/**
    Fonctions d'accés au attributs de la
    structure feuille

**/

int nb_fils(feuille * f ){
return f->nb_fils;
}
feuille ** fils(feuille *f){

    return f->fils;
}

feuille * fils_ieme(feuille * f,int numero){
        if(numero<f->nb_fils){
            return f->fils[numero];
        }
        return NULL;
}


char  lettre(feuille * f ){
    return f->lettre;
}

void est_terminal(feuille *f){
    f->terminal=1;
}
int terminal(feuille * f){
    return f->terminal;
}


// Recuperer le fils contenant la lettre c
feuille * fils_lettre(feuille * f,char c){
    int cpt=nb_fils(f);
    int i;
    for(i=0;i<cpt;i++){
            if(lettre(fils_ieme(f,i)) ==c  ){
                return fils_ieme(f,i);
            }
    }
    return NULL;
}

/**
    Manipulation des noeud
*/

void ajouter_fils(feuille * parent,feuille * fils){
    if(parent->nb_fils==0) {
        parent->fils=malloc(sizeof(void)*26);
    }
    parent->fils[parent->nb_fils]=fils;
    parent->nb_fils++;

}



// Supression de fils contenant la lettre c
void supprimer_fils(feuille * parent,char c){
    int i=0;
    feuille * temp;
    for(i=0;i<nb_fils(parent);i++){
        temp=fils_ieme(parent,i);
        if(lettre(temp)==c){
            // Liberer le noeud
            free(temp);
            decaler_tab(fils(parent),i,nb_fils(parent));
            parent->nb_fils--;
            return ;
        }
    }

}

void decaler_tab(feuille ** fils,int i, int taille){

    for(i;i<taille-1;i++){

        fils[i]=fils[i+1];

    }
}








/***

Fonctions de manipulation de dict

**/

// Creation d'un nouveau dictionnaire
dict * nouveau_dict(char * chemin_fich){
    dict * temp=malloc(sizeof(dict));

    temp->nom_fich=malloc(strlen(chemin_fich)+2);
    strcpy(temp->nom_fich,chemin_fich);
    temp->racine=nouvelle_feuille('-',0);
    temp->nb_noeuds=0;
    temp->nb_mots=0;

}

feuille * racine(dict * dictionnaire){
    return dictionnaire->racine;
}

int nb_noeuds(dict * dictionnaire)
  {
      return dictionnaire->nb_noeuds;

  }

int nb_mots(dict * dictionnaire)
  {
      return dictionnaire->nb_mots;

  }
void ajouter_mot(dict * dictionnaire, char * mot){
    int longueur=strlen(mot);
    int i;
    feuille * actuel=racine(dictionnaire);
    feuille * suivante;
    for(i=0;i<longueur;i++){
            suivante=fils_lettre(actuel,mot[i]);
            if(suivante==NULL){
                suivante=nouvelle_feuille(mot[i],0);
                ajouter_fils(actuel,suivante);
                dictionnaire->nb_noeuds++;
            }
            actuel=suivante;
    }
    est_terminal(actuel);
    dictionnaire->nb_mots++;

}


bool rechercher_mot(dict * dictionnaire, char * mot){
        feuille * actuel=racine(dictionnaire);
        feuille * suivante;
        int longueur=strlen(mot);
        int i=0;
        int k;
        while( actuel!=NULL &&  nb_fils(actuel)>0 && i<longueur){
            suivante=fils_lettre(actuel,mot[i]);
            actuel=suivante;
             if(actuel!=NULL) {
                printf("Noeud : %c\t   il a %d fils ",lettre(actuel),nb_fils(actuel));
                printf("Les fils : ");
                for(k=0;k<nb_fils(actuel);k++){
                    char t=lettre(fils_ieme(actuel,k));
                    if(t==mot[i+1]){
                        printf("(%c)\t",t);
                    }else{
                        printf("%c\t",t);
                    }
                }
                printf("\n\n\n");
            }
            i++;
        }
        if(actuel!=NULL && i==longueur && terminal(actuel)==1){
                printf("Le mot existe dans le dictionnaire");
            return true;
        }
        if(i=longueur && actuel!=NULL){
            printf("le noeud actuel n'est pas un noeud terminal !!\n");
        }
        else{
                printf("Aucun noeud fils ne contient la lettre %c\n",mot[i]);

        }
        printf("Mot introuvable ...");
        return false;


}


dict * charger_fichier(char * chemin){
        dict * temp=nouveau_dict(chemin);
        FILE * fichier;
        fichier=fopen(chemin,"r");
        if(fichier==NULL){
            printf("Erreur de lecture de fichier");
            return;
        }
        int nombre_ligne;
        char * mot =malloc(60);
        fscanf(fichier,"%d",&nombre_ligne);
        printf("le fichier contient %d lignes \n", nombre_ligne);
        printf("Chargement des mots en memoire ...\n");
        int cpt=0;
        for(cpt;cpt<nombre_ligne;cpt++){
            fscanf(fichier,"%s",mot);
            ajouter_mot(temp,mot);
        }

        printf("Chargement termine ...\n");
        return temp;

}

