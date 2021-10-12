#ifndef NOTE_
#define NOTE_

#include "../matieres/matiere.h"
#include "../etudiants/etudiant.h"

typedef struct Note{
	unsigned int id_etudiant;
	unsigned int id_matiere;
	float note_cc;
	float note_ds;
} Note;

void print_note_etudiant_matiere(Etudiant, Matiere);
void print_note_etudiants_classe(Classe, Matiere, Etudiant *);

Note find_note(Etudiant, Matiere);

#endif