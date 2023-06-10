#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int fork_or_die() {
  int rc = fork();
  assert(rc >= 0);
  return rc;
}

int main() {

  if(fork_or_die() == 0 ){
    int err =  execle("/bin/ls", ".", NULL);
    /* char *args[3]; */
    /* args[0] = "/bin/ls"; */
    /* args[1] = "."; */
    /* args[2] = NULL; */
    /* int err = execv(args[0], args); */
    assert(err < 0);
    exit(0);
  }
  wait(NULL);
  return 0;
}
