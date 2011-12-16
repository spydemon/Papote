#ifndef ECRITURE_H
#define ECRITURE_H 

#include <ncurses.h>
#include "message.h" 
#include "msgsrecu.h"

int ecriture( WINDOW *, char * );
void maj_saisie_user( WINDOW *, char *, int); 
int envoi_message( WINDOW *user_message, WINDOW *liste_message , struct Chaine *, struct Lmsgs *, int); 

#endif
