#ifndef BIBGRILLE_H_INCLUDED
#define BIBGRILLE_H_INCLUDED



#endif // BIBGRILLE_H_INCLUDED
struct grille{
    // Tableau contenant les lettres de la grille
    char ** tableau;
    int largeur;
    int longueur;

};


typedef struct grille grille;



char lettre_dans_case(grille *g,int x,int y);
int largeur(grille * g);
int longueur(grille * g);
void dessiner_grille(grille * g);

grille * genererGrille(int x,int y);
char lettre_aleatoire();




