// OUR CODE {

#include "types.h"
#include "stat.h"
#include "user.h"
#include "mthread.c"

int x = 0;

void long_function() {
    printf(1, "Function started.\n");
    sleep(500);
    printf(1, "Function finished.\n");
    return;
}

int main(int argc, char *argv[])  {
  int pid = fork();

  if (pid < 0)  {
    printf(2, "error!\n");
  } 
  else if (pid == 0)  {
      int args[] = {1};
      thread_create(&long_function, (void *)args);
      sleep(100);
  } 
  else  {
    wait();
  }

  exit();
}

// OUR CODE }