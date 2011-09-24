#include "shared.h"

int client_sockfd;

void usage() {
	printf("Usage:\n");
	printf("conman <directive> --server=<server> <filename>\n");
	printf("  <directive> is currently only \"start\"\n");
	printf("  <server> is the server to connect to\n");
	printf("  <filename> is the file to send\n");
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
	char server[128];
	struct hostent *hostinfo;

	if (argc < 2) {
		usage();
		exit(1);
	}

	// Check all arguments, make sure they're good
	static struct option long_options[] = {
		{"server", required_argument, NULL, 's'}
	};

	int c;
	int option_index;
	while ((c = getopt_long(argc, argv, "sd", long_options, &option_index)) != -1) {
		switch(c) {
			case 's':
				strcpy(server, optarg);
				break;
			default:
				usage();
				exit(1);
		}
	}

	if (strcmp(argv[3], "send") != 0) {
		usage();
		exit(1);
	}
	strcpy(filename, argv[4]);

	// Set up our server to connect to
	hostinfo = gethostbyname(server);
	if (!hostinfo) {
		perror("Couldn't get host information");
		exit(1);
	}

	signal(SIGINT, int_handler); 

	// Set up our server to connect to
	server_address.sin_family = PF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr = *(struct in_addr *)*hostinfo->h_addr_list;
	server_len = sizeof(server_address);

	client_sockfd = socket(PF_INET, SOCK_STREAM, 0);
	result        = connect (client_sockfd, (struct sockaddr *)&server_address, server_len);
	if (result == -1) {
		perror("Couldn't connect");
	}

	// Indicate we're a client
	write(client_sockfd, "clnt", 4);

	// Send the file to the server
	send_file(client_sockfd, filename);

	close(client_sockfd);

	return 0;
}

