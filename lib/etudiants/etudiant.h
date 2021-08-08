#ifndef ET_0
#define ET_0

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
} Etudiant;

Etudiant new_etudiant(unsigned int, char *, char *, char *, Date);

void print_etudiant(Etudiant);

#endif