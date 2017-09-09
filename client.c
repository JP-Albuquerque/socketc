#include <stdio.h> //printf
#include <string.h> //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
 
int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	char server_reply[80];
	int number[10],i, protocol, aux = 1;
	char ip[16];
	char temp[10];

	while(aux){
		printf("Escolha qual protocolo usar: (1 = TCP , 2 = UDP)\n");
		scanf("%d", &protocol);
		
		if ( protocol != 1 && protocol != 2){
			printf("Escolha de protocolo inválida, por favor tente de novo.\n");
		} // fim if
		else {aux = 0;}

	} // fim while

	printf("Escolha um endereço de ip: \n");
	scanf("%s", ip);
 
	if( protocol == 1){ // Se o protocolo escolhido é TCP

		printf("Escreva a mensagem a ser enviada:\n");
		//gets(temp);
		scanf("%s", temp);

		//Create socket TCP
		sock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
		if (sock == -1) {
		 	printf("Could not create socket");
		 } // fim if

		puts("Socket created");

		server.sin_addr.s_addr = inet_addr(ip);
		server.sin_family = AF_INET;
		server.sin_port = htons( 8880 );
		 
		//Connect to remote server
		if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
			 perror("connect failed. Error");
			 return 1;
		 } // fim if
		 
		puts("Connected\n");
		 
		 
		if( send(sock , &temp, 10*sizeof(int) , 0) < 0) {
			puts("Send failed");
			return 1;
		}
		 
		 //Receive a reply from the server
		if( recv(sock , &server_reply , 10*sizeof(int), 0) < 0) {
			puts("recv failed");
			return;
		}
		 
		puts("Server reply :\n");
		puts(server_reply);
	} // fim if de TCP
	else if( protocol == 2){ // Se o protocolo escolhido é UDP

		printf("Escreva a mensagem a ser enviada:\n");
		scanf("%s", temp);

		if( strcmp(temp, "ping") == 0) {
			printf("pong\n");
		} // fim if

		//Create socket UDP
		sock = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP);
		if (sock == -1) {
		 	printf("Could not create socket");
		 } // fim if

		puts("Socket created");

		server.sin_addr.s_addr = inet_addr(ip);
		server.sin_family = AF_INET;
		server.sin_port = htons( 8880 );
		 
		//Connect to remote server
		//if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
		//	 perror("connect failed. Error");
		//	 return 1;
		//} // fim if
		 
		//puts("Connected\n");
		 
		 
		if( sendto(sock , &temp, 10*sizeof(int) , 0, (struct sockaddr *) &server, sizeof(server) ) < 0) {
			puts("Send failed");
			return 1;
		}
		 
		 //Receive a reply from the server
		if( recv(sock , &server_reply , 10*sizeof(int), 0) < 0) {
			puts("recv failed");
			return;
		}
		 
		puts("Server reply :\n");
		puts(server_reply);
	} // fim else if de UDP
	 
	close(sock);
	
	return 0;
}