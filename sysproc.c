#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

// OUR CODE {  you can add these in defs.h
int             example(void);
int             clone(void *stack);
int             join();
// OUR CODE }

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
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// OUR CODE {
int
sys_example(void)
{
  example();
  return 0;
}

int sys_clone(void)
{
  int func_add;
  int arg;
  int stack_add;

  if (argint(0, &func_add) < 0){
    cprintf("Error! somthing wrong with the entry function");
    return -1;
  }
  if (argint(1, &arg) < 0){
    cprintf("Error! somthing wrong with the args");
    return -1;
  }
  if (argint(2, &stack_add) < 0){
    cprintf("Error! somthing wrong with the entry stack");
    return -1;
  }
  return clone((void *)stack_add);
  
}

int sys_join(void)
{
  return join();
}
// OUR CODE }