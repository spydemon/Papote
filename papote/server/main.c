#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Inclusions réseaux 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef int SOCKET;

#define SOCKET_ERROR -1

int main(int argc, char **argv) {
	int port_no;

	//Initialisation de la socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); 
	if (sock == SOCKET_ERROR) {
		printf("Érreur de déclaration de la socket\n");
		exit(1);
	}

	//Vérification de la saisie du numéro de port sur le quel le serveur doit écouter 
	if (argc != 2 ) {
		printf("Utilisation : %s <num port>\n", argv[0]);
		exit(1);
	}

	//Véritication que le paramètre soit bien le numéro d'un port
	port_no = atoi(argv[1]); 
	if (port_no < 1 || port_no > 65535) {
		printf("Le paramètre n'est pas un numéro de port.\n");
		exit(1);
	}

	//Initialisation connexion
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = port_no;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	memset(&(addr.sin_zero), '\0', 8);

	if(!bind(sock, (struct sockaddr *)&addr, sizeof(addr))) {
		printf("Erreur de bind du socket\n");
		exit(1);
	}

	//Écoute sur le port serveur l'arrivée de nouveau clients 
	while (1) {
		if (listen(sock, 1)) 
			printf("Nous somme bien dans la boucle");
	}
		

	return 0;
}
