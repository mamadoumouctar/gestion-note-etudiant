#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "../etudiants/etudiant.h"
#include "../appartenir.h"

int last = -1;

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

	printf("+------+---------------------+----------+\n");
	printf("| Code |  Nom                |  Niveau  |\n");
	printf("+------+---------------------+----------+\n");
	
	do{
		new_classe_from_file(file);
		if(last == get_code_classe())
			break;

		printf("|  %3d | %-20s| %-9s|\n", get_code_classe(), get_nom_classe(), get_niveau_classe());
		printf("+------+---------------------+----------+\n");

		last = get_code_classe();
	}while(!feof(file));

	fclose(file);
}

void add_classe()
{
	Classe cl = new_classe();
	unsigned short int niveau = 0, bad = 0;

	printf("\n***Ajout une classe***\n\n");

	printf("Entrer le nom de la classe : ");
	grab_nom_classe();

	GRAB_NOM_CLASSE:
	if(bad == 1){
		printf("Cette classe existe deja. entrer une autre classe svp : ");
		grab_nom_classe();
	}else if(bad == 2){
		printf("Incorrect le nom de la classe doit avoir au moins 3 carracteres. Entrer le nom : ");
		grab_nom_classe();
	}

	if(!(strlen(get_nom_classe()) >= 3)){
		bad = 2;
		goto GRAB_NOM_CLASSE;
	}else{
		Classe find = find_classe_with_nom(get_nom_classe());
		if(find.code){
			bad = 1;
			goto GRAB_NOM_CLASSE;
		}
	}

	bad = 0;
	while(1){
		printf("1. Pour LICENCE.\n");
		printf("2. Pour MASTER.\n");
		if(bad == 0){
			bad = 1;
			printf("Entrer le niveau: ");
		}else
			printf("Incorrect ceci ne fais pas partie des choix disponibles. Entrer le niveau: ");
		niveau = grab_niveau_classe();
		if(niveau == 1 || niveau == 2)
			break;
	}
	save_classe();

	printf("+-----------------------------------------------+\n");
	printf("|\tCode: %-3d                               |\n", get_code_classe());
	printf("+-----------------------------------------------+\n");
	printf("|\tNom: %-21s              |\n", get_nom_classe());
	printf("+-----------------------------------------------+\n");
	printf("|\tNiveau: %-9s                       |\n", get_niveau_classe());
	printf("+-----------------------------------------------+\n");
}

void update_classe(char *name)
{
	char nom[31];
	unsigned short int bad = 0;
	if(name == NULL){
		printf("***Modification d'une classe***\n");

		GRAB_NOM_CLASSE_EDIT:
		if(bad == 0){
			bad = 1;
			printf("Entrer le nom de la classe a modifier svp : ");
			scanf("%20[a-zA-Z0-9 ]", nom);
			fflush(stdin);
		}else{
			printf("Cette classe n'existe pas. entrer une classe existante svp : ");
			scanf("%[a-zA-Z0-9 ]", nom);
			fflush(stdin);
		}
	}else{
		strcpy(nom, name);
	}

	Classe find = find_classe_with_nom(nom);
	if(find.code == 0)
		goto GRAB_NOM_CLASSE_EDIT;

	printf("+-----------------------------------------------+\n");
	printf("|\tCode: %-3d                               |\n", find.code);
	printf("+-----------------------------------------------+\n");
	printf("|\tNom: %-21s              |\n", find.nom);
	printf("+-----------------------------------------------+\n");
	if(find.niveau == LICENCE)
		printf("|\tNiveau: %-9s                       |\n", "LICENCE");
	else if(find.niveau == MASTER)
		printf("|\tNiveau: %-9s                       |\n", "MASTER");
	printf("+-----------------------------------------------+\n");

	bad = 0;
	printf("Entrer le nouveau nom ou 0 pour ne pas modifier : ");
	GRAB_NOM_CLASSE_EDIT_UNIQUE:
	if(bad == 1)
		printf("Incorrect ce nom est deja utilise. Entrer le nom : ");
	scanf("%20[a-zA-Z0-9 ]", nom);
	fflush(stdin);

	if(strcmp(nom, "0") == 0)
		goto END_EDIT_CLASSE;

	Classe unique = find_classe_with_nom(nom);
	if(unique.code == 0 || strcmp(unique.nom, find.nom) == 0){
		strcpy(find.nom, nom);
	}else{
		bad = 1;
		goto GRAB_NOM_CLASSE_EDIT_UNIQUE;
	}

	END_EDIT_CLASSE:

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
	printf("|\tCode: %-3d                               |\n", find.code);
	printf("+-----------------------------------------------+\n");
	printf("|\tNom: %-21s              |\n", find.nom);
	printf("+-----------------------------------------------+\n");
	if(find.niveau == LICENCE)
		printf("|\tNiveau: %-9s                       |\n", "LICENCE");
	else if(find.niveau == MASTER)
		printf("|\tNiveau: %-9s                       |\n", "MASTER");
	printf("+-----------------------------------------------+\n");

	save_update_classe(find);
}

