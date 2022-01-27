#ifndef RENDER_H
#define RENDER_H

#include "game.h"

void check_terminal_size(game_t* game);
void initialize_window(game_t* game);
void end_game(game_t* game);
void render_game(game_t* game);

#endif
