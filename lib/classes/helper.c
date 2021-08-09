#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

int last = -1;

void print_classe()
{
	//Classe cl = get_last_code_classe();
	printf("+-----------------------------------------------+\n");
	printf("|\tCode: %-3d\t\t\t\t|\n", get_code_classe());
	printf("+-----------------------------------------------+\n");
	printf("|\tNom: %-21s\t\t|\n", get_nom_classe());
	printf("+-----------------------------------------------+\n");
	printf("|\tNiveau: %s\t\t\t\t|\n", get_niveau_classe());
	printf("+-----------------------------------------------+\n");
}

void view_classes()
{
	FILE *file;
	file = fopen("./data/classes.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue!\n");
		exit(1);
	}

	Classe cl = {0, "", LICENCE};

	printf("\n***Liste de toute les classes****\n\n");
	do{
		new_classe_from_file(file);
		if(last == get_code_classe())
			break;
		printf("+-----------------------------------------------+\n");
		printf("|\tCode: %-3d\t\t\t\t|\n", get_code_classe());
		printf("+-----------------------------------------------+\n");
		printf("|\tNom: %-21s\t\t|\n", get_nom_classe());
		printf("+-----------------------------------------------+\n");
		printf("|\tNiveau: %s\t\t\t\t|\n", get_niveau_classe());
		printf("+-----------------------------------------------+\n");
		last = get_code_classe();
		printf("\n");
	}while(!feof(file));

	fclose(file);
}

void add_classe()
{
	Classe cl = new_classe();
	unsigned short int niveau = 0, bad = 0;

	printf("\n***Ajout une classe***\n\n");

	GRAB_NOM_CLASSE:
	if(bad == 0){
		bad = 1;
		printf("Entrer le nom de la classe : ");
		grab_nom_classe();
	}else{
		printf("Cette classe existe deja. entrer une autre classe svp : ");
		grab_nom_classe();
	}
	Classe find = find_classe_with_nom(get_nom_classe());

	if(find.code)
		goto GRAB_NOM_CLASSE;

	printf("1. Pour LICENCE.\n");
	printf("2. Pour MASTER.\n");
	printf("Entrer le niveau: ");
	grab_niveau_classe();

	printf("+-----------------------------------------------+\n");
	printf("|\tCode: %d\t\t\t\t|\n", get_code_classe());
	printf("+-----------------------------------------------+\n");
	printf("|\tNom: %s\t\t\t\t|\n", get_nom_classe());
	printf("+-----------------------------------------------+\n");
	printf("|\tNiveau: %s\t\t\t\t|\n", get_niveau_classe());
	printf("+-----------------------------------------------+\n");
	save_classe();
}

void update_classe()
{
	char nom[31];
	unsigned short int bad = 0;
	printf("***Modification d'une classe***\n");

	GRAB_NOM_CLASSE_EDIT:
	if(bad == 0){
		bad = 1;
		printf("Entrer le nom de la classe a modifier svp : ");
		scanf("%[a-zA-Z0-9 ]", nom);
		fflush(stdin);
	}else{
		printf("Cette classe n'existe pas. entrer une classe existante svp : ");
		scanf("%[a-zA-Z0-9 ]", nom);
		fflush(stdin);
	}

	Classe find = find_classe_with_nom(nom);
	printf("+-----------------------------------------------+\n");
	printf("|\tCode: %-3d\t\t\t\t|\n", find.code);
	printf("+-----------------------------------------------+\n");
	printf("|\tNom: %-21s\t\t|\n", find.nom);
	printf("+-----------------------------------------------+\n");
	if(find.niveau == LICENCE)
		printf("|\tNiveau: LICENCE\t\t\t\t|\n");
	else if(find.niveau == MASTER)
		printf("|\tNiveau: MASTER\t\t\t\t|\n");
	printf("+-----------------------------------------------+\n");
	if(find.code == 0)
		goto GRAB_NOM_CLASSE_EDIT;

	printf("Entrer le nouveau nom ou 0 pour ne pas modifier : ");
	scanf("%[a-zA-Z0-9 ]", nom);
	fflush(stdin);

	if(strcmp(find.nom, nom) != 0 && strcmp(nom, "0") != 0)
		strcpy(find.nom, nom);

	printf("1. Pour LICENCE.\n");
	printf("2. Pour MASTER.\n");
	do{
		printf("Entrer le nouveau niveau ou 0 pour ne pas modifier : ");
		if(scanf("%d", &bad) == 1 && (bad == 0 || bad == 1 || bad == 2)){
			fflush(stdin);
			break;
		}
		fflush(stdin);
	}while(1);
	find.niveau = (bad-- == 0) ? find.niveau : bad;

	printf("+-----------------------------------------------+\n");
	printf("|\tCode: %-2d\t\t\t\t|\n", find.code);
	printf("+-----------------------------------------------+\n");
	printf("|\tNom: %s\t\t\t\t|\n", find.nom);
	printf("+-----------------------------------------------+\n");
	if(find.niveau == LICENCE)
		printf("|\tNiveau: LICENCE\t\t\t\t|\n", find.niveau);
	else if(find.niveau == MASTER)
		printf("|\tNiveau: MASTER\t\t\t\t|\n", find.niveau);
	printf("+-----------------------------------------------+\n");

	save_update_classe(find);
}

void delate_classe()
{
	char nom[31], rep;
	unsigned short int bad = 0;

	printf("***Suppression de classe***\n");	

	GRAB_NOM_CLASSE_DELATE:
	if(bad == 0){
		bad = 1;
		printf("Entrer le nom de la classe a Supprimer svp : ");
		scanf("%[a-zA-Z ]", nom);
		fflush(stdin);
	}else{
		printf("Cette classe n'existe pas. entrer une classe existante svp : ");
		scanf("%[a-zA-Z ]", nom);
		fflush(stdin);
	}

	Classe find = find_classe_with_nom(nom);
	if(find.code == 0)
		goto GRAB_NOM_CLASSE_DELATE;

	printf("Etes vous sure de vouloir Supprimer Cette classe ? [o/N]\n");
	scanf("%c", &rep);
	if(rep != 'N')
		save_delated_classe(find);
}

Classe find_classe_with_code(int code)
{
	FILE *file;
	file = fopen("./data/classes.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue!\n");
		exit(1);
	}

	Classe cl = {0, "", LICENCE};
	char niveau[8];

	do{
		fscanf(file, "%d,%[a-zA-Z ],%s", &cl.code, cl.nom, niveau);
	}while(!feof(file));

	fclose(file);
}

Classe find_classe_with_nom(char nom[31])
{
	FILE *file;
	file = fopen("./data/classes.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue!\n");
		exit(1);
	}

	char niveau[9];
	Classe cl = {0, "", LICENCE};
	printf("pass %s\n", nom);

	do{
		fscanf(file, "%d,%[a-zA-Z0-9 ],%s\n", &cl.code, cl.nom, niveau);
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

	fclose(file);
	cl.code = 0;
	return cl;
}
