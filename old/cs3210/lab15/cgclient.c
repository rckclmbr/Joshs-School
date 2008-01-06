// Josh Braegger
// CS3210

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>

int main (int argc, char** argv) {

	char ch;
	int sock_fd,
		result,
		len;
	struct hostent *hostinfo;
	struct sockaddr_in address;

	if (argc != 2) {
		printf("You must provide a hostname or ip address\n");
		return 1;
	}

	hostinfo = gethostbyname(argv[1]);
	if (!hostinfo) {
		perror("Could not get host information");
		return 1;
	}

	sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	
	address.sin_family = AF_INET;
	address.sin_port = htons(19);
	address.sin_addr = *(struct in_addr *)*hostinfo->h_addr_list;
	len = sizeof(address);

	result = connect(sock_fd, (struct sockaddr *)&address, len);
	if (result == -1) {
		perror("Could not connect");
	}
	
	while (read(sock_fd, &ch, sizeof(ch)) > 0 && ch != '\n') {
		write(STDOUT_FILENO, &ch, 1);
	}
	printf("\n");

	close(sock_fd);

	return 0;
}
