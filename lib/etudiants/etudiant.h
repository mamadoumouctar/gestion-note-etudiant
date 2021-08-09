#ifndef ET_0
#define ET_0

#include "../classes/classe.h"

typedef struct Date{
	unsigned short int jj;
	unsigned short int mm;
	unsigned int aaaa;
} Date;

typedef struct Etudiant{
	unsigned int numero;
	char nom[31];
	char prenom[21];
	char email[21];
	Date naissance;
	int code_classe;
} Etudiant;

Etudiant new_etudiant(unsigned int, char *, char *, char *, Date);
Date new_date(unsigned short int, unsigned short int, unsigned int);

int get_last_numero_etudiant();
Etudiant find_etudiant_with_email(char *);

void save_etudiant(Etudiant *et);
void update_etudiant(Etudiant , unsigned short int);
void print_etudiant(Etudiant);

#endif