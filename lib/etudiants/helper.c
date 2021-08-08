#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include "etudiant.h"

void view_etudiants()
{
	printf("***Liste de tout les etudiants***\n");
	Etudiant et;
	FILE *file = fopen("./data/etudiants.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}
	do{
		fscanf(file, "%d ,%s ,%s ,%s ,%d/%d/%d\n", &et.numero, et.nom, et.prenom, et.email, &et.naissance.jj, &et.naissance.mm, &et.naissance.aaaa);
		print_etudiant(et);
	}while(!feof(file));
	fclose(file);
}

void add_etudiant()
{
	
}
