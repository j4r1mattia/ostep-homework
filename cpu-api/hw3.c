#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


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

  if(fork_or_die() == 0) {
    printf("hello ");
    exit(0);
  }
  
  printf("goodbye");
  wait_or_die();
  return 0;
}
