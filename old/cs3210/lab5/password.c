/*
Josh Braegger
CS3210 Lab 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

int main(int argc, char** argv) {
	char* term = getenv("TERM");
	setupterm(term, fileno(stdout), (int *)0);
	tigetnum("xen1");

	// Clear screen
	char* str = tigetstr("clear");
	putp(str);

	// Get screen height
	int nrows = tigetnum("lines");
	int ncols = tigetnum("cols");

	// Get cursor
	char* cursor; 
	char* esc_sequence;
	cursor = tigetstr("cup");

	// Move cursor
	int y = nrows / 2;
	int x = ncols / 2 - 10;
	esc_sequence = tparm(cursor, y, x);
	putp(esc_sequence);

	// Output a string without a newline
	printf("Username: ");
	fflush(stdout);

	// Accept username
	char username[128];
	gets(username);

	// Move down one line, to middle column
	esc_sequence = tparm(cursor, y + 1, x);
	putp(esc_sequence);

	// setup terminal settings
	struct termios modes, oldmodes;
	tcgetattr(0, &oldmodes);
	modes = oldmodes;

	// Turn off echo
	modes.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &modes);

	// Prompt for password
	printf("Password: ");
	fflush(stdout);

	// Accept password invisibly
	char password[128];
	gets(password);

	// Move cursor to last line - 1, column 0
	esc_sequence = tparm(cursor, nrows - 2, 0);
	putp(esc_sequence);

	// Print password on the bottom line - 1 with string
	printf("Password is <%s>", password);

	// Restore terminal settings before exiting
	esc_sequence = tparm(cursor, nrows - 1, 0);
	putp(esc_sequence);
	tcsetattr(0, TCSANOW, &oldmodes);

	return 0;
}
