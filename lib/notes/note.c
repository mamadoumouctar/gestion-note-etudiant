#include <stdio.h>
#include <stdlib.h>
#include "note.h"

void print_note(Note note)
{
	printf("+-----------------------------------------------+\n");
	printf("|\t ID Etudiant : %d\t\t\t|\n", note.id_etudiant);
	printf("+-----------------------------------------------+\n");
	printf("|\t ID Matiere : %d\t\t\t\t|\n", note.id_matiere);
	printf("+-----------------------------------------------+\n");
	printf("|\t Note CC : %2.2f\t\t\t|\n", note.note_cc);
	printf("+-----------------------------------------------+\n");
	printf("|\t Note DS : %2.2f\t\t\t|\n", note.note_ds);
	printf("+-----------------------------------------------+\n");
}

void print_note_etudiant_matiere(Etudiant et, Matiere mat)
{
	unsigned int entier = 6;
	printf("Quel note voulez vous afficher ?\n");
	printf("1. Note CC.\n");
	printf("2. Note DS.\n");
	printf("3. Les deux.\n");
	printf("0. Retour.\n");
	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	Note find = find_note(et, mat);

	switch(entier){
		case 1:
		printf("+-----------------------------------------------+\n");
		printf("|\tNumero : %d\t\t\t\t|\n", et.numero);
		printf("+-----------------------------------------------+\n");
		printf("|\tNom : %-30s\t|\n", et.nom);
		printf("+-----------------------------------------------+\n");
		printf("|\tPrenom : %-20s\t\t|\n", et.prenom);
		printf("+-----------------------------------------------+\n");
		printf("|\tEmail : %-20s\t\t|\n", et.email);
		printf("+-----------------------------------------------+\n");
		printf("|\tNaissance :");
		if(et.naissance.jj < 10)
			printf(" 0%1d/", et.naissance.jj);
		else
			printf(" %2d/", et.naissance.jj);

		if(et.naissance.mm < 10)
			printf("0%1d/", et.naissance.mm);
		else
			printf("%2d/", et.naissance.mm);

		printf("%4d", et.naissance.aaaa);
		printf("\t\t\t|\n");
		printf("+-----------------------------------------------+\n");
		printf("|\tNote de CC : %2.2f\t\t\t|\n", find.note_cc);
		printf("+-----------------------------------------------+\n");
		break;
		case 2:
		printf("+-----------------------------------------------+\n");
		printf("|\tNumero : %d\t\t\t\t|\n", et.numero);
		printf("+-----------------------------------------------+\n");
		printf("|\tNom : %-30s\t|\n", et.nom);
		printf("+-----------------------------------------------+\n");
		printf("|\tPrenom : %-20s\t\t|\n", et.prenom);
		printf("+-----------------------------------------------+\n");
		printf("|\tEmail : %-20s\t\t|\n", et.email);
		printf("+-----------------------------------------------+\n");
		printf("|\tNaissance :");
		if(et.naissance.jj < 10)
			printf(" 0%1d/", et.naissance.jj);
		else
			printf(" %2d/", et.naissance.jj);

		if(et.naissance.mm < 10)
			printf("0%1d/", et.naissance.mm);
		else
			printf("%2d/", et.naissance.mm);

		printf("%4d", et.naissance.aaaa);
		printf("\t\t\t|\n");
		printf("+-----------------------------------------------+\n");
		printf("|\tNote de DS : %2.2f\t\t\t|\n", find.note_ds);
		printf("+-----------------------------------------------+\n");
		break;
		case 3:
		printf("+-----------------------------------------------+\n");
		printf("|\tNumero : %d\t\t\t\t|\n", et.numero);
		printf("+-----------------------------------------------+\n");
		printf("|\tNom : %-30s\t|\n", et.nom);
		printf("+-----------------------------------------------+\n");
		printf("|\tPrenom : %-20s\t\t|\n", et.prenom);
		printf("+-----------------------------------------------+\n");
		printf("|\tEmail : %-20s\t\t|\n", et.email);
		printf("+-----------------------------------------------+\n");
		printf("|\tNaissance :");
		if(et.naissance.jj < 10)
			printf(" 0%1d/", et.naissance.jj);
		else
			printf(" %2d/", et.naissance.jj);

		if(et.naissance.mm < 10)
			printf("0%1d/", et.naissance.mm);
		else
			printf("%2d/", et.naissance.mm);

		printf("%4d", et.naissance.aaaa);
		printf("\t\t\t|\n");
		printf("+-----------------------------------------------+\n");
		printf("|\tNote de CC : %2.2f\t\t\t|\n", find.note_cc);
		printf("+-----------------------------------------------+\n");
		printf("|\tNote de DS : %2.2f\t\t\t|\n", find.note_ds);
		printf("+-----------------------------------------------+\n");
		break;
		case 0:
		return;
		default:
		printf("Desole cette option n'est pas pris en charge.\n");
		exit(EXIT_FAILURE);
	}
}

