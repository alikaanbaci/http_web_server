/*
 * project and file name: src, web_server.c
 * created date: Sunday August 4th 2019
 * author: alikaanbaci
 */
/**
 * Create socket with socket() system call
 * Bind socket with an address using bind() system call
 * Address = hostname + portname
 * Listen for connection with listen() system call
 * Accept a connection with accept() system call
 **/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <arpa/inet.h>

/**
 * sys/types.h contains definitions of number of data types used in system calls
 **/
#include<sys/types.h>
/**
 * sys/socket.h contains definitions of structures needed for sockets
 **/
#include<sys/socket.h>
/**
 * netinet/sin.h contains constants and structures needed for internet domain addesses
 **/
#include<netinet/in.h>
#include<string.h>

#include "read_file.h"
#include "logger.h"


int main(int argc, char *argv[]){
  int socket_file_descriptor;
  int accept_file_descriptor;
  int port_number;
  int client_length;
  int n;
  
  char buffer[1000];
  
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  if(argc < 2){
    log_error("Error port number was not provided");
    exit(EXIT_FAILURE);
  }

  socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  
  port_number = atoi(argv[1]);

  /* internet domain */
  server_address.sin_family = AF_INET;
  /* port number */
  server_address.sin_port = htons(port_number);
  /* ip */
  server_address.sin_addr.s_addr = INADDR_ANY;
  
  if(bind(socket_file_descriptor, (struct sockaddr *) &server_address, sizeof(server_address)) < 0){
    log_error("Cannot bind port %d, address already in use", port_number);
    exit(EXIT_FAILURE);
  }
  
  listen(socket_file_descriptor, 5);
  
  log_info("Started to listeining on %u:%d", INADDR_ANY, port_number);
  
  client_length = sizeof(client_address);
    
	while(1){
		accept_file_descriptor = accept(socket_file_descriptor, (struct sockaddr *) &client_address, &client_length);
		char str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(client_address.sin_addr.s_addr), str, INET_ADDRSTRLEN);
		log_info("Client %s:%u\n", str, client_address.sin_port);
		
		if(accept_file_descriptor < 0){
		  log_error("Error while accept");
		  exit(EXIT_FAILURE);
		}
		
		bzero(buffer, 1000);

		n = read(accept_file_descriptor, buffer, 1000);

		if(n < 0){
		  log_error("Error reading from socket");
		}

		printf("Received a connection : \n%s", buffer);

        
		char* header = "HTTP/1.1 200 OK\n";
		char* content = read_file("index.html");
		char* html = (char*)malloc(sizeof(char*) * (strlen(header) + strlen(content)));
		    
		strcpy(html, header);
		strcat(html, content);
		    
			
		n = write(accept_file_descriptor, html, strlen(html));

		close(accept_file_descriptor);

		free(html);
  }
  close(socket_file_descriptor);
}
  log_info("Application closed");

  return 0;
}
