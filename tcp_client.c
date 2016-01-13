#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

 #define SERVER_PORT 12888
   int main(){


    struct sockaddr_in  client;

    int        		client_socket;
    socklen_t  		client_size;

    char message_buffer[256], data_buffer[1024];
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct timeval tv;


    /*support*/
    int connect_status, fdesc, recvdbytes, totalrecvd=0, totalsent, wrote;
    char filename[] = "clientfile";

    client.sin_family=AF_INET;
    client.sin_port=htons(SERVER_PORT);
    client.sin_addr.s_addr = inet_addr("192.168.81.128");

    client_size = sizeof(client);
    connect_status = connect(client_socket, (struct sockaddr*)&client, client_size);
    if (connect_status<0){
       printf("getting out\n"); exit(1);
    }

    
    fdesc = open(filename, O_WRONLY);
   
    if(fdesc <  0){
        memset(message_buffer, 0, sizeof(message_buffer));
        sprintf(message_buffer, "Unable to open file for writing");
        fprintf(stderr, "Unable to open file for writing\n");
        totalsent = send (client_socket, message_buffer, strlen(message_buffer),0);
        close(fdesc);
        close(client_socket);
        exit(1);
    }

    while(1){
	recvdbytes = 0;
	memset(data_buffer, 0, sizeof(data_buffer));
    	recvdbytes = recv(client_socket, data_buffer, 1024, 0);
	if(recvdbytes > 5){
            wrote = write(fdesc, data_buffer, recvdbytes);
    	    totalrecvd += recvdbytes;
    	    recvdbytes = 0;
        }
	else{
                 close(fdesc);
                 close(client_socket);
	         break;
	      /*
	       strncpy(message_buffer, data_buffer,recvdbytes);
	       printf("%s\n", message_buffer);
	       if(!strncmp(message_buffer,"ENDOFFILE",9)){
	         printf("Found the file end msg\n");
                 close(fdesc);
                 close(client_socket);
	         break;
	       }
	       else{
                 wrote = write(fdesc, data_buffer, recvdbytes);
    	         totalrecvd += recvdbytes;
	         printf("Wrote %d bytes to the file\n",recvdbytes);
	       } 
	      */
	     }
    }
    printf("File transfer complete %d\n", totalrecvd);
    return 0;
    }    
