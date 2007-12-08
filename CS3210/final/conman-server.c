#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>        // For O_WRONLY
#include <sys/sendfile.h> // For sendfile
#include "shared.h"

#define TEMP_DIR "temp"

// http://www.metalshell.com/view/source/116/ helped with directories

int server_sockfd, client_sockfd;

int make_socket(unsigned short int);

void int_handler(int sig) {
	printf("Interrupt caught\n");
	close(client_sockfd);
	close(server_sockfd);
	exit(0);
}

int main (int argc, char** argv) {
	int client_len;   // Used for accepting a connection from client
	int i;            // General variable used for storing read/write results
	struct sockaddr_in client_address; // Stores client information
	char   validator_buff[4];  // Used for validation string

	signal(SIGCHLD, SIG_IGN); 

	server_sockfd = make_socket(PORT);

	set_socket(server_sockfd);

// Create connection, wait for clients

	listen(server_sockfd, 5);
	while(1) {
		printf("Waiting for new connection\n");

		// Accept a connection
		client_len = (unsigned int)sizeof(client_address);
		client_sockfd = accept(server_sockfd,
			(struct sockaddr *)&client_address, (size_t *)&client_len);
		if (client_sockfd < 0) {
			perror("Error accepting socket");
			exit(1);
		}
		printf("Accepted connect\n");

		// Determine the client is a valid connection (read first 4 bytes)
		i = read(client_sockfd, (char *)&validator_buff, 4);
		if (i < 0) {
			perror("Error receiving authentication");
			close(client_sockfd);
			continue;
		}
		validator_buff[i] = '\0';

		if(!strcmp(validator_buff, "clnt") && !strcmp(validator_buff, "lsnr")) {
			printf("Invalid packet header\n");
			close(client_sockfd);
			continue;
		}

		// Handles client connections
		if(strcmp(validator_buff, "clnt") == 0) {
			// Clients just send a file
			if(!get_file(client_sockfd, TEMP_DIR)) {
				perror("Error getting file!");
				close(client_sockfd);
				continue;
			}
		}

		// Handles listener connections
		else if (strcmp(validator_buff, "lsnr") == 0) {
			DIR* dip;
			struct dirent* dit;
			char filename[MAX_PATH];

			// Open directory
			if ((dip = opendir(TEMP_DIR)) == NULL) {
				perror("Couldn't open directory");
				close(client_sockfd);
				continue;
			}

			// No files to send, tell the user
			if ((dit = readdir(dip)) == NULL) {
				write(client_sockfd, "0", sizeof("0"));
			}

			else {
				write(client_sockfd, "1", sizeof("1")); // Tell user there are files
				read(client_sockfd, validator_buff, sizeof(validator_buff)); // Get ok to send the file
				do {
					// Get full pathname
					strcpy(filename, TEMP_DIR);
					strcat(filename, "/");
					strcat(filename, dit->d_name);

					if ((dit->d_name)[0] == '.') // Don't send any hidden files
						continue;

					// Send files to client
					printf("Sending %s\n", dit->d_name);
					send_file(client_sockfd, dit->d_name);

					// Remove file after it's sent
					unlink(filename);
				} while ((dit = readdir(dip)) != NULL);
				// Delete the file after sent
			}

			// Close directory
			if (closedir(dip) == -1) {
				perror("Couldn't close directory");
				close(client_sockfd);
				continue;
			}
		}

		close(client_sockfd);
	}

	return 0;
}

// Used http://www.cs.utah.edu/dept/old/texinfo/glibc-manual-0.02/library_15.html#SEC238
// Creates and binds to a socket
int make_socket (unsigned short int port) {
	int sock;
	struct sockaddr_in server_address;

	sock = socket (PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror ("Error creating socket");
	}

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(sock, 
		(struct sockaddr *)&server_address, sizeof (server_address)) < 0) 
	{
		perror("Error binding");
		exit(1);
	}

	return sock;

}
