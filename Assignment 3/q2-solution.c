/** Assignment 3
 * Question 2
 * Calculate various statistics for a list of numbers.
 * Each statistic will be calculated in a separate thread.  Will this be data
 * parallelism or task parallelism?
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/* the list of integers */
static int *list;

/* the threads will set these values */
static double average;
static int maximum;
static int minimum;

void *calculate_average(void *param);
void *calculate_maximum(void *param);
void *calculate_minimum(void *param);

int main(int argc, char *argv[]) {
  int i;
  int num_of_args = argc - 1;

  pthread_t tid_1;
  pthread_t tid_2;
  pthread_t tid_3;
  /** Alternatively an array could be used
   * pthread_t tid[3];
   */

  /* allocate memory to hold array of integers */
  list = malloc(sizeof(int) * num_of_args);

  /** The actual arguments are always passed as an array of char *, specifically
   * char *argv[argc].  The conversion to integer has no error checking which is
   * not ideal, but for this assignment is sufficient.
   */
  for (i = 0; i < num_of_args; i++)
    list[i] = atoi(argv[i + 1]);

  /* create the threads */
  pthread_create(&tid_1, NULL, calculate_average, &num_of_args);
  pthread_create(&tid_2, 0, calculate_maximum, &num_of_args);
  pthread_create(&tid_3, 0, calculate_minimum, &num_of_args);

  /* wait for the threads to exit */
  pthread_join(tid_1, NULL);
  pthread_join(tid_2, NULL);
  pthread_join(tid_3, NULL);
  /** This is the only place where an array might be easier because a looped join
   * would be possible.  For the case of 3, the compiler would likely inline the
   * loop contents 3 times, so not necessarily a runtime optimisations
   */

  printf("The average is %f\n", average);
  printf("The maximum is %d\n", maximum);
  printf("The minimum is %d\n", minimum);

  return 0;
}

void *calculate_average(void *param) {
  /** Note: only the number of values is passed as a parameter.
   * The global variable "list", a pointer is then used as an array.
   * Note: the global variable is unprotected, it can be changed by the
   * function.  It's important that care be taken not to change any of the
   * values.  This use of a pointer to an array is where the security issues of
   * buffer overflows occurs
   */

  /** Note the name change, passed in address of "num_of_args" to pointer "param"
   * which is dereferenced by the "*" operator to an integer
   */
  int count = *(int *)param;

  int i, total = 0;

  printf("count = %d\n", count);
  for (i = 0; i < count; i++)
    printf("%d\n", list[i]);

  for (i = 0; i < count; i++)
    total += list[i];

  /* Set the global average value.  Could a return be used?  How? */
  average = total / count;

  pthread_exit(0);
}

void *calculate_maximum(void *param) {
  /* See comments in calculate_average */
  int count = *(int *)param;
  int i;

  maximum = list[0];

  for (i = 1; i < count; i++)
    if (list[i] > maximum)
      maximum = list[i];

  pthread_exit(0);
}

void *calculate_minimum(void *param) {
  /* See comments in calculate_average */
  int count = *(int *)param;
  int i;

  minimum = list[0];

  for (i = 1; i < count; i++)
    if (list[i] < minimum)
      minimum = list[i];

  pthread_exit(0);
}
