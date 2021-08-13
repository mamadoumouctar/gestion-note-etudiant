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

void add_matiere()
{
	printf("***Ajout d'une nouvelle matiere***\n");

	FILE *file = fopen("./data/matieres.csv", "a");
	
	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	Matiere mat;
	char chaine[16];
	unsigned short int entier = 0, bad = 0;

	printf("Entrer le libelle de la matiere : ");
	GRAB_LIBELLE_ADD:
	scanf("%[a-zA-Z0-9 ]", chaine);
	fflush(stdin);

	if(strlen(chaine) < 3){
		printf("Incorrect le libelle doit avoir plus que 3 carractere. Entrer le libelle : ");
		goto GRAB_LIBELLE_ADD;
	}
	strcpy(mat.libelle, chaine);

	printf("Entrer le coefficient de la matiere : ");
	GRAB_COEFICCIENT_ADD:
	bad = scanf("%d", &entier);
	fflush(stdin);

	if(bad != 1){
		printf("Incorrect le coefficient doit etre un entier. Entrer le coefficient : ");
		goto GRAB_COEFICCIENT_ADD;
	}
	mat.coefficient = entier;

	save_matiere(mat);
}
