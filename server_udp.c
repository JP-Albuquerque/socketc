#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //write
 
int main(int argc , char *argv[])
{
	int socket_desc_TCP, socket_desc_UDP , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char message[80] = { 0 };
	char response[80] = { 0 };
	int i, flag = 0, slen = sizeof(client);

	// create socket UDP
	socket_desc_UDP = socket(AF_INET , SOCK_DGRAM , 0);
	if (socket_desc_UDP == -1) {
	 	printf("Could not create UDP socket");
	} // fim if

	puts("Socket UDP created");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8880 );

	// bind UDP
	if ( bind(socket_desc_UDP,(struct sockaddr *)&server, sizeof(server)) < 0) {
	  	// print the error message
	   	perror("bind UDP failed. Error");
	   	return 1;
	}
	
	puts("bind UDP done");

	//Listen
	//listen(socket_desc_UDP , 5);

	while( (read_size = recvfrom(socket_desc_UDP , &message , 10*sizeof(int), 0, (struct sockaddr *)&client, &slen)) > 0 ) {
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
		
		if( sendto(socket_desc_UDP , &response, 10*sizeof(int) , 0, (struct sockaddr *) &client, sizeof(server) ) < 0) {
			puts("Send failed");
			return 1;
		} // fim if	 
		for( i = 1 ; i <= 80; i++ ){
			response[i] = 0;

			if (i==79) flag=0;
		}
	} // fim while

	//for( i = 1 ; i <= 80; i++ ){
	//	response[i] = 0;
	//}
	 
	return 0;
} // fim função main