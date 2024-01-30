// OUR CODE {

#include "types.h"
#include "stat.h"
#include "user.h"
#include "mthread.c"

int sum = 0;
int arr[] = {1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6}; // sum is 10

void add(void *y) {
    sum += *((int *) y);
    return;
}

int main() {
    int i = 0;

    for (i = 0; i < 12; ++i) {
        // sleep(100);
        int pid = thread_create(&add, (void *)&arr[i]);
        printf(1, "thread created with pid %d\n", pid);
    }

    for (i = 0; i < 12; ++i) {
        int pid = thread_join();
        printf(1, "thread joined with pid %d\n", pid);
    }
    printf(1, "sum is: %d\n", sum);

    exit(); 
}

// OUR CODE }