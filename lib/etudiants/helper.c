#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "etudiant.h"

void view_etudiants()
{
	printf("***Liste de tout les etudiants***\n");
	Etudiant et;
	FILE *file = fopen("./data/etudiants.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}
	do{
		fscanf(file, "%d ,%s ,%s ,%s ,%d/%d/%d\n", &et.numero, et.nom, et.prenom, et.email, &et.naissance.jj, &et.naissance.mm, &et.naissance.aaaa);
		print_etudiant(et);
	}while(!feof(file));
	fclose(file);
}

void add_etudiant()
{
	printf("***Ajout d'un etudiant***\n");

	Etudiant et = new_etudiant(0, "", "", "", new_date(0, 0, 0));
	unsigned int entier = 0, bad = 0;
	char chaine[31];

	//saisie du nom
	do{
		if(bad == 0)
			printf("Entrer le nom de l'etudiant : ");
		else
			printf("Incorrect le nom doit avoir au moin 3 carractere. entrer le nom : ");
		scanf("%s", chaine);
		fflush(stdin);
		bad = 1;
		if(strlen(chaine) >= 3)
			break;
	}while(1);
	strcpy(et.nom, chaine);
	strcpy(chaine, "");
	bad = 0;

	//saisie du prenom
	do{
		if(bad == 0)
			printf("Entrer le prenom de l'etudiant : ");
		else
			printf("Incorrect le prenom doit avoir au moin 3 carractere. entrer le prenom : ");
		scanf("%s", chaine);
		fflush(stdin);
		bad = 1;
		if(strlen(chaine) >= 3)
			break;
	}while(1);
	strcpy(et.prenom, chaine);
	strcpy(chaine, "");
	bad = 0;

	//saisie de l'email
	do{
		if(bad == 0)
			printf("Entrer l'email de l'etudiant : ");
		else
			printf("Incorrect ceci n'est pas un email. entrer l'email : ");
		GRAB_EMAIL_ETUDIANT_ADD:
		scanf("%s", chaine);
		fflush(stdin);
		bad = 1;
		if(strstr(chaine, "@") && strstr(chaine, ".")){
			Etudiant find = find_etudiant_with_email(chaine);
			if(find.numero != 0){
				printf("Incorrect cet email existe deja. entrer un autre email svp : ");
				goto GRAB_EMAIL_ETUDIANT_ADD;
			}
			break;
		}
	}while(1);
	strcpy(et.email, chaine);
	strcpy(chaine, "");
	bad = 0;

	//siasie de la date de naissance
	GRAB_NAISSANCE_ETUDIANT_ADD:
	if(bad == 0)
		printf("Entrer la date de naissance sous le format jj/mm/aaaa : ");
	else
		printf("Incorrect ceci n'est pas une date de naissance : ");

	scanf("%2d/%2d/%4d", &et.naissance.jj, &et.naissance.mm, &et.naissance.aaaa);

	if(
		(et.naissance.jj < 0 || et.naissance.jj > 31) ||
		(et.naissance.mm < 0 || et.naissance.mm > 12) ||
		et.naissance.aaaa < 1945
	){
		goto GRAB_NAISSANCE_ETUDIANT_ADD;
	}

	save_etudiant(&et);
	print_etudiant(et);
}

void delate_etudiant()
{
	printf("***Modification d'un etudiant***\n");
	unsigned int entier = 0, bad = 0;
	char chaine[31];

	printf("Entrer l'email de l'etudiant a Supprimer : ");
	GRAB_EMAIL_ETUDIANT_DELATE:
	scanf("%s", chaine);
	fflush(stdin);

	if(strcmp(chaine, "0") == 0) return;

	Etudiant find = find_etudiant_with_email(chaine);
	if(find.numero != 0){
		print_etudiant(find);
		printf("Etes vous sure de bien vouloir supprimer cet etudiant [o/N]? ");
	}else{
		printf("Cet email n'existe pas. Entrer un email svp ou 0 pour retourner : ");
		goto GRAB_EMAIL_ETUDIANT_DELATE;
	}

	scanf("%s", chaine);
	if(strcmp(chaine, "o") == 0 || strcmp(chaine, "O") == 0){
		update_etudiant(find, 0);
		printf("\nL'etudiant a ete supprimer avec succes.\n");
	}else{
		printf("\nL'etudiant n'a pas ete supprimer.\n");
	}
}