void print_note_etudiants_classe(Classe cl, Matiere mat, Etudiant * etudiants)
{
	unsigned int entier = 6, i = 0;
	printf("Quel note voulez vous afficher ?\n");
	printf("1. Note CC.\n");
	printf("2. Note DS.\n");
	printf("3. Les deux.\n");
	printf("0. Retour.\n");
	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	Note find;
	printf("Notes de la classe %s pour la matiere %s\n", cl.nom, mat.libelle);

	switch(entier){
		case 1:
		printf("+--------+-------------------------------+---------------------+---------------------+-------------------+---------+\n");
		printf("| Numero |  Nom                          | Prenom              | Email               | Date de naissance | Note CC |\n");
		printf("+--------+-------------------------------+---------------------+---------------------+-------------------+---------+\n");

		while(etudiants[i].numero != 0){
			find = find_note(etudiants[i], mat);
			printf("|  %3d   | %-30s| %-20s| %-20s| ", etudiants[i].numero, etudiants[i].nom, etudiants[i].prenom, etudiants[i].email);
			if(etudiants[i].naissance.jj < 10)
				printf("0%1d", etudiants[i].naissance.jj);
			else
				printf("%2d", etudiants[i].naissance.jj);

			printf("/");

			if(etudiants[i].naissance.mm < 10)
				printf("0%1d", etudiants[i].naissance.mm);
			else
				printf("%2d", etudiants[i].naissance.mm);

			printf("/%4d        |", etudiants[i].naissance.aaaa);
			if(find.note_cc != 0)
				printf("  %2.2f  |\n", find.note_cc);
			else
				printf("    -    |\n");
			printf("+--------+-------------------------------+---------------------+---------------------+-------------------+---------+\n");
			i++;
		}
		break;
		case 2:
		printf("+--------+-------------------------------+---------------------+---------------------+-------------------+---------+\n");
		printf("| Numero |  Nom                          | Prenom              | Email               | Date de naissance | Note DS |\n");
		printf("+--------+-------------------------------+---------------------+---------------------+-------------------+---------+\n");

		while(etudiants[i].numero != 0){
			find = find_note(etudiants[i], mat);
			printf("|  %3d   | %-30s| %-20s| %-20s| ", etudiants[i].numero, etudiants[i].nom, etudiants[i].prenom, etudiants[i].email);
			if(etudiants[i].naissance.jj < 10)
				printf("0%1d", etudiants[i].naissance.jj);
			else
				printf("%2d", etudiants[i].naissance.jj);

			printf("/");

			if(etudiants[i].naissance.mm < 10)
				printf("0%1d", etudiants[i].naissance.mm);
			else
				printf("%2d", etudiants[i].naissance.mm);

			printf("/%4d        |", etudiants[i].naissance.aaaa);
			if(find.note_ds != 0)
				printf("  %2.2f  |\n", find.note_ds);
			else
				printf("    -    |\n");
			printf("+--------+-------------------------------+---------------------+---------------------+-------------------+---------+\n");
			i++;
		}
		break;
		case 3:
		printf("+--------+-------------------------------+---------------------+---------------------+-------------------+---------+---------+\n");
		printf("| Numero |  Nom                          | Prenom              | Email               | Date de naissance | Note CC | Note DS |\n");
		printf("+--------+-------------------------------+---------------------+---------------------+-------------------+---------+---------+\n");

		while(etudiants[i].numero != 0){
			find = find_note(etudiants[i], mat);
			printf("|  %3d   | %-30s| %-20s| %-20s| ", etudiants[i].numero, etudiants[i].nom, etudiants[i].prenom, etudiants[i].email);
			if(etudiants[i].naissance.jj < 10)
				printf("0%1d", etudiants[i].naissance.jj);
			else
				printf("%2d", etudiants[i].naissance.jj);

			printf("/");

			if(etudiants[i].naissance.mm < 10)
				printf("0%1d", etudiants[i].naissance.mm);
			else
				printf("%2d", etudiants[i].naissance.mm);

			printf("/%4d        |", etudiants[i].naissance.aaaa);
			if(find.note_cc != 0)
				printf("  %2.2f  |", find.note_cc);
			else
				printf("    -    |");
			if(find.note_ds != 0)
				printf("  %2.2f  |\n", find.note_ds);
			else
				printf("    -    |\n");
			printf("+--------+-------------------------------+---------------------+---------------------+-------------------+---------+---------+\n");
			i++;
		}
		break;
		case 0:
		return;
		default:
		printf("Desole cette option n'est pas pris en charge.\n");
		exit(EXIT_FAILURE);
	}
}

