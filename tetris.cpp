#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>//think this is a c lib, should switch to a c++ one
#include "piece.hxx"
//#include <iostream>//ncurses includes this
//time.h

#define DELAY 1000000 //in miliseconds?
#define WIDTH 10 //width of screen
#define HEIGHT 20 //should use consts instead
#define DEBUG
#define TIME_OUT 200
int board[WIDTH][HEIGHT];
piece * Piece;

bool new_piece = true;
/*
struct block
{
  int x;
  int y;
};*/

///////////////////////////put this into a .h file
void plot_piece(piece*);
void key_press_handler();
void unplot_piece(piece*);
bool check_free(int, int, int, int, int, int, int, int);
////////////////////////////////////////////

void put_new_piece()
{
  Piece = new piece();
  plot_piece(Piece);
}

bool check_block_free(int x, int y)
{
  if (y > HEIGHT - 1 || x < 0 || x > WIDTH - 1 || board[x][y] != 0)
    return false;
  return true;
}

bool check_piece_free(piece * p)
{
  return check_free(p->a.x, p->a.y, p->b.x, p->b.y, p->c.x, p->c.y,
                                                    p->d.x, p->d.y);
}

//probably want to make all pieces use check_piece_free, instance method
//to move down one etc.
bool check_free(int newax, int neway, int newbx, int newby,
                int newcx, int newcy, int newdx, int newdy)
{
  block newa; block newb; block newc; block newd;
  newa.x = newax; newa.y = neway; newb.x = newbx; newb.y = newby;
  newc.x = newcx; newc.y = newcy; newd.x = newdx; newd.y = newdy;

  if (check_block_free(newa.x, newa.y) && check_block_free(newb.x, newb.y) 
      && check_block_free(newc.x, newc.y) && check_block_free(newd.x, newd.y))
    return true;
  return false;
}

void move_down()
{
  unplot_piece(Piece);
  Piece->move_down();
  plot_piece(Piece);
}

void move_right()
{
  unplot_piece(Piece);
  Piece->move_right();
  plot_piece(Piece);
}

void move_left()
{
  unplot_piece(Piece);
  Piece->move_left();
  plot_piece(Piece);
}

bool is_game_over()
{
  for (int i = 0; i <  WIDTH; i++)
    if (board[0][i] == 1)
      return true;
  return false;
}

void save_location()
{
  board[Piece->a.x + 1][Piece->a.y + 1] = 1;
  board[Piece->b.x + 1][Piece->b.y + 1] = 1;
  board[Piece->c.x + 1][Piece->c.y + 1] = 1;
  board[Piece->d.x + 1][Piece->d.y + 1] = 1;
}

//put these into one with char as a parameter?
void plot_piece(piece* given_piece)
{
  mvaddch(given_piece->a.y, given_piece->a.x, 'X');
  mvaddch(given_piece->b.y, given_piece->b.x, 'X');
  mvaddch(given_piece->c.y, given_piece->c.x, 'X');
  mvaddch(given_piece->d.y, given_piece->d.x, 'X');
  refresh();
}
  
void unplot_piece(piece* given_piece)
{ 
  mvaddch(given_piece->a.y, given_piece->a.x, '.');
  mvaddch(given_piece->b.y, given_piece->b.x, '.');
  mvaddch(given_piece->c.y, given_piece->c.x, '.');
  mvaddch(given_piece->d.y, given_piece->d.x, '.');
  refresh();
}

void rotate_right()
{
  //some code to check for collisions here
  if (check_piece_free(Piece->get_rotated_right_position()))
  {
    unplot_piece(Piece);
    Piece->rotatepiece();
    plot_piece(Piece);
  }
}

void rotate_left()
{
}

void clear_row(int row)
{
  for (int i = 0; i < WIDTH; i++)
  {
    board[row][i] = 0;
  }
  for (int i = row - 1; i < HEIGHT; i++)
  {
    for (int j = 0; j < WIDTH; j++)
      board[i + 1][j + 1] = board[i][j];
  }
}

void clear_lines()
{
  //would be more efficient to do backwards... (bottom up)
  for (int i = 0; i < HEIGHT; i++)
  {
    bool stop = false;
    for (int j = 0; j < WIDTH; j++)
    {
      if (board[i][j] == 0)
      {
        stop = true;
        break;
      }
    }
    if (! stop)
    {
      clear_row(i);
    }
  }
}

bool move()//returns false when game is over 
{
  clear_lines();
  if (new_piece)
  {
    put_new_piece();
    new_piece = false;
  }
  else if (check_free(Piece->a.x, Piece->a.y + 1, Piece->b.x, Piece->b.y + 1,
                      Piece->c.x, Piece->c.y + 1, Piece->d.x, Piece->d.y + 1))
    move_down();
  else
  {    
    new_piece = true;
    save_location();
  }
#ifdef DEBUG
  mvprintw(0, 20, "a.x: %d", Piece->a.x);
  mvprintw(1, 20, "a.y: %d", Piece->a.y);
  mvprintw(2, 20, "b.x: %d", Piece->b.x);
  mvprintw(3, 20, "b.y: %d", Piece->b.y);
  mvprintw(4, 20, "c.x: %d", Piece->c.x);
  mvprintw(5, 20, "c.y: %d", Piece->c.y);
  mvprintw(6, 20, "d.x: %d", Piece->d.x);
  mvprintw(7, 20, "d.y: %d", Piece->d.y);
  for (int i = 0; i++ < WIDTH;)
    for (int j = 0; j++ < HEIGHT;)
      mvprintw(j + 8, i + 30, "%d", board[i][j]);
  refresh();
#endif
  key_press_handler();
  key_press_handler();
  key_press_handler();
  key_press_handler();
  key_press_handler();

  return ! is_game_over();
}

void key_press_handler()
{
  char ch = getch();
#ifdef DEBUG
  mvprintw(8, 20, "key: %d", ch);
#endif
  switch(ch)
  {
    case 4://left arrow key
     if (check_free(Piece->a.x - 1, Piece->a.y, Piece->b.x - 1, Piece->b.y,
                    Piece->c.x - 1, Piece->c.y, Piece->d.x - 1, Piece->d.y))
       move_left();
     break;
    case 5://right arrow key
     if (check_free(Piece->a.x + 1, Piece->a.y, Piece->b.x + 1, Piece->b.y,
                    Piece->c.x + 1, Piece->c.y, Piece->d.x + 1, Piece->d.y))
       move_right();
     break;
    case 2://down arrow key
      if (check_free(Piece->a.x, Piece->a.y + 1, Piece->b.x, Piece->b.y + 1,
                     Piece->c.x, Piece->c.y + 1, Piece->d.x, Piece->d.y + 1))
        move_down();
      else
        save_location();
      break;
    case 3://up arrow key
      if (true /*add a check here*/)
        rotate_right();
      break;
  }
}

void initialise_game()
{
  //fill up array with 0s and plot initial empty squares
  for (int i = 0; i < WIDTH; i++)
    for (int j = 0; j < HEIGHT; j++)
    {
      board[i][j] = 0;
      mvaddch(j, i, '.');
    }
  refresh();
}

void initialise_curses()
{
  initscr();      /* Start curses mode */
  cbreak();       /* Line buffering disabled. Pass on everything. */
  keypad(stdscr, TRUE);
  noecho();
  timeout(TIME_OUT);
  //curs_set(FALSE);
}

int main(int argc, char **argv)
{
  initialise_curses();
  initialise_game();
  //then keep looping until game is over
  while (move())
    ;

  endwin();
}
