#include <ncurses.h>
#include <stdlib.h>
#include "message.h" 

/*******
  INITIALISATION DE Chaine 
  Le but de cette structure est de contenir l'intégrité du message à envoyer, pendant son écriture. 
*******/

struct Chaine * msg_init(WINDOW *f, int nbr) {
	struct Chaine *c = malloc(sizeof(struct Chaine));
	//c->octetEnCours = 0;
	c->maxChars = nbr;
	c->affichage = f;
	c->phrase = malloc(sizeof(char)*(nbr+1));
	//phrase contient la taille max de carractère + 1 pour s'assurer que le dernier carractère soit bien toujours un EOF
	msg_reinitialisation_phrase(c);
	return c;
}

int msg_ajouter_lettre(struct Chaine *chaine, int lettre) {
	//Vérification de si la chaine n'est pas pleine
	if (msg_nbre_elem(chaine->phrase) == chaine->maxChars)
		return 0;
	//Si non, on rajoute le nouveau carractère
	chaine->phrase[chaine->octetEnCours] = (char) lettre;
	chaine->octetEnCours++;
	return 1;
}

void msg_reinitialisation_phrase(struct Chaine *chaine) {
//void msg_reinitialisation_phrase(char * tab, int valeurs) {
	for (int j = 0; j <= chaine->maxChars; j++)
		chaine->phrase[j] = '\0';
	chaine->octetEnCours = 0;
}

int msg_nbre_elem(char * tab) {
	int nbr = 0;
	while (tab[nbr] != '\0')
		nbr++;
	return nbr;
}

int msg_backspace(struct Chaine *chaine) {
	if (msg_nbre_elem(chaine->phrase) == 0) 
		return 0;
	chaine->octetEnCours--;
	chaine->phrase[chaine->octetEnCours] = '\0';
	return 1;
}

//struct Chaine {
//	char phrase[MAX_CHARS];
//	int octetEnCours;
//	WINDOWS *affichage;
//};

//Chaine msg_init(WINDOW *, int );
//int msg_ajouter_lettre(int);

