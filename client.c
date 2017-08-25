#include<stdio.h> //printf
#include<string.h> //strlen
#include<sys/socket.h> //socket
#include<arpa/inet.h> //inet_addr
 
int main(int argc , char *argv[])
{
 int sock;
 struct sockaddr_in server;
 int  server_reply[10];
 int number[10],i,temp;
 //Create socket
 sock = socket(AF_INET , SOCK_STREAM , 0);
 if (sock == -1)
 {
 printf("Could not create socket");
 }
 puts("Socket created");
 
 server.sin_addr.s_addr = inet_addr("127.0.0.1");
 server.sin_family = AF_INET;
 server.sin_port = htons( 8880 );
 
 //Connect to remote server
 if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
 {
 perror("connect failed. Error");
 return 1;
 }
 
 puts("Connected\n");
 
 printf("enter 10 number");
 for (i=0;i<10;i++)
 {
 scanf("%d",&temp);
 number[i]= temp;
 }
 
 if( send(sock , &number, 10*sizeof(int) , 0) < 0)
 {
 puts("Send failed");
 return 1;
 }
 
 //Receive a reply from the server
 if( recv(sock , &server_reply , 10*sizeof(int), 0) < 0)
 {
 puts("recv failed");
 return;
 }
 
 puts("Server reply :\n");
 for(i=0;i<10;i++)
 {
 printf("%d\n",server_reply[i]);
 }
 close(sock);
 return 0;
}