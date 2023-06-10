
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

int fork_or_die() {
  int rc = fork();
  assert(rc > -1);
  return rc;
}

int wait_or_die() {
  int rc = wait(NULL);
  assert(rc > -1);
  return rc;
}

int close_or_die(int fd) {
  int rc = close(fd);
  assert(rc > -1);
  return rc;
}

int main(){
  if(fork_or_die() == 0){
    close_or_die(STDOUT_FILENO);
    printf("Writing after have been closed STDOUT");
    exit(0);
  }
  wait_or_die();
  return 0;
}
