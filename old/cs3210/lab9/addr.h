/*
	addr.h
	by Ted Cowan
*/

int dbStuff(void);
int screenStuff(void); 

struct addressRec {
	char name[30];
	char address[30];
	char citystatezip[50];
};
