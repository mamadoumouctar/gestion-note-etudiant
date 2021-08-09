#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "etudiant.h"

Etudiant new_etudiant(
	unsigned int numero, char nom[31], char prenom[21], char email[21], Date naissance
	)
{
	Etudiant et;
	et.numero = numero;
	strcpy(et.nom, nom);
	strcpy(et.prenom, prenom);
	strcpy(et.email, email);
	et.naissance.jj = naissance.jj;
	et.naissance.mm = naissance.mm;
	et.naissance.aaaa = naissance.aaaa;
	return et;
}

Date new_date(unsigned short int jj, unsigned short int mm, unsigned int aaaa)
{
	Date date;
	date.jj = jj;
	date.mm = mm;
	date.aaaa = aaaa;
	return date;
}

int get_last_numero_etudiant()
{
	Etudiant et;
	FILE *file = fopen("./data/etudiants.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%[a-zA-Z ],%[a-zA-Z ],%[a-zA-Z@.],%d/%d/%d\n", &et.numero, et.nom, et.prenom, et.email, &et.naissance.jj, &et.naissance.mm, &et.naissance.aaaa);
	}while(!feof(file));
	fclose(file);
	return et.numero;
}

Etudiant find_etudiant_with_email(char email[21])
{
	Etudiant et;
	FILE *file = fopen("./data/etudiants.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%[a-zA-Z ],%[a-zA-Z ],%[a-zA-Z@.],%d/%d/%d\n", &et.numero, et.nom, et.prenom, et.email, &et.naissance.jj, &et.naissance.mm, &et.naissance.aaaa);
		if(strcmp(et.email, email) == 0){
			fclose(file);
			return et;
		}
	}while(!feof(file));
	fclose(file);
	Date date = {0, 0, 0};
	return new_etudiant(0, "", "", "", date);
}

void save_etudiant(Etudiant *et)
{
	FILE *file = fopen("./data/etudiants.csv", "a");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	et->numero = get_last_numero_etudiant() + 1;
	fprintf(file, "%d,%s,%s,%s,", et->numero, et->nom, et->prenom, et->email);

	if(et->naissance.jj < 10)
		fprintf(file, "0%d/", et->naissance.jj);
	else
		fprintf(file, "%d/", et->naissance.jj);

	if(et->naissance.mm < 10)
		fprintf(file, "0%d/", et->naissance.mm);
	else
		fprintf(file, "%d/", et->naissance.mm);

	fprintf(file, "%d\n", et->naissance.aaaa);
}

/**
 * Fonction qui permet de supprimer ou de modifier un etudiant
 * si edit_or_delate est 0 on supprime
 * si edit_or_delate est 1 on modifie
*/
void update_etudiant(Etudiant update, unsigned short int edit_or_update)
{
	FILE *file = NULL, *tmp = NULL;
	Etudiant et;

	file = fopen("./data/etudiants.csv", "r");
	tmp  = fopen("./data/tmp.csv", "a");

	if(file == NULL || tmp == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%[a-zA-Z ],%[a-zA-Z ],%[a-zA-Z@.],%d/%d/%d\n", &et.numero, et.nom, et.prenom, et.email, &et.naissance.jj, &et.naissance.mm, &et.naissance.aaaa);

		if(update.numero == et.numero){
			if(edit_or_update){
				fprintf(tmp, "%d,%s,%s,%s,", update.numero, update.nom, update.prenom, update.email);

				if(update.naissance.jj < 10)
					fprintf(tmp, "0%d/", update.naissance.jj);
				else
					fprintf(tmp, "%d/", update.naissance.jj);

				if(update.naissance.mm < 10)
					fprintf(tmp, "0%d/", update.naissance.mm);
				else
					fprintf(tmp, "%d/", update.naissance.mm);

				fprintf(tmp, "%d\n", update.naissance.aaaa);
			}
		}else{
			fprintf(tmp, "%d,%s,%s,%s,", et.numero, et.nom, et.prenom, et.email);

			if(et.naissance.jj < 10)
				fprintf(tmp, "0%d/", et.naissance.jj);
			else
				fprintf(tmp, "%d/", et.naissance.jj);

			if(et.naissance.mm < 10)
				fprintf(tmp, "0%d/", et.naissance.mm);
			else
				fprintf(tmp, "%d/", et.naissance.mm);

			fprintf(tmp, "%d\n", et.naissance.aaaa);
		}
	}while(!feof(file));

	fclose(file);
	fclose(tmp);

	remove("./data/etudiants.csv");
	rename("./data/tmp.csv", "./data/etudiants.csv");
}

void print_etudiant(Etudiant et)
{
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
}
