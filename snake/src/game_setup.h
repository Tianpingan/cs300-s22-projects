#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include "common.h"

/** Enum to communicate board initialization status.
 * Values include INIT_SUCCESS, INIT_ERR_INCORRECT_DIMENSIONS,
 * INIT_ERR_WRONG_SNAKE_NUM, and INIT_ERR_BAD_CHAR.
 */
typedef enum board_init_status {
    INIT_SUCCESS,                   // no errors were thrown
    INIT_ERR_INCORRECT_DIMENSIONS,  // dimensions description was not formatted
                                    // correctly, or too many rows/columns are
                                    // specified anywhere in the string for the
                                    // given dimensions
    INIT_ERR_WRONG_SNAKE_NUM,  // no snake or multiple snakes are on the board
    INIT_ERR_BAD_CHAR,  // any other part of the compressed string was formatted
                        // incorrectly
    INIT_UNIMPLEMENTED  // only used in stencil, no need to handle this
} board_init_status_t;

board_init_status_t initialize_game(game_t* game, char* board_rep);

board_init_status_t decompress_board_str(board_t* board, char* compressed);
board_init_status_t initialize_default_board(board_t* board);

#endif
