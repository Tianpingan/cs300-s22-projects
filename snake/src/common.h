#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

// Let's see if we can keep this as simple as possible, lest we intimidate
// students looking through the provided code.

// Bitflags enable us to store cell data in integers!
#define FLAG_PLAIN_CELL 0x0
#define FLAG_SNAKE 0x1
#define FLAG_WALL 0x2
#define FLAG_FOOD 0x4

/** Enumerated key input options:
 * INPUT_UP, INPUT_DOWN, INPUT_LEFT, INPUT_RIGHT, and INPUT_NONE
 */
typedef enum input_key {
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT,
    INPUT_NONE
} input_key_t;

/** Snake struct.
 * Fields:
 * - None yet!
 */
typedef struct snake {
    // TODO: Define your snake struct!
    // Store any necessary information about your snake here.
} snake_t;

/** Struct containing board data.
 *
 * Fields:
 * - width: the width of the board.
 * - height: the height of the board.
 * - cells: a pointer to the first integer in an array of integers representing
 * each board cell.
 */
typedef struct board {
    size_t width;
    size_t height;
    int* cells;  // array of integers containing data re each cell via bitmap
    snake_t* snake;
} board_t;

/** Struct containing game data.
 *
 * You may need to modify this in part 2 of the project!
 *
 * Fields:
 * - game_over: if the game is over, then 1; else, 0.
 * - score: current game score. Starts at 0.
 * - board: a pointer to the game's board struct
 */
typedef struct game {
    int game_over;   // 1 if game is over, 0 otherwise
    int score;       // game score: 1 point for every food eaten
    board_t* board;  // pointer to the board struct for this game
} game_t;

void set_seed(unsigned seed);
int generate_index(int size);

#endif
