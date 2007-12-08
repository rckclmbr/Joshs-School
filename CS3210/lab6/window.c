/*
Josh Braegger
CS3210 Lab 6
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

int main(int argc, char** argv) {

    WINDOW *win1;
    WINDOW *win2;
	int key = -1;

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);

	int win1_lines = LINES / 2 - 1;
	int win2_top = win1_lines + 1;
	int win2_lines = LINES - win2_top;

	// create windows
	win1 = newwin(win1_lines, COLS, 0, 0);
	win2 = newwin(win2_lines, COLS, win2_top, 0);
	scrollok(win1, 1);
	scrollok(win2, 1);

	move(LINES / 2 - 1, 0);
	hline('_', 256);

	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

	wattrset(win1, COLOR_PAIR(1));
	wattrset(win2, COLOR_PAIR(2));

	int c_up = 0, c_down = 0;

	while (key == -1) {
		wprintw(win1, "\nCount up: %d", c_up++);
		wrefresh(win1);
		wprintw(win2, "\nCount down: %d", c_down--);
		wrefresh(win2);
		key = getch();
		usleep(250000);
	}

    delwin(win1);
    delwin(win2);

	endwin();
	exit(EXIT_SUCCESS);
}
