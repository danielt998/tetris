//#include <iostream>
//#include <stdlib.h>

#ifndef PIECE_H
#define PIECE_H
#endif
typedef struct
{
  int x;
  int y;
}block;

class piece
{
  public:
    block a, b, c, d;
    void rotatepiece();
    void placenewpiece();
    piece();
    void move_down();
    void move_left();
    void move_right();
    piece* get_rotated_right_position();
    piece* get_rotated_left_position();
    char* debuginfo;

  private:
    int rotatedtimes;
    int piece_type;//public?
    void add_rot_mat(int/* int mat[][8]*/);
    int** get_mat(int);
    int (*get_mat_2(int))[8];
};

