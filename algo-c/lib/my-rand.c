#include "my-rand.h"
void my_rand_reset() {
    srand(time(NULL));
}

int my_rand(int max) {
    return rand() % max;
}

int my_rand_range(int min, int max) {
    return (rand() % (max - min)) + min;
}

void rand_arr(int (*arr)[], int n) {
    my_rand_reset();

    for(int i=0; i<n; i++) {
        (*arr)[i] = my_rand_range(0, n*10);
    }
}


