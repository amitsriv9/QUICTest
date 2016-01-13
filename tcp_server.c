#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

 #define SERVER_PORT 12888
   int main(int argc, char *argv[]){


    struct sockaddr_in  server;

    int        		server_socket, new_client;
    socklen_t  		server_size;

    char message_buffer[256], data_buffer[1024];
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct timeval tv;
    char  ignore[128], ip[INET6_ADDRSTRLEN+6]="", broadcast[INET6_ADDRSTRLEN], mask[INET6_ADDRSTRLEN+6];

     /*check for input parameters if missing warn and exit*/
    if(argc < 3){
     fprintf(stderr, "Need a file name and port number\n");  
     fprintf(stderr, "Format ./tcp_server <port> <file> \n");
     return 0;  
     }
     
//--------------------------------------------------------------------
    system("ifconfig|grep -A1 eth6|grep inet > ipaddr.txt");
 
    FILE *fileread;
    fileread = fopen("ipaddr.txt","r"); 
 
    if(fileread==NULL){
       fprintf(stderr, "Never mind, could not get the IP addr\n");
       exit(1); // return 0;
     }
    fscanf(fileread,"%s %s %s %s",ignore,ip,broadcast,mask);
    fclose(fileread);
    printf("IP address:%s, Broadcast: %s\n",ip, broadcast);
//--------------------------------------------------------------------
    /*support*/
    int bind_status, fdesc, sentbytes, totalsent=0;
    char filename[64];
    strncpy(filename, argv[2], sizeof(filename));

    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(argv[1]));
    //server.sin_addr.s_addr = inet_addr("192.168.81.128");
    server.sin_addr.s_addr = inet_addr(ip+5);

    server_size = sizeof(server);
    bind_status = bind(server_socket, (struct sockaddr*) &server, server_size);
    if (bind_status<0){
       printf("Bind failed\n"); exit(1);
    }
    //connect(client_socket, (struct sockaddr*)client, client_size);
    listen(server_socket, 5);

    new_client = accept(server_socket, (struct sockaddr*)&server, &server_size);
    printf("accepted a new client %d\n", new_client);

    int fread;
    fdesc = open(filename , O_RDONLY); 

    if(fdesc < 0){  // deaking with failed file open we basically close and exit
        memset(message_buffer, 0, sizeof(message_buffer));
        sprintf(message_buffer, "Unable to open file for sending");
        fprintf(stderr, "Unable to open file for sending\n");
        sentbytes = send (new_client, message_buffer, strlen(message_buffer),0);
        exit(1);
    }

    while(1){
        fread = read(fdesc, data_buffer, 1024);
        if(fread == 0){
            printf("nothing more to send\n");
            close(fdesc);
	    memset(message_buffer, 0, sizeof(message_buffer));
            sprintf(message_buffer, "END");
    	    sentbytes = send(new_client, message_buffer, strlen(message_buffer), 0);
            close(server_socket);
	    break;
        } 
    	sentbytes = send(new_client, data_buffer, fread, 0);
    	totalsent += sentbytes;
    	sentbytes=0;
	memset(data_buffer, 0 , sizeof(data_buffer));
    }
    printf("file transfer complete %d\n", totalsent);
    return 0;
    }    
