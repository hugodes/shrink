//modifie le tableau tabproba pour contenir la distribustion probabilistique de chaque caractère
//ainsi que le nombre total de caratères
int distriproba(FILE *fichier, int *tabproba)
{
    int c, i;
    
    //rempli le tableau avec les distributions probabilistes
    for(i=0; (c = fgetc(fichier)) != EOF; i++)
        ++tabproba[c];
    return i;
}
