#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct pointnode {
  struct pointnode *nextpoint;
  int x;
  int y;
} PointNode;

struct pointnode *palloc(void);

int main() {
  PointNode *headpoint;
  headpoint = palloc();
  (*headpoint).x = 5;
  headpoint->y = 8;
  headpoint->nextpoint = NULL;

  PointNode *x = palloc();
  headpoint->nextpoint = x;
  x->x = 8;
  x->y = 12;
  x->nextpoint = NULL;

  PointNode *iter = headpoint;
  while(iter->nextpoint != NULL){
    printf("%3.2f\n", sqrt(pow(iter->nextpoint->x - iter->x, 2.0) + pow(iter->nextpoint->y - iter->y, 2.0)));
    iter = iter->nextpoint;
  }
}

struct pointnode *palloc(void){
  return (struct pointnode *)malloc(sizeof(struct pointnode));
}
