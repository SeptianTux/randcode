#include "linear-search.h"

int linear_search(int arr[], int n, int val) {
    for(int i=0, j=n-1; i<n; i++, j--) {
        if(arr[i] == val) {
            return i;
        }

        if(arr[j] == val) {
            return j;
        }
    }

    return -1;
}
