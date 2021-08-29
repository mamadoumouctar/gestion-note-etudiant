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

void edit_matiere()
{
	printf("***Modification d'une matiere***\n");
	unsigned short int entier = 0, bad = 0;
	char chaine[16];

	printf("Entrer le libelle de la matiere a modifier : ");
	GRAB_LIBELLE_EDIT:
	scanf("%[a-zA-Z0-9 ]", chaine);
	fflush(stdin);

	if(strcmp(chaine, "0") == 0)
		return;

	Matiere find = get_one_matiere_with(chaine);

	if(find.reference != 0){
		print_matiere(find);
	}else{
		printf("Cet libelle n'existe pas. Entrer un libelle svp ou 0 pour retourner : ");
		goto GRAB_LIBELLE_EDIT;
	}

	//Saisi du libelle
	printf("Entrer le nouveau libelle ou 0 pour ne pas modifier : ");
	GRAB_LIBELLE_EDIT_NEW:
	scanf("%[a-zA-Z0-9 ]", chaine);
	fflush(stdin);

	if(strcmp(chaine, "0") != 0){
		if(strlen(chaine) < 3){
			printf("Incorrect le libelle doit avoir plus que 3 carractere. Entrer le libelle : ");
			goto GRAB_LIBELLE_EDIT_NEW;
		}
		strcpy(find.libelle, chaine);
	}

	//Saisi du coefficient
	printf("Entrer le coefficient ou 0 pour ne pas modifier : ");
	GRAB_COEFICCIENT_EDIT_NEW:
	bad = scanf("%d", &entier);
	fflush(stdin);

	if(entier != 0 && bad == 1){
		find.coefficient = entier;
	}else{	
		if(entier != 0 || bad != 1){
			printf("Incorrect ceci n'est pas un coefficient. Entrer le coefficient : ");
			goto GRAB_COEFICCIENT_EDIT_NEW;
		}
	}

	print_matiere(find);
	update_matiere(find, 1);
}

void delate_matiere()
{
	printf("***Modification d'une matiere***\n");
	unsigned int entier = 0, bad = 0;
	char chaine[31];


	printf("Entrer le libelle de la matiere a Supprimer : ");
	GRAB_LIBELLET_MATIERE_DELATE:
	scanf("%s", chaine);
	fflush(stdin);

	if(strcmp(chaine, "0") == 0) return;

	Matiere find = get_one_matiere_with(chaine);

	if(find.reference != 0){
		print_matiere(find);
		printf("Etes vous sure de bien vouloir supprimer cette matiere [o/N]? ");
	}else{
		printf("Cet libelle n'existe pas. Entrer un libelle svp ou 0 pour retourner : ");
		goto GRAB_LIBELLET_MATIERE_DELATE;
	}

	scanf("%s", chaine);
	if(strcmp(chaine, "o") == 0 || strcmp(chaine, "O") == 0){
		update_matiere(find, 0);
		printf("\nLa matiere a ete supprimer avec succes.\n");
	}else{
		printf("\nLa matiere n'a pas ete supprimer.\n");
	}
}
