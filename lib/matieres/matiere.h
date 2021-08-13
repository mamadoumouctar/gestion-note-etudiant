#ifndef MA_MAIN
#define MA_MAIN

typedef struct Matiere{
	int reference;
	char libelle[16];
	short int coefficient;
} Matiere;

void print_matiere(Matiere);
void save_matiere(Matiere mat);

int get_last_reference_matiere();

#endif