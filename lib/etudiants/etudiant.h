#ifndef ET_0
#define ET_0

#include "../classes/classe.h"

typedef struct Date{
	int jj;
	int mm;
	int aaaa;
} Date;

typedef struct Etudiant{
	unsigned int numero;
	char nom[31];
	char prenom[21];
	char email[21];
	Date naissance;
	int code_classe;
} Etudiant;

Etudiant new_etudiant(int, char *, char *, char *, Date);
Date new_date(int, int, int);

int get_last_numero_etudiant();
Etudiant find_etudiant_with_email(char *);
int find_etudiant_from_classe(int, Etudiant *);

void save_etudiant(Etudiant *et);
void update_etudiant(Etudiant , int);
void print_etudiant(Etudiant);

#endif