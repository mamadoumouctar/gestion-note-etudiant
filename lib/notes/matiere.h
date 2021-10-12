#ifndef matiere_note_index_
#define matiere_note_index_

#include "../matieres/matiere.h"
#include "../etudiants/etudiant.h"
#include "../classes/classe.h"

typedef struct Faire{
	unsigned int id_matiere;
	unsigned int id_classe;
} Faire;

void matiere_note_index();

void call_controller(Matiere, unsigned int, unsigned int);
void call_controller_item(Etudiant, Matiere, unsigned int);
void call_controller_collection(Classe, Matiere, unsigned int);

unsigned int matiere_seFaire(unsigned int, unsigned int);

void update_sefaire(Faire, unsigned int);

#endif