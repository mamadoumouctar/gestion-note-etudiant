#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"

void print_matiere(Matiere mat)
{
	printf("+-----------------------------------------------+\n");
	printf("|\tReference : %d\t\t\t\t|\n", mat.reference);
	printf("+-----------------------------------------------+\n");
	printf("|\tLibelle : %-15s\t\t|\n", mat.libelle);
	printf("+-----------------------------------------------+\n");
	printf("|\tCoefficient : %d\t\t\t\t|\n", mat.coefficient);
	printf("+-----------------------------------------------+\n");
}