void add_note_etudiant_matiere(Etudiant et, Matiere mat)
{
	if(already_has_note(et, mat)){
		printf("Desole cette etudiants a deja une note dans cette matiere.");
		return;
	}
	unsigned int entier = 6, bad = 0;
	printf("Quel note voulez vous afficher ?\n");
	printf("1. Note CC.\n");
	printf("2. Note DS.\n");
	printf("3. Les deux.\n");
	printf("0. Retour.\n");
	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	printf("Ajout de la note l'etudiant %s %s pour la matiere %s\n", et.nom, et.prenom, mat.libelle);

	Note note;
	note.id_etudiant = et.numero;
	note.id_matiere = mat.reference;

	switch(entier){
		case 1:
		do{
			if(bad){
				printf("Incorrect la note de CC est comprise entre 0 et 20 : ");
			}else{
				bad = 1;
				printf("Entrer la note de CC : ");
			}
			scanf("%f", &note.note_cc);
			fflush(stdin);
		}while(note.note_cc > 20 || note.note_cc <= 0);
		note.note_ds = 0;
		break;
		case 2:
		do{
			if(bad){
				printf("Incorrect la note de DS est comprise entre 0 et 20 : ");
			}else{
				bad = 1;
				printf("Entrer la note de DS : ");
			}
			scanf("%f", &note.note_ds);
			fflush(stdin);
		}while(note.note_ds > 20 || note.note_ds <= 0);
		note.note_cc = 0;
		break;
		case 3:
		do{
			if(bad){
				printf("Incorrect la note de CC est comprise entre 0 et 20 : ");
			}else{
				bad = 1;
				printf("Entrer la note CC : ");
			}
			scanf("%f", &note.note_cc);
			fflush(stdin);
		}while(note.note_cc > 20 || note.note_cc <= 0);

		bad = 0;
		do{
			if(bad){
				printf("Incorrect la note de DS est comprise entre 0 et 20 : ");
			}else{
				bad = 1;
				printf("Entrer la note de DS : ");
			}
			scanf("%f", &note.note_ds);
			fflush(stdin);
		}while(note.note_ds > 20 || note.note_ds <= 0);
		break;
		case 0:
		return;
		break;
		default:
		printf("Desole cette option n'est pas pris en charge.\n");
		exit(EXIT_FAILURE);
	}
	save_note(note);
}

