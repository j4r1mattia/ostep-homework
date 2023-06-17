#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

long getMillis() {
  struct timeval time;
  int rc = gettimeofday(&time, NULL);
  assert(rc > -1);
  return time.tv_usec;
}

int executeWithDuration(int (*f)()){
  long before = getMillis();
  int rc = f();
  long after = getMillis();
  printf("Duration is %ld ms\n", (after - before));
  return rc;
}

void wait_or_die() {
  int rc = wait(NULL);
  assert(rc > 0);
}

int fork_or_die() {
  int rc = fork();
  assert(rc >= 0);
  return rc;
}

int main() {


  if(executeWithDuration(fork_or_die) == 0) {
    printf("hello ");
    exit(0);
  }

  printf("goodbye");
  wait_or_die();
  return 0;
}
