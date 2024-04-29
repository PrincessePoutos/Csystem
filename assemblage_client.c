#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <netdb.h>

#define PORT 8088
#define SIZE_MSG 300


int main(int argc, char const* argv[]) {

	int i;
	int client_fd;
	struct sockaddr_in serv_addr;
	int randtime = rand()%3;
	char buffer[SIZE_MSG] = { 0 };
	char fruitList[500] = {0};

//	printf("argv[1] = %s\n", argv[1]);

	while (1) {


//_______________________PREP_SOCKET_____________________________

		if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			printf("\n Socket creation error \n");
			return -1;
		}

			//on crée une variable de type struct sockaddr_in et on donne à sa variable sin_port
			//la valeur de retour de la fonction htons() avec pour argument PORT, définit plus haut
			//la fonction htons() convertit l'unsigned short integer hostshort de l'ordre de byte hôte
			//à l'ordre de byte réseau. ??? 
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);

			//la fonction inet_pton permet de convertir une chaine de caractères source en adresse réseau (en texte binaire).
			//on lui passe en argument AF_INET qui signifie qu'on convertit la chaine de caractère en adresse IPv4 
//		if (inet_pton(AF_INET, "192.168.30.30", &serv_addr.sin_addr) <= 0) {
		if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
			printf(
				"\nInvalid address/ Address not supported \n");
			return -1;
		}

			//on utilise la fonction connect() pour établir la connexion entre le socket client et le socket server
		if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		        printf("\nConnection Failed \n");
	        	return -1;
		}


//________________________GET_CLIENT_FQDN___________________________

		struct addrinfo hints, *info, *p;
		int gai_result;

		char hostname[1024];
		char fqdn[1024];
		hostname[1023] = '\0';
		gethostname(hostname, 1023);

		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC; /*either IPV4 or IPV6*/
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_CANONNAME;

		if ((gai_result = getaddrinfo(hostname, "http", &hints, &info)) != 0) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_result));
			exit(1);
		}

		for(p = info; p != NULL; p = p->ai_next) {
//			printf("hostname: %s\n", p->ai_canonname);
			sprintf(fqdn, "helo %s", p->ai_canonname);
//			printf("FQDN = %s\n", fqdn);
		}


	//___________________SEND_CLIENT_FQDN_______________________

		send(client_fd, fqdn, SIZE_MSG, 0);
		recv(client_fd, buffer, SIZE_MSG, 0);
		printf("\n%s\n", buffer);

		freeaddrinfo(info);

//		printf("Connexion...\n");
		sleep(randtime);

			
		char *oldfruit;
		char *fruitptr;
		int nb;
		char requete[50];
		char rcvListRequest[50];
		char sendListRequest[50];
		char *fruitArray[50];
		fruitptr=(char *)malloc(3);
		oldfruit=(char *)malloc(3);
		int choix;

//__________________________USER_CHOICE_______________________________
//_________________________CLIENT_REQUESTS____________________________

		printf("Quelle requête souhaitez-vous envoyer :\n1) sendfruit\n2) rcvfruit\n3) chngfruit\n4) howmany\n5) rcvlist\n6) sendlist\n\nPress 7 to end the connexion\n");
		scanf("%d", &choix);


		if (choix == 1) {

			printf("Entrez le fruit que vous souhaitez envoyer : ");
			scanf(" %s", fruitptr);
			printf("Entrez la quantité de fruits a envoyer : ");
			scanf("%d", &nb);
				
			sprintf(requete, "sendfruit %s %d", fruitptr, nb);
			printf("%s will be send to server...\n", requete);

			send(client_fd, requete, SIZE_MSG, 0);
			recv(client_fd, buffer, SIZE_MSG, 0);
			printf("%s\n", buffer);


		} else if (choix == 2) {
			printf("Enter the name fruit you want to send : ");
			scanf("%s", fruitptr);

			sprintf(requete, "rcvfruit %s", fruitptr);
			printf("%s will be send to server...\n", requete);
			send(client_fd, requete, SIZE_MSG, 0);
			recv(client_fd, buffer, SIZE_MSG, 0);
			printf("%s\n", buffer);


		} else if (choix == 3) {
			printf("Enter the name of the new fruit : ");
			scanf("%s", fruitptr);
			printf("Enter the name of the fruit to replace : ");
			scanf("%s", oldfruit);

			sprintf(requete, "chngfruit %s %s", fruitptr, oldfruit);
			printf("%s will be send to server...\n", requete);

			send(client_fd, requete, SIZE_MSG, 0);
			recv(client_fd, buffer, SIZE_MSG, 0);
			printf("%s\n", buffer);

		} else if (choix == 4) {
			strcpy(requete, "howmany");
			send(client_fd, requete, SIZE_MSG, 0);
			printf("%s send\n", requete);
			recv(client_fd, buffer, SIZE_MSG, 0);
			printf("%s\n", buffer);

		} else if (choix == 5) {
			strcpy(rcvListRequest, "rcvlist");

			send(client_fd, rcvListRequest, SIZE_MSG, 0);

			strcpy(fruitList, "sendlist \n");

			do {
//				printf("buffer avant recv = |%s|\n", buffer);
				recv(client_fd, buffer, SIZE_MSG, 0);
//				printf("buffer après recv = |%s| adresse de buffer %p\n", buffer, &buffer);
				strcat(fruitList, buffer);
			}

			while (strcmp(buffer, "ENDOFLIST") != 0);

			printf("%s\n", fruitList);

		} else if (choix == 6) {

		//	printf("fruitList in choix 6 = %s\n", fruitList);
		//	printf("taille de la liste : %d\n", strlen(fruitList));

			if (strlen(fruitList) == 0) {
				printf("Client does not have the list. Please ask list to server first.\n");

			} else {
				printf("Sendlist request will be send to server...\n");
				send(client_fd, fruitList, SIZE_MSG, 0);
//				printf("%s\n", fruitList);

			}


		} else if (choix == 7){
			printf("End of connexion...\n");
			close(client_fd);
			exit(EXIT_SUCCESS);
			return EXIT_SUCCESS;


		} else {
			printf("\nPlease select a choice from 1 to 7\n");

		}

//		printf("before memset, buffer = %s\n", buffer);

	//_________________FLUSH_BUFFER__________________

		memset(buffer, 0, strlen(buffer));

	//__________________FLUSH_STDIN__________________

		unsigned long* tmpstdin = (unsigned long*)stdin;
		unsigned long* oldbuf = (unsigned long*)*(tmpstdin+4);
		free((void*)oldbuf);
		*tmpstdin=(unsigned long)0xfbad2088;
		tmpstdin+=1;
		memset(tmpstdin,'\x00',64);

//		printf("after memset, buffer = %s\n", buffer);

	}

//___________________________________CLOSE_SOCKET__________________________________________

	close(client_fd);

	return 0;
}
