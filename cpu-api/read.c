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

int main(int argc, char *argv[]) {
  int x = 100;
    // process a
  int f = open("run.output", O_CREAT | O_RDWR, S_IRWXU);
  char parent_buf[] = "This is parent proc that write\n";


  if (fork_or_die() == 0) {
      printf("x in child proc = %d\n", x);
      char children_buf[] = "This is children proc that write\n";
      write(f, children_buf, sizeof(children_buf));
      sleep(3);
      x -= 20;
      printf("x in child proc after change = %d\n", x);
        // process b
      exit(0);
    }
    wait_or_die();
    if (fork_or_die() == 0) {
      char grandchildren_buf[] = "This is grandchildren proc that write\n";
      write(f,grandchildren_buf, sizeof(grandchildren_buf));
      sleep(4);
        // process c
        if (fork_or_die() == 0) {
            sleep(6);
            // process d
            exit(0);
        }
        wait_or_die();
        exit(0);
    }
    if (fork_or_die() == 0) {
        sleep(2);
        // process e
        exit(0);
    }

    //wait_or_die();
    //    wait_or_die();
    write(f, parent_buf, sizeof(parent_buf));
    printf("x in parent proc before wait = %d\n", x);
    x -= 20;
    printf("x in parent proc = %d\n", x);
    //    wait_or_die();
    return 0;
}

