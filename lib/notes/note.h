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

void print_note(Note);

void print_note_etudiant_matiere(Etudiant, Matiere);
void print_note_etudiants_classe(Classe, Matiere, Etudiant *);

void add_note_etudiant_matiere(Etudiant, Matiere);
void add_note_etudiant_classe(Classe, Matiere, Etudiant *);

void edit_note_etudiant_matier(Etudiant, Matiere);
void edit_note_etudiant_classe(Classe, Matiere, Etudiant *);

void delate_note_etudiant_matier(Etudiant, Matiere);

Note find_note(Etudiant, Matiere);
void save_note(Note);
void update_note(Note, unsigned int);
unsigned int already_has_note(Etudiant, Matiere);

#endif