void add_note_etudiant_classe(Classe cl, Matiere mat, Etudiant * etudiants)
{
	unsigned int entier = 6, i = 0, bad = 0, val = 0;
	printf("Quel note voulez vous afficher ?\n");
	printf("1. Note CC.\n");
	printf("2. Note DS.\n");
	printf("3. Les deux.\n");
	printf("0. Retour.\n");
	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	Note note;
	printf("Ajout de note a la classe %s pour la matiere %s\n", cl.nom, mat.libelle);

	switch(entier){
		case 1:
			while(etudiants[i].numero != 0){
				if(!already_has_note(etudiants[i], mat)){
					bad = 0;
					note.id_etudiant = etudiants[i].numero;
					note.id_matiere = mat.reference;
					note.note_ds = 0;
					print_etudiant(etudiants[i]);
					do{
						if(bad){
							printf("Incorrect la note de CC est comprise entre 0 et 20 : ");
						}else{
							bad = 1;
							printf("Entrer la note de CC : ");
						}
						val = scanf("%f", &note.note_cc);
						fflush(stdin);
					}while(note.note_cc > 20 || note.note_cc <= 0 || val != 1);
					save_note(note);
				}
				i++;
			}
		break;
		case 2:
			while(etudiants[i].numero != 0){
				if(!already_has_note(etudiants[i], mat)){
					bad = 0;
					note.id_etudiant = etudiants[i].numero;
					note.id_matiere = mat.reference;
					note.note_cc = 0;
					print_etudiant(etudiants[i]);
					do{
						if(bad){
							printf("Incorrect la note de DS est comprise entre 0 et 20 : ");
						}else{
							bad = 1;
							printf("Entrer la note de DS : ");
						}
						val = scanf("%f", &note.note_ds);
						fflush(stdin);
					}while(note.note_ds > 20 || note.note_ds <= 0 || val != 1);
					save_note(note);
				}
				i++;
			}
		break;
		case 3:
			while(etudiants[i].numero != 0){
				if(!already_has_note(etudiants[i], mat)){
					bad = 0;
					note.id_etudiant = etudiants[i].numero;
					note.id_matiere = mat.reference;
					print_etudiant(etudiants[i]);
					do{
						if(bad){
							printf("Incorrect la note de CC est comprise entre 0 et 20 : ");
						}else{
							bad = 1;
							printf("Entrer la note de CC : ");
						}
						val = scanf("%f", &note.note_cc);
						fflush(stdin);
					}while(note.note_cc > 20 || note.note_cc <= 0 || val != 1);

					bad = 0;
					do{
						if(bad){
							printf("Incorrect la note de DS est comprise entre 0 et 20 : ");
						}else{
							bad = 1;
							printf("Entrer la note de DS : ");
						}
						val = scanf("%f", &note.note_ds);
						fflush(stdin);
					}while(note.note_ds > 20 || note.note_ds <= 0 || val != 1);
					save_note(note);
				}
				i++;
			}
		break;
	}
}

