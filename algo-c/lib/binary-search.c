#include "binary-search.h"

int binary_search(int sorted_arr[], int l, int r, int val) {
    if(r >= 1) {
        int mid = l + (r - l) / 2;
        
        if(sorted_arr[mid] == val) {
            return mid;
        }
        
        if(sorted_arr[mid] > val) {
            return binary_search(sorted_arr, l, mid - 1, val);
        }

        return binary_search(sorted_arr, mid + 1, r, val);
    } else {
        return l;
    }

    return -1;
}

int binary_search1(int sorted_arr[], int l, int r, int val) {
    int mid;

    while(l <= r) {
        mid = l + (r - l) / 2;

        if(sorted_arr[mid] == val) {
            return mid;
        }

        if(sorted_arr[mid] < val) {
            l = mid;
        } else {
            r = mid;
        }
    }
        
    return -1;
}
