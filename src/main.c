#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>

#ifndef CTRL
#define CTRL(x)     ((x) & 0x1f)
#endif

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int
main(int argc, char *argv[])
{
    WINDOW *my_win;
    int ch;
    int quit = false;
    initscr();
    raw();
    cbreak();
    keypad(stdscr, TRUE);

    printw("Type any character to see it in bold\n");


    int height = 3;
    int width = 10;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    refresh();
    my_win = create_newwin(height, width, starty, startx);

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
            case 'j':
                destroy_win(my_win);
                my_win = create_newwin(height, width, ++starty, startx);
                break;
            case 'k':
                destroy_win(my_win);
                my_win = create_newwin(height, width, --starty, startx);
                break;
            case 'h':
                destroy_win(my_win);
                my_win = create_newwin(height, width, starty, --startx);
                break;
            case 'l':
                destroy_win(my_win);
                my_win = create_newwin(height, width, starty, ++startx);
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

WINDOW*
create_newwin(int height, int width, int starty, int startx)
{
    WINDOW* local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    wrefresh(local_win);
    return local_win;
}


void
destroy_win(WINDOW* local_win)
{
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(local_win);
    delwin(local_win);
}
