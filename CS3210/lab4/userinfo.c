/*  
Josh Braegger
CS3210 Lab 4
*/

/*  
Usage: userinfo -? -h -t -u username
-h show hostname
-t show time and date
-u show username, uid, gid, home dir, shell and GECOS
-? show usage
*/

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>

void usage() {

	printf(" \
Usage: userinfo -? -h -t -u username\n \
-h show hostname\n \
-t show time and date\n \
-u show username, uid, gid, home dir, shell and GECOS\n \
-? show usage\n ");
	return;
}

int main (int argc, char *argv[]) {
	int opt;
	char hostname[128];
	time_t raw_time;
	struct passwd* p;

	if (argc <= 1) {
		usage();
	}

	while ((opt = getopt(argc, argv, "htu:?")) > 0) {
		switch (opt) {
			case 'u': 
				p = getpwnam(optarg);
				printf("Username: %s\n", p->pw_name);
				printf("User ID: %d\n", p->pw_uid);
				printf("Group ID: %d\n", p->pw_gid);
				printf("Home Directory: %s\n", p->pw_dir);
				printf("Shell: %s\n", p->pw_shell);
				printf("GECOS Information: %s\n", p->pw_gecos);
				break;
			case 'h': 
				gethostname(hostname, 128);
				printf("Hostname: %s\n", hostname);
				break;
			case 't': 
				time( &raw_time );
				printf("Time: %s", ctime(&raw_time));
				break;
			case '?':
			default:
				usage();
		}
	}

	return 0;
}
