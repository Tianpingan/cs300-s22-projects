#include <assert.h>
#include <curses.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

#include "../src/common.h"
#include "../src/game.h"
#include "../src/game_setup.h"
#include "../src/mbstrings.h"

// Verbosity of test runner. Overridden via compilation flag
#ifdef VERBOSE
#define VERBOSE 1
#endif
#ifndef VERBOSE
#define VERBOSE 0
#endif

input_key_t get_input(char c) {
    if (c == 'U') {
        return INPUT_UP;
    } else if (c == 'D') {
        return INPUT_DOWN;
    } else if (c == 'L') {
        return INPUT_LEFT;
    } else if (c == 'R') {
        return INPUT_RIGHT;
    } else if (c == 'N') {
        return INPUT_NONE;
    } else {
        fprintf(stderr, "Invalid input character %c\n", c);
        exit(EXIT_FAILURE);
    }
}

void print_game(game_t *game) {
    setlocale(LC_CTYPE, "");
    for (size_t i = 0; i < game->board->height; i++) {
        for (size_t j = 0; j < game->board->width; j++) {
            char cell = game->board->cells[i * game->board->width + j];
            if (cell == FLAG_PLAIN_CELL) {
                printf(".");
            } else if (cell == FLAG_SNAKE) {
                printf("S");
            } else if (cell == FLAG_WALL) {
                printf("%lc", (wint_t)0x02588);
            } else if (cell == FLAG_FOOD) {
                printf("O");
            } else {
                printf("?");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// returns 0 if success, or a board decompress error code if failure
int run_test(game_t *output_game, char *board_string, unsigned int snake_grows,
             char *input_string) {
    int status = initialize_game(output_game, board_string);

    // return early if error parsing board
    if (status != INIT_SUCCESS) {
        return status;
    }

    int i = 0;
    while (1) {
        if (VERBOSE) {
            printf("Board at time step %d:\n", i);
            print_game(output_game);
        }
        // if we reach the end of the input, the trace is over
        if (*input_string == '\0') {
            break;
        }

        // Get user input
        input_key_t input = get_input(*input_string);
        input_string += 1;

        // Update game state
        update(output_game, input, snake_grows);

        i += 1;
    }

    return 0;
}

int main(int argc, char **argv) {
    if (getenv("DEBUG")) {
        sleep(1);
    }

    if (argc < 6) {
        printf(
            "Usage: autograder <board_string> <seed> <snake_grows> <key_input>"
            " <consider_name> <pipe>\n");
        exit(EXIT_FAILURE);
    }

    char *board_string = argv[1];
    unsigned int seed = atoi(argv[2]);
    unsigned int snake_grows = atoi(argv[3]);  // Should be 0 or 1
    char *key_input = argv[4];
    unsigned int consider_name = atoi(argv[5]);  // Should be 0 or 1
    FILE *pipe = fdopen(atoi(argv[6]), "w");

    set_seed(seed);
    // if no board string is provided then use the default board by setting
    // null
    if (board_string[0] == '0') {
        board_string = NULL;
    }

    // Run the snake game
    game_t final_game_state;
    board_t board;
    final_game_state.board = &board;

    // default the board to 0x0 so the stencil doesn't crash
    board.width = 0;
    board.height = 0;

    snake_t snake;
    final_game_state.board->snake = &snake;

    int status =
        run_test(&final_game_state, board_string, snake_grows, key_input);

    if (status != INIT_SUCCESS) {
        char *msg = "";
        if (status == INIT_ERR_BAD_CHAR) {
            msg = "BAD_CHAR";
        } else if (status == INIT_ERR_INCORRECT_DIMENSIONS) {
            msg = "INCORRECT_DIMENSIONS";
        } else if (status == INIT_ERR_WRONG_SNAKE_NUM) {
            msg = "WRONG_SNAKE_NUM";
        }
        fprintf(pipe,
                "{\n"
                "    \"board_error\": \"%s\"\n"
                "}\n",
                msg);
        return 0;
    }

    char *cell_string = (char *)malloc(
        final_game_state.board->width * final_game_state.board->height + 1);
    if (cell_string == NULL) {
        fprintf(stderr, "Failed to allocate memory for cell string\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < final_game_state.board->height; i++) {
        for (size_t j = 0; j < final_game_state.board->width; j++) {
            char cell = final_game_state.board
                            ->cells[i * final_game_state.board->width + j];
            char cell_as_char;
            if (cell == FLAG_PLAIN_CELL) {
                cell_as_char = '.';
            } else if (cell == FLAG_SNAKE) {
                cell_as_char = 'S';
            } else if (cell == FLAG_WALL) {
                cell_as_char = 'X';
            } else if (cell == FLAG_FOOD) {
                cell_as_char = 'O';
            } else {
                cell_as_char = '?';
            }
            cell_string[i * final_game_state.board->width + j] = cell_as_char;
        }
    }
    cell_string[final_game_state.board->width *
                final_game_state.board->height] = '\0';

    if (consider_name) {
        // Test name reading, mbslen
        char name_buf[1000];
        read_name(name_buf);
        size_t name_len = mbslen(name_buf);

        // Write bytes of name_buf into string
        char name_byte_str_buf[2000];
        assert(strlen(name_buf) < 1000);
        for (size_t i = 0; i <= strlen(name_buf); ++i) {
            if (name_buf[i] == 0) {
                break;
            }
            // Write two hex digits at a time, offset by (i * 2) —
            // each written string is three bytes long, so we overwrite the
            // trailing (null) byte with each write, giving us a continuous
            // string of hex values.
            snprintf(name_byte_str_buf + (i * 2), 3, "%02x",
                     (unsigned char)name_buf[i]);
        }

        fprintf(pipe,
                "{\n"
                "    \"game_over\": %d,\n"
                "    \"score\": %d,\n"
                "    \"name\": \"%s\",\n"
                "    \"name_len\": %lu,\n"
                "    \"width\": %lu,\n"
                "    \"height\": %lu,\n"
                "    \"cells\": \"%s\"\n"
                "}\n",
                final_game_state.game_over, final_game_state.score,
                name_byte_str_buf, name_len, final_game_state.board->width,
                final_game_state.board->height, cell_string);
    } else {
        fprintf(pipe,
                "{\n"
                "    \"game_over\": %d,\n"
                "    \"score\": %d,\n"
                "    \"width\": %lu,\n"
                "    \"height\": %lu,\n"
                "    \"cells\": \"%s\"\n"
                "}\n",
                final_game_state.game_over, final_game_state.score,
                final_game_state.board->width, final_game_state.board->height,
                cell_string);
    }

    if (final_game_state.game_over == 0) {
        teardown(&final_game_state);
    }

    free(cell_string);
    fclose(pipe);
    exit(EXIT_SUCCESS);
}
