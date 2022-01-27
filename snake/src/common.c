#include "common.h"

#include <stdlib.h>

/** Sets the seed for random number generation.
 * Arguments:
 * - `seed`: the seed.
 */
void set_seed(unsigned seed) {
    /* DO NOT MODIFY THIS FUNCTION */
    srand(seed);
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Returns a random index in [0, size)
 * Arguments:
 * - `size`: the upper bound for the generated value (exclusive).
 */
int generate_index(int size) {
    /* DO NOT MODIFY THIS FUNCTION */
    return rand() % size;
    /* DO NOT MODIFY THIS FUNCTION */
}
