#include "jump-search.h"

int jump_search(int sorted_arr[], int n, int val, int jump) {
    int ret = -1;
    
    for(int i=0; i<n; i=i+jump) {
        for(int j=i; j<j+jump; j++) {
            if(j >= n) {
                return -1;
            }

            if(sorted_arr[j] == val) {
                return j;
            }
        }
    }

    return -1;
}
