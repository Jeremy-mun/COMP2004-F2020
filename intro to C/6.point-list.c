#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pointnode {
  struct pointnode *nextpoint;
  int x;
  int y;
} PointNode;

struct pointnode *palloc(void);

int main() {
  PointNode *headpoint = 0x0;
  PointNode *i;

  i = palloc();
  i->x = 5;
  i->y = 8;
  i->nextpoint = NULL;
  headpoint = i;

  i = palloc();
  i->x = 8;
  i->y = 12;
  i->nextpoint = NULL;
  headpoint->nextpoint = i;

  i = palloc();
  i->x = 11;
  i->y = 16;
  i->nextpoint = NULL;
  headpoint->nextpoint->nextpoint = i;

  i = palloc();
  i->x = 11;
  i->y = 20;
  i->nextpoint = NULL;
  headpoint->nextpoint->nextpoint->nextpoint = i;

  PointNode *iter = headpoint;
  while (iter->nextpoint != NULL) {
    printf("%3.2f\n", sqrt(pow(iter->nextpoint->x - iter->x, 2.0) +
                           pow(iter->nextpoint->y - iter->y, 2.0)));
    iter = iter->nextpoint;
  }
}

struct pointnode *palloc(void) {
  return (struct pointnode *)malloc(sizeof(struct pointnode));
}
