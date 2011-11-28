void recupnbchar(FILE *fichierfrom) {
	extern int nbchar;
	int i, j;
	int c;
	int tabbin[33];
	tabbin[32]=32;
	int tabtemp[8];
	//printf("Je recup les 4 premiers octets\n");
	for (i=0; i<4; i++) {
		c=fgetc(fichierfrom);
		//printf("\t1");
		//printf("J'ai recupéré l'octet num %d de valeur %d\n", i+2, c);
		inttobin(c, tabtemp, 8);
		//printf("Le tableau n°%d donne: \n", i);
		//printinttab(tabtemp, 8);
		for (j=0; j<8; j++) {
			tabbin[i*8+j]=tabtemp[j];
			//printf("%d\n", i*8+j);
		}
	}
	//printf("J'ai créé bon tabbin\n");
	//printinttab(tabbin, 32);
	nbchar=bintoint(tabbin, 31, 32);
	//printf("j'ai fini nbchar: %d\n", nbchar);

}
		
		


void rebuildarbre(FILE *fichierfrom, int **arbre) {
	int i, j, c;
	extern int nbligne;
	//On saisi le nombre de caracteres independants
	nbligne = fgetc(fichierfrom);
	//printf("J'ai pris l'octet de valeur %d dans le ficher\n", nbligne);
	//printf("J'ai recup le premier octet de valeur: %d\n", nbligne);
	recupnbchar(fichierfrom);
	for (i=0; i<4; i++) {
		arbre[i]=malloc((2*nbligne-1)*sizeof(int));
	}
	//on popule le tableau, nous savons que les differents caractères 
	//sont codés par les char de valeur 1
	for (i=0; i<4; i++) {
		j=0;
		while((c=fgetc(fichierfrom)) != 255) {
			//printf("J'ai pris l'octet de valeur %d dans le ficher\n", c);
			arbre[i][j]=c;
			j++;
		}
	}
}
	

	
