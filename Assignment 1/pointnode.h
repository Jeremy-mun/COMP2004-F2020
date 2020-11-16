#ifndef POINTNODE
#define POINTNODE

#include "pointnode.h"

typedef struct pointnode {
  struct pointnode *next;
  int x;
  int y;
} PointNode;

PointNode *palloc(void);

#endif
