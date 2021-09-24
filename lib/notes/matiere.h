#ifndef matiere_note_index_
#define matiere_note_index_

#include "../matieres/matiere.h"

typedef struct Faire{
	unsigned int id_matiere;
	unsigned int id_classe;
} Faire;

void matiere_note_index();

void call_controller(Matiere, unsigned int, unsigned int);

unsigned int matiere_seFaire(unsigned int, unsigned int);

void update_sefaire(Faire, unsigned int);

#endif