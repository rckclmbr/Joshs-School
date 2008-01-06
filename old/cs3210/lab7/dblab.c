#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <gdbm-ndbm.h> 
#include <string.h>

DBM* db;

void usage() {
	printf("Usage: dblab -a KEY VALUE (add a record)\n");
	printf("             -d KEY (delete a record)\n");
	printf("             -g KEY (get a single record)\n");
	printf("             -l (list all records)\n");
}

int main(int argc, char** argv) {
	datum key_datum;
	datum data_datum;
	int i;

	if (argc == 1 || argc > 4) {
		usage();
		return 1;
	}

	if (argv[1][0] != '-') {
		printf("Invalid input!\n");
		usage();
		return 1;
	}

	db = dbm_open("lab", O_RDWR | O_CREAT, 0666);


	switch (argv[1][1]) {
		case 'a': // add KEY VALUE
			key_datum.dptr = (void *)argv[2];
			key_datum.dsize = strlen(argv[2]) + 1;
			data_datum.dptr = (void *)argv[3];
			data_datum.dsize = strlen(argv[3]) + 1;
			i = dbm_store(db, key_datum, data_datum, DBM_REPLACE);
			break;
		case 'd': // delete KEY
			key_datum.dptr = (void *)argv[2];
			key_datum.dsize = strlen(argv[2]) + 1;
			if (dbm_delete(db, key_datum) != 0) {
				printf("del record failed\n");
			}
			break;
		case 'g': // get KEY
			key_datum.dptr = (void *)argv[2];
			key_datum.dsize = strlen(argv[2]) + 1;
			data_datum = dbm_fetch(db, key_datum);
			if (data_datum.dptr != NULL) {
				printf("%s = %s\n", argv[2], (char*)data_datum.dptr);
			}
			else {
				printf("get record failed\n");
			}
			break;
		case 'l': // list all records
			for (key_datum = dbm_firstkey(db); key_datum.dptr; key_datum = dbm_nextkey(db)) {
				data_datum = dbm_fetch(db, key_datum);
				if (data_datum.dptr) {
					printf("%s = %s\n", key_datum.dptr, data_datum.dptr);
				}
			}
			break;
		default:
			printf("Invalid option!\n");
			usage();
	}

	dbm_close(db);

	return 0;
}
