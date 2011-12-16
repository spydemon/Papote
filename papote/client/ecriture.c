#include <ncurses.h>
#include <string.h>
#include <sys/socket.h>
#include "ecriture.h" 
#include "message.h"
#include "msgsrecu.h"

void ec_purge(WINDOW *fenetre, int tailleMax) {
	//Effassage des anciens carractères 
	for (int j = 1; j <= tailleMax; j++)
		mvwprintw(fenetre, 1, j, " ");
}

void maj_saisie_user(WINDOW *fenetre, char *texte, int tailleMax) {
	ec_purge(fenetre, tailleMax);
	mvwprintw(fenetre, 1, 1, "> %s", texte);
	wrefresh(fenetre);
}

int envoi_message(WINDOW *message_user, WINDOW *liste_message, struct Chaine *chaine, struct Lmsgs *liste_messages, int sockfd) {
	send(sockfd,chaine->phrase,(strlen(chaine->phrase)+1),0 );
	msgsrecu_ecriture(liste_message, chaine, liste_messages);
	msg_reinitialisation_phrase(chaine);	
	ec_purge(message_user, chaine->maxChars);
	wrefresh(message_user);
	wrefresh(liste_message);
	return 1;
}

int ecriture ( WINDOW *fenetre, char *texte ) {
	mvwprintw(fenetre, 1, 1, " >");
	wrefresh(fenetre);
	return 1;
}
