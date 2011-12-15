#ifndef MSGSRECU_H
#define MSGSRECU_H

#include <ncurses.h>
#include "message.h"

struct Msgs {
	char *message;
	struct Msgs *suivant;
};

struct Lmsgs {
	int tailleMaxListe;
	int tailleMaxMessage;
	int tailleEnCours;
	struct Msgs *premierMessage;
};

struct Lmsgs *msgs_init(int, int);
void msgsrecu_affichage(WINDOW *, struct Lmsgs *);
void msgsrecu_ecriture(WINDOW *, struct Chaine *, struct Lmsgs *); 
void msgsrecu_troncature(WINDOW *, struct Lmsgs *);

#endif
