#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.h"
#include "matiere.h"
#include "note.h"
#include "../classes/classe.h"
#include "../etudiants/etudiant.h"

void etudiant_note_index()
{
	char chaine[31];
	unsigned int entier = 0;
	printf("Entrer l'email de l'etudiant : ");
	GRAB_ET_NOTE_NOTE:
	scanf("%s",chaine);
	fflush(stdin);

	if(!strcmp(chaine, "0")) return;

	Etudiant find = find_etudiant_with_email(chaine);
	if(find.numero == 0){
		printf("Incorrect cet email n'existe pas. Entrer l'email ou 0 pour retourner : ");
		goto GRAB_ET_NOTE_NOTE;
	}
	print_etudiant(find);
	printf("\n");

	printf("1. Afficher toute les notes de l'etudiant dans toute ses matieres.\n");
	printf("2. Ajouter toute les notes de l'etudiant qui n'ont pas ete renseigner.\n");

	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	switch(entier){
		case 1:
		show_all_note_etudiant(find);
		break;
		case 2:
		add_all_note_etudiant(find);
		break;
		default:
		printf("L'option saisie n'est pas disponible.\n");
		exit(EXIT_FAILURE);
	}
}

void show_all_note_etudiant(Etudiant et)
{
	printf("\n");
	printf("\n");
	printf("+--------------------------------------------------------------------------------------------------+\n");
	printf("| Prenom et Nom : %20s %-30s                              |\n", et.prenom, et.nom);
	printf("| Email : %-20s                                                                     |\n", et.email);
	printf("| Date de naissance : ");
	if(et.naissance.jj < 10)
		printf(" 0%1d/", et.naissance.jj);
	else
		printf(" %2d/", et.naissance.jj);

	if(et.naissance.mm < 10)
		printf("0%1d/", et.naissance.mm);
	else
		printf("%2d/", et.naissance.mm);

	printf("%4d                                                                  |\n", et.naissance.aaaa);
	printf("+--------------------------------------------------------------------------------------------------+\n");

	printf("+--------------------------------------+---------+---------+---------+-------------+---------------+\n");
	goto_classe_find_note(et);
}

void add_all_note_etudiant(Etudiant et)
{
	Faire f = {0, 0};
	Matiere mat;
	Note note;
	note.id_etudiant = et.numero;
	unsigned int bad = 1, update_or_create = 0;
	FILE *file = fopen("./data/sefaire.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%d\n", &f.id_matiere, &f.id_classe);
		if(et.code_classe == f.id_classe){
			mat = find_matiere(f.id_matiere);
			Note find = find_note(et, mat);
			note.id_matiere = mat.reference;
			update_or_create = 0;

			if(find.note_cc == 0 | find.note_ds == 0)
				print_matiere(mat);
			
			//Saisie de la note de cc
			if(find.note_cc == 0){
				printf("Entrer la note de CC : ");
				GRAB_NOT_ALL_CC:
				bad = scanf("%f", &note.note_cc);
				fflush(stdin);

				if(note.note_cc <= 0 || note.note_cc > 20) bad = 0;

				if(bad == 0){
					printf("Incorrect la note CC est comprise entre 0 et 20. Entrer la note de CC : ");
					goto GRAB_NOT_ALL_CC;
				}
			}else{
				note.note_cc = find.note_cc;
				update_or_create = 1;
			}

			//Saisie de la note de ds
			if(find.note_ds == 0){
				printf("Entrer la note de DS : ");
				GRAB_NOT_ALL_DS:
				bad = scanf("%f", &note.note_ds);
				fflush(stdin);

				if(note.note_ds <= 0 || note.note_ds > 20) bad = 0;

				if(bad == 0){
					printf("Incorrect la note DS est comprise entre 0 et 20. Entrer la note de CC : ");
					goto GRAB_NOT_ALL_DS;
				}
			}else{
				note.note_ds = find.note_ds;
				update_or_create = 1;
			}

			if(update_or_create)
				update_note(note, 1);
			else
				save_note(note);
		}
	}while(!feof(file));
	fclose(file);
}

void goto_classe_find_note(Etudiant et)
{
	Faire f = {0, 0};
	Matiere mat;
	Note note;
	unsigned int coefs = 0;
	float moyenne, moyennes;
	FILE *file = fopen("./data/sefaire.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}
	printf("|  Libellet de la matiere              | Note CC | Note DS | Moyenne | Coefficient | Apprecitation |\n");
	printf("+--------------------------------------+---------+---------+---------+-------------+---------------+\n");
	do{
		fscanf(file, "%d,%d\n", &f.id_matiere, &f.id_classe);
		if(et.code_classe == f.id_classe){
			note = find_note_with_primary(et.numero, f.id_matiere);
			mat = find_matiere(f.id_matiere);
			moyenne = (note.note_cc + note.note_ds) / 2;
			moyennes += moyenne * mat.coefficient;
			coefs += mat.coefficient;
			printf("| %-35s  |", mat.libelle);
			if(note.note_cc < 10)
				printf("   %1.2f  |", note.note_cc);
			else
				printf("  %2.2f  |", note.note_cc);
			if(note.note_ds < 10)
				printf("   %1.2f  |", note.note_ds);
			else
				printf("  %2.2f  |", note.note_ds);
			if(moyenne < 10)
				printf("   %1.2f  |", moyenne);
			else
				printf("  %2.2f  |", moyenne);
			printf("    %d        | %-13s |\n", mat.coefficient, get_appreciation(moyenne));
			printf("+--------------------------------------+---------+---------+---------+-------------+---------------+\n");
		}
	}while(!feof(file));
	printf("Moyenne : %f\n", moyennes);
	printf("coefs %d\n", coefs);
	fclose(file);
}

char *get_appreciation(unsigned int moyenne)
{
	if(moyenne < 10)
		return "Insuffisant";
	if(moyenne < 12)
		return "Passable";
	if(moyenne < 14)
		return "Assez Bien";
	if(moyenne < 16)
		return "Bien";
	if(moyenne < 18)
		return "Tres Bien";
	if(moyenne <= 20)
		return "Excellent";
}