void delate_classe(char *name)
{
	char nom[31], rep;
	unsigned short int bad = 0;

	if(name == NULL){
		printf("***Suppression de classe***\n");	

		GRAB_NOM_CLASSE_DELATE:
		if(bad == 0){
			bad = 1;
			printf("Entrer le nom de la classe a Supprimer svp ou 0 pour retourner : ");
		}else{
			printf("Cette classe n'existe pas. entrer une classe existante svp : ");
		}
		scanf("%20[a-zA-Z0-9 ]", nom);
		fflush(stdin);

		if(strcmp(nom, "0") == 0) return;
	}else{
		strcpy(nom, name);
	}

	Classe find = find_classe_with_nom(nom);
	if(find.code == 0)
		goto GRAB_NOM_CLASSE_DELATE;

	printf("+-----------------------------------------------+\n");
	printf("|\tCode: %-3d                               |\n", find.code);
	printf("+-----------------------------------------------+\n");
	printf("|\tNom: %-21s              |\n", find.nom);
	printf("+-----------------------------------------------+\n");
	if(find.niveau == LICENCE)
		printf("|\tNiveau: %-9s                       |\n", "LICENCE");
	else if(find.niveau == MASTER)
		printf("|\tNiveau: %-9s                       |\n", "MASTER");
	printf("+-----------------------------------------------+\n");

	printf("Etes vous sure de vouloir Supprimer Cette classe ? [o/N] : ");
	scanf("%c", &rep);
	fflush(stdin);

	if(rep == 'o' || rep == '0'){
		printf("La classe a bien ete supprimer.\n");
		save_delated_classe(find);
	}
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
		fscanf(file, "%3d,%20[a-zA-Z0-9 ],%8s\n", &cl.code, cl.nom, niveau);
	}while(!feof(file));

	fclose(file);
}

void seach_classe(char *nom_classe)
{
	char chaine[31];
	unsigned int entier = 0;
	Etudiant * etudiants;

	if(nom_classe == NULL){
		printf("***Rechercher une classe***\n");

		printf("Entrer le nom de la classe a rechercher : ");
		scanf("%20[a-zA-Z0-9 ]", chaine);
		fflush(stdin);
	}else{
		strcpy(chaine, nom_classe);
	}

	Classe find = find_classe_with_nom(chaine);

	if(find.code == 0){
		printf("Incorrect cette classe n'existe pas.\n");
		return;
	}

	printf("------------Information sur la classe------------\n");
	print_classe(find);

	etudiants = malloc(sizeof(Etudiant) * 10);
	int max = find_etudiant_from_classe(find.code, etudiants);

	printf("\n---------Etudiants de la classe: %s---------\n", find.nom);
	if(max == 0){
		printf("Desole cette classe n'a pas encore d'etudiant.\n");
		free(etudiants);
		goto AUTHER_SYSTEM;
	}else{
		printf("\nNous avons %d etudiant(s) dans cette classe\n", max);
	}

	printf("+--------+-------------------------------+---------------------+---------------------+-------------------+\n");
	printf("| Numero |  Nom                          | Prenom              | Email               | Date de naissance |\n");
	printf("+--------+-------------------------------+---------------------+---------------------+-------------------+\n");
	for(unsigned int i = 0; i < max; i++){
		printf("|  %3d   | %-30s| %-20s| %-20s| ", etudiants[i].numero, etudiants[i].nom, etudiants[i].prenom, etudiants[i].email);
		if(etudiants[i].naissance.jj < 10)
			printf("0%1d", etudiants[i].naissance.jj);
		else
			printf("%2d", etudiants[i].naissance.jj);

		printf("/");

		if(etudiants[i].naissance.mm < 10)
			printf("0%1d", etudiants[i].naissance.mm);
		else
			printf("%2d", etudiants[i].naissance.mm);

		printf("/%4d        |\n", etudiants[i].naissance.aaaa);
		printf("+--------+-------------------------------+---------------------+---------------------+-------------------+\n");
		//print_etudiant(etudiants[i]);
	}
	free(etudiants);

	AUTHER_SYSTEM:
	printf("\n");
	printf("1. Gestion des etudiants de la classe.\n");
	printf("2. Gestion de la classe.\n");
	printf("3. Gestion des matiers de la classe.\n");

	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	switch(entier){
		case 1:
		gestion_etudiants_classe(&find);
		break;
		case 2:
		gestion_classe(&find);
		break;
	}
}

void gestion_etudiants_classe(Classe *cl)
{
	unsigned int entier = 0;
	system("cls");

	printf("Gestion des etudiants de la classe %s.\n", cl->nom);
	printf("\n");

	printf("1. Retirer un etudiant de la classe %s.\n", cl->nom);
	printf("2. Rajouter un etudiant de la classe %s.\n", cl->nom);
	printf("0. Pour retourner.\n");

	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	switch(entier){
		case 1:
		disappend_etudiant_into_classe(cl);
		break;
		case 2:
		append_etudiant_into_classe(cl);
		break;
		case 0: case 3:
		seach_classe(cl->nom);
		break;
		default:
		printf("L'option saisie n'est pas disponible.\n");
	}

}

void gestion_classe(Classe *cl)
{
	unsigned int entier = 0;
	system("cls");

	printf("1. Modifier la classe.\n");
	printf("2. Supprimer la classe.\n");
	printf("0. Pour retourner.\n");

	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	switch(entier){
		case 1:
		update_classe(cl->nom);
		break;
		case 2:
		delate_classe(cl->nom);
		break;
		case 0: case 3:
		seach_classe(cl->nom);
		break;
		default:
		printf("L'option saisie n'est pas disponible.\n");
	}
}
