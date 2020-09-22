#include <stdio.h>

/* Note: constant declaration.
 * This is only a string substitution, so be cautious.  Convention is to
 * upper case constants.
*/
#define MAXLINE 1000

/* Note: function prototypes at start of file.
*/
int mygetline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

/* Note: main should have a return type, and it should be int
*/
int
main() {
  char line[MAXLINE];
  int found = 0;

  while (mygetline(line, MAXLINE) > 0)
    if (strindex(line, pattern) >= 0) {
      printf("%s", line);
      found++;
    }
  return found;
}

/* Note: function bodies after main()
*/
int mygetline(char s[], int lim) {
  int c, i;
  i = 0;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') s[i++] = c;
  if (c == '\n') s[i++] = c;
  s[i] = '\0';
  return i;
}

int strindex(char s[], char t[]) {
  int i, j, k;

  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0') return i;
  }
  return -1;
}

