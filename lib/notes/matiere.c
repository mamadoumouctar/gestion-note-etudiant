#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"
#include "../etudiants/etudiant.h"
#include "../matieres/matiere.h"
#include "note.h"

char chaine[31];
unsigned int entier = 0;

void matiere_note_index()
{
	unsigned int entier = 0;
	unsigned int controller = 0, action = 0;

	printf("Entrer le nom de la matiere : ");
	GRAB_PREVENT_FIND_NULL:
	scanf("%s", chaine);
	fflush(stdin);
	Matiere find = get_one_matiere_with(chaine);

	if(!strcmp(chaine, "0")) return;

	if(find.reference == 0){
		printf("Desole cette matiere n'existe. Entrer le nom de la matiere ou 0 pour retourner : ");
		goto GRAB_PREVENT_FIND_NULL;
	}

	printf("\n");
	print_matiere(find);

	printf("1. Afficher les notes.\n");
	printf("2. Ajouter les notes.\n");
	printf("3. Modifier les notes.\n");
	printf("4. Supprimer les notes.\n");

	printf("Votre choix : ");
	scanf("%d", &controller);
	fflush(stdin);
	switch(controller){
		case 1: case 2: case 3: case 4:
		break;
		default:
		printf("L'option saisie n'est pas disponible.\n");
		exit(EXIT_FAILURE);
	}

	printf("1. Pour un etudiant.\n");
	printf("2. Pour une classe.\n");

	printf("Votre choix : ");
	scanf("%d", &action);
	fflush(stdin);

	if(action != 1 && action != 2){
		printf("L'option saisie n'est pas disponible.\n");
		exit(EXIT_FAILURE);
	}

	call_controller(find, controller, action);
}

void call_controller(Matiere mat, unsigned int controller, unsigned int action)
{
	unsigned int entier = 0;
	char chaine[31];

	if(action == 1){
		printf("Entrer l'email de l'etudiant : ");
		GRAB_IN_CONTROLLER_1:
		scanf("%[a-zA-Z0-9@.]", chaine);
		fflush(stdin);

		if(!strcmp(chaine, "0")) return;

		Etudiant find = find_etudiant_with_email(chaine);

		if(find.numero == 0){
			printf("Desole il n'existe pas d'etudiant avec cet email. Entrer l'email : ");
			goto GRAB_IN_CONTROLLER_1;
		}else{
			if(!matiere_seFaire(find.code_classe, mat.reference)){
				printf("Desole cette matiere ne se fait pas dans la classe de l'etudiant saisie. Entrer l'email ou 0 pour retourner : ");
				goto GRAB_IN_CONTROLLER_1;
			}
		}
		print_etudiant(find);
		call_controller_item(find, mat,controller);
	}else if(action == 2){
		printf("Entrer le nom de la classe : ");
		GRAB_IN_CONTROLLER_2:
		scanf("%[a-zA-Z0-9 ]", chaine);
		fflush(stdin);

		if(!strcmp(chaine, "0")) return;

		Classe find = find_classe_with_nom(chaine);
		if(find.code == 0){
			printf("Desole cette classe n'existe pas. Entrer le nom : ");
			goto GRAB_IN_CONTROLLER_2;
		}else{
			if(!matiere_seFaire(find.code, mat.reference)){
				printf("Desole cette matiere ne se fait pas dans cette classe.\n");
				printf("\n");

				printf("Voulez vous la rajouter[O/n] : ");
				scanf("%c", &entier);
				fflush(stdin);
				if(entier == 'O' || entier == 'o'){
					//On rajoute la matiere a la classe
					Faire f = {mat.reference, find.code};
					update_sefaire(f, 0);
				}
			}
		}
		print_classe(find);
	}else{
		printf("C'est sorcier ou quoi ?\n");
		exit(EXIT_FAILURE);
	}
}

void call_controller_item(Etudiant et, Matiere mat, unsigned int controller)
{
	switch (controller){
		//Afficher les notes
		case 1:
		print_note_etudiant_matiere(et, mat);
		break;
		//Ajouter les notes
		case 2:
		break;
		//Modifier les notes
		case 3:
		break;
		//Supprimer les notes
		case 4:
		break;
		default: 
		printf("C'est sorcier ou quoi\n");
		exit(EXIT_FAILURE);
	}
}

unsigned int matiere_seFaire(unsigned int code_classe, unsigned int reference_matiere)
{
	Faire f = {0, 0};
	FILE *file = fopen("./data/sefaire.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%d\n", &f.id_matiere, &f.id_classe);
		if(f.id_classe == code_classe && f.id_matiere == reference_matiere)
			return 1;
	}while(!feof(file));
	fclose(file);
	return 0;
}

/**
* Fonction qui permet de modifier le fichier sefaire.csv
* op = 0 insertion
* op = 1 modification
* op = 2 suppression
*/
void update_sefaire(Faire update, unsigned int op)
{
	Faire bin = {0, 0};
	if(op == 0){
		FILE *file = fopen("./data/sefaire.csv", "a");
		if(file == NULL){
			printf("L'ouverture du fichier a echoue\n");
			exit(EXIT_FAILURE);
		}
		fprintf(file, "%d,%d\n", update.id_matiere, update.id_classe);
		fclose(file);
		return;
	}else{
		FILE *file = fopen("./data/sefaire.csv", "r"), *tmp = fopen("./data/tmp.csv", "a");
		if(file == NULL){
			printf("L'ouverture du fichier a echoue\n");
			exit(EXIT_FAILURE);
		}
		do{
			fscanf(file, "%d,%d\n", &bin.id_matiere, &bin.id_classe);
			if(bin.id_matiere == update.id_matiere && bin.id_classe == update.id_classe){
				if(op == 1)
					fprintf(tmp, "%d,%d\n", update.id_matiere, update.id_classe);
			}else{
				fprintf(tmp, "%d,%d\n", bin.id_matiere, bin.id_classe);
			}
		}while(!feof(file));
		fclose(file);
		fclose(tmp);
	}
}
