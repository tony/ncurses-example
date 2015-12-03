#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>

#ifndef CTRL
#define CTRL(x)     ((x) & 0x1f)
#endif

int
main(int argc, char *argv[])
{
    int ch;
    int quit = false;
    initscr();
    raw();
    keypad(stdscr, TRUE);

    printw("Type any character to see it in bold\n");



    while(!quit) {
        ch = getch();
        switch(ch) {
            case KEY_F(1):
                printw("F1 Key pressed");
                break;
            case 'q':
                quit = true;
                break;
            case CTRL('c'):
                quit = true;
                break;
            default:
                printw("The pressed key is ");
                attron(A_BOLD);
                printw("%c", ch);
                attroff(A_BOLD);
        }
        refresh();
    }
    endwin();

    return 0;
}
