#ifndef MESSAGE_H
#define MESSAGE_H 

#include "ncurses.h" 

#define MAX_CHARS 40

struct Chaine {
	char *phrase;
	int octetEnCours;
	int maxChars;
	WINDOW *affichage;
};

void msg_reinitialisation_phrase(struct Chaine *); 
struct Chaine *msg_init(WINDOW *, int );
int msg_ajouter_lettre(struct Chaine *, int);
int msg_nbre_elem (char *);
int msg_backspace(struct Chaine *);

#endif
