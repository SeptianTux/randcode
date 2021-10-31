#include <stdio.h>
#include "lib/search.h"
#include "lib/my-rand.h"

#define SIZE 20
    
int main() {
    int arr[SIZE];
    int search;

    rand_arr(&arr, SIZE);

    search = arr[my_rand(SIZE-1)];

    printf("search : %d\n\n", search);
    
    for(int i=0; i<SIZE; i++) {
        printf("%d : %d\n", i, arr[i]);
    }

    int res = linear_search(arr, SIZE, search);

    printf("\n");
    printf("result : %d\n", res);

    return 0;
}
