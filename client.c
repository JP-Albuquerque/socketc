#include <stdio.h> //printf
#include <string.h> //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <time.h>
 
int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server, client;
	char server_reply[80];
	int number[10],i, protocol, aux = 1, slen = sizeof(client);
	double numOfPackets = 0;
	int sumOfTime = 0;
	float *v;
	char ip[16];
	char temp[10];
	clock_t inicio, fim;

	while(aux){
		printf("Escolha qual protocolo usar: (1 = TCP , 2 = UDP)\n");
		scanf("%d", &protocol);
		
		if ( protocol != 1 && protocol != 2){
			printf("Escolha de protocolo inválida, por favor tente de novo.\n");
		} // fim if
		else {aux = 0;}

	} // fim while

	printf("\nEscolha um endereço de ip: ");
	scanf("%s", ip);

	printf("\nQuantos pacotes devem ser enviados: ");
	scanf("%lf", &numOfPackets);

	v = (int *) malloc(numOfPackets * sizeof(int));
 
	if( protocol == 1){ // Se o protocolo escolhido é TCP

		printf("\nEscreva a mensagem a ser enviada: ");
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
		
		for( i = 1 ; i <= numOfPackets; i++ ){
			inicio = clock();

			if( send(sock , &temp, 10*sizeof(int) , 0) < 0) {
				puts("Send failed");
				return 1;
			} // fim if
			 
			 //Receive a reply from the server
			if( recv(sock , &server_reply , 10*sizeof(int), 0) < 0) {
				puts("recv failed");
				return;
			} // fim if
			
			fim = clock();
			v[i] = (fim - inicio);
			sumOfTime = sumOfTime + (fim - inicio);

		} // fim for

		bubble_sort(v, i);
		 
		puts("Server reply :\n");
		puts(server_reply);
		
		printf("Tempo mínimo: %.2f milissegundos.\n",v[1]);
		printf("Tempo médio: %0.2f milissegundos.\n",sumOfTime/numOfPackets);
		printf("Tempo máximo: %0.2f milissegundos.\n",v[i-1]);
	} // fim if de TCP
	else if( protocol == 2){ // Se o protocolo escolhido é UDP

		printf("Escreva a mensagem a ser enviada:\n");
		scanf("%s", temp);

		//Create socket UDP
		sock = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP);
		if (sock == -1) {
		 	printf("Could not create socket");
		 } // fim if

		puts("Socket UDP created");

		server.sin_addr.s_addr = inet_addr(ip);
		server.sin_family = AF_INET;
		server.sin_port = htons( 8880 );
		 
		for( i = 1 ; i <= numOfPackets; i++ ){
			inicio = clock();

			if( sendto(sock , &temp, 10*sizeof(int) , 0, (struct sockaddr *) &server, sizeof(client) ) < 0) {
				puts("Send failed");
				return 1;
			}
			 
			 //Receive a reply from the server
			if( recvfrom(sock , &server_reply , 10*sizeof(int), 0, (struct sockaddr *)&server, &slen) < 0) {
				puts("recv failed");
				return;
			}
			
			fim = clock();
			v[i] = (fim - inicio);
			sumOfTime = sumOfTime + (fim - inicio);
		} // fim for

		bubble_sort(v, i);
		 
		puts("Server reply :\n");
		puts(server_reply);
		
		printf("Tempo mínimo: %.2f milissegundos.\n",v[1]);
		printf("Tempo médio: %0.2f milissegundos.\n",sumOfTime/numOfPackets);
		printf("Tempo máximo: %0.2f milissegundos.\n",v[i-1]);
	} // fim else if de UDP
	 
	close(sock);

	free(v);
	
	return 0;
} // fim função main

void bubble_sort(int list[], int n)
{
	 int c, d, t;
	 
	for (c = 0 ; c < ( n - 1 ); c++) {
		for (d = 0 ; d < n - c - 1; d++) {
			if (list[d] > list[d+1]) {
			/* Swapping */
			t = list[d];
			list[d] = list[d+1];
			list[d+1] = t;
			} // fim if
		} // fim for interno
	} // fim for externo
} // fim função bubble_sort