#ifndef CL_HELPER
#define CL_HELPER

#include "classe.h"

void view_classes();
void add_classe();
void update_classe();
void delate_classe();

Classe find_classe_with_code(int code);
Classe find_classe_with_nom(char nom[31]);

#endif