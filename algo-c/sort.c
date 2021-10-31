#include <stdio.h>
#include "lib/sort.h"
#include "lib/my-rand.h"

#define SIZE 20

int main() {
    int arr[SIZE];

    rand_arr(&arr, SIZE);

    arr[2] = 1;
    arr[3] = 1;


    printf("arr :\n");

    for(int i=0; i<SIZE; i++) {
        printf("%d\n", arr[i]);
    }

    printf("\n\n");
    
    sort(&arr, SIZE);

    printf("sorted arr :\n");

    for(int i=0; i<SIZE; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}
