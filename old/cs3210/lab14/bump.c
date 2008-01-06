#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h>

int main(int argc, char** argv) {

	void* shared_mem;
	int shmid;

	shmid = shmget((key_t)23, sizeof(int), 0666 | IPC_CREAT);

	if (shmid == -1) {
		perror("shmget failed");
	}

	shared_mem = shmat(shmid, (void*)0, 0);

	int *counter;

	if (shared_mem == (void *)-1) {
		perror("shmat failed");
	}

	counter = (int *)shared_mem;
	*counter = 0;

	while(1) {
		(*counter)++;
		usleep(1000000);
	}

	return 0;
}
