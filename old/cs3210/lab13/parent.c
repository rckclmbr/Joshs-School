#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

#define FIFO_FILENAME "/tmp/user2"
#define BUFFER_SIZE PIPE_BUF

int main(int argc, char** argv) {

	char buffer[BUFFER_SIZE];
	int res, fd;

	// Make the fifo
    if (access(FIFO_FILENAME, F_OK) == -1) {
        res = mkfifo(FIFO_FILENAME, 0777);
        if (res != 0) {
			perror("Could not create fifo");
            exit(EXIT_FAILURE);
        }
    }

	fd = open(FIFO_FILENAME, O_WRONLY);

	if (fd == -1) {
		perror("Error opening file");
	}

	do {
		memset(buffer, '\0', sizeof(buffer));
		fgets(buffer, BUFFER_SIZE, stdin);
		res = write(fd, buffer, BUFFER_SIZE);
	} while (strncmp(buffer, "quit", BUFFER_SIZE) == -1);
	close(fd);

	return 0;
}
