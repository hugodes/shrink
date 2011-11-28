#include "utilitaires.c"

void inittab(int *tab, int lim);
void printinttab(int *tab, int lim);
void printncol(int **tab, int lim, int col);
void remonterarbre(int inddec, int **arbre, int *bin, int compteur);
void inverserligne(int *tab);
void putbincode(FILE *fichierto, int *bin);
int power(int x, int n);
int bintoint(int *bin, int ind, int nb);
int bintoint2(int *bin, int size); 
void inttobin(int d, int *tab, int nbbit);
void freearbre(int **arbre, int nbcol);
void make58(int *tab);
void intsur4oct(int d, int *tab);
