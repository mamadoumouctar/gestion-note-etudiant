#include <stdio.h>
#include <stdlib.h>
#include "lib/classes/helper.h"
#include "lib/etudiants/helper.h"

int clavier = 0;

void clear();
void gestion_etudiants();
void gestion_classes();

int main(int argc, char const *argv[])
{
	printf("Application de gestion d'etudiant.\n");

	printf("1. Gestion d'etudiant.\n");
	printf("2. Gestion de classe.\n");

	printf(": ");
	scanf("%d", &clavier);
	fflush(stdin);

	clear();
	switch(clavier){
		case 1:
		gestion_etudiants();
		break;
		case 2:
		gestion_classes();
		break;
		default:
		printf("L'option saisie n'est pas disponible.\n");
	}

	return 0;
}

void gestion_etudiants()
{
	printf("1. Afficher tout les etudiants.\n");
	printf("2. Ajouter un etudiant.\n");

	printf(" : ");
	scanf("%d", &clavier);
	fflush(stdin);

	switch(clavier){
		case 1:
		view_etudiants();
		break;
		case 2:
		add_etudiant();
		break;
		default:
		printf("L'option saisie n'est pas disponible");
		exit(1);
	}
}

void gestion_classes()
{
	printf("\n***Gestion des classes***\n\n");
	printf("1. Afficher toute les classes.\n");
	printf("2. Ajouter une classe.\n");
	printf("3. Modifier une classe.\n");
	printf("4. Supprimer une classe.\n");

	printf(": ");
	scanf("%d", &clavier);
	fflush(stdin);

	clear();
	switch(clavier){
		case 1:
		view_classes();
		break;
		case 2:
		add_classe();
		break;
		case 3:
		update_classe();
		break;
		case 4:
		delate_classe();
		break;
		default:
		printf("L'option saisie n'est pas disponible");
		exit(1);
	}
}

void clear()
{
	system("cls");
}
