#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 1000000

char *lineptr_p[MAXLINES]; /* pointers to text lines */
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int mygetline(char *, int);
void qsort(char *lineptr[], int left, int right);
void swap(char *v[], int i, int j);
char *alloc(int);

/* sort input lines */
int main() {
  int nlines; /* number of input lines read */

  if ((nlines = readlines(lineptr_p, MAXLINES)) >= 0) {
    writelines(lineptr_p, nlines);
    qsort(lineptr_p, 0, nlines - 1);
    // writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }

  return 0;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
  clock_t start, finish;
  start = clock();

  int len, nlines;
  char *p, line[MAXLEN];
  nlines = 0;
  while ((len = mygetline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0'; /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }

  finish = clock();
  printf("alloc: %f\n", ((double)(finish - start)) / CLOCKS_PER_SEC);
  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++) {
    printf("%s\n", lineptr[i]);
  }

  /* while (nlines-- > 0) printf("%s\n", *lineptr++); */
}

int mygetline(char *s, int lim) {
  int c;
  char *t = s;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') *t++ = c;

  if (c == '\n') *t++ = c;

  *t = '\0';
  return t - s;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right) return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0) swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else
    return 0;
}
