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

/**
 * Fonction qui permet de supprimer ou de modifier un etudiant
 * si edit_or_delate est 0 on supprime
 * si edit_or_delate est 1 on modifie
*/
void update_matiere(Matiere update, unsigned short int edit_or_update)
{
	FILE *file = NULL, *tmp = NULL;
	Matiere mat;

	file = fopen("./data/matieres.csv", "r");
	tmp  = fopen("./data/tmp.csv", "a");

	if(file == NULL || tmp == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%[a-zA-Z0-9 ],%d\n", &mat.reference, mat.libelle, &mat.coefficient);

		if(update.reference == mat.reference){
			if(edit_or_update)
				fprintf(tmp, "%d,%s,%d\n", update.reference, update.libelle, update.coefficient);
		}else{
			fprintf(tmp, "%d,%s,%d\n", mat.reference, mat.libelle, mat.coefficient);
		}
	}while(!feof(file));

	fclose(file);
	fclose(tmp);

	remove("./data/matieres.csv");
	rename("./data/tmp.csv", "./data/matieres.csv");
}

unsigned int get_nomber_of_matiere_with(char * libelle)
{
	FILE *file = fopen("./data/matieres.csv", "r");
	Matiere mat;
	unsigned int index = 0;

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%[a-zA-Z0-9 ],%d\n", &mat.reference, mat.libelle, &mat.coefficient);
		if(strcmp(libelle, mat.libelle) == 0){
			index++;
		}
	}while(!feof(file));

	fclose(file);

	return index;
}

void find_matieres(char *libelle, Matiere *matieres)
{
	FILE *file = fopen("./data/matieres.csv", "r");
	Matiere mat;
	unsigned int index = 0;

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%[a-zA-Z0-9 ],%d\n", &mat.reference, mat.libelle, &mat.coefficient);
		if(strcmp(libelle, mat.libelle) == 0){
			matieres[index] = mat;
			index++;
		}
	}while(!feof(file));
	fclose(file);
}

Matiere get_one_matiere_with(char *libelle)
{
	Matiere *matieres, mat, null = {0, "",0};
	unsigned int index, entier = 0;

	index = get_nomber_of_matiere_with(libelle);
	matieres = malloc(sizeof(Matiere) * index);

	find_matieres(libelle, matieres);

	if(index == 1)
		return matieres[0];
	else if(index == 0){
		Matiere null = {0, "", 0};
		return null;
	}

	printf("+----+---------------+------------------------+-----------------+\n");
	printf("| N  |   Reference   |        Libelle         |   Coefficient   |\n");
	printf("+----+---------------+------------------------+-----------------+\n");
	for(int i = 0; i < index; i++){
		printf("| %2d |      %3d      |  %-15s       |        %2d       |\n", i+1, matieres[i].reference, matieres[i].libelle, matieres[i].coefficient);
		printf("+----+---------------+------------------------+-----------------+\n");
	}

	printf("Entrer le N que vous avez choisi : ");
	GRAB_MATIERE_ONCE:
	scanf("%d", &entier);
	fflush(stdin);

	if(entier > 0 && entier <= index){
		mat = matieres[entier-1];
		free(matieres);
		return mat;
	}else{
		printf("Incorrect ce choix n'est pas disponible. Entrer le N : ");
		goto GRAB_MATIERE_ONCE;
	}
}

void find_matieres_and_print(char *libelle)
{
	FILE *file = fopen("./data/matieres.csv", "r");
	unsigned short int nomber = 0;
	Matiere mat;

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%[a-zA-Z0-9 ],%d\n", &mat.reference, mat.libelle, &mat.coefficient);
		if(strcmp(libelle, mat.libelle) == 0){
			nomber = 1;
			printf("|    %3d      |  %-16s|  %3d          |\n", mat.reference, mat.libelle, mat.coefficient);
			printf("+-------------+------------------+---------------+\n");
		}
	}while(!feof(file));
	fclose(file);
	if(nomber == 0){
		printf("|  Desole cet libelle n'existe pas...            |\n");
		printf("+------------------------------------------------+\n");
	}
}
