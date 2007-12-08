#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILENAME "/tmp/user2"
#define BUFFER_SIZE PIPE_BUF

int main(int argc, char** argv) {

	char buffer[BUFFER_SIZE];
	int res;

	int fd = open(FIFO_FILENAME, O_RDONLY);

	if (fd == -1) {
		perror("error");
	}

	do {
		memset(buffer, '\0', sizeof(buffer));
		res = read(fd, buffer, BUFFER_SIZE);
		printf("%s", buffer);
	} while (res > 0);
	close(fd);

	unlink(FIFO_FILENAME);

	return 0;
}
