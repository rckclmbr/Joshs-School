#include "shared.h"

// Get a file, handling all the requesting and stuff
int get_file(int client_sockfd, char* out_directory) {
	int i;            // General variable used for storing read/write results
	char   filename[MAX_PATH]; // Stores the filename to receive
	char   file_buff[BUFSIZ];  // Used when receiving the file
	struct stat stat_buf;              // For getting file information
	int file_sockfd;
	char   full_path[MAX_PATH];

	unsigned long file_size;
	// Request filename
	write(client_sockfd, "filename", 8);

	// Read the filename
	i = recv(client_sockfd, filename, sizeof(filename), 0);
	filename[i] = '\0';

	if (strlen(filename) == 0) {
		printf("No file to receive\n");
		return 0;
	}

	strcpy(full_path, out_directory);
	strcat(full_path, "/");
	strcat(full_path, filename);

printf("Attempting to get %s\n", full_path);

	// Request file size
	write(client_sockfd, "filesize", 8);

	// Get the file size
	i = recv(client_sockfd, &stat_buf.st_size, sizeof(stat_buf.st_size), 0);
	
	// make sure the file can be opened
	file_sockfd = open(full_path, O_CREAT | O_WRONLY, 0644);
	if (file_sockfd < 0) {
		return 0;
	}

	// Request data
	write(client_sockfd, "data", 4);

	// Write the file from the data coming from the socket
	do {
		i = recv(client_sockfd, file_buff, sizeof(file_buff) - 1, 0);
		file_buff[i] = '\0';
		write(file_sockfd, file_buff, strlen(file_buff));
	} while (i > 0);

	// Verify the file size is correct
	file_size = (unsigned long)stat_buf.st_size;
	fstat(file_sockfd, &stat_buf);
	if (file_size == stat_buf.st_size) {
		printf("File %s transferred successfully (%ld bytes)\n", filename, file_size);
	}
	else {
		printf("There may have been an error transferring file %s (%ld of %ld bytes transferred)\n", 
			filename, (unsigned long)stat_buf.st_size, file_size);
	}

	close(file_sockfd);
	return 1;
}

int send_file(int client_sockfd, char filename[]) {
	int i;
	struct stat stat_buf;   // For file information
	char buff[BUFSIZ];
	char* short_file;
	int file_sockfd;

	// Make sure they want the file
	i = read(client_sockfd, buff, sizeof(buff));
	buff[i] = '\0';
	if (strcmp(buff, "filename") != 0) {
		printf("Invalid request for filename\n");
		return 1;
	}

	// Only send them the filename, not the entire path
	char *ptr = strrchr(filename, '/');
	if (ptr != NULL)
		short_file = ptr + 1;
	else
		short_file = filename;

	// Give them the filename
	write(client_sockfd, short_file, strlen(short_file));

	// Open file
	file_sockfd = open(filename, O_RDONLY);
	if (file_sockfd == -1) {
		perror("Unable to open file");
		return 1;
	}


	// Make sure they want the filesize
	i = read(client_sockfd, buff, sizeof(buff));
	buff[i] = '\0';
	if (strcmp(buff, "filesize") != 0) {
		printf("An error occurred getting 'filesize'.  Got '%s'\n", buff);
		close(file_sockfd);
		return 1;
	}

	// Get size of the file from disk
	fstat(file_sockfd, &stat_buf);

	// Send the file size
	write(client_sockfd, &stat_buf.st_size, sizeof(stat_buf.st_size));

	// Make sure they want the file
	i = read(client_sockfd, buff, sizeof(buff));
	buff[i] = '\0';
	if (strcmp(buff, "data") != 0) {
		printf("An error occurred getting 'data'.  Got '%s'\n", buff);
		close(file_sockfd);
		return 1;
	}

	// Send the file
	int rc = sendfile(client_sockfd, file_sockfd, 0, stat_buf.st_size);
	if (rc == -1) {
		perror("Could not sendfile");
		close(file_sockfd);
		return 1;
	}

	close(file_sockfd);

	return 1;
}

void set_socket(int sockfd) {
	int opt = 1;
	int opt_len = sizeof(opt);

	struct linger l;
	l.l_onoff = 1;
	l.l_linger = 2;

	/* allow local address to be reused */
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
	    opt_len) < 0) {
		perror("setsockopt SO_REUSEADDR failed");
		close(sockfd);
		exit(-1);
	}
	opt = /* SB_MAX */  1024;
	/* set send and receive buffer size to maximum */
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (char *)&opt,
	    opt_len) < 0) {
		perror("setsockopt SO_RCVBUF failed");
		close(sockfd);
		exit(-1);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (char *)&opt,
	    opt_len) < 0) {
		perror("setsockopt SO_SNDBUF failed");
		close(sockfd);
		exit(-1);

	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (char *)&l,
	    sizeof(struct linger)) < 0) {
		perror("setsockopt SO_LINGER failed");
		close(sockfd);
		exit(-1);
	}

}

