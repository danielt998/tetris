//#include <iostream>
#include <stdlib.h>//think this is a c lib, should switch to a c++ one
#include <stdio.h>
#include <ncurses.h>
#include "piece.hxx"
#define DEBPNTR

//matrices to represent the changes of positions of the blocks
//must somehow do the checking first :p
//columns are a.x, a.y, b.x and so on, rows are rotated_times
//piece 1 does not rotate
int rotate_1[4][8] = 
{{ 0,  0,  0,  0,  0,  0,  0,  0},
 { 0,  0,  0,  0,  0,  0,  0,  0},
 { 0,  0,  0,  0,  0,  0,  0,  0},
 { 0,  0,  0,  0,  0,  0,  0,  0}};

int rotate_2[4][8] = 
{{ 0,  0,  0,  0,  0, -1, -2,  1},
 { 0,  0,  2,  0,  0,  0,  2, -2},
 { 2,  2,  0,  0,  0,  2,  0,  0},
 {-2, -2, -2,  0,  0, -1,  0,  1}};

int rotate_3[4][8] = 
{{ 0,  0,  2,  1,  2,  1,  0,  0},
 { 2,  1,  0,  0,  0, -1,  0,  0},
 { 0, -1,  2,  0,  0, -1,  2,  0},
 {-2,  0, -4, -1, -2,  1, -2,  0}};

int rotate_4[4][8] = 
{{ 0,  0,  1,  1,  0,  0,  0,  0},
 {-1,  1,  0,  0,  0,  0,  0,  0},
 { 0,  0,  0,  0,  0,  0, -1, -1},
 { 1, -1, -1, -1,  0,  0,  1,  1}};

int rotate_5[4][8] = 
{{ 0,  2,  0,  0,  0,  0, -2,  0},
 { 0, -2,  0,  0,  0,  0,  2,  0},
 { 0,  2,  0,  0,  0,  0, -2,  0},
 { 0, -2,  0,  0,  0,  0,  2,  0}};

int rotate_6[4][8] = 
{{ 0,  0,  0,  2,  2,  0,  0,  0},
 { 0,  0,  0, -2, -2,  0,  0,  0},
 { 0,  0,  0,  2,  2,  0,  0,  0},
 { 0,  0,  0, -2, -2,  0,  0,  0}};

int rotate_7[4][8] = 
{{ 1,  1,  0,  0, -1,  2, -2,  3},
 {-1, -1,  0,  0,  1, -2,  2, -3},
 { 1,  1,  0,  0, -1,  2, -2,  3},
 {-1, -1,  0,  0,  1, -2,  2, -3}};

void piece::move_down()
{
  a.y++;
  b.y++;
  c.y++;
  d.y++;
}

void piece::move_left()
{
  a.x--;
  b.x--;
  c.x--;
  d.x--;
}

void piece::move_right()
{
  a.x++;
  b.x++;
  c.x++;
  d.x++;
}

piece::piece()
{
  rotatedtimes = 0;
  piece_type = rand() % 7 + 1;//check that this works correctly!

  //want to make this more generic with parameters for width...
  //may want to use a matrix for this(and same matrix as rotate, with coords..?
  switch (piece_type)
  {
    case 1:
      a.x = 4; a.y = 0; b.x = 5; b.y = 0; c.x = 4; c.y = 1; d.x = 5; d.y = 1;
      break;
    case 2:
      a.x = 4; a.y = 0; b.x = 4; b.y = 1; c.x = 5; c.y = 1; d.x = 6; d.y = 1;
      break;
    case 3:
      a.x = 6; a.y = 0; b.x = 4; b.y = 1; c.x = 5; c.y = 1; d.x = 6; d.y = 1;
      break;
    case 4:
      a.x = 5; a.y = 0; b.x = 4; b.y = 1; c.x = 5; c.y = 1; d.x = 6; d.y = 1;
      break;
    case 5:
      a.x = 4; a.y = 0; b.x = 5; b.y = 0; c.x = 5; c.y = 1; d.x = 6; d.y = 1;
      break;
    case 6:
      a.x = 5; a.y = 0; b.x = 6; b.y = 0; c.x = 4; c.y = 1; d.x = 5; d.y = 1;
      break;
    case 7:
      a.x = 4; a.y = 0; b.x = 5; b.y = 0; c.x = 6; c.y = 0; d.x = 7; d.y = 0;
      break;
  }
}

