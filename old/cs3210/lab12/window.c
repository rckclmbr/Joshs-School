/*
Josh Braegger
CS3210 Lab 6
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>

int key = -1;

pthread_mutex_t ncurses = PTHREAD_MUTEX_INITIALIZER;

void *countUp(void *arg) {
	WINDOW *win = arg;
	int c_up = 0;
	while (key == -1) {
		pthread_mutex_lock(&ncurses);
		wprintw(win, "\nCount up: %d", c_up++);
		wrefresh(win);
		key = getch();
		pthread_mutex_unlock(&ncurses);
		usleep(50000);
	}
	pthread_exit(NULL);
}

void *countDown(void *arg) {
	WINDOW *win = arg;
	int c_down = 0;
	while (key == -1) {
		pthread_mutex_lock(&ncurses);
		wprintw(win, "\nCount down: %d", c_down--);
		wrefresh(win);
		key = getch();
		pthread_mutex_unlock(&ncurses);
		usleep(250000);
	}
	pthread_exit(NULL);
}

int main(int argc, char** argv) {

    WINDOW *win1;
    WINDOW *win2;

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

	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, countUp, (void *)win1);
	pthread_create(&thread2, NULL, countDown, (void *)win2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

    delwin(win1);
    delwin(win2);

	endwin();
	exit(EXIT_SUCCESS);
}
