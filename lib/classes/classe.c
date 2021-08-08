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
	fscanf(file, "%d ,%s ,%s", &cl.code, cl.nom, niveau);
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
		fscanf(file, "%d ,%s ,%s", &bin.code, bin.nom, niveau);
	}while(!feof(file));

	fclose(file);
	return bin.code;
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
	fprintf(file, "%d ,%s ,%s\n", get_code_classe(), get_nom_classe(), get_niveau_classe());
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
		fscanf(file, "%d ,%s ,%s\n", &bin.code, bin.nom, niveau);
		if(bin.code == save.code){
			fprintf(tmp, "%d ,%s ,%s\n", save.code, save.nom, niveau);
		}else{
			fprintf(tmp, "%d ,%s ,%s\n", bin.code, bin.nom, niveau);
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
		fscanf(file, "%d ,%s ,%s\n", &bin.code, bin.nom, niveau);
		if(bin.code != save.code){
			fprintf(tmp, "%d ,%s ,%s\n", bin.code, bin.nom, niveau);
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
	ret = scanf("%s", cl.nom);
	fflush(stdin);

	return ret;
}

int grab_niveau_classe()
{
	return scanf("%d", &cl.niveau), fflush(stdin), cl.niveau--;
}
