// OUR CODE {

#include "types.h"
#include "stat.h"
#include "user.h"
#define NUM_THREADS 2

void thread(void *args) {
    printf(1, "\n");
}

int main() {
    int i, args[] = {1, 2};

	printf(1, "main: running with %d threads...\n", NUM_THREADS);

	// Start all children
	for (i = 0; i < NUM_THREADS; i++) {
		int pid = thread_create(thread, args);
		printf(1, "main: created thread with pid %d\n", pid);
	}
	
	// Wait for all children
	for (i = 0; i < NUM_THREADS; i++) {
		int pid = join();
        printf(1, "Thread with pid %d has joined.\n", pid);
	} 
	
    exit();
}

// OUR CODE }