// Josh Braegger
// Lab 11
// CS3210

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int term = 0;
int counter = 0;

void handler(int);

int main(int argc, char** argv) {

    pid_t pid;
    pid = fork();

    // int sigaction(int sig, struct sigaction* sig, struct sigaction* osig
    struct sigaction act;
    // sa_handler - pointer to a function
    if (pid > 0) { // Parent
        printf("Child pid is %d\n", pid);
        // Wait for child to complete
        waitpid(pid, 0, 0); // options=0
        printf("Child has terminated\n");
        return 0;
    }
    else if (pid == 0) { // Child
        act.sa_handler = handler;
        sigemptyset(&act.sa_mask); // Clear act.sa_mask
        act.sa_flags = 0;
        sigaction(SIGHUP, &act, NULL); // SIGHUP
        sigaction(SIGTERM, &act, NULL); // SIGTERM
        while(1) {
            counter++;
            printf("Counter = %d\n", counter);
            sleep(3);
            if (term != 0) {
                return 0;
            }
        }
    }
    else { // Error

    }

    return 0;
}

void handler(int sig) {
    if (sig == SIGHUP) {
        printf("HUP received by Child\n");
        counter = 0;
    }
    if (sig == SIGTERM) {
        printf("TERM received by Child\n");
        term = 1;
    }
}

