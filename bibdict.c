#include <stdlib.h>
#include "bibdict.h"
#include <stdio.h>
#include <stdbool.h>




/**
    Créer une nouvelle feuille associé a une lettre et une variable
    indiquant si la feuille est un terminal ou non

**/
feuille * nouvelle_feuille(char lettre,bool terminal){

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
// retourne le nombre de fils d'un npeud f
int nb_fils(feuille * f ){
return f->nb_fils;
}
// retourne le tableau des fils d'un noeud f
feuille ** fils(feuille *f){

    return f->fils;
}

// tetourne le i-eme fils de noeud f si
// il existe sinon NULL
feuille * fils_ieme(feuille * f,int numero){
        if(numero<f->nb_fils){
            return f->fils[numero];
        }
        return NULL;
}

// retourne la lettre que contient le noeud
char  lettre(feuille * f ){
    return f->lettre;
}
// cette fonction permet de mettre l'attribut terminal de feuille a vrai
void est_terminal(feuille *f){
    f->terminal=true;
}
// retourne vrai si F est un noeud terminal
bool terminal(feuille * f){
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
    // si le noeud n as pas de fils on
    // alloue un tableau de 26 fils
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
    // pour chaque fils on verifie s il contient la lettre c
    for(i=0;i<nb_fils(parent);i++){
        temp=fils_ieme(parent,i);
        if(lettre(temp)==c){
            // Liberer le noeud
            free(temp);
            // decaler touts les fils suivants pour prendre la place de ce fils supprimé
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
// recuperer la racine de dictionnaire

feuille * racine(dict * dictionnaire){
    return dictionnaire->racine;
}
// retourner le nombre de noeud de dictionnaire
int nb_noeuds(dict * dictionnaire)
  {
      return dictionnaire->nb_noeuds;

  }
// retourner le nombre de mots saisis dans le dictionnaire
int nb_mots(dict * dictionnaire)
  {
      return dictionnaire->nb_mots;

  }

  // ajouter un mot au dictionnaire
void ajouter_mot(dict * dictionnaire, char * mot){
    int longueur=strlen(mot);
    int i;
    feuille * actuel=racine(dictionnaire);
    feuille * suivante;
    // pour chaque lettre de mot
    for(i=0;i<longueur;i++){
            // on cherche le fils qui contient cette lettre
            suivante=fils_lettre(actuel,mot[i]);
            //s'il existe pas alors doit le créer

            if(suivante==NULL){
                // on créer ce noeud est on l'ajoute au noeud
                // qu'on est entrain de parcourir
                suivante=nouvelle_feuille(mot[i],0);
                ajouter_fils(actuel,suivante);
                // on incremente le nombre de noeuds de dict
                dictionnaire->nb_noeuds++;
            }
            // on passe au noeud suivant
            actuel=suivante;
    }
    // a la fin de mot le noeud ou on s"est arreté est un noeud terminal
    est_terminal(actuel);
    // on increments le nombre de noeuds
    dictionnaire->nb_mots++;

}


bool rechercher_mot(dict * dictionnaire, char * mot){
        feuille * actuel=racine(dictionnaire);
        feuille * suivante;
        int longueur=strlen(mot);
        int i=0;
        int k;
        //pour chaque lettre c de mots
        while( actuel!=NULL &&  nb_fils(actuel)>0 && i<longueur){
                // in verifie si le noeud actuel contient un fils qyu contient
                // la lettre c
            suivante=fils_lettre(actuel,mot[i]);
            actuel=suivante;
             // si oui on passe vers ce noeud
             // il sera le noeud actuel et on passe a la lettre syuvante
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
        // si le noeud actuell n'est pas NULL et on a parcouru toutes les lettres de mot a chercher
        // alors cette sequence de lettre existe
        // reste a verifier que le noeud actuel est un noeud terminal
        if(actuel!=NULL && i==longueur   ){
                if(terminal(actuel)==1){
                    printf("Le mot existe dans le dictionnaire");
                    return true;
                }

                printf("le noeud actuel n'est pas un noeud terminal !!\n");
                return false;
        }


        printf("Aucun noeud fils ne contient la lettre %c\n",mot[i]);
        printf("Mot introuvable ...");
        return false;


}


dict * charger_fichier(char * chemin){
        dict * temp=nouveau_dict(chemin);
        FILE * fichier;
        // ouverture de fichier en mode lecture
        fichier=fopen(chemin,"r");
        if(fichier==NULL){
            printf("Erreur de lecture de fichier");
            return;
        }
        int nombre_ligne;
        char * mot =malloc(60);
        // lire la premiere ligne qui contient le nombre de mots
        fscanf(fichier,"%d",&nombre_ligne);
        printf("le fichier contient %d lignes \n", nombre_ligne);
        printf("Chargement des mots en memoire ...\n");
        int cpt=0;
        for(cpt;cpt<nombre_ligne;cpt++){
                // lire toutes les lignes et les ajouter dans le dictionnaire
            fscanf(fichier,"%s",mot);
            ajouter_mot(temp,mot);
        }

        printf("Chargement termine ...\n");
        return temp;

}