void edit_note_etudiant_matier(Etudiant et, Matiere mat)
{
	unsigned int has_not_note = -1;
	if(has_not_note = !already_has_note(et, mat)){
		printf("Desole cette etudiants n'a pas de note pour cette matiere. vous allez le rajouter une note.\n");
	}
	unsigned int entier = 6, bad = 0, val = 0;
	printf("Quel note voulez vous afficher ?\n");
	printf("1. Note CC.\n");
	printf("2. Note DS.\n");
	printf("3. Les deux.\n");
	printf("0. Retour.\n");
	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	printf("Modification de la note l'etudiant %s %s pour la matiere %s\n", et.nom, et.prenom, mat.libelle);
	Note note, find = find_note(et, mat);

	switch(entier){
		case 1:
		do{
			if(bad){
				printf("Incorrect la note de CC est comprise entre 0 et 20 ou 0 pour ne pas modifier : ");
			}else{
				bad = 1;
				printf("Entrer la note de CC : ");
			}
			val = scanf("%f", &note.note_cc);
			fflush(stdin);
			if(note.note_cc == 0) break;
		}while(note.note_cc > 20 || note.note_cc < 0 || val != 1);
		
		if(note.note_cc != 0)
			find.note_cc = note.note_cc;
		
		break;
		case 2:
		do{
			if(bad){
				printf("Incorrect la note de DS est comprise entre 0 et 20 ou 0 pour ne pas modifier : ");
			}else{
				bad = 1;
				printf("Entrer la note de DS : ");
			}
		val = scanf("%f", &note.note_ds);
			fflush(stdin);
			if(note.note_cc == 0) break;
		}while(note.note_ds > 20 || note.note_ds < 0 || val != 1);

		if(note.note_ds != 0)
			find.note_ds = note.note_ds;
		
		break;
		case 3:
		do{
			if(bad){
				printf("Incorrect la note de CC est comprise entre 0 et 20 ou 0 pour ne pas modifier : ");
			}else{
				bad = 1;
				printf("Entrer la note CC : ");
			}
			val = scanf("%f", &note.note_cc);
			fflush(stdin);
			if(note.note_cc == 0) break;
		}while(note.note_cc > 20 || note.note_cc < 0 || val != 1);

		bad = 0;
		do{
			if(bad){
				printf("Incorrect la note de DS est comprise entre 0 et 20 ou 0 pour ne pas modifier : ");
			}else{
				bad = 1;
				printf("Entrer la note de DS : ");
			}
			val = scanf("%f", &note.note_ds);
			fflush(stdin);
			if(note.note_cc == 0) break;
		}while(note.note_ds > 20 || note.note_ds < 0 || val != 1);

		if(note.note_cc != 0) find.note_cc = note.note_cc;
		if(note.note_ds != 0) find.note_ds = note.note_ds;

		break;
		case 0:
		return;
		break;
		default:
		printf("Desole cette option n'est pas pris en charge.\n");
		exit(EXIT_FAILURE);
	}
	print_note(find);

	if(has_not_note){
		find.id_etudiant = et.numero;
		find.id_matiere = mat.reference;
		save_note(find);
	}else{ update_note(find, 1); }
}

