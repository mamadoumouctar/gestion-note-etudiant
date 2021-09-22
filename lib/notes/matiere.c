#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"
#include "../matieres/matiere.h"

char chaine[31];
unsigned int entier = 0;

void matiere_note_index()
{
	printf("Entrer le nom de la matiere : ");
	GRAB_PREVENT_FIND_NULL:
	scanf("%s", chaine);
	fflush(stdin);
	Matiere find = get_one_matiere_with(chaine);

	if(!strcmp(chaine, "0")) return;

	if(find.reference == NULL){
		printf("Desole cette matiere n'existe. Entrer le nom de la matiere ou 0 pour retourner : ");
		goto GRAB_PREVENT_FIND_NULL;
	}

	printf("1. Afficher les notes.\n");
	printf("2. Ajouter une note.\n");
	printf("3. Modifier une note.\n");
	printf("4. Supprimer une note.\n");
}
