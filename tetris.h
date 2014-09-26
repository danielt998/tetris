
struct block;

void put_new_piece();
void plot_piece(block, block, block, block);
void unplot_piece(block, block, block, block);
bool check_block_free(int, int);
bool check_free(int, int, int, int, int, int, int, int);
void move_down();
void move_right();
void move_left();
bool is_game_over();
void save_location();
void rotate_right();
void rotate_left();
void clear_row(int);
void clear_lines();
bool move();
void key_press_handler();
void initialise_game();
void initialise_curses();
//int main(int, char**);
