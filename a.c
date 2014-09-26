#include <ncurses.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  initscr();      /* Start curses mode */
  cbreak();       /* Line buffering disabled. Pass on everything. */
  keypad(stdscr, TRUE);
  noecho();

  printw("HELLO");
  mvaddch(1, 1, 'X');
  refresh();
  while(true)
  {
    usleep(1000);
  }  
  endwin();
}
