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
	int i;
	//char filename[MAX_PATH];
	char buff[BUFSIZ];

	signal(SIGINT, int_handler); 

	// Set up our server to connect to
	server_address.sin_family = PF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_len = sizeof(server_address);

	// Periodically connect to see if there's any files
	while (1) {

		client_sockfd = socket(PF_INET, SOCK_STREAM, 0);

		buff[0] = '\0';
		bzero(buff,'\0');
		if (client_sockfd == -1) {
			perror("Couldn't create socket");
		}

		result = connect (client_sockfd, (struct sockaddr *)&server_address, server_len);
		if (result == -1) {
			perror("Couldn't connect");
			close(client_sockfd);
			exit(1);
		}

		// Indicate it's the proper format
		i = write(client_sockfd, "lsnr", 4);
		if (i == -1) {
			perror("Error writing");
			close(client_sockfd);
		}

		// Make sure they have files
		i = read(client_sockfd, buff, sizeof(buff));
		buff[i] = '\0';
		if (i <= 0) {
			if (i == 0) {
				printf("Error with validation\n");
			}
			else {
				perror("Error with validation");
				close(client_sockfd);
			}
		}

		// Indicates there are files, so get them!
		if (buff[0] == '1') {
			write(client_sockfd, "1", sizeof("1")); // Write that we're ok to send the file
			while( get_file(client_sockfd, "listener_files") > 0 ) { }
		}

		if (close(client_sockfd) == -1) {
			perror("error closing socket");
		}

		usleep(10000000);
	}


	return 0;
}

