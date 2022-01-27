#ifndef GAME_H
#define GAME_H

#include <stddef.h>

#include "common.h"

void read_name(char* write_into);
void update(game_t* game, input_key_t input, int growing);
void place_food(board_t* board);
void teardown(game_t* game);

#endif
