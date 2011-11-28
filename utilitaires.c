int power(int x, int n) {
	if (n==0) {
		return 1;
	}
	else {
		return x*power(x, (n-1));
	}
	return 1;
}
//initialise tout les elements à 0
void inittab(int *tab, int lim) {
    int i;
    for (i=0; i<lim; i++)
        tab[i]=0;
}

//imprime le contenue d'un tableau d'entiers
void printinttab(int *tab, int lim) {
    int i;
    
    for (i=0; i<lim; i++)
        printf("Element num: %6d --> %d\n", i, tab[i]);
}


void printncol(int **tab, int ligne, int col)
{
    int i, j;
    printf("columns: %d\n rows: %d\n", col, ligne);
    for (i=0; i<ligne; i++) {
        for (j=0; j<=col; j++) {
		if (j<col) {
            		printf("%7d", tab[j][i]);
		}
		else {
			printf("%4d", i);
		}
        }
        printf("\n");
    }
}
//remonte l'abre et stoke le code huffamn de chaque caractere à l'envers
void remonterarbre(int inddec, int **arbre, int *bin, int compteur)
{
	//printf("On est situé à l'indice %d\n", inddec);
	extern int racine;
	int indperedec = arbre[4][inddec];
	int indfgpere = arbre[2][indperedec];
	int indfdpere = arbre[3][indperedec];
	if (inddec >= racine-1) {
		bin[compteur] = 513;
		//printf("On est tombé sur la racine à l'indice %d\n", inddec);
		//printf("Fini la conversion en binaire\n");
		//printinttab(bin, compteur);
		//printf("Compteur = %d\n", compteur);
	}
	else if (inddec == indfgpere) {
		//printf("On est a l'indice %d on monte a l'indice %d\nOn met 0\n", inddec, indfgpere);
		bin[compteur++] = 0;
		//printf("Compteur = %d\n", compteur);
		remonterarbre(indperedec, arbre, bin, compteur);
	}	
	else if (inddec == indfdpere) {
		//printf("On est a l'indice %d on monte a l'indice %d\nOn met 1\n", inddec, indfdpere);
		bin[compteur++] = 1;
		//printf("Compteur = %d\n", compteur);
		remonterarbre(indperedec, arbre, bin, compteur);
	}
}
//simple fonction permettant d'inverser une ligne de charactères
void inverserligne(int *tab)
{
	//printf("On va inverser la ligne\n");
	int temp[100];
	int i, j=0, k;
	for (i=0; tab[i+1] != 513; i++)
		;
	//printf("Il y a %d elements a inverer\n", i+1);
	for(k=i; k>=0; k--) {
		temp[j++] = tab[k];
	}
	temp[j] = 513;
	//printinttab(temp, 10);
	for(k=0; k<=i; k++) {
		tab[k]=temp[k];
	}
}

//Pour cette conversion, j'utilise l'alogo de horner vu en TP2 GLIN302 (scheme)
int bintoint(int *bin, int ind, int nb)
{
	if (ind == 0) {
		return bin[bin[nb]-1];
	}
	else {
		return bin[--bin[nb]] + 2*bintoint(bin, (ind-1), nb);
	}
}
int bintoint2(int *bin, int size) {
	int i, count=0;
	int res;
	res=0;
	for (i=size-1; i>=0; i--) {
		//printf("bin[%d] = %d\n", i, bin[i]);
		//printf("2 power %d = %d\n", count, power(2, count));
		res=res+bin[i]*power(2, count);
		count++;
	}
	//printf("res= %d\n", res);
	return res;
}

//cette fonction convertit un entier en une chaine de 0 1 correspondant à
//son codage binaire
//1er argument: l'entier a coder
//2eme arg: un tableau de taille n pour contenir le codage binaire
//3eme arg: la taille du tableau
void inttobin(int d, int *tab, int nbbit) {
	//printf("j'arive ici");
	int i, div=d;
	//printf("div = %d\n", div);
	for (i=(nbbit-1); i>=0; i--) {
		//printf("je entre dans la boucle\n");
	      	tab[i]=div%2;
	      	//printf("%d", tab[i]);
	      	div=div/2;
	}
	//printf("\n");
}

void freearbre(int **arbre, int nbcol) {
	for(int i=0; i<nbcol; i++) {
		free(arbre[i]);
	}
}

void make58(int *tab) {
	tab[0]=1;
	tab[1]=0;
	tab[2]=0;
	tab[3]=0;
	tab[4]=0;
	tab[5]=0;
	tab[6]=0;
	tab[7]=1;
	tab[8]=8;
}
void intsur4oct(int d, int *tab) {
	int i, j, k, crit=0;
	int tempd=d;
	//printf("tempd = %d\n", tempd);
	int temptab[33];
	temptab[32]=32;
	int temptab2[8];
	for (i=31; i>=0; i--) {
		temptab[i]=tempd%2;
		tempd=tempd/2;
	}
	//printinttab(temptab, 32);
	//printf("nb char = %d\n", bintoint(temptab, 31, 32));
	k=0;
	for (i=0; i<32; i+=8) {
		for(j=0; j<8; j++) {
			temptab2[j]=temptab[i+j];
			//printf("i+j= %d\n", i+j);
			//printf("i=%d \t j=%d\n", i, j);
		}
		//printf("L'arbre numero %d est: \n", k);
		if (k==3) {
			++crit;
		}
		//printinttab(temptab2, 8);
		//printf("\n");
		//printinttab(temptab, 32);
		tab[k]=bintoint2(temptab2, 8);
		//printf("Sa valeur decimale du %deme element est: %d\n", k, tab[k]);
		k++;
	}
}


