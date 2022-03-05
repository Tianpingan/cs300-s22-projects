

#include <stdio.h>
// Does nothing

int main(void) {
    char *dummy = malloc(4096);
    sprintf(dummy, "Doing nothing, check my memory\n");
    printf("%s\n", dummy);
    free(dummy);
    return 0;
}