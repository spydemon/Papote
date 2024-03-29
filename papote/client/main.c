#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

//Inclusions réseaux 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//Inclusions projet
#include "ecriture.h"
#include "message.h"
#include "msgsrecu.h"
#include "reseaux.h"

//typedef int SOCKET;
#define SOCKET_ERROR -1
#define HAUTEUR_SAISIE_USER 3 
#define LARGEUR_LISTE_USER 25 
#define MARGE_HAUTE 2
#define TAILLE_MAX_MESSAGE 50

int main(int argc, char **argv) {
	//Vérification de la saisie du port et de l'adresse id
	if (argc != 3) {
		printf("Utilisation : %s <adresse ip> <num port>\n", argv[0]);
		exit(1);
	}

	//Vérification de l'adresse ip
	in_addr_t ip_serveur = inet_addr(argv[1]);
	if (!ip_serveur) {
		printf("Erreur : l'adresse ip du serveur est invalide.\n");
		exit(1);
	}

	//Vérification du port
	int port_no = atoi(argv[2]);
	if (port_no < 1 || port_no > 65535) {
		printf("Le paramètre n'est pas un numéro de port.\n");
		exit(1);
	}

  int i=0;
  int sockfd;                      // descripteur de socket
  char str[1024]; 		   //chaine de caractere envoyer au serveur 
  char buf[1024]; 		   //buffer pour la reception des messages
  int status;
  struct sockaddr_in dest;         // structure d'adresse qui contiendra les parametres reseaux du destinataire

  	// creation de la socket
  	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//Ititialisation connexion
	struct sockaddr_in addr;
	dest.sin_family = AF_INET;
	//dest.sin_port = port_no;
	//dest.sin_addr.s_addr = ip_serveur;
	memset(&(dest.sin_zero), '\0', 8);

  	// famille d'adresse
  	dest.sin_family = AF_INET;

  // adresse IPv4 du destinataire
  inet_aton(argv[1] , &(dest.sin_addr));

  // port du destinataire
  dest.sin_port = htons((uint16_t) port_no);

  //connection au receiver
  connect(sockfd, (struct sockaddr *)&dest, sizeof(struct sockaddr) );

	//1er paquet
  char *user = "Spydemon";
  send(sockfd,user,(strlen(user)+1),0 );

	//Initialisation de ncurses
	WINDOW *stdsrc = initscr();			//Allocation des fonctions utilisées
	cbreak();			//Interpértation automatique des signaux (SIGTERM)
	keypad(stdsrc, TRUE); //Utilisations des "touches spéciaux" (Flèches dirrectionnelles)
//	if (has_color()) 
//		start_color();		//Utilisation des couleurs si le terminal le suporte

	noecho();				//Afficher à l'écran le texte qu'entrera l'utilisateur (à desactiver pour les mdp par exemple)

	//CRÉATION DES FENÊTRES DU PROGRAMME 
	WINDOW *saisie_user; 		//Fenêtre dans la quelle l'utilisateur entrera son texte. 
	WINDOW *liste_msg; 			//Fenêtre d'affichage des messages déjà envoyés. 
	WINDOW *liste_user;			//Fenêtre de la liste des utilisateurs connectés au chat.

	refresh();
	//INITIALISATION DES FENÊTRE 
		//Celle de l'utilisateur sera en bas, sur toute la longueur de la console.
		saisie_user = newwin(HAUTEUR_SAISIE_USER, COLS, LINES - HAUTEUR_SAISIE_USER, 0);
		box(saisie_user, 0, 0); 
		wrefresh(saisie_user);
		//Celle de la liste des utilisateurs connecté sera sur le côté droit. 
		liste_user = newwin(LINES - HAUTEUR_SAISIE_USER - MARGE_HAUTE, LARGEUR_LISTE_USER, MARGE_HAUTE, COLS - LARGEUR_LISTE_USER);
		box(liste_user, 0, 0);
		wrefresh(liste_user);
		//Celle contenant les messages envoyés prendra le reste de la place. 
		liste_msg = newwin(LINES - HAUTEUR_SAISIE_USER - MARGE_HAUTE, COLS - LARGEUR_LISTE_USER, MARGE_HAUTE, 0);
		box(liste_msg, 0, 0);
		wrefresh(liste_msg);
	
	int fin = 0;
	int c;
	struct Chaine *chaine = msg_init(saisie_user, 50);
	struct Lmsgs *lmsgs = msgs_init(TAILLE_MAX_MESSAGE, LINES - HAUTEUR_SAISIE_USER - MARGE_HAUTE - 2);
	
	//Fork du programme pour surveiller les réceptions
	int forky = fork();
	if (forky == 0) {
		reseaux_veilleReception(forky, &status, &sockfd, buf, liste_msg, lmsgs);
		return 1;
	}

	else {
	//ecriture(saisie_user);
	while (!fin) {
		//c = wgetch(saisie_user);
		c = getch();
		switch(c) {
			case KEY_DOWN:
				fin = 1;
				break;
			//Si l'utilisateur entre un backspace, le dernier carractère est suprimmé. 
			case 263:
				msg_backspace(chaine);
			//	mvwprintw(saisie_user, 1, 1, "! %s", chaine->phrase);
			//	wrefresh(saisie_user);
				maj_saisie_user(saisie_user, chaine->phrase, TAILLE_MAX_MESSAGE); 
				break;
			case '\n':
				//ecriture(saisie_user);
				envoi_message(saisie_user, liste_msg, chaine, lmsgs, sockfd);
				break;
		}
		//Si l'utilisateur marque un carractère lisible, celui-ci sera utilisé pour construire une phrase qui sera envoyée ou traitée comme commande.
		if (c >= 32 && c <= 126) {
			msg_ajouter_lettre(chaine, c);
			maj_saisie_user(saisie_user, chaine->phrase, TAILLE_MAX_MESSAGE); 
			//mvwprintw(saisie_user, 1, 1, "> %s", chaine->phrase);
			//wrefresh(saisie_user);
		}


		mvwprintw(liste_user, 2, 2, "%d", c);	
		wrefresh(liste_user);
	}
	endwin();
	free(chaine);
	}

	//wprintw(liste_msg, "Un texte");
	//wrefresh(liste_msg);

	//char ligne[40];
	//getstr(ligne);

	/**
	mvwprintw(saisie_user, 1, 1, " > ");
	wrefresh(saisie_user);

	char ligne[40];
	getstr(ligne);

	getch();
	//printw("Écris ! ");
	//char ligne[50];
	getstr(ligne);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	attron(A_UNDERLINE | A_BLINK);
	printw("\n%s", ligne);
	//mvchgat(1, 0, -1, A_BLINK, 1, NULL);
	refresh();
	//int l = getch();
	**/

	//getch();

	return 0;

}
