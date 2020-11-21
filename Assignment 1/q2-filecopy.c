#include "../log.c/src/log.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  log_set_level(LOG_WARN);
  /* Rudimentary check for an actual argument on the command line */
  if (argc < 2) {
    fprintf(stderr, "Too few arguments\n");
    exit(1);
  }
  /* What extra checks would prevent further problems? */

  /** All arguments are char *, or strings.  To use a number the string has
   * to be converted to an integer.  The function atoi() from the stdlib.h
   * performs the conversion */
  int stopvalue = atoi(argv[1]) + 1;

  /* Sol'n 0 */
  log_info("Entering Solution 0");
  for (int i = 1; i < stopvalue; i++) {
    if ((i % 3) == 0 && (i % 5) == 0)
      printf("threefive\n");
    else if ((i % 3) == 0)
      printf("three\n");
    else if ((i % 5) == 0)
      printf("five\n");
    else
      printf("%d\n", i);
  }
  /* Sol'n 0 */

  /* Sol'n 1 */
  log_info("Entering Solution 1");
  for (int i = 1; i < stopvalue; i++) {
    if (!(i % 3) && !(i % 5))
      printf("threefive\n");
    else if (!(i % 3))
      printf("three\n");
    else if (!(i % 5))
      printf("five\n");
    else
      printf("%d\n", i);
  }
  /* Sol'n 1 */

  /* Sol'n 2 */
  log_info("Entering Solution 2");
  for (int i = 1; i < stopvalue; i++) {
    if (!(i % 3))
      printf("three");
    if (!(i % 5))
      printf("five");
    if ((i % 3) && (i % 5))
      printf("%d", i);
    printf("\n");
  }
  /* Sol'n 2 */

  /* Sol'n 4 */
  log_info("Entering Solution 4");
  for (int i = 1; i < stopvalue; i++) {
    printf("%s", (i % 3) ? "" : "three"); /* <if condition> ? <then> : <else> */
    printf("%s", (i % 5) ? "" : "five");
    printf("%.0d", (i % 3) && (i % 5) ? i : 0);
    printf("\n");
  }
  /* Sol'n 4 */
}
