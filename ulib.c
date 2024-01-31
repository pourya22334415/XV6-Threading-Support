#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "mmu.h"
#include "x86.h"


char*
strcpy(char *s, const char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(const char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, const void *vsrc, int n)
{
  char *dst;
  const char *src;
  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}

// Define a function to initialize a lock
int lock_init(lock_t *lock)
{
  // lock: the lock to initialize
  // return: 0 if successful
  lock->flag = 0;
  return 0;
}

// Define a function to acquire a lock
void lock_acquire(lock_t *lock)
{
  // xchg:  atomic exchange register

  // Continuously exchange the flag of the 
  // lock with 1 until it is 0
  while(xchg(&lock->flag, 1) != 0);
}

// Define a function to release a lock
void lock_release(lock_t *lock)
{
  // lock: the lock to release
  // return: None
  // xchg: atomic exchange register

  // Set the flag of the lock to 0
	xchg(&lock->flag, 0);
}

// Define a function to create a new thread
int thread_create(void (*func)(void *, void *), void* arg1, void* arg2)
{
  // func: the function to execute in the new thread
  // arg1: the first argument to pass to the function
  // arg2: the second argument to pass to the function
  // return: the thread ID if successful, -1 if an error occurred

  // Allocate a stack for the new thread
  void* stack;
  stack = malloc(PGSIZE);

  return clone(func, arg1, arg2, stack);
}

// Define a function to join a thread
int thread_join()
{
  // return: the exit status of the joined thread
  
  void * stackPtr;
  int x = join(&stackPtr);
  return x;
}