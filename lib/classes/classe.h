#ifndef CL_MAIN
#define CL_MAIN

typedef enum Niveau
{
	LICENCE,
	MASTER
} Niveau;

typedef struct Classe
{
	int code;
	char nom[31];
	Niveau niveau;
} Classe;

Classe new_classe();
Classe new_classe_from_file(FILE *file);
int get_last_code_classe();

void print_classe(Classe);

void save_classe();
void save_update_classe(Classe);
void save_delated_classe(Classe);

void set_code_classe(int code);
void set_nom_classe(char nom[31]);
void set_niveau_classe(Niveau niveau);
void set_niveau_classe_s(char niveau[9]);

int get_code_classe();
char * get_nom_classe();
char * get_niveau_classe();

int grab_nom_classe();
int grab_niveau_classe();

Classe find_classe_with_nom(char nom[31]);
Classe find_classe_from_etudiant(unsigned int);

#endif