void piece::add_rot_mat(/*int** mat*/int  p_type)
{
  int* mat = (int*)get_mat_2(p_type);

#ifdef DEBPNTR
  mvprintw(30, 0, "add_rot_mat start");
#endif
mvprintw(31, 0, "x,:%d, y:%d", a.x, a.y);
  a.x += *(mat + sizeof(int) * ((8 * rotatedtimes) + 0) );
mvprintw(32, 0, "x after:%d, yafter:%d", a.x, a.y);//this line is NOT debug code
mvprintw(33, 0, "mat:%d, mat+8*rottms:%d, rottmes(before):%d, *(mat_8*rottms:)%x",mat, mat +/* sizeof(int) */ ((8 * rotatedtimes) + 0),( rotatedtimes), *(mat + sizeof(int) * ((8 * rotatedtimes) + 0)));
mvprintw(34, 0,"sizeof(int):%d, mat:%x", sizeof(int) );


  a.y += *(mat + sizeof(int) * ((8 * rotatedtimes) + 1) );
  b.x += *(mat + sizeof(int) * ((8 * rotatedtimes) + 2) );
  b.y += *(mat + sizeof(int) * ((8 * rotatedtimes) + 3) );
  c.x += *(mat + sizeof(int) * ((8 * rotatedtimes) + 4) );
  c.y += *(mat + sizeof(int) * ((8 * rotatedtimes) + 5) );
  d.x += *(mat + sizeof(int) * ((8 * rotatedtimes) + 6) );
  d.y += *(mat + sizeof(int) * ((8 * rotatedtimes) + 7) );

#ifdef DEBPNTR
  mvprintw(30, 0, "add_rot_mat end");
#endif
}

void piece::rotatepiece()
{
  //some stuff (using matrices?)
  //
  //
  //
  add_rot_mat(piece_type);

  if (rotatedtimes > 2)
    rotatedtimes = 0;
  else
    rotatedtimes++;
}

//just have to trust that this returns pointer to mat whose width <= 8
int** piece::get_mat(int given_type)
{
  switch (given_type)
  {
    case 1:
           return (int**) &rotate_1[0];
           break;
    case 2:
           return (int**) rotate_2[0];
           break;
    case 3:
           return (int**) &rotate_3[0];
           break;
    case 4:
           return (int**) &rotate_4[0];
           break;
    case 5:
           return (int**) &rotate_5[0];
           break;
    case 6:
           return (int**) &rotate_6[0];
           break;
    case 7:
           return (int**) &rotate_7[0];
           break;
  }
}

int (*piece::get_mat_2(int given_type))[8]
{
  switch (given_type)
  {
    case 1:
           return rotate_1;
           break;
    case 2:
           return rotate_2;
           break;
    case 3:
           return rotate_3;
           break;
    case 4:
           return rotate_4;
           break;
    case 5:
           return rotate_5;
           break;
    case 6:
           return rotate_6;
           break;
    case 7:
           return rotate_7;
           break;
  }
}

piece* piece::get_rotated_right_position()
{
#ifdef DEBPNTR
  mvprintw(30, 0, "get_rotated_right_position start: %d", piece_type);
  refresh();
#endif
  int* mat = (int*)get_mat_2(piece_type);
#ifdef DEBPNTR
  mvprintw(30, 0, "get_rotated_right_position - retrieved matrix");
#endif
  piece* temp = new piece();
/*
  temp->a.x = this->a.x + mat[rotatedtimes][0];
  temp->a.y = this->a.y + mat[rotatedtimes][1];
  temp->b.x = this->b.x + mat[rotatedtimes][2];
  temp->b.y = this->b.y + mat[rotatedtimes][3];
  temp->c.x = this->c.x + mat[rotatedtimes][4];
  temp->c.y = this->c.y + mat[rotatedtimes][5];
  temp->d.x = this->d.x + mat[rotatedtimes][6];
  temp->d.y = this->d.y + mat[rotatedtimes][7];
*/
  temp->a.x = this->a.x + *(mat + sizeof(int) * ((8 * rotatedtimes) + 0));
  temp->a.y = this->a.y + *(mat + sizeof(int) * ((8 * rotatedtimes) + 1));
  temp->b.x = this->b.x + *(mat + sizeof(int) * ((8 * rotatedtimes) + 2));
  temp->b.y = this->b.y + *(mat + sizeof(int) * ((8 * rotatedtimes) + 3));
  temp->c.x = this->c.x + *(mat + sizeof(int) * ((8 * rotatedtimes) + 4));
  temp->c.y = this->c.y + *(mat + sizeof(int) * ((8 * rotatedtimes) + 5));
  temp->d.x = this->d.x + *(mat + sizeof(int) * ((8 * rotatedtimes) + 6));
  temp->d.y = this->d.y + *(mat + sizeof(int) * ((8 * rotatedtimes) + 7));

#ifdef DEBPNTR
  mvprintw(30, 0, "get_rotated_right_position - end has been reached  .. . ");
#endif
  return temp;
}
