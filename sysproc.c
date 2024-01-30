#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}


// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  // uint: unsigned integer (positive or zero)
  // acquire: lock a semaphore
  // release: unlock a semaphore
  // tickslock: the semaphore used by uptime() 
  //            to protect system time from changing

  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_clone(void)
{
  // arg1: the first argument to pass to the function
  // arg2: the second argument to pass to the function
  // stack: the stack pointer for the new process
  // return: the process ID of the new process if 
  //         successful, -1 if an error occurred
  // argint: get the value of an integer register

  int func, arg1, arg2, stack;
  if(argint(0, &func)<0 || argint(1, &arg1)<0 || argint(2, &arg2)<0 || argint(3, &stack)<0)
    return -1;
  return clone((void *)func, (void *)arg1, (void *)arg2, (void *)stack);
}

int
sys_join(void)
{
  // stack: the stack pointer of the process to join
  // return: 0 if successful, -1 if an error occurred
  // argint:  get the value of a pointer register
  
  void **stack;
  int arg;
  arg = argint(0, &arg);
  stack = (void**) arg;
  return join(stack);
}