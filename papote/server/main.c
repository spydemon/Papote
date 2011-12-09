#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
	//Vérification de l'intégrité des paramètres à l'appel du programme
	if (argc != 2 ) {
		printf("Utilisation : %s <num port>\n", argv[0]);
		exit(1);
	}

	return 0;
}
