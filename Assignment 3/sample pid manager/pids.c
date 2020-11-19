/** This sample program uses the included library to create threads with
 * allocated PID numbers.  However, it does not check the return value of
 * allocating a PID.
 *
 * To correctly work, the call that allocates a PID, should really occur inside
 * the thread.
 *
 * The program also has another flaw that would have to be corrected for full
 * functionality.
 *
 */
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pidmanager.h"

#define MAXTHREADS 100
#define MAXSLEEP 10

void *sleepingthread(void *mypid);

int main() {
  /* an array to hold the thread ids */
  pthread_t tid[MAXTHREADS];
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  /** Threads sleep for a random time.  rand() will generate the same sequence
   * unless seeded.  Alternatively for more secure random numbers, the linux
   * kernel random could be read.  A simple seed with sufficient randomness for
   * this case is to use the current time. */
  srand((unsigned)time(NULL));

  /** Calling a function, and testing the return inside an if statement
   * is a C-ism.  Python does not allow this. */
  if (allocate_map() == -1) {
    fprintf(stderr, "Could not allocate pid map\n");
    return -1;
  };

  /** Technically declarations should be at the start of the containing block,
   * but recent versions of C allow declarations more places.  It can add to
   * readabilty to have the declaration close to the place of use. */
  int mypid;
  for (int i = 0; i < MAXTHREADS; ++i) {
    mypid = allocate_pid();

    /** Fourth parameter requires a double cast for proper use.  There are other
     * ways to do this, but the double cast is explict and clearest */
    pthread_create(&tid[i], &attr, sleepingthread, (void *)(intptr_t)mypid);
  }

  /** Utility function in the library to print the list and the pointer values */
  /* print_pids(); */

  for (int i = 0; i < MAXTHREADS; ++i) {
    pthread_join(tid[i], NULL);
  }
  return 0;
}

void *sleepingthread(void *mypid) {
  int pid = (int)mypid;
  printf("Running as pid: %d\n", pid);
  sleep(rand() % MAXSLEEP);
  printf("Releasing pid: %d\n", pid);
  release_pid(pid);
  return NULL;
}
