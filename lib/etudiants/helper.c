#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "etudiant.h"
#include "../classes/classe.h"

void view_etudiants()
{
	printf("***Liste de tout les etudiants***\n");
	Etudiant et;
	FILE *file = fopen("./data/etudiants.csv", "r");

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	printf("+--------+-------------------------------+---------------------+---------------------+-------------------+\n");
	printf("| Numero |  Nom                          | Prenom              | Email               | Date de naissance |\n");
	printf("+--------+-------------------------------+---------------------+---------------------+-------------------+\n");

	do{
		fscanf(file, "%d,%[a-zA-Z ],%[a-zA-Z ],%[a-zA-Z@.],%d/%d/%d,%d\n", &et.numero, et.nom, et.prenom, et.email, &et.naissance.jj, &et.naissance.mm, &et.naissance.aaaa, &et.code_classe);

		printf("|  %3d   | %-30s| %-20s| %-20s| ", et.numero, et.nom, et.prenom, et.email);
		if(et.naissance.jj < 10)
			printf("0%1d", et.naissance.jj);
		else
			printf("%2d", et.naissance.jj);

		printf("/");

		if(et.naissance.mm < 10)
			printf("0%1d", et.naissance.mm);
		else
			printf("%2d", et.naissance.mm);

		printf("/%4d        |\n", et.naissance.aaaa);
		printf("+--------+-------------------------------+---------------------+---------------------+-------------------+\n");
	}while(!feof(file));
	fclose(file);
}

