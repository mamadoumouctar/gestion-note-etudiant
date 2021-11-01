#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classe.h"

Classe cl;

Classe new_classe()
{
	Classe new = {0, "", 0};
	cl = new;
	return cl;
}

Classe new_classe_from_file(FILE *file)
{
	char niveau[8];
	fscanf(file, "%3d,%20[a-zA-Z0-9 ],%8s\n", &cl.code, cl.nom, niveau);
	set_niveau_classe_s(niveau);
}

int get_last_code_classe()
{
	FILE *file;
	char niveau[8];
	Classe bin = {0, "", 0};
	file = fopen("./data/classes.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue!\n");
		exit(1);
	}

	do{
		fscanf(file, "%3d,%20[a-zA-Z0-9 ],%8s\n", &bin.code, bin.nom, niveau);
	}while(!feof(file));

	fclose(file);
	return bin.code;
}

void print_classe(Classe classe)
{
	printf("+-----------------------------------------------+\n");
	printf("|\tCode : %-3d\t\t\t\t|\n", classe.code);
	printf("+-----------------------------------------------+\n");
	printf("|\tNom : %-30s\t|\n", classe.nom);
	printf("+-----------------------------------------------+\n");
	if(classe.niveau == LICENCE)
		printf("|\tNiveau : LICENCE\t\t\t|\n");
	else if(classe.niveau == MASTER)
		printf("|\tNiveau : MASTER\t\t\t|\n");
	else
		printf("|\tNiveau : Inconnu\t\t\t|\n");
	printf("+-----------------------------------------------+\n");
}

void save_classe()
{
	FILE *file;
	file = fopen("./data/classes.csv", "a");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue!\n");
		exit(1);
	}
	int last_code = get_last_code_classe() + 1;
	set_code_classe(last_code);
	fprintf(file, "%d,%s,%s\n", get_code_classe(), get_nom_classe(), get_niveau_classe());
	fclose(file);
}

void save_update_classe(Classe save)
{
	Classe bin;
	char niveau[8];

	FILE *file, *tmp;
	
	tmp = fopen("./data/tmp.csv", "a");
	file = fopen("./data/classes.csv", "r");

	if(file == NULL || tmp == NULL){
		printf("L'ouverture du fichier a echoue!\n");
		exit(1);
	}
	do{
		fscanf(file, "%3d,%20[a-zA-Z0-9 ],%8s\n", &bin.code, bin.nom, niveau);
		if(bin.code == save.code){
			fprintf(tmp, "%d,%s,%s\n", save.code, save.nom, niveau);
		}else{
			fprintf(tmp, "%d,%s,%s\n", bin.code, bin.nom, niveau);
		}
	}while(!feof(file));
	
	fclose(tmp);
	fclose(file);

	remove("./data/classes.csv");
	rename("./data/tmp.csv", "./data/classes.csv");
}

void save_delated_classe(Classe save)
{
	Classe bin;
	char niveau[8];

	FILE *file, *tmp;
	
	tmp = fopen("./data/tmp.csv", "a");
	file = fopen("./data/classes.csv", "r");

	if(file == NULL || tmp == NULL){
		printf("L'ouverture du fichier a echoue!\n");
		exit(1);
	}
	do{
		fscanf(file, "%3d,%20[a-zA-Z0-9 ],%8s\n", &bin.code, bin.nom, niveau);
		if(bin.code != save.code){
			fprintf(tmp, "%d,%s,%s\n", bin.code, bin.nom, niveau);
		}
	}while(!feof(file));
	
	fclose(tmp);
	fclose(file);

	remove("./data/classes.csv");
	rename("./data/tmp.csv", "./data/classes.csv");	
}

void set_code_classe(int code)
{
	cl.code = code;
}

int get_code_classe()
{
	return cl.code;
}

void set_nom_classe(char nom[31])
{
	strcpy(cl.nom, nom);
}

char * get_nom_classe()
{
	return cl.nom;
}

void set_niveau_classe(Niveau niveau)
{
	if(niveau == 0 || niveau == 1)
		cl.niveau = niveau;
}

void set_niveau_classe_s(char niveau[9])
{
	if(strcmp(niveau, "LICENCE") == 0)
		cl.niveau = 0;
	else if(strcmp(niveau, "MASTER") == 0)
		cl.niveau = 1;
	else
		cl.niveau = -1;
}

char * get_niveau_classe()
{
	static char var[8];
	if(cl.niveau == 0)
		strcpy(var, "LICENCE");
	else if(cl.niveau == 1)
		strcpy(var, "MASTER");
	else
		strcpy(var, "");
	return var;
}

int grab_nom_classe()
{
	unsigned short int ret = 0;
	ret = scanf("%20[a-zA-Z0-9 ]", cl.nom);
	fflush(stdin);

	return ret;
}

int grab_niveau_classe()
{
	return scanf("%d", &cl.niveau), fflush(stdin), cl.niveau--;
}

Classe find_classe_with_nom(char nom[31])
{
	FILE *file;
	file = fopen("./data/classes.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue!\n");
		exit(EXIT_FAILURE);
	}

	char niveau[9];
	Classe cl = {0, "", LICENCE};

	do{
		fscanf(file, "%3d,%20[a-zA-Z0-9 ],%8s\n", &cl.code, cl.nom, niveau);
		if(strcmp(nom, cl.nom) == 0){
			if(strcmp(niveau, "LICENCE") == 0)
				cl.niveau = 0;
			else if(strcmp(niveau, "MASTER") == 0)
				cl.niveau = 1;
			else
				cl.niveau = -1;
			fclose(file);
			return cl;
		}
	}while(!feof(file));
	fclose(file);
	cl.code = 0;
	strcpy(cl.nom, "");
	cl.niveau = 0;
	return cl;
}

Classe find_classe_from_etudiant(unsigned int code_classe)
{
	FILE *file = fopen("./data/classes.csv", "r");
	Classe ret;
	char niveau[8];

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%3d,%20[a-zA-Z0-9 ],%8s\n",&ret.code, ret.nom, niveau);
		if(ret.code == code_classe){
			fclose(file);
			if(strcmp(niveau, "LICENCE") == 0)
				ret.niveau = 0;
			else if(strcmp(niveau, "MASTER") == 0)
				ret.niveau = 1;
			else
				ret.niveau = -1;
			return ret;
		}
	}while(!feof(file));
	fclose(file);
	ret.code = 0;
	strcpy(ret.nom, "\0");
	ret.niveau = LICENCE;

	return ret;
}