void edit_note_etudiant_classe(Classe cl, Matiere mat, Etudiant * etudiants)
{
	unsigned int entier = 6, i = 0, bad = 0, val = 0;
	Note note, find;
	printf("Modification des notes de la classe %s pour la matiere %s\n", cl.nom, mat.libelle);

	printf("Quel note voulez vous modifier ?\n");
	printf("1. Note CC.\n");
	printf("2. Note DS.\n");
	printf("3. Les deux.\n");
	printf("0. Retour.\n");
	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	switch(entier){
		case 1:
		while(etudiants[i].numero != 0){
			find = find_note(etudiants[i], mat);
			if(find.id_etudiant == 0 || find.id_matiere == 0){ i++; continue; }

			print_etudiant(etudiants[i]);
			printf("|\t Note CC : %2.2f\t\t\t|\n", find.note_cc);
			printf("+-----------------------------------------------+\n");
			printf("|\t Note DS : %2.2f\t\t\t|\n", find.note_ds);
			printf("+-----------------------------------------------+\n");
			do{
				if(bad){
					printf("Incorrect la note de CC est comprise entre 0 et 20 ou 0 pour ne pas modifier : ");
				}else{
					bad = 1;
					printf("Entrer la note de CC : ");
				}
				val = scanf("%f", &note.note_cc);
				fflush(stdin);
				if(note.note_cc == 0) break;
			}while(note.note_cc > 20 || note.note_cc < 0 || val != 1);

			if(note.note_cc != 0)
				find.note_cc = note.note_cc;

			update_note(find, 1);
			bad = 0;
			i++;
			printf("\n");
		}
		break;
		case 2:
		while(etudiants[i].numero != 0){
			find = find_note(etudiants[i], mat);
			if(find.id_etudiant == 0 || find.id_matiere == 0){ i++; continue; }

			print_etudiant(etudiants[i]);
			printf("|\t Note CC : %2.2f\t\t\t|\n", find.note_cc);
			printf("+-----------------------------------------------+\n");
			printf("|\t Note DS : %2.2f\t\t\t|\n", find.note_ds);
			printf("+-----------------------------------------------+\n");
			do{
				if(bad){
					printf("Incorrect la note de DS est comprise entre 0 et 20 ou 0 pour ne pas modifier : ");
				}else{
					bad = 1;
					printf("Entrer la note de DS : ");
				}
				val = scanf("%f", &note.note_ds);
				fflush(stdin);
				if(note.note_ds == 0) break;
			}while(note.note_ds > 20 || note.note_ds < 0 || val != 1);

			if(note.note_ds != 0)
				find.note_ds = note.note_ds;

			update_note(find, 1);
			bad = 0;
			i++;
			printf("\n");
		}
		break;
		case 3:
		while(etudiants[i].numero != 0){
			find = find_note(etudiants[i], mat);
			if(find.id_etudiant == 0 || find.id_matiere == 0){ i++; continue; }

			print_etudiant(etudiants[i]);
			printf("|\t Note CC : %2.2f\t\t\t|\n", find.note_cc);
			printf("+-----------------------------------------------+\n");
			printf("|\t Note DS : %2.2f\t\t\t|\n", find.note_ds);
			printf("+-----------------------------------------------+\n");
			do{
				if(bad){
					printf("Incorrect la note de CC est comprise entre 0 et 20 ou 0 pour ne pas modifier : ");
				}else{
					bad = 1;
					printf("Entrer la note de CC : ");
				}
				val = scanf("%f", &note.note_cc);
				fflush(stdin);
				if(note.note_cc == 0) break;
			}while(note.note_cc > 20 || note.note_cc < 0 || val != 1);

			if(note.note_cc != 0)
				find.note_cc = note.note_cc;

			bad = 0;
			do{
				if(bad){
					printf("Incorrect la note de DS est comprise entre 0 et 20 ou 0 pour ne pas modifier : ");
				}else{
					bad = 1;
					printf("Entrer la note de DS : ");
				}
				val = scanf("%f", &note.note_ds);
				fflush(stdin);
				if(note.note_ds == 0) break;
			}while(note.note_ds > 20 || note.note_ds < 0 || val != 1);

			if(note.note_ds != 0)
				find.note_ds = note.note_ds;

			update_note(find, 1);
			bad = 0;
			i++;
			printf("\n");
		}
		break;
		default:
		printf("Desole cette option n'est pas pris en charge.\n");
		exit(EXIT_FAILURE);
	}
}

void delate_note_etudiant_matier(Etudiant et, Matiere mat)
{
	system("cls");
	unsigned int has_not_note = -1;
	Note find = find_note(et, mat);
	printf("Suppression de la note de l'etudiant %s %s pour la matiere %s\n", et.nom, et.prenom, mat.libelle);
	if(has_not_note = (find.note_cc == 0 && find.note_ds == 0)){
		printf("Desole cette etudiants n'a pas de note pour cette matiere.\n");
		return;
	}
	print_etudiant(et);
	printf("|\t Note CC : %2.2f\t\t\t|\n", find.note_cc);
	printf("+-----------------------------------------------+\n");
	printf("|\t Note DS : %2.2f\t\t\t|\n", find.note_ds);
	printf("+-----------------------------------------------+\n");

	unsigned int entier = 6, bad = 0, val = 0;
	printf("Quel note voulez vous supprimer ?\n");
	printf("1. Note CC.\n");
	printf("2. Note DS.\n");
	printf("3. Les deux.\n");
	printf("0. Retour.\n");
	printf("Votre choix : ");
	scanf("%d", &entier);
	fflush(stdin);

	switch(entier){
		case 1:
		if(find.note_cc == 0){
			printf("Desole cette etudiants n'a pas de note CC\n");
			return;
		}
		printf("Voulez vous vraiment supprimer la note CC de cet etudiant ?[o/N] : ");
		scanf("%c", &val);
		fflush(stdin);

		if(val == 'o' || val == 'O'){
			find.note_cc = 0;
			update_note(find, 1);
			printf("La note a bien ete supprimer.\n");
		}else{
			printf("La note n'a pas ete supprimer.");
		}
		break;
		//
		case 2:
		if(find.note_ds == 0){
			printf("Desole cette etudiants n'a pas de note DS\n");
			return;
		}
		printf("Voulez vous vraiment supprimer la note DS de cet etudiant ?[o/N] : ");
		scanf("%c", &val);
		fflush(stdin);

		if(val == 'o' || val == 'O'){
			find.note_ds = 0;
			update_note(find, 1);
			printf("La note a bien ete supprimer.\n");
		}else{
			printf("La note n'a pas ete supprimer.");
		}
		break;
		//
		case 3:
		printf("Voulez vous vraiment supprimer la note CC de cet etudiant ?[o/N] : ");
		scanf("%c", &val);
		fflush(stdin);

		if(val == 'o' || val == 'O'){
			find.note_cc = 0;
			update_note(find, 0);
			printf("La note a bien ete supprimer.\n");
		}else{
			printf("La note n'a pas ete supprimer.");
		}
		break;
	}
}