void add_etudiant()
{
	printf("***Ajout d'un etudiant***\n");

	Etudiant et = new_etudiant(0, "", "", "", new_date(0, 0, 0));
	unsigned int entier = 0, bad = 0;
	char chaine[32];

	//saisie du nom
	do{
		if(bad == 0)
			printf("Entrer le nom de l'etudiant : ");
		else if(bad == 1)
			printf("Incorrect le nom doit avoir au moin 3 carractere. entrer le nom : ");

		scanf("%32[a-zA-Z ]", chaine);
		fflush(stdin);
		bad = 1;
		if(strlen(chaine) > 30){
			bad = 2;
			printf("Incorrect le nom doit avoir moin de 30 carractere. Entrer le nom : ");
			continue;
		}
		if(strlen(chaine) >= 3)
			break;

	}while(1);
	strcpy(et.nom, chaine);
	strcpy(chaine, "\0");
	bad = 0;

	//saisie du prenom
	do{
		if(bad == 0)
			printf("Entrer le prenom de l'etudiant : ");
		else if(bad == 1)
			printf("Incorrect le prenom doit avoir au moin 3 carracteres. Entrer le prenom : ");

		scanf("%21[a-zA-Z ]", chaine);
		fflush(stdin);
		bad = 1;
		if(strlen(chaine) > 20){
			bad = 2;
			printf("Incorrect le prenom doit avoir moin de 20 carracteres. Entrer le prenom : ");
			continue;
		}
		if(strlen(chaine) >= 3)
			break;
	}while(1);
	strcpy(et.prenom, chaine);
	strcpy(chaine, "\0");
	bad = 0;

	//saisie de l'email
	do{
		if(bad == 0)
			printf("Entrer l'email de l'etudiant : ");
		else if(bad == 1)
			printf("Incorrect ceci n'est pas un email. entrer l'email : ");
		GRAB_EMAIL_ETUDIANT_ADD:
		scanf("%21s", chaine);
		fflush(stdin);
		bad = 1;
		if(strlen(chaine) > 20){
			bad = 2;
			printf("Incorrect l'email doit avoir moin de 20 carracteres. Entrer l'email : ");
			continue;
		}
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
	strcpy(chaine, "\0");
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

	et.code_classe = -1;
	save_etudiant(&et);
	print_etudiant(et);
}

void delate_etudiant(char *mail)
{
	printf("***Modification d'un etudiant***\n");
	Etudiant find;
	char chaine[31];
	unsigned int entier = 0, bad = 0;

	if(mail == NULL){
		printf("Entrer l'email de l'etudiant a Supprimer : ");
		GRAB_EMAIL_ETUDIANT_DELATE:
		scanf("%20s", chaine);
		fflush(stdin);

		if(strcmp(chaine, "0") == 0) return;

		find = find_etudiant_with_email(chaine);
		if(find.numero != 0){
			print_etudiant(find);
			printf("Etes vous sure de bien vouloir supprimer cet etudiant [o/N]? ");
		}else{
			printf("Cet email n'existe pas. Entrer un email svp ou 0 pour retourner : ");
			goto GRAB_EMAIL_ETUDIANT_DELATE;
		}
	}else{
		find = find_etudiant_with_email(mail);
		if(find.numero == 0){
			printf("Desole cet etudiant n'existe pas\n");
			return;
		}
	}

	if(mail != NULL)
		printf("Etes vous sure de bien vouloir supprimer cet etudiant [o/N]? ");
	scanf("%20s", chaine);

	if(strcmp(chaine, "o") == 0 || strcmp(chaine, "O") == 0){
		update_etudiant(find, 0);
		printf("\nL'etudiant a ete supprimer avec succes.\n");
	}else{
		printf("\nL'etudiant n'a pas ete supprimer.\n");
	}
}

void edit_etudiant(char *mail)
{
	printf("***Modification d'un etudiant***\n");
	Etudiant find;
	char chaine[32];
	unsigned short int bad = 0;

	if(mail == NULL){
		printf("Entrer l'email de l'etudiant a modifier : ");
		GRAB_EMAIL_ETUDIANT_EDIT:
		scanf("%20s", chaine);
		fflush(stdin);

		if(strcmp(chaine, "0") == 0) return;

		find = find_etudiant_with_email(chaine);
		if(find.numero != 0){
			print_etudiant(find);
		}else{
			printf("Cet email n'existe pas. Entrer un email svp ou 0 pour retourner : ");
			goto GRAB_EMAIL_ETUDIANT_EDIT;
		}
	}else{
		find = find_etudiant_with_email(mail);
		if(find.numero == 0){
			printf("Desole cet etudiant n'existe pas.\n");
			return;
		}
	}

	//saisie du nom
	do{
		if(bad == 0)
			printf("Entrer le nom de l'etudiant ou 0 pour ne pas modifier : ");
		else if(bad == 1)
			printf("Incorrect le nom doit avoir au moin 3 carractere. entrer le nom : ");
		scanf("%31[a-zA-Z0 ]", chaine);
		fflush(stdin);
		bad = 1;
		if(strcmp(chaine, "0") == 0)
			break;

		if(strlen(chaine) > 20){
			bad = 2;
			printf("Incorrect le nom doit avoir moin de 30 carracteres. Entrer le nom : ");
			continue;
		}

		if(strlen(chaine) >= 3){
			strcpy(find.nom, chaine);
			strcpy(chaine, "");
			break;
		}
	}while(1);
	bad = 0;

	//saisie du prenom
	do{
		if(bad == 0)
			printf("Entrer le prenom de l'etudiant ou 0 pour ne pas modifier : ");
		else if(bad == 1)
			printf("Incorrect le prenom doit avoir au moin 3 carractere. entrer le prenom : ");
		scanf("%21[a-zA-Z0 ]", chaine);
		//gets(chaine);
		fflush(stdin);
		bad = 1;
		if(strcmp(chaine, "0") == 0)
			break;
		if(strlen(chaine) > 20){
			bad = 2;
			printf("Incorrect le prenom doit avoir moin de 20 carracteres. Entrer le prenom : ");
			continue;
		}

		if(strlen(chaine) >= 3){
			strcpy(find.prenom, chaine);
			//strcpy(chaine, "\0");
			break;
		}
	}while(1);
	bad = 0;

	//saisie de email
	do{
		if(bad == 0)
			printf("Entrer l'email de l'etudiant ou 0 pour ne pas modifier : ");
		else if(bad == 1)
			printf("Incorrect ceci n'est pas un email. entrer l'email : ");
		GRAB_EMAIL_ETUDIANT_EDIT_VALIDATION:
		scanf("%21s", chaine);
		fflush(stdin);
		bad = 1;
		if(strcmp(chaine, "0") == 0)
			break;

		if(strlen(chaine) > 20){
			bad = 2;
			printf("Incorrect l'email doit avoir moin de 20 carracteres. Entrer l'email : ");
			continue;
		}

		if(strstr(chaine, "@") && strstr(chaine, ".") && strlen(chaine) >= 3){
			Etudiant toBeUnique = find_etudiant_with_email(chaine);
			if(toBeUnique.numero == 0 || toBeUnique.numero == find.numero){
				strcpy(find.email, chaine);
				strcpy(chaine, "\0");
				break;
			}else{
				printf("Incorrect cet email existe deja chez un autre etudiant. entrer l'email svp : ");
				goto GRAB_EMAIL_ETUDIANT_EDIT_VALIDATION;
			}
		}
	}while(1);
	bad = 0;

	//saisie de la date de naisssance
	do{
		GRAB_NAISSANCE_ETUDIANT_EDIT:
		if(bad == 0)
			printf("Entrer la date de naissance sous le format jj/mm/aaaa ou 0 pour ne pas modifier : ");
		else
			printf("Incorrect ceci n'est pas une date de naissance : ");

		Date naissance;

		scanf("%2d/%2d/%4d", &naissance.jj, &naissance.mm, &naissance.aaaa);

		if(naissance.jj == 0)
			break;

		if(
			(naissance.jj < 0 || naissance.jj > 31) ||
			(naissance.mm < 0 || naissance.mm > 12) ||
			naissance.aaaa < 1945
		){
			bad = 1;
			goto GRAB_NAISSANCE_ETUDIANT_EDIT;
		}else{
			find.naissance = naissance;
			break;
		}
	}while(1);

	update_etudiant(find, 1);
	print_etudiant(find);
}

void seach_etudiant()
{
	printf("***Rechercher un etudiant***\n");
	char chaine[21];
	unsigned int entier = 0;

	printf("Entrer l'email de l'etudiant a rechercher ou 0 pour retourner : ");
	scanf("%[a-zA-Z0-9@.]", chaine);
	fflush(stdin);

	Etudiant find = find_etudiant_with_email(chaine);
	if(find.numero == 0){
		printf("L'email entrer ne correspond a aucun etudiant\n");
		return;
	}
	printf("\n\tInformation sur l'etudiant:\n");
	print_etudiant(find);
	if(find.code_classe != -1){
		Classe cl = find_classe_from_etudiant(find.code_classe);
		printf("\n\tInformation sur sa classe:\n");
		print_classe(cl);
		printf("\n1. Modifier la classe de l'etudiant.\n");
	}else{
		printf("\n\tInformation sur sa classe:\n");
		printf("\nDesole, cet etudiant n'est pas encore associe a une classe.\n\n");

		printf("1. Associe a une classe.\n");

	}
	printf("2. Modifier l'etudiant.\n");
	printf("3. Supprimer l'etudiant.\n");
	printf("4. Retour au menu principal.\n");

	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	switch(entier){
		case 1:
		update_etudiant_classe(&find);
		break;
		case 2:
		edit_etudiant(find.email);
		break;
		case 3:
		delate_etudiant(find.email);
		break;
		case 4:
		break;
		default:
		printf("L'option saisie n'est pas disponible");
	}
}

void update_etudiant_classe(Etudiant *et)
{
	unsigned int entier = 0;
	char chaine[32]; 

	printf("Entrer le nom de la classe a associe : ");
	GRAB_update_etudiant_classe:
	scanf("%30[a-zA-Z0-9 ]", chaine);
	fflush(stdin);

	if(strcmp(chaine, "0") == 0) return;

	Classe cl = find_classe_with_nom(chaine);
	if(cl.code != 0){
		print_classe(cl);
	}else{
		printf("Incorrect cette classe n'existe pas. Entrer le nom de la classe ou 0 pour retourner : ");
		goto GRAB_update_etudiant_classe;
	}

	if(et->code_classe != cl.code){
		et->code_classe = cl.code;
		update_etudiant(*et, 1);
		printf("La classe \"%s\" a ete ajoute a l'etudiant %s %s avec succes.\n", cl.nom, et->nom, et->prenom);
	}else{
		printf("La classe \"%s\" ete deja ajoute a l'etudiant %s %s.\n", cl.nom, et->nom, et->prenom);
	}
}
