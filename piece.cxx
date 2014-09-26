//#include <iostream>
//#include <stdlib.h>

struct block
{
  int x;
  int y;
};

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

  private:
    int rotatedtimes = 0;
    int piece_type;//public?

};

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
  piece_type = rand() % 7 + 1;//check that this works correctly!

  //want to make this more generic with parameters for width...
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

void piece::rotatepiece()
{
  //some stuff (using matrices?)
  //
  //
  //

  if (rotatedtimes > 3)
    rotatedtimes = 0;
  else
    rotatedtimes++;
}
