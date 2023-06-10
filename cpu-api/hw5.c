#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int fork_or_die(){
  int rc = fork();
  assert(rc > -1);
  return rc;
}

int wait_or_die(){
  int rc = wait(NULL);
  assert(rc > -1);
  return rc;
}
int main() {
  if(fork_or_die() == 0){
    //    int err = wait_or_die();

    exit(0);
  }

  int *wstatus = NULL;
  int rc = waitpid(-1, wstatus, WNOHANG);
  
  assert(rc > -1);

  return 0;
}
