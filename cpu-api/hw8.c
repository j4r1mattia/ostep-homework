#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include <fcntl.h>

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
  int stdin = open("stdin", O_CREAT | O_WRONLY, S_IRWXU);
  int stdout = open("stdout", O_CREAT | O_RDONLY, S_IRWXU);
  int pipefd[2] = {stdout, stdin};
  int rc = pipe(pipefd);
  assert(rc > -1);

  if(fork_or_die() == 0){
    close(pipefd[0]);
    char mess[] = "This is a message for you"; 
    write(pipefd[1], mess, sizeof(mess));
    close(pipefd[1]);
    exit(0);
  }

  if(fork_or_die() == 0){
    close(pipefd[1]);
    char reader[99];
    read(pipefd[0], reader, sizeof(reader));
    printf("%s\n", reader);
    close(pipefd[0]);
    exit(0);
  }
  waitpid(-1, NULL, 0);
  return 0;
}
