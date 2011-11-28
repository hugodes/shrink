#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "distriproba.h"
#include "utilitaires.h"
#include "creerarbre.h"
#include "creerfichcomp.h"
#include "rebuildarbre.h"
#include "decompresser.h"

#define NBCHAR 256

int nbligne;
int racine;
int nbchar;

//compresse, decompresse un fichier donner en argument.
//l'argument -c compresse, l'argument -d decompresse
int main (int argc, char * argv[], char *env[])
{

    int tabproba[NBCHAR];
    FILE *fichier = NULL;
    FILE *fichierto = NULL;
    FILE *fichierfrom = NULL;
    FILE *fichiercount = NULL;
    //racine de l'arbre
    extern int nbligne, nbchar;
    int *arbre[5];

    //si toutes les condtions sont réunies pour commencer la compression...
    if (argc > 2 && argv[1][1] == 'c'){
        fichier = fopen(argv[2], "r");
        //initialisation du tableau
        inittab(tabproba, NBCHAR);
        //stockage de la distribution probabilistique
        distriproba(fichier, tabproba);
	//printf("Fini la distriproba\n");
	//fermer le fichier
	fclose(fichier);
        //creer l'arbre à partir de la distri probabilistique retenir son
	//pointeur
        creerarbre(tabproba, arbre, NBCHAR);
        //printf("fini de creer arbre\n");

        //printinttab(tabproba, NBCHAR);
	//printf("%d\n", nbligne);
        //printncol(arbre, nbligne, 5);
	//creer le fichier compréssé
	fichier = fopen(argv[2], "r");
	fichierto = fopen(argv[3], "w");
	fichiercount = fopen(argv[2], "r");
	creerfichcomp(fichier, fichierto, arbre, fichiercount); 
	//printf("Le nombre de char= %d\n", nbchar);
	fclose(fichier);
	fclose(fichierto);
	fclose(fichiercount);
	freearbre(arbre, 5);
	//int bin[9];
	//make58(bin);
	//printf("Alors?: %d\n", bintoint2(bin, 8));
	printf("Le fichier %s a bien ete compresse\n", argv[2]);
	printf("Le nom du fichier compresse est: %s\n", argv[3]);
    }
    //si toute les elements sont réunis pour la decompression...
    if (argc > 2 && argv[1][1] == 'd') {
	    fichierfrom = fopen(argv[2], "r");
	    fichierto = fopen(argv[3], "w");
	    //ici on analyse le header du fichier compresse pour reconstruire 
	    //l'abre (sans la colone realtive aux proba
	    //Au passage on recupere aussi le nombre total de char dans 
	    //le fichier de depart
	    rebuildarbre(fichierfrom, arbre);
	    //printncol(arbre, nbligne, 4);
	    //Muni de l'abre (notre dictionaire) on reconstruit le fichier
	    decompresser(fichierfrom, fichierto, arbre);
	    freearbre(arbre, 4);
	    printf("Le fichier %s a bien ete decompresse\n", argv[2]);
	    printf("Le nom du fichier decompresse est: %s\n", argv[3]);
    }
    
    return 0;
}
