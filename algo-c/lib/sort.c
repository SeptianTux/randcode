#include "sort.h"

int sort(int (*arr)[], int n) {
    int  tmp;

    for(int i=0, j=0; i<n; i++) {
        for(j=i+1; j<n; j++) {
            if((*arr)[i] >= (*arr)[j]) {
                /*
                tmp = (*arr)[i];
                (*arr)[i] = (*arr)[j];
                (*arr)[j] = tmp;
                */
                (*arr)[i] = (*arr)[i] + (*arr)[j];
                (*arr)[j] = (*arr)[i] - (*arr)[j];
                (*arr)[i] = (*arr)[i] - (*arr)[j];
            }
        }
    }

    return 0;
}
