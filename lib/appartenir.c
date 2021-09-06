#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classes/classe.h"
#include "etudiants/etudiant.h"

void append_etudiant_into_classe(Classe *cl)
{
	Etudiant find;
	char chaine[31];
	append_etudiant_into_classe:
	printf("Entrer l'email de l'etudiant a rajouter dans la classe %s : ", cl->nom);
	GRAB_APPEND_CLASSE:
	scanf("%s", chaine);
	fflush(stdin);

	if(!strcmp(chaine, "0")) return;

	find = find_etudiant_with_email(chaine);
	if(find.numero == 0){
		printf("Desole cet etudiant n'existe. Entrer l'email de l'etudiant ou 0 pour ignorer : ");
		goto GRAB_APPEND_CLASSE;
	}
	print_etudiant(find);

	if(find.code_classe != -1){
		printf("Cet etudiant est deja dans une classe ete vous sure de modifier la classe de l'etudiant [o/N] : ");
	}else{
		printf("Etes vous sure de vraiment ajouter l'etudiant %s %s a la classe \"%s\" [o/N] : ", find.nom, find.prenom, cl->nom);
	}

	scanf("%s", chaine);
	fflush(stdin);

	if(!strcmp(chaine,"o") || !strcmp(chaine, "O")){
		find.code_classe = cl->code;
		update_etudiant(find, 1);
		printf("L'etudiant a bien ete ajouter a la classe %s\n", cl->nom);
	}else{
		printf("Aucune modification n'a ete fiate a la classe %s.\n", cl->nom);
	}

	printf("Voulez vous rajouter un autre etudiant a la classe %s [O/n] : ", cl->nom);
	scanf("%s", chaine);
	fflush(stdin);
	if(!strcmp(chaine, "o") || !strcmp(chaine, "O")) goto append_etudiant_into_classe;
}

void disappend_etudiant_into_classe(Classe *cl)
{
	char chaine[31];
	printf("Entrer l'email de l'etudiant a retirer de la classe %s : ", cl->nom);
	scanf("%s", chaine);
	fflush(stdin);

	Etudiant find = find_etudiant_with_email(chaine);
	if(find.numero == 0 || find.code_classe != cl->code){
		printf("Desole cet etudiant n'existe pas dans cette classe.\n");
		return;
	}
	printf("Etes vous sure de vraiment retirer l'etudiant %s %s de la classe \"%s\" [o/N] : ", find.nom, find.prenom, cl->nom);
	scanf("%s", chaine);
	fflush(stdin);

	if(!strcmp(chaine,"o") || !strcmp(chaine, "O")){
		find.code_classe = -1;
		update_etudiant(find, 1);
		printf("L'etudiant a bien ete supprimer de la classe %s.\n", cl->nom);
	}else{
		printf("Aucune modification n'a ete fiate a la classe %s.\n", cl->nom);
	}
}
