#include "game_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Some handy dandy macros for decompression
#define E_CAP_HEX 0x45
#define E_LOW_HEX 0x65
#define S_CAP_HEX 0x53
#define S_LOW_HEX 0x73
#define W_CAP_HEX 0x57
#define W_LOW_HEX 0x77
#define DIGIT_START 0x30
#define DIGIT_END 0x39

/* Initializes the board struct with walls around the edge of the board.
 * Returns NULL on failure; otherwise returns the pointer to the modified board.
 * Arguments:
 *  - board: a pointer to a board_t
 *  - width: a positive int equal to the desired outer width
 *  - height: a positive int equal to the desired outer height
 */
board_init_status_t initialize_default_board(board_t* board) {
    board->width = 20;
    board->height = 10;
    board->cells = calloc(20 * 10, sizeof(int));

    // Set edge cells!
    // Top and bottom edges:
    for (int i = 0; i < 20; ++i) {
        board->cells[i] = FLAG_WALL;
        board->cells[i + (20 * (10 - 1))] = FLAG_WALL;
    }
    // Left and right edges:
    for (int i = 0; i < 10; ++i) {
        board->cells[i * 20] = FLAG_WALL;
        board->cells[i * 20 + 20 - 1] = FLAG_WALL;
    }

    // Add snake
    board->cells[20 * 2 + 2] = FLAG_SNAKE;

    return INIT_SUCCESS;
}

/** Initialize the game struct, with a (potentially-empty) board representation.
 * Arguments:
 *  - `game`: a pointer to the game struct to be initialized.
 *  - `board_rep`: a string representing the initial board. May be empty.
 */
board_init_status_t initialize_game(game_t* game, char* board_rep) {
    // TODO: implement!

    return INIT_SUCCESS;
}

/** Takes in a string `compressed` and returns a board_t* that contains the
 * matching set of cells that can then be initialized. Arguments:
 *      - board: a pointer to the board that we would like to initialize
 *      - compressed: a string that contains the representation of the board.
 * Note: We assume that the string will be of the following form:
 * B|E5W2E73|E5W2S1E72... To read it, we scan the string row-by-row (delineated
 * by the `|` character), and read out a letter (E, S or W) a number of times
 * dictated by the number that follows the letter.
 */
board_init_status_t decompress_board_str(board_t* board, char* compressed) {
    // TODO: implement!
    return INIT_UNIMPLEMENTED;
}