void delate_note_etudiant_classe(Classe cl, Matiere mat, Etudiant * etudiants)
{
	
}

Note find_note(Etudiant et, Matiere mat)
{
	FILE *file = fopen("data/notes.csv", "r");
	Note note, null = {0,0,0.0,0.0};

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%d,%f,%f\n", &note.id_etudiant, &note.id_matiere, &note.note_cc, &note.note_ds);
		if(note.id_etudiant == et.numero && note.id_matiere == mat.reference){
			fclose(file);
			return note;
		}
	}while(!feof(file));
	fclose(file);
	return null;
}

Note find_note_with_primary(unsigned int numero, unsigned int reference)
{
	FILE *file = fopen("data/notes.csv", "r");
	Note note, null = {0,0,0.0,0.0};

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%d,%f,%f\n", &note.id_etudiant, &note.id_matiere, &note.note_cc, &note.note_ds);
		if(note.id_etudiant == numero && note.id_matiere == reference){
			fclose(file);
			return note;
		}
	}while(!feof(file));
	fclose(file);
	return null;
}

void save_note(Note note)
{
	FILE *file = fopen("data/notes.csv", "a");
	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(file, "%d,%d,%.2f,%.2f\n", note.id_etudiant, note.id_matiere, note.note_cc, note.note_ds);
	fclose(file);
}

/**
 * Fonction qui permet de supprimer ou de modifier une note
 * si edit_or_delate est 0 on supprime
 * si edit_or_delate est 1 on modifie
*/
void update_note(Note note, unsigned int edit_or_delate)
{
	FILE *file = fopen("data/notes.csv", "r"), *tmp = fopen("data/tmp.csv", "a");
	Note bin;

	if(file == NULL || tmp == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%d,%f,%f\n", &bin.id_etudiant, &bin.id_matiere, &bin.note_cc, &bin.note_ds);
		if(note.id_etudiant == bin.id_etudiant && note.id_matiere == bin.id_matiere){
			if(edit_or_delate)
				fprintf(tmp, "%d,%d,%.2f,%.2f\n", note.id_etudiant, note.id_matiere, note.note_cc, note.note_ds);
		}else{
			fprintf(tmp, "%d,%d,%.2f,%.2f\n", bin.id_etudiant, bin.id_matiere, bin.note_cc, bin.note_ds);
		}
	}while(!feof(file));

	fclose(file);
	fclose(tmp);

	remove("./data/notes.csv");
	rename("./data/tmp.csv", "./data/notes.csv");
}

unsigned int already_has_note(Etudiant et, Matiere mat)
{
	FILE *file = fopen("data/notes.csv", "r");
	Note note;

	if(file == NULL){
		printf("L'ouverture du fichier a echoue.\n");
		exit(EXIT_FAILURE);
	}

	do{
		fscanf(file, "%d,%d,%f,%f\n", &note.id_etudiant, &note.id_matiere, &note.note_cc, &note.note_ds);
		if(note.id_etudiant == et.numero && note.id_matiere == mat.reference){
			fclose(file);
			return 1;
		}
	}while(!feof(file));
	fclose(file);
	return 0;
}
