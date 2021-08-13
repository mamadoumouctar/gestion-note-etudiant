#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"

void view_matiere()
{
	printf("***Liste de toute les matiers***\n");
	FILE *file = fopen("./data/matieres.csv", "r");

	Matiere mat;

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}
	do{
		fscanf(file, "%d,%[a-zA-Z ],%d\n", &mat.reference, mat.libelle, &mat.coefficient);
		print_matiere(mat);
	}while(!feof(file));
	fclose(file);
}
