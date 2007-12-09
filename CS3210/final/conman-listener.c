#include "shared.h"

int client_sockfd;

void usage() {
	printf("\n");
	printf("Usage:\n");
	printf("conman-listener <directive> --server=<hostname> --save_to=<dir>\n");
	printf("  \"start\" is currently the only <directive> implemented\n");
	printf("  <hostname> is the server to connect to\n");
	printf("  <dir> is the directory to store saved files to\n");
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

	// From http://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
	int option_index;
	char server[128];
	char save_to[MAX_PATH];
	struct hostent *hostinfo;

	// Check all arguments, make sure they're good
	static struct option long_options[] = {
		{"server", required_argument, NULL, 's'},
		{"save_to", required_argument, NULL, 'd'}
	};

	int c;
	while ((c = getopt_long(argc, argv, "sd", long_options, &option_index)) != -1) {
		switch(c) {
			case 's':
				strcpy(server, optarg);
				break;
			case 'd':
				strcpy(save_to, optarg);
				break;
			default:
				printf("C is %d\n", c);
				printf("Optarg is %s\n", optarg);
				usage();
				exit(1);
		}

	}

	if (strcmp(argv[5], "start") != 0) {
		usage();
		exit(1);
	}

	signal(SIGINT, int_handler);

	// Set up our server to connect to
	hostinfo = gethostbyname(server);
	if (!hostinfo) {
		perror("Couldn't get host information");
		exit(1);
	}
	server_address.sin_family = PF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr = *(struct in_addr *)*hostinfo->h_addr_list;
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
			while( get_file(client_sockfd, save_to) > 0 ) { }
		}

		if (close(client_sockfd) == -1) {
			perror("error closing socket");
		}

		usleep(10000000);
	}


	return 0;
}

