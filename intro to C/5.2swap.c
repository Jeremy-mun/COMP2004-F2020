#include <stdio.h>

void swap(int *x, int *y);

int main() {
  int i, j;
  i = 10; j = 20;
  swap(&i, &j);
  printf("i = %d\nj = %d\n", i, j);
}

void swap(int *x, int *y) 
{
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}
