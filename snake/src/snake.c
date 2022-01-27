#define _XOPEN_SOURCE_EXTENDED 1
#include <curses.h>
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game.h"
#include "game_over.h"
#include "game_setup.h"
#include "mbstrings.h"
#include "render.h"

/** Gets the next input from the user, or returns INPUT_NONE if no input is
 * provided quickly enough.
 */
input_key_t get_input() {
    /* DO NOT MODIFY THIS FUNCTION */
    int input = getch();

    if (input == KEY_UP) {
        return INPUT_UP;
    } else if (input == KEY_DOWN) {
        return INPUT_DOWN;
    } else if (input == KEY_LEFT) {
        return INPUT_LEFT;
    } else if (input == KEY_RIGHT) {
        return INPUT_RIGHT;
    } else {
        // if the input isn't an arrow key, we treat it as no input (could add
        // other keys in if we want other commands, like 'pause' or 'quit')
        return INPUT_NONE;
    }
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Helper function that procs the GAME OVER screen and final key prompt.
 */
void end_game(game_t* game) {
    // Game over!

    // Free any memory we've taken
    teardown(game);

    // ****************** UNCOMMENT THIS CODE IN PART 2B ***********************
    /*
    // Render final GAME OVER PRESS ANY KEY TO EXIT screen
    render_game_over(game);
    usleep(1000 * 1000);  // 1000ms
    cbreak(); // Leave halfdelay mode
    getch();
    */

    // tell ncurses that we're done
    endwin();
}

int main(int argc, char** argv) {
    // Main program function — this is what gets called when you run the
    // generated executable file from the command line!

    // initialize board from command line arguments
    game_t game;
    board_t board;
    snake_t snake;
    game.board = &board;
    board.snake = &snake;
    int snake_grows;

    switch (argc) {
        case (2):
            snake_grows = atoi(argv[1]);
            if (snake_grows != 1 && snake_grows != 0) {
                printf(
                    "snake_grows must be either 1 (grows) or 0 (does not "
                    "grow)\n");
                return 0;
            }
            initialize_game(&game, NULL);
            break;
        case (3):
            snake_grows = atoi(argv[1]);
            if (snake_grows != 1 && snake_grows != 0) {
                printf(
                    "snake_grows must be either 1 (grows) or 0 (does not "
                    "grow)\n");
                return 0;
            } else if (*argv[2] == '\0') {
                initialize_game(&game, NULL);
                break;
            }
            initialize_game(&game, argv[2]);
            break;
        case (1):
        default:
            printf("usage: snake <GROWS: 0|1> [BOARD STRING]\n");
            return 0;
    }

    // ------------- DO NOT MODIFY ANYTHING ABOVE THIS LINE ------------------

    // Check validity of the board before rendering!
    // TODO: Implement (in Part 1C)
    // if ( ? board is not valid ? ) { return 0; }

    // Read in the player's name & save its name and length
    // TODO: Implement (in Part 2B)
    // char name_buffer[1000];
    // read_name(name_buffer);
    // ? save name_buffer in game struct ?
    // ? save mbslen(name_buffer) in game struct ?

    // TODO: Remove this message, uncomment the code below
    //       and implement Part 1A here.
    printf(
        "             ____   \n"
        "Hello       / . .\\ \n"
        "CS 300      \\  ---<\n"
        "student!     \\  /  \n"
        "   __________/ /    \n"
        "-=:___________/\n");

    // initialize_window(&game);
    // TODO: implement the game loop here!
    // end_game(&game);
}
