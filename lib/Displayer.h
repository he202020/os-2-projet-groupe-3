//
// Created by Antoine Geonet on 27/12/2022.
//
#include <ncurses.h>
#include <string.h>
#include "Car.h"
#include "Course.h"

WINDOW *display_init();
void display_end(WINDOW *win);
void display_titles(WINDOW *win, char list0fTitles[5][10], int colLg);
void display_data(WINDOW *win, Car car, int row, int colLg);

WINDOW *display_init() {
    initscr();
    noecho();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *win = newwin(yMax, xMax, 0, 0);
    box(win, 0, 0);

    return win;
}

void display_end(WINDOW *win) {
    wgetch(win);
    endwin();
}



void display_titles(WINDOW *win, char list0fTitles[5][10], int colLg) {
    int startCol = 1;
    for (int i = 0; i < 5; ++i) {
        mvwprintw(win, 4, startCol, list0fTitles[i]);
        startCol += colLg;
    }
}

void display_data(WINDOW *win, Car car, int row, int colLg) {
    char s1[sizeForTimeToStr(car.currentS1)];
    char s2[sizeForTimeToStr(car.currentS2)];
    char s3[sizeForTimeToStr(car.currentS3)];
    char lap[sizeForTimeToStr(getCurrentTurn(car))];
    timeToStr(s1, car.currentS1);
    timeToStr(s2, car.currentS2);
    timeToStr(s3, car.currentS3);
    timeToStr(lap, getCurrentTurn(car));

    char idStr[3];
    sprintf(idStr, "%d", car.id);

    int startCol = 1;
    mvwprintw(win, row, startCol, idStr);
    startCol += colLg;
    mvwprintw(win, row, startCol, s1);
    startCol += colLg;
    mvwprintw(win, row, startCol, s2);
    startCol += colLg;
    mvwprintw(win, row, startCol, s3);
    startCol += colLg;
    mvwprintw(win, row, startCol, lap);
}
