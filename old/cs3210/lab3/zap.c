/*  
Josh Braegger
CS3210 Lab 3 
*/

/*  usage:  zap <filename> <offset> <textstring> */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	void *buf;
	int inputFile;
	struct stat fileStat;
	int offset, len;
	char* filename;
	
	if (argc != 4) {
		printf("Usage: zap <filename> <offset> <textstring>\n");
		return 1;
	}

	filename = argv[1];
	offset = atoi(argv[2]);
	len = strlen(argv[3]);

	inputFile = open(filename,O_RDWR); 	
	if (inputFile<0) {
		perror("Cannot open input file");
		return 1;
	}
	if (fstat(inputFile, &fileStat)) {
		perror("fstat() failed");
		return 1;
	}

	/*  Map the file into memory */

	buf = mmap(NULL, fileStat.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, inputFile, 0);
	
	/*  Zap the file contents with my name */

	memcpy((char *)buf + offset, argv[3], len);

	/*  Clean up */

	msync(buf, fileStat.st_size, MS_SYNC);

	munmap(buf, fileStat.st_size);
	close(inputFile);

	return 0;
}

