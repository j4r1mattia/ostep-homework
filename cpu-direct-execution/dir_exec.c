#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>



int main() {

  //  struct timeval before, after;
  struct timespec before, after;
  clockid_t clock_id = CLOCK_THREAD_CPUTIME_ID;  

  char buf[99];

  
  int fd = open("./readme.md", O_RDONLY);
  //  clkid = FD_TO_CLOCKID(fd);
  size_t count = 100000;

  //gettimeofday(&before, NULL);
  clock_gettime(clock_id, &before);
  for(size_t i = 0; i <= count; ++i) {
    read(fd, &buf, sizeof(buf));
    //read(fd, NULL, 0);
} 
  clock_gettime(clock_id, &after);
  // gettimeofday(&after, NULL);

  //assert(rc > -1);

  double start = before.tv_sec*100000 + before.tv_nsec/1000;
  double end = after.tv_sec*100000 + after.tv_nsec/1000;
  printf("Avg duration is %f microseconds\n", (end - start)/count);
  return 0;
}
