#include "putheader.h"

void putchuffman(int c, int **arbre, int *bufferget)
{
	extern int racine;
	//indice de c
	int inddec;
	//determinons l'indice de c
	for (inddec = 0; arbre[0][inddec] != c; inddec++) {
		;
	}
	//printf("finin de trouver inddec= %d\n", inddec);
	//printf("racine: %d\n", racine);
	//renvoie le code binaire du caractère concerné (à l'envers)
	remonterarbre(inddec, arbre, bufferget, 0);
	//printinttab(bufferget, 10);
	//printf("Fini de remonter arbre\n");
	
	//comme remonterarbre renvoie le code binaire à l'envers,
	//on le remet à l'endroit
	inverserligne(bufferget);
	//printinttab(bufferget, 10);
	//printf("Fini d'inverser ligne\n");
	/*printf("La longeur du code binaire de ce char est: ");
	for (i=0; bin[i] < 513; i++) {
		;
	}
	printf("%d\n", i);*/
	//putbincode(fichierto, bin);
	//printf("Fini de mettre le code binaire\n");
	//
}

void finalflush(int *bufferput, FILE *fichierto)
{
	int c;
	for (int i=bufferput[8]; i < 8; i++) {
		bufferput[i] = 0;
		bufferput[8]++;
	}
	c=bintoint(bufferput, 7, 8);
	//printf("J'ai mi le dernier octet de valeur %d dans le fichier\n", c);
	fputc(c, fichierto);
}

void bufferinit(int *buffer, int lim)
{
	for (int i=0; i < lim; i++) {
		buffer[i] = 513;
	}
}

void passandflush(int *bufferget, int *bufferput, FILE *fichierto) 
{
	int i=0, c;
	int bin, ind;
	while((bin = bufferget[i]) != 513) {
		ind = bufferput[8];
		if (ind == 8) {
			c=bintoint(bufferput, 7, 8);
			fputc(c, fichierto);
			//printf("J'ai mi l'octet de valeur decimale :%d dans le fichier\n", c);
			bufferput[0]=bufferget[i];
			bufferput[8]=1;
			++i;
		}
		else {
			bufferput[ind] = bin;
			++bufferput[8];
			++i;
		}
	}
}
//creé le fichier compressé (avec des 0 et des 1) a partir du fichier orginal 
//et de l'arbre. Chaque valeur des rempalcée par sa valeur binaire
//à gauche 0 et à droite 1
void creerfichcomp(FILE *fichierfrom, FILE *fichierto, int **arbre, FILE *fichiercount)
{
	//printf("On rentre dans la fonction creerfichcomp\n");
	//mettre les informations relatives au codage en en-tête du fichier
	putheader(fichierto, arbre, fichiercount);
	//Ici, on prend code chaque caractere grave a l'abre de huffman.
	//On fait correspondre des packets de 8 bit à des caractère car
	//on ne peut pas output des bits.
	//tant qu'il reste des caractères à encoder, on insere le code binaire
	//bit par bit dans un buffer de 8bit.
	//Qaund le buffer est plein, on convertit l'ecriture binaire en un 
	//entier.
	//On met ensuite dans le fichier compréssé un char qui a pour code ASCII
	//l'entier que l'on vien de calculer 
	int c;
	//End est à 0 si il reste des chars à encoder, 1 sinon.
	int end=0;
	int bufferget[100];
	//bufferput contient 9 entier, les 8 premiers seront des binaires 
	//representant un char, le 9ème serra le l'indice de la premiere case
	//non populée
	int bufferput[9];
	bufferput[8]=0;
	while (end == 0) {
		if ((c = fgetc(fichierfrom)) == EOF) {
			//final flush rajoute des 0 à droite du bufferput
			//et le flush dans le fichier.
			//printf("On va comencer le final flush\n");
			finalflush(bufferput, fichierto);
			//printf("Fini, j'ai flushé\n");
			//printf("On a fini final flush\n");
			end++;
		}
		else { 
			//printf("\tJe veux mettre %c dans le fichier\n", c);
			bufferinit(bufferget, 100);
			//printf("Fini buffer init\n");
			putchuffman(c, arbre, bufferget);
			//printf("Fini putchuffman\n");
			//cette fonction permet de passer un à un les elements
			//d'un buffer dans un deuxième buffer j'usqu'a que le 
			//deuxieme soit plein, ensuite il flush le deuxieme 
			//et se repete j'usqu'a qu'il n'y ai plus d'elements 
			//dans le premier buffer.
			passandflush(bufferget, bufferput, fichierto);
			//printf("Fini passandflush\n");
		}
	}

}

