#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"

void print_matiere(Matiere mat)
{
	printf("+-----------------------------------------------+\n");
	printf("|\tReference : %d\t\t\t\t|\n", mat.reference);
	printf("+-----------------------------------------------+\n");
	printf("|\tLibelle : %-15s\t\t|\n", mat.libelle);
	printf("+-----------------------------------------------+\n");
	printf("|\tCoefficient : %d\t\t\t\t|\n", mat.coefficient);
	printf("+-----------------------------------------------+\n");
}

int get_last_reference_matiere()
{
	FILE *file = fopen("./data/matieres.csv", "r");
	Matiere mat;

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%[a-zA-Z0-9 ],%d", &mat.reference, mat.libelle, &mat.coefficient);
	}while(!feof(file));

	fclose(file);
	return mat.reference;
}

void save_matiere(Matiere mat)
{
	FILE *file = fopen("./data/matieres.csv", "a");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	mat.reference = get_last_reference_matiere() + 1;
	print_matiere(mat);

	fprintf(file, "%d,%s,%d\n", mat.reference, mat.libelle, mat.coefficient);
	fclose(file);
}
