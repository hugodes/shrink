//Dans le fichier d'en tête on met les informations relatives au codage
//pour pouvoir ensuite decoder sans soucis!
//Pour ceci on va constituer le header du fichier de cette façon:
//0)Le premier caractere est le nombre de caractèeres independants
//1)4 colones
//		c1: Le code ASCII du caractere
//		c2: indice fg
//		c3: indice fd
//		c4: indice pere
//2) Les colones sont séparées par des char de valeur 255
void putheader(FILE *fichierto, int **arbre, FILE *fichierfrom)
{
	int i, j;
	extern int nbligne;
	extern int nbchar;
	int tabnbchar[4];
	//on parcoure tout le fichier pour trouver le nombre de caractères
	nbchar=0;
	while ((i=fgetc(fichierfrom)) !=EOF) {
		nbchar++;
	}
	//on met le nombre de caractères originaux dans le fichier
	fputc(nbligne, fichierto);
	//printf("\n\n\n");
	//printf("J'ai mis l'octet de valeur %d dans le fichier (nbligne)\n\n\n\n", nbligne);
	//On inscrit sur 4 octets le nombre de caractères total du fichier 
	//orginial.
	//printf("nbchar= %d\n", nbchar);
	intsur4oct(nbchar, tabnbchar);
	for (i=0; i<4; i++) {
		//printf("J'ai mi l'octet de valeur %d dans le fichier (intsur4oct)\n", tabnbchar[i]);
		//printf("Et un autre\n");
		fputc(tabnbchar[i], fichierto);
	}
	//printf("\n\n\n");
	//printncol(arbre, nbligne, 5);
	for(i=0; i<5; i++) {
		if (i != 1) {
			for (j=0; j<nbligne; j++) {
				if (arbre[i][j] > 255) {
					fputc(254, fichierto);
					//printf("J'ai mi l'octet de valeur %d dans le fichier (arbre)\n", 254);
				}
				else {
					fputc(arbre[i][j], fichierto);
					//printf("J'ai mi l'octet de valeur %d dans le fichier (arbre)\n", arbre[i][j]);
				}
			}
			fputc(255, fichierto);
			//printf("J'ai mi l'octet de valeur %d dans le fichier (arbre)\n\n\n", 255);
		}
	}
}
