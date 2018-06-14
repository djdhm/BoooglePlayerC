#ifndef BIBDICT_H_INCLUDED
#define BIBDICT_H_INCLUDED



#endif // BIBDICT_H_INCLUDED
#include <stdbool.h>
/**
    Structure utilisé pour sauvegarder une lettre
    chaque lettre aura deux fils (droite et gauche)

    une feuille peut etre un terminal
    si il existe cet lettre est
    la fin d'un mot qui commence par la racine

*/
typedef struct feuille {
    char  lettre;
    struct feuille ** fils;
    int nb_fils;
    bool terminal;

} feuille;
/**
    Structure de Dictionnaire qui vas contenier tout les mots
    Le dictionnaire contient une racine
    et un nom de fichier depuis ou sont chargés les mots
*/
struct dict{
    feuille * racine; // racine de l'arbre
    char * nom_fich;
    int nb_noeuds;
    int nb_mots;

};
typedef struct dict dict;


typedef struct feuille feuille;
typedef struct dict dict;



feuille * nouvelle_feuille(char lettre,bool terminal);

int nb_fils(feuille * f );
feuille ** fils(feuille *f);
feuille * fils_ieme(feuille * f,int numero);
char  lettre(feuille * f );

void est_terminal(feuille *f);
bool terminal(feuille * f);
feuille * fils_lettre(feuille * f,char c);
void ajouter_fils(feuille * parent,feuille * fils);
void supprimer_fils(feuille * parent,char c);
void decaler_tab(feuille ** fils,int i, int taille);
dict * nouveau_dict(char * chemin_fich);
feuille * racine(dict * dictionnaire);
int nb_noeuds(dict * dictionnaire);
int nb_mots(dict * dictionnaire);
void ajouter_mot(dict * dictionnaire, char * mot);
bool rechercher_mot(dict * dictionnaire, char * mot);

dict * charger_fichier(char * chemin);
