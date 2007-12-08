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
#include <fcntl.h>        // For O_WRONLY
#include <sys/sendfile.h> // For sendfile

#define MAX_PATH 256
#define PORT 3333

int get_file(int, char*);
int send_file(int, char*);
void set_socket(int);
