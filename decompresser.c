//cette fonction (de genie) decompresse à elle seule le fichier
//(avaec l'aide de l'arbre reconstitué et de nbchar obtenu grave au codage sur 4 octets :)
void decompresser(FILE *fichierfrom, FILE *fichierto, int ** arbre) {

	//printf("Dans decompresser:\n");
	extern int nbchar, nbligne;
	int c, get;
	int bin[9];
	int indracine, needbin=1, charcount=0, inddansarbre;
	int ind;
	indracine=nbligne-1;
	//printf("indice racine = %d\n", nbligne);

	//printf("valeur ===== %d\n", arbre[0][1]);
	
	//cette boucle while prend un a un les cacteres du fichier codé
	//(post-header) à nous de les convertirs
	//a nous de les reconvertirs....
	charcount=0;
	inddansarbre=indracine;
	//printf("\tles variables sont initialisées\n");
	while (charcount<nbchar) {
		//printf("Charcount = %d\n", charcount);
		//needbin dit au programme d'aller chercher un autre octet dans le fichier
		if (needbin==1) {
			get=fgetc(fichierfrom);
			//printf("\nJe suis allé chercher l'octet de valeur decimale: %d dans le fichier\n\n", get);
			inttobin(get, bin, 8);
			bin[8]=0;
			needbin = 0;
			//printf("\t\tfonction needbin réussie!\n");
		}
		ind=bin[8];
		//ici on regarde si on est en train de lire le dernier bit de l'ocotet
		//pour indiquer au programme qu'il devra chercher un nouvel octet à la 
		//reitération de la boucle
		//printf("N°%d = ", ind);
		//printf("%d---->\t", bin[bin[8]]);
		//printf("valeur de l'indice courant:%d\n", arbre[0][inddansarbre]);
		if (bin[8]>=7) {
			//printf("Je rentre dans la 1ere boucle\n");
			//ci on se trouve sur une feuille, on met son charactere correspondant
			//dans le fichier sortie
			if (arbre[1][inddansarbre] == 254 && arbre[2][inddansarbre] == 254) {
				c=arbre[0][inddansarbre];
				//printf("L'indice %d est une feuille %d\n", inddansarbre, c);
				//printf("Fini de mettre le char de valeur : %d dans le fichier\n", c);
				fputc(c, fichierto);
				inddansarbre=indracine;
				charcount++;
			}
			//sisnon on se place sur le prochain neoud de l'arbre
			//0 pour fils gauche
			//1 pour fils droit
			else  {
				if (bin[bin[8]] == 0) {
					//printf("\tL'indice %d est un noeud, alons vers le fils gauche\n", inddansarbre);
					inddansarbre=arbre[1][inddansarbre];
				}
				else if (bin[bin[8]] == 1) {
					//printf("\tL'indice %d est un noeud, alons vers le fils droit\n", inddansarbre);
					inddansarbre=arbre[2][inddansarbre];
				}
				needbin=1;
			}
		}
		//On ne se trouve pas sur le dernier bit de l'octet
		else if (bin[8]>=0) {
			//si on est sur une feuille on met le character correspondant dans 
			//le fichier sortie et son se place sur le prochain bit.
			if (arbre[1][inddansarbre] == 254 && arbre[2][inddansarbre] == 254) {
				//printf("\t\t\tJe suis tombé sur une feuille!\n");
				c=arbre[0][inddansarbre];
				//printf("L'indice %d est une feuille %d\n", inddansarbre, c);
				//printf("\t\t\tLe char n°%d trouvé est:  %d\n", charcount, c);
				//printf("Fini de mettre le char de valuer : %d dans le fichier\n", c);
				//printf("J'inspecte l'octet n° %d\n", bin[8]);
				fputc(c, fichierto);
				inddansarbre=indracine;
				//printf("\t\t\tFini de traiter la feuille\n");
				charcount++;
			}

			//si le noeud actuel n'est pas une feuille on va dans le noeud fils:
			//0 pour fils gauche
			//1 pour fd
			//on se place ensuite sur le prochain bit
			else if (bin[bin[8]] == 1) {
				//printf("\tL'indice %d est un noeud, alons vers le fils droit\n", inddansarbre);
				inddansarbre=arbre[2][inddansarbre];
				//printf("\t\tJe ne suis pas sur une feuille\n");
				bin[8]++;
			}
			else if (bin[bin[8]] == 0) {
				//printf("\tL'indice %d est un noeud, alons vers le fils gauche\n", inddansarbre);
				inddansarbre=arbre[1][inddansarbre];
				//printf("\t\tJe ne suis pas sur une feuille\n");
				bin[8]++;
			}
		}
	}
	//printncol(arbre, indracine+1, 4);
}
