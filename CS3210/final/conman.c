#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/sendfile.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h> // For stat()
#include <fcntl.h>    // For open()
#include <string.h>
#include "shared.h"

int client_sockfd;

void usage() {
	printf("Usage:\n");
	printf("conman <filename>\n");
	printf("\n");
}

void int_handler(int sig) {
	printf("Interrupt caught\n");
	close(client_sockfd);
	exit(0);
}

int main (int argc, char** argv) {
	struct sockaddr_in server_address;
	int result, server_len;
	char filename[MAX_PATH];

	if (argc != 2) {
		usage();
		exit(1);
	}

	strcpy(filename, argv[1]);

	// Prevent zombie children
	// Inspired from http://www.cs.rpi.edu/courses/sysprog/sockets/sock.html
	signal(SIGCHLD, SIG_IGN); 
	signal(SIGINT, int_handler); 

	client_sockfd = socket(PF_INET, SOCK_STREAM, 0);

	// Set up our server to connect to
	server_address.sin_family = PF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_len = sizeof(server_address);

	result = connect (client_sockfd, (struct sockaddr *)&server_address, server_len);
	if (result == -1) {
		perror("Couldn't connect");
	}

	// Indicate it's the proper format
	write(client_sockfd, "clnt", 4);

	send_file(client_sockfd, filename);

	close(client_sockfd);

	return 0;
}

