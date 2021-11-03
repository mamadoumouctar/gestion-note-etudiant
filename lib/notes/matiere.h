#ifndef matiere_note_index_
#define matiere_note_index_

#include "../matieres/matiere.h"
#include "../etudiants/etudiant.h"
#include "../classes/classe.h"

typedef struct Faire{
	int id_matiere;
	int id_classe;
} Faire;

void matiere_note_index();

void call_controller(Matiere, int, int);
void call_controller_item(Etudiant, Matiere, int);
void call_controller_collection(Classe, Matiere, int);

int matiere_seFaire(int, int);
int linked_to_classes(int);
int linked_to_matieres(int);

void update_sefaire(Faire, int);

int class_appedd_to_matiere(Classe, Matiere);

void add_matiere_to_classe(Matiere);
void disadd_matiere_to_classe(Matiere);

#endif