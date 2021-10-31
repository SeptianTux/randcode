#include "search.h"

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

int binary_search_recursive(int sorted_arr[], int l, int r, int val) {
    if(r >= 1) {
        int mid = l + (r - l) / 2;
        
        if(sorted_arr[mid] == val) {
            return mid;
        }
        
        if(sorted_arr[mid] > val) {
            return binary_search_recursive(sorted_arr, l, mid - 1, val);
        }

        return binary_search_recursive(sorted_arr, mid + 1, r, val);
    } else {
        return l;
    }

    return -1;
}

int binary_search_iterative(int sorted_arr[], int l, int r, int val) {
    int mid;

    while(l <= r) {
        mid = (r + l) / 2;

        if(sorted_arr[mid] == val) {
            return mid;
        } else if(sorted_arr[mid] > val) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
        
    return -1;
}

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
