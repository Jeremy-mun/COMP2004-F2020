#include "pointnode.h"
#include <stdlib.h>

PointNode *palloc(void){
  return (struct pointnode *)malloc(sizeof(struct pointnode));
}
