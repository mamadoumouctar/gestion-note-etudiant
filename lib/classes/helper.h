#ifndef CL_HELPER
#define CL_HELPER

#include "classe.h"

void view_classes();
void add_classe();
void update_classe(char *);
void delate_classe(char *);
void seach_classe();

Classe find_classe_with_code(int code);

void gestion_etudiants_classe(Classe *);
void gestion_classe(Classe *);

#endif