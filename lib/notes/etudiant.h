#ifndef et_n
#define et_n

#include "../etudiants/etudiant.h"

void etudiant_note_index();

void show_all_note_etudiant(Etudiant);
void add_all_note_etudiant(Etudiant);

void goto_classe_find_note(Etudiant);

char *get_appreciation(unsigned int);
unsigned int linked_to_note(unsigned int);

#endif