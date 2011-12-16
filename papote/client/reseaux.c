//Inclusions réseaux 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/wait.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "reseaux.h"
#include "msgsrecu.h"
#include "ecriture.h"

void reseaux_veilleReception(int valretour, int *status, int *sockfd, char * buf, WINDOW *fenetre, struct Lmsgs *liste_m) {
		wprintw(fenetre, "RALALLALALALAAAAAAAAAAA");
    while(!waitpid(valretour, status, WNOHANG))
    {
		int val;
		wrefresh(fenetre);

		val = recv(*sockfd, buf, 1024, 0);
		/**
		if((val=recv(sockfd, buf, 1024, 0))==-1){
	   //perror("erreur de reception -> ");
	 	  exit(-3);
	 	}
		 // affichage de la chaine de caracteres recue
	 	if(val!=0){
			struct Chaine message;
			message.phrase = malloc(sizeof(char) * strlen(buf));
			strcpy(message.phrase, buf);
			msgsrecu_ecriture(fenetre, &message, liste_m);
	    //printf("Nombre d'octet reçu : %d\n",val-1);
	    //printf("Message reçu : %s\n", buf);
	 	}
		**/
    }
}
