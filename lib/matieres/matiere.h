#ifndef MA_MAIN
#define MA_MAIN

typedef struct Matiere{
	int reference;
	char libelle[16];
	int coefficient;
} Matiere;

void print_matiere(Matiere);
void save_matiere(Matiere mat);
void update_matiere(Matiere, int);

int get_nomber_of_matiere_with(char *);

int get_last_reference_matiere();

void find_matieres(char *, Matiere *);
Matiere find_matiere(int);
Matiere get_one_matiere_with(char *);

void find_matieres_and_print(char *);

#endif