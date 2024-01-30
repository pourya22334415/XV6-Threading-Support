// OUR CODE {

#include "types.h"
#include "stat.h"
#include "user.h"

int stack[4096] __attribute__ ((aligned (4096)));
int x = 0;

int main(int argc, char *argv[]) {
    printf(1, "Stack is at %p\n", stack);
    // int tid = fork();
    int tid = clone(stack);

    if (tid < 0)
        printf(2, "error!\n"); 
    // child
    else if (tid == 0)
        for( ; ; ) {
            x++;
            sleep(100);
        }
    // parent
    else
        //printf(1, "the child with tid %d is created\n", tid);
        //int join_tid = join();
        //printf(1, "the child with tid %d is joined\n", join_tid);
        for( ; ; ) {
            printf(1, "x = %d\n", x);
            sleep(100);
        }

    exit();
}

// OUR CODE }