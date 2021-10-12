#include <stdio.h>
#include <stdlib.h>
#include "note.h"

void print_note_etudiant_matiere(Etudiant et, Matiere mat)
{
	unsigned int entier = 6;
	printf("Quel note voulez vous afficher ?\n");
	printf("1. Note CC.\n");
	printf("2. Note DS.\n");
	printf("3. Les deux.\n");
	printf("0. Retour.\n");
	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	Note find = find_note(et, mat);

	switch(entier){
		case 1:
		printf("+-----------------------------------------------+\n");
		printf("|\tNumero : %d\t\t\t\t|\n", et.numero);
		printf("+-----------------------------------------------+\n");
		printf("|\tNom : %-30s\t|\n", et.nom);
		printf("+-----------------------------------------------+\n");
		printf("|\tPrenom : %-20s\t\t|\n", et.prenom);
		printf("+-----------------------------------------------+\n");
		printf("|\tEmail : %-20s\t\t|\n", et.email);
		printf("+-----------------------------------------------+\n");
		printf("|\tNaissance :");
		if(et.naissance.jj < 10)
			printf(" 0%1d/", et.naissance.jj);
		else
			printf(" %2d/", et.naissance.jj);

		if(et.naissance.mm < 10)
			printf("0%1d/", et.naissance.mm);
		else
			printf("%2d/", et.naissance.mm);

		printf("%4d", et.naissance.aaaa);
		printf("\t\t\t|\n");
		printf("+-----------------------------------------------+\n");
		printf("|\tNote de CC : %2.2f\t\t\t|\n", find.note_cc);
		printf("+-----------------------------------------------+\n");
		break;
		case 2:
		printf("+-----------------------------------------------+\n");
		printf("|\tNumero : %d\t\t\t\t|\n", et.numero);
		printf("+-----------------------------------------------+\n");
		printf("|\tNom : %-30s\t|\n", et.nom);
		printf("+-----------------------------------------------+\n");
		printf("|\tPrenom : %-20s\t\t|\n", et.prenom);
		printf("+-----------------------------------------------+\n");
		printf("|\tEmail : %-20s\t\t|\n", et.email);
		printf("+-----------------------------------------------+\n");
		printf("|\tNaissance :");
		if(et.naissance.jj < 10)
			printf(" 0%1d/", et.naissance.jj);
		else
			printf(" %2d/", et.naissance.jj);

		if(et.naissance.mm < 10)
			printf("0%1d/", et.naissance.mm);
		else
			printf("%2d/", et.naissance.mm);

		printf("%4d", et.naissance.aaaa);
		printf("\t\t\t|\n");
		printf("+-----------------------------------------------+\n");
		printf("|\tNote de DS : %2.2f\t\t\t|\n", find.note_ds);
		printf("+-----------------------------------------------+\n");
		break;
		case 3:
		printf("+-----------------------------------------------+\n");
		printf("|\tNumero : %d\t\t\t\t|\n", et.numero);
		printf("+-----------------------------------------------+\n");
		printf("|\tNom : %-30s\t|\n", et.nom);
		printf("+-----------------------------------------------+\n");
		printf("|\tPrenom : %-20s\t\t|\n", et.prenom);
		printf("+-----------------------------------------------+\n");
		printf("|\tEmail : %-20s\t\t|\n", et.email);
		printf("+-----------------------------------------------+\n");
		printf("|\tNaissance :");
		if(et.naissance.jj < 10)
			printf(" 0%1d/", et.naissance.jj);
		else
			printf(" %2d/", et.naissance.jj);

		if(et.naissance.mm < 10)
			printf("0%1d/", et.naissance.mm);
		else
			printf("%2d/", et.naissance.mm);

		printf("%4d", et.naissance.aaaa);
		printf("\t\t\t|\n");
		printf("+-----------------------------------------------+\n");
		printf("|\tNote de CC : %2.2f\t\t\t|\n", find.note_cc);
		printf("+-----------------------------------------------+\n");
		printf("|\tNote de DS : %2.2f\t\t\t|\n", find.note_ds);
		printf("+-----------------------------------------------+\n");
		break;
		case 0:
		return;
		default:
		printf("Desole cette option n'est pas pris en charge.\n");
		exit(EXIT_FAILURE);
	}
}

Note find_note(Etudiant et, Matiere mat)
{
	FILE *file = fopen("data/notes.csv", "r");
	Note note, null = {0,0,0.0,0.0};

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%d,%f,%f\n", &note.id_etudiant, &note.id_matiere, &note.note_cc, &note.note_ds);
		if(note.id_etudiant == et.numero && note.id_matiere == mat.reference){
			return note;
		}
	}while(!feof(file));
	fclose(file);
	return null;
}
