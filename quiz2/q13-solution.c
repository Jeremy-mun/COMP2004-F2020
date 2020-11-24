/** This code is a simple example of how threads can be used to speed up a
 * program in a multi-core system.  Unfortunately it doesn't function properly.
 * The function run on thread creation wasn't finished, and thus the program
 * doesn't produce any results.  Finish the function calculate_sum so that the
 * sum is correctly calculated.
 *
 * Comment your code with C style comments.  It's not necessary to comment every
 * line, but a comment on the strategy used should be present.
 *
 * There are diagnostic print statements included as well as a hint in the
 * function.
 *
 * Bonus: Find a logic flaw that exists and manifests when the number of threads
 * or values fed in are changed.  Place your answer and a suggested solution
 * strategy AFTER the end of ALL code.  If the bonus instructions are not
 * followed, there will be no bonus marks awarded.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define NUMTHREADS 5

struct thread_data {
  int *valuelist;
  int num_values;
  int sum;
};

void *calculate_sum(void *);

int main(void) {
  int values[] = {1,  3,  5,  7,  9,  2,  6,  7,  0,  10,
                  11, 12, 13, 14, 15, 40, 50, 60, 61, 62};
  int sum = 0;
  int *iter = values;
  pthread_t tids[NUMTHREADS];

  /* Calculate how much data each thread will work on */
  size_t num_values;
  num_values = sizeof(values) / sizeof(*values);
  int num_values_per_thread = num_values / NUMTHREADS;

  /** Standard C doesn't have variable length arrays.  To allocate a dynamic
   * array, calloc can be used.  This is different than dynamically creating a
   * list with multiple malloc calls.
   */
  struct thread_data *d = calloc(NUMTHREADS, sizeof(struct thread_data));
  for (int i = 0; i < NUMTHREADS; i++) {
    /* Using array notation changes -> into . */
    d[i].sum = 0;
    d[i].num_values = num_values_per_thread;
    d[i].valuelist = calloc(num_values_per_thread, sizeof(int));
    for (int j = 0; j < num_values_per_thread; j++) {
      fprintf(stderr, "assigning %d to thread %d \n", *iter, i);
      d[i].valuelist[j] = *iter;
      iter++;
    }
    fprintf(stderr, "\n");
  }

  for (int i = 0; i < NUMTHREADS; i++) {
    pthread_create(&tids[i], NULL, calculate_sum, (void *)&d[i]);
  }

  for (int i = 0; i < NUMTHREADS; i++) {
    pthread_join(tids[i], NULL);
    sum += d[i].sum;
  }
  printf("Sum is: %d\n", sum);
}

void *calculate_sum(void *param) {
  struct thread_data *localdata = (struct thread_data *)param;
  int *iter = localdata->valuelist;
  /** Hint: The localdata pointer also has fields num_values and sum. */

  for (int i = 0; i < localdata->num_values; i++) {
    localdata->sum += *iter;
    fprintf(stderr, "adding %d\n", *iter);
    iter++;
  }

  pthread_exit(NULL);
}
