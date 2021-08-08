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
