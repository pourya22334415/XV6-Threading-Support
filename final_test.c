// OUR CODE {

// this is a test for thread functions
#include "types.h"
#include "stat.h"
#include "user.h"
#include "mthread.c"

int arrsum = 0;
int arr[] = {1, 2, 3, 4, 5, 6}; // 1 + 2 + 3 + 4 + 5 + 6 = 21

void sum(void *x) {
    arrsum += *((int *)x);
}

int main() {
    for(int i = 0; i < 6; i++) {
        int tid = thread_create(&sum, (void *)&arr[i]);
        printf(1, "thread created with pid %d\n", tid);
    }

    for(int i = 0; i < 6; i++) {
        int tid = thread_join();
        printf(1, "thread joined with pid %d\n", tid);
    }
    printf(1,"*%d\n", arrsum);

    exit(); 
}

// OUR CODE }