//renvoie un pointeur vers la racine d'un arbre binaire
void creerarbre(int *tabproba, int **arbre, int NBCHAR) {
	extern int racine;
	int i, j;
	//int testcount=0;
	//nombre de caractères distints dans le fichier
	int nbcardist=0;
	//nombre de ligne du tableau
	extern int nbligne;
	/* ceci est le tableau qui permet de decire l'arbre de Huffman 
	colone n°0: contient le code des differents char
		1: contient la proba assiciée à chaque noeud
		2: fils gauche
		3: fils droit
		4: parent */
	//on determinde le nombre de lignes du tableau
	for (i=0; i<NBCHAR; i++) {
	    if (tabproba[i] != 0) {
		    nbcardist++;
	    }
	}
	nbligne = nbcardist*2-1;
	//on initialise le tableau
	for (j=0; j<5; j++) {
	    arbre[j] = malloc(nbligne * sizeof(int));
	}
	//on initialise les colones 0, 2, 3  et 4 avec un entier > à nbligne
	//cela sert a provoquer une erreur si on essaye d'acceder à une ligne
	//qui n'a pas été initialisée
	for (j=0; j<5; j++) {
	    if (j != 1) {
		for (i=0; i<nbligne; i++) {
			    arbre[j][i] = 513;
			}
	    }
	}
	//on initialise la colone 1 avec 0 avec le meme but que l'initialisation 
	//de la colone 0
	for (i=0; i<nbligne; i++) {
	    arbre[1][i] = 0;
	}
	//on met dans la colone 0 le code les car présents dans le fichier
	//dans la colone 1 on met le proba associée
	j=0;
	for (i=0; i<NBCHAR; i++) {
	    if (tabproba[i] != 0) {
		   arbre[0][j] = i;
		   arbre[1][j] = tabproba[i];
		   j++;
	    }
	}
	//printncol(arbre, nbligne, 5);
	//trouve les deux elemnt de plus petite probabilité sans père, et les lient
	// avec un noeud qui aura comme fils gauche et droit ceux ci, on mettra donc
	// a jour leur père aussi
	int fini=0, elemtrouve=0, k, l, indder, indpetitproba1, indpetitproba2;
	int ind2elem[2];

	indder = nbcardist;
	//printf("indder: %d\n", indder);
	//tant qu'il existe deux éléments sans pèere...
	while (fini == 0) {
		k=0;
		//printf("debut\n");
		//	printf("indince du dernier char = %d\n", indder);
		//on parcour le tableau pour trouver les 2 premiers element
		//sans pere si il y en a
		i=0;
		elemtrouve=0;
		k=0;
		while (i < nbligne && elemtrouve < 2) {
			//printf("bouclewhile test\n");
			if (arbre[1][i] > 0 && arbre[4][i] ==  513) {
			ind2elem[k] = i;
			k++;
			elemtrouve++;
		    }
			i++;
		}
		//printf("Elem trouvé: %d\n", elemtrouve);
		//printf("plus petit1: %d\n plus petit2: %d\n", 
		//ind2elem[0], ind2elem[1]);
		//printf("milieu1\n");
		//printf("racine = %d\nfini= %d\n", racine, fini);
		if (elemtrouve < 2) { 
			racine = indder;	    
			fini++;
			    }
		else {
			//on met dans indproba 1 l'indice des deuw pluys petites
			//probabilités sans père
			//et dans indproba2 la 2eme plus petite
			if (arbre[1][ind2elem[0]] < arbre[1][ind2elem[1]]) {
				indpetitproba1= ind2elem[0];
				indpetitproba2= ind2elem[1];
			}
			else {
				indpetitproba1= ind2elem[1];
				indpetitproba2= ind2elem[0];
			}
			//cherchons les 2 plus peites proba sans pere dans
			//tout le tableau
			//on commence à l'indice apres le 2eme element sasn
			//pere
			//On fini a l'indexe avant la racine
			for (l=ind2elem[1]+1; l<nbligne; l++) {
				if (arbre[4][l] == 513 && arbre[1][l] > 0 && arbre[1][l] < arbre[1][indpetitproba1]) {
				       indpetitproba2 = indpetitproba1;       
				       indpetitproba1 = l;
				}
				else if (arbre[4][l] == 513 && arbre[1][l] > 0 && arbre[1][l] < arbre[1][indpetitproba2]) {
					indpetitproba2 = l;
				}
			}
			//printf("indpeiti1: %d indpetit2: %d\n", indpetitproba1, indpetitproba2);
			//ind2elem[0] = indpluspetit1;
			//ind2elem[1] = indpluspetit2;
			//printf("Fini de trouver les 2 plus petits 1: %d 2: %d\n", indpluspetit1, indpluspetit2);
			

			//je donne l'information du fg et fd
			arbre[2][indder] = indpetitproba1;
			arbre[3][indder] = indpetitproba2; 
			//je donne la proba cummulée
			////printf("milieu2\n");
			//printf("indder: %d\n", indder);
			////printf("elements trouvés: %d\n", elemtrouve);
			arbre[1][indder] = arbre[1][indpetitproba1] + arbre[1][indpetitproba2];
			//je donne l'information du pere au deux fils
			arbre[4][indpetitproba1] = arbre[4][indpetitproba2] = indder;
			indder++;
			//printncol(arbre, nbligne, 5);
		}
	}
	//printf("test4\n");
}

