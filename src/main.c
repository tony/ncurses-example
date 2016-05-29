#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>

#ifndef CTRL
#define CTRL(x) ((x)&0x1f)
#endif

typedef struct _win_border_struct {
  chtype ls, rs, ts, bs, tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct {
  int startx, starty;
  int height, width;
  WIN_BORDER border;
} WIN;

void init_win_params(WIN* p_win);
void print_win_params(WIN* p_win);
void create_box(WIN* win, bool flag);

int main(int argc, char* argv[]) {
  WIN win;
  int ch;
  int quit = false;

  initscr();
  raw();
  start_color();
  cbreak();

  keypad(stdscr, true);
  noecho();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);

  init_win_params(&win);
  print_win_params(&win);

  attron(COLOR_PAIR(1));
  printw("Press Ctrl-C or Q to exit");
  refresh();
  attroff(COLOR_PAIR(1));

  create_box(&win, true);

  while (!quit) {
    ch = getch();
    switch (ch) {
      case 'q':
        quit = true;
        break;
      case CTRL('c'):
        quit = true;
        break;
      case 'j':
        create_box(&win, false);
        ++win.starty;
        create_box(&win, true);
        break;
      case 'h':
        create_box(&win, false);
        --win.startx;
        create_box(&win, true);
        break;
      case 'l':
        create_box(&win, false);
        ++win.startx;
        create_box(&win, true);
        break;
      case 'k':
        create_box(&win, false);
        --win.starty;
        create_box(&win, true);
        break;
    }
  }
  endwin();
  return 0;
}

void create_box(WIN* p_win, bool flag) {
  int i, j;
  int x, y, w, h;

  x = p_win->startx;
  y = p_win->starty;
  w = p_win->width;
  h = p_win->height;

  if (flag == true) {
    mvaddch(y, x, p_win->border.tl);
    mvaddch(y, x + w, p_win->border.tr);
    mvaddch(y + h, x, p_win->border.bl);
    mvaddch(y + h, x + w, p_win->border.br);
    mvhline(y, x + 1, p_win->border.ts, w - 1);
    mvhline(y + h, x + 1, p_win->border.bs, w - 1);
    mvvline(y + 1, x, p_win->border.ls, h - 1);
    mvvline(y + 1, x + w, p_win->border.rs, h - 1);
  } else {
    for (j = y; j <= y + h; ++j) {
      for (i = x; i <= x + w; ++i) {
        mvaddch(j, i, ' ');
      }
    }
  }
  refresh();
}

void print_win_params(WIN* p_win) {
#ifdef _DEBUG
  mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty, p_wni->width,
           p_win->height);

  refresh();
#endif
}

void init_win_params(WIN* p_win) {
  p_win->height = 3;
  p_win->width = 10;
  p_win->starty = (LINES - p_win->height) / 2;
  p_win->startx = (COLS - p_win->width) / 2;

  p_win->border.ls = '|';
  p_win->border.rs = '|';
  p_win->border.ts = '-';
  p_win->border.bs = '-';
  p_win->border.tl = '+';
  p_win->border.tr = '+';
  p_win->border.bl = '+';
  p_win->border.br = '+';
}
