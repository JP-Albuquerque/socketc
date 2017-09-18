#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //write
#include <time.h>
 
int main(int argc , char *argv[])
{
	int socket_desc_TCP, socket_desc_UDP , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char message[80] = { 0 };
	char response[80] = { 0 };
	int i, flag = 0;
	clock_t inicio, fim;
	
		//Create socket TCP
		socket_desc_TCP = socket(AF_INET , SOCK_STREAM , 0);
		if (socket_desc_TCP == -1) {
			printf("Could not create TCP socket");
		} // fim if

		puts("Socket TCP created");

		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons( 8880 );
		 
		//Bind TCP
		if( bind(socket_desc_TCP,(struct sockaddr *)&server , sizeof(server)) < 0) {
			//print the error message
			perror("bind TCP failed. Error");
			return 1;
		} // fim if

		puts("bind TCP done");

		//Listen
		listen(socket_desc_TCP , 5);
		 
		//Accept and incoming connection
		puts("Waiting for incoming connections...");
		c = sizeof(struct sockaddr_in);
		 
		//accept connection from an incoming client
		client_sock = accept(socket_desc_TCP, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0) {
			perror("accept failed");
			return 1;
		} // fim if

		puts("Connection accepted");
		 
		//Receive a message from client
		while( (read_size = recv(client_sock , &message , 10*sizeof(int), 0)) > 0 ) {
			// print client msg at server side
			puts("The string sent by client is: ");
			puts(message);

			if( (strcmp(message, "ping") == 0 || strcmp(message, "Ping") == 0)) {
			  	response[0] =  'p' ;
			  	response[1] =  'o' ;
			  	response[2] =  'n' ;
			  	response[3] =  'g' ;
			  	flag = 1;
			} // fim if

			if(flag == 0 && (strcmp(message, "marco") == 0 ||  strcmp(message, "Marco") == 0)) {
			  	response[0] =  'p' ;
			  	response[1] =  'o' ;
			  	response[2] =  'l' ;
			  	response[3] =  'o' ;
			  	flag = 1;
			} // fim if

			if( flag == 0 && (strcmp(message, "marco") != 0 ||  strcmp(message, "Marco") != 0 || strcmp(message, "ping") != 0 || strcmp(message, "Ping") != 0)) {
			  	  	response[0]  =  'B' ;
			  		response[1]  =  'a' ;
			  		response[2]  =  'd' ;
			  		response[3]  =  ' ' ;
			  		response[4]  =  'r' ;
			  		response[5]  =  'e' ;
			  		response[6]  =  'q' ;
			  		response[7]  =  'u' ;
			  		response[8]  =  'e' ;
			  		response[9]  =  's' ;
			  		response[10] =  't' ;
			} // fim if

			puts(response);
			 
			write(client_sock , &response, 10*sizeof(int));
			 
		} // fim while
		 
		if(read_size == 0) {
			puts("\nClient disconnected");
		} // fim if
		else if(read_size == -1) {
		 	perror("recv failed");
		} // fim else if
		 
		return 0;
} // fim função main