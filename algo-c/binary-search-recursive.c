#include <stdio.h>
#include "lib/sort.h"
#include "lib/search.h"
#include "lib/my-rand.h"

#define SIZE 10

int main() {
    int arr[SIZE];
    int val, ret;

    rand_arr(&arr, SIZE);

    sort(&arr, SIZE);

    val = arr[my_rand(SIZE-1)];
//    val = arr[9];
    
    printf("search : %d\n", val);

    for(int i=0; i<SIZE; i++) {
        printf("%d : %d\n", i, arr[i]);
    }

    ret = binary_search_recursive(arr, 0, SIZE-1, val);

    printf("%d\n", ret);

    return 0;
}
