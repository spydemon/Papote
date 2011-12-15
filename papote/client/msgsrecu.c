#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "msgsrecu.h"

struct Lmsgs *msgs_init(int tL, int tM) {
	struct Lmsgs *lmsgs = malloc(sizeof(struct Lmsgs));
	lmsgs->tailleMaxListe = tL;
	lmsgs->tailleMaxMessage = tM;
	lmsgs->tailleEnCours = 0;
	lmsgs->premierMessage = NULL;
	return lmsgs;
}

void msgsrecu_ecriture(WINDOW *fenetre, struct Chaine *texte, struct Lmsgs *liste_msgs) {
	//Si l'utilisateur veut envoyer un texte vide, on ne le laisse pas faire
	if (texte->octetEnCours == 0) 
		return ;
	struct Msgs *nouveau = malloc(sizeof(struct Msgs));
	//On doit copier la valeur du message parce que le contenu de texte sera effacé !
	nouveau->message = malloc(strlen(texte->phrase)+1);
	strcpy(nouveau->message, texte->phrase);
	nouveau->suivant = liste_msgs->premierMessage;

	liste_msgs->premierMessage = nouveau;
	msgsrecu_troncature(fenetre, liste_msgs);
	msgsrecu_affichage(fenetre, liste_msgs);
}

void msgsrecu_affichage(WINDOW *fenetre, struct Lmsgs *liste_msgs) {
//	if (liste_msgs->premierMessage == NULL)
//		exit(1);
	int x,y;
	getmaxyx(fenetre, y, x);
	struct Msgs *enCours = liste_msgs->premierMessage;

	//On redesine la fenêtre pour ne pas laisser les traces des enciens messages.
	wclear(fenetre);
	box(fenetre, 0, 0);
	while (enCours != NULL) {
		mvwprintw(fenetre, y-- - 2, 1, enCours->message);
		enCours = enCours->suivant;
	}

	wrefresh(fenetre);
}

void msgsrecu_troncature(WINDOW *fenetre, struct Lmsgs *liste_msgs) {
	int x, y, j=0;
	getmaxyx(fenetre, y, x);
	if (liste_msgs->premierMessage == NULL || liste_msgs->premierMessage->suivant == NULL )
		return ;
	struct Msgs *enCours = liste_msgs->premierMessage;

	
	while (enCours->suivant->suivant != NULL) {
		enCours = enCours->suivant;
		j++;
	}

	if (j == y - 3) {
		free(enCours->suivant);
		enCours->suivant = NULL;
	}
}


