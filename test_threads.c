#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "x86.h"

#define SLEEP_TIME 100

// Declare a global variable 'counter' to keep track 
// of the number of times the increment operation 
// is performed by the threads.
volatile int counter = 0;

// Declare a lock variable 'lock' to synchronize 
// access to the 'counter' variable.
lock_t* lock;

void thread1_func(void* arg1, void* arg2) 
{
  // Cast the first argument to an integer 
  // and store it in the 'num' variable.
  int num = *(int*)arg1;
  // If 'num' is non-zero, acquire the lock 'lock'.
  if (num) lock_acquire(lock);
  {
    counter++;
    // Print a message to the console indicating 
    // that the first thread has incremented the counter.
    printf(1, "1. First thread : %d \n", counter );
  }  
  // Sleep for a certain amount of time.
  sleep(SLEEP_TIME);

  // If 'num' is non-zero, release the lock 'lock'.
  if (num) lock_release(lock);

  // Exit the current thread.
  exit();
}

void thread2_func(void* arg1, void* arg2) 
{
  // Cast the first argument to an integer 
  // and store it in the 'num' variable.
  int num = *(int*)arg1;
  // If 'num' is non-zero, acquire the lock 'lock'.
  if (num) lock_acquire(lock);
  {
    counter++;
    // Print a message to the console indicating 
    // that the second thread has incremented the counter.
    printf(1, "2. Second Thread: %d \n", counter );
  }
  // Sleep for a certain amount of time.
  sleep(SLEEP_TIME);

  // If 'num' is non-zero, release the lock 'lock'.
  if (num) lock_release(lock);
  
  // Exit the current thread.
  exit();
}

void thread3_func(void* arg1, void* arg2) 
{
  // Cast the first argument to an integer 
  // and store it in the 'num' variable.
  int num = *(int*)arg1;
  // If 'num' is non-zero, acquire the lock 'lock'.
  if (num) lock_acquire(lock);
  {
    counter++;
    // Print a message to the console indicating 
    // that the third thread has incremented the counter.
    printf(1, "3. Third Thread: %d \n", counter );
  }
  // Sleep for a certain amount of time.
  sleep(SLEEP_TIME);

  // If 'num' is non-zero, release the lock 'lock'.
  if (num) lock_release(lock);
  
  // Exit the current thread.
  exit();
}


int
main(int argc, char *argv[])
{
  // Initialize the lock 'lock'.
  lock_init(lock);

  int arg1 = 1, arg2 = 1;

  // Create three threads and pass the 'thread1_func', 
  // 'thread2_func', and 'thread3_func' functions as 
  // arguments along with the 'arg1' and 'arg2' variables.
  thread_create(&thread1_func, (void *)&arg1, (void *)&arg2);
  thread_create(&thread2_func, (void *)&arg1, (void *)&arg2);
  thread_create(&thread3_func, (void *)&arg1, (void *)&arg2);

  // Wait for all the threads to complete their execution.
  thread_join();
  thread_join();
  thread_join();

  // Exit the main thread.
  exit();
}