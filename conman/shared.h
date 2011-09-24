#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>        // For O_WRONLY
#include <sys/sendfile.h> // For sendfile
#include <getopt.h>
#include <netdb.h>

#define MAX_PATH 256
#define PORT 3333

int get_file(int, char*);  // Gets a file
int send_file(int, char*); // Sends a file
void set_socket(int);      // Sets better handling for a socket
