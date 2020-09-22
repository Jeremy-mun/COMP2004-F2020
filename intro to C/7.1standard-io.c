#include <stdio.h>
#include <ctype.h> /* Utility functions for C variables */

/* lower: convert input to lower case */
int main()
{
  int c;

  while ((c = getchar()) != EOF)
    putchar(tolower(c));
  return 0;
}
